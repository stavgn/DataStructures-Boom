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
        bool insert_node_by_ptr(tree_node<KEY, DATA> *node, tree_node<KEY, DATA> *father_node);
        void remove_node_by_ptr(tree_node<KEY, DATA> *node, tree_node<KEY, DATA> *father_node);

    public:
        Tree();
        ~Tree();
        bool insert(KEY key, DATA *data);
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
        if (father_node == nullptr)
        {
            return nullptr;
        }
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
    template <class KEY, class DATA>
    bool Tree<KEY, DATA>::insert_node_by_ptr(tree_node<KEY, DATA> *node, tree_node<KEY, DATA> *father_node)
    {
        if (father_node == nullptr)
        {
            root_ptr = node;
            max_leaf = node;
            return true;
        }

        if (is_leaf(father_node) && (father_node == root_ptr))
        {
            if (node->key == root_ptr->key)
            {
                // throw
                return false;
            }

            tree_node<KEY, DATA> *max_node;
            tree_node<KEY, DATA> *min_node;
            if (node->key < root_ptr->key)
            {
                min_node = node;
                max_node = root_ptr;
            }
            else
            {
                max_leaf = node;
                min_node = root_ptr;
                max_node = node;
            }
            max_node->left_ptr = min_node;
            min_node->right_ptr = max_node;

            tree_node<KEY, DATA> *new_father = new tree_node<KEY, DATA>(max_node->key);
            new_father->children_array[0] = min_node;
            new_father->children_array[1] = max_node;
            new_father->length = 2;
            return true;
        }

        if (is_leaf(father_node->children_array[0]))
        {
            if (find_node(node->key, father_node) != nullptr) // incase the node is already exist
            {
                return false;
            }
            int place_in_node = father_node->insert(node);
            if (place_in_node == 0)
            {
                tree_node<KEY, DATA> *old_brother_node = father_node->children_array[place_in_node + 1];
                assert(old_brother_node != nullptr);
                if (old_brother_node->left_ptr == nullptr)
                {
                    node->left_ptr = nullptr;
                }
                else
                {
                    old_brother_node->left_ptr->right_ptr = node;
                }

                old_brother_node->left_ptr = node;
                node->right_ptr = old_brother_node;
            }
            else
            {
                tree_node<KEY, DATA> *young_brother_node = father_node->children_array[place_in_node - 1];
                if (young_brother_node->right_ptr == nullptr) // the new node is the bigest leaf now
                {
                    assert(young_brother_node == max_leaf);
                    max_leaf = node;
                    node->right_ptr = nullptr;
                }
                else
                {
                    young_brother_node->right_ptr->left_ptr = node;
                }

                young_brother_node->right_ptr = node;
                node->left_ptr = young_brother_node;
            }
            return true;
        }

        else if (!is_leaf(father_node->children_array[0]))
        {
            int i;
            for (i = 0; ((i < father_node->length - 1) && !(node->key < father_node->index_array[i])); i++)
                ;
            assert(father_node->children_array[i] != nullptr);
            tree_node<KEY, DATA> *child_node = father_node->children_array[i];
            if (!insert_node_by_ptr(node, child_node))
            {
                return false;
            }
            if (child_node->length == 4) //incase we need to split
            {
                tree_node<KEY, DATA> *new_splited_node = new tree_node<KEY, DATA>(child_node->index_array[2]);
                new_splited_node->children_array[0] = child_node->children_array[2];
                new_splited_node->children_array[1] = child_node->children_array[3];
                new_splited_node->length = 2;

                child_node->children_array[2] = child_node->children_array[3] = nullptr;
                child_node->length = 2;

                father_node->insert(new_splited_node);
                return true;
            }
        }
    }
    template <class KEY, class DATA>
    bool Tree<KEY, DATA>::insert(KEY key, DATA *data)
    {
        tree_node<KEY, DATA> *new_node = new tree_node<KEY, DATA>(key);
        new_node->data_ptr = data;
        if (!insert_node_by_ptr(new_node, root_ptr))
        {
            delete new_node;
            return false;
        }
        return true;
    }
    template <class KEY, class DATA>
    void Tree<KEY, DATA>::remove_node_by_ptr(tree_node<KEY, DATA> *node, tree_node<KEY, DATA> *father_node)
    {
        assert(node != nullptr);
        if (find_node(node, root_ptr) == nullptr)
        {
            return;
        }
        if ((father_node == root_ptr) && (is_leaf(root_ptr)))
        {
            assert(root_ptr == node);
            delete node->data_ptr;
            delete node;
            root_ptr = max_leaf = nullptr;
            return;
        }
        if (is_leaf(father_node->children_array[0]))
        {
            tree_node<KEY, DATA> *removen_node = father_node->remove(node->key);
            assert(removen_node != nullptr);
            if (node->left_ptr == nullptr)
            {
                assert(node->right_ptr != nullptr);
                node->right_ptr->left_ptr = nullptr;
            }
            else if (node->right_ptr == nullptr) //That means node is the bigest leaf
            {
                assert(node->leaft_ptr != nullptr);
                assert(node = max_leaf);
                node->leaft_ptr->right_ptr = nullptr;
            }
            else
            {
                node->left_ptr->right_ptr = node->right_ptr;
                node->right_ptr->left_ptr = node->left_ptr;
            }
            delete data;
            delete node;
            return;
        }
        if (!is_leaf(father_node->children_array[0]))
        {
            int i;
            for (i = 0; ((i < father_node->length - 1) && !(node->key < father_node->index_array[i])); i++)
                ;
            assert(father_node->children_array[i] != nullptr);
            tree_node<KEY, DATA> *child_node = father_node->children_array[i];
            remove_node_by_ptr(node, child_node);
            if (child_node->length < 2)
            {
                assert(child_node->length == 1);
                /*******
                 * 
                 * 
                 * 
                 * 
                 * need to fill this part
                 * 
                 * 
                 * ***/
            }
        }
        if (root_ptr->length < 2)
        {
            assert(root_ptr->length == 1);
            assert(!is_leaf(root_ptr));
            tree_node<KEY, DATA> *child_node = root_ptr->children_array[0];
            delete root_ptr;
            root_ptr = child_node;
        }
    }

} // namespace DS

#endif