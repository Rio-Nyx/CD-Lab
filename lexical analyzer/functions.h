#define KW_LEN 32
const char *keywords[] = {
    "auto",   "break",  "case",     "char",    "continue", "do",      "default",
    "const",  "double", "else",     "enum",    "extern",   "for",     "if",
    "goto",   "float",  "int",      "long",    "register", "return",  "signed",
    "static", "sizeof", "short",    "struct",  "switch",   "typedef", "union",
    "void",   "while",  "volatile", "unsigned"};

int isKeyword(char *lexeme) {
  for (int i = 0; i < KW_LEN; i++) {
    if (strncmp(lexeme, keywords[i], 10) == 0) return 1;
  }
  return 0;
}

#define OP_LEN 11
const char operators[] = {'-', '+', '/', '*', '#', '=',
                          '&', '!', '|', '^', '%', '\0'};

int isOperator(char lexeme) {
  for (int i = 0; i < sizeof(operators); i++) {
    if (lexeme == operators[i]) return 1;
  }
  return 0;
}

#define OP_LEN2 6
const char *operators2[] = {"&&", "||", "==", ">=", "<=", "!=", "-", "+", "/",
                            "*",  "#",  "=",  "&",  "!",  "|",  "^", "%"};

int isOperator2(char *lexeme) {
  int len = strlen(lexeme);
  if (len != 2) return 0;
  for (int i = 0; i < OP_LEN2; i++) {
    if (lexeme[0] == operators2[i][0] && lexeme[1] == operators2[i][1])
      return 1;
  }
  return 0;
}

int isIdentifier(char *lexeme) {
  if (isdigit(lexeme[0]) || strlen(lexeme) < 1) {
    return 0;
  }
  for (int i = 1; i < strlen(lexeme); i++) {
    if (!isalpha(lexeme[i]) && !isdigit(lexeme[i]) && lexeme[i] != '_')
      return 0;
  }
  return 1;
}

int isInteger(char *lexeme) {
  if (strlen(lexeme) < 1) return 0;

  for (int i = 0; i < strlen(lexeme); i++) {
    if (lexeme[i] < '0' || lexeme[i] > '9') return 0;
  }
  return 1;
}

#define DEL_LEN 10
const char delimeters[] = {'{', '}', '[', ']', '(',  ')',
                           '<', '>', ';', ',', '\0', '\n'};

int isDelim(char lexeme) {
  for (int i = 0; i < DEL_LEN; i++) {
    if (lexeme == delimeters[i]) return 1;
  }
  return 0;
}

int isSpaces(char lexeme) {
  if (lexeme == ' ' || lexeme == '\n' || lexeme == '\t')
    return 1;
  else
    return 0;
}