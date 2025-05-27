#include<stdio.h>
#include "funcoes.h"

int main() {
    char comando;
    no * lista = NULL;

    while(1){
        scanf("%c", &comando);

        if (comando == 'c'){
            lista = criar_lista();        
        }
        else if (comando == 'i'){
            int p;
            double x;
            scanf("%d %lf", &p, &x);
            inserir(&lista, x, p);  
        }
        else if (comando == 'r'){
            int p;
            scanf("%d", &p);
            remover(&lista, p);
        }
        else if (comando == 'p'){
            imprimir(lista);
        }
        else if (comando == 'v'){
            int i, t;
            scanf("%d %d", &i, &t);
            reverter(&lista, i, t);
        }
        else if (comando == 'x'){
            int i, t, p;
            scanf("%d %d %d", &i, &t, &p);
            mover(&lista, i, t, p);
        }
        else if (comando == 't'){
            terminar();
            break;
        }
    }
    return 0;
}