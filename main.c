#include <stdio.h>
#include <stdlib.h>

FILE* abrir(char nome[], char modo[]);
     FILE* fecharArg(FILE *arg);


int main() {
    FILE *temp;
    temp=abrir("temp.txt","r");//temp.txt deve existir para o programa funcionar
    temp=fecharArg(temp);
    return 0;
}
FILE* abrir(char nome[], char modo[]) {
    FILE *arg;
    arg=fopen(nome,modo);
    if(arg==NULL) {

        printf("Não foi possivel abrir o arquivo %s\n", nome);


    }
    return arg;

}
FILE* fecharArg(FILE *arg){

    if(arg==NULL) {
        printf("\n Erro ao fechar o arquivo\n");

    }
    fclose(arg);
    return arg;
}