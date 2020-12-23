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

    SUBCASE("Sub Menu")
    {
        auto f{ [](auto const& e) {
            return [e](std::vector<std::string> const&) { std::cout << e << std::endl; };
        } };

        std::stringbuf test_input("2\n1\n3", std::ios_base::in);
        std::stringbuf test_output(std::ios_base::out);
        std::streambuf* const cin_buf = std::cin.rdbuf(&test_input);
        std::streambuf* const cout_buf = std::cout.rdbuf(&test_output);

        REQUIRE_NOTHROW(
            CubbyMenu::Menu{ "MyMenu" }
                .add_header_ex("Main Menu")
                .add_item_ex("Option 0", f("Option 0 is called."))
                .add_item_ex("Option 1", f("Option 1 is called."))
                .add_item_ex(
                    CubbyMenu::Menu{ "Sub Menu" }
                        .add_header_ex("Sub Menu")
                        .add_item_ex("Option 2.0", f("Option 2.0 is called."))
                        .add_item_ex(
                            CubbyMenu::Menu{ "Sub Sub Menu" }
                                .add_header_ex("Sub Sub Menu")
                                .add_item_ex("Option 2.1.0",
                                             f("Option 2.1.0 is called."))
                                .add_item_ex("Option 2.1.1",
                                             f("Option 2.1.1 is called."))
                                .add_item_ex("Option 2.1.2",
                                             f("Option 2.1.2 is called."))
                                .add_item_ex("Option 2.1.3",
                                             f("Option 2.1.3 is called."))
                                .add_item_ex("Option 2.1.4",
                                             f("Option 2.1.4 is called.")))
                        .add_item_ex("Option 2.2", f("Option 2.2 is called."))
                        .add_item_ex("Option 2.3", f("Option 2.3 is called.")))
                .add_item_ex("Option 3", f("Option 3 is called."))
                .print());

        std::cout.rdbuf(cout_buf);
        std::cin.rdbuf(cin_buf);

        REQUIRE(test_output.str() == R"~(Main Menu
0. Option 0
1. Option 1
2. Sub Menu
3. Option 3
>> Sub Menu
0. Option 2.0
1. Sub Sub Menu
2. Option 2.2
3. Option 2.3
>> Sub Sub Menu
0. Option 2.1.0
1. Option 2.1.1
2. Option 2.1.2
3. Option 2.1.3
4. Option 2.1.4
>> Option 2.1.3 is called.
)~");
    }

    SUBCASE("Arguments")
    {
        auto f{ [](auto fo) {
            return [fo](std::vector<std::string> const& args) {
                if (std::size(args) < 3)
                {
                    std::cout << "Number of arguments must be at least 3\n";

                    return;
                }

                try
                {
                    std::invoke(fo, std::stoi(args[1]), std::stoi(args[2]));
                }
                catch (std::exception const& e)
                {
                    std::cout << e.what() << std::endl;
                }
            };
        } };

        std::stringbuf test_input("0 1 2 3 C++Korea", std::ios_base::in);
        std::stringbuf test_output(std::ios_base::out);
        std::streambuf* const cin_buf = std::cin.rdbuf(&test_input);
        std::streambuf* const cout_buf = std::cout.rdbuf(&test_output);

        REQUIRE_NOTHROW(
            CubbyMenu::Menu{ "MyMenu" }
                .add_header_ex("Main Menu")
                .add_item_ex("Arguments Test",
                             [](std::vector<std::string> const& args) {
                                 for (auto i{ 0u }; i < std::size(args); ++i)
                                     std::cout << "arg " << i << ": " << args[i]
                                               << std::endl;
                             })
                .add_item_ex("Add(int + int)", f([](auto a, auto b) {
                                 std::cout << a << " + " << b << " = " << a + b
                                           << '\n';
                             }))
                .add_item_ex("Sub(int - int)", f([](auto a, auto b) {
                                 std::cout << a << " - " << b << " = " << a - b
                                           << '\n';
                             }))
                .add_item_ex("Mul(int * int)", f([](auto a, auto b) {
                                 std::cout << a << " * " << b << " = " << a * b
                                           << '\n';
                             }))
                .add_item_ex("Div(int / int)", f([](auto a, auto b) {
                                 std::cout << a << " / " << b << " = " << a / b
                                           << '\n';
                             }))
                .print());

        std::cout.rdbuf(cout_buf);
        std::cin.rdbuf(cin_buf);

        REQUIRE(test_output.str() == R"~(Main Menu
0. Arguments Test
1. Add(int + int)
2. Sub(int - int)
3. Mul(int * int)
4. Div(int / int)
>> arg 0: 0
arg 1: 1
arg 2: 2
arg 3: 3
arg 4: C++Korea
)~");
    }

    SUBCASE("Add")
    {
        auto f{ [](auto fo) {
            return [fo](std::vector<std::string> const& args) {
                if (std::size(args) < 3)
                {
                    std::cout << "Number of arguments must be at least 3\n";

                    return;
                }

                try
                {
                    std::invoke(fo, std::stoi(args[1]), std::stoi(args[2]));
                }
                catch (std::exception const& e)
                {
                    std::cout << e.what() << std::endl;
                }
            };
        } };

        std::stringbuf test_input("1 18 10", std::ios_base::in);
        std::stringbuf test_output(std::ios_base::out);
        std::streambuf* const cin_buf = std::cin.rdbuf(&test_input);
        std::streambuf* const cout_buf = std::cout.rdbuf(&test_output);

        REQUIRE_NOTHROW(
            CubbyMenu::Menu{ "MyMenu" }
                .add_header_ex("Main Menu")
                .add_item_ex("Arguments Test",
                             [](std::vector<std::string> const& args) {
                                 for (auto i{ 0u }; i < std::size(args); ++i)
                                     std::cout << "arg " << i << ": " << args[i]
                                               << std::endl;
                             })
                .add_item_ex("Add(int + int)", f([](auto a, auto b) {
                                 std::cout << a << " + " << b << " = " << a + b
                                           << '\n';
                             }))
                .add_item_ex("Sub(int - int)", f([](auto a, auto b) {
                                 std::cout << a << " - " << b << " = " << a - b
                                           << '\n';
                             }))
                .add_item_ex("Mul(int * int)", f([](auto a, auto b) {
                                 std::cout << a << " * " << b << " = " << a * b
                                           << '\n';
                             }))
                .add_item_ex("Div(int / int)", f([](auto a, auto b) {
                                 std::cout << a << " / " << b << " = " << a / b
                                           << '\n';
                             }))
                .print());

        std::cout.rdbuf(cout_buf);
        std::cin.rdbuf(cin_buf);

        REQUIRE(test_output.str() == R"~(Main Menu
0. Arguments Test
1. Add(int + int)
2. Sub(int - int)
3. Mul(int * int)
4. Div(int / int)
>> 18 + 10 = 28
)~");
    }
}