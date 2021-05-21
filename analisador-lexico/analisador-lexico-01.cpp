// Analisador Léxico Inicial 4ECA
// Referência Apostila 2.1.1

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
  int tipo;
  int valor;
} Token;

#define TRUE 1  // Verdadeiro.
#define FALSE 0 // Falso.

#define TOK_NUM 0  // Token numérico.
#define TOK_OP 1   // Token de operações.
#define TOK_PONT 2 // Token de pont.

#define SOMA 0 // Operação de Soma.
#define SUB 1  // Operação de Subtração.
#define MULT 2 // Operação de Multiplicação.
#define DIV 3  // Operação de divisão.

#define PAR_E 0 // Parênteses esquerdo.
#define PAR_D 1 // Parênteses direito.

const char *ops = "+-*/"; // Ponteiro para localizar as operações.
char *codigo;             // Ponteiro para o código.
int tamanho;
int pos;

// Função para ler caractere e retornar seu código, caso não encontre retorna -1.
char le_caractere(void)
{
  char c;
  if (pos < tamanho)
  {
    c = codigo[pos];
    pos++;
    return c;
  }
  else
    return -1;
}

// Função para ler operador e retornar seu código, caso não encontre retorna -1.
int operador(char c)
{
  switch (c)
  {
  case '+':
    return SOMA;
  case '-':
    return SUB;
  case '*':
    return MULT;
  case '/':
    return DIV;

  default:
    return -1;
  }
}

// Função para ler código e retornar seu operador, caso não encontre retorna -1.
char *str_operador(int op)
{
  switch (op)
  {
  case SOMA:
    return "+";
    break;
  case SUB:
    return "-";
    break;
  case MULT:
    return "*";
    break;
  case DIV:
    return "/";
    break;
  default:
    return "Erro";
  }
}

// Função para iniciar analise.
void inicializa_analise(char *prog)
{
  codigo = prog;
  tamanho = strlen(codigo);
  pos = 0;
}

Token *proximo_token(Token *tok)
{
  char c;
  char valor[200];
  int valorPosicao = 0;

  c = le_caractere();

  while (isspace(c))
  {
    c = le_caractere();
  }

  if (isdigit(c))
  {
    tok->tipo = TOK_NUM;
    valor[valorPosicao++] = c;
    c = le_caractere();
    while (isdigit(c))
    {
      valor[valorPosicao++] = c;
      c = le_caractere();
    }
    pos--;
    valor[valorPosicao] = '\0';
    tok->valor = atoi(valor);
  }
  else if (strchr(ops, c) != NULL)
  {
    tok->tipo = TOK_OP;
    tok->valor = operador(c);
  }
  else if (c == '(' || c == ')')
  {
    tok->tipo = TOK_PONT;
    tok->valor = (c == '(' ? PAR_E : PAR_D);
  }
  else
  {
    return NULL;
  }
  return tok;
}

// Função básica para imprimir em um arquivo o tipo e valor do tok.
void imprime_token(Token *tok, FILE *arquivo)
{
  switch (tok->tipo)
  {
  case TOK_NUM:
    fprintf(arquivo, "Token Numérico");
    fprintf(arquivo, "\t  - Valor: %d\n", tok->valor);
    break;
  case TOK_OP:
    fprintf(arquivo, "Token de Operação");
    fprintf(arquivo, " - Valor: %s\n", str_operador(tok->valor));
    break;
  case TOK_PONT:
    fprintf(arquivo, "Token Pontuação");
    fprintf(arquivo, "\t  - Valor: %s\n", tok->valor == PAR_E ? "(" : ")");
    break;
  default:
    fprintf(arquivo, "Token desconhecido");
  }
}

int main(void)
{
  char entrada[200];
  Token tok;

  printf("\n\nAnalisador Léxico\n");

  printf("Lendo arquivo... ");
  FILE *arquivo_leitura;
  FILE *arquivo_escrita;

  arquivo_leitura = fopen("entrada.txt", "r");
  arquivo_escrita = fopen("saida.txt", "w");
  fgets(entrada, 200, arquivo_leitura);

  inicializa_analise(entrada);

  printf("\nEscrevendo arquivo... \n");
  while (proximo_token(&tok) != NULL)
  {
    imprime_token(&tok, arquivo_escrita);
  }

  fclose(arquivo_leitura);
  printf("Fim.\n");
  return 0;
}