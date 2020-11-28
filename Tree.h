#ifndef TREE_H
#define TREE_H

namespace DS
{
    template <class KEY, class DATA>
    class Tree
    {
    private:
        /* data */
    public:
        Tree(/* args */);
        ~Tree();
        void insert(KEY key, DATA data);
        void remove(KEY key);
        DATA *find(KEY key);
        void traverse_print();
    };

    template <class KEY, class DATA>
    Tree<KEY, DATA>::Tree(/* args */)
    {
    }

    template <class KEY, class DATA>
    Tree<KEY, DATA>::~Tree()
    {
    }

} // namespace DS

#endif