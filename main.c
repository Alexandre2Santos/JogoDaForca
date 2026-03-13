#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


FILE* abrir(char nome[], char modo[]);
     FILE* fecharArg(FILE *arg);
     void adicionarDicas();


int main() {
    FILE *temp;
    temp=abrir("temp.txt","r");//temp.txt deve existir para o programa funcionar
    temp=fecharArg(temp);
    return 0;
}
void adicionarDicas() {
    char dica[201];
    char resposta;
    bool validacao=false;
    do{  
            system("cls");
            printf("Digite uma dica de até 200 caracteres: \n");
            scanf("%200[^\n]", dica);
            printf("Deseja salvar a dica? (s/n): ");
            scanf(" %c", &resposta);
    }while(resposta!='s' && resposta!='n');

    FILE *arg;
    arg=abrir("dicas.txt","a");
    if(arg!=NULL) {
        fprintf(arg, "%s\n", dica);
        fecharArg(arg);
    }
    
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