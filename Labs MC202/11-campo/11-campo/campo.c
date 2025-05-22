#include<stdio.h>
#include<math.h>

// a função a seguir calcula a distância entre dois pontos no plano xyz.
// a função recebe como parâmetros os valores de x, y, z dos dois pontos
// e retorna a distância entre eles.

double dist(double x1, double y1, double z1, double x2, double y2, double z2){
    double distancia;
    distancia = sqrt(((x1 - x2)*(x1 - x2)) + ((y2-y1) * (y2-y1)) + ((z2 - z1)*(z2-z1)));
    return distancia;

}

int main(){
    while (1){

    int n;
    scanf("%d", &n);
    
    if (n < 0){
        break;
    }
    
    double xr, yr, xg, yg, zg; // xr e yr para coordenada do rato, e g para o gaviao
    scanf("%lf %lf %lf %lf %lf" ,&xr,&yr,&xg,&yg,&zg );
    
    int i;
    int contador = 0;
    double xb, yb; // coordenadas do buraco
    double xb_salvo = -1, yb_salvo = -1;; // salva a coordenada do primeiro buraco que o rato pode escapar
    int encontrou = 0; // serve para saber se o 
    
    for (i=0; i < n; i++){

        scanf("%lf %lf",&xb,&yb);

        double t1, t2; // t1 é o tempo para o rato alcançar o buraco e t2 o do gavião
        t1 = dist(xr, yr, 0, xb, yb, 0);
        //printf("tempo para o rato chegar no buraco: %.3f\n", t1);
        t2 = dist(xg, yg, zg, xb, yb, 0)/2.0;
        //printf("tempo para o gavião alcancar o rato: %.3f\n", t2);
        
        
        if (t1 < t2 && !encontrou){
            xb_salvo = xb;
            yb_salvo = yb;
            encontrou = 1;

        
            } else {
                contador++;
                }
        }
    if (contador == n && !encontrou){
        printf("O rato nao pode escapar.\n");
    } else if (encontrou && xb_salvo != -1 && yb_salvo != -1){
        printf("O rato pode escapar pelo buraco (%.3f,%.3f).\n", xb_salvo, yb_salvo);
    }
    }
    
    return 0;
}