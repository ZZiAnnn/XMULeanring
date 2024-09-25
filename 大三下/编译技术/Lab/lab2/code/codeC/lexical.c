#include "lexical.h"
const char* split = "\\+-*/><=();";
char keywords[][10] = {
    "if",
    "then",
    "else",
    "while",
    "do"
};
bool is_split(char c)
{
    for (int i = 0; split[i]; ++i)
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
void ret_str(char str[], int i, int j, token* t)
{
    char sub[1024];
    strncpy(sub, str + i, j - i + 1);
    sub[j - i + 1] = '\0';

    int is_keyword = 0;
    for (int k = 0; k < sizeof(keywords) / sizeof(keywords[0]); k++) {
        if (strcmp(sub, keywords[k]) == 0) {
            is_keyword = 1;
            break;
        }
    }
    if (is_keyword) {
        for (int k = 0; k < strlen(sub); ++k) sub[k] = tolower(sub[k]);
        t->type = KEY;
        memcpy(t->data, sub, sizeof(sub));
    }
    else {
        t->type = IDN;
        memcpy(t->data, sub, sizeof(sub));
    }
}
void ret_int(char s[], int i, int j, int p, token* t)
{
    if (p != 10) i += 2;
    int x = 0;
    for (int k = i; k <= j; ++k) {
        x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    t->type = INT;
    sprintf(t->data, "%d", x);
}
void ret_float(char s[], int start_idx, int end_idx, int p, token* t)
{
    t->type = FLOAT;
    char sub[2024];
    strncpy(sub, s + start_idx, end_idx - start_idx + 1);
    sub[end_idx - start_idx + 1] = '\0';

    int idx = start_idx + 2;
    for (; idx <= end_idx; ++idx) {
        if (s[idx] == '.') break;
    }
    double x = 0, y = 0;
    for (int k = start_idx + 2; k < idx; ++k) {
        x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    for (int k = idx + 1; k <= end_idx; ++k) {
        y = y / p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
    }
    sprintf(t->data, "%lf", x);
}
void ret_split(char s[], int idx, token * t)
{
    t->type = SPLIT;
    t->data[0] = s[idx];
    t->data[1] = 0;
}
void get_type(int T, char s[], int start_idx, int end_idx, token* t)
{
    switch (T)
    {
        case  1:
        case  2: ret_str  (s, start_idx, end_idx, t);break;
        case  3:
        case  4: ret_int  (s, start_idx, end_idx, 10, t);break;
        case  6: ret_float(s, start_idx, end_idx, 10, t);break;
        case  8: ret_int  (s, start_idx, end_idx, 8,  t);break;
        case 10: ret_float(s, start_idx, end_idx, 8,  t);break;
        case 12: ret_int  (s, start_idx, end_idx, 16, t);break;
        case 14: ret_float(s, start_idx, end_idx, 16, t);break;
        case 15: ret_split(s, start_idx, t);break;
    }
}
token_seq* scan(char s[])
{
    token* seq = malloc(sizeof(token) * 1024);
    int j = 0, i = 0, seq_size = 0;
    while (s[j]) {
        int T = 0, finished = 0;
        for (i = j; s[i]; ++i) {
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
        if (!s[i]) finished = 1;
        if (T == 0) continue;
        if (finished) {
            get_type(T, s, j, i - 1,&seq[seq_size++]);
            j = i;
        }
    }
    token_seq* ret = (token_seq*)malloc(sizeof(token_seq));
    ret->token_size = seq_size;
    ret->seq = seq;
    return ret;
}
