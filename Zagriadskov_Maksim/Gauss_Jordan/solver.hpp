#pragma once

#include "universal_zero.hpp"
#include "mathvector_realization.hpp"
#include "mathmatrix_realization.hpp"
#include <string>

class inconsistent_equation : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "The system of equations has no solutions\n";
    }
};

const static inconsistent_equation no_solutions;

template <class T>
class Solver {
private:
    mathvector<T> b;
    mathvector<T> error;
    mathmatrix<T> matrix;
    mathmatrix<T> bmatrix;
public:
    Solver() = default;
    Solver(const mathmatrix<T>& m) : bmatrix(m) { }
    Solver(const Solver& s) : bmatrix(s.bmatrix) { }
    Solver& operator= (const Solver& s) {
        bmatrix = s.bmatrix;
        return *this;
        
    }
    
    mathvector<T> get_error_vec() {
        get_error();
        return error;
    }

    T get_error() {
        if (bmatrix.size() - 1 != bmatrix.vecsize())
            throw simple_error("Not a square matrix");
        
        matrix = mathmatrix<T>(bmatrix.size() - 1, bmatrix.vecsize());
        for (size_t i = 0; i < matrix.size(); ++i)
            for (size_t j = 0; j < matrix.vecsize(); ++j)
                matrix[i][j] = bmatrix[i][j];
        b = bmatrix[bmatrix.size() - 1];
        
        bmatrix = bmatrix.transpose();
        trans_gauss_jordan(bmatrix);
        bmatrix = bmatrix.transpose();
        error = (matrix * bmatrix[bmatrix.size() - 1])[0] - b;
        
        T res = int(0);
        for (size_t i = 0; i < error.size(); ++i)
            if (abs(error[i]) > res)
                res = abs(error[i]);

        return res;
    }
};

template <class Ty>
size_t max_index(const mathmatrix<Ty>& m, const size_t& row, const size_t& colomn) {
    size_t res = colomn;
    for (size_t i = colomn; i < m.size(); ++i)
        if (abs(m[i][row]) > abs(m[res][row]))
            res = i;
    return res;
}

template <class Ty>
void trans_gauss_jordan(mathmatrix<Ty>& matrix) {
    mathvector<Ty> res;
    size_t max_ind, col, i, row;
    
    for (col = 0, row = 0; row < matrix.vecsize() - 1 && col < matrix.size(); ++col, ++row) {
        max_ind = max_index(matrix, row, col);
        if (matrix[max_ind][row] == ZERO) {
            --col;
            continue;
        }
        
        std::swap(matrix[max_ind], matrix[col]);
        for (i = 0; i < matrix.size(); ++i) {
            if (i == col || matrix[i][row] == ZERO) continue;
            matrix[i] -= matrix[col] * (matrix[i][row] / matrix[col][row]);
        }
        matrix[col] /= Ty(matrix[col][row]);
    }
}

template <class Ty>
void solve(mathmatrix<Ty> matrix) {
    try {
        matrix = matrix.transpose();
        trans_gauss_jordan(matrix);
        std::string str = "";
        size_t col, row, j, t_counter = 0;
        for (col = 0, row = 0; col < matrix.size() && row < matrix.vecsize() - 1; ++col, ++row) {
            str += "x" + std::to_string(row + 1) + " = ";
            
            if (matrix[col][row] == ZERO) {
                str += "t" + std::to_string(++t_counter) + '\n';
                if (row + 1 < matrix.vecsize() - 1)
                    --col;
                else if (matrix[col][matrix.vecsize() - 1] != ZERO)
                    throw no_solutions;
                
                continue;
            }
            
            str += std::to_string(matrix[col][matrix.vecsize() - 1]);
            for (j = row + 1; j < matrix.vecsize() - 1; ++j) {
                if (matrix[col][j] != ZERO) {
                    if (matrix[col][j] > 0) str += " - ";
                    else str += " + ";
                    if (abs(matrix[col][j]) != 1) str += std::to_string(abs(matrix[col][j]));
                    str += "x" + std::to_string(j + 1);
                }
            }
            str += '\n';
        }
        
        for (j = col; j < matrix.size(); ++j)
            if (matrix[j][matrix.vecsize() - 1] != ZERO)
                throw no_solutions;
        
        for (j = row; j < matrix.vecsize() - 1; ++j)
            str += "x" + std::to_string(j + 1) + " = t" + std::to_string(++t_counter) + '\n';
        
        for (j = 0; j < t_counter; ++j) {
            str += "t" + std::to_string(j + 1) + ", ";
        }
        if (j > 0) {
            str[str.length() - 2] = ' ';
            str[str.length() - 1] = '-';
            str += " any from numerical field Q";
        }
        std::cout << str;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown exception\n" << std::endl;
    }
}

