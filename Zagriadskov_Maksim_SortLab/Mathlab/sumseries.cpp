#include "sumseries.hpp"

float nextsin(float x, size_t i) {
    return -(x*x) / (2.0f*i * (2.0f*i + 1.0f));
}
float nextcos(float x, size_t i) {
    return -(x*x) / (2.0f*i * (2.0f*i - 1.0f));
}
float nextexp(float x, size_t i) {
    return x / i;
}
float nextlog(float x, size_t i) {
    return (x*x*(2.0f*i - 1)) / (2.0f*i + 1.0f);
}

float convergesin(float x) { return x;}
float convergecos(float x) { return x;}
float convergeexp(float x) { return x;}
float convergelog(float x) { return ((x - 1.0f) / (x + 1.0f));}

float direct_sum(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n) {
    float z = transform(x);
    float prev = a0;
    float res = prev;
    
    for (size_t i = 1; i <= n; i++) {
        prev *= next(z, i);
        res += prev;
    }
    return res;
}

float partial_sum(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n) {
    float z = transform(x);
    float prev = a0;
    float prefs = 0.0f;
    float res = prev;
    
    for (size_t i = 1; i <= n; i+=2) {
        prefs = prev * next(z, i) + prev * next(z, i) * next(z, i + 1);
        prev *= next(z, i) * next(z, i + 1);
        res += prefs;
    }
    if (n % 2 != 0) res += prev * next(z, n);
    return res;
}

float backward_sum(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n) {
    float z = transform(x);
    float res = 0.0f;
    float prev = a0;
    float tmp;
    size_t i;
    for (i = 1; i <= n; i++) {
        if (next(z, i) == 0.0f) {
            prev = 0.0f;
            break;
        }
        tmp = prev;
        prev *= next(z, i);
        if (prev == 0.0f) {
            prev = tmp;
            break;
        }
    }
    res = prev;
    if (prev == 0.0f) return 0.0f;
    
    for (size_t j = i - 1; j > 0; j--) {
        prev /= next(z, j);
        res += prev;
    }
    
    return res;
}

float backward_sum2(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n) {
    float z = transform(x);
    float res = 0.0f;
    float prev = a0;
    float tmp;
    float* data = new float[n + 1];
    for (size_t i = 1; i <= n; i++) data[i] = 0.0f;
    data[0] = prev;

    for (size_t i = 1; i <= n; i++) {
        prev *= next(z, i);
        data[i] = prev;
    }
    
    for (size_t i = n; i > 0; i--) {
        res += data[i];
    }
    res += a0;

    delete[] data;
    return res;
}