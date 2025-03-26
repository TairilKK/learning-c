#include <stdio.h>

int read_vector_double(double vec[], int size, double stop_value);
double horner(double a[], double x, int n);

int main()
{
    double x, vec[101];
    printf("Podaj wspolczynniki wielomianu:\n");
    int n=read_vector_double(vec,100,0);
    if(n == -2){
        printf("incorrect input");
        return 1;
    }
    else if(n== -1){
        printf("not enough data available");
        return 3;
    }
    printf("Podaj zmienna x:\n");
    if(scanf("%lf",&x)!=1){
        printf("incorrect input");
        return 1;
    }
    
    printf("W=%lf",horner(vec,x,n));
    
    return 0;

        
    }
int read_vector_double(double vec[], int size, double stop_value){
    int l=0;
    for(int i=0; i<size ;i++){
        if(scanf("%lf",&vec[i])!= 1)
            return -2;
        else if(i==0 && vec[i] == stop_value)
            return -1;
        else if(vec[i] == stop_value){
            while(getchar()!='\n');
            return l;
        }
        l++;
    }
    if(l<1)
        return -1;
    else{
        while(getchar()!='\n');
        return l;
    }
}

double horner(double a[], double x, int n){
    if(n<1)
        return -1;
    if(n==1)
		return a[0];
	
	return x*horner(a,x,n-1)+a[n-1];
}
