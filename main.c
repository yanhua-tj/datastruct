#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    int i;
    fp = fopen("test.csv","w");
    for(i=0;i<100;i++)
        fprintf(fp,"%d,ѧУ����,ѧУ���,������Ŀ\n",i);
    fclose(fp);
    system("pause");
    return 0;
}
