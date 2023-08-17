#pragma once

namespace my
{
    template <typename T, std::size_t size>
    class Allocator
    {
    private:
        T *memoryPool = nullptr;
        std::size_t nAllocated = 0;
        std::array<bool, size> memoryMap{0, 0, 0, 0, 0};

    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;

        Allocator()
        {
            memoryPool = static_cast<T *>(::operator new(size * sizeof(T)));
            if (memoryPool == nullptr)
                throw std::bad_alloc();
            memoryMap.fill(false);
        }
        template <class U>
        Allocator(const Allocator<U, size> &a)
        {
            // std::cout << "Allocator copy ctor!" << std::endl;
            // memoryPool = static_cast<T *>(::operator new(size * sizeof(T)));
            // if (memoryPool == nullptr)
            //     throw std::bad_alloc();
            // memoryMap.fill(false);
            // std::cout << "Allocator END copy ctor!" << std::endl;
        }

        ~Allocator()
        {
            ::operator delete(memoryPool);
        }

        T *allocate(std::size_t n)
        {
            if (size - nAllocated < n)
                throw std::bad_alloc();

            std::size_t from = 0, to = 0;
            for (std::size_t i = 0; i < size; ++i)
            {
                if (memoryMap[i])
                    continue;
                std::size_t j = i + 1;
                for (; j < size && !memoryMap[j] && j - i + 1 <= n; ++j)
                {
                }
                if (j - i == n)
                {
                    from = i;
                    to = j;
                    break;
                }
            }
            if (from == 0 && to == 0)
                throw std::bad_alloc();

            for (std::size_t i = from; i < to; ++i)
                memoryMap[i] = true;
            nAllocated += n;

            return memoryPool + from;
        }

        void deallocate(T *p, std::size_t n)
        {
            assert(n <= nAllocated);
            std::size_t from = p - memoryPool;
            assert(from + n <= size);

            for (std::size_t i = 0; i < n; ++i, ++p)
                memoryMap[from + i] = false;

            nAllocated -= n;
        }

        template <class Up, class... Args>
        void construct(Up *p, Args &&...args)
        {
            new ((void*)p) Up(std::forward<Args>(args)...);
        }

        void destroy(pointer p)
        {
            p->~T();
        }

        template <class U>
        struct rebind
        {
            using other = Allocator<U, size>;
        };
    };
} // namespace my
