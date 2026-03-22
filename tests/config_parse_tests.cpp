#include <catch2/catch_test_macros.hpp>
#include <Config/Config.hpp>
#include <sstream>

TEST_CASE("Empty config has no values")
{
    std::istringstream input("");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE_FALSE(cfg.has("graphics", "width"));
}

TEST_CASE("Parser reads simple key value")
{
    std::istringstream input(R"(
[graphics]
width=1280
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.has("graphics", "width"));
    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Parser reads multiple keys in a section")
{
    std::istringstream input(R"(
[graphics]
width=1280
height=720
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
    REQUIRE(cfg.getInt("graphics","height",0) == 720);
}

TEST_CASE("Parser reads multiple sections")
{
    std::istringstream input(R"(
[graphics]
width=1280

[audio]
volume=80
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
    REQUIRE(cfg.getInt("audio","volume",0) == 80);
}

TEST_CASE("Parser ignores spaces around keys and values")
{
    std::istringstream input(R"(
[graphics]
width = 1280
height = 720
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
    REQUIRE(cfg.getInt("graphics","height",0) == 720);
}

TEST_CASE("Parser ignores empty lines")
{
    std::istringstream input(R"(

[graphics]

width=1280

)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Missing key returns default value")
{
    std::istringstream input(R"(
[graphics]
width=1280
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","height",720) == 720);
}

TEST_CASE("Boolean values are parsed correctly")
{
    std::istringstream input(R"(
[graphics]
fullscreen=true
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getBool("graphics","fullscreen",false) == true);
}

TEST_CASE("Parser ignores comments")
{
    std::istringstream input(R"(
# graphics config
[graphics]

width=1280 ; screen width
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Inline comments are removed from values")
{
    std::istringstream input(R"(
[graphics]
width=1280 ; screen width
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getString("graphics","width","") == "1280");
}

TEST_CASE("Parser handles spaces before section")
{
    std::istringstream input(R"(
    [graphics]
    width=1280
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Parser trims section names")
{
    std::istringstream input(R"(
[  graphics  ]
width=1280
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Parser reads string values")
{
    std::istringstream input(R"(
[app]
name=ConfigTool
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getString("app","name","") == "ConfigTool");
}

TEST_CASE("Boolean values support numeric format")
{
    std::istringstream input(R"(
[graphics]
fullscreen=1
vsync=0
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getBool("graphics","fullscreen",false) == true);
    REQUIRE(cfg.getBool("graphics","vsync",true) == false);
}

TEST_CASE("Parser handles empty section")
{
    std::istringstream input(R"(
[graphics]

[audio]
volume=80
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("audio","volume",0) == 80);
}

TEST_CASE("Last key definition wins")
{
    std::istringstream input(R"(
[graphics]
width=800
width=1280
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Parser ignores invalid lines")
{
    std::istringstream input(R"(
[graphics]
invalid_line
width=1280
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE(cfg.getInt("graphics","width",0) == 1280);
}

TEST_CASE("Invalid boolean value throws")
{
    std::istringstream input(R"(
[graphics]
fullscreen=maybe
)");

    config::Config cfg;
    cfg.parse(input);

    REQUIRE_THROWS(cfg.getBool("graphics","fullscreen",false));
}