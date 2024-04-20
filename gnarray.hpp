#pragma once

#include <iostream>
#include <array>
#include <iomanip>

namespace MLP
{
    template <typename T, size_t... Sizes>
    class Ndarray;

    template <typename T, size_t Size>
    class Ndarray<T, Size>
    {
    private:
        std::array<T, Size> data;

    public:
        // Default constructor
        Ndarray() : data({}) {}

        // Constructor to initialize all elements with a specific value
        explicit Ndarray(T value) : data({}) { data.fill(value); }

        // Constructor to initialize from an std::array
        Ndarray(const std::array<T, Size> &arr) : data(arr) {}

        // Copy constructor
        Ndarray(const Ndarray &other) : data(other.data) {}

        // Move constructor
        Ndarray(Ndarray &&other) noexcept : data(std::move(other.data)) {}

        // Assignment Operators
        Ndarray &operator=(const Ndarray &other)
        {
            data = other.data;
            return *this;
        }
        Ndarray &operator=(Ndarray &&other) noexcept
        {
            data = std::move(other.data);
            return *this;
        }

        // Equality Operators
        bool operator==(const Ndarray &other) const { return data == other.data; }
        bool operator!=(const Ndarray &other) const { return !(*this == other); }

        // Relational Operators
        bool operator<(const Ndarray &other) const { return data < other.data; }
        bool operator>(const Ndarray &other) const { return other < *this; }
        bool operator<=(const Ndarray &other) const { return !(*this > other); }
        bool operator>=(const Ndarray &other) const { return !(*this < other); }

        // Access Operators
        T &operator[](size_t index) { return data[index]; }
        const T &operator[](size_t index) const { return data[index]; }

