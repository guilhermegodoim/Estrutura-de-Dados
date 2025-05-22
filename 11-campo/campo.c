#include<stdio.h>
#include<math.h>

// a função a seguir calcula a distância entre dois pontos no plano xyz.
// a função recebe como parâmetros os valores de x, y, z dos dois pontos
// e retorna a distância entre eles.

float dist(int x1, int y1, int z1, int x2, int y2, int z2){
    float distancia;
    distancia = sqrt(((x1 - x2)*(x1 - x2)) + ((y2-y1) * (y2-y1)) + ((z2 - z1)*(z2-z1)));
    return distancia;

}

int main(){
    while (1){

    int n;
    scanf("%d",&n);
    if (n < 0){
        break;
    }
    
    float xr, yr, xg, yg, zg; // xr e yr para coordenada do rato, e g para o gaviao
    scanf("%f %f %f %f %f" ,&xr,&yr,&xg,&yg,&zg );
    
    int i;
    int contador = 0;
    
    for (i=0; i < n; i++){
        float xb, yb; // coordenadas do buraco
        scanf("%f %f",&xb,&yb);

        float t1, t2; // t1 é o tempo para o rato alcançar o buraco e t2 o do gavião
        t1 = dist(xr, yr, 0, xg, yg, zg);
        printf("%.3f/n", t1);
        t2 = dist(xg, yg, zg, xb, yb, 0)/2;
        printf("%.3f/n", t2);
        
        if (t1 < t2){
            printf("O rato pode escapar pelo buraco\n");
            break;
        
            } else {
                contador++;
                }


        }
    if (contador == n){
        printf("O rato não consegue escapar/n");
    }
    }
}