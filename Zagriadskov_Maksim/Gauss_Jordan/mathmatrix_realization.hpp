#pragma once
#include "simple_error.hpp"
#include <iomanip>
#include <sstream>

class matrix_err : public simple_error {
public:
    matrix_err(const std::string& s) : simple_error("Matrix: " + s) { }
};

template <class T>
class mathmatrix {
protected:
    mathvector< mathvector<T> > data;
public:
    mathmatrix() {}
    mathmatrix(size_t m, size_t n, const T& t = 0) : data(n, mathvector<T>(m, t)) {
        if (m == 0 || n == 0) 
            throw matrix_err("Invaid constructor parametrs: 0");
    }
    mathmatrix(const mathmatrix& m) {
        data = mathvector< mathvector<T> >(m.size(), m[0]);
        for (size_t i = 0; i < m.size(); i++)
            data[i] = m[i];
    }
    mathmatrix(const mathvector<T>& m) {
        this->add(m);
    }
    mathmatrix& operator=(const mathmatrix& m) {
        if (this == &m) 
            return *this;
        data = mathvector< mathvector<T> >(m.size());
        for (size_t i = 0; i < m.size(); i++)
            data[i] = m[i];

        return *this;
    }
    void add(const mathvector<T>& v) {
        data.add(v);
    }
    mathvector<T>& operator[](size_t i) {
        return data[i];
    }
    mathvector<T> operator[](size_t i) const {
        return data[i];
    }
    friend std::ostream& operator<< (std::ostream& stream, const mathmatrix& m) {
        for (size_t j = 0; j < m.vecsize(); j++) {
            for (size_t i = 0; i < m.size(); i++)
                stream << m[i][j] << " ";
            stream << std::endl;
        }

        return stream;
    }
    mathmatrix& operator+=(const mathmatrix& v) {
        if (size() != v.size())
            throw matrix_err("Addition: incompatible size");
        for (size_t i = 0; i < size(); i++)
            data[i] += v.data[i];
        return *this;
    }
    mathmatrix& operator-=(const mathmatrix& v) {
        if (size() != v.size())
            throw matrix_err("Substraction: incompatible size");
        for (size_t i = 0; i < size(); i++)
            data[i] -= v.data[i];
        return *this;
    }
    mathmatrix& operator*=(const mathmatrix& m) {
        for (size_t i = 0; i < size(); i++)
            data[i] *= m;
        return *this;
    }
    mathmatrix& operator/=(const T& t) {
        for (size_t i = 0; i < size(); i++)
            data[i] /= t;
        return *this;
    }
    mathmatrix operator+(const mathmatrix& v) {
        mathmatrix tmp = *this;
        tmp += v;
        return tmp;
    }
    mathmatrix operator-(const mathmatrix& v) {
        mathmatrix tmp = *this;
        tmp -= v;
        return tmp;
    }
    mathmatrix operator*(const T& t) {
        mathmatrix tmp = *this;
        tmp *= t;
        return tmp;
    }
    mathmatrix operator*(const mathmatrix& m) {
        if (size() != m.vecsize()) 
            throw matrix_err("Multiplication: incompatible size");
        mathmatrix res(this->vecsize(), m.size());
        for (size_t i = 0; i < res.size(); ++i)
            for (size_t j = 0; j < res.vecsize(); ++j)
                for (size_t k = 0; k < size(); k++) 
                    res[i][j] += data[k][j] * m[i][k];
        return res;
    }
    mathmatrix operator/(const T& t) {
        mathmatrix tmp = *this;
        tmp /= t;
        return tmp;
    }
    mathmatrix transpose() {
        mathmatrix res(size(), vecsize());
        for (size_t i = 0; i < size(); ++i)
            for (size_t j = 0; j < vecsize(); ++j)
                res[j][i] = data[i][j];
        return res;
    }
    size_t size() const { return data.size(); }
    size_t vecsize() const { return data.size() != 0 ? data[0].size() : 0; }
    T abs_max() {
        if (size() < 1 || vecsize() <= 1)
            return 0;
        T min = abs(data[0][0]);
        T max = 0;
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = 0; j < vecsize(); ++j) {
                if (abs(data[i][j]) > max)
                    max = abs(data[i][j]);
                if (abs(data[i][j]) < min)
                    min = abs(data[i][j]);
            }
        }
        return abs(max - min);
    }
    T abs_max_zeros() {
        std::stringstream stream;
        stream << std::fixed << abs_max();
        return stream.str().length();
    }
    ~mathmatrix() {

    }
};

template <class T>
mathmatrix<T> operator*(const T& t, mathmatrix<T> v) {
    mathvector<T> tmp = v;
    tmp *= t;
    return tmp;
}

template <class T>
mathmatrix<T> operator/(const T& t, mathmatrix<T> v) {
    mathvector<T> tmp = v;
    tmp /= t;
    return tmp;
}
