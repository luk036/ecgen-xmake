#include <doctest/doctest.h>

#include <ecgen/set_partition.hpp>

TEST_CASE("set bipartition") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_bipart_gen(5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd2<5>());
}
