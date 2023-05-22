#include "parser.h"
#include <stdio.h>


FuncDecl::FuncDecl(OverRide* override, RetType* rt, Node* id, Formals* params){

}

FormalsList::FormalsList(FormalDecl* dec, FormalsList* list) {
    if(list == nullptr) {
        param_list.push_back(dec);
    }
}