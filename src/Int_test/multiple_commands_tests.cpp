#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "main.h"
#include "Command.h"
#include "Command_S.h"
#include "Command_M.h"
#include "Parse.h"
#include "Parse_S.h"
#include "Parse_M.h"
#include "Or.h"
#include "And.h"
#include "Scolon.h"

using namespace std;

int main(int argv, char** argc) {
    string input; 
    cout << "$ ";
    for(int i = 1; i < argv; i++){     
        string str(argc[i]);
        input += " " +str;
    }
    Parse_M* Parser = new Parse_M(input); 
    Parser->removeComment();
    Parser->separateString();
    Command_M* cmd1 = new Command_M(Parser);
    cmd1->execute(); 
   return 0;
}
