#ifndef SCOLON_H
#define SCOLON_H

#include <iostream>

class Scolon : public Command {
private:   
Command* left;
Command* right;
public:
     Scolon(Command* left, Command* right){
        this->left = left;
        this->right = right;
     };
     int execute(){
        left->execute();
       return right->execute();
     }
};

#endif

