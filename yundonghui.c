#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPOMAN_MAX 21   //男子体育项目最大值
#define SPOWOMAN_MAX 21 //女子体育项目最大值
#define SCHOOL_MAX 300  //学校个数最大值

struct Sports
{
    int id;        //体育编号
    char name[20]; //体育名称
    int score;     //体育分数
    int ranking;   //在该体育的排名
};

struct SCHOOL
{
    int id;                               //学校编号
    char name[20];                        //学校名字
    int schoolscore;                      //学校总分
    int spomanscore;                      //学校男子项目总分
    int spowomanscore;                    //学校女子项目总分
    struct Sports spoman[SPOMAN_MAX];     //男子项目数组
    struct Sports spowoman[SPOWOMAN_MAX]; //女子项目数组
    struct SCHOOL *next;                  //指向下一个学校
};

int SPORTMAN, SPORTWOMAN;                 //全局变量:存储数据文件的男女项目个数
int SCHOOLNUMS;                           //学校个数
int sportflag[SPOMAN_MAX + SPOWOMAN_MAX]; //存放倒数第一行前三或前五标记

void sortsportid(struct SCHOOL *head, int *spflag, int *flag, int AscDesc, int *output);

void Writecsv()
{ //手动输入数据文件
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

    fprintf(fp, "学校编号,学校名字");
    printf("输入男子项目m,女子项目w(例如2,3)\n");
    printf("0<=m<=%d,0<=w<=%d : ", SPOMAN_MAX, SPOWOMAN_MAX);
    scanfflag = scanf("%d,%d", &m, &w);
    while (scanfflag != 2 || m < 0 || m > SPOMAN_MAX || w < 0 || w > SPOWOMAN_MAX)
    {
        fflush(stdin);
        printf("输入不规范或w或m不在范围\n请重新输入男子项目m,女子项目w:\n");
        scanfflag = scanf("%d,%d", &m, &w);
    }

    if (m)
        printf("输入%d个男子项目名称：\n", m);
    for (i = 1; i <= m; i++)
    {
        scanf("%s", &soprname);
        printf("男子项目%d写入成功\n", i);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }

    if (w)
        printf("输入%d个女子项目名称：\n", w);
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
        printf("学校%d数据写入成功\n", i);
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
    fflush(stdin);
    printf("是否打开\"学校体育项目.csv\"查看?(y/n)\n查看完记得关闭文件哦\n");
    if ('y' == getchar())
        system("学校体育项目.csv");
}

void Randwritecsv()
{ //随机生成数据文件函数
    int schid, sporid, i, j, k, scanfflag;
    int n, m, w, sch[SCHOOL_MAX], spo[SPOMAN_MAX], flag, score;
    FILE *scfp, *spfp, *fp;
    char schname[17], sporname[12];

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
        while (scanfflag != 1 || n > SCHOOL_MAX || n < 1)
        {
            fflush(stdin);
            printf("请重新输入学校个数n(1<=n<=%d)：", SCHOOL_MAX);
            scanfflag = scanf("%d", &n);
        }

        printf("请输入男子体育项目个数m(0<=m<=%d)：", SPOMAN_MAX);
        scanfflag = scanf("%d", &m);
        while (scanfflag != 1 || m > SPOMAN_MAX || m < 0)
        {
            fflush(stdin);
            printf("请重新输入男子体育项目个数m(0<=m<=%d)：", SPOMAN_MAX);
            scanfflag = scanf("%d", &m);
        }

        printf("请输入女子体育项目个数w(0<=w<=%d)：", SPOWOMAN_MAX);
        scanfflag = scanf("%d", &w);
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
    printf("共写入：%d条学校记录，男子项目：%d项，女子项目：%d项\n", n, m, w);
    printf("数据文件\"学校体育项目.csv\"生成成功！\n");
    printf("\"学校体育项目.csv\"文件位于: ");
    system("echo %cd%");
    fflush(stdin);
    printf("是否打开\"学校体育项目.csv\"查看?(y/n)");
    if ('y' == getchar())
        system("学校体育项目.csv");
}

