#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPOMAN_MAX 21   //男子体育项目最大值
#define SPOWOMAN_MAX 21 //女子体育项目最大值
#define SCHOOL_MAX 300  //学校个数最大值

struct Sports
{
    int id;
    char name[20];
    int score;
    int randflag;
};

struct SCHOOL
{
    int id;
    char name[20];
    int schoolscore;
    int spomanscore;
    int spowomanscore;
    struct Sports spoman[SPOMAN_MAX];
    struct Sports spowoman[SPOWOMAN_MAX];
    struct SCHOOL *next;
};

void Writecsv()
{
    FILE *fp;
    int n, i, j, m, w, temp, scanfflag;
    char schname[33], soprname[20], tip[300] = "输入学校名称";
    srand(time(NULL));

    fp = fopen("学校体育项目.csv", "w");
    if (fp == NULL)
    {
        printf("学校体育项目.csv文件创建失败\n");
        system("pause");
        exit(1);
    }

    fprintf(fp, "学校编号,学校名称");
    printf("输入男子项目m,女子项目w(例如2,3)\n");
    printf("0<=m<=%d,0<=w<=%d : ", SPOMAN_MAX, SPOWOMAN_MAX);
    scanfflag = scanf("%d,%d", &m, &w);
    if (scanfflag != 2 || m < 0 || m > SPOMAN_MAX || w < 0 || w > SPOWOMAN_MAX)
        while (scanfflag != 2 || m < 0 || m > SPOMAN_MAX || w < 0 || w > SPOWOMAN_MAX)
        {
            fflush(stdin);
            printf("输入不规范或w或m不在范围\n请重新输入男子项目m,女子项目w:\n");
            scanfflag = scanf("%d,%d", &m, &w);
        }

    if (m)
        printf("输入m个男子项目名称：\n");
    for (i = 1; i <= m; i++)
    {
        scanf("%s", &soprname);
        printf("男子项目%d写入成功\n", i);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }

    if (w)
        printf("输入w个女子项目名称：\n");
    for (i = 1; i <= w; i++)
    {
        scanf("%s", &soprname);
        printf("女子项目%d写入成功\n", i);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }
    fputc('\n', fp);
    printf("输入参加运动会学校个数n：\n");
    printf("n的范围为1<= n <=%d\n", SCHOOL_MAX);
    scanfflag = scanf("%d", &n);
    if (scanfflag != 1 || n <= 0 || n > SCHOOL_MAX)
        while (scanfflag != 1 || n <= 0 || n > SCHOOL_MAX)
        {
            fflush(stdin);
            printf("输入不规范或n不在范围\n请重新输入参加运动会学校个数n:\n");
            scanfflag = scanf("%d", &n);
        }

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
    printf("数据文件\"学校体育项目.csv\"生成成功！\n");
    printf("\"学校体育项目.csv\"文件位于: ");
    system("echo %cd%");
}

