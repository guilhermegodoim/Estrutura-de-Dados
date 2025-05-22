#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pontuacao {
    int soad, a7x, guns, metallica, megadeth, rhcp, nirvana, acdc, aerosmith, pinkfloyd;
};

typedef struct pontuacao pt;

int main() {
    const char *candidatos[10] = {
        "SOAD", "A7X", "GUNS", "METALLICA", "MEGADETH",
        "RHCP", "NIRVANA", "AC/DC", "AEROSMITH", "PINK FLOYD"
    };

    pt art = {0}; // zera todos os campos

    while (1) {
        int voto;
        printf("Digite seu voto (1 a 10) ou 0 para sair: ");
        scanf("%d", &voto);

        if (voto == 0) {
            break; // encerra votação
        }

        switch (voto) {
            case 1: art.soad++; break;
            case 2: art.a7x++; break;
            case 3: art.guns++; break;
            case 4: art.metallica++; break;
            case 5: art.megadeth++; break;
            case 6: art.rhcp++; break;
            case 7: art.nirvana++; break;
            case 8: art.acdc++; break;
            case 9: art.aerosmith++; break;
            case 10: art.pinkfloyd++; break;
            default:
                printf("Voto inválido! Digite um número entre 1 e 10.\n");
                break;
        }
    }

    printf("\nResultado da votação:\n");
    printf("%s: %d votos\n", candidatos[0], art.soad);
    printf("%s: %d votos\n", candidatos[1], art.a7x);
    printf("%s: %d votos\n", candidatos[2], art.guns);
    printf("%s: %d votos\n", candidatos[3], art.metallica);
    printf("%s: %d votos\n", candidatos[4], art.megadeth);
    printf("%s: %d votos\n", candidatos[5], art.rhcp);
    printf("%s: %d votos\n", candidatos[6], art.nirvana);
    printf("%s: %d votos\n", candidatos[7], art.acdc);
    printf("%s: %d votos\n", candidatos[8], art.aerosmith);
    printf("%s: %d votos\n", candidatos[9], art.pinkfloyd);

    return 0;
}
