#include<stdio.h>
#include<stdlib.h>

struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct data data;



int main(){
    data dob;

    printf("Quando é seu aniversário?\n");

    scanf("%d/%d/%d", &dob.dia, &dob.mes, &dob.ano);

    printf("A festa será no dia %d/%d/%d\n", dob.dia+1, dob.mes, dob.ano);
    
    return 0;

}