#include <iostream>
#include <stdexcept>
#include "./trie_node.hpp"

// Begin Utility functions
int
charIndex
(char c)
{
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return c - 'A' + 26;

    std::cout << "Error trie_node.cpp:13" << std::endl;

    return 0;
}

char
indexChar
(int i)
{
    if (i < 26) return (char)(i + 'a');
    else return (char)(i % 26 + 'A');
}

template<typename T> void
insertVector
(std::vector<T>& storage, std::vector<T>& stack)
{
    for(const auto& item : stack)
        storage.push_back(item);
}
// lastChar

trie_node::trie_node
()
{
    next = (trie_node **) malloc(26 * 2 * sizeof(trie_node *));
    for(int i = 0; i < 26; i++) {
        next[i] = nullptr;
    }
    cnt = 0;
    lastChar = false;
}


trie_node::~trie_node
()
{
    delete* next;
    delete& cnt;
    delete& lastChar;
}


bool
trie_node::isLastChar
() const
{
    return lastChar;
}


void
trie_node::finish
()
{
    lastChar = true;
}


void
trie_node::unfinish
()
{
    lastChar = false;
}


int
trie_node::getCnt
()
{
    return cnt;
}


void
trie_node::addCnt
(int amount)
{
    cnt += amount;
}


void
trie_node::subCnt
(int amount)
{
    cnt -= amount;
    if (cnt < 0) cnt = 0;
}


trie_node*
trie_node::getNext
(int index) const
{
    return (index >= 0 && index < 2 * 26 ?
        next[index] : NULL);
}


void
trie_node::insert
(std::string word)
{
    if (word.empty()) {
        lastChar = true;
        cnt++;
        return;
    }

    int i = charIndex(word[0]);

    if(next[i] == nullptr) {
        next[i] = new trie_node();
//        std::cout << "NEW TRIE NODE " << (char)(i < 26 ? 'a' + i : 'A' + i % 26) << std::endl;
    }

    next[i]->insert(word.substr(1, word.size() - 1));
}


std::vector<std::pair<int, std::string>>
trie_node::getSimilar
(std::string word, std::string prefix) const
{
   if (word.empty()) {
//       std::cout << prefix << std::endl;
       return getChildren(prefix);
   } else {
        char c = word[0];
        prefix += c;
        int index = charIndex(c);

        return
            (next[index] != nullptr)
            ?
            next[index]->getSimilar(word.substr(1, word.size()), prefix)
            :
            std::vector<std::pair<int, std::string>>();
   } 
}


std::vector<std::pair<int, std::string>>
trie_node::getChildren
(const std::string& prefix) const
{
//    std::cout << prefix << std::endl;
    std::vector<std::pair<int, std::string>> children;

    if (lastChar) {
        children.emplace_back(cnt, prefix);
    }

    for(int i = 0; i < 2 * 26; i++) {
        if (next[i] != nullptr) {
//            std::cout << "=>" << indexChar(i) << std::endl;
            auto nextChildren
                =
            next[i]->getChildren(prefix + indexChar(i));

            for(const auto& child : nextChildren) {
                children.push_back(child);
//                std::cout << child << std::endl;
            }
        }
    }

    return children;
}