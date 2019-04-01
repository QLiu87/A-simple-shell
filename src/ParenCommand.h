#include "Command.h"
#ifndef PARENCOMMAND_H
#define PARENCOMMAND_H
using namespace std;

class Command;
class ParenCommand : public Command {
private:
   Command* top;
   string StringToParse;
public:
   ParenCommand(string input);
   int execute();
   int CheckParen(string input);
   Command* ParseString(string input);
   Command* buildNode(string temp);
   Command* createConnector(string con,Command* left,Command* right);
};

#endif
