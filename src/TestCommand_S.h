#ifndef TESTCOMMAND_S_H
#define TESTCOMMAND_S_H

#include "Command.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class TestCommand_S : public Command {
   private:
      string flag;
      string filePath;
   public:
      TestCommand_S(string flag, string filePath);
      int execute();
};

#endif
