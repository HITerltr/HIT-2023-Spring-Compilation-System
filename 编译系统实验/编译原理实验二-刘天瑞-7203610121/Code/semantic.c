#include"semantic.h"
#include<string.h>
//Using pointer arrays can reduce the use of memory space

struct TABLE* table[16384];//Storage structure or variable
struct FUNCTION* function[16384];//Store function definitions or declarations
int struct_without_name = 0;

void count_table_number()
{
    int a = 0;
    for(int i = 0;i < 16384;i++) 
    if(table[i] != NULL) 
    a++;
}

//Find if the name 'name' appears in the table, and return its TABLE value if it does
struct TABLE* find_struct_in_table(char* name)
{
    unsigned int val = generate_hash(name);
    if(table[val] == NULL) 
    return NULL;
    else{
        struct TABLE* now = table[val];
        while(now!=NULL)
        {
            if(strcmp(now->field->name,name)==0) 
            return now;
            now = now->next_for_openhash;
        }
    }
    return NULL;
}
//Only judge based on Name
struct FUNCTION* find_in_function(char* name)
{
    unsigned int val = generate_hash(name);
    if(function[val] == NULL) 
    return NULL;
    else{
        struct FUNCTION* now = function[val];
        while(now != NULL){
            if(strcmp(now->name,name) == 0) 
            return now;
            now = now->next_for_openhash;
        }
    }
    return NULL;
}

struct FUNCTION* add_to_function(struct FUNCTION* func)
{
    unsigned int val = generate_hash(func->name);
    if(function[val] == NULL) function[val] = func;
    else{
        struct FUNCTION* rem = function[val];
        while(rem->next_for_openhash != NULL)
        {
            rem = rem->next_for_openhash;
        }
        rem->next_for_openhash = func;
    }
}
//Based on all parameters, 0 represents the same, 1 represents the different
//Only determine parameter types
int conflict_between_functions(struct FUNCTION* funca,struct FUNCTION* funcb)
{
    if(strcmp(funca->name,funcb->name) != 0) 
    return 1;
    if(fieldcmp(funca->field,funcb->field) != 0) 
    return 1;
    if(typecmp(funca->return_type,funcb->return_type) != 0) 
    return 1;
    return 0;
}
int fieldcmp(FieldList a,FieldList b)
{
    if(a == NULL&&b == NULL) 
    return 0;
    if(a == NULL||b == NULL) 
    return 1;
    if(strcmp(a->name,b->name) != 0) 
    return 1;
    if(typecmp(a->type,b->type) != 0) 
    return 1;
    if(fieldcmp(a->tail,b->tail) != 0) 
    return 1;
    return 0;
}
int typecmp(Type a,Type b)
{
    if(a == NULL&&b == NULL) 
    return 0;
    if(a == NULL||b == NULL) 
    return 1;
    if(a->kind == BASIC&&b->kind == BASIC)
    {
        if(a->u.basic == b->u.basic) 
        return 0;
        else 
        return 1;
    }
    else if(a->kind == ARRAY&&b->kind == ARRAY) 
    return typecmp(a->u.array.elem,b->u.array.elem);
    else if(a->kind == STRUCTURE&&b->kind == STRUCTURE) 
    return fieldcmp(a->u.structure,b->u.structure);
    else 
    return 1;
}
int fieldcmp_forfunc(FieldList a,FieldList b)
{
    if(a == NULL&&b == NULL) 
    return 0;
    if(a == NULL||b == NULL) 
    return 1;
    if(typecmp(a->type,b->type) != 0) 
    return 1;
    if(fieldcmp_forfunc(a->tail,b->tail) != 0) 
    return 1;
    return 0;
}

void add_to_table(FieldList fiel,int line,int is_def)
{
    int val = generate_hash(fiel->name);
    if(table[val] == NULL)
    {
        table[val] = (struct TABLE*)malloc(sizeof(struct TABLE));
        table[val]->field = fiel;
        table[val]->is_def_struct = is_def;
        table[val]->next_for_openhash = NULL;
        table[val]->linenumber = line;
    }
    else{
        struct TABLE* new_table = (struct TABLE*)malloc(sizeof(struct TABLE));
        new_table->field = fiel;
        new_table->linenumber = line;
        new_table->is_def_struct = is_def;
        new_table->next_for_openhash = NULL;
        struct TABLE* rem = table[val];
        while(rem->next_for_openhash != NULL)
        {
            rem = rem->next_for_openhash;
        }
        rem->next_for_openhash = new_table;
    }
}

