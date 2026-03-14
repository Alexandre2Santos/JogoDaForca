// Gerencia dicas e palavras para o jogo da forca.
// Permite adicionar, listar e remover dicas armazenadas em "dicas.txt".
// Permite adicionar, listar e remover palavras armazenadas em "palavras.txt".

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Funções de manipulação de arquivo
FILE *abrir(char nome[], char modo[]);
FILE *fecharArg(FILE *arg);

// Funções de interação com o usuário para dicas
void adicionarDicas(void);
void mostrarDicas(void);
void removerDica(void);

// Funções de interação com o usuário para palavras
void adicionarPalavras(void);
void mostrarPalavras(void);
void removerPalavra(void);

int main(void)
{
    FILE *temp;
    temp = abrir("temp.txt", "r"); // temp.txt deve existir para o programa funcionar
    temp = fecharArg(temp);

    // Loop principal: exibe menu e processa opcao do usuario
    while (true)
    {
        int opcao;
        int c; // Declaracao unica para limpar buffer

        printf("\n=== Jogo da Forca ===\n");
        printf("1) Adicionar dica\n");
        printf("2) Listar dicas\n");
        printf("3) Remover dica\n");
        printf("4) Adicionar palavra\n");
        printf("5) Listar palavras\n");
        printf("6) Remover palavra\n");
        printf("0) Sair\n");
        printf("Escolha: ");

        // Le a opcao do usuario
        if (scanf("%d", &opcao) != 1)
        {
            // Limpa o restante da linha se a entrada for invalida
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        // Descarta qualquer caractere extra na linha, evitando loop infinito
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
        if (opcao == 4)
        {
            adicionarPalavras();
            continue;
        }
        if (opcao == 5)
        {
            mostrarPalavras();
            continue;
        }
        if (opcao == 6)
        {
            removerPalavra();
            continue;
        }
    }

    return 0;
}

void adicionarDicas(void)
{
    char dica[201];
    char temp[201];
    char resposta;
    bool validacao = false;

    // Pega a dica do usuario (max 200 caracteres)
    do
    {
        system("cls");
        printf("Digite uma dica de até 200 caracteres: \n");

        if (fgets(dica, sizeof(dica), stdin) == NULL)
        {
            continue;
        }
        // Remove newline final se houver
        dica[strcspn(dica, "\r\n")] = '\0';

        if (dica[0] == '\0')
        {
            printf("Dica vazia. Digite algo antes de continuar.\n");
            continue;
        }

        // Confirmacao do usuario antes de gravar
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

    // Abre o arquivo (cria se nao existir) e verifica se a dica ja existe
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
    int c; // Declaracao unica para limpar buffer

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
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Entrada invalida. Nao foi removido.\n");
        return;
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    if (escolha <= 0 || escolha > total)
    {
        printf("Operacao cancelada.\n");
        return;
    }

    int remover = escolha - 1;

    // Confirmacao final antes de remover
    printf("Tem certeza que deseja remover \"%s\"? (s/n): ", linhas[remover]);
    char confirmacao = '\0';
    if (fgets(&confirmacao, 2, stdin) == NULL)
    {
        confirmacao = '\0';
    }
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

void adicionarPalavras(void)
{
    char palavra[51]; // palavras até 50 caracteres
    char temp[51];
    char resposta;
    bool validacao = false;

    // Pega a palavra do usuario (max 50 caracteres)
    do
    {
        system("cls");
        printf("Digite uma palavra de até 50 caracteres: \n");

        if (fgets(palavra, sizeof(palavra), stdin) == NULL)
        {
            continue;
        }
        // Remove newline final se houver
        palavra[strcspn(palavra, "\r\n")] = '\0';

        if (palavra[0] == '\0')
        {
            printf("Palavra vazia. Digite algo antes de continuar.\n");
            continue;
        }

        // Confirmacao do usuario antes de gravar
        printf("Deseja salvar a palavra? (s/n): ");
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
        printf("Palavra descartada.\n");
        return;
    }

    // Abre o arquivo (cria se nao existir) e verifica se a palavra ja existe
    FILE *arg = abrir("palavras.txt", "a+"); // abre para leitura/escrita e cria se não existir
    if (arg == NULL)
    {
        return;
    }

    rewind(arg);
    while (fgets(temp, sizeof(temp), arg))
    {
        temp[strcspn(temp, "\r\n")] = '\0';
        if (strcmp(palavra, temp) == 0)
        {
            printf("A palavra já existe no arquivo. Não será adicionada.\n");
            validacao = true;
            break;
        }
    }

    if (!validacao)
    {
        fprintf(arg, "%s\n", palavra);
        printf("Palavra adicionada com sucesso!\n");
    }

    fecharArg(arg);
}

void mostrarPalavras(void)
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linha[51];
    int contador = 0;
    while (fgets(linha, sizeof(linha), arg))
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        contador++;
        printf("%2d) %s\n", contador, linha);
    }

    if (contador == 0)
    {
        printf("Nenhuma palavra cadastrada.\n");
    }

    fecharArg(arg);
}

void removerPalavra(void)
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linhas[200][51];
    int total = 0;
    int c; // Declaracao unica para limpar buffer

    while (total < 200 && fgets(linhas[total], sizeof(linhas[total]), arg))
    {
        linhas[total][strcspn(linhas[total], "\r\n")] = '\0';
        total++;
    }

    fecharArg(arg);

    if (total == 0)
    {
        printf("Nenhuma palavra para remover.\n");
        return;
    }

    printf("\nPalavras disponiveis:\n");
    for (int i = 0; i < total; i++)
    {
        printf("%2d) %s\n", i + 1, linhas[i]);
    }

    printf("Escolha o numero da palavra para remover (0 para cancelar): ");
    int escolha;
    if (scanf("%d", &escolha) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Entrada invalida. Nao foi removido.\n");
        return;
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    if (escolha <= 0 || escolha > total)
    {
        printf("Operacao cancelada.\n");
        return;
    }

    int remover = escolha - 1;

    // Confirmacao final antes de remover
    printf("Tem certeza que deseja remover \"%s\"? (s/n): ", linhas[remover]);
    char confirmacao = '\0';
    if (fgets(&confirmacao, 2, stdin) == NULL)
    {
        confirmacao = '\0';
    }
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    if (confirmacao != 's')
    {
        printf("Operacao cancelada.\n");
        return;
    }

    arg = abrir("palavras.txt", "w");
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
    printf("Palavra removida com sucesso.\n");
}

// Abre um arquivo com o modo especificado (r, w, a+, etc.)
// Retorna NULL se falhar.
FILE *abrir(char nome[], char modo[])
{
    FILE *arg = fopen(nome, modo);
    if (arg == NULL)
    {
        printf("Não foi possivel abrir o arquivo %s\n", nome);
    }
    return arg;
}

// Fecha o arquivo passado como argumento.
// Retorna NULL para facilitar uso em atribuições (e.g., temp = fecharArg(temp)).
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
