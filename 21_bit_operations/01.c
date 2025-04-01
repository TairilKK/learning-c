#include <stdio.h>

int is_equal(int a, int b);
int is_negative(int value);

int main() {
    int a, b;
    
    printf("Podaj dwie liczby:\n");
    int res = scanf("%d %d", &a, &b);
    if(!is_equal(res,2)){
        printf("Incorrect input");
        return 1;
    }
    
    res = is_equal(a ,b);
    if(is_equal(res,1))
        printf("rowne");
    else
        printf("nierowne");
    printf("\n");
	
    res = is_negative(a);
    if(is_equal(res,1))
        printf("ujemna");
    else
        printf("nieujemna");
    printf(" ");
	
	
		res = is_negative(b);
		if(is_equal(res,1))
			printf("ujemna");
		else
			printf("nieujemna");
		printf("\n");
	

    return 0;
}

int is_negative(int value){
	int s = (sizeof (int) * 8);
	--s;
    if(value >> s&1)
        return 1;
    return 0;
}
int is_equal(int a, int b){
	int s = (sizeof (int) * 8);
	--s;
    for(int i = s; !is_negative(i); --i)
        if((a>>i)^(b>>i))
            return 0;
    return 1;
}
