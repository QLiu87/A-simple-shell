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

int main() {
   string userInput;   
   bool hasTestCommand;
 
   cout << "$ ";
   getline(cin, userInput);

   while(!exitCommand(userInput)){
      removeComment(userInput);
      hasTestCommand = isTest(userInput);
      
      if(CheckForConnector(userInput)){ //If input contains a connector, it creates parse_m/command_m class instances
         if(CheckForParen(userInput)){
            Command* Paren = new ParenCommand(userInput);
            Paren->execute();
         
          }
          else {
         Parse_M* Parser = new Parse_M(userInput); //If input does not contain a test command, a normal Parser is created
         //}   
         Parser->separateString();
         Command_M* cmd1 = new Command_M(Parser);
         cmd1->execute(); 
         }
      }
      else{ //If no connector is found, parse_s/command_s class instances are created
         if(hasTestCommand){
            TestParse_S* Parser = new TestParse_S(userInput); //If input contains test command, a test subclass Parser is created
            Parser->separateString();
            Parser->setFlag();
            Parser->setFilePath();
            TestCommand_S* tcmd = new TestCommand_S(Parser->getFlag(), Parser->getFilePath());
            tcmd->execute();
         }
         else{
            Parse_S* Parser = new Parse_S(userInput); //If input does not contain a test command, a normal Parse is created
            Parser->separateString(); 
            Command* cmd2 = new Command_S(Parser->getExecutable(), Parser->getArg());
            cmd2->execute();
         }
      }
  
      cout << "$ ";
      getline(cin, userInput);
   }

   return 0;
}
