#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cassert>

namespace DS
{
    template <class KEY, class DATA>
    class tree_node
    {
    private:
        const int index_array_size = 3;
        const int children_array_size = 4;
        /* data */
    public:
        KEY key;                                 //in case of leaf
        KEY index_array[3];                      //in case of node
        tree_node<KEY, DATA> *children_array[4]; //in case of node
        DATA *data_ptr;                          //in case of leaf
        int length;
        tree_node<KEY, DATA> *left_ptr;  //in case of leaf
        tree_node<KEY, DATA> *right_ptr; //in case of leaf

        tree_node(KEY key = KEY());
        ~tree_node();
        int insert(tree_node<KEY, DATA> *node); //returns the place in the node of the new node
        tree_node<KEY, DATA> *remove(KEY key);
    };

    template <class KEY, class DATA>
    tree_node<KEY, DATA>::tree_node(KEY key) : children_array({nullptr,
                                                               nullptr,
                                                               nullptr,
                                                               nullptr}),
                                               data_ptr(nullptr)
    {
        key = (key);
        index_array[0] = (key);
        length = (0);
    }
    template <class KEY, class DATA>
    tree_node<KEY, DATA>::~tree_node()
    {
    }

    template <class KEY, class DATA>
    int tree_node<KEY, DATA>::insert(tree_node *node)
    {
        int place_in_node;
        for (int place_in_node = 0; place_in_node < length; place_in_node++)
        {
            if (node->key < children_array[place_in_node]->key)
            {
                for (int i = length; i > place_in_node; i--)
                {
                    children_array[i] = children_array[i - 1];
                    if (i > place_in_node)
                    {
                        index_array[i - 1] = children_array[i]->key[0];
                    }
                }
            }
        }
        children_array[place_in_node] = node;
        if (place_in_node > 0)
        {
            index_array[place_in_node - 1] = node->key;
        }
        length += 1;
        assert(length <= 4);
        return place_in_node;
    }
    template <class KEY, class DATA>
    tree_node<KEY, DATA> *tree_node<KEY, DATA>::remove(KEY key)
    {
        int place_in_node;
        for (place_in_node = 0; (place_in_node < length) && (key != children_array[place_in_node]->key); place_in_node++)
            ; // find the place in the node
        if (key != children_array[place_in_node]->key)
        {
            assert(place_in_node == length);
            return nullptr; //case not found
        }
        tree_node<KEY, DATA> *removen_node = children_array[place_in_node];
        for (int i = place_in_node; i < length - 1; i++)
        {
            children_array[i] = children_array[i + 1];
        }
        children_array[length - 1] = nullptr;
        length -= 1;
        assert(length >= 2);
        return removen_node;
    }

} // namespace DS

#endif