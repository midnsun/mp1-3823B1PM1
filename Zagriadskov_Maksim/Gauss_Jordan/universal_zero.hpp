#pragma once
#include <cmath>

class universal_zero {};
const static universal_zero ZERO;

bool operator == (const double& r, const universal_zero& l);
bool operator != (const double& r, const universal_zero& l);
bool operator == (const universal_zero& r, const double& l);
bool operator != (const universal_zero& r, const double& l);

bool operator == (const float& r, const universal_zero& l);
bool operator != (const float& r, const universal_zero& l);
bool operator == (const universal_zero& r, const float& l);
bool operator != (const universal_zero& r, const float& l);