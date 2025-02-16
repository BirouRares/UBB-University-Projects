%{
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

int yyerror(const char *s);
%}

%token INT;
%token REAL;
%token STR;
%token CHAR;
%token BOOL;
%token READ;
%token IF;
%token ELSE;
%token WRITE;
%token WHILE;
%token REPORT;
%token ARR;
%token AND;
%token OR;

%token PLUS;
%token MINUS;
%token TIMES;
%token DIV;
%token MOD;
%token BIGGEREQ;
%token LESSEQ;
%token BIGGER;
%token LESS;
%token EQQ;
%token EQ;
%token NEQ;

%token SQBRACKETOPEN;
%token SQBRACKETCLOSE;
%token OPEN;
%token CLOSE;
%token BRACKETOPEN;
%token BRACKETCLOSE;
%token DOT;
%token COMMA;
%token COLON;
%token SEMICOLON;
%token END_BLOCK;
%token BEGIN_BLOCK;
%token ENDL;

%token IDENTIFIER;
%token INTCONSTANT;
%token STRINGCONSTANT;


%start program

%%
program : REPORT BRACKETOPEN stmtlist BRACKETCLOSE   { printf("program -> report { stmtlist }\n"); }
        ;

stmtlist : stmt              { printf("stmtlist -> stmt\n"); }
         | stmt stmtlist     { printf("stmtlist -> stmt stmtlist\n"); }
         ;

stmt : simplstmt            { printf("stmt -> simplstmt\n"); }
     | structstmt           { printf("stmt -> structstmt\n"); }
     ;

simplstmt : declaration           { printf("stmt -> declaration\n"); }
          | assignstmt            { printf("stmt -> assignstmt\n"); }
          | iostmt                { printf("stmt -> iostmt\n"); }
          ;

declaration : IDENTIFIER COLON type { printf("declaration -> IDENTIFIER : type\n"); }
            ;

type : type1                { printf("type -> type1\n"); }
     | arraydecl            { printf("type -> arraydecl\n"); }
     ;

type1 : INT                { printf("type1 -> int\n"); }
      | REAL               { printf("type1 -> real\n"); }
      | STR                { printf("type1 -> str\n"); }
      | CHAR               { printf("type1 -> char\n"); }
      | BOOL               { printf("type1 -> bool\n"); }
      ;

arraydecl : ARR OPEN type1 CLOSE SQBRACKETOPEN INTCONSTANT SQBRACKETCLOSE { printf("arraydecl -> arr ( type1 ) [ INTCONSTANT ]\n"); }
          ;

assignstmt : IDENTIFIER EQ expression { printf("assignstmt -> IDENTIFIER = expression\n"); }
           ;

operator : PLUS              { printf("operator -> +\n"); }
         | MINUS             { printf("operator -> -\n"); }
         | TIMES             { printf("operator -> *\n"); }
         | DIV               { printf("operator -> /\n"); }
         | MOD               { printf("operator -> %%\n"); }
         ;

expression : term                         { printf("expression -> term\n"); }
           | term operator expression     { printf("expression -> term operator expression\n"); }
           ;

term : IDENTIFIER            { printf("term -> IDENTIFIER\n"); }
     | INTCONSTANT           { printf("term -> INTCONSTANT\n"); }
     | factor                { printf("term -> factor\n"); }
     ;

factor : MINUS IDENTIFIER            { printf("factor -> - IDENTIFIER\n"); }
       | IDENTIFIER SQBRACKETOPEN IDENTIFIER SQBRACKETCLOSE { printf("factor -> IDENTIFIER [ IDENTIFIER ]\n"); }
       | IDENTIFIER SQBRACKETOPEN INTCONSTANT SQBRACKETCLOSE { printf("factor -> IDENTIFIER [ INTCONSTANT ]\n"); }
       | OPEN expression CLOSE       { printf("factor -> ( expression )\n"); }
       ;

iostmt : READ OPEN IDENTIFIER CLOSE       { printf("iostmt -> read (IDENTIFIER )\n"); }
       | WRITE OPEN IDENTIFIER CLOSE      { printf("iostmt -> write ( IDENTIFIER )\n"); }
       | WRITE OPEN INTCONSTANT CLOSE     { printf("iostmt -> write ( INTCONSTANT )\n"); }
       | WRITE OPEN STRINGCONSTANT CLOSE  { printf("iostmt -> write ( STRINGCONSTANT )\n"); }
       | WRITE OPEN ENDL CLOSE            { printf("iostmt -> write ( endl )\n"); }
       ;

structstmt : ifstmt           { printf("structstmt -> ifstmt\n"); }
           | whilestmt        { printf("structstmt -> whilestmt\n"); }
           ;

ifstmt : IF condition BEGIN_BLOCK COLON stmtlist END_BLOCK SEMICOLON                                 { printf("ifstmt -> if condition begin : stmtlist end ;\n"); }
       | IF condition BEGIN_BLOCK COLON stmtlist ELSE BEGIN_BLOCK COLON stmtlist END_BLOCK SEMICOLON { printf("ifstmt -> if condition begin : stmtlist else begin : stmtlist end ;\n"); }
       ;

condition : expression RELATION expression                       { printf("condition -> expression RELATION expression\n"); }
          | expression RELATION expression AND condition         { printf("condition -> expression RELATION expression and condition\n"); }
          | expression RELATION expression OR condition          { printf("condition -> expression RELATION expression or condition\n"); }
          ;

RELATION : BIGGEREQ           { printf("RELATION -> >=\n"); }
         | LESSEQ             { printf("RELATION -> <=\n"); }
         | BIGGER             { printf("RELATION -> >\n"); }
         | LESS               { printf("RELATION -> <\n"); }
         | EQQ                { printf("RELATION -> ==\n"); }
         | EQ                 { printf("RELATION -> =\n"); }
         | NEQ                { printf("RELATION -> !=\n"); }
         ;

whilestmt : WHILE condition BEGIN_BLOCK COLON stmtlist END_BLOCK SEMICOLON { printf("whilestmt -> while condition begin : stmtlist end ;\n"); }
          ;


%%

int yyerror(const char *s) {
    printf("%s\n",s);
    return 0;
}

extern FILE *yyin;

int main(int argc, char** argv) {
    if (argc > 1)
        yyin = fopen(argv[1], "r");
    if (!yyparse())
        fprintf(stderr, "\tOK\n");
}
