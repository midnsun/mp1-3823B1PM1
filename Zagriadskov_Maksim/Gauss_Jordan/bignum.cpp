#include "bignum.hpp"

const static BUINT_TYPE half_type_bits = sizeof(BUINT_TYPE) * 4;
const static BUINT_TYPE half_max_value = (1ull << half_type_bits) - 1;
const static BUINT_TYPE max_value = half_max_value + ~half_max_value;
biguint::biguint() {}

biguint::biguint(const BUINT_TYPE& var) {
    data.push_back(var);
}

biguint::biguint(const biguint& b) {
    this->data = b.data;
}

biguint::~biguint() {
    
}

void biguint::normilize() {
    while (!((data[data.size() - 1])) && data.size() > 1) data.erase(data.end() - 1);
}

std::ostream& operator << (std::ostream& stream, const biguint &b) {
    if (b.data.size() == 0)
        return stream << "0";
    stream << std::hex << (uint64_t)b.data[b.data.size() - 1];
    for (size_t i = b.data.size() - 1; i > 0; --i) stream << std::setfill('0') << std::setw(sizeof(BUINT_TYPE)*2) << (uint64_t)b.data[i - 1];
    return stream;
}

biguint& biguint::operator = (const biguint& other) {
    if (&other != this) {
        data = other.data;
    }
    return *this;
}

inline biguint& biguint::operator = (const BUINT_TYPE &other) {
    data.clear();
    data.push_back(other);
    return *this;
}
    
biguint biguint::operator + (const biguint &b) const {
    biguint ans = *this;
    ans += b;
    return ans;
}

biguint biguint::operator + (const BUINT_TYPE& n) const {
        biguint ans = n;
        return *this + ans;
}

biguint& biguint::operator += (const biguint &b) {
    BUINT_TYPE left = 0;
    BUINT_TYPE right = 0;
    BUINT_TYPE tmp;
    if (b.data.size() > this->data.size()) this->data.resize(b.data.size());
    
    for (size_t c = 0; c < this->data.size(); c++) {
        if (c < b.data.size()) tmp = b.data[c];
        else tmp = 0;
        right = left + (this->data[c] & half_max_value) + (tmp & half_max_value);
        left = (right >> half_type_bits) + (this->data[c] >> half_type_bits) + (tmp >> half_type_bits);
        this->data[c] = ((left & half_max_value) << half_type_bits) + (right & half_max_value);
        left >>= half_type_bits;
    }
    if (left) this->data.push_back(left);
    return *this;
}

biguint& biguint::operator += (const BUINT_TYPE &b) {
    size_t c = 0;
    BUINT_TYPE left = 0;
    BUINT_TYPE right = 0;
    if (data.size() == 0) *this = 0;
    
    right = left + (data[0] & half_max_value) + (b & half_max_value);
    left = (right >> half_type_bits) + (data[0] >> half_type_bits) + (b >> half_type_bits);
    data[0] = ((left & half_max_value) << half_type_bits) + (right & half_max_value);
    left >>= half_type_bits;
    
    while (left && ++c < data.size()) {
        right = left + (data[c] & half_max_value);
        left = (right >> half_type_bits) + (data[c] >> half_type_bits);
        data[c] = ((left & half_max_value) << half_type_bits) + (right & half_max_value);
        left >>= half_type_bits;
    }
    
    if (left) data.push_back(left);
    return *this;
}
    
biguint biguint::operator - (const biguint &b) const {
    biguint ans = *this;
    ans -= b;
    return ans;
}
    
biguint biguint::operator - (const BUINT_TYPE& b) const {
        biguint ans = b;
        return *this - ans;
}

biguint& biguint::operator -= (const biguint& b) {
    BUINT_TYPE excess = 0;
    BUINT_TYPE tmp = 0;
    
    for (size_t c = 0; c < data.size(); c++) {
        if (excess <= data[c]) {
            this->data[c] -= excess;
            excess = 0;
        }
        if (c < b.data.size()) tmp = b.data[c];
        else tmp = 0;
        if (excess >= 1 && tmp == max_value) continue;
        if (tmp + excess > data[c]) {
            this->data[c] = max_value - tmp + data[c] + 1 - excess;
            excess = 1;
            continue;
        }
        else {
            this->data[c] -= tmp;
            excess = 0;
        }
    }
    
    normilize();
    return *this;
}

