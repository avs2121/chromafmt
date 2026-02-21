#pragma once

#include <cstdint>

static constexpr uint64_t MS_PER_SECOND = 1000;
static constexpr uint64_t MS_PER_MINUTE = MS_PER_SECOND * 60;
static constexpr uint64_t MS_PER_HOUR = MS_PER_MINUTE * 60;
static constexpr uint64_t MS_PER_DAY = MS_PER_HOUR * 24;
static constexpr uint64_t MS_PER_YEAR = MS_PER_DAY * 365;  // using integer year.

class Duration
{
   public:
    Duration(uint64_t ms) : ms_(ms)
    {
    }
    const uint64_t ms() const
    {
        return ms_;
    }

    const uint64_t s() const
    {
        return ms_ / MS_PER_SECOND;
    }

    const uint64_t m() const
    {
        return ms_ / MS_PER_MINUTE;
    }

    const uint64_t h() const
    {
        return ms_ / MS_PER_HOUR;
    }

    const uint64_t d() const
    {
        return ms_ / MS_PER_DAY;
    }
    const uint64_t y() const
    {
        return ms_ / MS_PER_YEAR;
    }

   private:
    uint64_t ms_;
};