void ReadFile(struct SCHOOL *head)
{ //读取文件函数
    char *str1, *str2, *str;
    char sportname[SPOMAN_MAX + SPOWOMAN_MAX][12]; //存放第一行男子项目,女子项目名字
    int i, j;
    int hangnum[SCHOOL_MAX + 3] = {0}; //存数据文件每一行的开头到文件头位置
    int hangsum;                       //存放行数0-n
    char A;
    char hang[700]; //存放每行数据
    struct SCHOOL *p = head, *q;

    FILE *fp;
    fp = fopen("学校体育项目.csv", "r");
    while (fp == NULL)
    {
        printf("数据文件\"学校体育项目.csv\"未能找到！\n");
        printf("是否重新打开？(y/n):");
        fflush(stdin);
        if (getchar() == 'y')
            fp = fopen("学校体育项目.csv", "r");
        else
        {
            printf("文件\"学校体育项目.csv\"未能打开！\n退出程序\n");
            system("pause");
            exit(1);
        }
    }
    i = 1;
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
    hangsum = i;

    rewind(fp); //重新回到文件头

    SPORTMAN = SPORTWOMAN = 0; //男女子体育项目个数清零
    SCHOOLNUMS = 0;            //学校个数清零

    fseek(fp, hangnum[hangsum - 2], SEEK_SET);
    fgets(hang, hangnum[hangsum - 1] - hangnum[hangsum - 2] - 1, fp);
    str1 = strtok(hang, ",");
    str2 = strtok(NULL, ",");
    if (strcmp(str1, "1") == 0 && strcmp(str2, "1") == 0)
    { //读取倒数第二行的男女体育项目个数信息
        while (1)
        {
            str = strtok(NULL, ",");
            if (str == NULL)
                break;
            if (strcmp(str, "0") == 0)
                SPORTMAN++;
            else if (strcmp(str, "1") == 0)
                SPORTWOMAN++;
        }
    }
    fseek(fp, hangnum[hangsum - 1], SEEK_SET);
    fgets(hang, hangnum[hangsum] - hangnum[hangsum - 1] + 1, fp);
    str1 = strtok(hang, ",");
    str2 = strtok(NULL, ",");
    if (strcmp(str1, "0") == 0 && strcmp(str2, "0") == 0)
    { //读取倒数第一行的取前三还是前五信息
        j = 0;
        while (1)
        {
            str = strtok(NULL, ",");
            if (str == NULL)
                break;
            if (strcmp(str, "0") == 0 || strcmp(str, "1") == 0)
                sportflag[j++] = atoi(str);
        }
    }

    for (i = 0; i < hangsum - 2; i++)
    {
        fseek(fp, hangnum[i], SEEK_SET);
        fgets(hang, hangnum[i + 1] - hangnum[i] - 1, fp);
        str1 = strtok(hang, ",");
        str2 = strtok(NULL, ",");
        if (strcmp(str1, "学校编号") == 0 && strcmp(str2, "学校名字") == 0)
        {
            j = 0;
            while (1)
            {
                str = strtok(NULL, ",");
                if (str == NULL)
                    break;
                strcpy(sportname[j++], str); //读取文件头一行的体育名字
            }
        }
        else
        {
            SCHOOLNUMS++;
            q = (struct SCHOOL *)malloc(sizeof(struct SCHOOL));
            q->next = NULL;
            q->id = atoi(str1);
            strcpy(q->name, str2);
            q->schoolscore = 0;
            q->spomanscore = 0;
            q->spowomanscore = 0;
            j = 0;
            while (1)
            {
                str = strtok(NULL, ",");
                if (str == NULL)
                    break;
                if (j < SPORTMAN)
                {
                    q->spoman[j].id = j;                     //体育项目编号
                    strcpy(q->spoman[j].name, sportname[j]); //体育项目名字
                    q->spoman[j].score = atoi(str);          //体育项目分数
                }
                if (j >= SPORTMAN && j < SPORTMAN + SPORTWOMAN)
                {
                    q->spowoman[j - SPORTMAN].id = j;                     //体育项目编号
                    strcpy(q->spowoman[j - SPORTMAN].name, sportname[j]); //体育项目名字
                    q->spowoman[j - SPORTMAN].score = atoi(str);          //体育项目分数
                }
                j++;
            }
            p->next = q;
            p = q;
        }
    }
    fclose(fp);
}

