#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <locale.h>



int i, j;
int entradaOrigem[100] = { 0, 1, 1, 1, 1, 0, 0, 0 ,0}; // dados a serem alimentados nos modelos
int camada;
int config[6]; //configura��o dos neuronios por camada

struct criarNeuronio {
    int numero;
    char entrada[10000];
    char peso[10000];
    int camada;
    int funcaoAtivacao;
    float saida;

};
struct criarNeuronio neural[10000];


void criarNeuronio() { 
    int contador = 0;
    for (i = 0; i < config[0]; i++) {   // para a primeira camada recebe a entrada e alimenta��o
        neural->numero = contador;
        *neural[contador].entrada = entradaOrigem[i];
        neural->camada = 1;
        degrauUnitario();
        contador++;
    }
    for (i = 0; i < config[1]; i++) {
        neural->numero = contador;
        int temp = 0;
        for (i = 0; i < config[0]; i++) {
            *neural[contador].entrada = neural[i].saida;// nas entradas recebe as saidas da camada 1
        }
        neural->camada = 2;
        degrauUnitario();
        contador++;
    }
    for (i = 0; i < config[2]; i++) {
        neural->numero = contador;
        int temp = 0;
        for (i = 0; i < config[1]; i++) {
            *neural[contador].entrada = neural[i + config[0]].saida;// nas entradas recebe as saidas da camada 2
        }
        neural->camada = 3;
        degrauUnitario();
        contador++;
    }
    for (i = 0; i < config[3]; i++) {
        neural->numero = contador;
        int temp = 0;
        for (i = 0; i < config[2]; i++) {
            *neural[contador].entrada = neural[i + config[1]].saida;// nas entradas recebe as saidas da camada 3
        }
        neural->camada = 4;
        degrauUnitario();
        contador++;
    }
    for (i = 0; i < config[4]; i++) {
        neural->numero = contador;
        int temp = 0;
        for (i = 0; i < config[2]; i++) {
            *neural[contador].entrada = neural[i + config[2]].saida;// nas entradas recebe as saidas da camada 4
        }
        neural->camada = 5;
        degrauUnitario();
        contador++;
    }
    for (i = 0; i < config[5]; i++) {
        neural->numero = contador;
        int temp = 0;
        for (i = 0; i < config[2]; i++) {
            *neural[contador].entrada = neural[i + config[3]].saida;// nas entradas recebe as saidas da camada 5
        }
        neural->camada = 6;
        degrauUnitario();
        contador++;
    }

}


void treinamentoRede() {
    printf("Digite a quantidade de camadas! \n");
    scanf_s("%i", &camada);                                                     // entrada de numero de camadas da rede
    printf("A rede neural sera com %i camada(s)!\n", camada);
    for ( i = 0; i < camada; i++)  {
        printf("Digite a quantidade de neuronios na camada %i!\n",i+1);
        int x;
        scanf_s("%i", &x);                                                     //entrada do numero de ner�nios por camada
        config[i] = x;
    }
    criarNeuronio();

}

void degrauUnitario() {//fun��o de degrau unitario
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
    printf_s("Ainda n�o fiz!");
}
void teste() {
    for ( i = 0; i < 100; i++)
    {
        printf_s("%d",i);
        printf_s(" teste %s \n", neural->numero);
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    printf_s("Escolha uma op��o\n");
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