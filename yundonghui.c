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
    char schname[33], soprname[20], tip[300] = "����ѧУ����";
    srand(time(NULL));

    fp = fopen("ѧУ������Ŀ.csv", "w");
    fprintf(fp, "ѧУ���,ѧУ����");
    printf("����������Ŀm,Ů����Ŀw\n(����2,3),m>=0,w>=0:");
    scanf("%d,%d", &m, &w);
    if (m < 0 || w < 0)
        while (m < 0 || w < 0)
        {
            printf("����������������Ŀm,Ů����Ŀw:\n");
            scanf("%d,%d", &m, &w);
        }

    if (m)
        printf("����m��������Ŀ���ƣ�\n");
    for (i = 1; i <= m; i++)
    {
        scanf("%s", &soprname);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }

    if (w)
        printf("����w��Ů����Ŀ���ƣ�\n");
    for (i = 1; i <= w; i++)
    {
        scanf("%s", &soprname);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }
    fputc('\n', fp);
    printf("����μ��˶���ѧУ����n��");
    scanf("%d", &n);
    printf("%s", tip);
    printf("������Ŀ����");
    printf("\n����:ɽ������ѧԺ ����A���� ����B���� ����C���� ����D���� ����E����\n");
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
        printf("д�����ݳɹ�\n");
    }

    fprintf(fp, "1,1");     //ǰ����λΪ:1,1��Ϊ������Ŀ�Ա���,����0��ʾ��,1��ʾŮ
    for (j = 0; j < m; j++) //���������Ŀ���
        fprintf(fp, ",%d", 0);
    for (j; j < m + w; j++) //���Ů����Ŀ���
        fprintf(fp, ",%d", 1);
    fputc('\n', fp);

    fprintf(fp, "0,0");         //ǰ����λΪ:0,0��Ϊ������Ŀȡǰ��orǰ�������,����0��ʾȡǰ��,1��ʾȡǰ��
    for (j = 0; j < m + w; j++) //���ȡǰ������ǰ����
        fprintf(fp, ",%d", rand() % 2);

    fclose(fp); /*�ر��ļ�*/
}

void randwritecsv()
{
    int schid, sporid, i, j, k;
    int n, m, w, sch[300], spo[21], flag, score;
    FILE *scfp, *spfp, *fp;
    char schname[17], sporname[11];

    scfp = fopen("schoolname.csv", "r");
    spfp = fopen("sports.csv", "r");
    fp = fopen("ѧУ������Ŀ.csv", "w");

    srand(time(NULL));

    printf("�Ƿ��������ѧУ����,��Ů������Ŀ����?\n�����0��ʾ�������,����0��ʾ�ֶ�����:\n");
    scanf("%d", &flag);
    if (flag == 0)
    {
        printf("������ѧУ����n(1<=n<=300)��");
        scanf("%d", &n);
        if (n > 300 || n < 1)
            while (n > 300 || n < 1)
            {
                printf("����������ѧУ����n(1<=n<=300)��");
                scanf("%d", &n);
            }

        printf("����������������Ŀ����m(0<=m<=21)��");
        scanf("%d", &m);
        if (m > 21 || m < 0)
            while (m > 21 || m < 0)
            {
                printf("��������������������Ŀ����m(0<=m<=21)��");
                scanf("%d", &m);
            }

        printf("������Ů��������Ŀ����w(0<=w<=21)��");
        scanf("%d", &w);
        if (w > 21 || w < 0)
            while (w > 21 || w < 0)
            {
                printf("��������������������Ŀ����w(0<=w<=21)��");
                scanf("%d", &w);
            }
    }
    else
    {
        n = rand() % 300 + 1; //n��Χ 1-300
        m = rand() % 22;      //m��Χ 0-21
        w = rand() % 22;      //w��Χ 0-21
    }

    fprintf(fp, "ѧУ���,ѧУ����");

    for (j = 0; j < m; j++) //�������������Ŀ
    {
        sporid = rand() % 21; //�����������������Ŀ
        while (1)
        {
            flag = 1; //���
            for (k = 0; k < j; k++)
                if (spo[k] == sporid) //�ж��������������������µ������ظ�
                {
                    flag = 0; //�ظ����޸ı��
                    break;
                }
            if (flag == 0)
                sporid = rand() % 21; //�ظ��������������
            else
            {
                spo[j] = sporid; //û���ظ��ͼ�������
                break;
            }
        }
        fseek(spfp, sporid * 13, SEEK_SET);
        fscanf(spfp, "%s", &sporname);
        fprintf(fp, ",%s", sporname);
    }
    for (j = 0; j < w; j++) //�������Ů����Ŀ
    {
        sporid = rand() % 20;
        while (1)
        {
            flag = 1; //���
            for (k = 0; k < j; k++)
                if (spo[k] == sporid) //�ж��������������������µ������ظ�
                {
                    flag = 0; //�ظ����޸ı��
                    break;
                }
            if (flag == 0)
                sporid = rand() % 21; //�ظ��������������
            else
            {
                spo[j] = sporid; //û���ظ��ͼ�������
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
        schid = rand() % 300; //�������ѧУ����
        while (1)
        {
            flag = 1; //���
            for (j = 0; j < i; j++)
                if (sch[j] == schid) //�ж�����ѧУ�������µ������ظ�
                {
                    flag = 0; //�ظ����޸ı��
                    break;
                }
            if (flag == 0)
                schid = rand() % 300; //�ظ��������������
            else
            {
                sch[i] = schid; //û���ظ��ͼ�������
                break;
            }
        }
        fseek(scfp, schid * 19, SEEK_SET);
        fscanf(scfp, "%s", &schname);
        fprintf(fp, "%d,%s", i, schname);
        for (j = 0; j < m + w; j++)
        {
            score = rand() % 101; //�������������Ŀ����,��Χ0-100
            fprintf(fp, ",%d", score);
        }
        fputc('\n', fp);
    }
    fprintf(fp, "1,1");     //ǰ����λΪ:1,1��Ϊ������Ŀ�Ա���,����0��ʾ��,1��ʾŮ
    for (j = 0; j < m; j++) //���������Ŀ���
        fprintf(fp, ",%d", 0);
    for (j; j < m + w; j++) //���Ů����Ŀ���
        fprintf(fp, ",%d", 1);
    fputc('\n', fp);

    fprintf(fp, "0,0");         //ǰ����λΪ:0,0��Ϊ������Ŀȡǰ��orǰ�������,����0��ʾȡǰ��,1��ʾȡǰ��
    for (j = 0; j < m + w; j++) //���ȡǰ������ǰ����
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
        printf("ʵ��һ��\n");
        printf("---------------------------------�˶������ͳ��---------------------------------\n");
        printf("-------------------------------1.�����ɼ��ļ�����-------------------------------\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-                                                                              -\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("����һ����ѡ���ܣ�");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            system("cls");
            printf("------------------------1.�ֶ�����ѧУ����,������Ŀ���ɼ�-----------------------\n");
            printf("------------------------2.�������ѧУ����,������Ŀ���ɼ�-----------------------\n");
            printf("����һ����ѡ���ܣ�");
            scanf("%d", &com2);
            if (com2 == 1)
                writecsv();
            else if (com2 == 2)
                randwritecsv();
            else
                printf("��������!!\n");
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
