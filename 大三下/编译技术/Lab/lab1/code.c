#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
char* split="\\+-*/><=();";
char keywords[][10] = {
    "if",
    "then",
    "else",
    "while",
    "do"
};
bool is_split(char c)
{
    for(int i = 0; split[i]; ++i)
    {
        if(split[i] == c) return true; 
    }
    return false;
}
int get_next(char c, int T)//return -1 means error,return -2 means terminal
{
    switch (T)
    {
    case 0: 
        if(c == '0') return 3;
        else if(isdigit(c) && c != '0') return 4;
        else if(isupper(c) || islower(c)) return 1;
        else if(is_split(c)) return 15;
        else if(c == '\n' || c == ' ') return 0;
    break;

    case 1:
        if(isdigit(c)||isupper(c) || islower(c)) return 1;
        else if(c == '.' || c == '_') return 2;
        else return -2;
    break;

    case 2:
        if(isdigit(c)||isupper(c) || islower(c)) return 2; 
        else return -2;
    break;

    case 3:
        if(c == 'o' || c == 'O') return 7;
        else if(c == 'x' || c == 'X') return 11;
        else if(c == '.') return 5;
        else return -2;
    break;

    case 4:
        if(isdigit(c)) return 4;
        else if(c == '.') return 5;
        else return -2;
    break;

    case 5:
        if(isdigit(c)) return 6; break;
    
    case 6:
        if(isdigit(c)) return 6;
        else return -2;
    break;

    case 7:
        if(c >= '0' && c <= '7') return 8;
    break;
    
    case 8:
        if(c == '.') return 9;
        else if(c >= '0' && c <= '7') return 8;
        else return -2;
    break;

    case 9:
        if(c >= '0' && c <= '7') return 10; break;

    case 10:
        if(c >= '0' && c <= '7') return 10;
        else return -2; break;
    
    case 11:
        if((c >= '0' && c <= '9') || ( c <= 'f' && c >= 'a')) return 12; break;
    
    case 12:
        if(c == '.') return 13;
        else if((c >= '0' && c <= '9') || ( c <= 'f' && c >= 'a')) return 12;
        else return -2; break;

    case 13:
        if((c >= '0' && c <= '9') || ( c <= 'f' && c >= 'a')) return 14; break;

    case 14:
        if((c >= '0' && c <= '9') || ( c <= 'f' && c >= 'a')) return 14;
        else return -2;
    break;

    case 15:
        return -2; break;

    default: 
        return -1; break;
    }
    return -1;
}
void put_word(char str[], int i, int j)
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
        for(int k = 0; k < strlen(sub); ++k) sub[k]=toupper(sub[k]);
		printf("%s",sub);
		for(int i = 8 - strlen(sub); i>=0 ; --i) putchar(' ');
		printf("_\n");
    } else {
        printf("IDN      %s\n",sub);
    }
}
void put_INT(char s[], int i, int j, int p)
{
	if(p != 10) i += 2;
	int x = 0;
	for(int k = i; k <= j; ++k){
		x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
	}
	printf("%d\n",x);
}
void put_FLOAT(char s[], int i, int j, int p)
{
	char sub[2024]; 
    strncpy(sub, s + i, j - i + 1);
    sub[j - i + 1] = '\0'; 
    if(p == 10) printf("%s\n",sub);
    else{
    	int idx = i + 2;
    	for(; idx <= j; ++idx){
    		if(s[idx] == '.') break;
		}
		double x = 0, y = 0;
		for(int k = i + 2; k < idx; ++k){
			x = x * p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
		}
		for(int k = idx + 1; k <= j; ++k){
			y = y / p + s[k] - (isdigit(s[k]) ? '0' : ('a' - 10));
		}
		printf("%.2lf\n",x + y);
	}
}
void put_type(int T, char s[], int i, int j)
{
	switch (T)
	{
		case  1:
		case  2: put_word(s, i, j);break;
		case  3:
		case  4: printf("INT10    "),put_INT(s, i, j, 10);break;
		case  6: printf("FLOAT10  "),put_FLOAT(s, i, j, 10);break;
		case  8: printf("INT8     "),put_INT(s, i, j, 8);break;
		case 10: printf("FLOAT8   "),put_FLOAT(s, i, j, 8);break;
		case 12: printf("INT16    "),put_INT(s, i, j, 16);break;
		case 14: printf("FLOAT16  "),put_FLOAT(s, i, j, 16);break;
		case 15: printf("%c\t _\n",s[i]);break;
	}
}
void scan(char s[], int len, int line)
{
    int j = 0, i = 0;
    while(s[j]){
    	int T = 0, finished = 0;
        for(i = j; s[i]; ++i){
            int next_T = get_next(s[i], T);
            if(next_T == -2){
                finished = 1;
                break;
            }
            if(next_T == -1) {
				printf("\nCompilation error in line %d , column %d:\n", line, i + 1);
				printf("| %s\n",s);
				for(int k = 0; k <= i + 1; ++k) putchar(' ');
				printf("^\n\n");
				return;
			}
			else if(next_T == 0){
				T = next_T;
				++j;
			}
            else T = next_T;
        }
        if(!s[i]) finished = 1;
        if(finished){
			put_type(T, s, j, i - 1);
			j = i;
        }
    }
}
int main()
{
    FILE *fp;
    char filename[] = "test.txt"; 
    char buffer[2024]; 
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("failed to open file:%s\n", filename);
        exit(1);
    }
    int line = 1;
    while(fgets(buffer, sizeof(buffer), fp) != NULL)
    {
    	scan(buffer,strlen(buffer),line++);
	}
    fclose(fp);
    return 0;
}