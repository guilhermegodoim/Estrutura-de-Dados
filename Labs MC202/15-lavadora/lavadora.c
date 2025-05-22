#include<stdio.h>
#include<math.h>
#define MAX_ROUPAS 100
#define MAX_K 2

/* a ideia geral do algoritmo é:
1. pra cada combinação de 3 roupas gerar um plano (prod. vetorial)
2. ver de qual lado do plano cada outro ponto está
3. criar dois grupos com base nessa separação
4. calcular a transferencia total de cores
5. ver qual é a menor transferencia possivel
*/

// funções auxiliares: utilizaremos v1 e v2 para denotar dois vetores 

// dado dois vetores tridimensionais(x,y,z) v1 e v2, retorna o vetor normal entre eles

void produto_vetorial(int v1[3], int v2[3], int v_normal[3]){
    v_normal[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v_normal[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v_normal[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

int produto_escalar(int v1[3], int v2[3]){
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

// funções para calcular a transferência de cores:

double transferencia(int roupas[][3], int indices[], int n){
    double rm = 0, gm = 0, bm = 0;
    int i;

    for (i = 0; i < n; i++){
        rm += roupas[indices[i]][0];
        gm += roupas[indices[i]][1];
        bm += roupas[indices[i]][2];
    }

    rm = rm / n;
    gm = gm / n;
    bm = bm / n;

    // printf("médias - r: %.4lf, g: %.4lf, b: %.4lf\n", rm, gm, bm);

    double transf = 0;
    for (i = 0; i < n; i++) {
        double dr = roupas[indices[i]][0] - rm;
        double dg = roupas[indices[i]][1] - gm;
        double db = roupas[indices[i]][2] - bm;
        transf += dr * dr + dg * dg + db * db;
    }

    return transf;
    }


double transferencia_minima(int roupas[][3], int n) {
    double menor = 1000000000;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                
                int AB[3] = {
                    roupas[j][0] - roupas[i][0],
                    roupas[j][1] - roupas[i][1],
                    roupas[j][2] - roupas[i][2]
                };
                int AC[3] = {
                    roupas[k][0] - roupas[i][0],
                    roupas[k][1] - roupas[i][1],
                    roupas[k][2] - roupas[i][2]
                };
                int normal[3];
                produto_vetorial(AB, AC, normal);

                // classificar roupas com base na divisão do plano
                int grupo1[MAX_ROUPAS], grupo2[MAX_ROUPAS];
                int tam1 = 0, tam2 = 0;

                int r;
                for (r = 0; r < n; r++) {
                    int AP[3] = { // AP denota aqui a distancia entre um ponto A (uma roupa qualquer) até um outro ponto P (outra roupa qualquer)
                        roupas[r][0] - roupas[i][0],
                        roupas[r][1] - roupas[i][1],
                        roupas[r][2] - roupas[i][2]
                    };
                    int prod = produto_escalar(normal, AP);

                    if (prod >= 0) grupo1[tam1++] = r;
                    else grupo2[tam2++] = r;
                }

                double c1 = transferencia(roupas, grupo1, tam1);
                double c2 = transferencia(roupas, grupo2, tam2);
                double total = c1 + c2;

                if (total < menor)
                    menor = total;
            }
        }
    }

    return menor;
}


int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    
    // vamos representar as roupas numa matriz, em que cada coluna representa a qt. de cada
    // cor (r,g,b) da roupa.

    int roupas[MAX_ROUPAS][3];  // coluna 0 = red, 1 = green, 2 = blue
    int i;
    for(i=0;i<n;i++){
        int r,g,b;
        scanf("%d %d %d",&r,&g,&b);
        roupas[i][0]=r;
        roupas[i][1]=g;
        roupas[i][2]=b;
        }
        
    double resultado;
    if (k == 1) {
        int indices[MAX_ROUPAS]; // cria uma lista com os índices das roupas pra facilitar a determinação dos lotes; tentar fazer isso só com n deu problema
        for (int i = 0; i < n; i++) indices[i] = i;
        resultado = transferencia(roupas, indices, n);
    } else {
        resultado = transferencia_minima(roupas, n);
    }

    printf("%.6lf\n", resultado);
    
    
    return 0; 
}