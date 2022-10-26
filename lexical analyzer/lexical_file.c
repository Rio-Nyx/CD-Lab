#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define file "lexical.c"

#define debug(x) puts(x)
static int comment_flag = 0;
// #define debug(x) ;

int handle_line(char *line) {
  int a = 8a;
  char line_copy[1024];
  strncpy(line_copy, line, 1024);
  int lit_flag = 0;
  int lit_type = 1;  // 1- "  &&  2-'
  char lexeme[1024] = "";
  for (int i = 0; i < strlen(line); i++) {
    char curr_char = line[i];

    // handling multiline comment
    if (i + 1 < strlen(line) && (line[i] == '/' && line[i + 1] == '*')) {
      comment_flag = 1;
    }
    if (i + 1 < strlen(line) && (line[i] == '*' && line[i + 1] == '/')) {
      comment_flag = 0;
    }
    // if still inside comment
    if (comment_flag == 1) {
      continue;
    }

    // handling single line comment
    if (i + 1 < strlen(line) && (line[i] == '/' && line[i + 1] == '/')) {
      break;
    }

    // handling string literals
    if (strlen(lexeme) < 1 && lit_flag == 0) {
      if (curr_char == '"') {
        lit_type = 1;
        lit_flag = 1;

      } else if (curr_char == '\'') {
        lit_type = 2;
        lit_flag = 1;
      }
    } else if (lit_flag == 1 && ((lit_type == 1 && curr_char == '"') ||
                                 (lit_type == 2 && curr_char == '\''))) {
      lit_flag = 0;
      int len = strlen(lexeme);
      lexeme[len] = curr_char;
      lexeme[len + 1] = '\0';

      // changes made to print literals and " seperately
      if (lexeme[len] == '"') {
        printf("<%s,%s>\n", "\"", "symbol");
        for (int i = 0; i < len + 1; i++) {
          lexeme[i] = lexeme[i + 1];
        }
        lexeme[len - 1] = '\0';
        printf("<%s,%s>\n", lexeme, "literal");
        printf("<%s,%s>\n", "\"", "symbol");
      }
      // printf("<%s,%s>\n", lexeme, "literal");
      lexeme[0] = '\0';
      continue;
    }

    // checking if encountered a delimiter outside a string literal
    if (lit_flag == 0 && (isSpaces(curr_char) == 1 || isDelim(curr_char) == 1 ||
                          isOperator(curr_char) == 1)) {
      if (isKeyword(lexeme) == 1) {
        printf("<%s,%s>\n", lexeme, "keyword");
      } else if (isIdentifier(lexeme) == 1) {
        printf("<%s,%s>\n", lexeme, "identifier");
      } else if (isInteger(lexeme) == 1) {
        printf("<%s,%s>\n", lexeme, "integer");
      } else if (strlen(lexeme) > 0) {
        if (isOperator2(lexeme) == 1) {
          printf("<%s,%s>\n", lexeme, "operator2");
        } else {
          printf("<%s,%s>\n", lexeme, "invalid identifier");
        }
      }
      if (isSpaces(curr_char) == 0) {
        if (isOperator(curr_char) == 1) {
          printf("<%c,%s>\n", curr_char, "operator");
        } else {
          printf("<%c,%s>\n", curr_char, "symbol");
        }
      }
      lexeme[0] = '\0';
    } else {
      // append to lexeme until a delimiter is encountered
      int len = strlen(lexeme);
      lexeme[len] = curr_char;
      lexeme[len + 1] = '\0';
    }
  }
}

int main() {
  /* comment */
  
  FILE *fp;
  fp = fopen(file, "r");
  fseek(fp, 0, SEEK_SET);

  char line[1024];
  int i=0;
  while (fgets(line, 1024, fp)) {
    i++;
    printf("%d\n",i); // comment
    handle_line(line);
  };
  // fclose(file);
  return 0;
}

