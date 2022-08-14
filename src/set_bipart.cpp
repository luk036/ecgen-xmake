#include <cassert>
#include <cctype>
#include <cstdio>
#include <ecgen/set_partition.hpp>
#include <functional>
#include <utility>

namespace ecgen {

    using namespace cppcoro;
    using ret_t = size_t;

    inline auto Move(size_t x) -> recursive_generator<ret_t> { co_yield x; }

    // The lists S(n,k,0) and S(n,k,1) satisfy the following properties.
    // 1. Successive RG sequences differ in exactly one position.
    // 2. first(S(n,k,0)) = first(S(n,k,1)) = 0^{n-k}0123...(k-1)
    // 3. last(S(n,k,0)) = 0^{n-k}12...(k-1)0
    // 4. last(S(n,k,1)) = 012...(k-1)0^{n-k}
    // Note that first(S'(n,k,p)) = last(S(n,k,p))

    inline auto GEN0_even(size_t n) -> recursive_generator<ret_t>;
    inline auto GEN1_even(size_t n) -> recursive_generator<ret_t>;
    inline auto NEG1_even(size_t n) -> recursive_generator<ret_t>;

    /**
     * @brief Set the bipart gen object
     *
     * @param n
     * @return recursive_generator<ret_t>
     */
    auto set_bipart_gen(size_t n) -> recursive_generator<ret_t> { co_yield GEN0_even(n); }

    /**
     * @brief S(n,k,0) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    inline auto GEN0_even(size_t n) -> recursive_generator<ret_t> {
        if (n < 3) {
            co_return;
        }
        co_yield Move(n - 1);
        co_yield GEN1_even(n - 1);  // S(n-1, k, 1).(k-1)
        co_yield Move(n);
        co_yield NEG1_even(n - 1);  // S'(n-1, k, 1).(k-2)
    }

    /**
     * @brief S(n, k, 1) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    inline auto GEN1_even(size_t n) -> recursive_generator<ret_t> {
        if (n < 3) {
            co_return;
        }
        co_yield Move(2);
        co_yield NEG1_even(n - 1);
        co_yield Move(n);
        co_yield GEN1_even(n - 1);
    }

    /**
     * @brief S'(n, k, 1) even k
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    inline auto NEG1_even(size_t n) -> recursive_generator<ret_t> {
        if (n < 3) {
            co_return;
        }
        co_yield NEG1_even(n - 1);
        co_yield Move(n);
        co_yield GEN1_even(n - 1);
        co_yield Move(2);
    }
}  // namespace ecgen
