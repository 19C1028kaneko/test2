#include <stdio.h>
#include <math.h>

#define EPS (0.0000001)
//#define f(x) (x*x+x-1)
//#define df(x) (2*x+1)

//#define f(x) (3*x*x+2*x-5)
//#define df(x) (6*x+2)

//#define f(x) (10*x*x+15*x+12)
//#define df(x) (20*x+15)

#define f(x) (x*x*x-3*x*x+9*x-8)
#define df(x) (3*x*x-6*x+9)

int main(void){
	int n = 0;
	int nmax = 300;
	double xnew, xold;
	FILE *fp;
	fp = fopen("out3.txt", "w");  
	xnew = (xold = 2) + 1;
	do{
		n++;
		xold = -1 *f(xnew) / df(xnew);
		xnew = xnew + xold;
		printf("%d[%lf]\n",n,xnew);
		fprintf(fp, "%d %lf\r\n",n,xnew);		
	}while(fabs(xold) > EPS && n <= nmax);
	if(n >= nmax){
		printf("収束しなかった\n");
	}
	else{
		printf("近似解は %f \n" ,xnew);
	}
}


	
