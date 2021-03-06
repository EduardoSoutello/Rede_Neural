#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>


int i, j;
//int tamanhoEntrada = 100;// substituir na entrada origem o tamanho de entrada
// entradas de alimentação de 0.1 == preto e 0.9 == branco manter apenas os dois.
float entradaOrigem[100] = { 0.0, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.1, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9 }; // dados a serem alimentados nos modelos
char nomeTipoTreinamento[40];
int camadaSelecao;
int config[6]; //configuração dos neuronios por camada
float delta[5000];
float taxaAprendizagem;
float teste2;


void criarNeuronio();
void inserirPesos();
void alimentacaoRede();
void degrauUnitario();
void regraDelta();
void teste();
//void abrirArquivo();

struct criarNeuronio {
    int numero;
    float entrada[5000] = { NULL };
    float peso[5000];
    int camada;
    // int funcaoAtivacao;
    float saida;

};
struct criarNeuronio neural[49500]; // valor maximo 49.500 posições permitido pelo programa no visual studio


void criarNeuronio()
{ // separar alientação de rede em uma função separada... 
    int contador = 0;
    int i, j;
    for ( i = 0; i < 6; i++ ) {
        for ( j = 0; j < config[i]; j++ ) {
            neural[contador].numero = contador;
            neural[contador].camada = i + 1;
            contador++;
        }
    }
}

void inserirPesos()
{
    /* inicializar o gerador de números aleatórios */
    int i, l, k = 0;
    int soma;
    srand( time( NULL ) );
    soma = config[0] + config[1] + config[2] + config[3] + config[4] + config[5];
    for ( i = 0; i < soma; i++ ) {
        for ( l = 0; l < config[0]; l++ ) {
            neural[l].peso[j] = rand() % 10; // valor de maximo dos numeros aleatorios.
            neural[l].peso[j] = neural[l].peso[j] / 10;
        }
        if ( neural[i].camada > 1 ) {
            for ( k = 0; k < 6; k++ ) {
                for ( l = 0; l < config[k]; l++ ) {
                    neural[i].peso[l] = rand() % 10; // valor de maximo dos numeros aleatorios.
                    neural[i].peso[l] = neural[i].peso[l] / 10;
                }
            }
        }

    }
}

void treinamentoRede()
{
    printf( "Digite a quantidade de camadas! (maximo 6 camadas)! \n" );
    scanf_s( "%i", &camadaSelecao );                                                     // entrada de numero de camadas da rede
    if ( camadaSelecao > 6 ) {
        printf( "MAXIMO 6 CAMADAS ! \nDigite novamente !\n" );
        scanf_s( "%i", &camadaSelecao );
    }
    system( "cls");
    printf( "A rede neural sera com %i camada(s)! E pode possuir ate 49.500 neurônios !\n\n", camadaSelecao );
    
    int temp = 49500;
    for ( i = 0; i < camadaSelecao; i++ ) {
        printf( "Digite a quantidade de neuronios na camada %i!\n\n", i + 1 );
        if ( i == 0 ) {
            printf( "A Primeira camada deve ter o tamanho da quantidade de alimentação desejada! (exemplo 100)\n" );
        }
        if ( i == camadaSelecao -1 ) {
            printf( "A ultima camada deve ter o tamanho 8 para comparação na tabela ASCII\n" );
        }
        int x;
        scanf_s( "%i", &x );                                                     //entrada do numero de nerônios por camada
        config[i] = x;
        temp = temp - x;
        if ( i < camadaSelecao -1 ) {
            printf( "\nVocê tem mais um total de %i neuronios !\n\n", temp );
        }
    }
    printf( "Digite a taxa de aprendizagem! \n" );
    scanf_s( "%f", &taxaAprendizagem );

    criarNeuronio();
    inserirPesos();
    alimentacaoRede();
    regraDelta();
    
    //salvar pesos após rede corretamente treinada

}

void alimentacaoRede()
{
    int k;
    int cont0 = 0;
    for ( j = 0; j < config[0]; j++ ) {// a primeira camada sempre tem a quantidade definida de acordo com a entrada de aliemntação 
        neural[cont0].entrada[0] = entradaOrigem[j];
        cont0++;
    }
    degrauUnitario();
    for ( j = 0; j < config[1]; j++ ) {
        for ( k = 0; k < config[0]; k++ ) {// repete a mesma quantidade de neuronios da primeira camada para que casa saida seja uma posição no vetor de entrada
            neural[cont0].entrada[k] = neural[k].saida;// nas entradas da segunda camada recebe as saidas da camada 1
        }
        cont0++;
    }
    degrauUnitario();
    for ( j = 0; j < config[2]; j++ ) {
        for ( k = 0; k < config[1]; k++ ) {// repete a mesma quantidade de neuronios da segunda camada para que casa saida seja uma posição no vetor de entrada
            neural[cont0].entrada[k] = neural[cont0 - config[1]].saida;// nas entradas recebe as saidas da camada 1   
        }
        cont0++;
    }
    degrauUnitario();
    for ( j = 0; j < config[3]; j++ ) {
        for ( k = 0; k < config[2]; k++ ) {// repete a mesma quantidade de neuronios da terceira camada para que casa saida seja uma posição no vetor de entrada
            neural[cont0].entrada[k] = neural[cont0 - config[2]].saida;// nas entradas recebe as saidas da camada 1
        }
        cont0++;
    }
    degrauUnitario();
    for ( j = 0; j < config[4]; j++ ) {
        for ( k = 0; k < config[3]; k++ ) {// repete a mesma quantidade de neuronios da quarta camada para que casa saida seja uma posição no vetor de entrada
            neural[cont0].entrada[k] = neural[cont0 - config[3]].saida;// nas entradas recebe as saidas da camada 1  
        }
        cont0++;
    }
    degrauUnitario();
}