biguint& biguint::operator -= (const BUINT_TYPE& b) {
    biguint temp = b;
    *this -= temp;
    return *this;
}
    
BUINT_TYPE biguint::to_uint() const { return data[0]; }
uint64_t biguint::t8_t64() {
    if (*this == 0) return 0;
    uint64_t ans = 0;
    uint64_t tmp;
    size_t s = (sizeof(uint64_t) / sizeof(uint8_t) < data.size() ? sizeof(uint64_t) / sizeof(uint8_t) : data.size());
    for (size_t i = 0; i < s; i++) {
        tmp = data[i];
        ans += (tmp << (sizeof(BUINT_TYPE) * 8 * i));
    }
    return ans;
}
void biguint::t64_t8(uint64_t b) {
    if (b == 0) {
        *this = 0;
        return;
    }
    data.clear();
    while (b > 0) {
        data.push_back(b & 0xff);
        b >>= 8;
    }
    
}

biguint& biguint::operator ++ () {
    *this += 1;
    return *this;
}

biguint biguint::operator ++ (int b) {
    biguint ans = *this;
    *this += 1;
    return ans;
}

biguint& biguint::operator -- () {
    *this -= 1;
    return *this;
}

biguint biguint::operator -- (int b) {
    biguint ans = *this;
    *this -= 1;
    return ans;
}
    
biguint biguint::operator * (const biguint &b) const { //(a+b) * (c+d)
    biguint ans = 0;
    for (size_t c = 0; c < b.data.size(); c++)
        ans += (*this * b.data[c]).cell_left_shift(c);
    
    return ans;
}
    
biguint biguint::operator * (const BUINT_TYPE &b) const { //ab + cd
    if (b == 0) return 0;
    biguint ans = 0;
    biguint tmp;
    BUINT_TYPE bd, ac, bcLeft, bcRight, adLeft, adRight;
    
    for (size_t c = 0; c < data.size(); c++) {
        bd = (data[c] & half_max_value) * (b & half_max_value);
        ac = (data[c] >> half_type_bits) * (b >> half_type_bits);
        bcRight = (((data[c] & half_max_value) * (b >> half_type_bits) & half_max_value) << half_type_bits);
        adRight = (((b & half_max_value) * (data[c] >> half_type_bits) & half_max_value) << half_type_bits);
        bcLeft = ((data[c] & half_max_value) * (b >> half_type_bits) >> half_type_bits);
        adLeft = ((b & half_max_value) * (data[c] >> half_type_bits) >> half_type_bits);

        tmp = ac;
        tmp += bcLeft;
        tmp += adLeft;
        tmp.cell_left_shift(1);
        tmp += bd;
        tmp += bcRight;
        tmp += adRight;
        tmp.cell_left_shift(c);
        ans += tmp;
    }
    return ans;
}

biguint& biguint::operator *= (const biguint &b) {
    *this = *this * b;
    return *this;
}

biguint& biguint::operator *= (const BUINT_TYPE &b) {
    *this = *this * b;
    return *this;
}

bool biguint::operator == (const biguint& b) const {
    if (data.size() != b.data.size()) return false;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] != b.data[i]) return false;
    }
    return true;
}

bool biguint::operator == (const BUINT_TYPE& n) const {
    if (n == 0) return (data.size() == 0 || (data.size() == 1 && data[0] == 0));
    else return (data.size() == 1) && (data[0] == n);
}
    
bool biguint::operator < (const biguint& b) const {
    if (data.size() < b.data.size()) return true;
    if (data.size() > b.data.size()) return false;
    size_t i;
    for (i = data.size(); i > 0; i--) {
        if (data[i - 1] == b.data[i - 1]) {
            continue;
        }
        else {
            break;
        }
    }
    return i && (data[i - 1] < b.data[i - 1]);
}

bool biguint::operator < (const BUINT_TYPE& b) const {
    if (data.size() == 0) return (b > 0);
    if (data.size() > 1) return false;
    return data[0] < b;
}
    
