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
        input += str+ " ";
    }
    
    removeComment(input);
    Parse_S* Parser = new Parse_S(input); //If connectors are not present, create a parser for single command
         Parser->separateString(); 
         Command* cmd2 = new Command_S(Parser->getExecutable(),Parser->getArg());
         cmd2->execute(); 
   return 0;
}
