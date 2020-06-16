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
    int k;
    for (i = 0; i < config[0]; i++) {   // para a primeira camada recebe a entrada e alimentação
        neural[contador].numero = contador;
        *neural[contador].entrada = entradaOrigem[i];
        neural->camada = 1;
        degrauUnitario();

        contador++;
    }
    for (i = 0; i < config[1]; i++) {
       int temp = contador;
        for (k = 0; k < config[0]; k++) {
            neural[contador].numero = contador;
            
            *neural[temp].entrada = neural[k].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 2;
            degrauUnitario();
            contador++;
        }  
    }
    for (i = 0; i < config[2]; i++) {
        int temp = contador;
        for (k = 0; k < config[1]; k++) {
            neural[contador].numero = contador;

            *neural[temp].entrada = neural[k].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 3;
            degrauUnitario();
            contador++;
        }
    }
    for (i = 0; i < config[3]; i++) {
        int temp = contador;
        for (k = 0; k < config[2]; k++) {
            neural[contador].numero = contador;

            *neural[temp].entrada = neural[k].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 4;
            degrauUnitario();
            contador++;
        }
    }
    for (i = 0; i < config[4]; i++) {
        int temp = contador;
        for (k = 0; k < config[3]; k++) {
            neural[contador].numero = contador;

            *neural[temp].entrada = neural[k].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 5;
            degrauUnitario();
            contador++;
        }
    }
    for (i = 0; i < config[5]; i++) {
        int temp = contador;
        for (k = 0; k < config[4]; k++) {
            neural[contador].numero = contador;

            *neural[temp].entrada = neural[k].saida;// nas entradas recebe as saidas da camada 1
            neural->camada = 6;
            degrauUnitario();
            contador++;
        }
    }
}


void treinamentoRede() {
    printf("Digite a quantidade de camadas! (maximo 6 camadas)! \n");
    scanf_s("%i", &camada);                                                     // entrada de numero de camadas da rede
    if (camada > 6){
        printf("MAXIMO 6 CAMADAS ! \nDigite novamente !\n");
        scanf_s("%i", &camada);
    }
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
    int e1 = 0;             // diferença entre a saida desejada e a saida obtida
    int o1;                 //saida desejada
    e1 = o1 - neural->saida;
    delta[i] = taxaAprendizagem * *neural->peso * e1;
}

void degrauUnitario() {//função de degrau unitario
    float func01;
    float temp=0;
    int cont=0;
    for ( j = 0; j < 10000; j++){
        if (neural->entrada[j]) {
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
      
    }
    int temp = (config[1] + config[1] + config[2] + config[3] + config[4] + config[5]);
        int i;
        for ( i = 0; i < temp; i++){
            printf ("%s ",neural[i].numero);
            printf("%s ", neural[i].entrada);
            printf("%s ", neural[i].saida);
            printf("%s ", neural[i].peso);

        }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf_s("Escolha uma opção\n");
    printf_s("1 : treinamento\n");
    printf_s("2 : usar rede\n");
    printf_s("3 : teste\n");

    int x, z = 0;

    scanf_s("%i", &x);

    switch (x)
    {
    case 1:
        treinamentoRede();
        main();
        break;
    case 2:
        usoRede();
        main();
        break;
    case 3:
        for (i = 0; i < 100; i++)
        {
            printf("%d", entradaOrigem[i]);
        }

        teste();
        system("pause");
        break;
    case 4:
        z = 1;
        system("pause");

    }
}
