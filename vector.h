#ifndef VECTOR_H
#define VECTOR_H

namespace data_stracture
{

    template <class T>
    class vecotr
    {
        struct node
        {
            T index;
            int place;
            void *data;
        };
        node *first_link;
        int length;

    public:
        vecotr<T>();
        vecotr<T>(T index);
    };

    template <class T>
    vecotr<T>::vecotr() : first_link(NULL), length(0)
    {
    }

    template <class T>
    vecotr<T>::vecotr(T index) : first_link(NULL), length(0)
    {
        first_link = new node
    }
}; // namespace data_stracture
#endif