#pragma

#ifndef __UTILS_GNUMERICAL__
#define __UTILS_GNUMERICAL__

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace gn {
    template <typename T>
    class Utils {
        public:
        template <typename type>
        bool isCustomCheckType() {
            return std::is_same<T, type>::value;
        }
        static constexpr bool isNumerical() {
            return std::is_arithmetic<T>::value;
        }
    };
}

#endif