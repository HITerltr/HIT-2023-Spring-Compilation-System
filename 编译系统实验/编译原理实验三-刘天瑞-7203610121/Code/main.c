#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "main.h"
#include "syntax.tab.h"
int globalID = 1;//  统一用一个整数x代表临时变量tx，为了随意分配临时变量，定义全局变量再++
int globallabel = 1;//  统一用一个整数x代表标号labelx，为了随意分配标号，定义全局变量再++
char* Xids[100]; //  变量名
int idnumber[100];//  变量的临时编号（对于数组表示其地址）
int idpointer = 0;
extern node* syntax_tree;
extern int yyparse();
extern void yyrestart(FILE*);
extern int yylineno;
FILE* FileOutPut = NULL;
 
/*将可能为临时变量或者常量的编号翻译为字符串，翻译的方法如下：
  将整常数都取负，如果表达式对应的整数x<=0，说明其值是一个为-x的整常数，否则为一个tx的临时变量。
  由于中间代码常数表示为#1代表常数1，临时变量表示为t1。
  使用stdio.h库中的sprintf函数直接将字符串输入数组变量里面。
  使用格式为sprintf(char* buffer, "格式", 数值)*/
char* ID_cons_translate(int x ,int a)
{ 
    static char str[3][30];
    if(x <= 0)
        sprintf(str[a],"#%d",-x);//  常数
    else
        sprintf(str[a],"t%d",x);//  临时变量编号
    return str[a];
}

//  在变量表里查变量编号
int ID_finder(char* str)
{    
    for(int i = 0; i < idpointer; i++)
        if(strcmp(str,Xids[i]) == 0)//  直接进行字符串匹配
            return idnumber[i];
    return 0;
}

/*对于非条件的Exp生成计算代码并返回临时变量，返回值是一个int。
  如果是常数x，则返回-x（此时返回值<=0）。
  isl=1则表示左值。
  isl=1表示数组，返回的是数组元素地址。
  除非是处理赋值表达式的左值，否则大部分情况isl=0。*/
