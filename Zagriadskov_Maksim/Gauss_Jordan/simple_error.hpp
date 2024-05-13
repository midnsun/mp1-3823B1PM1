#pragma once
#include <iostream>
#include <string>

class simple_error : public std::exception {
protected:
    char* str;
public:
    simple_error();
    simple_error(const std::string& s);
    virtual const char* what() const noexcept override;
    ~simple_error();
};
