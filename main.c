// ============================================================================
// JOGO DA FORCA - GERENCIADOR DE DICAS E PALAVRAS
// ============================================================================
// Descrição: Aplicação para gerenciar dicas e palavras de um jogo da forca.
// Funcionalidades:
//   - Adicionar dicas e palavras com validação de duplicatas
//   - Listar todas as dicas e palavras cadastradas
//   - Remover dicas e palavras com confirmação
//   - Vincular dicas às palavras (formato: palavra|dica)
//
// Arquivos de Armazenamento:
//   - dicas.txt: Contém todas as dicas cadastradas (uma por linha)
//   - palavras.txt: Contém palavras com suas dicas (formato: palavra|dica)
//   - temp.txt: Arquivo auxiliar para operações (criado automaticamente)
// ============================================================================

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// ============================================================================
// DECLARAÇÕES DE FUNÇÕES
// ============================================================================

// Funções de manipulação de arquivo
FILE *abrir(char nome[], char modo[]);
FILE *fecharArg(FILE *arg);

// Funções de gerenciamento de dicas
void adicionarDicas(void);
void mostrarDicas(void);
void removerDica(void);
void editarDica(void);

// Funções de gerenciamento de palavras
void adicionarPalavras(void);
void mostrarPalavras(void);
void removerPalavra(void);
void editarPalavra(void);

// Função de sorteio e jogo
void sorteio(void); // Seleciona uma palavra aleatória e exibe para teste (pode ser usado no modo forca)
bool sortearPalavra(char palavra[], char dica[]);
unsigned int contarPalavras(void);
unsigned int palavraSorteada(void);
void jogarForca(void);

// ============================================================================
// FUNÇÃO PRINCIPAL - MENU INTERATIVO
// ============================================================================
int main(void)
{
    // Inicializa o arquivo temporário
    FILE *temp;
    temp = abrir("temp.txt", "r");
    temp = fecharArg(temp);

    // ========================================================================
    // LOOP PRINCIPAL - EXIBE MENU E PROCESSA ESCOLHAS DO USUÁRIO
    // ========================================================================
    while (true)
    {
        int opcao; // Opção escolhida pelo usuário
        int c;     // Variável para limpar buffer de entrada

        // Exibe o menu de opcoes
        printf("\n=== Jogo da Forca ===");
        printf("\n\n--- GERENCIAR DICAS ---");
        printf("\n1) Adicionar dica");
        printf("\n2) Listar dicas");
        printf("\n3) Remover dica");
        printf("\n\n--- GERENCIAR PALAVRAS ---");
        printf("\n4) Adicionar palavra");
        printf("\n5) Listar palavras");
        printf("\n6) Remover palavra");
        printf("\n\n--- JOGO ---");
        printf("\n7) Jogar forca");
        printf("\n\n--- EDITAR ---");
        printf("\n8) Editar dica");
        printf("\n9) Editar palavra");
        printf("\n\n--- SAIR ---");
        printf("\n0) Sair");
        printf("\nEscolha: ");

        // Lê a opção do usuário com validação
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

        // Processa a opção escolhida pelo usuário
        // Cada opção chama a função correspondente
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
        if (opcao == 7)
        {
            jogarForca();
            continue;
        }
        if (opcao == 8)
        {
            editarDica();
            continue;
        }
        if (opcao == 9)
        {
            editarPalavra();
            continue;
        }
    }

    return 0;
}

