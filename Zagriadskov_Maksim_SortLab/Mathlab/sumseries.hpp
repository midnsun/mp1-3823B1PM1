#include <iostream>
#pragma once

float nextsin(float x, size_t i);
float nextcos(float x, size_t i);
float nextexp(float x, size_t i);
float nextlog(float x, size_t i);

float convergesin(float x);
float convergecos(float x);
float convergeexp(float x);
float convergelog(float x);

float direct_sum(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n);

float partial_sum(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n);

float backward_sum(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n);

float backward_sum2(float x,
                  float a0,
                  float (*next)(float, size_t),
                  float (*transform)(float),
                  size_t n);