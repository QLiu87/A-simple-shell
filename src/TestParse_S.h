#ifndef TESTPARSE_S_H
#define TESTPARSE_S_H

#include <string>
#include <vector>

#include "Parse.h"

class TestParse_S : public Parse{
   private:
      string flag = "-e";
      string filePath;
      vector<string> tokens;
   public:
      TestParse_S(string& StringToParse);
      bool isValidFlag(string flag);
      void separateString();
      void setFlag();
      char* getFlag();
      void setFilePath();
      char* getFilePath();
};

#endif