void regraDelta()
{
    int i, l, k;
    int e1 = 0;             // diferença entre a saida desejada e a saida obtida
    int o1 = 0;                 //saida desejada
    int temp;
    int temp2;
    e1 = 1; //o1 - neural->saida;

    for ( k = camadaSelecao; k > 0 ; k-- ){ // algoritmo de backpropagation
        temp2 = k;
        temp = 0;
        for ( i = 0; i < temp2 - 1; i++ ) {
            temp = temp + config[i];
        }
        for ( i = 0; i < config[temp2 - 1]; i++ ) {
            for ( l = 0; l < config[temp2 - 2]; l++ ) {
                delta[l] = taxaAprendizagem * neural[temp + i].entrada[l] * e1; 
                neural[temp + i].peso[l] = neural[temp + i].peso[l] - delta[l]; //peso recebe peso - dif delta
            }
        }
    }
    
    // verificar media e correção da ccamada oculta
}

void degrauUnitario()
{//função de degrau unitario
    float func01 = 0;
    float temp; // mudar função de ativação no intervalo de 0 e 1..
    int cont;
    int l;
    for ( l = 0; l < config[0] + config[1] + config[2] + config[3] + config[4] + config[5]; l++ ) {
        if ( neural[l].camada == 1 ) {
            func01 = (neural[l].entrada[0] * neural[l].peso[0]);
            if ( func01 < 0.5 ) {
                func01 = 0.1;
            }
            else {
                func01 = 0.9;
            }
            neural[l].saida = func01;// ver pq não esta indo valor para saida
        }

        for ( i = 0; i < 6; i++ ) {
            if ( neural[l].camada == i + 2 ) {
                temp = 0;
                for ( j = 0; j < config[i]; j++ ) {//destingue a entrada externa para o calculo
                    temp = temp + (neural[l].entrada[j] * neural[l].peso[j]);
                }
                func01 = temp;
                if ( func01 < 0.5 ) {
                    func01 = 0.1;
                }
                else {
                    func01 = 0.9;
                }
                neural[l].saida = func01;// ver pq não esta indo valor para saida
            }
        }
    }
}

/*
void abrirArquivo(){
    FILE* fptr;
    // use appropriate location if you are using MacOS or Linux
    fptr = fopen( "C:\temp\program.txt", "w" );

    if ( fptr == NULL )
    {
        printf( "Error!" );
        exit( 1 );
    }

    // printf( "Enter num: " );

    // scanf( "%d", &num );
    for ( i = 0; i < 6; i++ ) {
        for ( j = 0; j < config[i]; j++ ) {
            if ( neural[j].camada == 1 ) {
                fprintf( fptr, "%2.f ;", neural[j].peso[0] );
            }
            fprintf( fptr, "%d\n" );
            if ( neural[j].camada == i + 1 ) {
                fprintf( fptr, "%2.f ;", neural[j].peso[0] );
            }
            fprintf( fptr, "%d\n" );
        }
    }
    fclose( fptr );

}
  */  

void usoRede(){
    criarNeuronio();
    inserirPesos();
    alimentacaoRede();
    printf_s( "Ainda não fiz!" );
}

void teste(){
    int i;
    float b[2];
    int temp = 0;
    for (  i = 0; i < camadaSelecao - 1; i++ ){
        temp = temp + config[i];
    }
    for ( i = 0; i < config[camadaSelecao - 1]; i++ ) {
        b[0] = neural[temp + i].numero;
        printf( "%d ", b[0] );
        b[1] = neural[temp + i].saida;
        printf( "%.2f \n", b[1] );
    }
    for ( i = 0; i < config[camadaSelecao - 1]; i++ ) {
        printf( "%.2f \n", delta[i] );
    }

    system( "pause" );
}

int main()
{
    setlocale( LC_ALL, "Portuguese" );

    printf_s( " ______________________\n" );
    printf_s( "|  Escolha uma opção   |\n" );
    printf_s( "|______________________|\n" );
    printf_s( "|                      |\n" );
    printf_s( "| 1 : treinamento      |\n" );
    printf_s( "| 2 : usar rede        |\n" );
    printf_s( "| 3 : teste            |\n" );
    printf_s( "|______________________|\n" );

    int x, z = 0;
    scanf_s( "%i", &x );

    switch ( x )
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
        for ( i = 0; i < 100; i++ )
            teste();
        system( "pause" );
        break;
    case 4:
        z = 1;
        system( "pause" );

    }
}

