/*
 ============================================================================
 Name        : Teste.c
 Author      : Wagner
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main(){

	char nome[100];
	unsigned char capture;
	printf("Digite o nome do arquivo: ");
	scanf("%s",nome);

	int ascii[256] = {0};
    int i;

	FILE *arqv = fopen(nome,"rb"), *f_new = fopen("gerado","wb");

	while((fscanf(arqv,"%c",&capture)) != EOF){
		++ascii[capture];
		fprintf(f_new,"%c",capture);
	}

	for(i = 0 ; i<256 ; i++)
		printf("%d = %d\n",i,ascii[i]);

}

