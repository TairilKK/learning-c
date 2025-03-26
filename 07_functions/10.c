#include <stdio.h>
#include <math.h>

double mySin(double x, int n);
double myCos(double x, int n);
int fact(int k);

int main()
{
    double x;
    int n;
    int c=0;
    printf("Podaj wartosc kata, dla ktorego chcesz obliczyc wartosc funkcji sin i cos: ");
    c=scanf("%lf",&x);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    printf("Podaj liczbÄ wyrazĂłw szegegu Taylora: ");
    c=scanf("%d",&n);
    if(c!=1||n<0){
        printf("incorrect input");
        return 1;
    }
    printf("%lf %lf",mySin(x,n),myCos(x,n));
    
    
    return 0;
}
double mySin(double x, int n){
    double res=0;
    if(n<0)
        return -1;
    for(int k=0;k<=n;k++){
        res+=(pow(-1,k)/fact(2*k+1))*pow(x,2*k+1);
    }
    return res;
}
double myCos(double x, int n){
    double res=0;
    if(n<0)
        return -1;
    for(int k=0;k<=n;k++){
        res+=(pow(-1,k)/fact(2*k))*pow(x,2*k);
    }
    return res;
}

int fact(int x){
    int res=1;
    if(x>0){
        for(int i=1;i<=x;i++){
            res*=i;
        }
    }
    return res;
}
