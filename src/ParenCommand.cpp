#include "ParenCommand.h"
#include "Command_S.h"
#include "Command_M.h"
#include "Parse_S.h"
#include "Parse_M.h"
#include "And.h"
#include "Or.h"
#include "Scolon.h"
#include "Parse.h"

ParenCommand::ParenCommand(string input){
    this->StringToParse = input;
}

int ParenCommand::execute(){
    this->top = ParseString(this->StringToParse);
    this->top->execute(); 
}

int ParenCommand::CheckParen(string input){
   int count = 0;
   for(int i = 0; i < input.size(); i++){
      if(input.at(i) =='('){
         count++;
      }
   }
   return count;
}

Command* ParenCommand::ParseString(string input){
   bool quoExist = false;
   bool parenExist = false;
   int marker = 0;
   vector<Command*> innernodes;
   vector<Command*> current;
   vector<string> connectors;
   for(int i = 0; i < input.size(); i++){
      if(input.at(i) == '\"'){
         quoExist = !quoExist;
      }
      if(input.at(i) == '('){
         parenExist = true;
      }
      if(input.at(i) == ')'){
         parenExist = false;
      }
      if(quoExist== true || parenExist == true){ 
         continue;
      }
      else{
         if(input.at(i)== '|' || input.at(i)== '&' || input.at(i) == ';'){ 
            string temp = input.substr(marker, i - marker-1);  
            connectors.push_back(input.substr(i,1));
            current.push_back(buildNode(temp));
            marker = i;
            if(input.at(i) == ';'){
               marker += 2;
            }
            else{
               marker += 3;
            }
            i++;
         }
      }
   }
   current.push_back(buildNode(input.substr(marker, input.size() - marker)));
   Command* node1 = createConnector(connectors.at(0),current.at(0), current.at(1)); 
   innernodes.push_back(node1);
   if(current.size() > 2){
      for(int i = 2; i < connectors.size()-1; i++){
         Command* node2 = createConnector(connectors.at(i-1),innernodes.at(i-2),current.at(i));
         innernodes.push_back(node2);
      }
   }
   return innernodes.back();
}

Command* ParenCommand::buildNode(string temp){
   if(CheckParen(temp)== 0){ 
      Parse_S* Parser = new Parse_S(temp);
      Parser->separateString();
      return new Command_S(Parser->getExecutable(), Parser->getArg());
      //current.push_back(single);
   }
   else if(CheckParen(temp) == 1){
      temp.erase(0,1);
      temp.erase(temp.size()-1,1);
      Parse_M* ParserM = new Parse_M(temp);
      ParserM->separateString();
      return new Command_M(ParserM);
     // current.push_back(mul);
   }
   else if(CheckParen(temp) > 1) {
      temp.erase(0,1);
      temp.erase(temp.size()-1,1);
      return ParseString(temp);
     // current.push_back(nested);
   }
}  
Command* ParenCommand::createConnector(string con, Command* left, Command* right){
      if(con.at(0) == '|'){
         return new Or(left,right);
      } 
      else if(con.at(0) == '&'){
         return new And(left,right);
      }
      else if( con.at(0) == ';'){
      return new Scolon(left,right);
      }
}
