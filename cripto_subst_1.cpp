#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ql 26

void cripto(char msg[], int chave) 
{
    for (int i = 0; i < strlen(msg); i++) 
	{
        if (msg[i] >= 'a' && msg[i] <= 'z') 
		{
            msg[i] = 'a' + (msg[i] - 'a' + chave) % ql;
        } 
		else if (msg[i] >= 'A' && msg[i] <= 'Z') 
		{
            msg[i] = 'A' + (msg[i] - 'A' + chave) % ql;
        }
    }
}

void descripto(char msg[], int chave) 
{
    cripto(msg, ql - chave); 
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
            printf("\nOpção inválida!\n");
    }
}

