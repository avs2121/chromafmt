#pragma once

#include <format>

#include "duration.hpp"

/*
wrap a uint64_t ms

{:ms}  ->  15023ms
{:s}   ->  15.023s
{:m}   ->  0m 15s
{:h}   ->  0h 0m 15s
{:f}   ->  00:00:15.023 - removed

convertion from ms to years from maximum duration using uint64_t :
18,446,744,073,709,551,615 / 1000 / 60 / 60 / 24 / 365.25 = 584.542.046 (584.5 million years)
ms -> s -> m -> h -> d -> y
*/

template <>
struct std::formatter<Duration>
{
    bool isMs = false;    // [:ms]
    bool isSec = false;   // [:s]
    bool isMin = false;   // [:m]
    bool isHour = false;  // [:h]
    bool isDay = false;   // [:d]
    bool isYear = false;  // [:y]

    constexpr auto parse(std::format_parse_context& ctx)
    {
        auto it = ctx.begin();
        auto end = ctx.end();

        if (it == end)
        {
            return it;
        }

        auto type_it = it;
        while (type_it != end && *type_it != '}')
        {
            type_it++;
        }

        auto ranged_end = type_it;
        if (ranged_end != it)
        {
            auto last = ranged_end - 1;
            if (*last == 's' && *(last - 1) == 'm')
            {
                isMs = true;
                ranged_end = last - 1;
            }
            else if (*last == 's')
            {
                isSec = true;
                ranged_end = last;
            }
            else if (*last == 'm')
            {
                isMin = true;
                ranged_end = last;
            }
            else if (*last == 'h')
            {
                isHour = true;
                ranged_end = last;
            }
            else if (*last == 'd')
            {
                isDay = true;
                ranged_end = last;
            }
            else if (*last == 'y')
            {
                isYear = true;
                ranged_end = last;
            }
        }

        spec_len = 0;
        for (auto i = it; i != ranged_end; ++i)
        {
            spec_buf[spec_len++] = *i;
        }
        return type_it;
    }

    auto format(Duration d, std::format_context& ctx) const
    {
        std::string result;
        if (isMs)
        {
        }
        else if (isSec)
        {
        }
        else if (isMin)
        {
        }
        else if (isHour)
        {
        }
        else if (isDay)
        {
        }
        else if (isYear)
        {
        }
        else
        {
            result = std::format("{}y, {}d, {}h, {}m, {}s, {}ms", d.y(), d.d(), d.h(), d.m(), d.s(), d.ms());
        }

        std::string fmt = std::string("{:" + std::string(spec_buf, spec_len) + "}");
        return std::vformat_to(ctx.out(), fmt, std::make_format_args(result));
    }

   private:
    char spec_buf[32]{};
    size_t spec_len{0};
};
