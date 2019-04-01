#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool CheckForConnector(string userInput){
   int quoPos = userInput.find('\"');
   vector<int> quoLoc;
   //check for quotation marks 
   if( quoPos <= userInput.length()){
      for(int i = 0; i < userInput.size(); i++) {
         if(userInput.at(i) == '\"'){
            quoLoc.push_back(i);
         }
      }
   //if yes, erase contents between ""
      if(quoLoc.size() % 2 != 0){
         cout << "Input wrong number of \"" << endl;
         exit(0);
      }
      else{
         for(int i = 0; i < quoLoc.size() - 1; i += 2){
            userInput.erase(quoLoc.at(i),quoLoc.at(i+1)-quoLoc.at(i));
         }
      }
   }
   for(int i = 0; i < userInput.size() - 2; ++i){
      if((userInput.at(i) == userInput.at(i + 1) && userInput.at(i) == '&') ||
      (userInput.at(i) == userInput.at(i + 1) && userInput.at(i) == '|' || userInput.at(i) == ';')){
         return true;
      }
   }
   return false;
}
bool CheckForParen(string input){
   int count_left = 0;
   int count_right = 0;
   bool quoExist = false;
   for(int i = 0; i < input.size(); i++){
      if(input.at(i) == '\"'){
         quoExist = !quoExist;
      }
      if(quoExist){
         continue;
      }
      else{
         if(input.at(i) == '(')
            count_left++;
         if(input.at(i) == ')')
            count_right++;
      }
   }
   if(count_left == count_right && count_left == 0){
      return false;
   }
   else if(count_left == count_right){
      return true;
   }
   cout << "Wrong number of Paren!" << endl;
   exit(0);
}

int numQuoteBeforePos(string& userInput, int& commentPos){
   int counter = 0;

   for(int i = 0; i < commentPos; ++i){
      if(userInput.at(i) == '"'){
         ++counter;
      }
   }

   return counter;
}

void removeComment(string& StringToParse){
   int commentPos = StringToParse.find('#');
   string comment;

   if(commentPos != string::npos){
      if(numQuoteBeforePos(StringToParse, commentPos) % 2 == 0){
         comment = StringToParse.substr(commentPos);
         StringToParse.erase(StringToParse.begin() + commentPos, StringToParse.end());
      }
   }
}

bool exitCommand(string& userInput){
  // string::iterator end_pos = remove(userInput.begin(), userInput.end(), ' ');
  // userInput.erase(end_pos, userInput.end());
   if(userInput == "exit"){
      exit(0);
   }
}

bool isTest(string& userInput){
   int count = 0;
   bool quo = false;
   if((userInput.substr(0,4) == "test")){ //If first 4 chars of string is test command, sets returnVal to true
      return true;
   }
   for(int i = 0; i < userInput.size(); i++){
      if(userInput.at(i) == '\"'){
         quo = !quo;
      }
      if(quo){
         continue;
      }
      else{
         if(userInput.at(i) == '[' || userInput.at(i) == ']'){ //If the first char of string is the bracket indicating the test command, search for the closing bracket
            count++; 
         }
      }
   }
   if(count % 2 != 0){
      cout << "wrong number of [ ] " <<count <<endl;
      exit(0);
   }
   if(userInput.at(0) == '['){
      return true;
   }

   return false;
}
