#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Sports
{
    int id;
    char name[20];
    char sex[3];
    int score;
    struct Sports *next;
};

struct SCHOOL
{
    int id;
    char name[33];
    struct Sports *sphead;
    struct SCHOOL *next;
};
struct SCHOOL *head;

void writecsv()
{
    FILE *fp;
    int n, i, j, m, w, temp;
    char schname[33], soprname[20], tip[300] = "输入学校名称";
    srand(time(NULL));

    fp = fopen("学校体育项目.csv", "w");
    fprintf(fp, "学校编号,学校名称");
    printf("输入男子项目m,女子项目w\n(例如2,3),m>=0,w>=0:");
    scanf("%d,%d", &m, &w);
    if (m < 0 || w < 0)
        while (m < 0 || w < 0)
        {
            printf("请重新输入男子项目m,女子项目w:\n");
            scanf("%d,%d", &m, &w);
        }

    if (m)
        printf("输入m个男子项目名称：\n");
    for (i = 1; i <= m; i++)
    {
        scanf("%s", &soprname);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }

    if (w)
        printf("输入w个女子项目名称：\n");
    for (i = 1; i <= w; i++)
    {
        scanf("%s", &soprname);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }
    fputc('\n', fp);
    printf("输入参加运动会学校个数n：");
    scanf("%d", &n);
    printf("%s", tip);
    printf("体育项目分数");
    printf("\n例如:山东工商学院 体育A分数 体育B分数 体育C分数 体育D分数 体育E分数\n");
    for (i = 1; i <= n; i++)
    {
        scanf("%s", &schname);
        fprintf(fp, "%d,%s", i, schname);
        for (j = 1; j <= m + w; j++)
        {
            scanf("%d", &temp);
            fprintf(fp, ",%d", temp);
        }
        fputc('\n', fp);
        printf("写入数据成功\n");
    }

    fprintf(fp, "1,1");     //前面两位为:1,1即为体育项目性别编号,后面0表示男,1表示女
    for (j = 0; j < m; j++) //输出男子项目标记
        fprintf(fp, ",%d", 0);
    for (j; j < m + w; j++) //输出女子项目标记
        fprintf(fp, ",%d", 1);
    fputc('\n', fp);

    fprintf(fp, "0,0");         //前面两位为:0,0即为体育项目取前三or前五名编号,后面0表示取前三,1表示取前五
    for (j = 0; j < m + w; j++) //输出取前三或者前五标记
        fprintf(fp, ",%d", rand() % 2);

    fclose(fp); /*关闭文件*/
}

