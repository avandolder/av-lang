#ifndef TRIE_H
#define TRIE_H

#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

template <typename T>
class TrieNode {
 public:
  std::unordered_map<char, std::shared_ptr<TrieNode<T>>> children;
  std::string key;
  T value;

  bool empty() { return children.empty(); }
  bool is_end() { return !key.empty(); }
  bool has_child(char c) { return children.find(c) != children.end(); }
  void add_child(char c) { children[c] = std::make_shared<TrieNode<T>>(); }
  auto get_child(char c) { return children[c]; }
  void remove_child(char c) { children.erase(c); }
  void add_key(std::string k, T v) { key = k; value = v; }
  void remove_key() { key.clear(); }
};

// Define a basic Trie, with insertion and deletion abilities.
template <typename T>
class Trie {
 public:
  using NodePtr = std::shared_ptr<TrieNode<T>>;
  NodePtr root;

  Trie() : root(std::make_shared<TrieNode<T>>()) {};
  Trie(std::initializer_list<std::pair<std::string, T>>);

  std::shared_ptr<TrieNode<T>> find(std::string key);
  void insert(std::string key, T value);
  void remove(std::string key) { remove_helper(key, root, 0); }
  bool remove_helper(std::string key, NodePtr node, int depth);
  bool has_child(char c) { return root->has_child(c); }
  auto get_child(char c) { return root->get_child(c); }
};

template <typename T>
Trie<T>::Trie(std::initializer_list<std::pair<std::string, T>> list) {
  root = std::make_shared<TrieNode<T>>();

  for (auto& elem : list)
    insert(elem.first, elem.second);
}

template <typename T>
std::shared_ptr<TrieNode<T>> Trie<T>::find(std::string key) {
  auto node = root;

  for (char c : key) {
    if (node->has_child(c))
      node = node->get_child(c);
    else
      return nullptr;
  }

  return node;
}

// Insert a key into a trie.
template <typename T>
void Trie<T>::insert(std::string key, T value) {
  auto node = root;

  for (char c : key) {
    if (!node->has_child(c))
      node->add_child(c);

    node = node->get_child(c);
  }

  node->add_key(key, value);
}

// Recursive helper function that removes a key from a trie.
template <typename T>
bool Trie<T>::remove_helper(std::string key, NodePtr node, int depth) {
  if (depth == key.size()) {
    node->remove_key();
    return node->empty();
  }

  if (remove_helper(key, node->get_child(key[depth]), depth + 1)) {
    node->remove_child(key[depth]);
    return !node->is_end() && node->empty();
  }

  return false;
}

#endif
