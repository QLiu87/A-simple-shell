#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>
#include <string>
#include "base.h"

using namespace std;

class Parse : public base{
   protected:
      string StringToParse;
   public:
      //Parse(string StringToParse){ this->StringToParse = StringToParse; }
      bool isValid();
      void removeComment(){
         int commentPos = StringToParse.find('#');
         string comment;

         if(commentPos != string::npos){
            comment = StringToParse.substr(commentPos);
            StringToParse.erase(StringToParse.begin() + commentPos, StringToParse.end());
         }
      }
      virtual void separateString() = 0;
};
      int execute();

#endif