int Normal_Exp_Analysis(node* tree,int isl)
{
    switch(tree->subtype)
    {
    case 0:     //  Exp->ID，查找变量表返回编号
             return ID_finder(tree->child->str_val);
    case 1:     //  Exp->INT，返回整数值
             return -(tree->child->int_val);
    case 3:     //  Exp->LP EXP RP，套括号表达式，继续递归解析
             return Normal_Exp_Analysis(tree->child->next,0);
    case 4:     //  Exp->ID LP RP
    case 5:{    //  Exp->ID LP Args RP，函数调用
        char*  Function_Name = tree->child->str_val;
        node* args = tree->child->next->next;
        static int arglist[30];
        int ptree = 0;
        if(!args->isTerminal)
        { //  args非空
            //  Args → Exp COMMA Args | Exp
            while(1)
            {//  直接硬循环，剥离Exp，得到的参数传入各个表达式
                node* EXP = args->child;
                arglist[ptree++] = Normal_Exp_Analysis(EXP,0);
                if(args->subtype == 0)  //  Args->Exp
                    break;
                args = args->child->next->next;//  Args → Exp COMMA Args
            }
        }
        //  特殊处理输入输出函数read()/write(x)
        if(strcmp( Function_Name,"read") == 0)
        {
            int ret = globalID++;
            fprintf(FileOutPut,"READ t%d\n",ret);//  使用fprintf函数，作用是直接输出到文件中
            return ret;
        }
        else if(strcmp( Function_Name,"write") == 0)
        {
            fprintf(FileOutPut,"WRITE %s\n",ID_cons_translate(arglist[0],0));
            return 0;   //  write不参与运算
        }
        for(int i = ptree - 1; i >= 0; i--)//  倒向传入参数
            fprintf(FileOutPut,"ARG %s\n",ID_cons_translate(arglist[i],0));
        int ret=globalID++;//  存入返回值的临时变量ID
        fprintf(FileOutPut,"t%d := CALL %s\n",ret, Function_Name);
        return ret;
    }
    case 6:{    
        /*Exp->Exp LB Exp RB 访问一维int数组变量元素部分
          根据名字在变量表中查出来的位置计算地址，“基地址+下标*4” */

        char* name = tree->child->child->str_val;//  变量名，第一个Exp一定是Exp->ID
        int base_addr = ID_finder(name);//  数组基地址变量编号
        int addr = globalID++;//  计算元素地址的临时变量
        int index = Normal_Exp_Analysis(tree->child->next->next,0);//  数组下标
        fprintf(FileOutPut,"t%d := %s * #4\n",addr,ID_cons_translate(index,0));//  限定类型一定是int
        fprintf(FileOutPut,"t%d := t%d + t%d\n",addr,addr,base_addr);
        if(isl) return addr;//  数组元素为左值，取地址即可，没必要取值
        int ret = globalID++;
        fprintf(FileOutPut,"t%d := *t%d\n",ret,addr);//  否则，用在表达式中，取地址处值
        return ret;
    }
    case 8:{    //  Exp->MINUS Exp 负整数，减整数
        int re1 = Normal_Exp_Analysis(tree->child->next,0);
        int ret = globalID++;
        fprintf(FileOutPut,"t%d := #0 - %s\n",ret,ID_cons_translate(re1,0));
        return ret;
    }
    /*处理一般运算符，基础运算式子*/
    case 10:    //  Exp->Exp STAR Exp
    case 11:    //  Exp->Exp DIV Exp
    case 12:    //  Exp->Exp PLUS Exp
    case 13:{   //  Exp->Exp MINUS Exp
        char OPERATION=(tree->subtype == 10) ? '*' : (
                (tree->subtype == 11) ? '/' : (
                (tree->subtype == 12) ? '+' : '-'));
        int a = Normal_Exp_Analysis(tree->child,0);
        int b = Normal_Exp_Analysis(tree->child->next->next,0);
        int ret = globalID++;//  进行运算的临时变量赋值
        fprintf(FileOutPut,"t%d := %s %c %s\n",ret,ID_cons_translate(a,0),OPERATION,ID_cons_translate(b,1));
        return ret;
    }
    case 17:{   //  Exp->Exp ASSIGNOP Exp 赋值
        int r = Normal_Exp_Analysis(tree->child->next->next,0);
        int l = Normal_Exp_Analysis(tree->child,1);//  isl = 1，左边为数组则返回存地址的临时变量
        if(tree->child->subtype == 6)//  左边是数组，返回地址，解引用赋值
            fprintf(FileOutPut,"*t%d := %s\n",l,ID_cons_translate(r,0));
        else
            fprintf(FileOutPut,"t%d := %s\n",l,ID_cons_translate(r,0));
        return l;  
    }
    default:{
        printf("Error when calc exp\n");
        exit(-1);
    }
    }
}

/*处理if&while使用的条件表达式，若真则跳转到指定标签，
  保证条件表达式一定为Exp RELOP Exp或者普通Exp（判断非0）。在本次实验中，仅考虑一下两种：
  1. 普通表达式，直接用分析函数计算出值，然后 IF exp != #0 GOTO label；
  2. 形如A RELOP B的条件表达式，需要用分析函数解析A和B，然后显式的在条件跳转指令中指定RELOP。
  此函数用来解析条件表达式并产生条件转移指令*/
void Condition_Exp_Analysis(node* condexp,int true_label)
{
    if(condexp->subtype == 14)
    { //  Exp->Exp RELOP Exp
        int a = Normal_Exp_Analysis(condexp->child,0);
        int b = Normal_Exp_Analysis(condexp->child->next->next,0);
        char* rel;
        int relop = condexp->child->next->relop;
        switch(relop)
        {
        case RELOP_EQU: rel="=="; break;
        case RELOP_NEQ: rel="!="; break;
        case RELOP_GE:  rel=">="; break;
        case RELOP_LE:  rel="<="; break;
        case RELOP_GT:  rel=">";  break;
        case RELOP_LT:  rel="<";  break;
        }
        fprintf(FileOutPut,"IF %s %s %s GOTO label%d\n",ID_cons_translate(a,0),rel,ID_cons_translate(b,1),true_label);     
    }
    else{  //  普通Exp，先计算然后判断是否非0
        int Cond = Normal_Exp_Analysis(condexp,0);
        fprintf(FileOutPut,"IF %s != #0 GOTO label%d\n",ID_cons_translate(Cond,0),true_label);
    }
}

