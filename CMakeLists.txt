CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
   src/main.cpp
   src/Parse_S.cpp
   src/Parse_M.cpp
   src/Command_S.cpp
   src/Command_M.cpp
   src/ParenCommand.cpp
   src/TestParse_S.cpp
   src/TestCommand_S.cpp
)

ADD_EXECUTABLE(test
    unit_tests/testFile.cpp
    src/Parse_S.cpp
    src/Parse_M.cpp
    src/Command_S.cpp
    src/Command_M.cpp
    src/ParenCommand.cpp
   src/TestParse_S.cpp
   src/TestCommand_S.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
