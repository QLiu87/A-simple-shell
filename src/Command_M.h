#ifndef COMMAND_M_H
#define COMMAND_M_H

#include "Command.h"

using namespace std;

class Command_S;
class Parse_M;
class Command_M : public Command { 
   private:
      vector<Command*> innernodes;
      vector<char*> executables;
      vector<char*> args;
      vector<char*> cons;
   public:
      Command_M(Parse_M* parse);
      int execute();
      Command* createConnector(char*,Command*, Command*);
      Command* createCommand(char*,char*);
};

#endif
