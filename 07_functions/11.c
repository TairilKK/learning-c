#include <stdio.h>

int concat_begin(const int first[], int size, const int second[], int size2, int dest[], int size3);
int concat_end(const int first[], int size, const int second[], int size2, int dest[], int size3);
int concat_zip(const int first[], int size, const int second[], int size2, int dest[], int size3);

int read_vector(int vec[], int size, int stop_value);
void display_vector(const int vec[], int size);

int main()
{
    int L1, L2, l_begin, l_end, l_zip;
    int size=50;
    int vec1[50], vec2[50], vec3[100];
    int stop_value=0;
    printf("Podaj pierwszy wektor: ");
    L1 = read_vector(vec1,size,stop_value);
    if(L1 == -2)
    {
        printf("incorrect input");
        return 1;
    }
    else if(L1== -1)
    {
        printf("not enough data available");
        return 2;
    }
    while(getchar()!='\n');
    printf("Podaj drugi wektor: ");
    L2 = read_vector(vec2,size,stop_value);
    if(L2 == -2)
    {
        printf("incorrect input");
        return 1;
    }
    else if(L2 == -1)
    {
        printf("not enough data available");
        return 2;
    }
    display_vector(vec1, L1);
    display_vector(vec2, L2);
    
    if(L1 + L2>50)
    {
        printf("Output buffer is too small");
        return 0;
    }
    l_begin = concat_begin(vec1, L1, vec2, L2, vec3, L1 + L2);
    if(l_begin != -2 && l_begin != -1)
    {
        for(int i=0; i<L1 + L2; i++)
            printf("%d ", vec3[i]);
        printf("\n");
    }
    l_end = concat_end(vec1, L1, vec2, L2, vec3, L1 + L2);
    if(l_end != -2 && l_end != -1)
    {
        for(int i=0; i<L1 + L2; i++)
            printf("%d ", vec3[i]);
        printf("\n");
    }
    l_zip = concat_zip(vec1, L1, vec2, L2, vec3, L1 + L2);
    if(l_zip != -2 && l_zip != -1)
    {
        for(int i=0; i<L1 + L2; i++)
            printf("%d ", vec3[i]);
        printf("\n");
    }
    return 0;
}
int concat_begin(const int first[], int size, const int second[], int size2, int dest[], int size3){
    if(size<1 || size2<1 || size3<1)
        return -1;
    else if(size+size2>size3)
        return -2;

    int i=0;
    while(i<size){
        dest[i]=first[i];
        i++;
    }
    int j=0;
    while(i<size3&&j<size2){
        dest[i]=second[j];
        j++;
        i++;
    }
    return size3;
}
int concat_end(const int first[], int size, const int second[], int size2, int dest[], int size3){
    if(size<1 || size2<1 || size3<1)
        return -1;
    else if(size+size2>size3)
        return -2;

    int i=0;
    while(i<size2){
        dest[i]=second[i];
        i++;
    }
    int j=0;
    while(i<size3&&j<size){
        dest[i]=first[j];
        j++;
        i++;
    }
    return size3;
}
int concat_zip(const int first[], int size, const int second[], int size2, int dest[], int size3){
    if(size<1 || size2<1 || size3<1)
        return -1;
    else if(size+size2>size3)
        return -2;

    int i=0,j=0,k=0;
    while(i<size3){
        if(i%2==0 && j<size||k>size2-1){
            dest[i]=first[j];
            i++;
            j++;
        }
        else if(k<size2||j>size-1){
            dest[i]=second[k];
            i++;
            k++;
        }
    }
    return size3;
}
int read_vector(int vec[], int size, int stop_value){
    int l=0;
    for(int i=0; i<size ;i++)   {
        if(scanf("%d",&vec[i])!= 1)
            return -2;
        else if(i==0 && vec[i] == stop_value)
            return -1;
        else if(vec[i] == stop_value)
            return l;
        l++;
    }
    if(l<1)
        return -1;
    else
        return l;
}
void display_vector(const int vec[], int size){
    if(size>0){
        for(int i=0;i<size;i++)
            printf("%d ",vec[i]);
        printf("\n");
    }
}
