#ifndef TREE_NODE_H
#define TREE_NODE_H

namespace DS
{
    template <class KEY, class DATA>
    class tree_node
    {
    private:
        const int index_array_size = 3;
        /* data */
    public:
        KEY key;                                 //in case of leaf
        KEY index_array[3];                      //in case of node
        tree_node<KEY, DATA> *children_array[4]; //in case of node
        DATA *data_ptr;                          //in case of leaf
        int length;

        tree_node(KEY key = KEY());
        ~tree_node();
        void insert(tree_node<KEY, DATA> *node);
    };

    template <class KEY, class DATA>
    tree_node<KEY, DATA>::tree_node(KEY key) : children_array({nullptr,
                                                               nullptr,
                                                               nullptr,
                                                               nullptr}),
                                               data_ptr(nullptr)
    {
        key(key);
        index_array[0](key);
        length(0);
    }
    template <class KEY, class DATA>
    tree_node<KEY, DATA>::~tree_node()
    {
    }

    template <class KEY, class DATA>
    void tree_node<KEY, DATA>::insert(tree_node *node)
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
    }

} // namespace DS

#endif