void adicionarDicas(void)
// ============================================================================
// ADICIONA UMA NOVA DICA AO ARQUIVO
// ============================================================================
// Processo:
//   1. Solicita ao usuário uma dica (máximo 200 caracteres)
//   2. Valida se a dica não está vazia
//   3. Pede confirmação antes de salvar
//   4. Verifica se a dica já existe (evita duplicatas)
//   5. Grava no arquivo dicas.txt se válida
// Variáveis:
//   - dica[201]: buffer para armazenar a dica digida
//   - temp[201]: buffer para leitura de dicas existentes
//   - resposta: caractere para confirmação (s/n)
//   - validacao: flag indicando se a dica já existe
//
{
    char dica[201];         // Dica digitada pelo usuário
    char temp[201];         // Buffer para leitura de verificação
    char resposta;          // Confirmação do usuário (s ou n)
    bool validacao = false; // Flag: true se dica já existe

    // Loop de validação: continua até o usuário digitar s ou n
    do
    {
        system("cls"); // Limpa a tela
        printf("Digite uma dica de ate 200 caracteres: \n");

        // Lê a dica do usuário com fgets (seguro para strings grandes)
        if (fgets(dica, sizeof(dica), stdin) == NULL)
        {
            continue;
        }
        // Remove a quebra de linha final (\n ou \r\n) adicionada por fgets
        dica[strcspn(dica, "\r\n")] = '\0';

        // Validação: rejeita dicas vazias
        if (dica[0] == '\0')
        {
            printf("Dica vazia. Digite algo antes de continuar.\n");
            continue;
        }

        // Pede confirmação ao usuário
        printf("Deseja salvar a dica? (s/n): ");
        if (scanf(" %c", &resposta) != 1)
        {
            resposta = '\0';
        }

        // Limpa o buffer de entrada para evitar problemas em próximas leituras
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

    } while (resposta != 's' && resposta != 'n'); // Repete enquanto não for s ou n

    // Usuário cancelou a operação
    if (resposta != 's')
    {
        printf("Dica descartada.\n");
        return;
    }

    // Abre o arquivo para verificar se a dica já existe e gravá-la
    // Modo a+: abre para leitura/escrita e cria se não existir
    FILE *arg = abrir("dicas.txt", "a+");
    if (arg == NULL)
    {
        return;
    }

    // Retorna ao início do arquivo para verificar duplicatas
    rewind(arg);

    // Verifica se a dica já existe no arquivo
    while (fgets(temp, sizeof(temp), arg))
    {
        temp[strcspn(temp, "\r\n")] = '\0';
        if (strcmp(dica, temp) == 0) // Comparação exata
        {
            printf("A dica ja existe no arquivo. Nao sera adicionada.\n");
            validacao = true; // Marca como duplicata
            break;
        }
    }

    // Grava a dica se não for duplicata
    if (!validacao)
    {
        fprintf(arg, "%s\n", dica);
        printf("Dica adicionada com sucesso!\n");
    }

    fecharArg(arg);
}