unsigned int generate_hash(char* name)
{
    unsigned int val = 0,i;
    for(;*name;++name)
    {
        val=(val<<2) + *name;
        if(i = val*~0x3fff) val = (val^(i>>12))&0x3fff;
    }
    return val;
}
//Yes indicates found, NULL indicates not found
Type find_domain_in_struct(Type type,struct TreeNode* now)
{
    FieldList temp_field = type->u.structure;
    while(temp_field != NULL)
    {
        if(strcmp(now->char_name,temp_field->name) == 0) 
        return temp_field->type;
        temp_field = temp_field->tail;
    }
    return NULL;
}
int find_param_in_function(struct FUNCTION* func,struct TreeNode* now)
{
    FieldList temp_field = func->field;
    if(now == NULL)
    {
        if(temp_field != NULL) 
        return 1;
        else 
        return 0;
    }
    else
    {
        FieldList arg_field = Args(now);
        if(fieldcmp_forfunc(temp_field,arg_field) == 0) 
        return 0;
        else 
        return 1;
    }
}

void Program(struct TreeNode* now)
{
    for(int i = 0;i < 16384;i++)
    {
        table[i] = NULL;
        function[i] = NULL;
    }
    struct TreeNode* extdeflist = now->child;
    while(extdeflist->child != NULL)
    {
       struct TreeNode* extdef = extdeflist->child;
       ExtDef(extdef);
       extdeflist = extdef->brother;
    }
}

void ExtDef(struct TreeNode* now)
{
    /*
    ExtDef → Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    | Specifier FunDec SEMI //add for 2.1
    */
   struct TreeNode* specifier = now->child;
   Type specifier_type = Specifier(specifier);

   struct TreeNode* fir_bro = specifier->brother;
   struct TreeNode* sec_bro = fir_bro->brother;
   if(sec_bro == NULL)
   {
        return;
   }
   else if(strcmp(fir_bro->name,"ExtDecList\0") == 0)
   {
       //Specifier ExtDecList SEMI
       //int a;struct complex a;
       //Need to associate extdeclist with type and place it in the symbol table
       //Whether the name of the variable used
       ExtDecList(fir_bro,specifier_type);
   }
   else if(strcmp(sec_bro->name,"CompSt\0") == 0)
   {
       //Specifier FunDec CompSt
       //Function definition requires putting function correlation into the function table
       FunDec(fir_bro,specifier_type,1);
       //Passing the return type for the judgment of the return statement
       CompSt(sec_bro,specifier_type);
   }
   else{
       //Specifier FunDec SEMI
       //Function declaration, placing in function table
       FunDec(fir_bro,specifier_type,0);
   }
}

Type Specifier(struct TreeNode* now)
{
    //Specifier → TYPE| StructSpecifier
    struct TreeNode* child = now->child;
    if(strcmp(child->name,"TYPE\0") == 0)
    {
        Type return_type = (Type)malloc(sizeof(struct Type_));
        return_type->kind = BASIC;
        if(strcmp(child->char_name,"int") == 0) return_type->u.basic = 0;
        else return_type->u.basic = 1;
        return return_type;
    }
    else{
        Type return_type = StructSpecifier(child);
        return return_type;
    }
}

