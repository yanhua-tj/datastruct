#include <stdio.h>
#include <stdlib.h>
int main()
{
    int scaflag, a, b;
    scaflag = scanf("%d,%d", &a, &b);
    if(scaflag != 2)
        while (scaflag != 2)
        {
            fflush(stdin);
            printf("%d,%d,%d\n", a, b, scaflag);
            scaflag = scanf("%d,%d", &a, &b);
        }
    printf("%d,%d,%d\n", a, b, scaflag);
    system("pause");
    return 0;
}