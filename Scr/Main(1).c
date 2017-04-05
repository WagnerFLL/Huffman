#include <stdio.h>

int main(){

    int option;

    while(1){
        printf("--------------------------\n");
        printf("  Escolha uma das opcoes: \n");
        printf("  Tecle 1 para comprimir. \n");
        printf("  Tecle 2 para descomprimir.\n");
        printf("--------------------------\n");
        printf("> ");
        scanf("%d",&option);

        if(option == 1){
            //compress();
            break;
        }
        else if(option == 1){
            //descompress();
            break;
        }
        else{
            printf("Opcao inválida! Tente Novamente.\n");
        }
        system("cls");
    }

}
