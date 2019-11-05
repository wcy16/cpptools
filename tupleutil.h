#pragma once

#include <tuple>
#include <variant>
#include <stdexcept>

template <size_t N, typename... T>
std::variant<T...> getN(std::tuple<T...>& t, int pos)
{
    if constexpr (N == std::tuple_size<std::tuple<T...>>::value)
    {
        throw std::out_of_range("tuple index out of range");
    }
    else
    {
        if (N == pos)
            return std::get<N>(t);
        else
            return getN<N + 1, T...>(t, pos);
    }
}

template <typename Ty, typename... T>
void get(std::tuple<T...>& t, int pos, Ty& val)
{
    if (pos < 0 || pos >= std::tuple_size<std::tuple<T...>>::value)
        throw std::out_of_range("tuple index out of range");

    auto v = getN<0, T...>(t, pos);
    val = std::get<Ty>(v);
}