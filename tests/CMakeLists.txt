cmake_minimum_required(VERSION 3.16)

# 1. Automatyczne pobranie GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 2. Ścieżki
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# 3. Test dla PythonExecutor
add_executable(test_executor 
    test_executor.cpp 
    ${SRC_DIR}/pythonexecutor.cpp
)
target_link_libraries(test_executor
    Qt6::Core
    Qt6::Test
    gtest
)

# 4. Test dla OllamaClient
add_executable(test_ollama 
    test_ollama.cpp 
    ${SRC_DIR}/ollamaclient.cpp
)
target_link_libraries(test_ollama
    Qt6::Core
    Qt6::Network
    Qt6::Test
    gtest
)

# 5. Aktywacja testów
enable_testing()
add_test(NAME ExecutorTests COMMAND test_executor)
add_test(NAME OllamaTests COMMAND test_ollama)