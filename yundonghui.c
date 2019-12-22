#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPOMAN_MAX 21   //����������Ŀ���ֵ
#define SPOWOMAN_MAX 21 //Ů��������Ŀ���ֵ
#define SCHOOL_MAX 300  //ѧУ�������ֵ

struct Sports
{
    int id;        //�������
    char name[20]; //��������
    int score;     //��������
    int ranking;   //�ڸ�����������
};

struct SCHOOL
{
    int id;                               //ѧУ���
    char name[20];                        //ѧУ����
    int schoolscore;                      //ѧУ�ܷ�
    int spomanscore;                      //ѧУ������Ŀ�ܷ�
    int spowomanscore;                    //ѧУŮ����Ŀ�ܷ�
    struct Sports spoman[SPOMAN_MAX];     //������Ŀ����
    struct Sports spowoman[SPOWOMAN_MAX]; //Ů����Ŀ����
    struct SCHOOL *next;                  //ָ����һ��ѧУ
};

int SPORTMAN, SPORTWOMAN;                 //ȫ�ֱ���:�洢�����ļ�����Ů��Ŀ����
int SCHOOLNUMS;                           //ѧУ����
int sportflag[SPOMAN_MAX + SPOWOMAN_MAX]; //��ŵ�����һ��ǰ����ǰ����

void sortsportid(struct SCHOOL *head, int *spflag, int *flag, int AscDesc, int *output);

void Writecsv()
{ //�ֶ����������ļ�
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
    while (scanfflag != 2 || m < 0 || m > SPOMAN_MAX || w < 0 || w > SPOWOMAN_MAX)
    {
        fflush(stdin);
        printf("���벻�淶��w��m���ڷ�Χ\n����������������Ŀm,Ů����Ŀw:\n");
        scanfflag = scanf("%d,%d", &m, &w);
    }

    if (m)
        printf("����%d��������Ŀ���ƣ�\n", m);
    for (i = 1; i <= m; i++)
    {
        scanf("%s", &soprname);
        printf("������Ŀ%dд��ɹ�\n", i);
        strcat(tip, " ");
        strcat(tip, soprname);
        fprintf(fp, ",%s", soprname);
    }

    if (w)
        printf("����%d��Ů����Ŀ���ƣ�\n", w);
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
        printf("ѧУ%d����д��ɹ�\n", i);
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
    fflush(stdin);
    printf("�Ƿ��\"ѧУ������Ŀ.csv\"�鿴?(y/n)\n�鿴��ǵùر��ļ�Ŷ\n");
    if ('y' == getchar())
        system("ѧУ������Ŀ.csv");
}

void Randwritecsv()
{ //������������ļ�����
    int schid, sporid, i, j, k, scanfflag;
    int n, m, w, sch[SCHOOL_MAX], spo[SPOMAN_MAX], flag, score;
    FILE *scfp, *spfp, *fp;
    char schname[17], sporname[12];

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
        while (scanfflag != 1 || n > SCHOOL_MAX || n < 1)
        {
            fflush(stdin);
            printf("����������ѧУ����n(1<=n<=%d)��", SCHOOL_MAX);
            scanfflag = scanf("%d", &n);
        }

        printf("����������������Ŀ����m(0<=m<=%d)��", SPOMAN_MAX);
        scanfflag = scanf("%d", &m);
        while (scanfflag != 1 || m > SPOMAN_MAX || m < 0)
        {
            fflush(stdin);
            printf("��������������������Ŀ����m(0<=m<=%d)��", SPOMAN_MAX);
            scanfflag = scanf("%d", &m);
        }

        printf("������Ů��������Ŀ����w(0<=w<=%d)��", SPOWOMAN_MAX);
        scanfflag = scanf("%d", &w);
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
    printf("��д�룺%d��ѧУ��¼��������Ŀ��%d�Ů����Ŀ��%d��\n", n, m, w);
    printf("�����ļ�\"ѧУ������Ŀ.csv\"���ɳɹ���\n");
    printf("\"ѧУ������Ŀ.csv\"�ļ�λ��: ");
    system("echo %cd%");
    fflush(stdin);
    printf("�Ƿ��\"ѧУ������Ŀ.csv\"�鿴?(y/n)");
    if ('y' == getchar())
        system("ѧУ������Ŀ.csv");
}

