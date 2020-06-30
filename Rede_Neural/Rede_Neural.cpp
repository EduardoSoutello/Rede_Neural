#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <locale.h>


int i, j;
int tamanhoEntrada = 100;// substituir na entrada origem o tamanho de entrada
// entradas de alimentação de 0.1 == preto e 0.9 == branco manter apenas os dois.
float entradaOrigem[100] = { 0.0, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9 }; // dados a serem alimentados nos modelos
char nomeTipoTreinamento[40];
int camadaSelecao;
int config[5]; //configuração dos neuronios por camada
float delta[5000];
float taxaAprendizagem;
float teste2;

void degrauUnitario();
void alimentacaoRede();
void teste();

struct criarNeuronio {
    int numero;
    float entrada[500] = { NULL };
    int peso[500];
    int camada;
   // int funcaoAtivacao;
    float saida;

};
struct criarNeuronio neural[49500]; // valor maximo 49.500 posições permitido pelo programa no visual studio


void criarNeuronio() { // separar alientação de rede em uma função separada... 
    int contador = 0;
    int k;

    for (i = 0; i < config[0]; i++) {   // para a primeira camada recebe a entrada e alimentação
        neural[contador].numero = contador;
        neural[contador].camada = 1;
        contador++;
        teste2 = *neural[contador].entrada;// teste
    }
    for (i = 0; i < config[1]; i++) {
        neural[contador].numero = contador; 
        neural[contador].camada = 2;
        contador++;
        teste2 = *neural[contador].entrada;//teste
    }
    for (i = 0; i < config[2]; i++) {
        neural[contador].numero = contador;
        neural[contador].camada = 3;
        contador++;
    }
    for (i = 0; i < config[3]; i++) {
        neural[contador].numero = contador;
        neural[contador].camada = 4;
        contador++;
        teste2 = *neural[contador].entrada;//teste
    }
    for (i = 0; i < config[4]; i++) {
        neural[contador].numero = contador;
        neural->camada = 5;
        contador++;
        teste2 = *neural[contador].entrada;//teste
    }
    
}

void inserirPesos() {
    /* inicializar o gerador de números aleatórios */
    int i, k =0;
    srand( time( NULL ) );
    for ( i = 0; i < (config[0] + config[1] + config[2] + config[3] + config[4] + config[5]); i++ ){
        if ( neural[i].camada == 1 ) {
            for ( j = 0; j < tamanhoEntrada; j++ ) {// trata a primeira camada
                neural[i].peso[j] = rand() % 10; // valor de maximo dos numeros aleatorios.
            }
        }
        else{
            for ( j = 0; j < config[k]; j++ ) { // trata da segunda camada pra cima 
                neural[i].peso[j] = rand() % 10;
            }
            k++;
        }
    }
}

void treinamentoRede() {

    printf("Digite a quantidade de camadas! (maximo 6 camadas)! \n");
    scanf_s("%i", &camadaSelecao);                                                     // entrada de numero de camadas da rede
    if (camadaSelecao > 5){
        printf("MAXIMO 5 CAMADAS ! \nDigite novamente !\n");
        scanf_s("%i", &camadaSelecao);
    }
    printf("A rede neural sera com %i camada(s)!\n", camadaSelecao);
    printf("A rede pode possuir ate 49.500 neurônios\n");
    int temp = 49500;
    for ( i = 0; i < camadaSelecao; i++)  {
        printf("Digite a quantidade de neuronios na camada %i!\n",i+1);
        printf("Você tem mais um total de %i neuronios !\n", temp);
        int x;
        scanf_s("%i", &x);                                                     //entrada do numero de nerônios por camada
        config[i] = x;
        temp = temp - x;
    }
    printf("Digite a taxa de aprendizagem! \n");
    scanf_s("%f", &taxaAprendizagem);

    criarNeuronio();
    inserirPesos();
    alimentacaoRede();
    
}

