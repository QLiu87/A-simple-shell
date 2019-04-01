#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "base.h"
#include "main.h"
#include "Command.h"
#include "Command_S.h"
#include "TestCommand_S.h"
#include "Command_M.h"
#include "Parse.h"
#include "Parse_S.h"
#include "TestParse_S.h"
#include "Parse_M.h"
#include "Or.h"
#include "And.h"
#include "Scolon.h"
#include "ParenCommand.h"

using namespace std;
int main(int argv, char** argc) {
    string userInput; 
    cout << "$ ";
    for(int i = 1; i < argv-1; i++){     
        string str(argc[i]);
        userInput += str+ " ";
    }
   string str(argc[argv-1]);
   userInput += str;
   cout << "Input is: " << userInput << endl;
   removeComment(userInput);
   Command* Paren = new ParenCommand(userInput);
   Paren->execute();
}
         
