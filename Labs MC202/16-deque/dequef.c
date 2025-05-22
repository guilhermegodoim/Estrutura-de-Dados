#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef *df_alloc(long capacity, double factor){
    // possíveis casos de falha:
    if (capacity <= 0 || factor <= 1.0)
	return NULL;

    dequef *deque = malloc(sizeof(dequef));
    if (!deque)
	return NULL;

    deque->data = malloc(capacity * sizeof(float));
    if (!deque->data) {
	free(deque);
	return NULL;
    }
    // inicializando a struct
    deque->first = 0;
    deque->size = 0;
    deque->cap = capacity;
    deque->mincap = capacity;
    deque->factor = factor;

    return deque;
}



/**
  Release a dequef and its data.
**/
void df_free(dequef * D){
    if (D != NULL) {
	free(D->data);
	free(D);
    }
}



/**
   The size of the deque.
**/
long df_size(dequef * D){
    if (D == NULL){
    return 0;}
    
    return D->size;
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef * D, float x){
    if (D == NULL)
	    return 0;

    // checar se o deque está cheio ou não
    if (D->size == D->cap) {	
        long nova_cap = (long) (D->cap * D->factor);
        float *novo_dados = malloc(nova_cap * sizeof(float));
	
    if (novo_dados == NULL) {
	    return 0;
	}
	
    for (long i = 0; i < D->size; i++) {
	    novo_dados[i] = D->data[(D->first + i) % D->cap];
	}

    free(D->data);
	D->data = novo_dados;
	D->cap = nova_cap;
	D->first = 0;
   }

   // adicionando o elemento 
   long pos = (D->first + D->size) % D->cap;
   D->data[pos] = x;
   D->size++;

   return 1;
}



/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, the returned float is meaningless.
**/
float df_pop(dequef * D){
    if (D == NULL || D->size == 0)
	return 0;

    long fim = (D->first + D->size - 1) % D->cap;
    float valor = D->data[fim];
    D->size--;

    double fator_quadrado = D->factor * D->factor;
    if (D->size <= D->cap / fator_quadrado && D->cap > D->mincap) {
	long capacidade_nova = (long) (D->cap / D->factor);
	if (capacidade_nova < D->mincap)
	    capacidade_nova = D->mincap;

	float *nova_info = malloc(capacidade_nova * sizeof(float));
	if (nova_info != NULL) {
	    for (long i = 0; i < D->size; i++) {
		nova_info[i] = D->data[(D->first + i) % D->cap];
	    }

	    free(D->data);
	    D->data = nova_info;
	    D->cap = capacidade_nova;
	    D->first = 0;
	}
    }

    return valor;
}




/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef * D, float x){
    if (D == NULL)
	return 0;

    if (D->size == D->cap) {
	long capacidade_nova = (long) (D->cap * D->factor);
	float *nova_info = malloc(capacidade_nova * sizeof(float));
	if (nova_info == NULL)
	    return 0;

	for (long i = 0; i < D->size; i++) {
	    nova_info[i] = D->data[(D->first + i) % D->cap];
	}

	free(D->data);
	D->data = nova_info;
	D->cap = capacidade_nova;
	D->first = 0;
    }
    
    D->first = (D->first - 1 + D->cap) % D->cap;
    D->data[D->first] = x;
    D->size++;

    return 1;}


/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, the returned float is meaningless.
**/
float df_eject(dequef * D){
    if (D == NULL || D->size == 0)
	return 0;

    float valor_remov = D->data[D->first];
    D->first = (D->first + 1) % D->cap;
    D->size--;

    double fator_quadrado = D->factor * D->factor;
    if (D->size <= D->cap / fator_quadrado && D->cap > D->mincap) {
	long capacidade_nova = (long) (D->cap / D->factor);
	if (capacidade_nova < D->mincap)
	    capacidade_nova = D->mincap;

	float *nova_info = malloc(capacidade_nova * sizeof(float));
	if (nova_info != NULL) {
	    for (long i = 0; i < D->size; i++) {
		nova_info[i] = D->data[(D->first + i) % D->cap];
	    }

	    free(D->data);
	    D->data = nova_info;
	    D->cap = capacidade_nova;
	    D->first = 0;
	}
    }

    return valor_remov;
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef * D, long i, float x)
{
    if (D == NULL || i < 0 || i >= D->size)
	return;

    long id_x = (D->first + i) % D->cap;
    D->data[id_x] = x;
}





/**
   Return D[i].

   If i is not in [0,|D|-1]] the returned float is meaningless.
**/
float df_get(dequef * D, long i)
{
    if (D == NULL || i < 0 || i >= D->size)
	return 0;

    long id_x = (D->first + i) % D->cap;
    return D->data[id_x];
}


/**
   Print the elements of D in a line.
**/
void df_print(dequef * D)
{
    if (D == NULL) {
	return;
    }

    printf("deque (%ld):", D->size);

    for (long i = 0; i < D->size; i++) {
	long id_x = (D->first + i) % D->cap;
	printf(" %.1f", D->data[id_x]);
    }

    printf("\n");
}