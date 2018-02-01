#include <bits/stdc++.h>

using namespace std;

#define judge_input if (msg != "") { cerr << msg << endl; a.c.clear(); break; }

void read(string s, int &p, char c, string &msg) {
    if (s[p] == c) {
        msg = "";
        ++p;
    } else {
        msg = (string)"error: expect '" + c + (string)"' but found '" + s[p] + (string)"'";
    }
}

int readint(string s, int &p, string &msg) {
    if (!isdigit(s[p]) && s[p] != '-') {
        msg = (string)"error: expect a number but found '" + s[p] + (string)"'";
        return 0;
    } else {
        int ret = 0;
        int sign = 0;
        if (s[p] == '-') {
            sign = 1;
            ++p;
            if (!isdigit(s[p])) {
                msg = (string)"error: expect a number but found '" + s[p] + (string)"'";
                return 0;
            }
        }
        while (isdigit(s[p])) {
            ret = ret * 10 + s[p] - '0';
            ++p;
        }
        msg = "";
        return sign ? -ret : ret;
    }
}

class poly {
public:
    poly() { c.clear(); }
    friend istream& operator >> (istream &in, poly &a) {
        a.c.clear();
        string s;
        in >> s;
        int i = 0;
        while (i < s.length()) {
            string msg;
            read(s, i, '(', msg);
            judge_input;

            int x = readint(s, i, msg);
            judge_input;

            read(s, i, ',', msg);
            judge_input;

            int y = readint(s, i, msg);
            judge_input;
            if (y < 0) msg = "error: parameter exponentiation cannot be nagative";
            judge_input;

            read(s, i, ')', msg);
            judge_input;
            a.c.resize(max((int)a.c.size(), y + 1));
            a.c[y] += x;
        }
        return in;
    }
    friend ostream& operator << (ostream &out, const poly &a) {
        for (int i = a.c.size() - 1; i >= 0; --i)
            if (i == a.c.size() - 1 || a.c[i] != 0) {
                if (i != a.c.size() - 1 && a.c[i] > 0)
                    out << "+";
                if (i > 0 && a.c[i] == -1) out << "-";
                else if (i > 0 && a.c[i] == 1) out << "";
                else out << a.c[i];
                if (i > 0) out << "x";
                if (i > 1) out << "^" << i;
            }
        return out;
    }
    poly operator + (const poly &rhs) {
        poly ret;
        ret.c.resize(max(c.size(), rhs.c.size()));
        for (int i = 0; i < c.size(); ++i)
            ret.c[i] += c[i];
        for (int i = 0; i < rhs.c.size(); ++i)
            ret.c[i] += rhs.c[i];
        ret.optim();
        return ret;
    }
    poly operator - (const poly &rhs) {
        poly ret;
        ret.c.resize(max(c.size(), rhs.c.size()));
        for (int i = 0; i < c.size(); ++i)
            ret.c[i] += c[i];
        for (int i = 0; i < rhs.c.size(); ++i)
            ret.c[i] -= rhs.c[i];
        ret.optim();
        return ret;
    }
    poly operator * (const int rhs) {
        poly ret = *this;
        for (int i = 0; i < ret.c.size(); ++i)
            ret.c[i] *= rhs;
        ret.optim();
        return ret;
    }
    poly operator * (const poly &rhs) {
        poly ret;
        ret.c.resize(c.size() + rhs.c.size());
        for (int i = 0; i < c.size(); ++i)
            for (int j = 0; j < rhs.c.size(); ++j)
                ret.c[i + j] += c[i] * rhs.c[j];
        ret.optim();
        return ret;
    }
    bool operator == (const poly &rhs) {
        if (c.size() != rhs.c.size()) return 0;
        for (int i = 0; i < c.size(); ++i)
            if (c[i] != rhs.c[i]) return 0;
        return 1;
    }
    void optim() {
        for (int i = c.size() - 1; i >= 1; --i)
            if (c[i] != 0) {
                c.resize(i + 1);
                return;
            }
        c.resize(1);
    }
    int solve(int x) const {
        int ans = 0;
        for (int i = c.size() - 1; i >= 0; --i)
            ans = ans * x + c[i];
        return ans;
    }
    poly derivative() {
        for (int i = 0; i < c.size() - 1; ++i)
            c[i] = (i + 1) * c[i + 1];
        c[c.size() - 1] = 0;
        optim();
        return *this;
    }
    int valid() {
        return c.size() > 0;
    }
private:
    vector<int> c;
};
