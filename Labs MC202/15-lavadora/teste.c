#include <stdio.h>
#include <math.h>

#define MAX_ROUPAS 100

// Calcula a transferência de cores dentro de um grupo de roupas
double transferencia(int roupas[][3], int indices[], int tamanho) {
    double rm = 0, gm = 0, bm = 0;

    for (int i = 0; i < tamanho; i++) {
        rm += roupas[indices[i]][0];
        gm += roupas[indices[i]][1];
        bm += roupas[indices[i]][2];
    }

    rm /= tamanho;
    gm /= tamanho;
    bm /= tamanho;

    double transf = 0;
    for (int i = 0; i < tamanho; i++) {
        double dr = roupas[indices[i]][0] - rm;
        double dg = roupas[indices[i]][1] - gm;
        double db = roupas[indices[i]][2] - bm;
        transf += dr * dr + dg * dg + db * db;
    }

    return transf;
}

// Função para o caso k = 2, tentando separar os pontos por planos
double transferencia_minima(int roupas[][3], int n) {
    double min_transf = 1e18;

    int indices1[MAX_ROUPAS], indices2[MAX_ROUPAS];

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int *a = roupas[i];
                int *b = roupas[j];
                int *c = roupas[k];

                int ab[3] = {b[0] - a[0], b[1] - a[1], b[2] - a[2]};
                int ac[3] = {c[0] - a[0], c[1] - a[1], c[2] - a[2]};

                int normal[3] = {
                    ab[1]*ac[2] - ab[2]*ac[1],
                    ab[2]*ac[0] - ab[0]*ac[2],
                    ab[0]*ac[1] - ab[1]*ac[0]
                };

                int count1 = 0, count2 = 0;

                for (int r = 0; r < n; r++) {
                    if (r == i || r == j || r == k) continue;

                    int diff[3] = {
                        roupas[r][0] - a[0],
                        roupas[r][1] - a[1],
                        roupas[r][2] - a[2]
                    };

                    int dot = diff[0]*normal[0] + diff[1]*normal[1] + diff[2]*normal[2];

                    if (dot > 0)
                        indices1[count1++] = r;
                    else if (dot < 0)
                        indices2[count2++] = r;
                    else {
                        if (count1 <= count2)
                            indices1[count1++] = r;
                        else
                            indices2[count2++] = r;
                    }
                }

                // Inclui A, B, C no grupo 1
                indices1[count1++] = i;
                indices1[count1++] = j;
                indices1[count1++] = k;

                if (count1 == 0 || count2 == 0) continue;

                double transf1 = transferencia(roupas, indices1, count1);
                double transf2 = transferencia(roupas, indices2, count2);
                double total = transf1 + transf2;

                if (total < min_transf)
                    min_transf = total;
            }
        }
    }

    return min_transf;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int roupas[MAX_ROUPAS][3];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &roupas[i][0], &roupas[i][1], &roupas[i][2]);
    }

    double resultado;

    if (k == 1) {
        int indices[MAX_ROUPAS];
        for (int i = 0; i < n; i++) indices[i] = i;
        resultado = transferencia(roupas, indices, n);
    } else {
        resultado = transferencia_minima(roupas, n);
    }

    printf("%.6lf\n", resultado);
    return 0;
}
