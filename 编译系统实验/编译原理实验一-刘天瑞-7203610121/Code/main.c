#include <stdlib.h>
#include <stdio.h>
#include "TreeNode.h"
extern FILE* yyin;
extern P_Node root;
void yyrestart (FILE *input_file);
int yyparse(void);
int hasFault = FALSE;

int main(int a, char** b)
{
    if (a <= 1) return 1;
    FILE* f = fopen(b[1], "r");
    if (!f){
        perror(b[1]);  //将一个描述性错误消息输出到标准错误stderr中
        return 1;
    }
    yyrestart(f); //初始化输入文件指针yyin
    yyparse(); //开始进行语法分析
    if (!hasFault){
        Traverse_Print(root, 0);
    }
    return 0;
}

/*
int main(int a, char** b){
    if (a > 1)
    {
        if (!(yyin=fopen(b[1], "r"))){
            perror(b[1]); //将一个描述性错误消息输出到标准错误stderr中
            return 1;
        }
    }
    while (yylex() != 0);
    return 0;
}
*/


