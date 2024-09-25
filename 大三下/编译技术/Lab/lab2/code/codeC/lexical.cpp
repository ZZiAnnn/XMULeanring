#include "lexical.hpp"
#include <stdexcept>
std::string split = "\\+-*/><=();";
std::vector<std::string> keywords= {
    "if",
    "then",
    "else",
    "while",
    "do"
};
bool is_split(char c)
{
    for (int i = 0; i < split.size(); ++i)
    {
        if (split[i] == c) return true;
    }
    return false;
}
int get_next(char c, int T)//return -1 means error,return -2 means terminal
{
    switch (T)
    {
    case 0:
        if (c == '0') return 3;
        else if (isdigit(c) && c != '0') return 4;
        else if (isupper(c) || islower(c)) return 1;
        else if (is_split(c)) return 15;
        else if (c == '\n' || c == ' ' || c == '\t') return 0;
        break;

    case 1:
        if (isdigit(c) || isupper(c) || islower(c)) return 1;
        else if (c == '.' || c == '_') return 2;
        else return -2;
        break;

    case 2:
        if (isdigit(c) || isupper(c) || islower(c)) return 2;
        else return -2;
        break;

    case 3:
        if (c == 'o' || c == 'O') return 7;
        else if (c == 'x' || c == 'X') return 11;
        else if (c == '.') return 5;
        else return -2;
        break;

    case 4:
        if (isdigit(c)) return 4;
        else if (c == '.') return 5;
        else return -2;
        break;

    case 5:
        if (isdigit(c)) return 6; break;

    case 6:
        if (isdigit(c)) return 6;
        else return -2;
        break;

    case 7:
        if (c >= '0' && c <= '7') return 8;
        break;

    case 8:
        if (c == '.') return 9;
        else if (c >= '0' && c <= '7') return 8;
        else return -2;
        break;

    case 9:
        if (c >= '0' && c <= '7') return 10; break;

    case 10:
        if (c >= '0' && c <= '7') return 10;
        else return -2; break;

    case 11:
        if ((c >= '0' && c <= '9') || (c <= 'f' && c >= 'a')) return 12; break;

    case 12:
        if (c == '.') return 13;
        else if ((c >= '0' && c <= '9') || (c <= 'f' && c >= 'a')) return 12;
        else return -2; break;

    case 13:
        if ((c >= '0' && c <= '9') || (c <= 'f' && c >= 'a')) return 14; break;

    case 14:
        if ((c >= '0' && c <= '9') || (c <= 'f' && c >= 'a')) return 14;
        else return -2;
        break;

    case 15:
        return -2; break;

    default:
        return -1; break;
    }
    return -1;
}
token ret_str(const std::string& str, int i, int j)
{
    token ret;
    std::string sub = str.substr(i, j - i + 1);

    int is_keyword = 0;
    for (int k = 0; k < keywords.size(); k++) {
        if (sub == keywords[k]) {
            is_keyword = 1;
            break;
        }
    }
    if (is_keyword) {
        for (int k = 0; k < sub.size(); ++k) sub[k] = tolower(sub[k]);
        ret.type = KEY;
        ret.data = sub;
    } 
    else {
        ret.type = IDN;
        ret.data = sub;
    }
    return ret;
}
token ret_int(const std::string& s, int i, int j, int p)
{
    token ret;
    if (p != 10) i += 2;
    int x = 0;
    for (int k = i; k <= j; ++k) {
        x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    ret.type = INT;
    ret.data = std::to_string(x);
    return ret;
}
token ret_float(const std::string& s, int i, int j, int p)
{
    token ret;
    ret.type = FLOAT;
    std::string sub = s.substr(i, j - i + 1);

    int idx = i + 2;
    for (; idx <= j; ++idx) {
        if (s[idx] == '.') break;
    }
    double x = 0, y = 0;
    for (int k = i + 2; k < idx; ++k) {
        x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    for (int k = idx + 1; k <= j; ++k) {
        y = y / p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    ret.data = std::to_string(x);
    return ret;
}
token ret_split(const std::string& s, int idx)
{
    token ret;
    ret.type = SPLIT;
    ret.data = s[idx];
    return ret;
}
token get_type(int T, const std::string& s, int i, int j)
{
    int base = 10; 
    switch (T)
    {
    case 1:
    case 2:
        return ret_str(s, i, j);
    case 3:
    case 4:
    case 6:
        return (T == 6) ? ret_float(s, i, j, base) : ret_int(s, i, j, base);
    case 8:
    case 10:
        base = 8;
        return (T == 10) ? ret_float(s, i, j, base) : ret_int(s, i, j, base);
    case 12:
    case 14:
        base = 16;
        return (T == 14) ? ret_float(s, i, j, base) : ret_int(s, i, j, base);
    case 15:
        return ret_split(s, i);
    default:
        throw std::invalid_argument("Unsupported type");
    }
}

std::vector<token> scan(const std::string s)
{
    std::vector<token> seq;
    int j = 0, i = 0;
    while (j < s.size()) {
        int T = 0, finished = 0;
        for (i = j; i < s.size(); ++i) {
            int next_T = get_next(s[i], T);
            if (next_T == -2) {
                finished = 1;
                break;
            }
            if (next_T == -1) {
                printf("\nLexical error in line, column %d:\n", i + 1);
                printf("| %s\n", s);
                for (int k = 0; k <= i + 1; ++k) putchar(' ');
                printf("^\n\n");
                exit(0);
            }
            else if (next_T == 0) {
                T = next_T;
                ++j;
            }
            else T = next_T;
        }
        if (i == s.size()) finished = 1;
        if (T == 0) continue;
        if (finished) {
            seq.push_back(get_type(T, s, j, i - 1));
            j = i;
        }
    }
    return move(seq);
}
