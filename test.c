#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE *fp;
    int hangnum[300], i;
    char A;
    fp = fopen("学校体育项目.csv", "r");
    if (fp == NULL)
    {
        printf("打开文件错误\n");
        system("pause");
        exit(1);
    }
    i = 0;
    while (feof(fp) == 0)
    {
        A = fgetc(fp);
        if (A == '\n')
        {
            hangnum[i] = (int)ftell(fp);
            i++;
        }
    }
    hangnum[i] = (int)ftell(fp);
    for (i; i >= 0 ; i--)
        printf("%d\n", hangnum[i]);
    system("pause");
    return 0;
}