void put_over_data(struct SCHOOL *head)
{ //显示从文件读取的信息
    struct SCHOOL *p = head, *q;
    int i, j;
    char text1[] = "学校编号", text2[] = "学校名字";
    ReadFile(head); //调用读文件函数
    q = p->next;
    printf("%-10s%-16s", text1, text2);
    for (i = 0; i < SPORTMAN; i++)
        printf("%s%s:%d%4s", q->spoman[i].name, "男", q->spoman[i].id, "");
    for (i = 0; i < SPORTWOMAN; i++)
        printf("%s%s:%d%4s", q->spowoman[i].name, "女", q->spowoman[i].id, "");
    printf("\n");

    p = head;
    for (i = 0; i < SCHOOLNUMS; i++)
    {
        q = p->next;
        printf("%-10d%-16s", q->id, q->name);
        for (j = 0; j < SPORTMAN; j++)
            printf("%10d%4s", q->spoman[j].score, "");
        for (j = 0; j < SPORTWOMAN; j++)
            printf("%10d%4s", q->spowoman[j].score, "");
        printf("\n");
        p = q;
    }
}

void put_over_data_score(struct SCHOOL *head)
{ //显示全部信息,总分,男女总分
    struct SCHOOL *p = head, *q;
    int i, j;
    char text1[] = "学校编号", text2[] = "学校名字", text3[] = "学校总分", text4[] = "男子总分", text5[] = "女子总分";
    q = p->next;
    printf("%-10s%-16s", text1, text2);
    for (i = 0; i < SPORTMAN; i++)
        printf("%s%s:%d%4s", q->spoman[i].name, "男", q->spoman[i].id, "");
    for (i = 0; i < SPORTWOMAN; i++)
        printf("%s%s:%d%4s", q->spowoman[i].name, "女", q->spowoman[i].id, "");
    printf("%-10s%-10s%-10s\n", text3, text4, text5);

    p = head;
    for (i = 0; i < SCHOOLNUMS; i++)
    {
        q = p->next;
        printf("%-10d%-16s ", q->id, q->name);
        for (j = 0; j < SPORTMAN; j++)
            printf("%-14d", q->spoman[j].score);
        for (j = 0; j < SPORTWOMAN; j++)
            printf("%-14d", q->spowoman[j].score);
        printf("%-10d%-10d%-10d\n", q->schoolscore, q->spomanscore, q->spowomanscore);
        p = q;
    }
}

