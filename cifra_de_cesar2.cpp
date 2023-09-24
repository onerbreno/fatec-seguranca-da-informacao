#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ql 94

// Fun��o para criptografar a mensagem usando a cifra de C�sar
void cripto(char msg[], int chave) 
{
    for (int i = 0; i < strlen(msg)-1; i++) 
	{
            msg[i] = '!' + (msg[i] - '!' + chave) % ql;
    }
}

// Fun��o para descriptografar a mensagem usando a cifra de C�sar
void descripto(char msg[], int chave) 
{
    cripto(msg, ql - chave); 
	// A decifra��o � simplesmente a cifra com a chave complementar
}

main() 
{
    char msg[1000];
    int op, chave;

    printf("\nDigite a mensagem: ");
    fgets(msg,sizeof(msg),stdin);

    printf("\n\n1. Criptografar");
    printf("\n2. Descriptografar\n-> ");
    scanf("%d",&op);

    printf("\nDigite a chave: ");
    scanf("%d",&chave);

    switch(op) 
	{
        case 1:
            cripto(msg,chave);
            printf("\nMensagem criptografada: %s\n", msg);
            break;
        case 2:
            descripto(msg,chave);
            printf("\nMensagem descriptografada: %s\n", msg);
            break;
        default:
            printf("\nOp��o inv�lida!\n");
    }
}

