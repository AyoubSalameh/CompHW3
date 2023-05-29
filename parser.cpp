#include "parser.h"
#include "symbol.h"

#include <stdio.h>

extern table_stack table;
extern int yylineno;
using namespace std;



///******************************************FUNC DECL***************************************************

FuncDecl::FuncDecl(OverRide* override, RetType* rt, Node* id, Formals* params){

}

///******************************************FORMALS LIST***************************************************

FormalsList::FormalsList(FormalDecl* dec, FormalsList* list) : Node(dec->name){
    this->param_list.push_back(*dec);
    for( auto& item : list->param_list){
        this->param_list.push_back(item);
    }
}

FormalsList::FormalsList(FormalDecl *dec) : Node(dec->name) {
    this->param_list.push_back(*dec);
}

///******************************************EXP***************************************************

Exp::Exp(Exp *e1, Node *op, Exp *e2) : Node(op) {
    string type1 = e1->type;
    string type2 = e2->type;
    string operation = op->name;

    //exp -> exp binop exp
    if(operation == "+" || operation == "-" || operation == "*" || operation == "/") {
        if( (type1 != "int" && type1 != "byte") || (type2 != "int" && type2 != "byte") ) {
            output::errorMismatch(yylineno);
            exit(0);
        }
        if(type1 == "byte" && type2 == "byte") {
            this->type = "byte";
        }
        else {
            this->type = "int";
        }
    }

    //exp -> exp relop exp
    if(operation == "<" || operation == ">" || operation == "<=" || operation == ">=" ||
       operation == "!=" || operation == "==") {
        if( (type1 != "int" && type1 != "byte") || (type2 != "int" && type2 != "byte") ) {
            output::errorMismatch(yylineno);
            exit(0);
        }
        this->type = "bool";
    }

    //exp -> exp AND||OR exp
    if(operation == "and" || operation == "or") {
        if(type1 != "bool" || type2 != "bool") {
            output::errorMismatch(yylineno);
            exit(0);
        }
        this->type = "bool";
    }
}

Exp::Exp(Node *op, Exp *e) : Node(op) {
    if(e->type != "bool") {
        output::errorMismatch(yylineno);
        exit(0);
    }
    this->type = "bool";
}

Exp::Exp(Node *n, Node *b) : Node(n) {
    int num = stoi(n->name);
    if(num > 255) {
        output::errorByteTooLarge(yylineno, n->name);
        exit(0);
    }
    this->type = "byte";
}

Exp::Exp(Node *n, std::string type) : Node(n), type(type) {}

Exp::Exp(Type *t, Exp *e) : Node(t->type) {
    string e_type = e->type;
    if((e_type != "byte" && e_type != "int") || (t->type != "byte" && t->type != "int")) {
        output::errorMismatch(yylineno);
        exit(0);
    }
    this->type = t->type;
}

Exp::Exp(Node *id) : Node(id) {
    symbol_table_entry* entry = table.get_variable(id->name);
    this->type = entry->type;
}

Exp::Exp(Call *c) : Node(c->name), type(c->type) {}

///******************************************EXP LIST*******************************************

ExpList::ExpList(Exp *e) : Node(e->name) {
    this->expressions.push_back(*e);
}

ExpList::ExpList(Exp *e, ExpList *list) : Node(e->name) {
    this->expressions.push_back(*e);
    for( auto& item : list->expressions){
        this->expressions.push_back(item);
    }
}

///****************************************** STATEMENT *******************************************

Statement::Statement(Type *t, Node *id) {
    table.insert_symbol(id->name, t->type);
}

Statement::Statement(Type *t, Node *id, Exp *e) {
    if(!type_compatible(t->type, e->type)) {
        output::errorMismatch(yylineno);
        exit(0);
    }
    table.insert_symbol(id->name, t->type);
}

Statement::Statement(Node *id, Exp *e) {
    if(id->name == "return"){
        string ret_type = table.tables_stack.back().func_ret_type;
        if(!(type_compatible(ret_type, e->type))) {
            output::errorMismatch(yylineno);
            exit(0);
        }
    else{
        symbol_table_entry* entry = table.get_variable(id->name);
        //if we get here, symbol exists, otherwise we wouldve thrown error from the function

        if(!type_compatible(entry->type, e->type)) {
            output::errorMismatch(yylineno);
            exit(0);
        }
    }
    }  
}


Statement::Statement(Node* n) {
    if(n->name == "return") {
        string ret_type = table.tables_stack.back().func_ret_type;
        if (ret_type != "void") {
            output::errorMismatch(yylineno);
            exit(0);
        }
    }
    if(n->name == "break") {
        if(table.tables_stack.back().is_loop == false) {
            output::errorUnexpectedBreak(yylineno);
            exit(0);
        }
    }
    if(n->name == "continue") {
        if(table.tables_stack.back().is_loop == false) {
            output::errorUnexpectedContinue(yylineno);
            exit(0);
        }
    }

}



Statement::Statement(Exp* e) {
    if(e->type != "bool") {
        output::errorMismatch(yylineno);
        exit(0);
    }

}



///****************************************** Call *******************************************
Call::Call(Node *id, ExpList *params)  : Node(id->name) {
    vector<string> par = {};
    if(params){
        for(int i = 0; i < params->expressions.size(); i++){
            par.push_back(params->expressions[i].type);
        }
    }
    this->type = table.get_function(id->name, par)->type;
    /*errors(if there are any) are thrown from within get_functions*/
}


///****************************************** Call *******************************************
FuncDecl::FuncDecl(OverRide* override, RetType* rt, Node* id, Formals* params){
    vector<FormalDecl> param_list = params->param_list;
    vector<string> types{};
    vector<string> ids{};
    for(int i = 0; i<param_list.size(); i++) {
        types.push_back(param_list[i].type);
        types.push_back(param_list[i].name);
    }
    table.insert_symbol(id->name, rt->type, true, override->isOverRide, types);
    table.insert_func_args(types, ids, rt->type);
    //buils vector params
}