#include <iostream>
#include <fstream>
#include <cmath>
#include "sumseries.hpp"

const size_t methods = 4;

using namespace std;

void _funcs(float* res, float x, size_t n1, size_t n2, int flag) {
    switch (flag) {
        case 0:
            res[0] = sin(x);
            res[1] = cos(x);
            res[2] = exp(x);
            res[3] = log(x);
            break;
        case 1:
            res[0] = direct_sum(x, convergesin(x), nextsin, convergesin, n1);
            res[1] = direct_sum(x, convergecos(1.0f), nextcos, convergecos, n1);
            res[2] = direct_sum(x, convergeexp(1.0f), nextexp, convergeexp, n1);
            res[3] = direct_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n2);
            break;
        case 2:
            res[0] = partial_sum(x, convergesin(x), nextsin, convergesin, n1);
            res[1] = partial_sum(x, convergecos(1.0f), nextcos, convergecos, n1);
            res[2] = partial_sum(x, convergeexp(1.0f), nextexp, convergeexp, n1);
            res[3] = partial_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n2);
            break;
        case 3:
            res[0] = backward_sum(x, convergesin(x), nextsin, convergesin, n1);
            res[1] = backward_sum(x, convergecos(1.0f), nextcos, convergecos, n1);
            res[2] = backward_sum(x, convergeexp(1.0f), nextexp, convergeexp, n1);
            res[3] = backward_sum(x, 2.0f*convergelog(x), nextlog, convergelog, n2);
            break;
        case 4:
            res[0] = backward_sum2(x, convergesin(x), nextsin, convergesin, n1);
            res[1] = backward_sum2(x, convergecos(1.0f), nextcos, convergecos, n1);
            res[2] = backward_sum2(x, convergeexp(1.0f), nextexp, convergeexp, n1);
            res[3] = backward_sum2(x, 2.0f*convergelog(x), nextlog, convergelog, n2);
        default:
            break;
    }
    return;
}

int main(int argc, const char * argv[]) {
    ofstream file;
    file.open("file.txt");
    int flag = 0;
    float scale = 4.2f;
    size_t nfact = 11;
    size_t nlog = 256;
    size_t n1;
    size_t n2;
    float func[4];
    float corr[4];
    float x;
    file << fixed << setprecision(8);

    for (x = 0.0f; x <= 64.0f; x+=1.0f/1024.0f) {
        n1 = nfact;
        if (x >= 1.0f) n1 += round(log(x)*log(x)*scale);
        n2 = nlog;
        file << x;
        
        _funcs(corr, x, 0, 0, 0);
        _funcs(func, x, n1, n2, flag);
        
        for (size_t j = 0; j < 4; j++) file << " " << corr[j]-func[j];
        file << endl;
    }
    file.close();
    return 0;
}