void randwritecsv()
{
    int schid, sporid, i, j, k;
    int n, m, w, sch[300], spo[21], flag, score;
    FILE *scfp, *spfp, *fp;
    char schname[17], sporname[11];

    scfp = fopen("schoolname.csv", "r");
    spfp = fopen("sports.csv", "r");
    fp = fopen("学校体育项目.csv", "w");

    srand(time(NULL));

    printf("是否随机生成学校个数,男女体育项目个数?\n输入非0表示随机生成,输入0表示手动输入:\n");
    scanf("%d", &flag);
    if (flag == 0)
    {
        printf("请输入学校个数n(1<=n<=300)：");
        scanf("%d", &n);
        if (n > 300 || n < 1)
            while (n > 300 || n < 1)
            {
                printf("请重新输入学校个数n(1<=n<=300)：");
                scanf("%d", &n);
            }

        printf("请输入男子体育项目个数m(0<=m<=21)：");
        scanf("%d", &m);
        if (m > 21 || m < 0)
            while (m > 21 || m < 0)
            {
                printf("请重新输入男子体育项目个数m(0<=m<=21)：");
                scanf("%d", &m);
            }

        printf("请输入女子体育项目个数w(0<=w<=21)：");
        scanf("%d", &w);
        if (w > 21 || w < 0)
            while (w > 21 || w < 0)
            {
                printf("请重新输入男子体育项目个数w(0<=w<=21)：");
                scanf("%d", &w);
            }
    }
    else
    {
        n = rand() % 300 + 1; //n范围 1-300
        m = rand() % 22;      //m范围 0-21
        w = rand() % 22;      //w范围 0-21
    }

    fprintf(fp, "学校编号,学校名字");

    for (j = 0; j < m; j++) //随机生成男子项目
    {
        sporid = rand() % 21; //随机生成男子体育项目
        while (1)
        {
            flag = 1; //标记
            for (k = 0; k < j; k++)
                if (spo[k] == sporid) //判断已有男子体育名字与新的有无重复
                {
                    flag = 0; //重复则修改标记
                    break;
                }
            if (flag == 0)
                sporid = rand() % 21; //重复就重新随机生成
            else
            {
                spo[j] = sporid; //没有重复就加入数组
                break;
            }
        }
        fseek(spfp, sporid * 13, SEEK_SET);
        fscanf(spfp, "%s", &sporname);
        fprintf(fp, ",%s", sporname);
    }
    for (j = 0; j < w; j++) //随机生成女子项目
    {
        sporid = rand() % 20;
        while (1)
        {
            flag = 1; //标记
            for (k = 0; k < j; k++)
                if (spo[k] == sporid) //判断已有男子体育名字与新的有无重复
                {
                    flag = 0; //重复则修改标记
                    break;
                }
            if (flag == 0)
                sporid = rand() % 21; //重复就重新随机生成
            else
            {
                spo[j] = sporid; //没有重复就加入数组
                break;
            }
        }

        fseek(spfp, sporid * 13, SEEK_SET);
        fscanf(spfp, "%s", &sporname);
        fprintf(fp, ",%s", sporname);
    }
    fputc('\n', fp);
    for (i = 0; i < n; i++)
    {
        schid = rand() % 300; //随机生成学校名字
        while (1)
        {
            flag = 1; //标记
            for (j = 0; j < i; j++)
                if (sch[j] == schid) //判断已有学校名字与新的有无重复
                {
                    flag = 0; //重复则修改标记
                    break;
                }
            if (flag == 0)
                schid = rand() % 300; //重复就重新随机生成
            else
            {
                sch[i] = schid; //没有重复就加入数组
                break;
            }
        }
        fseek(scfp, schid * 19, SEEK_SET);
        fscanf(scfp, "%s", &schname);
        fprintf(fp, "%d,%s", i, schname);
        for (j = 0; j < m + w; j++)
        {
            score = rand() % 101; //随机生成体育项目分数,范围0-100
            fprintf(fp, ",%d", score);
        }
        fputc('\n', fp);
    }
    fprintf(fp, "1,1");     //前面两位为:1,1即为体育项目性别编号,后面0表示男,1表示女
    for (j = 0; j < m; j++) //输出男子项目标记
        fprintf(fp, ",%d", 0);
    for (j; j < m + w; j++) //输出女子项目标记
        fprintf(fp, ",%d", 1);
    fputc('\n', fp);

    fprintf(fp, "0,0");         //前面两位为:0,0即为体育项目取前三or前五名编号,后面0表示取前三,1表示取前五
    for (j = 0; j < m + w; j++) //输出取前三或者前五标记
        fprintf(fp, ",%d", rand() % 2);

    fclose(spfp);
    fclose(scfp);
    fclose(fp);
}

int main()
{
    FILE *fp;
    int command, com2;
    while (1)
    {
        printf("实验一：\n");
        printf("---------------------------------运动会分数统计---------------------------------\n");
        printf("-------------------------------1.体育成绩文件生成-------------------------------\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("输入一个数选择功能：");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            system("cls");
            printf("------------------------1.手动输入学校名字,体育项目及成绩-----------------------\n");
            printf("------------------------2.随机生成学校名字,体育项目及成绩-----------------------\n");
            printf("输入一个数选择功能：");
            scanf("%d", &com2);
            if (com2 == 1)
                writecsv();
            else if (com2 == 2)
                randwritecsv();
            else
                printf("输入有误!!\n");
            system("pause");
            system("cls");
            break;

            /*default:
        break;*/
        }
    }
    system("pause");
    return 0;
}