void mostrarDicas(void)
// ============================================================================
// EXIBE TODAS AS DICAS CADASTRADAS
// ============================================================================
// Processo:
//   1. Abre o arquivo dicas.txt para leitura
//   2. Lê todas as linhas e exibe numeradas
//   3. Mostra mensagem se não houver dicas
//
{
    FILE *arg = abrir("dicas.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linha[201];  // Buffer para leitura de cada linha
    int contador = 0; // Contador para numeração

    // Lê e exibe cada dica do arquivo
    while (fgets(linha, sizeof(linha), arg))
    {
        linha[strcspn(linha, "\r\n")] = '\0'; // Remove quebra de linha
        contador++;
        printf("%2d) %s\n", contador, linha);
    }

    // Mensagem se nenhuma dica foi encontrada
    if (contador == 0)
    {
        printf("Nenhuma dica cadastrada.\n");
    }

    fecharArg(arg);
}

void removerDica(void)
// ============================================================================
// REMOVE UMA DICA ESPECÍFICA
// ============================================================================
// Processo:
//   1. Carrega todas as dicas em memória
//   2. Exibe a lista numerada
//   3. Pede ao usuário qual dica remover
//   4. Pede confirmação
//   5. Escreve todas as dicas EXCETO a removida no arquivo
//
{
    FILE *arg = abrir("dicas.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linhas[200][201]; // Array para armazenar até 200 dicas
    int total = 0;         // Contador de dicas carregadas
    int c;                 // Variável para limpar buffer

    // Carrega todas as dicas em memória
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

    // Exibe a lista de dicas disponíveis
    printf("\nDicas disponiveis:\n");
    for (int i = 0; i < total; i++)
    {
        printf("%2d) %s\n", i + 1, linhas[i]);
    }

    // Solicita qual dica remover
    printf("Escolha o numero da dica para remover (0 para cancelar): ");
    int escolha;
    if (scanf("%d", &escolha) != 1)
    {
        // Lida com entrada inválida
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Entrada invalida. Nao foi removido.\n");
        return;
    }

    // Limpa o buffer de entrada
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    // Valida a escolha
    if (escolha <= 0 || escolha > total)
    {
        printf("Operacao cancelada.\n");
        return;
    }

    int remover = escolha - 1; // Converte para índice do array (0-based)

    // Pede confirmação final antes de remover
    printf("Tem certeza que deseja remover \"%s\"? (s/n): ", linhas[remover]);
    char confirmacao = '\0';
    if (scanf(" %c", &confirmacao) != 1)
    {
        confirmacao = '\0';
    }

    // Limpa o buffer
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    if (confirmacao != 's')
    {
        printf("Operacao cancelada.\n");
        return;
    }

    // Abre o arquivo para escrita (sobrescreve o conteúdo)
    arg = abrir("dicas.txt", "w");
    if (arg == NULL)
    {
        return;
    }

    // Escreve todas as dicas EXCETO a que será removida
    for (int i = 0; i < total; i++)
    {
        if (i == remover)
        {
            continue; // Pula a dica a ser removida
        }
        fprintf(arg, "%s\n", linhas[i]);
    }

    fecharArg(arg);
    printf("Dica removida com sucesso.\n");
}

void editarDica(void)
{
    FILE *arg = abrir("dicas.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linhas[200][201];
    int total = 0;
    int c;

    while (total < 200 && fgets(linhas[total], sizeof(linhas[total]), arg))
    {
        linhas[total][strcspn(linhas[total], "\r\n")] = '\0';
        total++;
    }

    fecharArg(arg);

    if (total == 0)
    {
        printf("Nenhuma dica para editar.\n");
        return;
    }

    printf("\nDicas disponiveis:\n");
    for (int i = 0; i < total; i++)
    {
        printf("%2d) %s\n", i + 1, linhas[i]);
    }

    printf("Escolha o numero da dica para editar (0 para cancelar): ");
    int escolha;
    if (scanf("%d", &escolha) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Entrada invalida. Nao foi editado.\n");
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

    int editar = escolha - 1;
    char dicaNova[201];

    printf("Dica atual: %s\n", linhas[editar]);
    printf("Digite a nova dica: ");
    if (fgets(dicaNova, sizeof(dicaNova), stdin) == NULL)
    {
        printf("Erro na leitura.\n");
        return;
    }
    dicaNova[strcspn(dicaNova, "\r\n")] = '\0';

    if (dicaNova[0] == '\0')
    {
        printf("Dica vazia. Operacao cancelada.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (i != editar && strcmp(linhas[i], dicaNova) == 0)
        {
            printf("Ja existe uma dica igual. Nao sera editado.\n");
            return;
        }
    }

    printf("Confirmar alteracao (s/n): ");
    char confirmacao = '\0';
    if (scanf(" %c", &confirmacao) != 1)
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

    strcpy(linhas[editar], dicaNova);

    arg = abrir("dicas.txt", "w");
    if (arg == NULL)
    {
        return;
    }

    for (int i = 0; i < total; i++)
    {
        fprintf(arg, "%s\n", linhas[i]);
    }

    fecharArg(arg);
    printf("Dica editada com sucesso.\n");
}

void editarPalavra(void)
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linhas[200][252];
    int total = 0;
    int c;
    char palavraAtual[51];
    char dicaAtual[201];

    while (total < 200 && fgets(linhas[total], sizeof(linhas[total]), arg))
    {
        linhas[total][strcspn(linhas[total], "\r\n")] = '\0';
        total++;
    }

    fecharArg(arg);

    if (total == 0)
    {
        printf("Nenhuma palavra para editar.\n");
        return;
    }

    printf("\nPalavras disponiveis:\n");
    for (int i = 0; i < total; i++)
    {
        sscanf(linhas[i], "%50[^|]|%200[^\n]", palavraAtual, dicaAtual);
        printf("%2d) %s | %s\n", i + 1, palavraAtual, dicaAtual);
    }

    printf("Escolha o numero da palavra para editar (0 para cancelar): ");
    int escolha;
    if (scanf("%d", &escolha) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Entrada invalida. Nao foi editado.\n");
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

    int editar = escolha - 1;
    sscanf(linhas[editar], "%50[^|]|%200[^\n]", palavraAtual, dicaAtual);

    char novaPalavra[51];
    char novaDica[201];

    printf("Palavra atual: %s\nDica atual: %s\n", palavraAtual, dicaAtual);
    printf("Digite a nova palavra: ");
    if (fgets(novaPalavra, sizeof(novaPalavra), stdin) == NULL)
    {
        printf("Erro na leitura.\n");
        return;
    }
    novaPalavra[strcspn(novaPalavra, "\r\n")] = '\0';

    if (novaPalavra[0] == '\0')
    {
        printf("Palavra vazia. Operacao cancelada.\n");
        return;
    }

    printf("Digite a nova dica: ");
    if (fgets(novaDica, sizeof(novaDica), stdin) == NULL)
    {
        printf("Erro na leitura.\n");
        return;
    }
    novaDica[strcspn(novaDica, "\r\n")] = '\0';

    if (novaDica[0] == '\0')
    {
        strcpy(novaDica, "Sem dica");
    }

    for (int i = 0; i < total; i++)
    {
        if (i != editar)
        {
            char outraPalavra[51], outraDica[201];
            sscanf(linhas[i], "%50[^|]|%200[^\n]", outraPalavra, outraDica);
            if (strcmp(outraPalavra, novaPalavra) == 0)
            {
                printf("Ja existe uma palavra igual. Nao sera editado.\n");
                return;
            }
        }
    }

    printf("Confirmar alteracao (s/n): ");
    char confirmacao = '\0';
    if (scanf(" %c", &confirmacao) != 1)
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

    snprintf(linhas[editar], sizeof(linhas[editar]), "%s|%s", novaPalavra, novaDica);

    arg = abrir("palavras.txt", "w");
    if (arg == NULL)
    {
        return;
    }

    for (int i = 0; i < total; i++)
    {
        fprintf(arg, "%s\n", linhas[i]);
    }

    fecharArg(arg);
    printf("Palavra editada com sucesso.\n");
}

void adicionarPalavras(void)
// ============================================================================
// ADICIONA UMA PALAVRA VINCULADA A UMA DICA
// ============================================================================
// Processo:
//   1. Solicita uma palavra ao usuário (máximo 50 caracteres)
//   2. Exibe lista de dicas disponíveis para seleção
//   3. Permite escolher uma dica ou deixar sem dica
//   4. Pede confirmação antes de salvar
//   5. Verifica se a palavra já existe (evita duplicatas)
//   6. Grava no arquivo palavras.txt no formato: palavra|dica
//
{
    char palavra[51];       // Palavra até 50 caracteres
    char dica[201];         // Dica selecionada do usuário
    char linha[252];        // Buffer para leitura completa (palavra|dica)
    char temp[51];          // Buffer para verificação temporária
    char resposta;          // Confirmação do usuário (s/n)
    bool validacao = false; // Flag: true se palavra já existe
    int c;
    int dicaEscolhida = -1; // Índice da dica escolhida pelo usuário

    // Loop para obter e validar a palavra do usuário
    do
    {
        system("cls");
        printf("Digite uma palavra de ate 50 caracteres: \n");

        if (fgets(palavra, sizeof(palavra), stdin) == NULL)
        {
            continue;
        }
        // Remove newline final
        palavra[strcspn(palavra, "\r\n")] = '\0';

        if (palavra[0] == '\0')
        {
            printf("Palavra vazia. Digite algo antes de continuar.\n");
            continue;
        }

        // Exibe as dicas disponíveis para o usuário escolher
        FILE *dicasArq = abrir("dicas.txt", "r");
        if (dicasArq != NULL)
        {
            printf("\n=== DICAS DISPONIVEIS ===");
            char dicaTemp[201];
            int contador = 1;
            while (fgets(dicaTemp, sizeof(dicaTemp), dicasArq))
            {
                dicaTemp[strcspn(dicaTemp, "\r\n")] = '\0';
                printf("\n%d) %s", contador, dicaTemp);
                contador++;
            }
            printf("\n\nEscolha o numero da dica (0 para nenhuma): ");
            fecharArg(dicasArq);
        }
        else
        {
            printf("\nNenhuma dica cadastrada. Adicione dicas primeiro.\n");
            return;
        }

        // Lê a escolha da dica do usuário
        if (scanf("%d", &dicaEscolhida) != 1)
        {
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            dicaEscolhida = -1;
        }
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        // Obtém o texto completo da dica selecionada
        if (dicaEscolhida > 0)
        {
            dicasArq = abrir("dicas.txt", "r");
            if (dicasArq != NULL)
            {
                int contador = 1;
                while (fgets(dica, sizeof(dica), dicasArq))
                {
                    if (contador == dicaEscolhida)
                    {
                        dica[strcspn(dica, "\r\n")] = '\0';
                        break;
                    }
                    contador++;
                }
                fecharArg(dicasArq);
            }
        }
        else
        {
            strcpy(dica, "Sem dica"); // Usa texto padrão se nenhuma dica foi escolhida
        }

        // Confirmação final do usuário
        printf("\nDeseja salvar a palavra '%s' com a dica '%s'? (s/n): ", palavra, dica);
        if (scanf(" %c", &resposta) != 1)
        {
            resposta = '\0';
        }
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

    } while (resposta != 's' && resposta != 'n');

    if (resposta != 's')
    {
        printf("Palavra descartada.\n");
        return;
    }

    // Abre/cria o arquivo para adicionar a nova palavra
    FILE *arg = abrir("palavras.txt", "a+");
    if (arg == NULL)
    {
        return;
    }

    rewind(arg);
    // Verifica se a palavra já existe no arquivo
    while (fgets(linha, sizeof(linha), arg))
    {
        sscanf(linha, "%[^|]", temp); // Extrai apenas a palavra (antes do |)
        if (strcmp(palavra, temp) == 0)
        {
            printf("A palavra ja existe no arquivo. Nao sera adicionada.\n");
            validacao = true;
            break;
        }
    }

    // Grava a nova palavra e dica se não for duplicata
    if (!validacao)
    {
        fprintf(arg, "%s|%s\n", palavra, dica); // Formato: palavra|dica
        printf("Palavra '%s' adicionada com dica '%s'!\n", palavra, dica);
    }

    fecharArg(arg);
}

void sorteio(void)
{
    char palavra[51];
    char dica[201];

    if (!sortearPalavra(palavra, dica))
    {
        printf("Nao foi possivel sortear palavra. Verifique se 'palavras.txt' existe e possui registros.\n");
        return;
    }

    printf("Palavra sorteada: %s\n", palavra);
    printf("Dica sorteada: %s\n", dica);
}

bool sortearPalavra(char palavra[], char dica[])
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
        return false;

    char linha[252];
    unsigned int total = 0;

    while (fgets(linha, sizeof(linha), arg))
    {
        total++;
    }

    if (total == 0)
    {
        fecharArg(arg);
        return false;
    }

    srand((unsigned int)time(NULL));
    unsigned int indice = rand() % total;

    rewind(arg);
    unsigned int atual = 0;

    while (fgets(linha, sizeof(linha), arg))
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (atual == indice)
        {
            if (sscanf(linha, "%50[^|]|%200[^\n]", palavra, dica) < 1)
            {
                fecharArg(arg);
                return false;
            }
            if (dica[0] == '\0')
            {
                strcpy(dica, "Sem dica");
            }
            fecharArg(arg);
            return true;
        }
        atual++;
    }

    fecharArg(arg);
    return false;
}

unsigned int contarPalavras(void)
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
        return 0;

    char linha[252];
    unsigned int total = 0;

    while (fgets(linha, sizeof(linha), arg))
    {
        total++;
    }

    fecharArg(arg);
    return total;
}

unsigned int palavraSorteada(void)
{
    unsigned int total = contarPalavras();
    if (total == 0)
        return UINT_MAX;

    srand((unsigned int)time(NULL));
    return rand() % total;
}

void jogarForca(void)
{
    printf("\n=== JOGO DA FORCA ===\n");

    char palavra[51];
    char dica[201];

    if (!sortearPalavra(palavra, dica))
    {
        printf("Nenhuma palavra disponivel. Adicione palavras antes de jogar.\n");
        return;
    }

    printf("Dica: %s\n", dica);
    printf("(Modo simplificado) Palavra sorteada: %s\n", palavra);
    printf("Implementacao completa do jogo pode ser adicionada aqui.\n");
}

void mostrarPalavras(void)
// ============================================================================
// EXIBE TODAS AS PALAVRAS COM SUAS DICAS ASSOCIADAS
// ============================================================================
// Processo:
//   1. Abre o arquivo palavras.txt para leitura
//   2. Lê cada linha no formato: palavra|dica
//   3. Extrai a palavra e a dica usando sscanf
//   4. Exibe cada par de forma clara e numerada
//   5. Mostra mensagem se não houver palavras
//
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linha[252];  // Buffer para leitura de linha completa (palavra|dica)
    char palavra[51]; // Palavra extraída
    char dica[201];   // Dica extraída
    int contador = 0; // Contador para numeração

    printf("\n=== PALAVRAS COM DICAS ===");

    // Lê todas as linhas do arquivo
    while (fgets(linha, sizeof(linha), arg))
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        // Extrai palavra e dica do formato: palavra|dica
        // %[^|] lê até encontrar o caractere |
        // %[^\n] lê tudo até a quebra de linha
        sscanf(linha, "%[^|]|%[^\n]", palavra, dica);
        contador++;
        printf("\n%2d) Palavra: %s\n    Dica: %s", contador, palavra, dica);
    }

    if (contador == 0)
    {
        printf("Nenhuma palavra cadastrada.\n");
    }
    else
    {
        printf("\n");
    }

    fecharArg(arg);
}

