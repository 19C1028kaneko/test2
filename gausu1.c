#include<stdio.h>
#include<math.h>
#include <string.h>
#define EPS (1e-5) 					//収束する値を設定
FILE *fp;
int N;
char fop(){						//ファイルの読み込みとエラー判定関数
	char fname[50];
	scanf("%s", fname);				//ファイル名入力
	fp=fopen(fname,"r");				//ファイルの読み込み
	if(fp==NULL){					//ファイルが読み込み判定
		printf("ファイルがありません\nキーボード入力に移行します\n");
		return 'n';
	}
	return 'y';
}
double pgr(double a[][N]){ 				//読み込み確認関数　係数行列
	int i,j;
	printf("==import==\n");
	for(i=0; i<N; i++){
		printf("[");
		for(j = 0; j < N; j++){
			printf("%9.5f  ", a[i][j]);
		}
		printf("]\n");
	}
	return 0;
}

double phd(double *b){					//読み込み確認関数　被同次項
	int i;
	printf("==import==\n");
	for(i=0; i<N; i++){
		printf("[%9.5f]\n", b[i]);
	}
	return 0;
}

int main(){

	printf("係数行列のサイズ指定\n");
	scanf("%d", &N);				//行列のサイズ指定

	double a[N][N], b[N], x[N], sz;
	double dx, abx, sum, new;
      	int i, j;
	int m = 0;
	char fh[5];
	printf("初期値の入力=>");			
	scanf("%lf", &sz);				//初期値の入力
		
	for(i = 0; i < N; i++){				//初期値の代入
		x[i] = sz;
	}

	printf("ファイル入力しますか？[y/n]");		//ファイル入力かキーボード入力か確認 ＊ファイル入力とキーボード入力ができる＊
	scanf("%s", &fh[0]);

	if(fh[0] == 'y'){				//ファイル入力判定
		printf("==ファイル入力==\n");
		printf("係数行列を定義します\n読み込むファイルを指定してください＝>");
		fh[0]=fop();				//ファイル読み込み関数
		for(i = 0; i < N; i++)			//係数行列書き込みループ
		{
			for(j = 0; j < N; j++){
				fscanf(fp,"%lf",&a[i][j]);
			}
		}

		pgr(a);					//読み込み確認関数

		printf("被同次項を定義します\n読み込むファイルを指定してください＝>");
		fh[0]=fop();				//ファイル読み込み関数
		for(i = 0; i < N; i++){			//被同次項書き込みループ
			fscanf(fp,"%lf",&b[i]);
		}

		phd(b);					//読み込み確認関数

		printf("正しいファイルを読み込んだ？[y/n]");//ファイル読み込み確認
		scanf("%s", &fh[0]);

	}
	if(fh[0] != 'y'){				//キーボード入力判定
		printf("==キーボード入力==\n係数行列の定義\n");
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				printf("%d行%d列目＝＞", i+1, j+1);
				scanf("%lf", &a[i][j]);	//行列を入力
			}			
		}

		pgr(a);					//読み込み確認関数

		printf("被同次項の定義\n");
		for(i = 0; i < N; i++){			
			printf("b[%d]=",i+1);
			scanf("%lf", &b[i]);		//被同次項の入力
		}
	}

	do{
		m++;
		printf("[%3d]", m);			//ループ回数表示
		dx=0.0;
		abx=0.0;
		for(i=0; i<N; i++){			//ガウス・ザイデル計算ループ
			sum = 0;
			for(j=0; j<N; j++){
				if(i != j){ 		//i==jの時は計算しない
					sum+=a[i][j]*x[j]; //反復計算
				}
				}
			new=1.0/a[i][i]*(b[i]-sum); 	//反復計算後の近似解
			dx+=fabs(new-x[i]); 		//近似解の変化を加算
			abx+=fabs(new);			//近似解の総和計算
			x[i]=new;			//新しい近似解を代入
			printf("%25.20f", x[i]);	//近似解を出力
		}
		printf("\n");
		if(m >= 500){				//500ループ以上になったら強制終了
			printf("==収束できない==\n");
			break;
		}
	}while(dx/abx > EPS);				//収束判定

	for(i=0; i<N; i++){				//出力ループ
		printf("x[%2d]=%8.5f\n",i+1,x[i]);	//結果の出力
	}	
}
