#ifndef PARSE_M_H
#define PARSE_M_H

#include "Parse.h"

using namespace std;

class Parse_M : public Parse {
   private:
      vector<string> tokens;
      vector<char*> executable;
      vector<char*> arg;
      vector<char*> con;
      string input;
      friend class Command_S;
      friend class Command_M;

   public:
      Parse_M(string input);
      void separateString();
      char* Convert(string);
      void removeComment(); 
      bool isTest(string& userInput);
};

#endif
