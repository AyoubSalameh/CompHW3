#include "parser.h"
#include <stdio.h>

using namespace std;

FuncDecl::FuncDecl(OverRide* override, RetType* rt, Node* id, Formals* params){

}

FormalsList::FormalsList(FormalDecl* dec, FormalsList* list) {
    this->param_list.push_back(*dec);
    for( auto& item : list->param_list){
        this->param_list.push_back(item);
    }
}

FormalsList::FormalsList(FormalDecl *dec) {
    this->param_list.push_back(*dec);
}

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