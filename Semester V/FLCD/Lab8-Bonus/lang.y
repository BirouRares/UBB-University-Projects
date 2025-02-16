%{
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1
#define INITIAL_BUFFER_SIZE 1024

int yyerror(const char *s);
char *production;
size_t buffer_size = INITIAL_BUFFER_SIZE;

void append_production(const char *prod) {
    size_t needed = strlen(production) + strlen(prod) + 2; // +2 for newline and null terminator
    if (needed > buffer_size) {
        buffer_size *= 2;
        production = realloc(production, buffer_size);
        if (!production) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(1);
        }
    }
    strcat(production, prod);
    strcat(production, "\n");
}

%}

%token BEGIN_BLOCK END_BLOCK IF ELSE WHILE READ WRITE INT STRING CHAR BOOLEAN REAL
%token PLUS MINUS TIMES DIVIDE MODULO ASSIGN EQ NEQ LESS LESSEQ GREATER GREATEREQ
%token BRACEOPEN BRACECLOSE PARENOPEN PARENCLOSE SQBRACKETOPEN SQBRACKETCLOSE
%token COLON SEMICOLON IDENTIFIER INTCONSTANT STRINGCONSTANT
%token INVALID

%start program

%%

program : BEGIN_BLOCK stmtlist END_BLOCK {
    append_production("program -> BEGIN_BLOCK stmtlist END_BLOCK");
}
;

stmtlist : stmt {
    append_production("stmtlist -> stmt");
}
| stmt stmtlist {
    append_production("stmtlist -> stmt stmtlist");
}
;

stmt : simplstmt {
    append_production("stmt -> simplstmt");
}
| structstmt {
    append_production("stmt -> structstmt");
}
;

simplstmt : declaration {
    append_production("simplstmt -> declaration");
}
| assignstmt {
    append_production("simplstmt -> assignstmt");
}
| iostmt {
    append_production("simplstmt -> iostmt");
}
;

declaration : IDENTIFIER COLON type SEMICOLON {
    append_production("declaration -> IDENTIFIER : type ;");
}
;

type : INT {
    append_production("type -> INT");
}
| STRING {
    append_production("type -> STRING");
}
| CHAR {
    append_production("type -> CHAR");
}
| BOOLEAN {
    append_production("type -> BOOLEAN");
}
| REAL {
    append_production("type -> REAL");
}
;

assignstmt : IDENTIFIER ASSIGN expression SEMICOLON {
    append_production("assignstmt -> IDENTIFIER = expression ;");
}
;

expression : term {
    append_production("expression -> term");
}
| term PLUS expression {
    append_production("expression -> term + expression");
}
| term MINUS expression {
    append_production("expression -> term - expression");
}
;

term : IDENTIFIER {
    append_production("term -> IDENTIFIER");
}
| INTCONSTANT {
    append_production("term -> INTCONSTANT");
}
| STRINGCONSTANT {
    append_production("term -> STRINGCONSTANT");
}
;

iostmt : READ PARENOPEN IDENTIFIER PARENCLOSE SEMICOLON {
    append_production("iostmt -> READ ( IDENTIFIER ) ;");
}
| WRITE PARENOPEN expression PARENCLOSE SEMICOLON {
    append_production("iostmt -> WRITE ( expression ) ;");
}
;

structstmt : ifstmt {
    append_production("structstmt -> ifstmt");
}
| whilestmt {
    append_production("structstmt -> whilestmt");
}
;

ifstmt : IF condition BRACEOPEN stmtlist BRACECLOSE {
    append_production("ifstmt -> IF condition { stmtlist }");
}
| IF condition BRACEOPEN stmtlist BRACECLOSE ELSE BRACEOPEN stmtlist BRACECLOSE {
    append_production("ifstmt -> IF condition { stmtlist } ELSE { stmtlist }");
}
;

whilestmt : WHILE condition BRACEOPEN stmtlist BRACECLOSE {
    append_production("whilestmt -> WHILE condition { stmtlist }");
}
;

condition : expression LESS expression {
    append_production("condition -> expression < expression");
}
| expression LESSEQ expression {
    append_production("condition -> expression <= expression");
}
| expression GREATER expression {
    append_production("condition -> expression > expression");
}
| expression GREATEREQ expression {
    append_production("condition -> expression >= expression");
}
| expression EQ expression {
    append_production("condition -> expression == expression");
}
| expression NEQ expression {
    append_production("condition -> expression != expression");
}
;

%%

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}

extern FILE *yyin;

int main(int argc, char **argv) {
    production = malloc(INITIAL_BUFFER_SIZE);
    if (!production) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }
    production[0] = '\0';

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Failed to open file");
            return 1;
        }
    }
    if (!yyparse()) {
        printf("Parsing completed successfully.\n");
        printf("Productions:\n%s", production);
    } else {
        printf("Parsing failed.\n");
    }

    free(production);
    return 0;
}
