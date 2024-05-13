#include "universal_zero.hpp"

double double_eps = 1e-14;
float float_eps = 1e-7;

bool operator == (const double& r, const universal_zero& l) { return abs(r) <= double_eps; }
bool operator != (const double& r, const universal_zero& l) { return abs(r) > double_eps; }
bool operator == (const universal_zero& r, const double& l) { return abs(l) <= double_eps; }
bool operator != (const universal_zero& r, const double& l)  { return abs(l) > double_eps; }

bool operator == (const float& r, const universal_zero& l) { return abs(r) <= float_eps; }
bool operator != (const float& r, const universal_zero& l) { return abs(r) > float_eps; }
bool operator == (const universal_zero& r, const float& l) { return abs(l) <= float_eps; }
bool operator != (const universal_zero& r, const float& l)  { return abs(l) > float_eps; }
