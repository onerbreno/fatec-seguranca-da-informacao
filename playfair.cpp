#include <stdio.h>
#include <string.h>

#define TAMANHO 5

// Função para encontrar as coordenadas de uma letra na matriz
void acharPosicao(char m[TAMANHO][TAMANHO], char ch, int *lin, int *col) 
{
    if (ch == 'J') ch = 'I';
    for (*lin=0; *lin<TAMANHO; (*lin)++) 
	{
        for (*col=0; *col<TAMANHO; (*col)++) 
		{
            if (m[*lin][*col] == ch) return;
        }
    }
}
// Função para criptografar um par de letras
void criptoPar(char m[TAMANHO][TAMANHO], char par[2], char cripto[2]) 
{
    int lin1, col1, lin2, col2;
    acharPosicao(m, par[0], &lin1, &col1);
    acharPosicao(m, par[1], &lin2, &col2);

    if (lin1==lin2) 
	{ // Mesma linha
        cripto[0] = m[lin1][(col1+1) % TAMANHO];
        cripto[1] = m[lin2][(col2+1) % TAMANHO];
    } 
	else if (col1==col2) 
	{ // Mesma coluna
        cripto[0] = m[(lin1 + 1) % TAMANHO][col1];
        cripto[1] = m[(lin2 + 1) % TAMANHO][col2];
    } 
	else 
	{ // Forma retangular
        cripto[0] = m[lin1][col2];
        cripto[1] = m[lin2][col1];
    }
}
// Função para realizar a criptografia da mensagem
void criptoMsg(char m[TAMANHO][TAMANHO], char *msg) 
{
    int tam = strlen(msg);
    for (int i=0; i<tam; i+=2) 
	{
        char par[2];
        par[0] = msg[i];
        if (i+1<tam && par[0] == msg[i+1]) 
		{ // Mesma letra, inserir 'X'
            par[1] = 'X';
            i--; // Processar a mesma letra novamente
        } 
		else 
		{
            par[1] = (i+1<tam) ? msg[i+1] : 'X'; 
			// Última letra, inserir 'X'
        }
        char cripto[2];
        criptoPar(m, par, cripto);
        printf("%c%c", cripto[0], cripto[1]);
    }
    printf("\n");
}
//função para imprimir matriz PlayFair
void imprimeMatriz(char m[TAMANHO][TAMANHO])
{
	int i, j;
	printf("\n");
	for(i=0; i<TAMANHO; i++)
	{
		printf("\n");
		for(j=0; j<TAMANHO; j++) printf("%c\t",m[i][j]);
	}
	printf("\n");
}
main() 
{
    char chave[] = "MONARCHY"; // Chave para construir a matriz Playfair
    char m[TAMANHO][TAMANHO];
    int usado[26] = {0};

    // Construir a matriz de Playfair
    int lin = 0, col = 0; usado[9]=1; // GAMBI DO J
    for (int i=0;chave[i]!='\0';i++) 
	{
        if (chave[i] == 'J') chave[i] = 'I';
        if (!usado[chave[i] - 'A']) 
		{
            m[lin][col] = chave[i];
            usado[chave[i] - 'A'] = 1;
            col = (col + 1) % TAMANHO;
            if (col == 0) lin = (lin + 1) % TAMANHO;
        }
    }
    for (int i=0; i<26; i++) 
	{
        if (!usado[i]) 
		{
            m[lin][col] = i + 'A';
            col = (col + 1) % TAMANHO;
            if (col == 0) lin = (lin + 1) % TAMANHO;
        }
    }
    printf("\nMatriz PlayFair:\n"); imprimeMatriz(m);
    char msg[1000];
    printf("\nDigite a mensagem     : ");
    fgets(msg,sizeof(msg),stdin);
    printf("\nMensagem original     : %s",msg);
    printf("\nMensagem criptografada: ");
    criptoMsg(m,msg);
}

