#include <catch2/catch_test_macros.hpp>
#include <Config/Config.hpp>

TEST_CASE("Empty config has no values") {
    config::Config cfg;

    REQUIRE_FALSE(cfg.has("graphics", "width"));
}