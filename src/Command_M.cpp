#include "Command_S.h"
#include "Command.h"
#include "Command_M.h"
#include <vector>
#include <string>
#include "Or.h"
#include "And.h"
#include "Scolon.h"
#include <string.h>
#include "Parse_M.h"
#include "TestCommand_S.h"
Command_M::Command_M(Parse_M* parse){
   this->executables = parse->executable;
   this->args = parse->arg;
   this->cons = parse->con;
   //building the tree
}
int Command_M::execute(){
   vector<Command*> tree;
   for(int i = 0; i <= cons.size(); i++){
      Command* cmd = createCommand(executables.at(i),args.at(i));
      tree.push_back(cmd);
   }
   Command* node1 = createConnector(cons.at(0),tree.at(0),tree.at(1)); 
   innernodes.push_back(node1);
   if( tree.size() > 2){
      for(int i = 1; i < cons.size(); i++){
         Command* node2 = createConnector(cons.at(i),innernodes.at(i-1),tree.at(i+1));
         innernodes.push_back(node2);
      }
   }

     return innernodes.at(innernodes.size()-1)->execute();
}

Command* Command_M::createConnector(char* con, Command* left, Command* right){
      if(strcmp(con,"||") == 0){
         return new Or(left,right);
      } 
      else if(strcmp(con,"&&") == 0){
         return new And(left,right);
      }
      else if( strcmp(con, ";") ==0){
      return new Scolon(left,right);
      }
}

Command* Command_M::createCommand(char* exe, char* arg){
   if(strcmp(exe, "-e") == 0 || strcmp(exe, "-f") == 0 || strcmp(exe,"-d") == 0){
      string temp = exe;
      string temp2 = arg;
      return new TestCommand_S(temp,temp2);
   }
   else{
      Command_S* cmd = new Command_S(exe, arg);
      return cmd;
   }
}
