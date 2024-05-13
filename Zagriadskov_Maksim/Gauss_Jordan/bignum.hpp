#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "universal_zero.hpp"
#include "simple_error.hpp"

typedef uint64_t BUINT_TYPE;
typedef int64_t BINT_TYPE;

struct biguint {
private:
    std::vector<BUINT_TYPE> data;
    void normilize();
    void simpledivision(biguint a, const biguint& b, biguint& p, biguint &q);
    biguint binarydivision(const biguint& d) const;
public:
    biguint();
    biguint(const BUINT_TYPE& var);
    biguint(const biguint& b);
    ~biguint();
    friend std::ostream& operator << (std::ostream& stream, const biguint& b);
    biguint& operator = (const biguint& other);
    biguint& operator = (const BUINT_TYPE& other);
    biguint operator + (const biguint& b) const;
    biguint operator + (const BUINT_TYPE& b) const;
    biguint& operator += (const biguint& b);
    biguint& operator += (const BUINT_TYPE& b);
    biguint operator - (const biguint& b) const;
    biguint operator - (const BUINT_TYPE& b) const;
    biguint& operator -= (const biguint& b);
    biguint& operator -= (const BUINT_TYPE& b);
    BUINT_TYPE to_uint() const;
    uint64_t t8_t64();
    void t64_t8(uint64_t b);
    biguint operator * (const biguint& b) const;
    biguint operator * (const BUINT_TYPE& b) const;
    biguint& operator *= (const biguint& b);
    biguint& operator *= (const BUINT_TYPE& b);
    bool operator == (const biguint& b) const;
    bool operator == (const BUINT_TYPE& b) const;
    bool operator < (const biguint& b) const;
    bool operator > (const biguint& b) const;
    bool operator >= (const biguint& b) const;
    bool operator <= (const biguint& b) const;
    bool operator < (const BUINT_TYPE& b) const;
    bool operator > (const BUINT_TYPE& b) const;
    bool operator >= (const BUINT_TYPE& b) const;
    bool operator <= (const BUINT_TYPE& b) const;
    bool operator != (const BUINT_TYPE& b) const;
    bool operator != (const biguint& b) const;
    biguint& operator ++ ();
    biguint operator ++ (int b);
    biguint& operator -- ();
    biguint operator -- (int b);
    biguint& operator /= (const biguint& b);
    biguint& operator /= (const BUINT_TYPE& b);
    biguint operator / (const biguint& b) const;
    biguint operator / (const BUINT_TYPE& b) const;
    biguint& operator %= (const biguint& b);
    biguint& operator %= (const BUINT_TYPE& b);
    biguint operator % (const biguint& b) const;
    biguint operator % (const BUINT_TYPE& b) const;
    biguint operator << (const size_t& n) const;
    biguint& operator <<= (const size_t& n);
    biguint operator >> (const size_t& n) const;
    biguint& operator >>= (const size_t& n);
    biguint& cell_left_shift(const size_t& n);
    biguint& cell_right_shift(const size_t& n);
    static biguint gcd(biguint a, biguint b);
    double newtondivision(const biguint& d) const;
    void shortdivision(const BUINT_TYPE& d, biguint& q, biguint& r) const;
};

