#ifndef CUBBY_MENU_HPP
#define CUBBY_MENU_HPP

#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace CubbyMenu
{
class MenuItem
{
 public:
    explicit MenuItem(std::string_view title) : m_title{ title }
    {
        // Do nothing
    }

    explicit MenuItem(std::string_view title, std::function<void()>&& callback)
        : m_title{ title }, m_callback{ std::move(callback) }
    {
        // Do nothing
    }

    [[nodiscard]] std::string_view get_title() const
    {
        return m_title;
    }

    [[nodiscard]] std::function<void()> get_callback() const
    {
        return m_callback;
    }

 private:
    std::string_view m_title;
    std::function<void()> m_callback;
};

class Menu
{
 public:
    void add_header(std::string_view header)
    {
        m_header = header;
    }

    void add_item(std::string_view title)
    {
        m_items.emplace_back(MenuItem{ title });
    }

    void add_item(std::string_view title, std::function<void()> callback)
    {
        m_items.emplace_back(MenuItem{ title, std::move(callback) });
    }

    void print() const
    {
        std::string option;
        int converted_option;

        if (!m_header.empty())
        {
            std::cout << m_header << '\n';
        }

        for (std::size_t i = 0; i < m_items.size(); ++i)
        {
            std::cout << i << ". " << m_items[i].get_title() << '\n';
        }

        while (true)
        {
            std::cout << ">> ";
            std::cin >> option;

            try
            {
                converted_option = std::stoi(option);
            }
            catch (...)
            {
                std::cout << "Invalid option! Try again.\n";
                continue;
            }

            if (converted_option < 0 ||
                converted_option >= static_cast<int>(m_items.size()))
            {
                std::cout << "Invalid option! Try again.\n";
            }
            else
            {
                m_items[converted_option].get_callback()();
                break;
            }
        }
    }

 private:
    std::string_view m_header;
    std::vector<MenuItem> m_items;
};
}  // namespace CubbyMenu

#endif