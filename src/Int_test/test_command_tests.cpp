#include <iostream>
#include <string>
#include <fstream>

#include "../base.h"
#include "../main.h"
#include "../TestCommand_S.h"
#include "../TestParse_S.h"

using namespace std;

int main(int argc, char** argv){
   ifstream fin;
   string userInput;

   fin.open(argv[1]);
 
   while(getline(fin, userInput)){
      TestParse_S* parser = new TestParse_S(userInput);
      parser->separateString();
      parser->setFlag();
      parser->setFilePath();
      TestCommand_S* command = new TestCommand_S(parser->getFlag(), parser->getFilePath());

      cout << "Testing: " << userInput << endl;
      command->execute();
   }
   fin.close();

   return 0;
}
