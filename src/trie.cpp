#include <initializer_list>
#include <string>
#include <utility>

#include "token.h"
#include "trie.h"

template <typename T>
Trie<T>::Trie(std::initializer_list<std::pair<std::string, T>> list)
{
    root = std::make_shared<Node>();

    for (auto& elem : list)
        insert(elem.first, elem.second);
}

// Insert a key into a trie.
template <typename T>
void Trie<T>::insert(std::string key, T value)
{
    auto node = root;

    for (char c : key)
    {
        if (!node->has_child(c))
            node->add_child(c);

        node = node->get_child(c);
    }

    node->add_key(key, value);
}

// Recursive helper function that removes a key from a trie.
template <typename T>
bool Trie<T>::remove_helper(std::string key, NodePtr node, int depth)
{
    if (depth == key.size())
    {
        node->remove_key();
        return node->empty();
    }

    if (remove_helper(key, node->get_child(key[depth]), depth + 1))
    {
        node->remove_child(key[depth]);
        return !node->is_end() && node->empty();
    }

    return false;
}
