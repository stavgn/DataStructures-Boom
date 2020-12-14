#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <cassert>

#include <iostream>
namespace DS
{
    template <class KEY, class DATA>
    class Tree
    {
    private:
        tree_node<KEY, DATA> *max_leaf;
        tree_node<KEY, DATA> *min_leaf;
        tree_node<KEY, DATA> *root_ptr;
        tree_node<KEY, DATA> *find_node(const KEY &key, tree_node<KEY, DATA> *father_node);
        bool is_leaf(tree_node<KEY, DATA> *node);
        bool insert_node_by_ptr(tree_node<KEY, DATA> *node, tree_node<KEY, DATA> *father_node);
        void remove_node_by_ptr(tree_node<KEY, DATA> *node, tree_node<KEY, DATA> *father_node);
        void balnce_node(tree_node<KEY, DATA> *unbalnced_node, tree_node<KEY, DATA> *brother_node, tree_node<KEY, DATA> *father_node, int place_in_node);
        void destroy_by_ptr(tree_node<KEY, DATA> *father_node);

    public:
        Tree();
        ~Tree();
        bool insert(const KEY &key, DATA *data); // inserts a node with data and key, return true if it was sucessfull or false if a node with the same key is alredy exists
        void remove(const KEY &key); // remove the node with the same key or do nothing incase the node wasn't found
        DATA *find(const KEY &key); //find the node with that key and returns pointer to it's data
        tree_node<KEY, DATA> *get_max_leaf(); //return's a pointer to the bigest leaf
        tree_node<KEY, DATA> *get_min_leaf(); //return's a pointer to the smallest leaf
        void printTree(); // FOR DEBUGING: prints the leafs from the bigest to the smallest 
        void treeClear(); // FOR DEBUGING: delte all the node in the tree
    };

    template <class KEY, class DATA>
    Tree<KEY, DATA>::Tree() : max_leaf(nullptr), min_leaf(nullptr), root_ptr(nullptr)
    {
    }

    template <class KEY, class DATA>
    Tree<KEY, DATA>::~Tree()
    {
        if (root_ptr == nullptr)
        {
            return;
        }
        else
        {
            destroy_by_ptr(root_ptr);
        }
    }

    template <class KEY, class DATA>
    bool Tree<KEY, DATA>::is_leaf(tree_node<KEY, DATA> *node)
    {
        return (node->children_array[0] == nullptr);
    }

