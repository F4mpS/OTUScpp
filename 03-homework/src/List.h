#pragma once

namespace my
{
    template <typename T, typename Allocator = std::allocator<T>>
    class List
    {
    private:
        struct Node
        {
            Node(T data, Node *next) : data(std::move(data)), next(next)
            {}
            Node *next;
            T data;

        };

        using NodeAllocator = typename Allocator::template rebind<Node>::other;

        Node *headPtr = nullptr;
        NodeAllocator alloc;
        std::size_t size = 0;

    public:
        List() {}

        ~List()
        {
            assert((size == 0 && headPtr == nullptr) || (size != 0 && headPtr != nullptr));
            while (headPtr != nullptr)
            {
                Node *ptr = headPtr;
                headPtr = headPtr->next;
                alloc.destroy(ptr);
                alloc.deallocate(ptr, 1);
            }
        }

        void Push(T value)
        {
            Node *inserted = alloc.allocate(1);
            if (headPtr == nullptr)
            {
                alloc.construct(inserted, std::move(value), headPtr);
                headPtr = inserted;
            }
            else 
            {
                Node* nodePtr = headPtr;

                while (nodePtr->next != nullptr)
                    nodePtr = nodePtr->next;

                alloc.construct(inserted, std::move(value), nodePtr->next);
                nodePtr->next = inserted;
            }
            
            size++;
        }

        class Iterator
        {
        private:
            Node* cur;
        public:
            Iterator(Node* node) : cur(node) {}

            T& operator++ () 
            {
                cur = cur->next;
                return cur->data;
            }

            bool operator== (const Iterator& it) { return cur == it.cur; }
            bool operator!= (const Iterator& it) { return cur != it.cur; }

            T& operator* () { return cur->data; }
        };

        const Iterator begin() { return Iterator(headPtr); }
        const Iterator end() 
        {
            Node* ptr = headPtr;

            while (ptr->next != nullptr)
            {
                ptr = ptr->next;
            }
            
            return Iterator(ptr->next);
        }
    };
} // namespace my
