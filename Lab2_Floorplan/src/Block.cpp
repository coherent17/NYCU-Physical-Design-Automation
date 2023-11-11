#include "Block.h"

Block::Block(string Name, size_t Width, size_t Height):
    Name(Name),
    Width(Width),
    Height(Height)
{
    ;
}

Block::~Block(){
    ;
}

ostream &operator<<(ostream &out, const Block &block){
    out << "Block Name: " << block.Name << endl;
    out << "Block Width: " << block.Width << endl;
    out << "Block Height: " << block.Height << endl;
    return out;
}