void removerPalavra(void)
// ============================================================================
// REMOVE UMA PALAVRA E SUA DICA ASSOCIADA
// ============================================================================
// Processo:
//   1. Carrega todas as palavras em memória
//   2. Exibe a lista numerada com suas dicas
//   3. Pede ao usuário qual palavra remover
//   4. Pede confirmação
//   5. Escreve todas as EXCETO a removida no arquivo
//
{
    FILE *arg = abrir("palavras.txt", "r");
    if (arg == NULL)
    {
        return;
    }

    char linhas[200][252]; // Array para armazenar até 200 palavras
    char palavra[51];      // Buffer para extrair palavra
    char dica[201];        // Buffer para extrair dica
    int total = 0;         // Contador de palavras carregadas
    int c;                 // Variável para limpar buffer

    // Carrega todas as palavras em memória
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
        sscanf(linhas[i], "%[^|]|%[^\n]", palavra, dica);
        printf("%2d) Palavra: %s | Dica: %s\n", i + 1, palavra, dica);
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
    sscanf(linhas[remover], "%[^|]|%[^\n]", palavra, dica);
    printf("Tem certeza que deseja remover \"%s\" (dica: %s)? (s/n): ", palavra, dica);
    char confirmacao = '\0';
    if (scanf(" %c", &confirmacao) != 1)
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

// ============================================================================
// FUNÇÕES AUXILIARES DE GERENCIAMENTO DE ARQUIVOS
// ============================================================================

FILE *abrir(char nome[], char modo[])
// ============================================================================
// ABRE UM ARQUIVO COM O MODO ESPECIFICADO
// ============================================================================
// Parâmetros:
//   - nome[]: nome do arquivo a abrir
//   - modo[]: modo de abertura (r=leitura, w=escrita, a+=append, etc.)
//
// Retorno:
//   - FILE*: ponteiro para o arquivo aberto
//   - NULL: se houver erro
//
{
    FILE *arg = fopen(nome, modo);
    if (arg == NULL)
    {
        printf("Nao foi possivel abrir o arquivo %s\n", nome);
    }
    return arg;
}

FILE *fecharArg(FILE *arg)
// ============================================================================
// FECHA UM ARQUIVO ABERTO
// ============================================================================
// Parâmetro:
//   - arg: ponteiro para arquivo aberto
//
// Retorno:
//   - NULL: sempre retorna NULL para facilitar uso em atribuições
//   - Exemplo: temp = fecharArg(temp);
//
{
    if (arg == NULL)
    {
        printf("\nErro ao fechar o arquivo\n");
        return NULL;
    }
    fclose(arg);
    return NULL;
}
