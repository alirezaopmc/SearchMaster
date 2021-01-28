cmake_minimum_required(VERSION 3.17)
project(SearchMaster)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs/trie)
include_directories(libs/trie_node)

add_executable(SearchMaster
        libs/trie/trie.cpp
        libs/trie/trie.hpp
        libs/trie_node/trie_node.cpp
        libs/trie_node/trie_node.hpp
        search.cpp)
