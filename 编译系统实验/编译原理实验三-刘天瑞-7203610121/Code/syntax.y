%{
#include<stdio.h>
#include<stdlib.h>
#include "main.h"
#include "lex.yy.c"
node* syntax_tree = NULL;         
node* CreateTree(int type,int line,node* ch_0,node* ch_1,node* ch_2)
{
    if(ch_0 == NULL)
        ch_0 = ch_1, ch_1 = ch_2, ch_2 = NULL;
    if(ch_1 == NULL)
        ch_1 = ch_2, ch_2 = NULL;              
    node* node = Newnode();
    node->isTerminal = 0;
    node->type = type;
    node->line = line;
    node->child = ch_0;
    if(ch_0 != NULL)
        ch_0->next = ch_1;
    if(ch_1 != NULL)
        ch_1->next = ch_2;
    return node;
}
void AddChild(node* node,node* child)
{
    if(child == NULL)
        return;
    if(node->child == NULL)
        node->child = child;
    else{
        for(node* i = node->child; i; i = i->next)
            if(i->next == NULL){
                i->next = child;
                break;
            }
    }
}
%}

%union{
    node* type_node;
}

%token <type_node> SEMI
%token <type_node> COMMA
%token <type_node> ASSIGNOP
%token <type_node> PLUS
%token <type_node> MINUS
%token <type_node> STAR
%token <type_node> DIV
%token <type_node> AND
%token <type_node> OR
%token <type_node> DOT
%token <type_node> NOT
%token <type_node> LP
%token <type_node> RP
%token <type_node> LB
%token <type_node> RB
%token <type_node> LC
%token <type_node> RC
%token <type_node> RELOP
%token <type_node> TYPE
%token <type_node> STRUCT
%token <type_node> RETURN
%token <type_node> IF
%token <type_node> ELSE
%token <type_node> WHILE
%token <type_node> FLOAT
%token <type_node> INT
%token <type_node> ID

%type <type_node> Program ExtDefList ExtDef ExtDecList
%type <type_node> Specifier StructSpecifier OptTag Tag
%type <type_node> VarDec FunDec VarList ParamDec
%type <type_node> CompSt StmtList Stmt
%type <type_node> DefList Def DecList Dec
%type <type_node> Exp Exp1 Exp2 Exp3 Exp4 Exp5 Exp6 Exp7 Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left MINUS PLUS
%left STAR DIV
%right NOT
%left LB RB DOT LP RP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

Program : ExtDefList {
    syntax_tree = CreateTree(Unterm_Program,@$.first_line,$1,NULL,NULL);
    $$ = syntax_tree;
}
;

ExtDefList : ExtDef ExtDefList {
    $$ = CreateTree(Unterm_ExtDefList,@$.first_line,$1,$2,NULL);
}
| {$$ = NULL;}
;

ExtDef : Specifier ExtDecList SEMI {
    $$ = CreateTree(Unterm_ExtDef,@$.first_line,$1,$2,$3);
    $$->subtype = 0;
}
| Specifier SEMI {
    $$ = CreateTree(Unterm_ExtDef,@$.first_line,$1,$2,NULL);
    $$->subtype = 1;
}
| Specifier FunDec CompSt {
    $$ = CreateTree(Unterm_ExtDef,@$.first_line,$1,$2,$3);
    $$->subtype = 2;
}
;