Type StructSpecifier(struct TreeNode* now)
{
    //StructSpecifier → STRUCT OptTag LC DefList RC| STRUCT Tag
   Type return_type = (Type)malloc(sizeof(struct Type_));
   return_type->kind = STRUCTURE;
   struct TreeNode* struct_s = now->child;
   struct TreeNode* fir_bro = struct_s->brother;
   struct TreeNode* sec_bro = fir_bro->brother;
   if(sec_bro == NULL)
   {
       //Tag → ID
       struct TABLE* find_struct = find_struct_in_table(fir_bro->child->char_name);
       if(find_struct == NULL||find_struct->field->type->kind != STRUCTURE)
       {
           printf("Error type 17 at Line %d: Undefined structure \"%s\".\n",now->linenumber,fir_bro->child->char_name);
           return NULL;
       }
       return_type = find_struct->field->type;
       return return_type;
   }
   else
   {
       //OptTag → ID|
       FieldList struct_field = (FieldList)malloc(sizeof(struct FieldList_));
       struct TreeNode* opttag = fir_bro;
       struct TreeNode* deflist = opttag->brother->brother;
       //Handling opttags
       if(opttag->child == NULL)
       {
           struct_without_name++;
           char name[200] = "struct_without_name\0";
           for(int i = 0;i < struct_without_name;i++) strcat(name,"a\0");
           struct_field->name = name;
       }
       else
       {
           //Determine if there is a duplicate error16
            struct TABLE* find_struct = find_struct_in_table(opttag->child->char_name);
            if(find_struct != NULL)
            {
                printf("Error type 16 at Line %d: Duplicated name \"%s\".\n",opttag->linenumber,opttag->child->char_name);
                return NULL;
            }
            struct_field->name = opttag->child->char_name;
       }
       //Handling deflist
       return_type->u.structure = DefList(deflist,0);
       //Place the struct itself in the symbol table, and the fields of the struct should also be placed in the symbol table
       struct_field->type = return_type;
       struct_field->tail = NULL;
       add_to_table(struct_field,struct_s->linenumber,0);
   }
   return return_type;
}

FieldList DefList(struct TreeNode* now,int judge)
{
    //DefList → Def DefList|
    struct TreeNode* newdef = now->child;
    FieldList head = NULL;
    FieldList nownode = NULL;
    while(newdef != NULL)
    {
        FieldList after = Def(newdef,judge);
        if(head == NULL) 
        {
            head = after;
            nownode = after;
        }
        else 
        {
            nownode->tail = after;
            nownode = after;
        }
        if(nownode == NULL) 
        break;
        while(nownode->tail != NULL) nownode = nownode->tail;
        newdef = newdef->brother->child;
    }
    return head;  
}

FieldList Def(struct TreeNode* now,int judge)
{
    //Def → Specifier DecList SEMI
    Type specifier_type = Specifier(now->child);
    struct TreeNode* declist = now->child->brother;
    FieldList return_field = NULL;
    return_field = DecList(declist,specifier_type,judge);
    return return_field;
}

FieldList DecList(struct TreeNode* now,Type type,int judge)
{
    //DecList → Dec| Dec COMMA DecList
    struct TreeNode* dec = now->child;
    struct TreeNode* fir_bro = dec->brother;
    if(fir_bro == NULL)
    {
        FieldList return_field = NULL;
        return_field = Dec(dec,type,judge);
        return return_field;
    }
    else
    {
        FieldList return_field = NULL;
        return_field = Dec(dec,type,judge);
        if(return_field != NULL) return_field->tail = DecList(dec->brother->brother,type,judge);
        return return_field; 
    }
}

FieldList Dec(struct TreeNode* now,Type type,int judge)
{
    //Dec → VarDec| VarDec ASSIGNOP Exp
    struct TreeNode* vardec = now->child;
    struct TreeNode* fir_bro = vardec->brother;
    if(fir_bro == NULL)
    {
        FieldList return_field = NULL;
        return_field = VarDec(vardec,type,judge);
        return return_field;
    }
    else{
        if(judge == 0)
        {
            printf("Error type 15 at Line %d: Initialize domain in structure.\n",vardec->linenumber);
            return NULL;
        }
        else{
            Type exp_type = Exp(fir_bro->brother);
            if(typecmp(type,exp_type) == 0)
            { 
                FieldList return_field = NULL;
                return_field = VarDec(vardec,type,judge);
                return return_field;
            }
            else{
                printf("Error type 5 at Line %d: Type mismatched for assignment.\n",now->linenumber);
                return NULL;
            }
        }
    }
}

