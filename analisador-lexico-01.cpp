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

char le_caractere(void)
{
  char c;

  if (pos < tamanho)
  {
    c = codigo[pos];
    pos++;
  }
  else
  {
    c = -1;
  }

  return c;
}