#ifndef COMMAND_S_H
#define COMMAND_S_H

#include "Command.h"
#include "string.h"
using namespace std;
class Parse_S;
class Command_S : public Command{
   private:
     char* executable;
     char* arg;
     char* con;
   public:
      Command_S(char* executable = nullptr, char* arg= nullptr){; 
         this->executable = executable;
         this->arg = arg;
      }
      int execute();
      string getE(){ return (string)executable;}
};

#endif