void Statotalscore(struct SCHOOL *head)
{ //统计总分函数
    int i, j, k;
    int qian3[3] = {5, 3, 2}, qian5[5] = {7, 5, 3, 2, 1};
    int rank[SCHOOL_MAX];
    struct SCHOOL *p = head, *q;
    struct SCHOOL *temp, *spscqian, *spmaxqian; //spscqian存储交换位置前驱,spmaxqian存储最大的前驱
    ReadFile(head);
    for (i = 0; i < SPORTMAN; i++) //男子体育项目分数计算
    {
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spmaxqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if ((spmaxqian->next)->spoman[i].score < q->spoman[i].score) //读出体育项目分数比较
                    spmaxqian = p;
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spmaxqian->next;
            spmaxqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spmaxqian->next->next;
            spmaxqian->next->next = temp;
        }
        p = head;
        k = 0;
        for (j = 0; j < SCHOOLNUMS; j++)
        {
            q = p->next;
            rank[k] = q->spoman[i].score;
            if (k > 0 && rank[k - 1] == rank[k])
                k--;
            q->spoman[i].ranking = k + 1; //把排名存进每个体育项目数组中
            if (sportflag[i] == 0)        //取前三名,前三名积分为:5、3、2
            {
                if (k < 3)
                {
                    q->schoolscore += qian3[k];
                    q->spomanscore += qian3[k];
                }
            }
            else if (sportflag[i] == 1) //取前五名,积分分别为:7、5、3、2、1
            {
                if (k < 5)
                {
                    q->schoolscore += qian5[k];
                    q->spomanscore += qian5[k];
                }
            }
            p = q;
            k++;
        }
    }
    for (i = 0; i < SPORTWOMAN; i++) //女子体育项目分数计算
    {
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spmaxqian = spscqian = p; //记下第j个交换位置的前驱,假设第j个为最大
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if ((spmaxqian->next)->spowoman[i].score < q->spowoman[i].score) //读出体育项目分数比较
                    spmaxqian = p;
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spmaxqian->next;
            spmaxqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spmaxqian->next->next;
            spmaxqian->next->next = temp;
        }
        p = head;
        k = 0;
        for (j = 0; j < SCHOOLNUMS; j++)
        {
            q = p->next;
            rank[k] = q->spowoman[i].score;
            if (k > 0 && rank[k - 1] == rank[k])
                k--;
            q->spowoman[i].ranking = k + 1;   //把排名存进每个体育项目数组中
            if (sportflag[i + SPORTMAN] == 0) //取前三名,前三名积分为:5、3、2
            {
                if (k < 3)
                {
                    q->schoolscore += qian3[k];
                    q->spowomanscore += qian3[k];
                }
            }
            else if (sportflag[i + SPORTMAN] == 1) //取前五名,积分分别为:7、5、3、2、1
            {
                if (k < 5)
                {
                    q->schoolscore += qian5[k];
                    q->spowomanscore += qian5[k];
                }
            }
            p = q;
            k++;
        }
    }
}

void Sortdata(struct SCHOOL *head, int command, int AscDesc, int *output)
{ //排序：command:1学校编号,2学校名字,3学校总分,4男子总分,5女子总分,AscDesc:0升序,1降序,output 1输出
    int j, k;
    struct SCHOOL *p = head, *q;
    struct SCHOOL *spqian, *spscqian, *temp;
    int sportid, scaflag, spflag, flag;
    system("cls");
    switch (command)
    {
    case 1:                              //按学校编号排序，升序or降序
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->id < q->id) //读出学校编号比较
                        spqian = p;                 //降序
                }
                else
                {
                    if ((spqian->next)->id > q->id) //读出学校编号比较
                        spqian = p;                 //升序
                }
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spqian->next;
            spqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spqian->next->next;
            spqian->next->next = temp;
        }
        break;
    case 2:                              //按学校名字排序，升序or降序
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if (AscDesc)
                {
                    if (strcmp((spqian->next)->name, q->name) < 0) //读出学校名字比较
                        spqian = p;                                //降序
                }
                else
                {
                    if (strcmp((spqian->next)->name, q->name) > 0) //读出学校名字比较
                        spqian = p;                                //升序
                }
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spqian->next;
            spqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spqian->next->next;
            spqian->next->next = temp;
        }
        break;
    case 3:                              //按学校总分排序，升序or降序
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->schoolscore < q->schoolscore) //读出学校总分比较
                        spqian = p;                                   //降序
                }
                else
                {
                    if ((spqian->next)->schoolscore > q->schoolscore) //读出学校总分比较
                        spqian = p;                                   //升序
                }
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spqian->next;
            spqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spqian->next->next;
            spqian->next->next = temp;
        }
        break;
    case 4:                              //按男子总分排序，升序or降序
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->spomanscore < q->spomanscore) //读出男子总分比较
                        spqian = p;                                   //降序
                }
                else
                {
                    if ((spqian->next)->spomanscore > q->spomanscore) //读出男子总分比较
                        spqian = p;                                   //升序
                }
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spqian->next;
            spqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spqian->next->next;
            spqian->next->next = temp;
        }
        break;
    case 5:                              //按女子总分排序，升序or降序
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->spowomanscore < q->spowomanscore) //读出女子总分比较
                        spqian = p;                                       //降序
                }
                else
                {
                    if ((spqian->next)->spowomanscore > q->spowomanscore) //读出女子总分比较
                        spqian = p;                                       //升序
                }
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spqian->next;
            spqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spqian->next->next;
            spqian->next->next = temp;
        }
        break;
    case 6: //按输入体育项目编号排序，升序or降序
        sortsportid(head, &spflag, &flag, AscDesc, output);
        break;
    }
}