void ReadFile(struct SCHOOL *head)
{ //��ȡ�ļ�����
    char *str1, *str2, *str;
    char sportname[SPOMAN_MAX + SPOWOMAN_MAX][12]; //��ŵ�һ��������Ŀ,Ů����Ŀ����
    int i, j;
    int hangnum[SCHOOL_MAX + 3] = {0}; //�������ļ�ÿһ�еĿ�ͷ���ļ�ͷλ��
    int hangsum;                       //�������0-n
    char A;
    char hang[700]; //���ÿ������
    struct SCHOOL *p = head, *q;

    FILE *fp;
    fp = fopen("ѧУ������Ŀ.csv", "r");
    while (fp == NULL)
    {
        printf("�����ļ�\"ѧУ������Ŀ.csv\"δ���ҵ���\n");
        printf("�Ƿ����´򿪣�(y/n):");
        fflush(stdin);
        if (getchar() == 'y')
            fp = fopen("ѧУ������Ŀ.csv", "r");
        else
        {
            printf("�ļ�\"ѧУ������Ŀ.csv\"δ�ܴ򿪣�\n�˳�����\n");
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

    rewind(fp); //���»ص��ļ�ͷ

    SPORTMAN = SPORTWOMAN = 0; //��Ů��������Ŀ��������
    SCHOOLNUMS = 0;            //ѧУ��������

    fseek(fp, hangnum[hangsum - 2], SEEK_SET);
    fgets(hang, hangnum[hangsum - 1] - hangnum[hangsum - 2] - 1, fp);
    str1 = strtok(hang, ",");
    str2 = strtok(NULL, ",");
    if (strcmp(str1, "1") == 0 && strcmp(str2, "1") == 0)
    { //��ȡ�����ڶ��е���Ů������Ŀ������Ϣ
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
    { //��ȡ������һ�е�ȡǰ������ǰ����Ϣ
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
        if (strcmp(str1, "ѧУ���") == 0 && strcmp(str2, "ѧУ����") == 0)
        {
            j = 0;
            while (1)
            {
                str = strtok(NULL, ",");
                if (str == NULL)
                    break;
                strcpy(sportname[j++], str); //��ȡ�ļ�ͷһ�е���������
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
                    q->spoman[j].id = j;                     //������Ŀ���
                    strcpy(q->spoman[j].name, sportname[j]); //������Ŀ����
                    q->spoman[j].score = atoi(str);          //������Ŀ����
                }
                if (j >= SPORTMAN && j < SPORTMAN + SPORTWOMAN)
                {
                    q->spowoman[j - SPORTMAN].id = j;                     //������Ŀ���
                    strcpy(q->spowoman[j - SPORTMAN].name, sportname[j]); //������Ŀ����
                    q->spowoman[j - SPORTMAN].score = atoi(str);          //������Ŀ����
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
{ //��ʾ���ļ���ȡ����Ϣ
    struct SCHOOL *p = head, *q;
    int i, j;
    char text1[] = "ѧУ���", text2[] = "ѧУ����";
    ReadFile(head); //���ö��ļ�����
    q = p->next;
    printf("%-10s%-16s", text1, text2);
    for (i = 0; i < SPORTMAN; i++)
        printf("%s%s:%d%4s", q->spoman[i].name, "��", q->spoman[i].id, "");
    for (i = 0; i < SPORTWOMAN; i++)
        printf("%s%s:%d%4s", q->spowoman[i].name, "Ů", q->spowoman[i].id, "");
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
{ //��ʾȫ����Ϣ,�ܷ�,��Ů�ܷ�
    struct SCHOOL *p = head, *q;
    int i, j;
    char text1[] = "ѧУ���", text2[] = "ѧУ����", text3[] = "ѧУ�ܷ�", text4[] = "�����ܷ�", text5[] = "Ů���ܷ�";
    q = p->next;
    printf("%-10s%-16s", text1, text2);
    for (i = 0; i < SPORTMAN; i++)
        printf("%s%s:%d%4s", q->spoman[i].name, "��", q->spoman[i].id, "");
    for (i = 0; i < SPORTWOMAN; i++)
        printf("%s%s:%d%4s", q->spowoman[i].name, "Ů", q->spowoman[i].id, "");
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
{ //ͳ���ֺܷ���
    int i, j, k;
    int qian3[3] = {5, 3, 2}, qian5[5] = {7, 5, 3, 2, 1};
    int rank[SCHOOL_MAX];
    struct SCHOOL *p = head, *q;
    struct SCHOOL *temp, *spscqian, *spmaxqian; //spscqian�洢����λ��ǰ��,spmaxqian�洢����ǰ��
    ReadFile(head);
    for (i = 0; i < SPORTMAN; i++) //����������Ŀ��������
    {
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spmaxqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if ((spmaxqian->next)->spoman[i].score < q->spoman[i].score) //����������Ŀ�����Ƚ�
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
            q->spoman[i].ranking = k + 1; //���������ÿ��������Ŀ������
            if (sportflag[i] == 0)        //ȡǰ����,ǰ��������Ϊ:5��3��2
            {
                if (k < 3)
                {
                    q->schoolscore += qian3[k];
                    q->spomanscore += qian3[k];
                }
            }
            else if (sportflag[i] == 1) //ȡǰ����,���ֱַ�Ϊ:7��5��3��2��1
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
    for (i = 0; i < SPORTWOMAN; i++) //Ů��������Ŀ��������
    {
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spmaxqian = spscqian = p; //���µ�j������λ�õ�ǰ��,�����j��Ϊ���
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if ((spmaxqian->next)->spowoman[i].score < q->spowoman[i].score) //����������Ŀ�����Ƚ�
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
            q->spowoman[i].ranking = k + 1;   //���������ÿ��������Ŀ������
            if (sportflag[i + SPORTMAN] == 0) //ȡǰ����,ǰ��������Ϊ:5��3��2
            {
                if (k < 3)
                {
                    q->schoolscore += qian3[k];
                    q->spowomanscore += qian3[k];
                }
            }
            else if (sportflag[i + SPORTMAN] == 1) //ȡǰ����,���ֱַ�Ϊ:7��5��3��2��1
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
{ //����command:1ѧУ���,2ѧУ����,3ѧУ�ܷ�,4�����ܷ�,5Ů���ܷ�,AscDesc:0����,1����,output 1���
    int j, k;
    struct SCHOOL *p = head, *q;
    struct SCHOOL *spqian, *spscqian, *temp;
    int sportid, scaflag, spflag, flag;
    system("cls");
    switch (command)
    {
    case 1:                              //��ѧУ�����������or����
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->id < q->id) //����ѧУ��űȽ�
                        spqian = p;                 //����
                }
                else
                {
                    if ((spqian->next)->id > q->id) //����ѧУ��űȽ�
                        spqian = p;                 //����
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
    case 2:                              //��ѧУ������������or����
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if (AscDesc)
                {
                    if (strcmp((spqian->next)->name, q->name) < 0) //����ѧУ���ֱȽ�
                        spqian = p;                                //����
                }
                else
                {
                    if (strcmp((spqian->next)->name, q->name) > 0) //����ѧУ���ֱȽ�
                        spqian = p;                                //����
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
    case 3:                              //��ѧУ�ܷ���������or����
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->schoolscore < q->schoolscore) //����ѧУ�ֱܷȽ�
                        spqian = p;                                   //����
                }
                else
                {
                    if ((spqian->next)->schoolscore > q->schoolscore) //����ѧУ�ֱܷȽ�
                        spqian = p;                                   //����
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
    case 4:                              //�������ܷ���������or����
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->spomanscore < q->spomanscore) //���������ֱܷȽ�
                        spqian = p;                                   //����
                }
                else
                {
                    if ((spqian->next)->spomanscore > q->spomanscore) //���������ֱܷȽ�
                        spqian = p;                                   //����
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
    case 5:                              //��Ů���ܷ���������or����
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if (AscDesc)
                {
                    if ((spqian->next)->spowomanscore < q->spowomanscore) //����Ů���ֱܷȽ�
                        spqian = p;                                       //����
                }
                else
                {
                    if ((spqian->next)->spowomanscore > q->spowomanscore) //����Ů���ֱܷȽ�
                        spqian = p;                                       //����
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
    case 6: //������������Ŀ�����������or����
        sortsportid(head, &spflag, &flag, AscDesc, output);
        break;
    }
}

void sortsportid(struct SCHOOL *head, int *spflag, int *flag, int AscDesc, int *output)
{
    struct SCHOOL *p, *q, *spqian, *spscqian, *temp;
    int scaflag, sportid, j, k;
    p = head->next;
    for (j = 0; j < SPORTMAN; j++) //�������������Ŀ����
        printf("%s:%d, ", p->spoman[j].name, p->spoman[j].id);
    for (j = 0; j < SPORTWOMAN; j++) //�������Ů����Ŀ����
        printf("%s:%d, ", p->spowoman[j].name, p->spowoman[j].id);
    printf("\n\n����������Ŀ�����ѡ������\n");
    scaflag = scanf("%d", &sportid);
    while (scaflag != 1)
    {
        fflush(stdin);
        printf("����Ĳ�������,���������룡\n");
        scaflag = scanf("%d", &sportid);
    }
    p = head->next; //ѭ�����ҷ��ϱ�ŵ�������Ŀ
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
        for (j = 1; j < SCHOOLNUMS; j++) //����ѧУ����-1��
        {
            p = head;
            for (k = 0; k < j; k++) //����ǰj���Ѿ��ź����
            {
                spqian = spscqian = p; //��������ǵ�j��,���µ�j������λ�õ�ǰ��
                q = p->next;
                p = q;
            }
            for (k = j; k < SCHOOLNUMS; k++) //���ұȽϽ���
            {
                q = p->next;
                if (AscDesc)
                {
                    if (*flag == 1)
                    {
                        if ((spqian->next)->spoman[*spflag].score < q->spoman[*spflag].score) //����������Ŀ�Ƚ�
                            spqian = p;                                                       //����
                    }
                    else if (*flag == 2)
                    {
                        if ((spqian->next)->spowoman[*spflag].score < q->spowoman[*spflag].score) //����������Ŀ�Ƚ�
                            spqian = p;                                                           //����
                    }
                }
                else
                {
                    if (*flag == 1)
                    {
                        if ((spqian->next)->spoman[*spflag].score > q->spoman[*spflag].score) //����������Ŀ�Ƚ�
                            spqian = p;                                                       //����
                    }
                    else if (*flag == 2)
                    {
                        if ((spqian->next)->spowoman[*spflag].score > q->spowoman[*spflag].score) //����������Ŀ�Ƚ�
                            spqian = p;                                                           //����
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
        printf("���޴��\n");
    }
}

void Mainmenu()
{ //���˵�
    printf("ʵ��һ��\n");
    printf("---------------------------------�˶������ͳ��---------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("-------------------------------1.�����ɼ��ļ�����-------------------------------\n");
    printf("----------------------------2.�����ɼ��ļ���ȡ����ʾ----------------------------\n");
    printf("---------------3.��ѧУ��š����ơ�ѧУ�ܷ֡���Ů�����ܷ��������---------------\n");
    printf("-----------------------4.��ѧУ��Ų�ѯѧУĳ����Ŀ�����-----------------------\n");
    printf("---------------------5.����Ŀ��Ų�ѯȡ��ǰ����ǰ������ѧУ---------------------\n");
    printf("-----------------------------------6.�˳�����-----------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------2019��12��21��--̷����д\n");
}

void menu1makefile()
{ //�˵�1
    int com2, scaflag;
    system("cls");
    printf("------------------------1.�ֶ�����ѧУ����,������Ŀ���ɼ�-----------------------\n");
    printf("------------------------2.�������ѧУ����,������Ŀ���ɼ�-----------------------\n");
    printf("----------------------------------3.������һ����--------------------------------\n");
    printf("����һ����ѡ���ܣ�");
    scaflag = scanf("%d", &com2);
    while (scaflag != 1 || com2 < 1 || com2 > 3)
    {
        fflush(stdin);
        printf("����Ĳ������ֻ������������������,���������룡\n");
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
{ //�˵�3
    int com2, scaflag, output;
    Statotalscore(head); //�����ܷ�
    while (1)
    {
        system("cls");
        printf("-------------------------------1.��ѧУ��Ž������-----------------------------\n");
        printf("-------------------------------2.��ѧУ����������-----------------------------\n\n");
        printf("-------------------------------3.��ѧУ���ֽ������-----------------------------\n");
        printf("-------------------------------4.��ѧУ�����������-----------------------------\n\n");
        printf("-------------------------------5.��ѧУ�ֽܷ������-----------------------------\n");
        printf("-------------------------------6.��ѧУ�ܷ��������-----------------------------\n\n");
        printf("-------------------------------7.�������ֽܷ������-----------------------------\n");
        printf("-------------------------------8.�������ܷ��������-----------------------------\n\n");
        printf("-------------------------------9.��Ů���ֽܷ������-----------------------------\n");
        printf("------------------------------10.��Ů���ܷ��������-----------------------------\n\n");
        printf("--------------------------11.������������Ŀ��Ž������-------------------------\n");
        printf("--------------------------12.������������Ŀ����������-------------------------\n\n");
        printf("---------------------------------13.������һ����--------------------------------\n");
        printf("����һ����ѡ���ܣ�");
        scaflag = scanf("%d", &com2);
        while (scaflag != 1 || com2 < 1 || com2 > 13)
        {
            fflush(stdin);
            printf("����Ĳ������ֻ������������������,���������룡\n");
            scaflag = scanf("%d", &com2);
        }
        if (com2 == 13)
            break;
        else
        {
            output = 1;
            Sortdata(head, com2 / 2 + com2 % 2, com2 % 2, &output); //��Ҫ������
            if (output)
                put_over_data_score(head); //����������
        }
        system("pause");
        system("cls");
    }
    system("cls");
}

void menu4(struct SCHOOL *head)
{ //�˵�4
    int i, j;
    struct SCHOOL *p, *q;
    int schid, spoid, schflag = 0, spoflag = 0, scaflag;
    system("cls");
    Statotalscore(head); //�����ܷ�
    printf("ѧУ����--ѧУ���\n");
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
    printf("\n\n������Ŀ����--���\n");
    for (i = 0; i < SPORTMAN; i++)
        printf("%s(%s)--%d\n", p->spoman[i].name, "��", p->spoman[i].id);
    for (i = 0; i < SPORTWOMAN; i++)
        printf("%s(%s)--%d\n", p->spowoman[i].name, "Ů", p->spowoman[i].id);
    printf("\n����ѧУ���,������Ŀ���\n���磺1,2\n");
    scaflag = scanf("%d,%d", &schid, &spoid);
    while (scaflag != 2)
    {
        printf("���벻�淶������������\n");
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
            printf("%s��%s(%s)�ɼ�Ϊ��%d��\n", q->name, q->spoman[i].name, "��", q->spoman[i].ranking);
        else if (spoflag == 2)
            printf("%s��%s(%s)�ɼ�Ϊ��%d��\n", q->name, q->spowoman[j].name, "Ů", q->spowoman[j].ranking);
        else
            printf("%sû�д���������Ŀ��\n", q->name);
    }
    else
        printf("���޴�У��\n");
    printf("\n%sȫ��������Ŀ�����\n", q->name);
    if (schflag && spoflag)
    {
        for (i = 0; i < SPORTMAN; i++)
            printf("%s(%s)��%d��\n", q->spoman[i].name, "��", q->spoman[i].ranking);
        for (i = 0; i < SPORTWOMAN; i++)
            printf("%s(%s)��%d��\n", q->spowoman[i].name, "Ů", q->spowoman[i].ranking);
    }
    system("pause");
    system("cls");
}

void menu5(struct SCHOOL *head)
{                                                 //�˵�5
    int output = 0, spoid, spflag, scaflag, flag; //spflag���±꣬flag�ж���1Ů2��Ŀ
    int i, j;
    struct SCHOOL *p, *q;
    Statotalscore(head);
    sortsportid(head, &spflag, &flag, 1, &output); //1����
    if (flag == 1)
    {
        if (sportflag[spflag]) //������Ŀȡǰ��
        {
            p = head->next;
            while (p->spoman[spflag].ranking <= 5)
            {
                printf("��%d��%s\n", p->spoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
        else //������Ŀȡǰ��
        {
            p = head->next;
            while (p->spoman[spflag].ranking <= 3)
            {
                printf("��%d��%s\n", p->spoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
    }
    else if (flag == 2)
    {
        if (sportflag[spflag + SPORTMAN]) //Ů����Ŀȡǰ��
        {
            p = head->next;
            while (p->spowoman[spflag].ranking <= 5)
            {
                printf("��%d��%s\n", p->spowoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
        else //Ů����Ŀȡǰ��
        {
            p = head->next;
            while (p->spowoman[spflag].ranking <= 3)
            {
                printf("��%d��%s\n", p->spowoman[spflag].ranking, p->name);
                p = p->next;
            }
        }
    }
    else
        printf("û�����������Ŀ�����������룡\n");
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
        printf("����һ����ѡ���ܣ�");
        scaflag = scanf("%d", &command);
        while (scaflag != 1)
        {
            fflush(stdin);
            system("cls");
            Mainmenu();
            printf("���벻������,���������룡\n");
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
            printf("����������������������룡\n");
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