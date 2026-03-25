# Jogo da Forca - Gerenciador de Dicas e Palavras

## Descrição do Projeto

Este é um programa em **C** que gerencia dicas e palavras para o jogo da forca. Permite ao usuário adicionar, listar e remover dicas e palavras, com a capacidade de vincular dicas às palavras para melhorar a experiência do jogo.

### Funcionalidades Principais

1. **Gerenciar Dicas**
   - Adicionar novas dicas (máximo 200 caracteres)
   - Listar todas as dicas cadastradas
   - Remover dicas específicas com confirmação
   - Editar dicas existentes
   - Validação de duplicatas

2. **Gerenciar Palavras**
   - Adicionar palavras do jogo (máximo 50 caracteres)
   - Listar todas as palavras com suas dicas associadas
   - Remover palavras específicas com confirmação
   - Editar palavras existentes
   - Validação de duplicatas

3. **Jogo da Forca**
   - Sorteio aleatório de palavra e dica
   - Controle de tentativas e erros
   - Desenho de boneco do enforcado
   - Histórico de partidas (venceu/perdeu, erros, tentativas)
   - Reset de palavras sorteadas

### Arquivos de Dados

- **dicas.txt** - Armazena todas as dicas (uma por linha)
- **palavras.txt** - Armazena as palavras com suas dicas no formato: `palavra|dica`
- **temp.txt** - Arquivo auxiliar para operações temporárias

---

## O Que se Aprende com Este Código

### 1. **Manipulação de Arquivos em C**

- Abrir arquivos em diferentes modos (leitura, escrita, append)
- Ler linhas de arquivos com `fgets()`
- Escrever dados em arquivos com `fprintf()`
- Reposicionar arquivo com `rewind()`
- Fechar arquivos com `fclose()`
- Tratamento de erros ao abrir/fechar arquivos

### 2. **Gerenciamento de Strings**

- Leitura segura de strings com `fgets()` (evita buffer overflow)
- Remoção de caracteres de quebra de linha com `strcspn()`
- Comparação de strings com `strcmp()`
- Cópia de strings com `strcpy()`
- Extração de dados de strings com `sscanf()`

### 3. **Estrutura de Controle de Programa**

- Menu interativo com loop principal (`while(true)`)
- Input validation (validação de entrada do usuário)
- Tratamento de opções do menu
- Limpeza de buffer de entrada
- Uso de flags booleanas para controle de fluxo

### 4. **Organização de Código**

- Separação de responsabilidades (funções específicas)
- Funções auxiliares para tarefas comuns
- Boas práticas de documentação com comentários
- Nomenclatura clara de variáveis
- Estrutura lógica e modular

### 5. **Algoritmos**

- Busca linear em arquivos
- Validação de duplicatas
- Processamento de dados em memória (arrays 2D)
- Reconstrução de arquivos após remoção
- Matching de dados em múltiplos formatos

### 6. **Segurança e Robustez**

- Verificação de retorno de funções
- Validação de limites de array
- Tratamento de entrada inválida do usuário
- Proteção contra leitura/escrita em pontos nulos (NULL pointers)

### 7. **Operações com Arrays**

- Arrays bidimensionais (`char linhas[200][252]`)
- Iteração sobre elementos
- Acesso condicional
- Uso de contadores para rastreamento

---

## Como Compilar e Executar

### Compilação

```bash
gcc.exe -fdiagnostics-color=always -g main.c -o main.exe
```

### Execução

```bash
main.exe
```

---

## Menu do Programa

```
=== Jogo da Forca ===

--- GERENCIAR DICAS ---
1) Adicionar dica
2) Listar dicas
3) Remover dica

--- GERENCIAR PALAVRAS ---
4) Adicionar palavra
5) Listar palavras
6) Remover palavra

--- JOGO ---
7) Jogar forca

--- EDITAR ---
8) Editar dica
9) Editar palavra
10) Resetar palavras sorteadas
11) Mostrar historico de partidas

--- SAIR ---
0) Sair
```

---

## Fluxo de Uso

### Adicionando uma Dica

1. Selecione opção **1**
2. Digite a dica (até 200 caracteres)
3. Confirme com **s** ou **n**
4. O programa verifica se já não existe
5. Grava no arquivo `dicas.txt`

### Adicionando uma Palavra

1. Selecione opção **4**
2. Digite a palavra (até 50 caracteres)
3. Escolha uma dica da lista disponível
4. Confirme a operação
5. O programa grava no formato: `palavra|dica`

### Listando Dados

1. Selecione opção **2** para listar dicas
2. Selecione opção **5** para listar palavras com suas dicas

### Removendo Dados

1. Selecione opção **3** ou **6**
2. Escolha o número do item a remover
3. Confirme a exclusão
4. Arquivo é reescrito sem o item removido

### Jogando Forca

1. Selecione opção **7**
2. Tente adivinhar letra por letra
3. O sistema atualiza tentativas e erros
4. Vence ao completar a palavra antes do boneco ser desenhado

### Editar e Histórico

- Opção **8**: editar texto da dica no arquivo `dicas.txt`
- Opção **9**: editar palavra/dica no arquivo `palavras.txt`
- Opção **10**: resetar o registro de palavras já sorteadas para novo ciclo
- Opção **11**: exibir histórico (palavra, resultado, erros, tentativas)

---

## Conceitos-Chave Implementados

| Conceito                       | Implementação                                |
| ------------------------------ | -------------------------------------------- |
| Entrada do usuário             | `scanf()`, `fgets()`                         |
| Validação                      | Comparação de strings, verificação de vazios |
| Armazenamento persistente      | Arquivos de texto                            |
| Estrutura de dados             | Arrays, strings                              |
| Tratamento de erros            | Verificação de NULL, validação de entrada    |
| Interface de usuário           | Menu baseado em terminal                     |
| Separação de responsabilidades | Funções modularizadas                        |

---

## Estrutura do Código

```
main()
├── adicionarDicas()
├── mostrarDicas()
├── removerDica()
├── adicionarPalavras()
├── mostrarPalavras()
├── removerPalavra()
├── abrir()
└── fecharArg()
```

---

## Extensões Possíveis

O código pode ser melhorado e expandido com:

1. **Estruturas (struct)** - Para armazenar palavra e dica como um único objeto
2. **Busca avançada** - Procurar palavras ou dicas por padrão
3. **Banco de dados** - Usar SQLite em vez de arquivos de texto
4. **Interface gráfica** - Usar bibliotecas como SDL ou Qt
5. **Sistema de pontuação** - Adicionar dificuldade e pontos
6. **Multiplayer** - Suportar múltiplos jogadores
7. **Estatísticas** - Rastrear desempenho do jogador

---

## Requisitos

- **Compilador C** - GCC ou MinGW
- **Sistema Operacional** - Windows, Linux ou macOS
- **Espaço em disco** - Mínimo para armazenar dicas.txt e palavras.txt

---

## Autor

Desenvolvido para aprender conceitos fundamentais de programação em C.

---

## Licença

Este projeto está disponível sob a licença MIT.

---

## Data de Criação

19 de março de 2026
