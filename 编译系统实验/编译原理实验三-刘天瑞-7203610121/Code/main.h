#ifndef MAIN
#define MAIN

#define RELOP_EQU       0
#define RELOP_NEQ       1
#define RELOP_GT        2
#define RELOP_LT        5
#define RELOP_GE        4
#define RELOP_LE        3
#define Unterm_Program          0
#define Unterm_ExtDefList       1
#define Unterm_ExtDef           2
#define Unterm_ExtDecList       3
#define Unterm_Specifier        4
#define Unterm_StructSpecifier  5
#define Unterm_OptTag           6
#define Unterm_Tag              7
#define Unterm_VarDec           8
#define Unterm_FunDec           9
#define Unterm_VarList          10
#define Unterm_ParamDec         11
#define Unterm_CompSt           12
#define Unterm_StmtList         13
#define Unterm_Stmt             14
#define Unterm_DefList          15
#define Unterm_Def              16
#define Unterm_DecList          17
#define Unterm_Dec              18
#define Unterm_Exp              19
#define Unterm_Args             20

typedef struct Treenode{       
    int isTerminal;         
    int type;                          
    int subtype;            
    int line;               
    int mustright; 
    int relop;//  关系运算符         
    union{                  
        int int_val;        
        float float_val;    
        char str_val[33];   
    };
    struct Treenode* next;     
    struct Treenode* child;    
}node;
typedef node* pnode;



#endif