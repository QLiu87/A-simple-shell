#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>
#include <vector>
#include "base.h"

class Command : public base {
   public:
      Command(){}
      virtual int execute() = 0;
};

#endif