ExtDecList : VarDec {
    $$ = CreateTree(Unterm_ExtDecList,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| VarDec COMMA ExtDecList {
    $$ = CreateTree(Unterm_ExtDecList,@$.first_line,$1,$2,$3);
    $$->subtype = 1;
}
;

Specifier : TYPE {
    $$ = CreateTree(Unterm_Specifier,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| StructSpecifier {
    $$ = CreateTree(Unterm_Specifier,@$.first_line,$1,NULL,NULL);
    $$->subtype = 1;
}
;

StructSpecifier : STRUCT OptTag LC DefList RC {
    $$ = CreateTree(Unterm_StructSpecifier,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    AddChild($$,$5);
    $$->subtype = 0;
}
| STRUCT Tag {
    $$ = CreateTree(Unterm_StructSpecifier,@$.first_line,$1,$2,NULL);
    $$->subtype = 1;
}
;

OptTag : {  $$=NULL;    }
| ID {
    $$ = CreateTree(Unterm_OptTag,@$.first_line,$1,NULL,NULL);
}
;

Tag : ID {
    $$ = CreateTree(Unterm_Tag,@$.first_line,$1,NULL,NULL);
}
;

VarDec : ID {
    $$ = CreateTree(Unterm_VarDec,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| VarDec LB INT RB {
    $$ = CreateTree(Unterm_VarDec,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    $$->subtype = 1;
}
;

FunDec : ID LP VarList RP {
    $$ = CreateTree(Unterm_FunDec,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    $$->subtype = 0;
}
| ID LP RP {
    $$ = CreateTree(Unterm_FunDec,@$.first_line,$1,$2,$3);
    $$->subtype = 1;
}
;

VarList : ParamDec COMMA VarList {
    $$ = CreateTree(Unterm_VarList,@$.first_line,$1,$2,$3);
    $$->subtype = 0;
}
| ParamDec {
    $$ = CreateTree(Unterm_VarList,@$.first_line,$1,NULL,NULL);
    $$->subtype = 1;
}
;

ParamDec : Specifier VarDec {
    $$ = CreateTree(Unterm_ParamDec,@$.first_line,$1,$2,NULL);
}
;

CompSt : LC DefList StmtList RC {
    $$ = CreateTree(Unterm_CompSt,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
}
;

StmtList : {    $$=NULL;    }
| Stmt StmtList {
    $$ = CreateTree(Unterm_StmtList,@$.first_line,$1,$2,NULL);
}
;

Stmt : Exp SEMI {
    $$ = CreateTree(Unterm_Stmt,@$.first_line,$1,$2,NULL);
    $$->subtype = 0;
}
| CompSt {
    $$ = CreateTree(Unterm_Stmt,@$.first_line,$1,NULL,NULL);
    $$->subtype = 1;
}
| RETURN Exp SEMI {
    $$ = CreateTree(Unterm_Stmt,@$.first_line,$1,$2,$3);
    $$->subtype = 2;
}
| IF LP Exp RP Stmt {
    $$ = CreateTree(Unterm_Stmt,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    AddChild($$,$5);
    $$->subtype = 3;
}
| IF LP Exp RP Stmt ELSE Stmt {
    $$ = CreateTree(Unterm_Stmt,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    AddChild($$,$5);
    AddChild($$,$6);
    AddChild($$,$7);
    $$->subtype = 4;
}
| WHILE LP Exp RP Stmt {
    $$ = CreateTree(Unterm_Stmt,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    AddChild($$,$5);
    $$->subtype = 5;
}
;

DefList : { $$=NULL;    }
| Def DefList {
    $$ = CreateTree(Unterm_DefList,@$.first_line,$1,$2,NULL);
}
;

Def : Specifier DecList SEMI {
    $$ = CreateTree(Unterm_Def,@$.first_line,$1,$2,$3);
}
;

DecList : Dec {
    $$ = CreateTree(Unterm_DecList,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| Dec COMMA DecList {
    $$ = CreateTree(Unterm_DecList,@$.first_line,$1,$2,$3);
    $$->subtype = 1;
}
;

Dec : VarDec {
    $$ = CreateTree(Unterm_Dec,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| VarDec ASSIGNOP Exp {
    $$ = CreateTree(Unterm_Dec,@$.first_line,$1,$2,$3);
    $$->subtype = 1;
}
;

Exp1 : ID {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| INT {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,NULL,NULL);
    $$->subtype = 1;
}
| FLOAT {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,NULL,NULL);
    $$->subtype = 2;
}
| LP Exp RP {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 3;
}
| ID LP RP {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 4;
}
| ID LP Args RP {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    $$->subtype = 5;
}
| Exp1 LB Exp RB {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    AddChild($$,$4);
    $$->subtype = 6;
}
| Exp1 DOT ID {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 7;
}
;

Exp2 : Exp1 {
    $$ = $1;      
}
| MINUS Exp2 {
    $$ = reateTree(Unterm_Exp,@$.first_line,$1,$2,NULL);
    $$->subtype = 8;
}
| NOT Exp2 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,NULL);
    $$->subtype = 9;
}
;

Exp3 : Exp2 {
    $$ = $1;
}
| Exp3 STAR Exp2 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 10;
}
| Exp3 DIV Exp2 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 11;
}
;

Exp4 : Exp3 {
    $$ = $1;
}
| Exp4 PLUS Exp3 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 12;
}
| Exp4 MINUS Exp3 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 13;
}
;

Exp5 : Exp4 {
    $$ = $1;
}
| Exp5 RELOP Exp4 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 14;
}
;

Exp6 : Exp5 {
    $$ = $1;
}
| Exp6 AND Exp5 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 15;
}
;

Exp7 : Exp6 {
    $$ = $1;
}
| Exp7 OR Exp6 {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 16;
}
;

Exp : Exp7 {
    $$ = $1;
}
| Exp7 ASSIGNOP Exp {
    $$ = CreateTree(Unterm_Exp,@$.first_line,$1,$2,$3);
    $$->subtype = 17;
}
;

Args : Exp {
    $$ = CreateTree(Unterm_Args,@$.first_line,$1,NULL,NULL);
    $$->subtype = 0;
}
| Exp COMMA Args {
    $$ = CreateTree(Unterm_Args,@$.first_line,$1,$2,$3);
    $$->subtype = 1;
}
;

%%
void yyerror(const char* msg)
{
}
