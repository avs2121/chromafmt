
#include <cstdint>
#include <format>
#include <iostream>

/*
Primary template looks like template<Class T, class CharT> -> struct formatter.
Here T is the type we are formatting, and charT is the character type of the string.
  - Because the character type can be both char and wchar -> important distinction.

So basically says std::formatter<Color, char> -> The formatter formats Color when
the format string is made out of char

The Template <> signals full specilization of std::formatter for the combination of <T =
Color, CharT = char>
*/

struct Color
{
    uint8_t r{0};
    uint8_t g{0};
    uint8_t b{0};
};

template <>
struct std::formatter<Color>
{
    bool isHex = false;
    constexpr auto parse(std::format_parse_context& ctx)  // sets internal state
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it == 'h' || *it == 'H')
        {
            isHex = true;
            ++it;
        }
        if (it != ctx.end() && *it != '}')
            throw std::format_error("Invalid format args for QuotableString.");

        return it;
    }

    auto format(Color c, std::format_context& ctx) const  // read the interal state
    {
        if (isHex)
        {
            uint32_t val = (c.r << 16 | c.g << 8 | c.b);
            return std::format_to(ctx.out(), "#{:x}", val);
        }
        else
            return std::format_to(ctx.out(), "({}, {}, {})", c.r, c.g, c.b);
    }
};

int main()
{
    Color c1(200, 200, 100);
    std::cout << std::format("col {}\n", c1);
    std::cout << std::format("col {:h}\n", c1);
    std::cout << std::format("col {:H}\n", c1);
}

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