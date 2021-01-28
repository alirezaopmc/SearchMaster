#ifndef TRIE_HPP
#define TRIE_HPP

#include "../trie_node/trie_node.hpp"
#include "iostream"

class trie {
private:
public:
    trie_node *root;

    trie
    ();

    ~trie
    ();


    void
    insert
    (std::string word) const;

    std::vector<std::pair<int, std::string>>
    search
    (const std::string& word) const;

};


#endif