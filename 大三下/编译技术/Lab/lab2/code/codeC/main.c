#include <stdio.h>
#include <stdlib.h>
#include "grammatical.h"
int main()
{
    FILE* fp;
    char filename[] = "test.txt";
    char buffer[2024];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("failed to open file:%s\n", filename);
        exit(1);
    }
    int line = 1;
    token_seq* tokens = (token_seq*)malloc(sizeof(token_seq));
    tokens->seq = (token*)malloc(sizeof(token) * 1024);
    tokens->token_size = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        token_seq* res = scan(buffer);
        for (int i = 0; i < res->token_size; ++i)
        {
            (tokens->seq[tokens->token_size]).type = (res->seq)[i].type;
            strcpy((tokens->seq[tokens->token_size++]).data, (res->seq[i]).data);
        }
        free(res);
    }
    printf("%d\n", tokens->token_size);
    for (int i = 0; i < tokens->token_size; ++i)
    {
        printf("%s ", tokens->seq[i].data);
    }
    puts("");
    parse(tokens);
    free(tokens->seq);
    free(tokens);
    fclose(fp);
    return 0;
}