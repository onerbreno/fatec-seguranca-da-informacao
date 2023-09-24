#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
void converteBinario(int nd, int bin[8]) 
{
    int j = 0; int binario[8];
    while (nd > 0) 
	{
        binario[j] = nd % 2;
        nd = nd / 2;
        j++;
    }
    for (int i=j; i>=0; i--) bin[8-i-1]=binario[i]; 
}
void converteDecimal(int *ci, int *mcd, int tam)
{
	int k=0, n;
	for(int i=0; i<tam; i++)
	{
		mcd[i]=0; n=7;
		for(int j=0;j<8;j++) 
		{
			mcd[i]+=(pow(2,n--)*ci[j+k]);
		}
		k+=8;
	}
}
void Vernam (int *vn, int *vc, int *ci, int tam)
{
	for (int i=0; i<tam*8; i++) ci[i] = vn[i] ^ vc[i];
}
main() 
{
    int nd, bin[8],j=0; char msg[100], chv[100];
    printf("\nDigite uma frase: "); fgets(msg,sizeof(msg),stdin);
    do
    {
		printf("\nDigite uma chave: "); 
		fgets(chv,sizeof(chv),stdin);
	}while(strlen(msg)!=strlen(chv));
    int *vn = (int *) malloc ((strlen(msg)-1)*8 * sizeof(int));
    int *vc = (int *) malloc ((strlen(chv)-1)*8 * sizeof(int));
	int *ci = (int *) malloc ((strlen(msg)-1)*8 * sizeof(int));
    
    for (int i=0;i<strlen(msg)-1; i++)
    {
		nd=msg[i];
	    converteBinario(nd,bin);
	    for (int k=0; k<8; k++) vn[j+k] = bin[k];
	    j+=8;
	}
	printf("\nMensagem: \n");
    for (int i=0; i<(strlen(msg)-1)*8; i++) printf("%d",vn[i]);
    j=0;
    for (int i=0;i<strlen(chv)-1; i++)
    {
		nd=chv[i];
	    converteBinario(nd,bin);
	    for (int k=0; k<8; k++) vc[j+k] = bin[k];
	    j+=8;
	}
	printf("\nChave: \n");
    for (int i=0; i<(strlen(chv)-1)*8; i++) printf("%d",vc[i]);
    Vernam(vn,vc,ci,strlen(chv)-1);
    printf("\nCripto binaria: \n");
    for (int i=0; i<(strlen(msg)-1)*8; i++) printf("%d",ci[i]);
    int *mcd = (int *) malloc ((strlen(msg)-1) * sizeof(int));
    converteDecimal(ci,mcd,strlen(msg)-1);
    printf("\nCripto caracteres: \n");
    for (int i=0; i<(strlen(msg)-1); i++) printf("%d ",mcd[i]);
    printf(" --> ");
    for (int i=0; i<(strlen(msg)-1); i++) printf("%c", 'a'+mcd[i]);
    Vernam(ci,vc,vn,strlen(chv)-1);
    printf("\nDescripto binaria: \n");
    for (int i=0; i<(strlen(msg)-1)*8; i++) printf("%d",vn[i]);
    converteDecimal(vn,mcd,strlen(msg)-1);
    printf("\nDescripto caracteres: \n");
    for (int i=0; i<(strlen(msg)-1); i++) printf("%d ",mcd[i]);
    printf(" --> ");
    for (int i=0; i<(strlen(msg)-1); i++) printf("%c",mcd[i]);
}
