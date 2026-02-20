
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
    bool isHexUpper = false;
    bool isHexLower = false;

    constexpr auto parse(std::format_parse_context& ctx)  // parses spec format and stores state
    {
        auto it = ctx.begin();  // points to first character of spec e.g -> '*'
        auto end = ctx.end();   // points 1 past the ctx buffer.

        if (it == end)  // stop if empty (when spec is {}).
        {
            return it;
        }

        auto type_it = it;
        while (type_it != end && *type_it != '}')  // advance until '}' to find end.
        {
            ++type_it;
        }

        auto ranged_end = type_it;  // pointing to last '}'

        if (ranged_end != it)
        {
            auto last = ranged_end - 1;  // pointing to last character before '}'
            if (*last == 'h')
            {
                isHexLower = true;
                ranged_end = last;
            }
            else if (*last == 'H')
            {
                isHexUpper = true;
                ranged_end = last;
            }
        }

        // the range [it, ranged_end] only contains spec parts now.
        // Store the spec as a string, in a fixed-size char array.
        spec_len = 0;
        for (auto i = it; i != ranged_end; ++i)
        {
            spec_buf[spec_len++] = *i;
        }

        return type_it;  // returning iterator pointing to '}'
    }

    auto format(Color c, std::format_context& ctx) const  // read the interal state at runtime
    {
        std::string result;
        if (isHexUpper || isHexLower)
        {
            uint32_t val = (static_cast<uint32_t>(c.r) << 16) | (static_cast<uint32_t>(c.g) << 8) |
                           static_cast<uint32_t>(c.b);

            if (isHexUpper)
                result = std::format("#{:06X}", val);  // 06 for width

            else
                result = std::format("#{:06x}", val);  // 06 for width
        }
        else
            result = std::format("({}, {}, {})", c.r, c.g, c.b);

        // reconstruct the format string
        std::string fmt = std::string{"{:" + std::string(spec_buf, spec_len) + "}"};

        // takes the build string (fmt) wraps the result as the argument to format, and into the
        // output iterator (ctx)
        return std::vformat_to(ctx.out(), fmt, std::make_format_args(result));
    }

   private:
    size_t spec_len{0};
    char spec_buf[32]{};
};

int main()
{
    // clang-format off
    Color c1(0, 0, 1);
    std::cout << std::format("standard color rgb {}\n", c1);        // standard output
    std::cout << std::format("lower case hex color {:h}\n", c1);    // lower case hex
    std::cout << std::format("upper case hex color {:H}\n", c1);    // upper case hex
    std::cout << std::format("specifier last color {:>20H}\n",c1);  // test of type specifier in last position
    std::cout << std::format("fill width color: {:*^20}\n", c1);    // fill width 20 with *

    // clang-format on
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