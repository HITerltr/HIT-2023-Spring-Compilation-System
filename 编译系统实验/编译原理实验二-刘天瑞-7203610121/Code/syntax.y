%{
#include<stdio.h>
#include<string.h>
#include"TreeNode.h"
extern int yylineno;
extern char* yytext;
#define YYSTYPE struct Node* 
struct Node* head = NULL;//Every time a new malloc is generated, it is updated because the last header must be generated last.
int is_error = 0;//0 indicates no errors, printing; Other++.
struct Node* Create_TreeNode(struct Node* c,char* name,int line)
{
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->judge = 1;
    newnode->child = c;
    newnode->brother = NULL;
    newnode->linenumber = line;
    newnode->int_number = 1;
    strcpy(newnode->name,name);
    head = newnode;
    ("head: %u\n",head);
    ("newnode'name: %s\n",head->name);
    return newnode;
}
void print_node(struct Node* now)
{
    if(now->judge == 0)
    {
        //syntax
        if(!strcmp(now->name,"ID\0"))
        {
            printf("ID: %s\n",now->char_name);
            }
        else if(!strcmp(now->name,"TYPE\0"))
        {
            printf("TYPE: %s\n",now->char_name);
            }
        else if(!strcmp(now->name,"INT\0"))
        {
            printf("INT: %u\n",now->int_number);
            }
        else if(!strcmp(now->name,"FLOAT\0"))
        {
            printf("FLOAT: %f\n",now->float_number);
            }
        else
        {
            printf("%s\n",now->name);
            }
            }
    else
    {
        //lexical
        printf("%s (%d)\n",now->name,now->linenumber);
        }
}

void print_tree(struct Node* heads)
{
    struct Node* tree_sort[2000];
    tree_sort[0] = heads;
    print_node(heads);
    int number = 1;
    int depth = 0;
    while(number != 0)
    {
        if(tree_sort[number - 1]->child != NULL){
            tree_sort[number] = tree_sort[number-1]->child;
            tree_sort[number - 1]->child = NULL;
            number++;
            depth++;
            if(tree_sort[number - 1]->judge != 0&&tree_sort[number - 1]->int_number == 0);
            else
            {
                for(int i = 0;i < depth;i++)
                {
                    printf("  ");
                    }
                print_node(tree_sort[number - 1]);
            }
        }
        else if(tree_sort[number - 1]->brother != NULL)
        {
            tree_sort[number - 1] = tree_sort[number - 1]->brother;
            if(tree_sort[number - 1]->judge != 0&&tree_sort[number - 1]->int_number == 0);
            else
            {
                for(int i = 0;i < depth;i++)
                {
                    printf("  ");
                    }
                print_node(tree_sort[number - 1]);
            }
        }
        else
        {
            number--;
            depth--;
        }
    }
}
//Just mark all token types as nodes for the following reasons:
//1.Because they can all be printed as nodes;
//2.You can directly use $1 to take values.
%}
%locations
%token STRUCT
%token RETURN
%token IF
%token ELSE
%token WHILE
%token SEMI
%token COMMA
%token ASSIGNOP
%token PLUS
%token MINUS
%token STAR
%token DIV
%token AND
%token OR
%token NOT
%token LP
%token RP
%token LB
%token RB
%token LC
%token RC
%token TYPE
%token INT
%token FLOAT
%token ID
%token RELOP
%token DOT
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NAGATE NOT
%right DOT LP LB RP RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
Program:ExtDefList
{
    //printf("Program->ExtDefList\n");
    if($1->int_number == 0)
    {
        $$ = Create_TreeNode($1,"Program\0",$1->linenumber);
    }
    else
        $$ = Create_TreeNode($1,"Program\0",@1.first_line);
        }

ExtDefList: 
{
    $$ = Create_TreeNode(NULL,"ExtDefList\0",yylineno);
    $$->int_number=0;
    }
|ExtDef ExtDefList
{
    //printf("ExtDefList->ExtDef ExtDefList\n");
    $$ = Create_TreeNode($1,"ExtDefList\0",@1.first_line);
    $$->int_number = 2;
    $1->brother = $2;
    }

