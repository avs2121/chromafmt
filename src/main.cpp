#include <iostream>

#include "color_formatter.hpp"

/*
Input to handle :
std::format("col {}\n", Color{100, 255, 255}); -> col(100, 255, 255)
std::format("col {:h}\n", Color{100, 255, 255}); -> col #64c8ff

{:*>10} -> fills the width to the left with '*' if empty -> *****hello
{:*<10} -> fills the width to the right with '*' if empty ->  hello*****
{:*^10} -> fills the width to right and left with '*' if empty -> **hello***

format specification -> {'[arg-id]':'[format-spec]'}
  -> {0:*>10} -> first argument, fills width with '*' to the left of the argument

*/

int main()
{
    Color c1(0, 0, 1);
    std::cout << std::format("standard color rgb {}\n", c1);         // standard output
    std::cout << std::format("lower case hex color {:h}\n", c1);     // lower case hex
    std::cout << std::format("upper case hex color {:H}\n", c1);     // upper case hex
    std::cout << std::format("specifier last color {:>20H}\n", c1);  // type specifier in last position
    std::cout << std::format("fill width color: {:*^20}\n", c1);     // fill width 20 with *
}
