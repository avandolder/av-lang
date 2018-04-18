#ifndef TRIE_H
#define TRIE_H

#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

// Define a basic Trie, with insertion and deletion abilities.
template <typename T>
struct Trie
{
    struct Node
    {
        std::unordered_map<char, std::shared_ptr<Node>> children;
        std::string key;
        T value;

        bool empty() { return children.empty(); }
        bool is_end() { return !key.empty(); }
        bool has_child(char c) { return children.find(c) != children.end(); }
        void add_child(char c) { children[c] = std::make_shared<Node>(); }
        auto get_child(char c) { return children[c]; }
        void remove_child(char c) { children.erase(c); }
        void add_key(std::string k, T v) { key = k; value = v; }
        void remove_key() { key.clear(); }
    };

    using NodePtr = std::shared_ptr<Node>;
    NodePtr root;

    Trie() : root(std::make_shared<Node>()) {};
    Trie(std::initializer_list<std::pair<std::string, T>>);

    void insert(std::string key, T value);
    void remove(std::string key) { remove_helper(key, root, 0); }
    bool remove_helper(std::string key, NodePtr node, int depth);
    bool has_child(char c) { return root->has_child(c); }
    auto get_child(char c) { return root->get_child(c); }
};

#endif
