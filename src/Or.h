#ifndef OR_H
#define OR_H

#include <iostream>

class Or : public Command {
private:   
Command* left;
Command* right;
public:
     Or(Command* left, Command* right){
        this->left = left;
        this->right = right;
     };
     int execute(){
        int i = left->execute();
        if(i == 1){
           return 1;
        } 
        else{
        return right->execute();
       }
     }
};

#endif
