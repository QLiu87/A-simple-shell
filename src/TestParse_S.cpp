#include "TestParse_S.h"
#include <boost/tokenizer.hpp>
#include <string>

using namespace std;
using namespace boost;

TestParse_S::TestParse_S(string& StringToParse){
   this->StringToParse = StringToParse;
}

void TestParse_S::separateString(){
   typedef boost:: tokenizer<boost::char_separator<char>> Tokenizer;
   boost::char_separator<char> sep(" ");
   Tokenizer tok(StringToParse, sep);
      
   for(Tokenizer::iterator iter = tok.begin(); iter != tok.end(); ++iter){
      tokens.push_back(*iter);
   }
}

bool TestParse_S::isValidFlag(string f){

   if((f == "-e") || (f == "-f") || (f == "-d")){
      return true;
   }
   
   return false;
}

void TestParse_S::setFlag(){
   if((this->tokens.at(0) == "test")){ //Making sure that the first element is the test function 
      if(isValidFlag(this->tokens.at(1))){ //If a flag is given, use it
         flag = this->tokens.at(1);
      }
   }
   else if(this->tokens.at(0) == "["){
       if(isValidFlag(this->tokens.at(1))){ //If the first element is a flag, use it
         flag = this->tokens.at(1);
       }    
   }
   else{ //No flag was specified, so go with default
      flag = "-e";
   }
}

char* TestParse_S::getFlag(){
   return &this->flag[0u];
}

void TestParse_S::setFilePath(){
   if((tokens.at(0) == "test") && (isValidFlag(tokens.at(1)))){ // test flag filePath
      filePath = tokens.at(2);
   }
   else if((tokens.at(0) == "test") && (!isValidFlag(tokens.at(1)))){ //test filePath
      filePath = tokens.at(1);
   }
   else if(isValidFlag(tokens.at(1))){ //flag filePath
      filePath = tokens.at(2);
   }
   else { //filePath
      filePath = tokens.at(1);
   }
}

char* TestParse_S::getFilePath(){
   return &this->filePath[0u];
}
