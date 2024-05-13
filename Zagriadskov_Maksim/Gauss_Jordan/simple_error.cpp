#include "simple_error.hpp"

simple_error::simple_error() {
    str = nullptr;
}
simple_error::simple_error(const std::string& s) {
    str = new char[s.length() + 1];
    std::copy(s.begin(), s.end(), str);
    str[s.length()] = '\0';
}
const char* simple_error::what() const noexcept {
    return str;
}
simple_error::~simple_error() {
    delete[] str;
}
