cmake_minimum_required(VERSION 3.20)
project(hashtable)

set(CMAKE_CXX_STANDARD 14)

add_executable(hashtable main.cpp HashTable.cpp HashTable.h FileReader.cpp FileReader.h)
