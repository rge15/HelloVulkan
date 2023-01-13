#include "commonIncludes.hpp"

template<typename T>
using UniqPtr = std::unique_ptr<T>;

template<typename... T>
using Vector = std::vector<T...>;