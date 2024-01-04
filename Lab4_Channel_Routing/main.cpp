#include <bits/stdc++.h>
#include "Channel_Router.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    Channel_Router channel_router;
    channel_router.Parser(input);
    return 0;
}