        // Compound Assignment Operators
        Ndarray &operator+=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] += other.data[i];
            return *this;
        }
        Ndarray &operator-=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] -= other.data[i];
            return *this;
        }
        Ndarray &operator*=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] *= other.data[i];
            return *this;
        }
        Ndarray &operator/=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] /= other.data[i];
            return *this;
        }
        Ndarray &operator%=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] %= other.data[i];
            return *this;
        }
        Ndarray &operator^=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] ^= other.data[i];
            return *this;
        }
        Ndarray &operator|=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] |= other.data[i];
            return *this;
        }
        Ndarray &operator&=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] &= other.data[i];
            return *this;
        }

        // Increment and Decrement Operators
        Ndarray &operator++()
        {
            for (auto &val : data)
                ++val;
            return *this;
        }
        Ndarray &operator--()
        {
            for (auto &val : data)
                --val;
            return *this;
        }

        // Size Function
        size_t size() const { return Size; }

        // Output Function
        void print(std::ostream &os, int depth = 0) const
        {
            os << "[";
            for (size_t i = 0; i < Size; ++i)
            {
                if (i > 0)
                    os << ", ";
                os << data[i];
            }
            os << "]";
        }
        // Output Stream Operator
        friend std::ostream &operator<<(std::ostream &os, const Ndarray<T, Size> &arr)
        {
            arr.print(os);
            return os;
        }
    };

    // Binary Arithmetic Operators
    template <typename T, size_t Size>
    Ndarray<T, Size> operator+(const Ndarray<T, Size> &lhs, const Ndarray<T, Size> &rhs)
    {
        Ndarray<T, Size> result;
        for (size_t i = 0; i < Size; ++i)
            result[i] = lhs[i] + rhs[i];
        return result;
    }

    template <typename T, size_t Size>
    Ndarray<T, Size> operator-(const Ndarray<T, Size> &lhs, const Ndarray<T, Size> &rhs)
    {
        Ndarray<T, Size> result;
        for (size_t i = 0; i < Size; ++i)
            result[i] = lhs[i] - rhs[i];
        return result;
    }

    template <typename T, size_t Size>
    Ndarray<T, Size> operator*(const Ndarray<T, Size> &lhs, const Ndarray<T, Size> &rhs)
    {
        Ndarray<T, Size> result;
        for (size_t i = 0; i < Size; ++i)
            result[i] = lhs[i] * rhs[i];
        return result;
    }

    template <typename T, size_t Size>
    Ndarray<T, Size> operator/(const Ndarray<T, Size> &lhs, const Ndarray<T, Size> &rhs)
    {
        Ndarray<T, Size> result;
        for (size_t i = 0; i < Size; ++i)
            result[i] = lhs[i] / rhs[i];
        return result;
    }

    template <typename T, size_t Size>
    Ndarray<T, Size> operator%(const Ndarray<T, Size> &lhs, const Ndarray<T, Size> &rhs)
    {
        Ndarray<T, Size> result;
        for (size_t i = 0; i < Size; ++i)
            result[i] = lhs[i] % rhs[i];
        return result;
    }

    //// N DIMENSIONAL ARRAY

    // Recursive case: For n-dimensional arrays
    template <typename T, size_t Size, size_t... Sizes>
    class Ndarray<T, Size, Sizes...>
    {
    private:
        std::array<Ndarray<T, Sizes...>, Size> data;

    public:
        // Constructors
        // Default constructor
        Ndarray() : data({}) {}

        // Constructor to initialize all elements with a specific value
        explicit Ndarray(T value) : data()
        {
            for (auto &element : data)
                element = Ndarray<T, Sizes...>(value);
        }

        // Copy constructor
        Ndarray(const Ndarray &other) : data(other.data) {}

        // Move constructor
        Ndarray(Ndarray &&other) noexcept : data(std::move(other.data)) {}

        // Assignment Operators
        Ndarray &operator=(const Ndarray &other)
        {
            if (this != &other)
                data = other.data;
            return *this;
        }
        Ndarray &operator=(Ndarray &&other) noexcept
        {
            if (this != &other)
                data = std::move(other.data);
            return *this;
        }

        // Comparison Operators
        bool operator==(const Ndarray &other) const
        {
            return data == other.data;
        }
        bool operator!=(const Ndarray &other) const
        {
            return !(*this == other);
        }
        bool operator<(const Ndarray &other) const
        {
            return data < other.data;
        }
        bool operator>(const Ndarray &other) const
        {
            return data > other.data;
        }
        bool operator<=(const Ndarray &other) const
        {
            return data <= other.data;
        }
        bool operator>=(const Ndarray &other) const
        {
            return data >= other.data;
        }

        // Arithmetic Operators
        Ndarray operator+(const Ndarray &other) const
        {
            Ndarray result;
            for (size_t i = 0; i < Size; ++i)
                result.data[i] = data[i] + other.data[i];
            return result;
        }
        Ndarray operator-(const Ndarray &other) const
        {
            Ndarray result;
            for (size_t i = 0; i < Size; ++i)
                result.data[i] = data[i] - other.data[i];
            return result;
        }
        Ndarray operator*(const Ndarray &other) const
        {
            Ndarray result;
            for (size_t i = 0; i < Size; ++i)
                result.data[i] = data[i] * other.data[i];
            return result;
        }
        Ndarray operator/(const Ndarray &other) const
        {
            Ndarray result;
            for (size_t i = 0; i < Size; ++i)
                result.data[i] = data[i] / other.data[i];
            return result;
        }
        Ndarray operator%(const Ndarray &other) const
        {
            Ndarray result;
            for (size_t i = 0; i < Size; ++i)
                result.data[i] = data[i] % other.data[i];
            return result;
        }

        // Compound Assignment Operators
        Ndarray &operator+=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] += other.data[i];
            return *this;
        }
        Ndarray &operator-=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] -= other.data[i];
            return *this;
        }
        Ndarray &operator*=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] *= other.data[i];
            return *this;
        }
        Ndarray &operator/=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] /= other.data[i];
            return *this;
        }
        Ndarray &operator%=(const Ndarray &other)
        {
            for (size_t i = 0; i < Size; ++i)
                data[i] %= other.data[i];
            return *this;
        }

        // Subscript Operator
        Ndarray<T, Sizes...> &operator[](size_t index)
        {
            return data[index];
        }
        const Ndarray<T, Sizes...> &operator[](size_t index) const
        {
            return data[index];
        }

        // Size Function
        size_t size() const
        {
            return Size;
        }

        // Print Function
        void print(std::ostream &os, int depth = 0) const
        {
            os << "[";
            for (size_t i = 0; i < Size; ++i)
            {
                if (i > 0)
                    os << "," << std::endl;
                data[i].print(os, depth + 1);
            }
            os << "]";
        }
    };

    // Output Operator
    template <typename T, size_t... Sizes>
    std::ostream &operator<<(std::ostream &os, const Ndarray<T, Sizes...> &arr)
    {
        arr.print(os);
        return os;
    }

    // Arithmetic Operator Overloads
    template <typename T, size_t Size, size_t... Sizes>
    Ndarray<T, Size, Sizes...> operator+(const Ndarray<T, Size, Sizes...> &lhs, const Ndarray<T, Size, Sizes...> &rhs)
    {
        return lhs + rhs;
    }
    template <typename T, size_t Size, size_t... Sizes>
    Ndarray<T, Size, Sizes...> operator-(const Ndarray<T, Size, Sizes...> &lhs, const Ndarray<T, Size, Sizes...> &rhs)
    {
        return lhs - rhs;
    }
    template <typename T, size_t Size, size_t... Sizes>
    Ndarray<T, Size, Sizes...> operator*(const Ndarray<T, Size, Sizes...> &lhs, const Ndarray<T, Size, Sizes...> &rhs)
    {
        return lhs * rhs;
    }
    template <typename T, size_t Size, size_t... Sizes>
    Ndarray<T, Size, Sizes...> operator/(const Ndarray<T, Size, Sizes...> &lhs, const Ndarray<T, Size, Sizes...> &rhs)
    {
        return lhs / rhs;
    }
    template <typename T, size_t Size, size_t... Sizes>
    Ndarray<T, Size, Sizes...> operator%(const Ndarray<T, Size, Sizes...> &lhs, const Ndarray<T, Size, Sizes...> &rhs)
    {
        return lhs % rhs;
    }

} // namespace MLP