void compile(node* tree)
{
    //  对一般语法树生成中间代码
    if(tree->isTerminal)
        return;
    switch(tree->type)
    {

    /*函数定义的编译：
      以非递归方式把VarList中每个ParamDec剥离出来，它一定不是数组就是简单的参数，
      分配临时变量，用PARAM声明，插入变量表即可，随后递归解析函数体。*/
    case Unterm_ExtDef:
    {
        //  ExtDef → Specifier Funcdec CompSt
        //  这里仅处理函数定义，并且specifier一定为INT
        node* funcdec = tree->child->next;
        /*
            VarDec → ID
            Funcdec → ID LP VarList RP | ID LP RP
            VarList → ParamDec COMMA VarList | ParamDec
            ParamDec → Specifier VarDec
        */
        node* varlist = funcdec->child->next->next;
        fprintf(FileOutPut,"FUNCTION %s :\n",funcdec->child->str_val);
        if(!varlist->isTerminal)
        {   //  varlist不为空
            while(1)
            { //  VarList → ParamDec COMMA VarList | ParamDec，遍历所有ParamDec
                node* paramdec = varlist->child;
                int arg = globalID++;
                fprintf(FileOutPut,"PARAM t%d\n",arg);
                node* vardec = paramdec->child->next;
                Xids[idpointer] = vardec->child->str_val; //  假定数组不作为参数，只有ID
                idnumber[idpointer++] = arg; //  连同名字存入变量表
                if(varlist->subtype == 1)  //  VarList->ParamDec
                    break;
                varlist = varlist->child->next->next; //  VarList → ParamDec COMMA VarList
            }
        }
        node* compst = tree->child->next->next;
        compile(compst); //  递归解析函数体
        return;
    }
    /*变量定义的编译：
      因为没有全局变量，变量定义只会在CompSt的DefList里出现。*/
    case Unterm_CompSt:
    {
        //  CompSt → LC DefList StmtList RC
        /*
        StmtList → Stmt StmtList | e
        Stmt → Exp SEMI | CompSt | RETURN Exp SEMI | IF LP Exp RP Stmt 
            | IF LP Exp RP Stmt ELSE Stmt | WHILE LP Exp RP Stmt
        DefList → Def DefList | e
        Def → Specifier DecList SEMI
        DecList → Dec | Dec COMMA DecList
        Dec → VarDec | VarDec ASSIGNOP Exp
        VarDec → ID | VarDec LB INT RB
        */
        node* deflist = tree->child->next;
        node* stmtlist = tree->child->next;
        if(!deflist->isTerminal && deflist->type == Unterm_DefList)
        {
            stmtlist = stmtlist->next;
            //  处理deflist中的变量定义，所有变量定义都是这里处理的（没有全局变量）
            while(deflist != NULL)
            {     //  枚举DefList中的每一行Def
                node* def = deflist->child;
                node* declist = def->child->next;
                while(1)
                { //  枚举DecList中的每一个Dec（定义的单个变量）
                    node* dec = declist->child;
                    node* vardec = dec->child;
                    int var = globalID++;      //  新分配一个临时变量
                    if(vardec->subtype == 0)
                    {   //  VarDec->ID
                        Xids[idpointer] = vardec->child->str_val;
                        idnumber[idpointer++] = var;   
                        if(dec->subtype == 1)
                        {  //  Dec → VarDec ASSIGNOP Exp
                            //  处理赋初值表达式
                            int re = Normal_Exp_Analysis(dec->child->next->next,0);
                            fprintf(FileOutPut,"t%d := %s\n",var,ID_cons_translate(re,0));
                        }
                    }
                    else
                    {  //  VarDec->VarDec LB INT RB, 假定一定是一维数组
                        int size = vardec->child->next->next->int_val;
                        fprintf(FileOutPut,"DEC t%d %d\n",var,size * 4);//  分配空间
                        int addr = globalID++;
                        fprintf(FileOutPut,"t%d := &t%d\n",addr,var);
                        //  注意：var仅表示这个数组，而addr表示其首地址
                        //  以后var这个编号就没用了，用数组的时候直接用表示地址的临时变量addr
                        Xids[idpointer] = vardec->child->child->str_val; //  第一个VarDec一定是ID
                        idnumber[idpointer++] = addr;
                    }
                    if(declist->subtype == 0)   //  DecList->Dec
                        break;
                    declist = declist->child->next->next; //  DecList → Dec COMMA DecList
                }
                deflist = deflist->child->next;
            }
        }
        if(!stmtlist->isTerminal && stmtlist->type == Unterm_StmtList)
            compile(stmtlist);      //  直接递归处理stmtlist
        return;
    }
    /*控制及一般语句的编译*/
    case Unterm_Stmt:
    {
        /*
        Stmt → Exp SEMI | CompSt | RETURN Exp SEMI | IF LP Exp RP Stmt 
                | IF LP Exp RP Stmt ELSE Stmt | WHILE LP Exp RP Stmt
        */
        switch(tree->subtype)
        {
        case 0: //  Stmt->Exp SEMI
            Normal_Exp_Analysis(tree->child,0); 
            break;
        case 1: //  Stmt->CompSt
            compile(tree->child); 
            break;
        case 2:{//  Stmt->RETURN Exp SEMI
            int ret = Normal_Exp_Analysis(tree->child->next,0);
            fprintf(FileOutPut,"RETURN %s\n",ID_cons_translate(ret,0));
            break;
        }
        case 3: //  IF LP Exp RP Stmt
        case 4:{//  IF LP Exp RP Stmt ELSE Stmt
            //  保证Exp一定是ID或者Exp RELOP Exp这样的简单条件表达式。
            /*[计算条件表达式]
                    IF [条件为真] GOTO true_label
                    [else语句体]
                    GOTO end_label
                LABEL true_label:
                    [if语句体]
                LABEL end_label :*/
            int true_label = globallabel++;    //  True语句体入口
            int end_label = globallabel++;     //  if后续语句
            node* condexp = tree->child->next->next;
            Condition_Exp_Analysis(condexp,true_label);//  条件跳转
            //  如果有else，把else语句体放在前面，这样省跳转
            if(tree->subtype == 4)  //IF LP Exp RP Stmt ELSE Stmt
                compile(tree->child->next->next->next->next->next->next);   //  生成else的stmt代码
            fprintf(FileOutPut,"GOTO label%d\n",end_label);    //  无论是不是有else，条件不成立时必须跳过true语句块
            fprintf(FileOutPut,"LABEL label%d :\n",true_label);
            compile(tree->child->next->next->next->next);
            fprintf(FileOutPut,"LABEL label%d :\n",end_label);
            break;
        }
        case 5:{    //  WHILE LP Exp RP Stmt
            /*LABEL begin_label:
                 [ 计 算 条 件 表 达 式 ]
                 IF [ 条件为真 ] GOTO true_label
                 GOTO end_label
              LABEL true_label:
                 [ 循环体 ]
                 GOTO begin_label
              LABEL end_label :*/
            int begin_label = globallabel++;   //  循环入口
            int true_label = globallabel++;    //  循环体入口
            int end_label = globallabel++;     //  循环后续语句
            fprintf(FileOutPut,"LABEL label%d :\n",begin_label);
            node* condexp = tree->child->next->next;
            Condition_Exp_Analysis(condexp,true_label);
            fprintf(FileOutPut,"GOTO label%d\n",end_label);    //  结束循环
            fprintf(FileOutPut,"LABEL label%d :\n",true_label);
            compile(tree->child->next->next->next->next);
            fprintf(FileOutPut,"GOTO label%d\n",begin_label);
            fprintf(FileOutPut,"LABEL label%d :\n",end_label);
            break;
        }
        }
        return;
    }
    default:{   //  其它非终结符直接递归遍历
        for(node* ptree = tree->child; ptree != NULL; ptree = ptree->next)
            compile(ptree);
    }
    }
}

int main(int Argc,char** Argv)
{
    if(Argc < 3)
    {
        printf("Error: Too few args.\n");
        return -1;
    }
    syntax_tree = NULL;
    yylineno = 1;
    FILE* f = fopen(Argv[1],"r");
    if(f == NULL)
    {
        printf("Error: Cannot open file '%s'\n",Argv[1]);
        exit(-1);
    }
    yyrestart(f);
    yyparse();
    fclose(f);
    FileOutPut = fopen(Argv[2],"w");
    if(FileOutPut == NULL)
    {
        printf("Cannot open output file\n",Argv[2]);
        return -1;
    }

    compile(syntax_tree);
    fclose(FileOutPut);
    return 0;
}