void sortsportid(struct SCHOOL *head, int *spflag, int *flag, int AscDesc, int *output)
{
    struct SCHOOL *p, *q, *spqian, *spscqian, *temp;
    int scaflag, sportid, j, k;
    p = head->next;
    for (j = 0; j < SPORTMAN; j++) //输出体育男子项目名字
        printf("%s:%d, ", p->spoman[j].name, p->spoman[j].id);
    for (j = 0; j < SPORTWOMAN; j++) //输出体育女子项目名字
        printf("%s:%d, ", p->spowoman[j].name, p->spowoman[j].id);
    printf("\n\n输入体育项目编号以选择排序\n");
    scaflag = scanf("%d", &sportid);
    while (scaflag != 1)
    {
        fflush(stdin);
        printf("输入的不是数字,请重新输入！\n");
        scaflag = scanf("%d", &sportid);
    }
    p = head->next; //循环查找符合编号的体育项目
    *flag = 0;
    for (j = 0; j < SPORTMAN; j++)
        if (sportid == p->spoman[j].id)
        {
            *spflag = j;
            *flag = 1;
            break;
        }
    for (j = 0; j < SPORTWOMAN; j++)
        if (sportid == p->spowoman[j].id)
        {
            *spflag = j;
            *flag = 2;
            break;
        }
    if (*flag)
        for (j = 1; j < SCHOOLNUMS; j++) //排序学校个数-1趟
        {
            p = head;
            for (k = 0; k < j; k++) //跳过前j个已经排好序的
            {
                spqian = spscqian = p; //假设最大是第j个,记下第j个交换位置的前驱
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //查找比较交换
            {
                q = p->next;
                if (AscDesc)
                {
                    if (*flag == 1)
                    {
                        if ((spqian->next)->spoman[*spflag].score < q->spoman[*spflag].score) //读出体育项目比较
                            spqian = p;                                                       //降序
                    }
                    else if (*flag == 2)
                    {
                        if ((spqian->next)->spowoman[*spflag].score < q->spowoman[*spflag].score) //读出体育项目比较
                            spqian = p;                                                           //降序
                    }
                }
                else
                {
                    if (*flag == 1)
                    {
                        if ((spqian->next)->spoman[*spflag].score > q->spoman[*spflag].score) //读出体育项目比较
                            spqian = p;                                                       //升序
                    }
                    else if (*flag == 2)
                    {
                        if ((spqian->next)->spowoman[*spflag].score > q->spowoman[*spflag].score) //读出体育项目比较
                            spqian = p;                                                           //升序
                    }
                }
                p = q;
            }
            temp = spscqian->next;
            spscqian->next = spqian->next;
            spqian->next = temp;
            temp = spscqian->next->next;
            spscqian->next->next = spqian->next->next;
            spqian->next->next = temp;
        }
    else
    {
        *output = 0;
        printf("查无此项！\n");
    }
}

void Mainmenu()
{ //主菜单
    printf("实验一：\n");
    printf("---------------------------------运动会分数统计---------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("-------------------------------1.体育成绩文件生成-------------------------------\n");
    printf("----------------------------2.体育成绩文件读取并显示----------------------------\n");
    printf("---------------3.按学校编号、名称、学校总分、男女团体总分排序输出---------------\n");
    printf("-----------------------4.按学校编号查询学校某个项目的情况-----------------------\n");
    printf("---------------------5.按项目编号查询取得前三或前五名的学校---------------------\n");
    printf("-----------------------------------6.退出程序-----------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------2019年12月21日--谭剑编写\n");
}

void menu1makefile()
{ //菜单1
    int com2, scaflag;
    system("cls");
    printf("------------------------1.手动输入学校名字,体育项目及成绩-----------------------\n");
    printf("------------------------2.随机生成学校名字,体育项目及成绩-----------------------\n");
    printf("----------------------------------3.返回上一级？--------------------------------\n");
    printf("输入一个数选择功能：");
    scaflag = scanf("%d", &com2);
    while (scaflag != 1 || com2 < 1 || com2 > 3)
    {
        fflush(stdin);
        printf("输入的不是数字或输入的数不符合条件,请重新输入！\n");
        scaflag = scanf("%d", &com2);
    }
    if (com2 == 1)
        Writecsv();
    else if (com2 == 2)
        Randwritecsv();
    if (com2 != 3)
        system("pause");
    system("cls");
}

void menu3sortput(struct SCHOOL *head)
{ //菜单3
    int com2, scaflag, output;
    Statotalscore(head); //计算总分
    while (1)
    {
        system("cls");
        printf("-------------------------------1.按学校编号降序输出-----------------------------\n");
        printf("-------------------------------2.按学校编号升序输出-----------------------------\n\n");
        printf("-------------------------------3.按学校名字降序输出-----------------------------\n");
        printf("-------------------------------4.按学校名字升序输出-----------------------------\n\n");
        printf("-------------------------------5.按学校总分降序输出-----------------------------\n");
        printf("-------------------------------6.按学校总分升序输出-----------------------------\n\n");
        printf("-------------------------------7.按男子总分降序输出-----------------------------\n");
        printf("-------------------------------8.按男子总分升序输出-----------------------------\n\n");
        printf("-------------------------------9.按女子总分降序输出-----------------------------\n");
        printf("------------------------------10.按女子总分升序输出-----------------------------\n\n");
        printf("--------------------------11.按输入体育项目编号降序输出-------------------------\n");
        printf("--------------------------12.按输入体育项目编号升序输出-------------------------\n\n");
        printf("---------------------------------13.返回上一级？--------------------------------\n");
        printf("输入一个数选择功能：");
        scaflag = scanf("%d", &com2);
        while (scaflag != 1 || com2 < 1 || com2 > 13)
        {
            fflush(stdin);
            printf("输入的不是数字或输入的数不符合条件,请重新输入！\n");
            scaflag = scanf("%d", &com2);
        }
        if (com2 == 13)
            break;
        else
        {
            output = 1;
            Sortdata(head, com2 / 2 + com2 % 2, com2 % 2, &output); //按要求排序
            if (output)
                put_over_data_score(head); //输出排序后结果
        }
        system("pause");
        system("cls");
    }
    system("cls");
}

void menu4(struct SCHOOL *head)
{ //菜单4
    int i, j;
    struct SCHOOL *p, *q;
    int schid, spoid, schflag = 0, spoflag = 0, scaflag;
    system("cls");
    Statotalscore(head); //计算总分
    printf("学校名字--学校编号\n");
    p = head;
    for (i = 0; i < SCHOOLNUMS; i++)
    {
        q = p->next;
        printf("%s--%d\t", q->name, q->id);
        p = q;
        if (i % 6 == 0)
            printf("\n");
    }
    p = head->next;
    printf("\n\n体育项目名字--编号\n");
    for (i = 0; i < SPORTMAN; i++)
        printf("%s(%s)--%d\n", p->spoman[i].name, "男", p->spoman[i].id);
    for (i = 0; i < SPORTWOMAN; i++)
        printf("%s(%s)--%d\n", p->spowoman[i].name, "女", p->spowoman[i].id);
    printf("\n输入学校编号,体育项目编号\n例如：1,2\n");
    scaflag = scanf("%d,%d", &schid, &spoid);
    while (scaflag != 2)
    {
        printf("输入不规范，请重新输入\n");
        fflush(stdin);
        scaflag = scanf("%d,%d", &schid, &spoid);
    }
    p = head;
    for (i = 0; i < SCHOOLNUMS; i++)
    {
        q = p->next;
        if (q->id == schid)
        {
            schflag = 1;
            break;
        }
        p = q;
    }
    if (schflag)
    {
        for (i = 0; i < SPORTMAN; i++)
            if (spoid == q->spoman[i].id)
            {
                spoflag = 1;
                break;
            }
        for (j = 0; j < SPORTWOMAN; j++)
            if (spoid == q->spowoman[j].id)
            {
                spoflag = 2;
                break;
            }
        if (spoflag == 1)
            printf("%s的%s(%s)成绩为第%d名\n", q->name, q->spoman[i].name, "男", q->spoman[i].ranking);
        else if (spoflag == 2)
            printf("%s的%s(%s)成绩为第%d名\n", q->name, q->spowoman[j].name, "女", q->spowoman[j].ranking);
        else
            printf("%s没有此项体育项目！\n", q->name);
    }
    else
        printf("查无此校！\n");
    printf("\n%s全部体育项目情况：\n", q->name);
    if (schflag && spoflag)
    {
        for (i = 0; i < SPORTMAN; i++)
            printf("%s(%s)第%d名\n", q->spoman[i].name, "男", q->spoman[i].ranking);
        for (i = 0; i < SPORTWOMAN; i++)
            printf("%s(%s)第%d名\n", q->spowoman[i].name, "女", q->spowoman[i].ranking);
    }
    system("pause");
    system("cls");
}

void menu5(struct SCHOOL *head)
{                                                 //菜单5
    int output = 0, spoid, spflag, scaflag, flag; //spflag存下标，flag判断男1女2项目
    int i, j;
    struct SCHOOL *p, *q;
    Statotalscore(head);
    sortsportid(head, &spflag, &flag, 1, &output); //1降序
    if (flag == 1)
    {
        if (sportflag[spflag]) //男子项目取前五
        {
            p = head->next;
            while (p->spoman[spflag].ranking <= 5)
            {
                printf("第%d名%s\n", p->spoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
        else //男子项目取前三
        {
            p = head->next;
            while (p->spoman[spflag].ranking <= 3)
            {
                printf("第%d名%s\n", p->spoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
    }
    else if (flag == 2)
    {
        if (sportflag[spflag + SPORTMAN]) //女子项目取前五
        {
            p = head->next;
            while (p->spowoman[spflag].ranking <= 5)
            {
                printf("第%d名%s\n", p->spowoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
        else //女子项目取前三
        {
            p = head->next;
            while (p->spowoman[spflag].ranking <= 3)
            {
                printf("第%d名%s\n", p->spowoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
    }
    else
        printf("没有这个体育项目，请重新输入！\n");
    system("pause");
    system("cls");
}

int main()
{
    FILE *fp;
    int command, scaflag;
    struct SCHOOL *head, *p, *q;
    head = (struct SCHOOL *)malloc(sizeof(struct SCHOOL));
    head->next = NULL;

    while (1)
    {
        Mainmenu();
        printf("输入一个数选择功能：");
        scaflag = scanf("%d", &command);
        while (scaflag != 1)
        {
            fflush(stdin);
            system("cls");
            Mainmenu();
            printf("输入不是数字,请重新输入！\n");
            scaflag = scanf("%d", &command);
        }
        if (command == 6)
            break;
        switch (command)
        {
        case 1:
            menu1makefile();
            break;
        case 2:
            system("cls");
            put_over_data(head);
            system("pause");
            system("cls");
            break;
        case 3:
            menu3sortput(head);
            break;
        case 4:
            menu4(head);
            break;
        case 5:
            menu5(head);
            break;
        default:
            printf("输入的命令有误，请重新输入！\n");
            system("pause");
            system("cls");
            break;
        }
    }
    p = head;
    while (p)
    {
        q = p;
        p = q->next;
        free(q);
    }
    system("pause");
    return 0;
}