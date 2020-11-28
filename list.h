#ifndef LIST_NODE_H
#define LIST_NODE_H

namespace DS
{
    class list_node
    {
    private:
        /* data */
    public:
        list_node(/* args */);
        ~list_node();
        *list_node next();
        *list_node prev();
        void print();
        void insert(int data);
        void remove(*list_node node) void link(*list_node prev, *list_node next);
    };

    list_node::list_node(/* args */)
    {
    }

    list_node::~list_node()
    {
    }

} // namespace DS

#endif