ExtDef:Specifier ExtDecList SEMI
{
    //printf("ExtDef->Specifier ExtDecList SEMI\n");
    $$ = Create_TreeNode($1,"ExtDef\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Specifier SEMI
{
    //printf("ExtDef->Specifier SEMI\n");
    $$ = Create_TreeNode($1,"ExtDef\0",@1.first_line);
    $1->brother=$2;
    }
|Specifier FunDec CompSt
{
    //printf("ExtDef->Specifier FunDec CompSt\n");
    $$ = Create_TreeNode($1,"ExtDef\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Specifier ExtDecList error SEMI
{//printf("error2\n");
}
|Specifier error SEMI
{//printf("error2.1\n");
}
|Specifier FunDec SEMI
{
    //add for 2.1
    //printf("ExtDef->Specifier FunDec SEMI\n");
    $$ = Create_TreeNode($1,"ExtDef\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }

ExtDecList:VarDec
{
    //printf("ExtDecList->VarDec\n");
    $$ = Create_TreeNode($1,"ExtDecList\0",@1.first_line);
    }
|VarDec COMMA ExtDecList
{
    //printf("ExtDecList->VarDec COMMA ExtDecList\n");
    $$ = Create_TreeNode($1,"ExtDecList\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|VarDec COMMA error ExtDecList

Specifier:TYPE
{
    //printf("Specifier->TYPE\n");
    $$ = Create_TreeNode($1,"Specifier\0",@1.first_line);
    }
|StructSpecifier
{
    //printf("Specifier->StructSpecifier\n");
    $$ = Create_TreeNode($1,"Specifier\0",@1.first_line);
    }

StructSpecifier:STRUCT OptTag LC DefList RC
{
    //printf("StructSpecifier->STRUCT OptTag LC DefList RC\n");
    $$ = Create_TreeNode($1,"StructSpecifier\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    $4->brother = $5;
    }
|STRUCT Tag
{
    //printf("StructSpecifier->STRUCT Tag\n");
    $$ = Create_TreeNode($1,"StructSpecifier\0",@1.first_line);
    $1->brother = $2;
    }
|STRUCT OptTag LC error RC
{//printf("error4\n");
}
|STRUCT error LC DefList RC
{//printf("error5\n");
}

OptTag: 
{
    $$ = Create_TreeNode(NULL,"OptTag\0",0);
    $$->int_number = 0;
    }
|ID
{
    //printf("OptTag->ID");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"OptTag\0",@1.first_line);
    }

Tag:ID
{
    //printf("Tag->ID");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"Tag\0",@1.first_line);
    }

VarDec:ID
{
    //printf("VarDec->ID");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"VarDec\0",@1.first_line);
    }
|VarDec LB INT RB
{
    //printf("VarDec->VarDec LB INT RB\n");
    $$ = Create_TreeNode($1,"VarDec\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    }
|VarDec LB error RB
{//printf("error6\n");
}

FunDec:ID LP VarList RP
{
    //printf("FunDec->ID LP VarList RP");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"FunDec\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    }
|error LP VarList RP
{//printf("error7\n");
}
|ID LP error RP
{//printf("error8\n");
}
|ID LP RP
{
    //printf("FunDec->ID LP RP");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"FunDec\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }

VarList:ParamDec COMMA VarList
{
    //printf("VarList->ParamDec COMMA VarList\n");
    $$ = Create_TreeNode($1,"VarList\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|error COMMA VarList
|ParamDec
{
    //printf("VarList->ParamDec\n");
    $$ = Create_TreeNode($1,"VarList\0",@1.first_line);
    }

ParamDec:Specifier VarDec
{
    //printf("ParamDec->Specifier VarDec\n");
    $$ = Create_TreeNode($1,"ParamDec\0",@1.first_line);
    $1->brother = $2;
    }

CompSt:LC DefList StmtList RC
{
    //printf("CompSt->LC DefList StmtList RC\n");
    $$ = Create_TreeNode($1,"CompSt\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    }
|LC DefList StmtList error RC

StmtList: 
{
    $$ = Create_TreeNode(NULL,"StmtList\0",0);
    $$->int_number = 0;
    }
|Stmt StmtList
{
    //printf("StmtList->Stmt StmtList\n");
    $$ = Create_TreeNode($1,"StmtList\0",@1.first_line);
    $1->brother = $2;
    }

Stmt:Exp SEMI
{
    //printf("Stmt->Exp SEMI\n");
    $$ = Create_TreeNode($1,"Stmt\0",@1.first_line);
    $1->brother = $2;
    }
|Exp error
|Exp error SEMI
{//printf("error10\n");
}
|CompSt
{
    //printf("Stmt->CompSt\n");
    $$ = Create_TreeNode($1,"Stmt\0",@1.first_line);
    }
|RETURN Exp SEMI
{
    //printf("Stmt->RETURN Exp SEMI\n");
    $$ = Create_TreeNode($1,"Stmt\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|RETURN error SEMI
{//printf("error11\n");
}
|RETURN Exp error
{//printf("error12\n");
}
|IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
{
    //printf("Stmt->IF LP Exp RP Stmt\n");
    $$ = Create_TreeNode($1,"Stmt\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    $4->brother = $5;
    }
|IF LP error RP Stmt
|IF LP Exp RP Stmt ELSE Stmt
{
    //printf("Stmt->IF LP Exp RP Stmt ELSE Stmt\n");
    $$ = Create_TreeNode($1,"Stmt\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    $4->brother = $5;
    $5->brother = $6;
    $6->brother = $7;
    }
|IF LP error RP Stmt ELSE Stmt
|WHILE LP Exp RP Stmt
{
    //printf("Stmt->WHILE LP Exp RP Stmt\n");
    $$ = Create_TreeNode($1,"Stmt\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    $4->brother = $5;
    }
|WHILE LP error RP Stmt
{//printf("error13\n");
}
|WHILE LP Exp RP error
{//printf("error14\n");
}
|WHILE error RP Stmt
{//printf("error15\n");
}
|WHILE LP error Stmt
{//printf("error16\n");
}

DefList: 
{
    $$ = Create_TreeNode(NULL,"DefList\0",0);
    $$->int_number = 0;
    }
|Def DefList
{
    //printf("DefList->Def DefList\n");
    $$ = Create_TreeNode($1,"DefList\0",@1.first_line);
    $1->brother = $2;
    }

Def:Specifier DecList SEMI
{
    //printf("Def->Specifier DecList SEMI\n");
    $$ = Create_TreeNode($1,"Def\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Specifier DecList error SEMI

DecList:Dec
{
    //printf("DecList->Dec\n");
    $$ = Create_TreeNode($1,"DecList\0",$1->linenumber);
    }
|Dec COMMA DecList{
    //printf("DecList->Dec COMMA DecList\n");
    $$ = Create_TreeNode($1,"DecList\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|error COMMA DecList

Dec:VarDec
{
    //printf("Dec->VarDec\n");
    $$ = Create_TreeNode($1,"Dec\0",@1.first_line);
    }
|VarDec ASSIGNOP Exp
{
    //printf("Dec->VarDec ASSIGNOP Exp\n");
    $$ = Create_TreeNode($1,"Dec\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|VarDec ASSIGNOP error Exp
{//printf("error var\n");
}

Exp:Exp ASSIGNOP Exp
{
    //printf("Exp->Exp ASSIGNOP Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp ASSIGNOP error
{//printf("error19\n");
}
|Exp AND Exp
{
    //printf("Exp->Exp AND Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp AND error
{//printf("error20\n");
}
|Exp OR Exp
{
    //printf("Exp->Exp OR Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp OR error
{//printf("error21\n");
}
|Exp RELOP Exp
{
    //printf("Exp->Exp RELOP Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp RELOP error
{//printf("error22\n");
}
|Exp PLUS Exp
{
    //printf("Exp->Exp PLUS Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp PLUS error
{//printf("error23\n");
}
|Exp MINUS Exp
{
    //printf("Exp->Exp MINUS Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp MINUS error
{//printf("error24\n");
}
|Exp STAR Exp
{
    //printf("Exp->Exp STAR Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp STAR error
{//printf("error25\n");
}
|Exp DIV Exp
{
    //printf("Exp->Exp DIV Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp DIV error
{//printf("error26\n");
}
|LP Exp RP
{
    //printf("Exp->LP Exp RP\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|LP error RP
{//printf("error27\n");
} 
|MINUS Exp %prec NAGATE
{
    //printf("Exp->MINUS Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    }
|MINUS error
{//printf("error27.1\n");
}
|NOT Exp
{
    //printf("Exp->NOT Exp\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    }
|NOT error
{//printf("error27.2\n");
}
|ID LP Args RP
{
    //printf("Exp->ID LP Args RP");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    }
|ID LP RP
{
    //printf("Exp->ID LP RP");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp LB Exp RB
{
    //printf("Exp->Exp LB Exp RB\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    $3->brother = $4;
    }
|Exp DOT ID
{
    //printf("Exp->Exp DOT ID");
    //printf("   ID:%s\n",$3->char_name);
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|ID
{
    //printf("Exp->ID");
    //printf("   ID:%s\n",$1->char_name);
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    }
|INT
{
    //printf("Exp->INT\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    }
|FLOAT
{
    //printf("Exp->FLOAT\n");
    $$ = Create_TreeNode($1,"Exp\0",@1.first_line);
    }

Args:Exp COMMA Args
{
    //printf("Args->Exp COMMA Args\n");
    $$ = Create_TreeNode($1,"Args\0",@1.first_line);
    $1->brother = $2;
    $2->brother = $3;
    }
|Exp COMMA error Args
|Exp
{
    //printf("Args->Exp\n");
    $$ = Create_TreeNode($1,"Args\0",@1.first_line);
    }  
%%
#include"lex.yy.c"
int yyerror(char* msg)
{
    printf("Error type B at Line %d: syntax error at \"%s\".\n", yylineno, yytext);
    is_error++;
}
// yyprint(NODE* head);
