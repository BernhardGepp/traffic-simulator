# CMake generated Testfile for 
# Source directory: C:/Users/bernh/Documents/25_Sommer2022/unitTest
# Build directory: C:/Users/bernh/Documents/25_Sommer2022/CMBuild/unitTest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(ExampleTests "C:/Users/bernh/Documents/25_Sommer2022/CMBuild/unitTest/Debug/ExampleTests.exe")
  set_tests_properties(ExampleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;34;add_test;C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(ExampleTests "C:/Users/bernh/Documents/25_Sommer2022/CMBuild/unitTest/Release/ExampleTests.exe")
  set_tests_properties(ExampleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;34;add_test;C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(ExampleTests "C:/Users/bernh/Documents/25_Sommer2022/CMBuild/unitTest/MinSizeRel/ExampleTests.exe")
  set_tests_properties(ExampleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;34;add_test;C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(ExampleTests "C:/Users/bernh/Documents/25_Sommer2022/CMBuild/unitTest/RelWithDebInfo/ExampleTests.exe")
  set_tests_properties(ExampleTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;34;add_test;C:/Users/bernh/Documents/25_Sommer2022/unitTest/CMakeLists.txt;0;")
else()
  add_test(ExampleTests NOT_AVAILABLE)
endif()
