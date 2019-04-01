#include "gtest/gtest.h"
#include "../src/base.h"
#include "../src/main.h"
#include "../src/Parse.h"
#include "../src/Parse_S.h"
#include "../src/TestParse_S.h"
#include "../src/Parse_M.h"
#include "../src/Command.h"
#include "../src/Command_S.h"
#include "../src/TestCommand_S.h"
#include "../src/Command_M.h"
#include "../src/ParenCommand.h"
using namespace std;

TEST(MainTest, HasConnector){
   string testString1 = "mkdir && ls";
   string testString2 = "no connector";
   
   EXPECT_EQ(true, CheckForConnector(testString1));
   EXPECT_EQ(false, CheckForConnector(testString2));
}
/*
TEST(MainTest, ExitCommand){ //Test passes but exits the program (as implemented)
   string testString1 = "exit";
   string testString2 = "mkdir exit";

   EXPECT_EQ(true, exitCommand(testString1));
   EXPECT_EQ(false, exitCommand(testString2));
}
*/
TEST(ParseTest, ParseGetExeGetArgSeparateString){
   string testExecutable = "mkdir";
   string testArg = "assignment2";

   Parse_S* parser = new Parse_S(testExecutable + " " + testArg);

   parser->separateString();

   EXPECT_EQ(testExecutable, parser->getExecutable());
   EXPECT_EQ(testArg, parser->getArg());

}

TEST(ParseTest, ParseConvert){
   string testString = "this is a test string";
   Parse_M* parser = new Parse_M(testString);

   EXPECT_EQ(*testString.c_str(), *parser->Convert(testString));
}

TEST(TestParseTest, MutatorAccessorTests){
   string testString = "test -f path/to/file.cpp";
   string testFlag = "-f";
   string testPath = "path/to/file.cpp";
   TestParse_S* parser = new TestParse_S(testString);
   
   parser->separateString();
   parser->setFlag();
   parser->setFilePath();

   EXPECT_EQ(*testFlag.c_str(), *parser->getFlag());
   EXPECT_EQ(*testPath.c_str(), *parser->getFilePath());
}

TEST(TestParseTest, isValidFlagTest){
   string testString = "test -e test/path";
   TestParse_S* parser = new TestParse_S(testString);

   EXPECT_EQ(true, parser->isValidFlag("-e"));
   EXPECT_EQ(true, parser->isValidFlag("-f"));
   EXPECT_EQ(true, parser->isValidFlag("-d"));
   EXPECT_EQ(false, parser->isValidFlag("-a"));
}
 
//The following tests rely on local files & don't always cooperate. All tests in their current state have been passed on hammer.

TEST(TestCommandTest, eFlag){ 
   string testFlag = "-e";
   string testPath1 = "src/main.cpp";
   string testPath2 = "src/nullFile.cpp";

   TestCommand_S* command1 = new TestCommand_S(testFlag, testPath1);
   TestCommand_S* command2 = new TestCommand_S(testFlag, testPath2);

   EXPECT_EQ(true, command1->execute()); //Test a real path
   EXPECT_EQ(false, command2->execute()); //Test a fake path
}

TEST(TestCommandTest, defaultFlag){
   string input = "test src/main.cpp";
   TestParse_S* parser = new TestParse_S(input);

   parser->separateString();
   parser->setFlag();
   parser->setFilePath();

   TestCommand_S* command = new TestCommand_S(parser->getFlag(), parser->getFilePath());
   
   EXPECT_EQ(true, command->execute());
}

TEST(TestCommandTest, fFlag){
   string testFlag = "-f";
   string testPath1 = "src/TestParse_S.h";
   string testPath2 = "src/test.txt";

   TestCommand_S* command1 = new TestCommand_S(testFlag, testPath1);
   TestCommand_S* command2 = new TestCommand_S(testFlag, testPath2);

   EXPECT_EQ(true, command1->execute());
   EXPECT_EQ(false, command2->execute());
}

TEST(TestCommandTest, dFlag){
   string testFlag = "-d";
   string testPath1 = "unit_tests";
   string testPath2 = "CMakeDirectory";

   TestCommand_S* command1 = new TestCommand_S(testFlag, testPath1);
   TestCommand_S* command2 = new TestCommand_S(testFlag, testPath2);

   EXPECT_EQ(true, command1->execute());
   EXPECT_EQ(false, command2->execute());
}
TEST(ParenCommandTest, precedence){
   string input = "(echo 1 && echo 2) || (echo 3 && echo 4)";
   string input1 = "echo 1 || (echo 3 && echo 4)";
   ParenCommand* cmd = new ParenCommand(input);
   ParenCommand* cmd1 = new ParenCommand(input1);
   string ans = "1\n2";
   EXPECT_EQ(1,cmd->execute());
}

int main(int argc, char** argv){
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
