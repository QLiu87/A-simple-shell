#include "TestCommand_S.h"

using namespace std;

TestCommand_S::TestCommand_S(string flag, string filePath){
   this->flag = flag;
   this->filePath = filePath;
}

int TestCommand_S::execute(){
   struct stat testStat;
   int tempStat = stat(filePath.c_str(), &testStat);
   if(this->flag == "-e"){
      if(tempStat < 0){
         cout << "(false)" << endl;
         return 0;
      }
      else{
         cout << "(true)" << endl;
         return 1;
      }
   }
   else if(flag == "-f"){
      if(S_ISREG(testStat.st_mode)){
         cout << "(true)" << endl;
         return 1;
      }
      else{
          cout << "(false)" << endl;
          return 0;
      }
   }
   else if(flag == "-d"){
      if(S_ISDIR(testStat.st_mode)){
          cout << "(true)" << endl;
          return 1;
      }
      else{
         cout << "(false)" << endl;
         return 0;
      }
   }
}
 
