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

std::vector<std::pair<int, std::string>>
trie::search
(const std::string& word) const
{
    return root->getSimilar(word, "");
}