#include "Node.h"

// Dummy node constructor used for dummy head node
Node::Node():cell(nullptr), next(nullptr), prev(nullptr){
    ;
}

Node::Node(Cell *c):cell(c), next(nullptr), prev(nullptr){
    ;
}

// Called in Cell destructor
Node::~Node(){

}