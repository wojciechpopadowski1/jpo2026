# CMakeLists.txt - Główny plik konfiguracji CMake dla PyScript AI Generator
cmake_minimum_required(VERSION 3.16)

project(PyScriptAI VERSION 1.0.0 LANGUAGES CXX)

# Standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatyczne przetwarzanie plików Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Znajdź pakiety Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Test)

# Katalog źródłowy
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Lista plików źródłowych
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/mainwindow.cpp
    ${SOURCE_DIR}/ollamaclient.cpp
    ${SOURCE_DIR}/pythonexecutor.cpp
    ${SOURCE_DIR}/workerthread.cpp
)

# Lista plików nagłówkowych
set(HEADERS
    ${SOURCE_DIR}/mainwindow.h
    ${SOURCE_DIR}/ollamaclient.h
    ${SOURCE_DIR}/pythonexecutor.h
    ${SOURCE_DIR}/workerthread.h
    ${SOURCE_DIR}/config.h
)

# Plik UI
set(UI_FILES
    ${SOURCE_DIR}/mainwindow.ui
)

# Utwórz plik wykonywalny
if(WIN32)
    # Windows - aplikacja okienkowa
    add_executable(PyScriptAI WIN32 ${SOURCES} ${HEADERS} ${UI_FILES})
else()
    add_executable(PyScriptAI ${SOURCES} ${HEADERS} ${UI_FILES})
endif()

# Linkowanie z bibliotekami Qt
target_link_libraries(PyScriptAI
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

# Włącz katalog include
target_include_directories(PyScriptAI PRIVATE ${SOURCE_DIR})

# Opcjonalne: dodaj testy
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Instalacja
install(TARGETS PyScriptAI
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Informacja o konfiguracji
message(STATUS "======================================")
message(STATUS "PyScript AI Generator Configuration")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Qt version: ${Qt6_VERSION}")
message(STATUS "  Build tests: ${BUILD_TESTS}")
message(STATUS "======================================")
