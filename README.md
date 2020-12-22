# CubbyMenu

<img src="./Medias/Logo.png" width=256 height=256 />

[![License](https://img.shields.io/badge/Licence-MIT-blue.svg)](./LICENSE) ![Windows](https://github.com/utilForever/CubbyMenu/workflows/Windows/badge.svg) ![Ubuntu](https://github.com/utilForever/CubbyMenu/workflows/Ubuntu/badge.svg) ![macOS](https://github.com/utilForever/CubbyMenu/workflows/macOS/badge.svg) ![Ubuntu - Codecov](https://github.com/utilForever/CubbyMenu/workflows/Ubuntu%20-%20Codecov/badge.svg) [![Build Status](https://travis-ci.com/utilForever/CubbyMenu.svg?branch=main)](https://travis-ci.com/utilForever/CubbyMenu)

[![codecov](https://codecov.io/gh/utilForever/CubbyMenu/branch/main/graph/badge.svg?token=ZDJPA79SFV)](undefined) [![Codacy Badge](https://app.codacy.com/project/badge/Grade/0e09b079e82b4523ad264365bf8eb1e9)](https://www.codacy.com/gh/utilForever/CubbyMenu/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=utilForever/CubbyMenu&amp;utm_campaign=Badge_Grade) [![Total alerts](https://img.shields.io/lgtm/alerts/g/utilForever/CubbyMenu.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/utilForever/CubbyMenu/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/utilForever/CubbyMenu.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/utilForever/CubbyMenu/context:cpp) [![CodeFactor](https://www.codefactor.io/repository/github/utilforever/CubbyMenu/badge)](https://www.codefactor.io/repository/github/utilforever/CubbyMenu)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=CubbyMenu&metric=alert_status)](https://sonarcloud.io/dashboard?id=CubbyMenu) [![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=CubbyMenu&metric=ncloc)](https://sonarcloud.io/dashboard?id=CubbyMenu) [![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=CubbyMenu&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=CubbyMenu) [![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=CubbyMenu&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=CubbyMenu) [![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=CubbyMenu&metric=security_rating)](https://sonarcloud.io/dashboard?id=CubbyMenu)

CubbyMenu is a header only Modern C++ library to easily create simple menus for programs.
The code is built on C++17 and can be compiled with commonly available compilers such as g++, clang++, or Microsoft Visual Studio. CubbyMenu currently supports macOS (10.12.6 or later), Ubuntu (17.04 or later), Windows (Visual Studio 2017 or later), and Windows Subsystem for Linux (WSL). Other untested platforms that support C++17 also should be able to build CubbyMenu.

## Example usage

```c++
#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0", []() { std::cout << "Option 0 is called!\n"; });
    menu.add_item("Option 1", []() { std::cout << "Option 1 is called!\n"; });
    menu.add_item("Option 2", []() { std::cout << "Option 2 is called!\n"; });

    menu.print();
}
```

## Dependencies

*CubbyMenu* only depends on [C++ Standard Library](http://en.cppreference.com/w/cpp/header). In other words, you don't need any 3rd party dependencies.

## Installation

*CubbyMenu* is a single header-only library. Put `CubbyMenu.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Examples

### Simple menu without callback

```C++
#include <CubbyMenu/CubbyMenu.hpp>

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0");
    menu.add_item("Option 1");
    menu.add_item("Option 2");

    menu.print();
}
```

### Simple menu with header

```C++
#include <CubbyMenu/CubbyMenu.hpp>

int main()
{
    CubbyMenu::Menu menu;
    menu.add_header("Header");

    menu.add_item("Option 0");
    menu.add_item("Option 1");
    menu.add_item("Option 2");

    menu.print();
}
```

### Simple menu with function callback

```C++
#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

void option0()
{
    std::cout << "Option 0 is called!\n";
}

void option1()
{
    std::cout << "Option 1 is called!\n";
}

void option2()
{
    std::cout << "Option 2 is called!\n";
}

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0", &option0);
    menu.add_item("Option 1", &option1);
    menu.add_item("Option 2", &option2);

    menu.print();
}
```

### Simple menu with lambda callback

```C++
#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0", []() { std::cout << "Option 0 is called!\n"; });
    menu.add_item("Option 1", []() { std::cout << "Option 1 is called!\n"; });
    menu.add_item("Option 2", []() { std::cout << "Option 2 is called!\n"; });

    menu.print();
}
```

## How To Contribute

Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please contact me.

## Contact

You can contact me via e-mail (utilForever at gmail.com). I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2020 [Chris Ohk](http://www.github.com/utilForever).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.