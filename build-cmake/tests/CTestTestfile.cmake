# CMake generated Testfile for 
# Source directory: C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/tests
# Build directory: C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/build-cmake/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ExecutorTests "C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/build-cmake/tests/test_executor.exe")
set_tests_properties(ExecutorTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/tests/CMakeLists.txt;40;add_test;C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/tests/CMakeLists.txt;0;")
add_test(OllamaTests "C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/build-cmake/tests/test_ollama.exe")
set_tests_properties(OllamaTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/tests/CMakeLists.txt;41;add_test;C:/Users/wojty/Desktop/jpo/pyscript_ai_generator/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