bool biguint::operator > (const biguint& b) const {
    if (data.size() > b.data.size()) return true;
    if (data.size() < b.data.size()) return false;
    size_t i;
    for (i = data.size(); i > 0; --i) {
        if (data[i - 1] == b.data[i - 1]) continue;
        else break;
    }
    return i && (data[i - 1] > b.data[i - 1]);
}

bool biguint::operator > (const BUINT_TYPE& b) const {
    for (size_t i = data.size() - 1; i > 0; --i) {
        if (data[i] != 0) {
            return true;
        }
    }
    return data[0] > b;
}

bool biguint::operator >= (const biguint& b) const {
    if (data.size() > b.data.size()) return 1;
    if (data.size() < b.data.size()) return 0;
    size_t i;
    for (i = data.size(); i > 0; i--) {
        if (data[i - 1] == b.data[i - 1]) continue;
        else break;
    }
    return !i || (data[i - 1] >= b.data[i - 1]);
}

bool biguint::operator >= (const BUINT_TYPE& b) const {
    if (data.size() == 0) return b == 0;
    if (data.size() > 1) return true;
    return data[0] >= b;
}

bool biguint::operator <= (const biguint& b) const {
    if (data.size() < b.data.size()) return 1;
    if (data.size() > b.data.size()) return 0;
    size_t i;
    for (i = data.size(); i > 0; i--) {
        if (data[i - 1] == b.data[i - 1]) continue;
        else break;
    }
    return !i || (data[i - 1] <= b.data[i - 1]);
}

bool biguint::operator <= (const BUINT_TYPE& b) const {
    if (data.size() == 0) return (b >= 0);
    if (data.size() > 1) return false;
    return data[0] <= b;
}

bool biguint::operator != (const biguint& b) const {
    if (data.size() != b.data.size()) return true;
    size_t i;
    for (i = data.size(); i > 0; --i) {
        if (data[i - 1] == b.data[i - 1]) continue;
        else break;
    }
    return i && (data[i - 1] != b.data[i - 1]);
}

bool biguint::operator != (const BUINT_TYPE& b) const {
    return !(*this == b);
}

biguint biguint::operator << (const size_t& n) const {
    biguint res = *this;
    res <<= n;
    return res;
}

biguint& biguint::operator <<= (const size_t& n) { //in progress
    this->data.resize(this->data.size() + n / sizeof(BUINT_TYPE) + 1);
    
    
    
    //if (!*(this->data.end() - 1)) this->data.erase(this->data.end() - 1);
    return *this;
}

biguint biguint::operator >> (const size_t& n) const {
    biguint res = *this;
    res >>= n;
    return res;
}

biguint& biguint::operator >>= (const size_t& n) { //in progress

    return *this;
}

biguint& biguint::cell_left_shift(const size_t& n) {
    if (n == 0) return *this;
    if (*this == 0) {
        if (data.size() == 0) *this = 0;
        return *this;
    }
    this->data.insert(data.begin(), n, 0);
    return *this;
}

biguint& biguint::cell_right_shift(const size_t& n) {
    if (n == 0) return *this;
    if (*this == 0) return *this;
    this->data.erase(data.begin(), data.begin() + n);
    return *this;
}

void biguint::simpledivision(biguint n, const biguint& d, biguint& q, biguint &r) { //n - делимое, d - делитель, q - неполн. частное, r - остаток
    if (d == 0)
        throw simple_error("DIVISIOV BY ZERO");
    biguint temp;
    q.data.clear();
    
    while (n >= d) {
        q.cell_left_shift(1);
        temp = d;
        while (n > temp) {
            temp.cell_left_shift(1);
        }
        temp.cell_right_shift(1);
        while (n >= temp) {
            n -= temp;
            ++q;
        }
    }
    if (q.data.size() == 0) q = 0;
    r = n;
}

