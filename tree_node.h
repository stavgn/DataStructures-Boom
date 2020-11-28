#ifndef TREE_NODE_H
#define TREE_NODE_H

namespace DS
{
    template <class KEY, class DATA>
    class tree_node
    {
    private:
        const int key_array_size = 3;
        /* data */
    public:
        KEY key[3];
        tree_node<KEY, DATA> *children_array[4];
        DATA *data_ptr;
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
        key[0](key);
        length(1);
    }
    template <class KEY, class DATA>
    tree_node<KEY, DATA>::~tree_node()
    {
    }

    template <class KEY, class DATA>
    void tree_node<KEY, DATA>::insert(tree_node *node)
    {
        for (int place_in_node = 0; place_in_node < length - 1; place_in_node++)
        {
            if (node->key[0] < key[place_in_node])
            {
                for (int i = length - 1; i > place_in_node; i--)
                {
                    children_array[i] = children_array[i - 1];
                    if (i < key_array_size)
                    {
                        key[i] = key[i - 1];
                    }
                }
                children_array[place_in_node] = node;
                key[place_in_node] = children_array[place_in_node + 1]->key[0];
            }
        }
    }

} // namespace DS

#endif