#include "mathvector_realization.hpp"
#include "mathmatrix_realization.hpp"
#include "bignum.hpp"
#include "universal_zero.hpp"
#include "solver.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

int main(int argc, const char * argv[]) {
    try {
        std::string float_or_bignums;
        std::string str;
        std::cout << "1 for floating point calculations, 2 for bignumbers calculations\n";
        std::getline(std::cin, float_or_bignums);

        if (float_or_bignums == "1") {
            mathmatrix<double> Matrix;

            std::cout << "Enter a path to a file with matrix or type \"Console\" to enter matrix manually\n";
            std::getline(std::cin, str);
            if (str == "console" || str == "Console") {
                int m, n;
                std::cout << "Enter number of equations: \n";
                std::cin >> m;
                std::cout << "Enter number of variables: \n";
                std::cin >> n;
                Matrix = mathmatrix<double>(m, n + 1);

                std::cout << "Enter all of the coefficients\n";
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n + 1; j++) {
                        std::cin >> Matrix[j][i];
                    }
                    std::cout << std::endl;
                }
            }
            else {
                std::string tmp;
                std::string::iterator it;
                size_t counter;
                std::ifstream in(str);
                if (in.is_open()) {
                    while (std::getline(in, str)) {
                        counter = 0;
                        it = str.begin();
                        while (it != str.end()) {
                            tmp = "";
                            while (it != str.end() && *it == ' ') ++it;
                            while (it != str.end() && *it != ' ') {
                                tmp += *it;
                                ++it;
                            }
                            if (tmp != "") {
                                if (counter >= Matrix.size()) {
                                    Matrix.add(mathvector<double>(1, std::stod(tmp)));
                                }
                                else {
                                    Matrix[counter].add(std::stod(tmp));
                                }
                                ++counter;
                            }
                        }
                    }
                    in.close();
                }
                else {
                    std::cout << "File not found\n";
                    return 0;
                }
            }

            if (Matrix.size() < 2)
                std::cout << "There are no any system of equations\n";
            else {
                Solver<double> solver(Matrix);
                std::cout << "Error is:\n";
                auto start = std::chrono::high_resolution_clock::now();
                std::cout << solver.get_error();
                auto stop = std::chrono::high_resolution_clock::now();
                std::cout << std::endl;
                std::cout << "Time is: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds" << std::endl;
            }
        }

        if (float_or_bignums == "2") {
            mathmatrix<bigrational> Matrix;

            std::cout << "Enter a path to a file with matrix or type \"Console\" to enter matrix manually\n";
            std::getline(std::cin, str);
            if (str == "console" || str == "Console") {
                int m, n;
                std::cout << "Enter number of equations: \n";
                std::cin >> m;
                std::cout << "Enter number of variables: \n";
                std::cin >> n;
                Matrix = mathmatrix<bigrational>(m, n + 1);

                std::cout << "Enter all of the coefficients\n";
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n + 1; j++) {
                        std::cin >> Matrix[j][i];
                    }
                    std::cout << std::endl;
                }
            }
            else {
                std::string tmp;
                uint64_t n, d, pos;
                std::string::iterator it;
                size_t counter;
                std::ifstream in(str);
                if (in.is_open()) {
                    while (std::getline(in, str)) {
                        counter = 0;
                        it = str.begin();
                        while (it != str.end()) {
                            tmp = "";
                            while (it != str.end() && *it == ' ') ++it;
                            while (it != str.end() && *it != ' ') {
                                tmp += *it;
                                ++it;
                            }
                            if (tmp != "") {
                                pos = tmp.find("/");
                                if (pos == std::string::npos) {
                                    n = std::stoull(tmp);
                                    d = 1;
                                }
                                else {
                                    n = std::stoull(tmp.substr(0, pos));
                                    d = std::stoull(tmp.substr(pos + 1));
                                }
                                if (counter >= Matrix.size()) {
                                    Matrix.add(mathvector<bigrational>(1, bigrational(n, d)));
                                }
                                else {
                                    Matrix[counter].add(bigrational(n, d));
                                }
                                ++counter;
                            }
                        }
                    }
                    in.close();
                }
                else {
                    std::cout << "File not found\n";
                    return 0;
                }
            }

            if (Matrix.size() < 2)
                std::cout << "There are no any system of equations\n";
            else {
                Solver<bigrational> solver(Matrix);
                std::cout << "Error is:\n";
                auto start = std::chrono::high_resolution_clock::now();
                std::cout << solver.get_error();
                auto stop = std::chrono::high_resolution_clock::now();
                std::cout << std::endl;
                std::cout << "Time is: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds" << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Uncaught exception\n";
    }
    system("pause");
    return 0;
}