void biguint::shortdivision(const BUINT_TYPE& d, biguint& q, biguint& r) const {
    if (d == 1) {
        q = *this;
        r = 0;
        return;
    }
    biguint temp;
    biguint right, left, res = 0;
    q = 0;
    r = 0;
    if (d == 0)
        throw simple_error("DIVISIOV BY ZERO");

    for (int64_t c = (int64_t)data.size() - 1; c >= 0; --c) {
        r += data[c];

        if (r < d || r.data.size() > 1) {
            if (r.data.size() == 1) {
                do {
                    if (c == 0)
                        return;
                    r.cell_left_shift(1);
                    q.cell_left_shift(1);
                    r += data[--c];
                } while (r == 0);
            }
            left = 0;
            right = max_value;
            while (left <= right) {
                res = left + (right - left).data[0] / 2;
                temp = res;
                temp *= d;
                if (temp > r) {
                    right = res - 1;
                }
                else if ((r - temp) >= d) {
                    left = res + 1;
                }
                else {
                    break;
                }
            }
            temp = res * d;
            temp.normilize();
            while (temp > r) {
                --res;
                temp -= d;
            }
            while ((r - temp) >= d) {
                ++res;
                temp += d;
            }
            r -= temp;
            q += res;
        }
        else {
            q += r.data[0] / d; //to_uint
            r = r.data[0] % d;
        }
        if (c > 0) {
            r.cell_left_shift(1);
            q.cell_left_shift(1);
        }
    }
}

biguint biguint::binarydivision(const biguint& d) const {
    biguint ans;
    biguint left, right;
    if (d.data.size() == 0)
        throw simple_error("DIVISIOV BY ZERO");
    if (d.data.size() == 1) {
        shortdivision(d.data[0], ans, left);
        return ans;
    }
    if (*this < d) {
        ans = 0;
        return ans;
    }
    ans = *this;
    ans.cell_right_shift(d.data.size() - 1);
    right = ans;
    left = ans;
    right /= d.data[d.data.size() - 1];
    if (d.data[d.data.size() - 1] == max_value) left.cell_right_shift(1);
    else left /= d.data[d.data.size() - 1] + 1;

    while (left <= right) {
        ans = left + (right - left) / 2;
        if (ans * d > *this) {
            right = ans - 1;
        }
        else if ((*this - ans * d) >= d) {
            left = ans + 1;
        }
        else {
            break;
        }
    }
    while (ans * d > *this) {
        --ans;
    }
    while ((*this - ans * d) >= d) {
        ++ans;
    }
    return ans; //n = q*d + r q - ? -> 0 <= n - q*d < d -> q*d <= n
}

biguint& biguint::operator /= (const biguint& b) {
    *this = binarydivision(b);
    return *this;
}

biguint& biguint::operator /= (const BUINT_TYPE& b) {
    biguint dummy;
    biguint temp = *this;
    temp.shortdivision(b, *this, dummy);
    return *this;
}

biguint biguint::operator / (const biguint& b) const {
    return binarydivision(b);
}

biguint biguint::operator / (const BUINT_TYPE& b) const {
    biguint ans;
    biguint dummy;
    shortdivision(b, ans, dummy);
    return ans;
}

biguint& biguint::operator %= (const biguint& b) {
    *this -= binarydivision(b) * b;
    return *this;
}

biguint& biguint::operator %= (const BUINT_TYPE& b) {
    biguint dummy;
    biguint temp = *this;
    temp.shortdivision(b, dummy, *this);
    return *this;
}

biguint biguint::operator % (const biguint& b) const {
    return *this - binarydivision(b) * b;
}

biguint biguint::operator % (const BUINT_TYPE& b) const {
    biguint ans;
    biguint dummy;
    shortdivision(b, dummy, ans);
    return ans;
}