    template <class KEY, class DATA>
    tree_node<KEY, DATA> *Tree<KEY, DATA>::find_node(const KEY &key, tree_node<KEY, DATA> *father_node)
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
    DATA *Tree<KEY, DATA>::find(const KEY &key)
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
            min_leaf = node;
            return true;
        }

        if (is_leaf(father_node) && (father_node == root_ptr))
        {
            if (node->key == root_ptr->key)
            {
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
                min_node = root_ptr;
                max_node = node;
            }
            min_leaf = min_node;
            max_leaf = max_node;
            max_node->left_ptr = min_node;
            min_node->right_ptr = max_node;

            tree_node<KEY, DATA> *new_father = new tree_node<KEY, DATA>(max_node->key);
            new_father->children_array[0] = min_node;
            new_father->children_array[1] = max_node;
            new_father->length = 2;
            root_ptr = new_father;
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
                if (old_brother_node->left_ptr == nullptr) //the new node is the smallest leaf now
                {
                    assert(old_brother_node == min_leaf);
                    min_leaf = node;
                    node->left_ptr = nullptr;
                }
                else
                {
                    old_brother_node->left_ptr->right_ptr = node;
                    node->left_ptr = old_brother_node->left_ptr;
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
                    node->right_ptr = young_brother_node->right_ptr;
                }

                young_brother_node->right_ptr = node;
                node->left_ptr = young_brother_node;
            }
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

                int place_inserted = father_node->insert(new_splited_node);
                father_node->index_array[place_inserted - 1] = child_node->index_array[1];
                
            }
        }
        if (root_ptr->length == 4)
        {
            tree_node<KEY, DATA> *new_splited_node = new tree_node<KEY, DATA>(root_ptr->index_array[2]);
            new_splited_node->children_array[0] = root_ptr->children_array[2];
            new_splited_node->children_array[1] = root_ptr->children_array[3];
            new_splited_node->length = 2;

            root_ptr->children_array[2] = root_ptr->children_array[3] = nullptr;
            root_ptr->length = 2;

            tree_node<KEY, DATA> *new_root = new tree_node<KEY, DATA>(root_ptr->index_array[1]);
            new_root->children_array[0] = root_ptr;
            new_root->children_array[1] = new_splited_node;
            new_root->length = 2;
            root_ptr = new_root;

            return true;
        }

        return true;
    }
    template <class KEY, class DATA>
    bool Tree<KEY, DATA>::insert(const KEY &key, DATA *data)
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
        if ((father_node == root_ptr) && (is_leaf(root_ptr)))
        {
            assert(root_ptr == node);
            delete node;
            root_ptr = max_leaf = min_leaf = nullptr;
            return;
        }
        if (is_leaf(father_node->children_array[0]))
        {
            father_node->remove(node->key);
            if (node->left_ptr == nullptr) //That means node is the smallest leaf
            {
                assert(node->right_ptr != nullptr);
                assert(node == min_leaf);
                node->right_ptr->left_ptr = nullptr;
                min_leaf = node->right_ptr;
            }
            else if (node->right_ptr == nullptr) //That means node is the bigest leaf
            {
                assert(node->left_ptr != nullptr);
                assert(node == max_leaf);
                node->left_ptr->right_ptr = nullptr;
                max_leaf = node->left_ptr;
            }
        
            else
            {
                node->left_ptr->right_ptr = node->right_ptr;
                node->right_ptr->left_ptr = node->left_ptr;
            }
            delete node;
        }
        else if (!is_leaf(father_node->children_array[0]))
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
                if (i == 0) //if the child is first born
                {
                    balnce_node(child_node, father_node->children_array[i + 1], father_node, i);
                }
                else
                {
                    assert((i == 1) || (i == 2));
                    balnce_node(child_node, father_node->children_array[i - 1], father_node, i);
                }
            }
        }
        if (root_ptr->length < 2)
        {
            assert(root_ptr->length == 1);
            assert(!is_leaf(root_ptr));
            tree_node<KEY, DATA> *child_node = root_ptr->children_array[0];
            delete root_ptr;
            root_ptr = child_node;
            return;
        }

    }

    template <class KEY, class DATA>
    void Tree<KEY, DATA>::balnce_node(tree_node<KEY, DATA> *unbalnced_node, tree_node<KEY, DATA> *brother_node, tree_node<KEY, DATA> *father_node, int place_in_node)
    {
        assert(unbalnced_node->length == 1);
        if (brother_node->length == 3) // taking from a brother
        {
            tree_node<KEY, DATA> *taken_node;
            if (place_in_node == 0) // older brother
            {
                taken_node = brother_node->children_array[0];
                unbalnced_node->insert(taken_node);
                unbalnced_node->index_array[0] = father_node->index_array[0];
                father_node->index_array[0] = brother_node->index_array[0]; // casue we are in older brother case
                brother_node->remove(taken_node->key);
            }
            else // younger brother
            {
                taken_node = brother_node->children_array[2]; //max child
                unbalnced_node->insert(taken_node);
                unbalnced_node->index_array[0] = father_node->index_array[place_in_node - 1];
                father_node->index_array[place_in_node - 1] = brother_node->index_array[1]; //max index
                brother_node->remove(taken_node->key);
            }
        }
        else // combining children
        {
            assert(brother_node->length == 2);
            tree_node<KEY, DATA> *lonly_child = unbalnced_node->children_array[0];
            brother_node->insert(lonly_child);
            //fixing indexing
            if ((place_in_node == 0)) // incase the lonly node is the youngest
            {
                brother_node->index_array[0] = father_node->index_array[0];
                if (father_node->length)
                {
                    father_node->index_array[0] = father_node->index_array[1];
                }
            }
            else if (father_node->children_array[0] == brother_node) // incase the lonly node is the the middle child and combine with the youngest
            {
                brother_node->index_array[1] = father_node->index_array[0];
                if (father_node->length)
                {
                    father_node->index_array[0] = father_node->index_array[1];
                }
            }                                                        //if we got here this mean there is 3 children
            else if (father_node->children_array[2] == brother_node) // incase the lonly node is the  middle child and combine with the eldest
            {
                brother_node->index_array[0] = father_node->index_array[1];
            }
            else if (place_in_node == 2) // incase the lonly node is the  eldest child and combine
            {
                brother_node->index_array[1] = father_node->index_array[1];
            }
            unbalnced_node->key = -1;
            father_node->remove(unbalnced_node->key);
            delete unbalnced_node;
        }
    }
    template <class KEY, class DATA>
    void Tree<KEY, DATA>::remove(const KEY &key)
    {
        tree_node<KEY, DATA> *node = find_node(key, root_ptr);
        if (node == nullptr)
        {
            return;
        }
        remove_node_by_ptr(node, root_ptr);
        assert((root_ptr == nullptr) || (is_leaf(root_ptr)) || (root_ptr->length >= 2));

    }

    template <class KEY, class DATA>
    tree_node<KEY, DATA> *Tree<KEY, DATA>::get_max_leaf()
    {
        return max_leaf;
    }
    template <class KEY, class DATA>
    tree_node<KEY, DATA> *Tree<KEY, DATA>::get_min_leaf()
    {
        return min_leaf;
    }

    template <class KEY, class DATA>
    void Tree<KEY, DATA>::destroy_by_ptr(tree_node<KEY, DATA> *father_node)
    {
        if (is_leaf(father_node))
        {
            delete father_node;
            return;
        }
        else
        {
            for (int i = 0; i < father_node->length; i++)
            {
                destroy_by_ptr(father_node->children_array[i]);
            }
            assert(father_node->length < 4);
            delete father_node;
        }
    }

    template <class KEY, class DATA>
    void Tree<KEY, DATA>::printTree()
    {
        for (tree_node<KEY, DATA> *p = max_leaf; p != nullptr; p = p->left_ptr)
        {
            assert((find(p->key) != nullptr));
            if (p->right_ptr != nullptr)
            {
                assert(*(p->data_ptr) < *(p->right_ptr->data_ptr));
            }
            std::cout << *(p->data_ptr) << "   ";
        }
    }

    template <class KEY, class DATA>
    void Tree<KEY, DATA>::treeClear()
    {
        if (root_ptr == nullptr)
        {
            return;
        }
        destroy_by_ptr(root_ptr);
        root_ptr = max_leaf = min_leaf = nullptr;
    }

} // namespace DS

#endif