#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <vector>
#include <iostream>

class trie_node {
private:
public:
    trie_node** next;
    int cnt;
    bool lastChar;

    trie_node
    ();

    ~trie_node
    ();

    bool isLastChar
    () const;


    void finish
    ();

    void unfinish
    ();

    int getCnt
    ();

    void addCnt
    (int amount = 1);

    void subCnt
    (int amount = 1);

    trie_node*
    getNext(int index) const;

    void 
    insert
    (std::string word);


    std::vector<std::pair<int, std::string>>
    getSimilar
    (std::string word, std::string prefix) const;
    
    std::vector<std::pair<int, std::string>>
    getChildren
    (const std::string& prefix) const;
};

#endif