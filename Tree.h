#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <cassert>
namespace DS
{
    template <class KEY, class DATA>
    class Tree
    {
    private:
        tree_node<KEY, DATA> *max_leaf;
        tree_node<KEY, DATA> *root_ptr;
        tree_node<KEY, DATA> *find_node(KEY key, tree_node<KEY, DATA> *father_node);
        bool is_leaf(tree_node<KEY, DATA> *node);

    public:
        Tree();
        ~Tree();
        void insert(KEY key, DATA data);
        void remove(KEY key);
        DATA *find(KEY key);
        void traverse_print();
    };

    template <class KEY, class DATA>
    Tree<KEY, DATA>::Tree() : max_leaf(nullptr), root_ptr(nullptr)
    {
    }

    template <class KEY, class DATA>
    Tree<KEY, DATA>::~Tree()
    {
    }

    template <class KEY, class DATA>
    bool Tree<KEY, DATA>::is_leaf(tree_node<KEY, DATA> *node)
    {
        return ((node->children_array[0] == nullptr) && (assert(node->length == 0)));
    }

    template <class KEY, class DATA>
    tree_node<KEY, DATA> *Tree<KEY, DATA>::find_node(KEY key, tree_node<KEY, DATA> *father_node)
    {
        assert(father_node != nullptr);
        if (is_leaf(father_node))
        {
            if (father_node->key == key)
            {
                return father_node;
            }
            else
            {
                return nullptr;
            }
        }
        int i;
        for (i = 0; ((i < father_node->length - 1) && !(key < father_node->index_array[i])); i++)
            ;
        assert(father_node->children_array[i] != nullptr);
        return (find_node(key, father_node->children_array[i]));
    }

    template <class KEY, class DATA>
    DATA *Tree<KEY, DATA>::find(KEY key)
    {
        tree_node<KEY, DATA> *tmp_node = find_node(key, root_ptr);
        if (tmp_node == nullptr)
        {
            return nullptr;
        }
        else
        {
            return tmp_node->data_ptr;
        }
    }
} // namespace DS

#endif