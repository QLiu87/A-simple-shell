#ifndef PARSE_S_H
#define PARSE_S_H

#include "Parse.h"

using namespace std;

class Parse_S : public Parse {
   private:
      string executable;
      string arg;
      string cmd;
      string StringToParse;
      friend class Command_S;
      friend class Command_M;

   public:
      Parse_S(string input);
      void separateString();
      char* getExecutable();
      void removeComment();
      char* getArg();
};

#endif
