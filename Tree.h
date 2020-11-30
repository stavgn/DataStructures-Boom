#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
namespace DS
{
    template <class KEY, class DATA>
    class Tree
    {
    private:
        tree_node<KEY, DATA> *max_leaf;
        tree_node<KEY, DATA> *root_ptr;
        DATA *find_father(KEY key);
        bool is_leaf(tree_node<KEY, DATA> *node);

    public:
        Tree(/* args */);
        ~Tree();
        void insert(KEY key, DATA data);
        void remove(KEY key);
        DATA *find(KEY key);
        void traverse_print();
    };

    template <class KEY, class DATA>
    Tree<KEY, DATA>::Tree(/* args */) : max_leaf(nullptr), root_ptr(nullptr)
    {
    }

    template <class KEY, class DATA>
    Tree<KEY, DATA>::~Tree()
    {
    }

    template <class KEY, class DATA>
    bool Tree<KEY, DATA>::is_leaf(tree_node<KEY, DATA> *node)
    {
        return (node->length == 1);
    }
} // namespace DS

#endif