struct bigint {
private:
    biguint num;
    char sign;
public:
    bigint();
    bigint(const BINT_TYPE& var);
    bigint(const BUINT_TYPE& var);
    bigint(const bigint& b);
    bigint(const biguint& b);
    ~bigint();
    inline void normilize();
    friend std::ostream& operator << (std::ostream& stream, const bigint& b);
    bigint& operator = (const bigint& other);
    bigint& operator = (const biguint& other);
    bigint& operator = (const BINT_TYPE& other);
    bigint operator + (const bigint& b) const;
    bigint operator + (const BINT_TYPE& b) const;
    bigint& operator += (const bigint& b);
    bigint& operator += (const BINT_TYPE& b);
    bigint& operator - ();
    bigint operator - (const bigint& b) const;
    bigint operator - (const BINT_TYPE& b) const;
    bigint& operator -= (const bigint& b);
    bigint& operator -= (const BINT_TYPE& b);
    bigint operator * (const bigint& b) const;
    bigint operator * (const BINT_TYPE& b) const;
    bigint& operator *= (const bigint& b);
    bigint& operator *= (const BINT_TYPE& b);
    bool operator == (const bigint& b) const;
    bool operator == (const BINT_TYPE& b) const;
    bool operator < (const bigint& b) const;
    bool operator > (const bigint& b) const;
    bool operator >= (const bigint& b) const;
    bool operator <= (const bigint& b) const;
    bool operator < (const BINT_TYPE& b) const;
    bool operator > (const BINT_TYPE& b) const;
    bool operator >= (const BINT_TYPE& b) const;
    bool operator <= (const BINT_TYPE& b) const;
    bool operator != (const BINT_TYPE& b) const;
    bool operator != (const bigint& b) const;
    bigint& operator ++ ();
    bigint operator ++ (int b);
    bigint& operator -- ();
    bigint operator -- (int b);
    bigint& operator /= (const bigint& b);
    bigint& operator /= (const BINT_TYPE& b);
    bigint operator / (const bigint& b) const;
    bigint operator / (const BINT_TYPE& b) const;
    bigint& operator %= (const bigint& b);
    bigint& operator %= (const BINT_TYPE& b);
    bigint operator % (const bigint& b) const;
    bigint operator % (const BINT_TYPE& b) const;
    bigint operator << (const size_t& n) const;
    bigint& operator <<= (const size_t& n);
    bigint operator >> (const size_t& n) const;
    bigint& operator >>= (const size_t& n);
    biguint& b_abs();
    biguint b_abs() const;
    std::string bigint_to_string() const;
};

struct bigrational {
private:
    bigint num;
    biguint denum;
    void normalize();
public:
    bigrational();
    bigrational(const int8_t& var);
    bigrational(const uint8_t& var);
    bigrational(const int16_t& var);
    bigrational(const uint16_t& var);
    bigrational(const int32_t& var);
    bigrational(const uint32_t& var);
    bigrational(const int64_t& var);
    bigrational(const uint64_t& var);
    bigrational(const float& var);
    bigrational(const double& var);
    bigrational(const bigint& b);
    bigrational(const biguint& b);
    bigrational(const bigrational& b);
    bigrational(const uint64_t& n, const uint64_t& d);
    ~bigrational();
    friend std::ostream& operator << (std::ostream& stream, const bigrational& b);
    friend std::istream& operator >> (std::istream& stream, bigrational& b);
    void rawprint() const;
    void floatprint() const;
    double to_double() const;
    bigrational& operator = (const bigrational& other);
    bigrational operator + (const bigrational& b) const;
    bigrational& operator += (const bigrational& b);
    bigrational& operator - ();
    bigrational operator - (const bigrational& b) const;
    bigrational& operator -= (const bigrational& b);
    bigrational operator * (const bigrational& b) const;
    bigrational& operator *= (const bigrational& b);
    bigrational operator / (const bigrational& b) const;
    bigrational& operator /= (const bigrational& b);
    bool operator == (const bigrational& b) const;
    bool operator < (const bigrational& b) const;
    bool operator > (const bigrational& b) const;
    bool operator >= (const bigrational& b) const;
    bool operator <= (const bigrational& b) const;
    bool operator != (const bigrational& b) const;
    bigrational& operator ++ ();
    bigrational operator ++ (int b);
    bigrational& operator -- ();
    bigrational operator -- (int b);
    friend bigrational abs(const bigrational& b);
    std::string bigrational_to_string() const;
};

bool operator == (const bigrational& r, const universal_zero& l);
bool operator != (const bigrational& r, const universal_zero& l);
bool operator == (const universal_zero& r, const bigrational& l);
bool operator != (const universal_zero& r, const bigrational& l);

namespace std {
    std::string to_string(const bigrational& b);
    std::string to_string(const bigint& b);
}

template <class T>
bigrational operator + (const T& a, const bigrational& b) { return b + a; }

template <class T>
bigrational operator - (const T& a, const bigrational& b) { return bigrational(a) - b; }

template <class T>
bigrational operator * (const T& a, const bigrational& b) { return b * a; }

template <class T>
bigrational operator / (const T& a, const bigrational& b) { return bigrational(a) / b; }

template <class T>
bool operator == (const T& a, const bigrational& b) { return b == a; }

template <class T>
bool operator < (const T& a, const bigrational& b) { return b > a; }

template <class T>
bool operator > (const T& a, const bigrational& b) { return b < a; }

template <class T>
bool operator >= (const T& a, const bigrational& b) { return b <= a; }

template <class T>
bool operator <= (const T& a, const bigrational& b) { return b >= a; }

template <class T>
bool operator != (const T& a, const bigrational& b) { return b != a; }
