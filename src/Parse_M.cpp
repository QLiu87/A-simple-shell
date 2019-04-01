#include "Parse_M.h"
#include <boost/tokenizer.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <string.h>
using namespace std;
using namespace boost;

Parse_M::Parse_M(string input){
    this->input = input;
}

void Parse_M::separateString(){
   typedef boost::tokenizer<boost::char_separator<char> > Tok;
   boost::char_separator<char> sep(" ","\""); // default constructed
   Tok tok(this->input, sep);
   for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter){
      tokens.push_back(*tok_iter);
   }   
   int marker = 0;
   string argList;
   string tempStr;
   bool quoExist = false;
   for(int i = 0; i < tokens.size(); i++){
      if(tokens.at(i) == "\"" || tokens.at(i) == "\""){
         quoExist = !quoExist;
      }
      if(quoExist== true){ 
         continue;
      }
      else{
         if(tokens.at(i)== "||" || tokens.at(i)== "&&" || tokens.at(i)== ";"){
            //If token is a connector
            if((tokens.at(marker) == "[" && tokens.at(i-1) == "]") || tokens.at(marker) == "test"){ 
               if((tokens.at(marker) == "[" && (i-marker == 3)) || (tokens.at(marker) == "test" && (i - marker == 2))){
                  this->executable.push_back(Convert("-e"));
                  this->arg.push_back(Convert(tokens.at(marker+1)));
               }
               else{
                  this->executable.push_back(Convert(tokens.at(marker+1)));
                  this->arg.push_back(Convert(tokens.at(marker+2)));
               }
               this->con.push_back(Convert(tokens.at(i)));
               marker = i+1;
            }
            else{ 
               this->executable.push_back(Convert(tokens.at(marker)));
               this->con.push_back(Convert(tokens.at(i)));
               while(marker + 1 != i){
                  if(tokens.at(marker + 1) == "\""){
                     marker++;
                     continue;
                  }
                  else{   
                     argList += tokens.at(marker+1) + " "; 
                     marker++;
                  }
               }
               this->arg.push_back(Convert(argList)); 
               argList.clear();
               marker += 2;
            }
         }
      }
   }
   if((tokens.at(marker) == "[" && (tokens.size()-marker == 4)) || (tokens.at(marker) == "test" && (tokens.size() - marker == 3))){
      this->executable.push_back(Convert("-e"));
      this->arg.push_back(Convert(tokens.at(marker+1)));
   } 
   else if(tokens.at(marker) == "[" || tokens.at(marker) == "test"){
      this->executable.push_back(Convert(tokens.at(marker+1)));
      this->arg.push_back(Convert(tokens.at(marker+2)));
   }
   else{
      this->executable.push_back(Convert(tokens.at(marker)));
      while(marker+1 != tokens.size()){
         if(tokens.at(marker+1) == "\""){
            marker++;
            continue;
         }
         else{  
         argList += tokens.at(marker+1);
         marker++;
         }
      } 
      this->arg.push_back(Convert(argList));
   }
}

char* Parse_M::Convert(string str){
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
// do stuff
    return cstr;
}
void Parse_M::removeComment(){
         int commentPos = this->input.find('#');
         string comment;

         if(commentPos != string::npos){
            comment = this->input.substr(commentPos);
            this->input.erase(this->input.begin() + commentPos, this->input.end());
         }
}

