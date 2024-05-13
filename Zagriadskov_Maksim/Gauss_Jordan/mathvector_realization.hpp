#pragma once
#include "simple_error.hpp"

class vector_err : public simple_error {
public:
    vector_err(const std::string& s) : simple_error("Vector: " + s) { }
};

template <class T>
class mathvector {
    size_t sizevar;
    T* data;
    size_t capacity;
    const size_t scale;
public:
    mathvector() : scale(2) {
        data = nullptr;
        sizevar = 0;
        capacity = 0;
    }
    mathvector(size_t s) : scale(2) {
        if (s == 0) 
            throw vector_err("Invalid constructor parametr: 0");
        data = new T[s];
        sizevar = s;
        capacity = s;
    }
    mathvector(size_t s, const T& a) : scale(2) {
        if (s == 0) 
            throw vector_err("Invalid constructor parametr: 0");
        data = new T[s];
        sizevar = s;
        capacity = s;
        std::fill(data, data + s, a);
    }
    mathvector(const mathvector& v) : scale(2) {
        data = new T[v.size()];
        sizevar = v.sizevar;
        capacity = v.capacity;
        std::copy(v.data, v.data + v.sizevar, data);
    }
    mathvector& operator=(const mathvector& v) {
        if (this == &v) 
            return *this;
        if (capacity < v.size()) {
            capacity = v.size();
            delete[] data;
            data = new T[v.size()];
        }
        sizevar = v.size();
        std::copy(v.data, v.data + v.sizevar, data);
        return *this;
    }
    T& operator[](size_t i) {
        return data[i];
    }
    T operator[](size_t i) const {
        return data[i];
    }
    T& at(size_t i) {
        if (i >= size()) 
            throw vector_err("Out of range: " + std::to_string(i));
        return data[i];
    }
    T at(size_t i) const {
        if (i >= size()) 
            throw vector_err("Out of range: " + std::to_string(i));
        return data[i];
    }
    void add(const T& a) {
        if (size() > 0 && capacity <= sizevar) {
            capacity *= scale;
            T* newdata = new T[capacity];
            std::copy(data, data + sizevar, newdata);
            delete[] data;
            data = newdata;
            data[sizevar] = a;
        }
        else if (size() == 0) {
            data = new T[1];
            data[0] = a;
            capacity = 1;
        }
        else
            data[sizevar] = a;
        ++sizevar;
    }
    mathvector& operator+=(const mathvector& v) {
        if (size() != v.size())
            throw vector_err("Addition: incompatible size");
        for (size_t i = 0; i < size(); i++)
            data[i] += v.data[i];
        return *this;
    }
    mathvector& operator-=(const mathvector& v) {
        if (size() != v.size())
            throw vector_err("Substraction: incompatible size");
        for (size_t i = 0; i < size(); i++)
            data[i] -= v.data[i];
        return *this;
    }
    mathvector& operator*=(const T& t) {
        for (size_t i = 0; i < size(); i++)
            data[i] *= t;
        return *this;
    }
    mathvector& operator/=(const T& t) {
        for (size_t i = 0; i < size(); ++i)
            data[i] /= t;
        return *this;
    }
    mathvector operator+(const mathvector& v) const {
        mathvector tmp = *this;
        tmp += v;
        return tmp;
    }
    mathvector operator-(const mathvector& v) const {
        mathvector tmp = *this;
        tmp -= v;
        return tmp;
    }
    mathvector operator*(const T& t) const {
        mathvector tmp = *this;
        tmp *= t;
        return tmp;
    }
    mathvector operator/(const T& t) const {
        mathvector tmp = *this;
        tmp /= t;
        return tmp;
    }
    
    friend std::ostream& operator<< (std::ostream& stream, const mathvector& v) {
        for (size_t i = 0; i < v.size(); i++)
            stream << v[i] << " ";
        return stream;
    }
    size_t size() const { return sizevar; }
    ~mathvector(){
        delete[] data;
    }
};

template <class T>
mathvector<T> operator*(const T& t, mathvector<T> v){
    mathvector<T> tmp = v;
    tmp *= t;
    return tmp;
}

template <class T>
mathvector<T> operator/(const T& t, mathvector<T> v) {
    mathvector<T> tmp = v;
    tmp /= t;
    return tmp;
}

template <class T1, class T2>
mathvector<T1> operator-(const mathvector<T1> v1, const mathvector<T2> v2) {
    if (v1.size() != v2.size())
        throw vector_err("Substraction: incompatible size");
    mathvector<T1> res = v1;
    for (size_t i = 0; i < v1.size(); i++)
        res[i] -= v2[i];
    return res;
}