FieldList VarDec(struct TreeNode* now,Type type,int judge)
{
    //VarDec → ID| VarDec LB INT RB
    //Add a symbol table to vardec, there is no need to add a symbol table when coming from a function
    //Symbols from function definitions need to be added to the symbol table, while symbols from function declarations do not need to be added to the symbol table
    struct TreeNode* child = now->child;
    struct TreeNode* fir_bro = child->brother;
    if(fir_bro == NULL)
    {
        FieldList vardec_field = (FieldList)malloc(sizeof(struct FieldList_));
        vardec_field->name = child->char_name;
        vardec_field->type = type;
        vardec_field->tail = NULL;
        if(judge == 3) 
        return vardec_field;
        struct TABLE* find_struct = find_struct_in_table(vardec_field->name);
        if(judge == 0&&find_struct != NULL)
        {
            printf("Error type 15 at Line %d: Redefined field \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        }
        else if(judge == 1&&find_struct != NULL)
        {
            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        }
        else if(judge == 2&&find_struct != NULL)
        {
            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        }
        add_to_table(vardec_field,child->linenumber,1);
        return vardec_field;
    }
    else
    {
        struct TreeNode* int_num = fir_bro->brother;
        Type vardec_type = (Type)malloc(sizeof(struct Type_));
        vardec_type->kind = ARRAY;
        vardec_type->u.array.size = int_num->int_number;
        vardec_type->u.array.elem = type;
        FieldList find_upper = VarDec(child,vardec_type,judge);
        return find_upper;
    }
}

void ExtDecList(struct TreeNode* now,Type type)
{
    //ExtDecList → VarDec| VarDec COMMA ExtDecList
    //There is only one possibility for extdeclist, simply pass 1 to vardec here
    //printf("aExtDecList\n");
    struct TreeNode* vardec = now->child;
    struct TreeNode* fir_bro = vardec->brother;
    if(fir_bro == NULL)
    {
        VarDec(vardec,type,1);
    }
    else
    {
        VarDec(vardec,type,1);
        ExtDecList(fir_bro->brother,type);
    }
}

void FunDec(struct TreeNode* now,Type type,int judge)
{
    //FunDec → ID LP VarList RP| ID LP RP
    //Conflict between definitions error4
    //1. Create a new Function 2. Compare 3. Error or add
    //struct FUNCTION* find_func=find_in_function(now->child->char_name);
    //printf("aFunDec\n");
    //Variables in function declarations are not added to the variable table
    //Only determine the type
    struct FUNCTION* func = (struct FUNCTION*)malloc(sizeof(struct FUNCTION));
    func->name = now->child->char_name;
    func->field = NULL;
    func->return_type = type;
    func->declaration = 0;
    func->definition = 0;
    func->linenumber = now->linenumber;
    func->next_for_openhash = NULL;
    if(now->child->brother->brother->brother == NULL);
    else
    {
        func->field = VarList(now->child->brother->brother,judge);
    }
    struct FUNCTION* find_func = find_in_function(func->name);
    if(judge == 0)
    {
        if(find_func == NULL)
        {
            func->declaration++;
            add_to_function(func);
        }
        else
        {
            //Declaration conflict or multiple declarations
            int is_conflict = conflict_between_functions(find_func,func);
            if(is_conflict == 0) find_func->declaration++;
            else
            {
                return;
            } 
        }
    }
    else
    {
        if(find_func == NULL)
        {
            func->definition++;
            add_to_function(func);
        }
        else
        {
            //Conflicting definitions
            int is_conflict = conflict_between_functions(find_func,func);
            if(is_conflict == 0)
            {
                //If the find is found_ Func is consistent with the current Func, which means it is defined repeatedly or for the first time
                if(func->definition != 0)
                {
                    printf("Error type 4 at Line %d: Redefined function \"%s\".\n",now->linenumber,func->name);
                    return;
                }
                else find_func->definition++;
            }
            else
            {
                //If the find is found_ Func is not consistent with the current Func. If defined, it can be attributed to error4, and if not defined, it can be attributed to error19
                if(find_func->definition == 0)
                {
                    return;
                    }
                else
                {
                    printf("Error type 4 at Line %d: Redefined function \"%s\".\n",now->linenumber,func->name);
                    return;
                }
            } 
        }
    }
}

FieldList VarList(struct TreeNode* now,int judge)
{
    //VarList → ParamDec COMMA VarList| ParamDec
    //Similar to DecList
    struct TreeNode* paramdec = now->child;
    struct TreeNode* fir_bro = paramdec->brother;
    if(fir_bro == NULL)
    {
        FieldList varlist_field = NULL;
        varlist_field = ParamDec(paramdec,judge);
        return varlist_field;
    }
    else
    {
        FieldList varlist_field = NULL;
        varlist_field = ParamDec(paramdec,judge);
        if(varlist_field != NULL) varlist_field->tail = VarList(fir_bro->brother,judge);
        return varlist_field; 
    }
}

FieldList ParamDec(struct TreeNode* now,int judge)
{
    //ParamDec → Specifier VarDec
    Type specifier_type = Specifier(now->child);
    if(judge == 0) 
    return VarDec(now->child->brother,specifier_type,3);
    else 
    return VarDec(now->child->brother,specifier_type,2);
}

void CompSt(struct TreeNode* now,Type type)
{
    //CompSt → LC DefList StmtList RC
    struct TreeNode* deflist = now->child->brother;
    struct TreeNode* stmtlist = deflist->brother;
    DefList(deflist,1);
    StmtList(stmtlist,type);
}

void StmtList(struct TreeNode* now,Type type)
{
    //StmtList → Stmt StmtList|
    struct TreeNode* child = now->child;
    while(child != NULL)
    {
        Stmt(child,type);
        child = child->brother->child;
    }
}

void Stmt(struct TreeNode* now,Type type)
{
    struct TreeNode* child = now->child;
    //printf("aStmt\n");
    if(strcmp(child->name,"Exp\0") == 0)
    {
        //Stmt → Exp SEMI
        Exp(now->child);
    }
    else if(strcmp(child->name,"CompSt\0") == 0)
    {
        //Stmt →CompSt
        CompSt(now->child,type);
    }
    else if(strcmp(child->name,"RETURN\0") == 0)
    {
        //Stmt →RETURN Exp SEMI
        Type exp_type = Exp(child->brother);
        if(typecmp(exp_type,type) == 0) 
        return;
        else
        {
            printf("Error type 8 at Line %d: Type mismatched for return.\n",now->linenumber);
            return;
        }
    }
    else if(strcmp(child->name,"IF\0") == 0)
    {
        //Stmt →IF LP Exp RP Stmt|IF LP Exp RP Stmt ELSE Stmt
        struct TreeNode* exp_in_if = child->brother->brother;
        Type exp_type = Exp(exp_in_if);
        if(exp_type == NULL) 
        return;
        if(exp_type->kind == BASIC&&exp_type->u.basic == 0);
        else{
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",exp_in_if->linenumber);
            return;
        }
        struct TreeNode* else_node = child->brother->brother->brother->brother->brother;
        if(else_node == NULL)
        {
            Stmt(exp_in_if->brother->brother,type);
        }
        else
        {
            Stmt(exp_in_if->brother->brother,type);
            Stmt(else_node->brother,type);
        }
    }
    else if(strcmp(child->name,"WHILE\0") == 0)
    {
        //Stmt →WHILE LP Exp RP Stmt
        struct TreeNode* exp_in_while = child->brother->brother;
        Type exp_type = Exp(exp_in_while);
        if(exp_type == NULL) 
        return;
        if(exp_type->kind == BASIC&&exp_type->u.basic == 0);
        else
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",exp_in_while->linenumber);
            return;
        }
        Stmt(exp_in_while->brother->brother,type);
    }   
}

Type Exp(struct TreeNode* now)
{
    struct TreeNode* child = now->child;
    struct TreeNode* fir_bro = child->brother;
    if(fir_bro == NULL)
    {
        if(strcmp(child->name,"INT\0") == 0)
        {
            //Exp → INT
            Type return_type = (Type)malloc(sizeof(struct Type_));
            return_type->kind = BASIC;
            return_type->u.basic = 0;
            return return_type;
        }
        else if(strcmp(child->name,"FLOAT\0") == 0)
        {
            //Exp → FLOAT
            Type return_type = (Type)malloc(sizeof(struct Type_));
            return_type->kind = BASIC;
            return_type->u.basic = 1;
            return return_type;
        }
        else if(strcmp(child->name,"ID\0") == 0)
        {
            //Exp → ID
            struct TABLE* find_id = find_struct_in_table(child->char_name);
            if(find_id == NULL)
            {
                printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",now->linenumber,child->char_name);
                return NULL;
            }
            else
            {
                if(find_id->is_def_struct == 0)
                {
                    printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",now->linenumber,child->char_name);
                    return NULL;
                }
                //If this id is found, then return the type of this table
                return find_id->field->type;
            }
        }
    }
    struct TreeNode* sec_bro = fir_bro->brother;
    if(sec_bro == NULL)
    {
        if(strcmp(child->name,"MINUS\0") == 0)
        {
            //Exp → MINUS Exp
            Type return_type=Exp(fir_bro);
            return return_type;
        }
        else if(strcmp(child->name,"NOT\0") == 0)
        {
            //Exp →NOT Exp
            Type return_type = Exp(fir_bro);
            if(return_type == NULL) 
            return NULL;
            if(return_type->kind == BASIC&&return_type->u.basic == 0) 
            return return_type;
            else
            {
                printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
                return NULL;
            }
        }
    }
    if(strcmp(fir_bro->name,"ASSIGNOP\0") == 0)
    {
        //Exp → Exp ASSIGNOP Exp
        //For lvalues, it was found that only vardec and exp are useful for assigning op, while vardec can guarantee lvalues
        //child->ID、Exp LB Exp RB以及Exp DOT ID
        //printf("aExp → Exp ASSIGNOP Exp\n");
        Type left_type = Exp(child);
        struct TreeNode* child_child = child->child;
        if(child_child == NULL) 
        return NULL;
        else if(strcmp(child_child->name,"ID\0") == 0&&child_child->brother == NULL);
        else if(strcmp(child_child->name,"Exp\0") == 0&&strcmp(child_child->brother->name,"LB\0") == 0);
        else if(strcmp(child_child->name,"Exp\0") == 0&&strcmp(child_child->brother->name,"DOT\0") == 0);
        else
        {
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",now->linenumber);
            return NULL;
        }
        Type right_type = Exp(fir_bro->brother);
        if(typecmp(left_type,right_type) == 0) 
        return right_type;
        else 
        {
            if(left_type == NULL||right_type == NULL)
            {
                return NULL;
            }
            printf("Error type 5 at Line %d: Type mismatched for assignment.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"AND\0") == 0)
    {
        //Exp → Exp AND Exp
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(left_type == NULL&&right_type == NULL) 
        return NULL;
        if(typecmp(left_type,right_type) == 0&&left_type->kind == BASIC&&left_type->u.basic == 0) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"OR\0") == 0)
    {
        //Exp → Exp OR Exp
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(left_type == NULL&&right_type == NULL) 
        return NULL;
        if(typecmp(left_type,right_type) == 0&&left_type->kind == BASIC&&left_type->u.basic == 0) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"RELOP\0") == 0)
    {
        //Exp → Exp RELOP Exp
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(left_type == NULL||right_type == NULL) 
        return NULL;
        if(typecmp(left_type,right_type) == 0) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"PLUS\0") == 0)
    {
        //Exp → Exp PLUS Exp
        //Arithmetic operation
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(typecmp(left_type,right_type) == 0&&left_type != NULL&&left_type->kind == BASIC) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"MINUS\0") == 0)
    {
        //Exp → Exp MINUS Exp
        //Arithmetic operation
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(typecmp(left_type,right_type) == 0&&left_type != NULL&&left_type->kind == BASIC) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"STAR\0") == 0)
    {
        //Exp → Exp STAR Exp
        //Arithmetic operation
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(typecmp(left_type,right_type) == 0&&left_type != NULL&&left_type->kind == BASIC) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"DIV\0") == 0)
    {
        //Exp → Exp DIV Exp
        //Arithmetic operation
        Type left_type = Exp(child);
        Type right_type = Exp(fir_bro->brother);
        if(typecmp(left_type,right_type) == 0&&left_type->kind == BASIC) 
        return right_type;
        else 
        {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"DOT\0") == 0)
    {
        //Exp → Exp DOT ID
        Type return_type = Exp(child);
        if(return_type == NULL) 
        return NULL;
        if(return_type->kind == STRUCTURE);
        else 
        {
            printf("Error type 13 at Line %d: Illegal use of \".\".\n",now->linenumber);
            return NULL;
        }
        Type has_domain = find_domain_in_struct(return_type,fir_bro->brother);
        if(has_domain == NULL)
        {
            printf("Error type 14 at Line %d: Non-existent field \"%s\".\n",now->linenumber,fir_bro->brother->char_name);
            return NULL;
        }
        return has_domain;
    }
    if(strcmp(fir_bro->name,"LB\0") == 0)
    {
        //Exp → Exp LB Exp RB
        Type return_type = Exp(child);
        if(return_type == NULL) 
        return NULL;
        if(return_type->kind == ARRAY);
        else 
        {
            printf("Error type 10 at Line %d: \"i\" is not a array.\n",child->linenumber);
            return NULL;
        }
        Type int_type = Exp(child->brother->brother);
        if(int_type == NULL) 
        return NULL;
        if(int_type->kind == BASIC&&int_type->u.basic == 0)
        {
            return return_type->u.array.elem;
        }
        else
        {
            printf("Error type 12 at Line %d: \"%f\" is not an integer.\n",child->linenumber,child->brother->brother->child->float_number);
            return NULL;
        }
    }
    if(strcmp(fir_bro->name,"Exp\0") == 0)
    {
        //Exp → LP Exp RP
        Type return_type = Exp(fir_bro);
        return return_type;
    }
    if(strcmp(sec_bro->name,"Args\0") == 0)
    {
        //Exp → ID LP Args RP
        struct TABLE* id_table = find_struct_in_table(child->char_name);
        if(id_table != NULL)
        {
            printf("Error type 11 at Line %d: \"%s\" is not a function.\n",now->linenumber,child->char_name);
            return NULL;
        }
        struct FUNCTION* id_function = find_in_function(child->char_name);
        if(id_function == NULL||id_function->definition == 0)
        {
            printf("Error type 2 at Line %d: Undefined function \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        }
        int judge = find_param_in_function(id_function,sec_bro);
        if(judge == 0) 
        return id_function->return_type;
        else 
        {
            printf("Error type 9 at Line %d: Function \"%s(%s)\" is not applicable for arguments \"(%s, %s)\".\n",now->linenumber,id_function->name,child->brother->brother->name,child->brother->brother->name,child->brother->brother->name);
            return NULL;
        }
    }
    if(strcmp(sec_bro->name,"RP\0") == 0)
    {
        //Exp → ID LP RP
        struct TABLE* id_table = find_struct_in_table(child->char_name);
        if(id_table != NULL)
        {
            printf("Error type 11 at Line %d: \"%s\" is not a function.\n",now->linenumber,child->char_name);
            return NULL;
        }
        struct FUNCTION* id_function = find_in_function(child->char_name);
        if(id_function == NULL||id_function->definition == 0)
        {
            printf("Error type 2 at Line %d: Undefined function \"%s\".\n",child->linenumber,child->char_name);
            return NULL;
        }
        int judge = find_param_in_function(id_function,NULL);
        if(judge == 0) 
        return id_function->return_type;
        else {
            printf("Error type 9 at Line %d: Function \"%s()\" is not applicable for arguments \"()\".\n",now->linenumber,id_function->name);
            return NULL;
        }
    }
}

FieldList Args(struct TreeNode* now)
{
    //Args → Exp COMMA Args| Exp
    struct TreeNode* child = now->child;
    struct TreeNode* fir_bro = child->brother;
    if(fir_bro == NULL)
    {
        FieldList exp_field = (FieldList)malloc(sizeof(struct FieldList_));
        exp_field->type = Exp(child);
        return exp_field;
    }
    else
    {
        FieldList exp_field = (FieldList)malloc(sizeof(struct FieldList_));
        exp_field->type = Exp(child);
        exp_field->tail = Args(fir_bro->brother);
        return exp_field; 
    }
}
