#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPOMAN_MAX 21   //����������Ŀ���ֵ
#define SPOWOMAN_MAX 21 //Ů��������Ŀ���ֵ
#define SCHOOL_MAX 300  //ѧУ�������ֵ

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
    char schname[33], soprname[20], tip[300] = "����ѧУ����";
    srand(time(NULL));

    fp = fopen("ѧУ������Ŀ.csv", "w");
    if (fp == NULL)
    {
        printf("ѧУ������Ŀ.csv�ļ�����ʧ��\n");
        system("pause");
        exit(1);
    }

    fprintf(fp, "ѧУ���,ѧУ����");
    printf("����������Ŀm,Ů����Ŀw(����2,3)\n");
    printf("0<=m<=%d,0<=w<=%d : ", SPOMAN_MAX, SPOWOMAN_MAX);
    scanfflag = scanf("%d,%d", &m, &w);
    if (scanfflag != 2 || m < 0 || m > SPOMAN_MAX || w < 0 || w > SPOWOMAN_MAX)
        while (scanfflag != 2 || m < 0 || m > SPOMAN_MAX || w < 0 || w > SPOWOMAN_MAX)
        {
            fflush(stdin);
            printf("���벻�淶��w��m���ڷ�Χ\n����������������Ŀm,Ů����Ŀw:\n");
            scanfflag = scanf("%d,%d", &m, &w);
        }

    if (m)
        printf("����m��������Ŀ���ƣ�\n");
    for (i = 1; i <= m; i++)
    {
        scanf("%s", &soprname);
        printf("������Ŀ%dд��ɹ�\n", i);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }

    if (w)
        printf("����w��Ů����Ŀ���ƣ�\n");
    for (i = 1; i <= w; i++)
    {
        scanf("%s", &soprname);
        printf("Ů����Ŀ%dд��ɹ�\n", i);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }
    fputc('\n', fp);
    printf("����μ��˶���ѧУ����n��\n");
    printf("n�ķ�ΧΪ1<= n <=%d\n", SCHOOL_MAX);
    scanfflag = scanf("%d", &n);
    if (scanfflag != 1 || n <= 0 || n > SCHOOL_MAX)
        while (scanfflag != 1 || n <= 0 || n > SCHOOL_MAX)
        {
            fflush(stdin);
            printf("���벻�淶��n���ڷ�Χ\n����������μ��˶���ѧУ����n:\n");
            scanfflag = scanf("%d", &n);
        }

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
    printf("�����ļ�\"ѧУ������Ŀ.csv\"���ɳɹ���\n");
    printf("\"ѧУ������Ŀ.csv\"�ļ�λ��: ");
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
    fp = fopen("ѧУ������Ŀ.csv", "w");

    if (scfp == NULL)
    {
        printf("schoolname.csv��ȡʧ��\n");
        system("pause");
        exit(1);
    }
    if (spfp == NULL)
    {
        printf("sports.csv��ȡʧ��\n");
        system("pause");
        exit(1);
    }
    if (fp == NULL)
    {
        printf("ѧУ������Ŀ.csv�ļ�����ʧ��\n");
        system("pause");
        exit(1);
    }

    srand(time(NULL));

    printf("�Ƿ��������ѧУ����,��Ů������Ŀ����?\n�����0��ʾ�������,����0��ʾ�ֶ�����:\n");
    scanfflag = scanf("%d", &flag);
    if (scanfflag != 1)
        while (scanfflag != 1)
        {
            fflush(stdin);
            printf("���벻�淶,���������룡\n");
            scanfflag = scanf("%d", &flag);
        }

    if (flag == 0)
    {
        printf("������ѧУ����n(1<=n<=%d)��", SCHOOL_MAX);
        scanfflag = scanf("%d", &n);
        if (scanfflag != 1 || n > SCHOOL_MAX || n < 1)
            while (scanfflag != 1 || n > SCHOOL_MAX || n < 1)
            {
                fflush(stdin);
                printf("����������ѧУ����n(1<=n<=%d)��", SCHOOL_MAX);
                scanfflag = scanf("%d", &n);
            }

        printf("����������������Ŀ����m(0<=m<=%d)��", SPOMAN_MAX);
        scanfflag = scanf("%d", &m);
        if (scanfflag != 1 || m > SPOMAN_MAX || m < 0)
            while (scanfflag != 1 || m > SPOMAN_MAX || m < 0)
            {
                fflush(stdin);
                printf("��������������������Ŀ����m(0<=m<=%d)��", SPOMAN_MAX);
                scanfflag = scanf("%d", &m);
            }

        printf("������Ů��������Ŀ����w(0<=w<=%d)��", SPOWOMAN_MAX);
        scanfflag = scanf("%d", &w);
        if (scanfflag != 1 || w > SPOWOMAN_MAX || w < 0)
            while (scanfflag != 1 || w > SPOWOMAN_MAX || w < 0)
            {
                fflush(stdin);
                printf("��������������������Ŀ����w(0<=w<=%d)��", SPOWOMAN_MAX);
                scanfflag = scanf("%d", &w);
            }
    }
    else
    {
        n = rand() % SCHOOL_MAX + 1;     //n��Χ 1-SCHOOL_MAX
        m = rand() % (SPOMAN_MAX + 1);   //m��Χ 0-SPOMAN_MAX
        w = rand() % (SPOWOMAN_MAX + 1); //w��Χ 0-SPOMAN_MAX
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
        sporid = rand() % 21;
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
    for (j = 0; j < w; j++) //���Ů����Ŀ���
        fprintf(fp, ",%d", 1);
    fputc('\n', fp);

    fprintf(fp, "0,0");         //ǰ����λΪ:0,0��Ϊ������Ŀȡǰ��orǰ�������,����0��ʾȡǰ��,1��ʾȡǰ��
    for (j = 0; j < m + w; j++) //���ȡǰ������ǰ����
        fprintf(fp, ",%d", rand() % 2);

    fclose(spfp);
    fclose(scfp);
    fclose(fp);
    printf("�����ļ�\"ѧУ������Ŀ.csv\"���ɳɹ���\n");
    printf("\"ѧУ������Ŀ.csv\"�ļ�λ��: ");
    system("echo %cd%");
}

void Mainmenu()
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
}

int main()
{
    FILE *fp;
    int command, com2, scaflag;
    while (1)
    {
        Mainmenu();
        printf("����һ����ѡ���ܣ�");
        scaflag = scanf("%d", &command);
        if (scaflag != 1)
            while (scaflag != 1)
            {
                fflush(stdin);
                printf("���벻������,���������룡\n");
                scaflag = scanf("%d", &command);
            }
        switch (command)
        {
        case 1:
            system("cls");
            printf("------------------------1.�ֶ�����ѧУ����,������Ŀ���ɼ�-----------------------\n");
            printf("------------------------2.�������ѧУ����,������Ŀ���ɼ�-----------------------\n");
            printf("����һ����ѡ���ܣ�");
            scaflag = scanf("%d", &com2);
            if (scaflag != 1 || com2 < 1 || com2 > 2)
                while (scaflag != 1 || com2 < 1 || com2 > 2)
                {
                    fflush(stdin);
                    printf("����Ĳ������ֻ������������������,���������룡\n");
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