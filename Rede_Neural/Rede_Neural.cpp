#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <locale.h>



int i, j;
int entradaOrigem[100] = { 0, 1, 1, 1, 1, 0, 0, 0 ,0}; // dados a serem alimentados nos modelos
int camada;
int config[6]; //configuração dos neuronios por camada
float delta[10000];
float taxaAprendizagem;

void degrauUnitario();

struct criarNeuronio {
    int numero;
    float entrada[10000];
    int peso[10000];
    int camada;
   // int funcaoAtivacao;
    float saida;

};
struct criarNeuronio neural[10000];


void criarNeuronio() { 
    int contador = 0;
    for (i = 0; i < config[0]; i++) {   // para a primeira camada recebe a entrada e alimentação
        neural->numero = contador;
        *neural[contador].entrada = entradaOrigem[i];
        neural->camada = 1;
        degrauUnitario();

        contador++;
    }
    for (i = 0; i < config[1]; i++) {
       int temp = contador;
        for (i = 0; i < config[0]; i++) {
            neural->numero = contador;
            
            *neural[temp].entrada = neural[i].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 2;
            degrauUnitario();
            contador++;
        }
        
    }
    for (i = 0; i < config[2]; i++) {
        int temp = contador;
        for (i = 0; i < config[1]; i++) {
            neural->numero = contador;

            *neural[temp].entrada = neural[i].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 3;
            degrauUnitario();
            contador++;
        }
    }
    for (i = 0; i < config[3]; i++) {
        int temp = contador;
        for (i = 0; i < config[2]; i++) {
            neural->numero = contador;

            *neural[temp].entrada = neural[i].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 4;
            degrauUnitario();
            contador++;
        }
    }
    for (i = 0; i < config[4]; i++) {
        int temp = contador;
        for (i = 0; i < config[3]; i++) {
            neural->numero = contador;

            *neural[temp].entrada = neural[i].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 5;
            degrauUnitario();
            contador++;
        }
    }
    for (i = 0; i < config[5]; i++) {
        int temp = contador;
        for (i = 0; i < config[4]; i++) {
            neural->numero = contador;

            *neural[temp].entrada = neural[i].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 6;
            degrauUnitario();
            contador++;
        }
    }

}


void treinamentoRede() {
    printf("Digite a quantidade de camadas! \n");
    scanf_s("%i", &camada);                                                     // entrada de numero de camadas da rede
    printf("A rede neural sera com %i camada(s)!\n", camada);
    for ( i = 0; i < camada; i++)  {
        printf("Digite a quantidade de neuronios na camada %i!\n",i+1);
        int x;
        scanf_s("%i", &x);                                                     //entrada do numero de nerônios por camada
        config[i] = x;
    }
    printf("Digite a taxa de aprendizagem! \n");
    scanf_s("%f", &taxaAprendizagem);

    criarNeuronio();

}

void regraDelta() {
    delta[i] = taxaAprendizagem * *neural->peso;
}

void degrauUnitario() {//função de degrau unitario
    float func01;
    float temp=0;
    int cont=0;
    for ( i = 0; i < 10000; i++){
        if (neural->entrada[i]) {
            temp = temp + *neural->entrada;
            cont++;
        }
        func01 = (temp / cont);
        if (func01 <0){
            func01 = -1;
        }
        func01 = 1;
    }
    neural->saida = func01;
}


void usoRede() {
    criarNeuronio();
    printf_s("Ainda não fiz!");
}
void teste() {
    for ( i = 0; i < 100; i++)
    {
        printf_s("%d",i);
        printf_s(" teste %s \n", neural->numero);
        printf("%s", neural->saida);
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    printf_s("Escolha uma opção\n");
    printf_s("1 : treinamento\n");
    printf_s("2 : usar rede\n");
    printf_s("3 : teste\n");

    int x,z=0;

    scanf_s("%i", &x);
    while (z!=1)
    {
    switch (x)
    {
    case 1:
        treinamentoRede();
        break;
    case 2:
        usoRede();
        break;
    case 3:
        for ( i = 0; i < 100; i++)
        {
            printf("%d",entradaOrigem[i]);
        }
        
        teste();
        break;
    case 4:
        z = 1;
    default:
        break;
    }
    system ("pause");
    }
}
