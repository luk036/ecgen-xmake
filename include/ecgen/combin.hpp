#pragma once

// #include <algorithm>                        // for fill_n
#include <cppcoro/recursive_generator.hpp>  // for recursive_generator
#include <type_traits>                      // for integral_constant
#include <utility>                          // for pair

namespace ecgen {

    /**
     * @brief EMK (GEN)
     *
     * @param[in] n
     * @param[in] k
     * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
     */
    extern auto EMK_gen(size_t n, size_t k)
        -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;

    /**
     * @brief EMK (NEG)
     *
     * @param[in] n
     * @param[in] k
     * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
     */
    extern auto EMK_neg(size_t n, size_t k)
        -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;

    /**
     * @brief Generate all combinations in reverse order by homogeneous
     * revolving-door
     *
     * @tparam Container
     * @param[in] n
     * @param[in] k
     * @param[in] lst
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> auto EMK(size_t n, size_t k, Container& lst)
        -> cppcoro::generator<Container&> {
        // auto lst = Container(n, 0);
        // std::fill_n(lst.begin(), k, 1);
        co_yield lst;
        for (auto [x, y] : EMK_gen(n, k)) {
            auto temp = lst[x];  // swap
            lst[x] = lst[y];
            lst[y] = temp;
            co_yield lst;
        }
    }

    /**
     * @brief The number of combinations
     *
     * @tparam N
     * @tparam K
     * @return constexpr auto
     */
    template <size_t N, size_t K> constexpr auto Combination() {
        if constexpr (K >= N || K == 0) {
            return std::integral_constant<size_t, 1U>{};
        } else {
            return std::integral_constant<size_t,
                                          Combination<N - 1, K - 1>() + Combination<N - 1, K>()>{};
        }
    }

}  // namespace ecgen