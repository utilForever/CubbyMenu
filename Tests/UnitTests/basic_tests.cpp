#include "doctest_proxy.hpp"

#include <CubbyMenu/CubbyMenu.hpp>

#include <sstream>

void option0(std::vector<std::string> const&)
{
    std::cout << "Option 0 is called!\n";
}

void option1(std::vector<std::string> const&)
{
    std::cout << "Option 1 is called!\n";
}

void option2(std::vector<std::string> const&)
{
    std::cout << "Option 2 is called!\n";
}

TEST_CASE("CubbyMenu - basic tests")
{
    SUBCASE("Simple menu without callback")
    {
        CubbyMenu::Menu menu;

        REQUIRE_NOTHROW(menu.add_item("Option 0"));
        REQUIRE_NOTHROW(menu.add_item("Option 1"));
        REQUIRE_NOTHROW(menu.add_item("Option 2"));
    }

    SUBCASE("Simple menu with header")
    {
        CubbyMenu::Menu menu;

        menu.add_header("Header");

        REQUIRE_NOTHROW(menu.add_item("Option 0"));
        REQUIRE_NOTHROW(menu.add_item("Option 1"));
        REQUIRE_NOTHROW(menu.add_item("Option 2"));
    }

    SUBCASE("Simple menu with function callback")
    {
        CubbyMenu::Menu menu;

        REQUIRE_NOTHROW(menu.add_item("Option 0", &option0));
        REQUIRE_NOTHROW(menu.add_item("Option 1", &option1));
        REQUIRE_NOTHROW(menu.add_item("Option 2", &option2));
    }

    SUBCASE("Simple menu with lambda callback")
    {
        CubbyMenu::Menu menu;

        REQUIRE_NOTHROW(menu.add_item(
            "Option 0", [](std::vector<std::string> const&) { std::cout << "Option 0 is called!\n"; }));
        REQUIRE_NOTHROW(menu.add_item(
            "Option 1", [](std::vector<std::string> const&) { std::cout << "Option 1 is called!\n"; }));
        REQUIRE_NOTHROW(menu.add_item(
            "Option 2", [](std::vector<std::string> const&) { std::cout << "Option 2 is called!\n"; }));
    }

    SUBCASE("Input option")
    {
        CubbyMenu::Menu menu;

        REQUIRE_NOTHROW(menu.add_item(
            "Option 0", [](std::vector<std::string> const&) { std::cout << "Option 0 is called!\n"; }));
        REQUIRE_NOTHROW(menu.add_item(
            "Option 1", [](std::vector<std::string> const&) { std::cout << "Option 1 is called!\n"; }));
        REQUIRE_NOTHROW(menu.add_item(
            "Option 2", [](std::vector<std::string> const&) { std::cout << "Option 2 is called!\n"; }));

        std::stringbuf test_input("1", std::ios_base::in);
        std::stringbuf test_output(std::ios_base::out);
        std::streambuf* const cin_buf = std::cin.rdbuf(&test_input);
        std::streambuf* const cout_buf = std::cout.rdbuf(&test_output);

        menu.print();

        std::cout.rdbuf(cout_buf);
        std::cin.rdbuf(cin_buf);

        REQUIRE(test_output.str() == "0. Option 0\n1. Option 1\n2. Option 2\n>> Option 1 is called!\n");
    }
}