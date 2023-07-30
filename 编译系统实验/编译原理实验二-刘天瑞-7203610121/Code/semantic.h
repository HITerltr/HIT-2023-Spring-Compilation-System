#ifndef SEMANTIC_H
#define SEMANTIC_H
#include<stdio.h>
#include<stdlib.h>
#include"TreeNode.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
struct Type_
{
    enum {BASIC,ARRAY,STRUCTURE} kind;
    union
    {
        int basic;//0 represents int 1 represents float
        struct {Type elem;int size;} array;//Element type+array size
        FieldList structure;//Structure type
    }u;
};
struct FieldList_
{
    char* name;
    Type type;
    FieldList tail;
};
struct TABLE
{
    //0 is Yes, 1 is No
    //The name of the structure definition will be placed in the symbol table, but it is not a variable that can be used
    int is_def_struct;
    FieldList field;
    struct TABLE* next_for_openhash;
    int linenumber;
};
struct FUNCTION
{
    char* name;//function name
    FieldList field;//parameter list
    Type return_type;//return value
    int declaration;//Number of declarations
    int definition;//Define the number 
    int linenumber;//For error printing
    struct FUNCTION* next_for_openhash;
};

unsigned int generate_hash(char* name);
struct TABLE* find_struct_in_table(char* name);
struct FUNCTION* find_in_function(char* name);
struct FUNCTION* add_to_function(struct FUNCTION* func);
int conflict_between_functions(struct FUNCTION* funca,struct FUNCTION* funcb);
int fieldcmp(FieldList a,FieldList b);
int typecmp(Type a,Type b);
int fieldcmp_forfunc(FieldList a,FieldList b);
void add_to_table(FieldList fiel,int line,int is_def);
Type find_domain_in_struct(Type type,struct TreeNode* now);
int find_param_in_function(struct FUNCTION* func,struct TreeNode* now);

void Program(struct TreeNode* now);
void ExtDef(struct TreeNode* now);
Type Specifier(struct TreeNode* now);
Type StructSpecifier(struct TreeNode* now);

FieldList DefList(struct TreeNode* now,int judge);
FieldList Def(struct TreeNode* now,int judge);
FieldList DecList(struct TreeNode* now,Type type,int judge);
FieldList Dec(struct TreeNode* now,Type type,int judge);

FieldList VarDec(struct TreeNode* now,Type type,int judge);
void ExtDecList(struct TreeNode* now,Type type);

void FunDec(struct TreeNode* now,Type type,int judge);
FieldList VarList(struct TreeNode* now,int judge);
FieldList ParamDec(struct TreeNode* now,int judge);
void CompSt(struct TreeNode* now,Type type);
void StmtList(struct TreeNode* now,Type type);
void Stmt(struct TreeNode* now,Type type);
Type Exp(struct TreeNode* now);
FieldList Args(struct TreeNode* now);

#endif
