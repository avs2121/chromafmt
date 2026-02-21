/*
wrap a uint64_t ms

{:ms}  ->  1523ms
{:s}   ->  1.523s
{:f}   ->  00:00:01.523
{:h}   ->  0h 0m 1s

convertion from ms to years from maximum duration using uint64_t :
18,446,744,073,709,551,615 / 1000 / 60 / 60 / 24 / 365.25 = 584.542.046 (584.5 million years)
ms -> s -> m -> h -> d -> y
*/
