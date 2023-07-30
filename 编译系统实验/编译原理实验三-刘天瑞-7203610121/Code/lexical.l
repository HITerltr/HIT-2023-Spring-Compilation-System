%option yylineno
%option noyywrap
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "main.h"
#include "syntax.tab.h"
int yycolumn = 1;
#define YY_USER_ACTION \
yylloc.first_line = yylloc.last_line = yylineno; \
yylloc.first_column = yycolumn; \
yylloc.last_column = yycolumn + yyleng - 1; \
yycolumn += yyleng;
char error_msg[1024];
char tmpbuf[1024];
node* newnode(){//  CreateNode
    node* node = (node*)malloc(sizeof(node));
    memset(node,0,sizeof(node));
    return node;
}
%}
/*
digits [0-9] 
letter [_a-zA-Z]
RELOP  >|<|>=|<=|==|!=
TAB [\t]
ENTER [\n\r]
TYPE   int|float
STRUCT struct
RETURN return
IF     if
ELSE   else
WHILE  while
INT 0|[1-9]{digits}*
OCT 0[0-7]+
HEX 0x[0-9a-fA-F]+
FLOAT {digits}+"."{digits}+|{digits}+"."{digits}*[Ee][+-]?{digits}+|{digits}*"."{digits}+[Ee][+-]?{digits}+
ID {letter}({digits}|{letter})*
*/
digits [0-9] 
letter [_a-zA-Z]
RELOP  >|<|>=|<=|==|!=
INT 0|[1-9]{digits}*
FLOAT {digits}+"."{digits}+|{digits}+"."{digits}*[Ee][+-]?{digits}+|{digits}*"."{digits}+[Ee][+-]?{digits}+
ID {letter}({digits}|{letter})*
TYPE   int|float

%%


";" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = SEMI;
    node->line = yylineno;
    yylval.type_node = node;
    return SEMI;
}

"," {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = COMMA;
    node->line = yylineno;
    yylval.type_node = node;
    return COMMA;
}

"=" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = ASSIGNOP;
    node->line = yylineno;
    yylval.type_node = node;
    return ASSIGNOP;
}

{RELOP} {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = RELOP;
    node->line = yylineno;
    if(yytext[0] == '>')
        node->relop = RELOP_GT;
    if(yytext[0] == '<')
        node->relop = RELOP_LT;
    if(yytext[0] == '>' && yytext[1] == '=')
        node->relop = RELOP_GE;
    if(yytext[0] == '<' && yytext[1] == '=')
        node->relop = RELOP_LE;
    if(yytext[0] == '=')
        node->relop = RELOP_EQU;
    if(yytext[0] == '!')
        node->relop = RELOP_NEQ;
    yylval.type_node = node;
    return RELOP;
}

"+" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = PLUS;
    node->line = yylineno;
    yylval.type_node = node;
    return PLUS;
}

"-" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = MINUS;
    node->line = yylineno;
    yylval.type_node = node;
    return MINUS;
}

"*" {
    node* node = newnode();
    node->isTerminal=1;
    node->type=STAR;
    node->line=yylineno;
    yylval.type_node=node;
    return STAR;
}

"/" { 
    node* node = newnode();
    node->isTerminal = 1;
    node->type = DIV;
    node->line = yylineno;
    yylval.type_node = node;
    return DIV;
}

"&&" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = AND;
    node->line = yylineno;
    yylval.type_node = node;
    return AND;
}

"||" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = OR;
    node->line = yylineno;
    yylval.type_node = node;
    return OR;
}

"." {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = DOT;
    node->line = yylineno;
    yylval.type_node = node;
    return DOT;
}

"!" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = NOT;
    node->line = yylineno;
    yylval.type_node = node;
    return NOT;
}

{TYPE} {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = TYPE;
    node->line = yylineno;
    strcpy(node->str_val,yytext);
    yylval.type_node = node;
    return TYPE;
}

"(" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = LP;
    node->line = yylineno;
    yylval.type_node = node;
    return LP;
}

")" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = RP;
    node->line = yylineno;
    yylval.type_node = node;
    return RP;
}

"[" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = LB;
    node->line = yylineno;
    yylval.type_node = node;
    return LB;
}

"]" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = RB;
    node->line = yylineno;
    yylval.type_node = node;
    return RB;
}

"{" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = LC;
    node->line = yylineno;
    yylval.type_node = node;
    return LC;
}

"}" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = RC;
    node->line = yylineno;
    yylval.type_node = node;
    return RC;
}

"struct" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = STRUCT;
    node->line = yylineno;
    yylval.type_node = node;
    return STRUCT;
}

"return" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = RETURN;
    node->line = yylineno;
    yylval.type_node = node;
    return RETURN;
}

"if" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = IF;
    node->line = yylineno;
    yylval.type_node = node;
    return IF;
}

"else" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = ELSE;
    node->line = yylineno;
    yylval.type_node = node;
    return ELSE;
}

"while" {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = WHILE;
    node->line = yylineno;
    yylval.type_node = node;
    return WHILE;
}

{FLOAT} {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = FLOAT;
    node->line = yylineno;
    sscanf(yytext,"%f",&node->float_val);
    yylval.type_node = node;
    return FLOAT;
}

{INT} {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = INT;
    node->line = yylineno;
    if(yytext[0] == '0' && (yytext[1] == 'x' || yytext[1] == 'X'))
        sscanf(yytext + 2,"%x",&node->int_val);
    else if(yytext[0] == '0')
        sscanf(yytext,"%o",&node->int_val);
    else
        sscanf(yytext,"%d",&node->int_val);
    yylval.type_node = node;
    return INT;
}

{ID} {
    node* node = newnode();
    node->isTerminal = 1;
    node->type = ID;
    node->line = yylineno;
    strcpy(node->str_val,yytext);
    yylval.type_node = node;
    return ID;
}

\n { yycolumn = 1; }

((" ")|(\t)|\r) {}
"#" {}
"\"" {}
"'" {}
. {}
%%
