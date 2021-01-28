#include "trie.hpp"

#include <utility>

trie::trie() {
    root = new trie_node();
}

trie::~trie() = default;

void
trie::insert
(std::string word) const
{
    root->insert(std::move(word));
}

std::vector<std::string>
trie::search
(std::string word) const
{
    return root->getSimilar(std::move(word), "");
}