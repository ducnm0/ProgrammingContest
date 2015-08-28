/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Duc
 */

#include <iostream>
#include <fstream>

#define C11

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11

#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>

#endif

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define countBit __builtin_popcount
#define countBit64 __builtin_popcountl

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007

using namespace std;

#ifndef GLOBAL_H
#define GLOBAL_H

string toYesNo(bool b) {
    return b ? "YES" : "NO";
}

#endif


template<class T>
class Iterator {
public:
    virtual bool hasNext() const = 0;

    virtual T next() = 0;
};

template<class T>
class Iterable {
public:
    virtual Iterator<T> *iterator() const = 0;
};


template<class T, class UnaryPredicate>
bool any(const Iterable<T> &iterable, const UnaryPredicate &pred) {
    auto it = iterable.iterator();
    while (it->hasNext()) {
        if (pred(it->next())) {
            return true;
        }
    }
    return false;
}

template<class T, class UnaryPredicate>
bool all(const Iterable<T> &iterable, const UnaryPredicate &pred) {
    auto it = iterable.iterator();
    while (it->hasNext()) {
        if (!pred(it->next())) {
            return false;
        }
    }
    return true;
}

// O(sqrt(n))
bool isPrime(int64 n) {
    for (int64 i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// O(sqrtn*logn)
set<int64> findDivisors(int64 n) {
    set<int64> ret;
    ret.insert(1);
    ret.insert(n);
    for (int64 i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ret.insert(i);
            ret.insert(n / i);
        }
    }
    return ret;
}

template<class T>
class DivisorIterator : public Iterator<T> {
    T cur, next_, n;

public:
    DivisorIterator(T n) {
        assert(n > 0);
        this->n = n;
        cur = 0;
        next_ = 1;
    }

    virtual bool hasNext() const {
        return next_ != -1;
    }

    virtual T next() {
        cur = next_;
        if (next_ * next_ < n) {
            next_ = n / next_;
        } else if (next_ * next_ == n) {
            next_ = -1;
        } else {
            next_ = n / next_ + 1;
            bool found = false;
            while (next_ * next_ <= n) {
                if (n % next_ == 0) {
                    found = true;
                    break;
                }
                next_++;
            }
            if (!found) {
                next_ = -1;
            }
        }
        return cur;
    }
};

template<class T>
class DivisorIterable : public Iterable<T> {
    T n;
public:
    DivisorIterable(T n) {
        this->n = n;
    }

    virtual Iterator<T> *iterator() const {
        return new DivisorIterator<T>(n);
    }
};

template<class T>
DivisorIterable<T> divisors(T n) {
    return DivisorIterable<T>(n);
}

template<class T>
class DigitIterator : public Iterator<T> {
    T n;

public:
    DigitIterator(T n) {
        assert(n > 0);
        this->n = n;
    }

    virtual bool hasNext() const {
        return n > 0;
    }

    virtual T next() {
        T ret = n % 10;
        n /= 10;
        return ret;
    }
};

template<class T>
class DigitIterable : public Iterable<T> {
    T n;
public:
    DigitIterable(T n) {
        this->n = n;
    }

    virtual Iterator<T> *iterator() const {
        return new DigitIterator<T>(n);
    }
};

template<class T>
DigitIterable<T> digits(T n) {
    return DigitIterable<T>(n);
}

template<class T>
void extendedEuclid(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    T x2;
    extendedEuclid(b, a % b, x2, x);
    y = x2 - (a / b) * x;
}

template<class T>
T modulo(int64 a, T b) {
    T r = a % b;
    if (r < 0)
        r += b;
    return r;
}

template<class T>
T modularInverse(T a, T m) {
    T x, y;
    extendedEuclid(a, m, x, y);
    return modulo(x, m);
}

template<class T>
bool isPalindromic(T x) {
    int n = x;
    int rev = 0;
    while (n > 0) {
        int d = n % 10;
        rev = rev * 10 + d;
        n /= 10;
    }
    return x == rev;
}


bool isLuckyDigit(int d) {
    return d == 4 || d == 7;
}

bool isLucky(int n) {
    return all(digits(n), isLuckyDigit);
}

class TaskA {
public:
    void solve(std::istream &in, std::ostream &out) {
        int n;
        in >> n;
        out << toYesNo(any(divisors(n), isLucky));
    }
};


int main() {
    TaskA solver;
    std::istream &in(std::cin);
    std::ostream &out(std::cout);
    solver.solve(in, out);
    return 0;
}
