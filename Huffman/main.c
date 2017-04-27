#include "compress.h"
#include "decompress"

int main(){

    int option;

    while(1){

        printf("  Escolha uma das opcoes: \n");
        printf("  Tecle 1 para comprimir. \n");
        printf("  Tecle 2 para descomprimir.\n  ");

        scanf("%d",&option);
        getchar();

        if(option == 1){
            compress();
            system("pause");
            break;
        }
        else if(option == 2){
            decompress();
            system("pause");
            break;
        }
        else{
            printf("Opcao invalida! Tente Novamente.\n");
        }
        system("cls");
    }

    getchar();
}
