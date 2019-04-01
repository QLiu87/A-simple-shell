# CS 100 Programming Project

# Project Information
Winter 2019
Michael Baluja 862009661
Qi Liu 861231381

# Introduction
This program is a C++ implementation of a bash command shell. It allows users to execute any command listed in a PATH directory, such as ls, echo, mkdir, etc... To do so, the program uses the system calls execvp(), fork(), and waitpid(). This program also has functionality to execute the test command, as well as it's symbolic [] counterpart. The test command is executed using the stat() function, as well as S_ISREG and S_ISDIR in order to accomodate input flags.

The main intentional design pattern that is used is the composite pattern, and it is used when ingesting commands. When multiple commands are passed into the program, the part-whole structure of the composite pattern is used to execute the commands.

In short, input is read into a string variable, which is then checked for valid connectors, comments, or test commands, and is then used to create a new instance of TestParse_S for a single test command, Parse_S for a single non-test command, or Parse_M for multiple test or non-test commands which are all derived classes from the abstract base Parse class. During this initial check, the input is also checked for the exit command, which terminates the program if and only if it is the only valid command in the input string. Once a command is properly parsed, a derived command class is made (TestCommand_S for TestParse_S, Command_S for Parse_S, and Command_M for Parse_M), which executes commands using the previously mentioned system calls.

# Diagram
[UML Diagram for class heirarchy](images/UML.png)

# Classes
## Parse:
Parse serves as an abstract base class for the TestParse_S, Parse_S and Parse_M derived classes. The main goal of the parse classes is to turn the user input into tokens that are easy for the command class to ingest. To accomplish this, user input is separated into the $ executable [argumentList] [connector] [cmd] … format given in the Assignment 2 spec sheet for Parse_S and Parse_M. For TestParsE_S, it is separated into a flag (if present) and a filePath. This is done by iterating through the input string, and then storing each command component in its own string variable. All tokenization is perfomed using the boost library tokenizer class.

- TestParse_S:
TestParse_S is called after a test command has been recognized, either from the test command itself, or its symbolic equivalent. TestParse_S then uses the tokenizer class to parse the input, and sets the string variables flag and filePath accordingly. To do so, there is an isValidFlag command that checks for a valid flag, or sets a default flag, and then sets the filePath to be the following token.

- Parse_S:
Parse_S is called after a connector-check has been performed, and did not show that the input contains valid connectors. By following the format mentioned in the base Parse class description, Parse_S tokenizes input to properly separate each element of the input string. Once the command is properly broken up, the elements of the command are then stored as private string variables with accessor functions.

- Parse_M:
Parse_M is called after a connector-check has been performed, and showed that the input did contain valid connectors. Following the format shown in the base Parse class description, Parse_M also tokenizes input to find indicators of different command elements, and then stores them into private string vectors. Each time a connector is found in the input, the process is repeated, until no more connectors are found, or the end of the input string is reached. To access the protected string vectors, there are accessor functions that take in input to indicate the position of the desired element. If an invalid position is passed in, and error is returned. If an invalid command is found, the other commands are executed, and an error message is outputted for the incorrect command.

### Command:
The Command classes is a friend class of Parse, giving it access to the accessor functions needed for the different elements of the commands. Since the Parse child classes already check for command validity, Command uses execvp() to execute these commands once an instance of Command is initialized. After Command takes the proper input from Parse, the Parse class destructor is called, to eliminate unnecessary class instances.

- TestCommand_S:
TestCommand_S: Once a test command is properly parsed, it’s flag and filepath are passed to TestCommand_S, which uses the stat() function to check existence of the filepath. S_ISDIR and S_ISREG are also used to check the filepath type, since stat() only checks general existence.

- Command_S:
In the same way Parse_S will parse a single command, Command_S will call the accessor classes for the command elements made in the Parse_S class, fork() it, and make a call to execvp() to run the command. Once the command is finished, waitpid() is called to stop the system from being filled with dead children.

- Command_M:
Similar to Command_S, Command_M receives the necessary input from Parse_M. Once input is received, it is again stored in the proper string vector.Then a vector is used to store Command object. Then each object is being paired up by their connectors and being executed. With connector class being the innernodes, and Command_S objects as the leaf node. A tree is built up from the vector of commands. Then execute is being called on the last tree nodes to execute the whole tree. 

- ParenCommand:
If parentheses are detected in the userInput, a ParenCommand constructor would be called. This child of command class parses the userInput by the highest level of connectors recursively, and stops when there's no more parenthesis. It then builds a Command object from the parsing string. Then, in each level of recursion, the command objects are built into connectors objects, and finally built into a tree. After all recursion is done, the root would be executed to execute the whole tree.

# Prototype/Research
- Fork() is a operation that a process makes a copy of itself. The duplicated process is called child, and the original process is called parent. 
- Execvp executes the command and if the execution fails, it returns -1
waitpid() suspends the process its in, and wait for a terminated child process.
In assignment 2, we first use fork to create a child process, then we execute the command from the user in the child process. After the execution is complete, the child process is then terminated, and we go back to the parent process. During the above steps, if any error had happened, we use perror() to translate the error message stored in errno and output it. 
- Notes on seperators: seperators extracts the string between seperators; If two function are separated by ||. Then if the first command executed sucessfully, the second command would not execute. But if the first command failed, the second command would start to execute. For &&, only when both commands are true, the command would execute. For ;, the command are executed in order. 
# Development and Testing Roadmap
 [ ] Implement Parse Classes
 [ ] Implement Command Classes
 [ ] Unit Test Parse Classes
 [ ] Unit Test Command Classes
 [ ] Integration Testing
1. [Planning of classes](https://github.com/cs100/assignment-cs-100-michael-richard/issues/5)
    - Class Parse
      * Parse_single
      * Parse_multiple
    - Class Command
      * Command_single
      * Command_multiple
    - Class execution
2. [Set up the program](https://github.com/cs100/assignment-cs-100-michael-richard/issues/2)
    - Create header files for each planned class
    - Create main.cpp, unit_test.cpp and integration_test.cpp
    - Create a CMakeList.txt that can generate executable for main.cpp, unit_test.cpp, and integration_test.cpp.
3. [Building the program](https://github.com/cs100/assignment-cs-100-michael-richard/issues/3)
    - Implement each class
    - Compile the program using CMake
    - Use googletest to validate the program, and make sure it’s working.
4. [Testing](https://github.com/cs100/assignment-cs-100-michael-richard/issues/4)
    - Unit test
    - Integration test