biguint biguint::gcd(biguint a, biguint b) {
    a.normilize();
    b.normilize();
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

double biguint::newtondivision(const biguint& d) const {
    if (data.size() > d.data.size()) return NAN;
    if (data.size() < d.data.size()) return 0.0;
    return static_cast<double>(data[data.size() - 1]) / d.data[d.data.size() - 1];
}

/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */

bigint::bigint() {
    num = 0;
    sign = 0;
}

bigint::bigint(const BINT_TYPE& var) {
    num = abs(var);
    sign = var < 0;
}

bigint::bigint(const BUINT_TYPE& var) {
    num = var;
    sign = 0;
}

bigint::bigint(const bigint& b) {
    num = b.num;
    sign = b.sign;
}

bigint::bigint(const biguint& b) {
    num = b;
    sign = 0;
}

bigint::~bigint() {
    
}

inline void bigint::normilize() { sign = sign && (num != 0); }

std::ostream& operator << (std::ostream& stream, const bigint &b) {
    if (b.sign) stream << "-";
    stream << b.num;
    return stream;
}

bigint& bigint::operator = (const bigint& other) {
    if (&other != this) {
        sign = other.sign;
        num = other.num;
    }
    return *this;
}

bigint& bigint::operator = (const biguint& other) {
    sign = 0;
    num = other;
    return *this;
}

inline bigint& bigint::operator = (const BINT_TYPE &other) {
    num = abs(other);
    sign = other < 0;
    return *this;
}

bigint bigint::operator + (const bigint &b) const {
    bigint ans = *this;
    ans += b;
    return ans;
}

bigint bigint::operator + (const BINT_TYPE& n) const {
        bigint ans = n;
        return *this + ans;
}

bigint& bigint::operator += (const bigint &b) {
    int t = b.sign + sign;
    if (t == 1) {
        if (num < b.num) {
                sign = b.sign;
                num = b.num - num;
        }
        else num -= b.num;
    }
    else num += b.num;
    normilize();
    return *this;
}

bigint& bigint::operator += (const BINT_TYPE &b) {
    return *this += bigint(b);
}
                                                                 
bigint& bigint::operator - () {
    if (num == 0) return *this;
    if (sign) sign = 0;
    else sign = 1;
    return *this;
}
            
bigint bigint::operator - (const bigint &b) const {
    bigint ans = *this;
    ans -= b;
    return ans;
}

bigint bigint::operator - (const BINT_TYPE& b) const {
        return *this - bigint(b);
}

bigint& bigint::operator -= (const bigint& b) {
    int t = sign + b.sign;
    if (t == 1) num += b.num;
    else {
        if (num < b.num) {
            sign = !b.sign;
            num = b.num - num;
        }
        else num -= b.num;
    }
    normilize();
    return *this;
}

bigint& bigint::operator -= (const BINT_TYPE& b) {
    return *this -= bigint(b);
}

bigint& bigint::operator ++ () {
    *this += 1;
    return *this;
}

bigint bigint::operator ++ (int b) {
    bigint ans = *this;
    *this += 1;
    return ans;
}

bigint& bigint::operator -- () {
    *this -= 1;
    return *this;
}

bigint bigint::operator -- (int b) {
    bigint ans = *this;
    *this -= 1;
    return ans;
}

bigint bigint::operator * (const bigint &b) const { //(a+b) * (c+d)
    bigint ans = *this;
    ans *= b;
    return ans;
}

bigint bigint::operator * (const BINT_TYPE &b) const { //ab + cd
    bigint ans = *this;
    ans *= b;
    return ans;
}

bigint& bigint::operator *= (const bigint &b) {
    num *= b.num;
    sign = (sign != b.sign);
    return *this;
}

bigint& bigint::operator *= (const BINT_TYPE &b) {
    num *= abs(b);
    sign = (sign != (b < 0));
    return *this;
}

bool bigint::operator == (const bigint& b) const {
    if (sign != b.sign) return false;
    else return num == b.num;
}

bool bigint::operator == (const BINT_TYPE& n) const {
    if (num == 0) return !n;
    if (sign != n < 0) return false;
    else return num == abs(n);
}

bool bigint::operator < (const bigint& b) const {
    int var = sign + b.sign;
    if (var == 1) return sign;
    else return num < b.num;
}

bool bigint::operator < (const BINT_TYPE& b) const {
    int var = sign + (b < 0);
    if (var == 1) return sign;
    else return num < abs(b);
}

bool bigint::operator > (const bigint& b) const {
    int var = sign + b.sign;
    if (var == 1) return !sign;
    else return num > b.num;
}

bool bigint::operator > (const BINT_TYPE& b) const {
    int var = sign + (b < 0);
    if (var == 1) return !sign;
    else return num > abs(b);
}

bool bigint::operator >= (const bigint& b) const {
    int var = sign + b.sign;
    if (var == 1) return !sign;
    else return num >= b.num;
}

bool bigint::operator >= (const BINT_TYPE& b) const {
    int var = sign + (b < 0);
    if (var == 1) return !sign;
    else return num >= abs(b);
}

bool bigint::operator <= (const bigint& b) const {
    int var = sign + b.sign;
    if (var == 1) return sign;
    else return num <= b.num;
}

bool bigint::operator <= (const BINT_TYPE& b) const {
    int var = sign + (b < 0);
    if (var == 1) return sign;
    else return num <= abs(b);
}

bool bigint::operator != (const bigint& b) const {
    if (sign != b.sign) return true;
    else return num != b.num;
}

bool bigint::operator != (const BINT_TYPE& b) const {
    if (sign != b < 0) return true;
    else return num != abs(b);
}

bigint bigint::operator << (const size_t& n) const {
    bigint res = *this;
    res <<= n;
    return res;
}

bigint& bigint::operator <<= (const size_t& n) { //in progress
    return *this;
}

bigint bigint::operator >> (const size_t& n) const {
    bigint res = *this;
    res >>= n;
    return res;
}

bigint& bigint::operator >>= (const size_t& n) { //in progress
    return *this;
}

bigint& bigint::operator /= (const bigint& b) {
    num /= b.num;
    sign = (sign != b.sign);
    return *this;
}

bigint& bigint::operator /= (const BINT_TYPE& b) {
    num /= abs(b);
    sign = (sign != b < 0);
    return *this;
}

bigint bigint::operator / (const bigint& b) const {
    bigint ans = *this;
    ans /= b;
    return ans;
}

bigint bigint::operator / (const BINT_TYPE& b) const {
    bigint ans = *this;
    ans /= b;
    return ans;
}

bigint& bigint::operator %= (const bigint& b) {
    num %= b.num;
    return *this;
}

bigint& bigint::operator %= (const BINT_TYPE& b) {
    num %= abs(b);
    return *this;
}

bigint bigint::operator % (const bigint& b) const {
    bigint ans = *this;
    ans %= b;
    return ans;
}

bigint bigint::operator % (const BINT_TYPE& b) const {
    bigint ans = *this;
    ans %= abs(b);
    return ans;
}

biguint& bigint::b_abs(){
    return num;
}

biguint bigint::b_abs() const {
    return num;
}

std::string bigint::bigint_to_string() const {
    if (*this == 0) return "0";
    std::string str = "";
    if (sign) str += "-";
    biguint tmp = this->num;
    biguint div, mod;
    std::cout << "started\n";
    while (tmp > 0) {
        tmp.shortdivision(10000000000000000000ull, div, mod);
        std::cout << tmp << " " << div << " " << mod << std::endl;
        if (mod == 0)
            str = "0000000000000000000" + str;
        else 
            str = std::to_string(mod.to_uint()) + str;
        tmp = div;
    }
    std::cout << "ended\n" << std::endl;
    return str;
}

/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */

bigrational::bigrational() {}

bigrational::bigrational(const int8_t& var) {
    num = static_cast<BINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const uint8_t& var) {
    num = static_cast<BUINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const int16_t& var) {
    num = static_cast<BINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const uint16_t& var) {
    num = static_cast<BUINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const int32_t& var) {
    num = static_cast<BINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const uint32_t& var) {
    num = static_cast<BUINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const int64_t& var) {
    num = static_cast<BINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const uint64_t& var) {
    num = static_cast<BUINT_TYPE>(var);
    denum = 1;
}

bigrational::bigrational(const float& var) {
    float f = var;
    uint32_t tmp = *reinterpret_cast<uint32_t*>(&f);

    if (!isfinite(var)) {
        denum = 0;
        if (var > 0.0f) num = 1;
        if (var < 0.0f) num = -1;
        return;
    }
    if (isnan(var)) {
        denum = 0;
        num = 0;
    }

    uint32_t sign = ((tmp & 0x80000000) >> 31);
    int32_t exp = ((tmp & 0x7F800000) >> 23) - 127;
    uint32_t mant = (tmp & 0x7FFFFF) + 0x800000;
    if (exp > 0) {
        num = (1ull << (exp % (sizeof(BUINT_TYPE) * 8)));
        num.b_abs().cell_left_shift(exp / (sizeof(BUINT_TYPE) * 8));
        num *= mant;
        denum = 0x800000;
    }
    else if (exp < 0) {
        num = mant;
        exp = abs(exp);
        denum = (1ull << (exp % (sizeof(BUINT_TYPE) * 8)));
        denum.cell_left_shift(exp / (sizeof(BUINT_TYPE) * 8));
        denum *= 0x800000;
    }
    else {
        num = mant;
        denum = 0x800000;
    }
    if (sign) num *= -1;
    normalize();

}

bigrational::bigrational(const double& var) {
    double f = var;
    uint64_t tmp = *reinterpret_cast<uint64_t*>(&f);

    if (!isfinite(var)) {
        denum = 0;
        if (var > 0.0f) num = 1;
        if (var < 0.0f) num = -1;
        return;
    }
    if (isnan(var)) {
        denum = 0;
        num = 0;
    }
    uint64_t sign = ((tmp & 0x8000000000000000) >> 63);
    int64_t exp = ((tmp & 0x7FF0000000000000) >> 52) - 1023;
    uint64_t mant = (tmp & 0xFFFFFFFFFFFFF) + (1ull << 52);
    if (exp > 0) {
        num = (1ull << (exp % (sizeof(BUINT_TYPE) * 8)));
        num.b_abs().cell_left_shift(exp / (sizeof(BUINT_TYPE) * 8));
        num *= mant;
        denum = (1ull << 52);
    }
    else if (exp < 0) {
        num = mant;
        exp = abs(exp);
        denum = (1ull << (exp % (sizeof(BUINT_TYPE) * 8)));
        denum.cell_left_shift(exp / (sizeof(BUINT_TYPE) * 8));
        denum *= (1ull << 52);
    }
    else {
        num = mant;
        denum = (1ull << 52);
    }
    if (sign) num *= -1;
    normalize();
}

bigrational::bigrational(const bigint& b) {
    num = b;
    denum = 1;
}

bigrational::bigrational(const biguint& b) {
    num = b;
    denum = 1;
}

bigrational::bigrational(const bigrational& b) {
    num = b.num;
    denum = b.denum;
}

bigrational::bigrational(const uint64_t& n, const uint64_t& d) {
    num = n;
    denum = d;
}

bigrational::~bigrational() {}

void bigrational::normalize() {
    if (num == 0) {
        denum = 1;
        return;
    }
    biguint tmp = biguint::gcd(num.b_abs(), denum);
    num /= tmp;
    denum /= tmp;
}

void bigrational::rawprint() const {
    std::cout << std::hex << num << "/" << denum;
}

void bigrational::floatprint() const {
    std::string str = std::to_string(num / denum);
    str += std::to_string((num.b_abs() % denum).newtondivision(denum)).substr(1);
    std::cout << str << std::endl;
}

double bigrational::to_double() const {
    std::string str = std::to_string(num / denum);
    str += std::to_string((num.b_abs() % denum).newtondivision(denum)).substr(1);
    return std::stod(str);
}

std::ostream& operator << (std::ostream& stream, const bigrational& b) {
    if (b == 0) {
        stream << "0";
        return stream;
    }
    if (b.num < 0) stream << "-";
    std::string str = "";
    biguint tmp = b.num.b_abs();
    biguint div, mod;
    while (tmp > 0) {
        tmp.shortdivision(10000000000000000000ull, div, mod);
        if (mod == 0)
            str = "0000000000000000000" + str;
        else
            str = std::to_string(mod.to_uint()) + str;
        tmp = div;
    }
    stream << str;
    if (b.denum != 1) {
        stream << "/";
        str = "";
        tmp = b.denum;
        while (tmp > 0) {
            tmp.shortdivision(10000000000000000000ull, div, mod);
            if (mod == 0)
                str = "0000000000000000000" + str;
            else
                str = std::to_string(mod.to_uint()) + str;
            tmp = div;
        }
        stream << str;
    }
    return stream;
}

std::istream& operator >> (std::istream& stream, bigrational& b) {
    std::string str;
    size_t pos;
    stream >> str;

    if (str != "") {
        pos = str.find("/");
        if (pos == std::string::npos) {
            b.num = std::stoull(str);
            b.denum = 1;
        }
        else {
            b.num = std::stoull(str.substr(0, pos));
            b.denum = std::stoull(str.substr(pos + 1));
        }
    }
    return stream;
}

bigrational& bigrational::operator = (const bigrational& other) {
    num = other.num;
    denum = other.denum;
    return *this;
}

bigrational& bigrational::operator += (const bigrational& b) {
    num *= b.denum;
    num += b.num * denum;
    denum *= b.denum;
    normalize();
    return *this;
}

bigrational bigrational::operator + (const bigrational& b) const {
    bigrational res = *this;
    res += b;
    return res;
}

bigrational& bigrational::operator -= (const bigrational& b) {
    num *= b.denum;
    num -= b.num * denum;
    denum *= b.denum;
    normalize();
    return *this;
}

bigrational bigrational::operator - (const bigrational& b) const {
    bigrational res = *this;
    res -= b;
    return res;
}

bigrational& bigrational::operator *= (const bigrational& b) {
    num *= b.num;
    denum *= b.denum;
    normalize();
    return *this;
}

bigrational bigrational::operator * (const bigrational& b) const {
    bigrational res = *this;
    res *= b;
    return res;
}

bigrational& bigrational::operator /= (const bigrational& b) {
    if (b.num == 0) throw simple_error("DIVISION BY ZERO");
    num *= b.denum;
    denum *= b.num.b_abs();
    if (b.num < 0) - num;
    normalize();
    return *this;
}

bigrational bigrational::operator / (const bigrational& b) const {
    bigrational ans = *this;
    ans /= b;
    return ans;
}

bool bigrational::operator == (const bigrational& b) const {
    return (num == b.num && denum == b.denum);
}

bool bigrational::operator != (const bigrational& b) const {
    return (num != b.num || denum != b.denum);
}

bool bigrational::operator < (const bigrational& b) const {
    return (num*b.denum < b.num*denum);
}

bool bigrational::operator <= (const bigrational& b) const {
    return (num*b.denum <= b.num*denum);
}

bool bigrational::operator > (const bigrational& b) const {
    return (num*b.denum > b.num*denum);
}

bool bigrational::operator >= (const bigrational& b) const {
    return (num*b.denum >= b.num*denum);
}

bigrational& bigrational::operator ++ () {
    num += denum;
    return *this;
}

bigrational& bigrational::operator -- () {
    num -= denum;
    return *this;
}

bigrational bigrational::operator ++ (int b) {
    bigrational ans = *this;
    num += denum;
    return ans;
}

bigrational bigrational::operator -- (int b) {
    bigrational ans = *this;
    num -= denum;
    return ans;
}

bigrational abs(const bigrational& b) {
    bigrational ans = b;
    ans.num = ans.num.b_abs();
    return ans;
}

bigrational& bigrational::operator - () {
    -num;
    return *this;
}

bool operator == (const bigrational& r, const universal_zero& l) { return r == 0; }

bool operator != (const bigrational& r, const universal_zero& l) { return r != 0; }

bool operator == (const universal_zero& r, const bigrational& l) { return l == 0; }

bool operator != (const universal_zero& r, const bigrational& l) { return l != 0; }

std::string bigrational::bigrational_to_string() const {
    std::string res = "";
    if (*this == 0) {
        res = "0";
        return res;
    }
    if (this->num < 0) res += "-";
    std::string str = "";
    biguint tmp = this->num.b_abs();
    biguint div, mod;
    while (tmp > 0) {
        tmp.shortdivision(10000000000000000000ull, div, mod);
        if (mod == 0)
            str = "0000000000000000000" + str;
        else 
            str = std::to_string(mod.to_uint()) + str;
        tmp = div;
    }
    res += str;
    if (denum != 1) {
        res += "/";
        str = "";
        tmp = this->denum;
        while (tmp > 0) {
            tmp.shortdivision(10000000000000000000ull, div, mod);
            if (mod == 0)
                str = "0000000000000000000" + str;
            else
                str = std::to_string(mod.to_uint()) + str;
            tmp = div;
        }
        res += str;
    }
    return res;
}
std::string std::to_string(const bigrational& b) { return b.bigrational_to_string(); }

std::string std::to_string(const bigint& b) { return b.bigint_to_string(); }