void alimentacaoRede() {
    for ( i = 0; i < (config[0] + config[1] + config[2] + config[3] + config[4] + config[5]); i++ ) {
        int k;
        int cont = 0;
        for ( j = 0; j < config[0]; j++ ) {
             for ( k = 0; k < tamanhoEntrada; k++ ) { //variavel global da quantidade de entradas pro neuronio
                neural[cont].entrada[k] = entradaOrigem[k];
                cont++;
            }
            degrauUnitario();
        }
        for ( j = 0; j < config[1]; j++ ) {
            for ( k = 0; k < config[0]; k++ ) {// repete a mesma quantidade de neuronios da primeira camada para que casa saida seja uma posição no vetor de entrada
                neural[cont].entrada[k] = neural[k].saida;// nas entradas da segunda camada recebe as saidas da camada 1
                cont++;
            }
            degrauUnitario();
        }
        for ( j = 0; j < config[2]; j++ ) {
            for ( k = 0; k < config[1]; k++ ) {// repete a mesma quantidade de neuronios da segunda camada para que casa saida seja uma posição no vetor de entrada
                *neural[cont].entrada = neural[cont - config[1]].saida;// nas entradas recebe as saidas da camada 1   
                cont++;
            }
            degrauUnitario();
        }
        for ( j = 0; j < config[3]; j++ ) {
            for ( k = 0; k < config[2]; k++ ) {// repete a mesma quantidade de neuronios da terceira camada para que casa saida seja uma posição no vetor de entrada
                *neural[cont].entrada = neural[cont - config[2]].saida;// nas entradas recebe as saidas da camada 1
                cont++;
            }
            degrauUnitario();
        }
        for ( j = 0; j < config[4]; j++ ) {
            for ( k = 0; k < config[3]; k++ ) {// repete a mesma quantidade de neuronios da quarta camada para que casa saida seja uma posição no vetor de entrada
                *neural[cont].entrada = neural[cont - config[3]].saida;// nas entradas recebe as saidas da camada 1
                cont++;
            }
            degrauUnitario();
        }
       
    }
}

void regraDelta() {
    int e1 = 0;             // diferença entre a saida desejada e a saida obtida
    int o1 = 0;                 //saida desejada
    e1 = o1 - neural->saida;
    delta[i] = taxaAprendizagem * *neural->peso * e1;
}

void degrauUnitario() {//função de degrau unitario
    float func01 = 0;
    float temp; // mudar função de ativação no intervalo de 0 e 1..
    int cont;
    int l;
    for (l = 0; l < config[0] + config[1] + config[2] + config[3] + config[4] + config[5]; l++) {
        if (neural[l].camada == 1) {
            temp = 0;
            cont = 0;
            for (j = 0; j < tamanhoEntrada; j++) {//destingue a entrada externa para o calculo
                temp = temp + (neural[l].entrada[j] * neural[l].peso[j]);
                cont++;
            }
            func01 = (temp / cont);
            if (func01 < 0.5) {
                func01 = 0.1;
            }
            else {
                func01 = 0.9;
            }
            neural[l].saida = func01;// ver pq não esta indo valor para saida
        }
        else
        {
            temp = 0;
            cont = 0;
            for (j = 0; j < sizeof config[-2 + neural[l].camada]; j++) {// contabiliza as saidas da primeira camada o calculo
                temp = temp + (neural[l].entrada[j] * neural[l].peso[j]);
                cont++;
            }
            func01 = (temp / cont);
            if (func01 < 0.5) {
                func01 = 0.1;
            }
            else {
                func01 = 0.9;
            }
            neural[l].saida = func01;
        }
    }
}


void usoRede() {
    criarNeuronio();
    printf_s("Ainda não fiz!");
}
void teste() {
    
    int temp = (config[1] + config[1] + config[2] + config[3] + config[4] + config[5]);
        int i;
        int b[4];
        for ( i = 0; i < temp; i++){
            b[0] = neural[i].numero;
            printf("%s ",b[1]);
            b[2] = neural[i].saida;
            printf( "%s ", b[1] );
        }
        system( "pause" );
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
        teste();
        system("pause");
        break;
    case 4:
        z = 1;
        system("pause");

    }
}

