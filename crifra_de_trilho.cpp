#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void preencheMatriz(char mensagem[], int numeroLinhas, int tamanhoChave, int tamanhoMensagem, char **matrizMensagem)
{

    int posicaoMensagem = 0;

    // Preenche matriz com mensagem
    for (int i = 0; i < numeroLinhas; i++)
    {
        for (int j = 0; j < tamanhoChave; j++)
        {
            
            if (posicaoMensagem <= (tamanhoMensagem -1))
            {
                matrizMensagem[i][j] = mensagem[posicaoMensagem];
                posicaoMensagem++;
            }
            else
            {
                matrizMensagem[i][j] = '0';
            }
        }
    }

    // Completa Matriz com alfabeto
    char alfabeto = 'z';
    for (int i = (numeroLinhas - 1); i >= 0 ; i--)
    {
        for (int j = (tamanhoChave - 1); j >= 0; j--)
        {
            // printf("%c", matrizMensagem[i][j]);
            if (matrizMensagem[i][j] == '0' || matrizMensagem[i][j] == '\n')
            {
                matrizMensagem[i][j] = alfabeto;
                alfabeto--;
                
            }
        }
    }
    printf("Matriz de encriptacao: \n");
    for (int i = 0; i < numeroLinhas; i++)
    {
        for (int j = 0; j < tamanhoChave; j++)
        {
            if (matrizMensagem[i][j] != ' ')
            {
                printf("[%c]", matrizMensagem[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    

}

char* criptografaMensagem(int numeroLinhas, int tamanhoChave, char **matrizMensagem, int chave[])
{
    char* mensagemCifrada = (char*)malloc((numeroLinhas * tamanhoChave) * sizeof(char));       

    int posicaoMensagemCifrada = 0;    

    for (int i = 0; i < tamanhoChave; i++)
    {
        int k = 0;
        int posicaoChave = 0;
        //Procura a posição da coluna
        while (chave[k] != i + 1)
        {
            posicaoChave++;
            k++;
            
        }
        //Faz a transposição da coluna
        int coluna = posicaoChave;
        for (int j = 0; j < numeroLinhas; j++)
        {
            mensagemCifrada[posicaoMensagemCifrada] = matrizMensagem[j][coluna];
            posicaoMensagemCifrada++;
        }

    }
    mensagemCifrada[posicaoMensagemCifrada] = '\0';

    printf("Mensagem Codificada: %s\n", mensagemCifrada);
    printf("\n");
    return mensagemCifrada;  
}

char* descriptografaMensagem(int numeroLinhas, int tamanhoChave, char **matrizMensagem, int chave[], char* mensagemCifrada)
{
    
    char* mensagemDescriptografada = (char*)malloc((numeroLinhas * tamanhoChave) * sizeof(char));

    int posicaoMensagem = 0;  

    for (int i = 0; i < tamanhoChave; i++)
    {
        int k = 0;
        int posicaoChave = 0;
        //Procura a posição da coluna
        while (chave[k] != i + 1)
        {
            posicaoChave++;
            k++;
            
        }        
        int coluna = posicaoChave;
        //Escreve a mesagem na coluna encontrada de acordo com a chave 
        for (int j = 0; j < numeroLinhas; j++)
        {
            matrizMensagem[j][coluna] = mensagemCifrada[posicaoMensagem];
            posicaoMensagem++;
        }

    }

    posicaoMensagem = 0;
    //Lê a matriz linha por linha e guarda a mensagem em um array
    for (int i = 0; i < numeroLinhas; i++)
    {
        for (int j = 0; j < tamanhoChave; j++)
        {
                   
            mensagemDescriptografada[posicaoMensagem] = matrizMensagem[i][j];
            posicaoMensagem++;
     
        }
    }
    mensagemDescriptografada[posicaoMensagem] = '\0';
    
    return mensagemDescriptografada;

    // free(mensagemDecifrada);
    
}

main()
{
    int chave[] = {4, 3, 1, 2, 5, 6, 7}, tamanhoChave = sizeof(chave) / sizeof(chave[0]);
    char mensagem[100];

    printf("Digite a mensagem a ser codificada: ");
    fgets(mensagem, sizeof(mensagem), stdin);

    printf("Chave: ");
    for (int i = 0; i < tamanhoChave; i++) {
        printf("%d, ", chave[i]);
    }
    printf("\n");

    //Calcula o tamanho da mensagem digitada e o numeros de linha que tera a matriz
    double tamanhoMensagem = strlen(mensagem);
    int numeroLinhas = ceil(tamanhoMensagem / tamanhoChave);
    
    char **matrizMensagem = (char **)malloc(numeroLinhas * sizeof(char *));
    for (int i = 0; i < numeroLinhas; i++)
    {
        matrizMensagem[i] = (char *)malloc(tamanhoChave * sizeof(char *));
    }

    //Preenche Matriz com a mensagem 
    preencheMatriz(mensagem, numeroLinhas, tamanhoChave, tamanhoMensagem, matrizMensagem);

    //Recebe o retorno da função(A mensagem criptografada)
    char* mensagemCifrada = criptografaMensagem(numeroLinhas, tamanhoChave, matrizMensagem, chave);    
    int tamanhoMensagemCifrada = strlen(mensagemCifrada);

    //Preenche Matriz novamente com a mensagem cifrada
    preencheMatriz(mensagemCifrada, numeroLinhas, tamanhoChave, tamanhoMensagemCifrada, matrizMensagem);

    //Recebe retorno com a mensagem cifrada (encriptação com 2 estágios)
    mensagemCifrada = criptografaMensagem(numeroLinhas, tamanhoChave, matrizMensagem, chave);
    
    //Descriptografa a mensagem no primero estágio
    char* mensagemDecifrada = descriptografaMensagem(numeroLinhas, tamanhoChave, matrizMensagem, chave, mensagemCifrada);

    //Descriptografa a mensagem no segundo estágio
    mensagemDecifrada = descriptografaMensagem(numeroLinhas, tamanhoChave, matrizMensagem, chave, mensagemDecifrada);
        

    printf("Mensagem Decodificada: %s\n", mensagemDecifrada);

    for (int i = 0; i < numeroLinhas; i++)
    {
        free(matrizMensagem[i]);
    }
    free(matrizMensagem);

    
}
