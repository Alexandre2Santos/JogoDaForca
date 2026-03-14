#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *abrir(char nome[], char modo[]);
FILE *fecharArg(FILE *arg);
void adicionarDicas(void);
void mostrarDicas(void);
void removerDica(void);

int main(void)
{
    FILE *temp;
    temp = abrir("temp.txt", "r"); // temp.txt deve existir para o programa funcionar
    temp = fecharArg(temp);

    while (true)
    {
        int opcao;

        printf("\n=== Jogo da Forca - Dicas ===\n");
        printf("1) Adicionar dica\n");
        printf("2) Listar dicas\n");
        printf("3) Remover dica\n");
        printf("0) Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        if (opcao == 0)
        {
            break;
        }
        if (opcao == 1)
        {
            adicionarDicas();
            continue;
        }
        if (opcao == 2)
        {
            mostrarDicas();
            continue;
        }
        if (opcao == 3)
        {
            removerDica();
            continue;
        }

        printf("Opcao invalida. Tente novamente.\n");
    }

    return 0;
}

void adicionarDicas(void)
{
    char dica[201];
    char temp[201];
    char resposta;
    bool validacao = false;

    do
    {
        system("cls");
        printf("Digite uma dica de até 200 caracteres: \n");

        if (fgets(dica, sizeof(dica), stdin) == NULL)
        {
            continue;
        }
        dica[strcspn(dica, "\r\n")] = '\0';

        if (dica[0] == '\0')
        {
            printf("Dica vazia. Digite algo antes de continuar.\n");
            continue;
        }

        printf("Deseja salvar a dica? (s/n): ");
        if (fgets(&resposta, 2, stdin) == NULL)
        {
            resposta = '\0';
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

    } while (resposta != 's' && resposta != 'n');

    if (resposta != 's')
    {
        printf("Dica descartada.\n");
        return;
    }

    FILE *arg = abrir("dicas.txt", "a+"); // abre para leitura/escrita e cria se não existir
    if (arg == NULL)
    {
        return;
    }

    rewind(arg);
    while (fgets(temp, sizeof(temp), arg))
    {
        temp[strcspn(temp, "\r\n")] = '\0';
        if (strcmp(dica, temp) == 0)
        {
            printf("A dica já existe no arquivo. Não será adicionada.\n");
            validacao = true;
            break;
        }
    }

    if (!validacao)
    {
        fprintf(arg, "%s\n", dica);
        printf("Dica adicionada com sucesso!\n");
    }

    fecharArg(arg);
}

void mostrarDicas(void)
{
    FILE *arg = abrir("dicas.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linha[201];
    int contador = 0;
    while (fgets(linha, sizeof(linha), arg))
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        contador++;
        printf("%2d) %s\n", contador, linha);
    }

    if (contador == 0)
    {
        printf("Nenhuma dica cadastrada.\n");
    }

    fecharArg(arg);
}

void removerDica(void)
{
    FILE *arg = abrir("dicas.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linhas[200][201];
    int total = 0;

    while (total < 200 && fgets(linhas[total], sizeof(linhas[total]), arg))
    {
        linhas[total][strcspn(linhas[total], "\r\n")] = '\0';
        total++;
    }

    fecharArg(arg);

    if (total == 0)
    {
        printf("Nenhuma dica para remover.\n");
        return;
    }

    printf("\nDicas disponiveis:\n");
    for (int i = 0; i < total; i++)
    {
        printf("%2d) %s\n", i + 1, linhas[i]);
    }

    printf("Escolha o numero da dica para remover (0 para cancelar): ");
    int escolha;
    if (scanf("%d", &escolha) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Entrada invalida. Nao foi removido.\n");
        return;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    if (escolha <= 0 || escolha > total)
    {
        printf("Operacao cancelada.\n");
        return;
    }

    int remover = escolha - 1;

    printf("Tem certeza que deseja remover \"%s\"? (s/n): ", linhas[remover]);
    char confirmacao = '\0';
    if (fgets(&confirmacao, 2, stdin) == NULL)
    {
        confirmacao = '\0';
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    if (confirmacao != 's')
    {
        printf("Operacao cancelada.\n");
        return;
    }

    arg = abrir("dicas.txt", "w");
    if (arg == NULL)
    {
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (i == remover)
        {
            continue;
        }
        fprintf(arg, "%s\n", linhas[i]);
    }

    fecharArg(arg);
    printf("Dica removida com sucesso.\n");
}

FILE *abrir(char nome[], char modo[])
{
    FILE *arg = fopen(nome, modo);
    if (arg == NULL)
    {
        printf("Não foi possivel abrir o arquivo %s\n", nome);
    }
    return arg;
}

FILE *fecharArg(FILE *arg)
{
    if (arg == NULL)
    {
        printf("\nErro ao fechar o arquivo\n");
        return NULL;
    }
    fclose(arg);
    return NULL;
}
