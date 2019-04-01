#ifndef AND_H
#define AND_H

#include <iostream>

class And : public Command {
private:   
Command* left;
Command* right;
public:
     And(Command* left, Command* right){
        this->left = left;
        this->right = right;
     };
     int execute(){
        int i = left->execute();
        if( i == 1) 
           return right->execute();
        return 0;
        }
};

#endif
