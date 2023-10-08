#pragma once

#include <cstddef>
#include <concepts>
#include <unordered_map>
#include <tuple>

class Key
{
public:
    std::size_t a;
    std::size_t b;

    Key(std::size_t a, std::size_t b) : a(a), b(b) {}

    bool operator== (const Key& other) const
    {
        return a == other.a && b == other.b;
    }
};

// bool operator== (const Key& left, const Key& right)
// {
//     return left == right;
// }

class HashGenerator
{
public:
    std::size_t operator()(const Key& key) const
    {
        return key.a + key.b * 2;
    }
};

template <std::integral T, T defaultValue>
class Matrix
{
private:
    class MatrixImpl
    {
    public:
        using matrix_iterator = typename std::unordered_map<Key, T, HashGenerator>::iterator;

        MatrixImpl() = default;
        ~MatrixImpl() = default;

        T Get(std::size_t rowIndex, std::size_t columnIndex)
        {
            auto it = matrix.find(Key(rowIndex, columnIndex));
            return it == matrix.end() ? defaultValue : it->second;
        }

        void Set(std::size_t rowIndex, std::size_t columnIndex, T value)
        {
            if (value != defaultValue) {
                matrix[Key(rowIndex, columnIndex)] = value;
            }
            else {
                matrix.erase(Key(rowIndex, columnIndex));
            }
        }

        std::size_t Size()
        {
            return matrix.size();
        }

        matrix_iterator begin()
        {
            return matrix.begin();
        }

        matrix_iterator end()
        {
            return matrix.end();
        }
    private:
        std::unordered_map<Key, T, HashGenerator> matrix;
    };

    class Column
    {
    public:
        Column(std::size_t rowIndex, std::size_t columnIndex, MatrixImpl& matrix) : rowIndex(rowIndex), columnIndex(columnIndex), matrix(matrix) {}

        ~Column() = default;

        Column& operator= (T value)
        {
            matrix.Set(rowIndex, columnIndex, value);
            return *this;
        }

        bool operator==(T value) const
        {
            return matrix.Get(rowIndex, columnIndex) == value;
        }

        bool operator!=(T value) const
        {
            return !operator==(value);
        }

        operator T()
        {
            return matrix.Get(rowIndex, columnIndex);
        }

        std::size_t rowIndex;
        std::size_t columnIndex;
        MatrixImpl& matrix;
    };

    class Row
    {
    public:
        Row(std::size_t rowIndex, MatrixImpl& matrix) : rowIndex(rowIndex), matrix(matrix) {}

        ~Row() = default;

        Column operator[] (std::size_t columnIndex)
        {
            return Column(rowIndex, columnIndex, matrix);
        }

        std::size_t rowIndex;
        MatrixImpl& matrix;
    };

    class iterator
    {
    public:
        using value_type = std::tuple<std::size_t, std::size_t, T>;

        iterator(typename MatrixImpl::matrix_iterator iter) : iter(iter) {}

        value_type operator*()
        {
            return std::make_tuple(iter->first.a, iter->first.b, iter->second);
        }

        iterator& operator++()
        {
            ++iter;
            return *this;
        }

        bool operator==(const iterator& other)
        {
            return (iter == other.iter);
        }

        bool operator!=(const iterator& other)
        {
            return !(*this == other);
        }

    private:
        typename MatrixImpl::matrix_iterator iter;
    };
public:
    Matrix() = default;
    ~Matrix() = default;

    Row operator[] (std::size_t rowIndex)
    {
        return Row(rowIndex, matrix);
    }

    std::size_t Size()
    {
        return matrix.Size();
    }

    iterator begin()
    {
        return iterator(matrix.begin());
    }

    iterator end()
    {
        return iterator(matrix.end());
    }

    MatrixImpl matrix;
};