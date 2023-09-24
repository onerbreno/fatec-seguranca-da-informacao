#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int modulo = 26; // O alfabeto tem 26 letras

// Função para calcular o determinante de uma matriz N x N
int calculaDeterminante(int **chave, int tamanho) 
{
    // a implementar (recursividade)
}

// Função para calcular o inverso multiplicativo modular de um número
int inversoMultiplicativo(int num, int modulo) 
{
    num = num % modulo;
    for (int x = 1; x < modulo; x++) 
	{
        if ((num * x) % modulo == 1) 
		{
            return x;
        }
    }
    return -1; // Inverso não encontrado
}

// Função para criptografar uma mensagem usando a cifra de Hill
void criptoMsg(char *msg, int **chave, int tamanho) 
{
    int tam = strlen(msg);
    int tamBloco = tamanho;
    int bloco[tamanho];
    int cripto[tam];

    for (int i = 0; i < tam; i += tamBloco) 
	{
		printf ("\n"); //t
        for (int j = 0; j < tamBloco; j++) 
		{
            bloco[j] = (i + j < tam) ? msg[i + j] - 'a' : 0;
            printf("%d\t",bloco[j]); //t
        }
        int criptoBloco[tamanho];
        memset(criptoBloco, 0, sizeof(criptoBloco));
        printf ("\n"); //t
        for (int j = 0; j < tamanho; j++) 
		{
            for (int k = 0; k < tamanho; k++) 
			{
                criptoBloco[j] += chave[k][j] * bloco[k];
                criptoBloco[j] %= modulo;
            }
            printf("%d\t",criptoBloco[j]); //t
        }
        printf("\n"); //t
        for (int j = 0; j < tamBloco; j++) 
		{
            cripto[i + j] = criptoBloco[j];
        }
    }
    printf("\n\nMensagem criptografada: ");
    for (int i = 0; i < tam; i++) 
	{
        printf("%c", cripto[i] + 'a');
    }
    printf("\n");
}
main() 
{
    int tamanho;
    do
	{
		printf("\nDigite o tamanho da matriz-chave (N x N, N>=2): ");
    	scanf("%d", &tamanho);
	}while(tamanho<2);
    int **chave = (int**)malloc(tamanho * sizeof(int*));
    for (int i = 0; i < tamanho; i++) 
	{
        chave[i] = (int*)malloc(tamanho * sizeof(int));
        printf("\nDigite os %d elementos da linha %d: ", tamanho, i + 1);
        for (int j = 0; j < tamanho; j++) 
		{
            scanf("%d", &chave[i][j]);
        }
    }
    char msg[100];
    do
    {
		printf("\nDigite a mensagem a ser criptografada: ");
    	scanf("%s",msg);
    	if (strlen(msg)%tamanho!=0) printf("\nComplete para ser multiplo de %d...\n",tamanho);
	}while(strlen(msg)%tamanho!=0);	
    // Verificação de inverso multiplicativo: a implementar (determinante)
    /*
    int determinante = calculaDeterminante(chave, tamanho);
    int inversoDet = inversoMultiplicativo(determinante, modulo);
    if (inversoDet == -1) 
	{
        printf("A matriz-chave não tem inverso multiplicativo com o módulo fornecido.\n");
        return 1;
    }
    */
    criptoMsg(msg, chave, tamanho);
    for (int i=0; i<tamanho; i++) 
	{
        free(chave[i]);
    }
    free(chave);
}

