#ifndef __GNUMERICAL_HPP__
#define __GNUMERICAL_HPP__

#include <iostream>
#include <type_traits>
#include <array>
#include "gnarray.hpp"

namespace MLP
{
    template <typename T, size_t Size, size_t... Sizes>
    class GNumerical
    {
    private:
        using NdarrayType = Ndarray<T, Size, Sizes...>;
        using NdarrayRef = const Ndarray<T, Size, Sizes...> &;

        // data member
        NdarrayType ndarray;

    public:
        // Constructors
        template <typename... Args>
        GNumerical(Args &&...args) : ndarray(std::forward<Args>(args)...) {}

        // Comparison operators
        bool operator==(const GNumerical &other) const { return ndarray == other.ndarray; }
        bool operator!=(const GNumerical &other) const { return !(*this == other); }

        // Arithmetic operators
        GNumerical operator+(const GNumerical &other) const
        {
            static_assert(std::is_arithmetic<T>::value, "T must be numerical for implementing arithmetic operators.");
            return GNumerical(ndarray + other.ndarray);
        }

        // Getter method
        NdarrayType getNdarray() const { return ndarray; }

        // Output stream operator for GNumerical
        friend std::ostream &operator<<(std::ostream &os, const GNumerical<T, Size, Sizes...> &gn)
        {
            os << gn.ndarray;
            return os;
        }

        // method
        constexpr size_t ndim() const
        {
            return sizeof...(Sizes) + 1;
        }
        constexpr size_t size() const
        {
            if constexpr (sizeof...(Sizes) == 0)
            {
                return Size;
            }
            else
            {
                return Size * (... * Sizes);
            }
        }
        constexpr std::array<size_t, sizeof...(Sizes) + 1> shape() const
        {
            return {Size, Sizes...};
        }
    };

    // Output stream operator for std::array<size_t>
    template <typename T, size_t Size>
    std::ostream &operator<<(std::ostream &os, const std::array<T, Size> &array)
    {
        os << "{";
        for (size_t i = 0; i < Size; i++)
        {
            os << array[i];
            if (i < Size - 1)
            {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }

} /* namespace MLP */

#endif
