#include "Parse_S.h"
#include <boost/tokenizer.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace boost;

Parse_S::Parse_S(string input){
    this->StringToParse = input;
} 
void Parse_S::separateString(){
   typedef boost::tokenizer<boost::char_separator<char> > Tok;
   boost::char_separator<char> sep(" ");
   vector<string> tokens;
   Tok tok(this->StringToParse,sep);   
   for(Tok::iterator beg=tok.begin(); beg != tok.end(); ++beg){
      if((*beg) != "\""){
         tokens.push_back(*beg);
      }
   }
  
   //Sets string variables according to # of tokens
   this->executable = tokens.at(0);
   if(tokens.size() > 1){
      for(int i = 1; i < tokens.size()-1; i++){
         if((tokens.at(i) == "|" || tokens.at(i) == "&") && tokens.at(i) == tokens.at(i+1)){
            this->arg += tokens.at(i);
         }
         else{
         this->arg += tokens.at(i) + " ";
         }
      }
      this->arg += tokens.at(tokens.size()-1);
   }

  
}

char* Parse_S::getExecutable(){
   //vector<char> cstr(this->executable.c_str(), this->executable.c_str() + this->executable.size() + 1);
   return &this->executable[0u];
   //return &cstr[:0];
}
char* Parse_S::getArg(){
   
   if(!this->arg.empty()){
      return &this->arg[0u];
   }  
   return nullptr;
   //vector<char> cstr(this->arg.c_str(), this->arg.c_str() + this->arg.size() + 1);
   //return &cstr[0];
}
void Parse_S::removeComment(){
         int commentPos = this->StringToParse.find('#');
         string comment;

         if(commentPos != string::npos){
            comment = this->StringToParse.substr(commentPos);
            this->StringToParse.erase(this->StringToParse.begin() + commentPos, this->StringToParse.end());
         }
      }
