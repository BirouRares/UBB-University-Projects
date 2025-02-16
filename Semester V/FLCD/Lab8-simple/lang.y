%{
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

int yyerror(const char *s);
%}

%token BEGIN_BLOCK END_BLOCK IF ELSE WHILE READ WRITE INT STRING CHAR BOOLEAN REAL
%token PLUS MINUS TIMES DIVIDE MODULO ASSIGN EQ NEQ LESS LESSEQ GREATER GREATEREQ
%token BRACEOPEN BRACECLOSE PARENOPEN PARENCLOSE SQBRACKETOPEN SQBRACKETCLOSE
%token COLON SEMICOLON IDENTIFIER INTCONSTANT STRINGCONSTANT
%token INVALID

%start program

%%

program : BEGIN_BLOCK stmtlist END_BLOCK {
    printf("program -> BEGIN_BLOCK stmtlist END_BLOCK\n");
}
;

stmtlist : stmt {
    printf("stmtlist -> stmt\n");
}
| stmt stmtlist {
    printf("stmtlist -> stmt stmtlist\n");
}
;

stmt : simplstmt {
    printf("stmt -> simplstmt\n");
}
| structstmt {
    printf("stmt -> structstmt\n");
}
;

simplstmt : declaration {
    printf("simplstmt -> declaration\n");
}
| assignstmt {
    printf("simplstmt -> assignstmt\n");
}
| iostmt {
    printf("simplstmt -> iostmt\n");
}
;

declaration : IDENTIFIER COLON type SEMICOLON {
    printf("declaration -> IDENTIFIER : type ;\n");
}
;

type : INT {
    printf("type -> INT\n");
}
| STRING {
    printf("type -> STRING\n");
}
| CHAR {
    printf("type -> CHAR\n");
}
| BOOLEAN {
    printf("type -> BOOLEAN\n");
}
| REAL {
    printf("type -> REAL\n");
}
;

assignstmt : IDENTIFIER ASSIGN expression SEMICOLON {
    printf("assignstmt -> IDENTIFIER = expression ;\n");
}
;

expression : term {
    printf("expression -> term\n");
}
| term PLUS expression {
    printf("expression -> term + expression\n");
}
| term MINUS expression {
    printf("expression -> term - expression\n");
}
;

term : IDENTIFIER {
    printf("term -> IDENTIFIER\n");
}
| INTCONSTANT {
    printf("term -> INTCONSTANT\n");
}
| STRINGCONSTANT {
    printf("term -> STRINGCONSTANT\n");
}
;

iostmt : READ PARENOPEN IDENTIFIER PARENCLOSE SEMICOLON {
    printf("iostmt -> READ ( IDENTIFIER ) ;\n");
}
| WRITE PARENOPEN expression PARENCLOSE SEMICOLON {
    printf("iostmt -> WRITE ( expression ) ;\n");
}
;

structstmt : ifstmt {
    printf("structstmt -> ifstmt\n");
}
| whilestmt {
    printf("structstmt -> whilestmt\n");
}
;

ifstmt : IF condition BRACEOPEN stmtlist BRACECLOSE {
    printf("ifstmt -> IF condition { stmtlist }\n");
}
| IF condition BRACEOPEN stmtlist BRACECLOSE ELSE BRACEOPEN stmtlist BRACECLOSE {
    printf("ifstmt -> IF condition { stmtlist } ELSE { stmtlist }\n");
}
;

whilestmt : WHILE condition BRACEOPEN stmtlist BRACECLOSE {
    printf("whilestmt -> WHILE condition { stmtlist }\n");
}
;

condition : expression LESS expression {
    printf("condition -> expression < expression\n");
}
| expression LESSEQ expression {
    printf("condition -> expression <= expression\n");
}
| expression GREATER expression {
    printf("condition -> expression > expression\n");
}
| expression GREATEREQ expression {
    printf("condition -> expression >= expression\n");
}
| expression EQ expression {
    printf("condition -> expression == expression\n");
}
| expression NEQ expression {
    printf("condition -> expression != expression\n");
}
;

%%

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}

extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Failed to open file");
            return 1;
        }
    }
    if (!yyparse()) {
        printf("Parsing completed successfully.\n");
    } else {
        printf("Parsing failed.\n");
    }
    return 0;
}