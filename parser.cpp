#include "parser.h"
#include <stdio.h>


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