#ifndef CUBBY_MENU_HPP
#define CUBBY_MENU_HPP

#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <variant>
#include <any>
#include <sstream>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

namespace CubbyMenu
{
class MenuItem
{
 public:
    explicit MenuItem(std::string_view title) : m_title{ title }
    {
        // Do nothing
    }

    explicit MenuItem(std::string_view title, std::function<void(std::vector<std::string> const&)>&& callback)
        : m_title{ title }, m_callback{ std::move(callback) }
    {
        // Do nothing
    }

    [[nodiscard]] std::string_view get_title() const
    {
        return m_title;
    }

    void operator()(std::vector<std::string> const& args) const
    {
        std::invoke(m_callback, args); 
    }

 private:
    std::string_view m_title;
    std::function<void(std::vector<std::string> const&)> m_callback;
};

class Menu
{
 public:
    explicit Menu(std::string_view title = "No Title") : m_title(title)
    {
        // Do nothing
    }

    ~Menu() = default;

    void add_header(std::string_view header)
    {
        m_header = header;
    }

    Menu add_header_ex(std::string_view header) &&
    {
        m_header = header;

        return std::move(*this);
    }

    void add_item(std::string_view title)
    {
        m_items.emplace_back(MenuItem{ title });
    }

    Menu add_item_ex(std::string_view title) &&
    {
        m_items.emplace_back(MenuItem{ title });

        return std::move(*this);
    }

    void add_item(Menu&& menu)
    {
        m_items.emplace_back(std::move(menu));
    }

    Menu add_item_ex(Menu&& menu) &&
    {
        m_items.emplace_back(std::move(menu));

        return std::move(*this);
    }

    void add_item(std::string_view title, std::function<void(std::vector<std::string> const&)> callback)
    {
        m_items.emplace_back(MenuItem{ title, std::move(callback) });
    }

    Menu add_item_ex(std::string_view title, std::function<void(std::vector<std::string> const&)> callback) &&
    {
        m_items.emplace_back(MenuItem{ title, std::move(callback) });

        return std::move(*this);
    }

    void print() const
    {
        if (!m_header.empty())
        {
            std::cout << m_header << '\n';
        }

        for (std::size_t i = 0; i < m_items.size(); ++i)
        {
            std::visit(overloaded {
                [i](Menu const& menu) {
                    std::cout << i << ". " << menu.m_title << '\n';
                },
                [i](MenuItem const& menu_item) {
                    std::cout << i << ". " << menu_item.get_title() << '\n';
                }
            }, m_items[i]);
        }

        auto end_flag{ false };

        while (!end_flag)
        {
            std::vector<std::string> args;

            std::cout << ">> ";

            if (std::string line; std::getline(std::cin, line))
            {
                std::istringstream is(line);

                for (std::string arg; std::getline(is, arg, ' '); )
                    args.push_back(std::move(arg));

                if (std::empty(args))
                {
                    std::cout << "Invalid option! Try again.\n";
                    continue;
                }

                try
                {
                    if (auto converted_option{ std::stoi(args[0]) };
                        converted_option < 0 ||
                        converted_option >= static_cast<int>(m_items.size()))
                    {
                        std::cout << "Invalid option! Try again.\n";
                    }
                    else
                    {
                        std::visit(
                            overloaded{ [](Menu const& menu) { menu.print(); },
                                        [&args](MenuItem const& menu_item) {
                                            std::invoke(menu_item, args);
                                        } },
                            m_items[converted_option]);

                        end_flag = true;
                    }
                }
                catch (...)
                {
                    std::cout << "Invalid option! Try again.\n";
                    continue;
                }
            }
        }
    }

 private:
    std::string_view m_header;
    std::string_view m_title;
    std::vector<std::variant<Menu, MenuItem>> m_items;
};
}  // namespace CubbyMenu

#endif