void Randwritecsv()
{
    int schid, sporid, i, j, k, scanfflag;
    int n, m, w, sch[SCHOOL_MAX], spo[SPOMAN_MAX], flag, score;
    FILE *scfp, *spfp, *fp;
    char schname[17], sporname[11];

    scfp = fopen("schoolname.csv", "r");
    spfp = fopen("sports.csv", "r");
    fp = fopen("学校体育项目.csv", "w");

    if (scfp == NULL)
    {
        printf("schoolname.csv读取失败\n");
        system("pause");
        exit(1);
    }
    if (spfp == NULL)
    {
        printf("sports.csv读取失败\n");
        system("pause");
        exit(1);
    }
    if (fp == NULL)
    {
        printf("学校体育项目.csv文件创建失败\n");
        system("pause");
        exit(1);
    }

    srand(time(NULL));

    printf("是否随机生成学校个数,男女体育项目个数?\n输入非0表示随机生成,输入0表示手动输入:\n");
    scanfflag = scanf("%d", &flag);
    if (scanfflag != 1)
        while (scanfflag != 1)
        {
            fflush(stdin);
            printf("输入不规范,请重新输入！\n");
            scanfflag = scanf("%d", &flag);
        }

    if (flag == 0)
    {
        printf("请输入学校个数n(1<=n<=%d)：", SCHOOL_MAX);
        scanfflag = scanf("%d", &n);
        if (scanfflag != 1 || n > SCHOOL_MAX || n < 1)
            while (scanfflag != 1 || n > SCHOOL_MAX || n < 1)
            {
                fflush(stdin);
                printf("请重新输入学校个数n(1<=n<=%d)：", SCHOOL_MAX);
                scanfflag = scanf("%d", &n);
            }

        printf("请输入男子体育项目个数m(0<=m<=%d)：", SPOMAN_MAX);
        scanfflag = scanf("%d", &m);
        if (scanfflag != 1 || m > SPOMAN_MAX || m < 0)
            while (scanfflag != 1 || m > SPOMAN_MAX || m < 0)
            {
                fflush(stdin);
                printf("请重新输入男子体育项目个数m(0<=m<=%d)：", SPOMAN_MAX);
                scanfflag = scanf("%d", &m);
            }

        printf("请输入女子体育项目个数w(0<=w<=%d)：", SPOWOMAN_MAX);
        scanfflag = scanf("%d", &w);
        if (scanfflag != 1 || w > SPOWOMAN_MAX || w < 0)
            while (scanfflag != 1 || w > SPOWOMAN_MAX || w < 0)
            {
                fflush(stdin);
                printf("请重新输入男子体育项目个数w(0<=w<=%d)：", SPOWOMAN_MAX);
                scanfflag = scanf("%d", &w);
            }
    }
    else
    {
        n = rand() % SCHOOL_MAX + 1;     //n范围 1-SCHOOL_MAX
        m = rand() % (SPOMAN_MAX + 1);   //m范围 0-SPOMAN_MAX
        w = rand() % (SPOWOMAN_MAX + 1); //w范围 0-SPOMAN_MAX
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
        sporid = rand() % 21;
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
    for (j = 0; j < w; j++) //输出女子项目标记
        fprintf(fp, ",%d", 1);
    fputc('\n', fp);

    fprintf(fp, "0,0");         //前面两位为:0,0即为体育项目取前三or前五名编号,后面0表示取前三,1表示取前五
    for (j = 0; j < m + w; j++) //输出取前三或者前五标记
        fprintf(fp, ",%d", rand() % 2);

    fclose(spfp);
    fclose(scfp);
    fclose(fp);
    printf("数据文件\"学校体育项目.csv\"生成成功！\n");
    printf("\"学校体育项目.csv\"文件位于: ");
    system("echo %cd%");
}

void Mainmenu()
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
}

int main()
{
    FILE *fp;
    int command, com2, scaflag;
    while (1)
    {
        Mainmenu();
        printf("输入一个数选择功能：");
        scaflag = scanf("%d", &command);
        if (scaflag != 1)
            while (scaflag != 1)
            {
                fflush(stdin);
                printf("输入不是数字,请重新输入！\n");
                scaflag = scanf("%d", &command);
            }
        switch (command)
        {
        case 1:
            system("cls");
            printf("------------------------1.手动输入学校名字,体育项目及成绩-----------------------\n");
            printf("------------------------2.随机生成学校名字,体育项目及成绩-----------------------\n");
            printf("输入一个数选择功能：");
            scaflag = scanf("%d", &com2);
            if (scaflag != 1 || com2 < 1 || com2 > 2)
                while (scaflag != 1 || com2 < 1 || com2 > 2)
                {
                    fflush(stdin);
                    printf("输入的不是数字或输入的数不符合条件,请重新输入！\n");
                    scaflag = scanf("%d", &com2);
                }
            if (com2 == 1)
                Writecsv();
            else if (com2 == 2)
                Randwritecsv();
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