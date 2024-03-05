#include "sumseries.hpp"
#include "_math.hpp"

float scale = 4.2f;
size_t nfact = 11;
size_t nlog = 256;

float _sin(float x) {
    size_t n = nfact + round(log(x)*log(x)*scale);
    return direct_sum(x, convergesin(x), nextsin, convergesin, n);
}

float _sin(float x, int method) {
    size_t n = nfact + round(log(x)*log(x)*scale);
    switch (method)
    {
    case 1:
        return direct_sum(x, convergesin(x), nextsin, convergesin, n);
    case 2:
        return partial_sum(x, convergesin(x), nextsin, convergesin, n);
    case 3:
        return backward_sum(x, convergesin(x), nextsin, convergesin, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _sin(float x, int method, size_t n) {
    switch (method)
    {
    case 1:
        return direct_sum(x, convergesin(x), nextsin, convergesin, n);
    case 2:
        return partial_sum(x, convergesin(x), nextsin, convergesin, n);
    case 3:
        return backward_sum(x, convergesin(x), nextsin, convergesin, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _cos(float x) {
    size_t n = nfact + round(log(x)*log(x)*scale);
    return direct_sum(x, convergecos(1.0f), nextcos, convergecos, n);
}

float _cos(float x, int method) {
    size_t n = nfact + round(log(x)*log(x)*scale);
    switch (method)
    {
    case 1:
        return direct_sum(x, convergecos(1.0f), nextcos, convergecos, n);
    case 2:
        return partial_sum(x, convergecos(1.0f), nextcos, convergecos, n);
    case 3:
        return backward_sum(x, convergecos(1.0f), nextcos, convergecos, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _cos(float x, int method, size_t n) {
    switch (method)
    {
    case 1:
        return direct_sum(x, convergecos(1.0f), nextcos, convergecos, n);
    case 2:
        return partial_sum(x, convergecos(1.0f), nextcos, convergecos, n);
    case 3:
        return backward_sum(x, convergecos(1.0f), nextcos, convergecos, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _exp(float x) {
    size_t n = nfact + round(log(x)*log(x)*scale);
    return partial_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
}

float _exp(float x, int method) {
    size_t n = nfact + round(log(x)*log(x)*scale);
    switch (method)
    {
    case 1:
        return direct_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
    case 2:
        return partial_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
    case 3:
        return backward_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _exp(float x, int method, size_t n) {
    switch (method)
    {
    case 1:
        return direct_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
    case 2:
        return partial_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
    case 3:
        return backward_sum(x, convergeexp(1.0f), nextexp, convergeexp, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _ln(float x) {
    size_t n = nlog;
    return partial_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
}

float _ln(float x, int method) {
    size_t n = nlog;
    switch (method)
    {
    case 1:
        return direct_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
    case 2:
        return partial_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
    case 3:
        return backward_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}

float _ln(float x, int method, size_t n) {
    switch (method)
    {
    case 1:
        return direct_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
    case 2:
        return partial_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
    case 3:
        return backward_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n);
    default:
        std::cout << "Error: no method found\n";
        break;
    }
    return 0.0f;
}