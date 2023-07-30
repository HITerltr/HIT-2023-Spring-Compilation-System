#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
// 行数
extern int yy_lineno;

// 文本
extern char* yy_text;

// 错误处理
extern int Has_Fault;

// bison是否有词法或者语法错误
int yy_error(char *msg);


// 抽象逻辑语法分析树
struct TreeNode{
    int line;   // 行数
    
    char* Token;// Token类型
    
    int Is_leaf; // 为叶节点 即为终结符
    // 联合体，其中同一时间内只能保存一个成员的值，分配空间是=为最大类型的内存其大小
    union{
        // ID内容，即TYPE类型
        char* Id_Type;  // = int/float
        // 具体的数值
        int intVal;  // INT
        float floatVal;  // FLOAT
    };

    // 其中first_child为第一个孩子节点，next_brother为兄弟节点，即使用孩子兄弟表示法：用二叉树来表示多叉树
    struct TreeNode *first_child,*next_brother;

};
typedef struct TreeNode* P_Node;

//语法生成式为空的节点
static P_Node Empty_Node()
{
    P_Node null = (P_Node)malloc(sizeof(struct TreeNode)); //分配空间给空节点
    null->Token = NULL;
    return null;
}

//建立新的节点
static P_Node New_TreeNode(int line, char* TOKEN, int amount, ...)
    {
    if(Has_Fault) return NULL; // 存在错误，退出，不建立节点
    P_Node root = (P_Node)malloc(sizeof(struct TreeNode)); //分配空间给根节点
    P_Node child = (P_Node)malloc(sizeof(struct TreeNode)); //分配空间给孩子节点
    if (!root){
        yyerror("Create TreeNode Error");
        exit(0);
    }
    root->line = line;
    root->Token = TOKEN;
    root->isleaf = FALSE;
    if (amount == 0){
        //表示当前节点为终结符（叶节点）
        root->Is_leaf = TRUE;
        if ((!strcmp(TOKEN, "ID"))||(!strcmp(TOKEN, "TYPE"))){ // strcmp()==0表示相同
            char *str;
            str = (char *)malloc(sizeof(char) * 40);
            strcpy(str, yytext);
            root->Id_Type = str;
        }
        else if(!strcmp(TOKEN, "INT")){
            root->intVal = atoi(yytext);
        }
        else if(!strcmp(TOKEN, "FLOAT")){
            root->floatVal = atof(yytext);
        }
    }
    else if(amount > 0)
    {
        // 设置参数列表
        va_list list;
        // 初始化参数列表
        va_start(list, amount);
        //第一个孩子节点
        child = va_arg(list,P_Node);
        root->first_child = child;
        if (amount >= 2){
            // 谁明存在两个以上的子节点，即第一个孩子节点有兄弟节点
            for (int i = 0; i < (amount - 1); i++){
                child->next_brother = va_arg(list,P_Node);
                child = child->next_brother;
            }
        }
        va_end(list);
    }
    return root;
}
//递归遍历语法分析树, 语法分析树的高度Height从0开始
static void Traverse_Print(P_Node tree, int Height)
{
    if (tree != NULL && tree->Token != NULL)
    {
        printf("%*s", 2 * Height, ""); // 注意先缩进两个空格
        printf("%s", tree->Token);  // 其次打印其名称
        if ((!strcmp(tree->Token, "ID"))||(!strcmp(tree->Token, "TYPE")))
        {
            printf(": %s", tree->Id_Type);
        }
        else if(!strcmp(tree->Token, "INT"))
        {
            printf(": %d", tree->intVal);
        }
        else if(!strcmp(tree->Token, "FLOAT"))
        {
            printf(": %f", tree->floatVal);
        }
        else if (!tree->Is_leaf) // 为非终结符
        {
            printf(" (%d)", tree->line);
        }
        printf("\n");
        Traverse_Print(tree->first_child, Height + 1);
        Traverse_Print(tree->next_brother, Height);
    }
}

#endif