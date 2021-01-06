#pragma once

namespace MathUtils
{
    template<typename T>
    T Modulo(T a, T b)
    {
        return (a % b + b) % b; 
    }
}