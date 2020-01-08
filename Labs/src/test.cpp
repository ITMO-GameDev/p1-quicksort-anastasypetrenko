#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <algorithm>

#include "catch.hpp"
#include "sort.h"


template< typename T>
bool VectorEqual(const std::vector<T>& v1, const std::vector<T>& v2) {
    return v1.size() == v2.size() && std::equal(v1.begin(), v1.end(), v2.begin());
}

TEST_CASE( "sort test", "[basic]" ) {
    auto comp = std::less<int>();

    SECTION("empty") {
        std::vector<int> v;
        anastasy_sort(v.begin(), v.end(), comp);
        REQUIRE(VectorEqual(v, {}));
    }

    SECTION("one value") {
        std::vector<int> v = {1};
        anastasy_sort(v.begin(), v.end(), comp);
        REQUIRE(VectorEqual(v, {1}));
    }

    SECTION("two value(right order)") {
        std::vector<int> v = {1, 2};
        anastasy_sort(v.begin(), v.end(), comp);
        REQUIRE(VectorEqual(v, {1, 2}));
    }

    SECTION("two value(wrong order)") {
        std::vector<int> v = {2, 1};
        anastasy_sort(v.begin(), v.end(), comp);
        REQUIRE(VectorEqual(v, {1, 2}));
    }

    SECTION("many equal value") {
        std::vector<int> v = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        anastasy_sort(v.begin(), v.end(), comp);
        REQUIRE(VectorEqual(v, {1, 1, 1, 1, 1, 1, 1, 1, 1}));
    }

    SECTION("reversed order") {
        std::vector<int> v = {5, 4, 3, 2, 1};
        anastasy_sort(v.begin(), v.end(), comp);
        REQUIRE(VectorEqual(v, {1, 2, 3, 4, 5}));
    }
}
