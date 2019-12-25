#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct HuffmanTree
{
    int weight;                 //����Ȩֵ
    int Lchild, Rchild, Parent; //������ҽ��,������±�
    char letter;                //�������ʾ���ַ�
};

struct code
{
    char col[28]; //��ű���
    char letter;  //�������ʾ���ַ�
} HC[28];         //0�ŵ�Ԫ����

struct HuffmanTree *HT = NULL; //�����������
int N;                         //ȫ�ֱ������ַ�����

void Input();                         //�����ַ���������
void Init();                          //��ʼ����������
void CreateHTree(char a[], int w[]);  //����������������
void Select(int n, int *s1, int *s2); //��1-nѡ��Ȩֵ��С������Ԫ���±�
void PutHuffmanTree();                //��ӡ����������
void CreateHuffmanCode();             //����������
void Puteverycode();                  //���ÿ���ַ��ı������
int FILEhfmtree();                    //���ļ��ж�ȡ��������
void Codetxt();                       //�����ļ�
void DeCodetxt();                     //�����ļ�
void Printcodetxt();                  //��ӡ�������ɵ��ļ�
void Printhftree();                   //��ӡ����������

int main()
{
    int i, j;
    char command;
    system("color 0f");
    while (1)
    {
        printf("��������������\n\n");
        printf("O: ����һ���ַ�(����26����д��ĸ�Ϳո�),ͳ�Ƴ������ַ����ֵĴ���\n\n");
        printf("I����ʼ��,������������\n\n");
        printf("E������(Encoding)\n\n");
        printf("D������(Decoding)\n\n");
        printf("P����ӡ�����ļ�(Print)\n\n");
        printf("T����ӡ��������(Tree Printing)\n\n");
        printf("Q���˳�����\n\n");
        printf("������һ����ĸѡ����:");
        scanf("%c", &command);
        fflush(stdin);
        if ('Q' == command || 'q' == command)
            break;
        switch (command)
        {
        case 'o':
        case 'O':
            Input();
            break;
        case 'i':
        case 'I':
            Init();
            break;
        case 'e':
        case 'E':
            Codetxt();
            break;
        case 'd':
        case 'D':
            DeCodetxt();
            break;
        case 'p':
        case 'P':
            Printcodetxt();
            break;
        case 't':
        case 'T':
            Printhftree();
            break;
        default:
            printf("�������������\n");
            system("pause");
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}
void Input()
{ //�����ַ�������
    char str[1024], a[27] = " ";
    int Alph[27], i, j, flag = 1;
    FILE *fp;
    memset(Alph, 0, 27 * sizeof(int));
    printf("������һ���������26����дӢ����ĸ�Ϳո���ַ���\n");
    printf("Tip:�����Իس�����\n");
    gets(str);
    i = 0;
    while (str[i])
    {
        if ('A' <= str[i] && str[i] <= 'Z')
            Alph[str[i] - 'A' + 1] += 1;
        else if (str[i] == ' ')
            Alph[0] += 1;
        else
        {
            flag = 0;
            printf("�����ַ����в����������ַ�,���˳������ԣ�\n");
            break;
        }
        i++;
    }
    if (flag)
    {
        if (!Alph[0])
        {
            flag = 0;
            printf("������ַ���������  �ո�\n");
        }
        for (i = 1; i < 27; i++)
            if (!Alph[i])
            {
                flag = 0;
                printf("������ַ���������  %c\n", i + 64);
            }
        if (!flag)
            printf("���˳�����������\n");
    }
    if (flag)
    {
        fp = fopen("chartexfile.txt", "w");
        if (fp == NULL)
        {
            printf("�����ļ�chartexfile.txt����\n");
            system("pause");
            system("cls");
            return;
        }
        fputs(str, fp);
        fclose(fp);
        printf("\n�ַ����Ѿ�д��chartexfile.txt�ļ�\n\n");
        fp = fopen("charsumfile.txt", "w");
        if (fp == NULL)
        {
            printf("�����ļ�charsumfile.txt����\n");
            system("pause");
            system("cls");
            return;
        }
        fprintf(fp, "%c%d", '@', Alph[0]); //��@����ո񷽱���������
        printf("�ַ�  �ո�");
        for (i = 1; i < 27; i++)
            printf("%3c", i + 64);
        printf("\nƵ��  %4d", Alph[0]);
        for (i = 1; i < 27; i++)
        {
            fprintf(fp, "\n%c%d", i + 64, Alph[i]);
            printf("%3d", Alph[i]);
        }
        printf("\n\n���ַ����ִ����Ѿ�д��charsumfile.txt�ļ�\n");
        fclose(fp);
        printf("\n�Ƿ�ʹ��������ַ���Ƶ��������������?(Y/N)");
        if ('Y' == fgetc(stdin))
        {
            for (i = 1; i < 27; i++)
                a[i] = i + 64;
            N = 27;
            CreateHTree(a, Alph);
            PutHuffmanTree();
            CreateHuffmanCode();
            Puteverycode();
        }
    }
    system("pause");
    system("cls");
    fflush(stdin);
}

void Init()
{ //��ʼ������
    int i, flag, com;
    FILE *fp;
    char ABC[27], temp;
    int ABCnums[27];
    int filenums[27];
    system("cls");
    printf("1.�����ַ���charsumfile.txt�ж�ȡƵ��\n\n");
    printf("2.�����ַ���Ƶ��\n\n");
    printf("����һ����ѡ����:");
    flag = scanf("%d", &com);
    while (flag != 1 || com > 2 || com < 1)
    {
        printf("����ָ��ԣ�����������\n");
        fflush(stdin);
        flag = scanf("%d", &com);
    }
    printf("\n�������ַ�����СN, 1<= N <=27\n");
    flag = scanf("%d", &N);
    while (flag != 1 || N < 1 || N > 27)
    {
        printf("����ָ��ԣ�����������\n");
        fflush(stdin);
        flag = scanf("%d", &N);
    }
    if (com == 1)
    {
        fp = fopen("charsumfile.txt", "r");
        if (fp == NULL)
        {
            printf("charsumfile.txt��ȡ����\n");
            system("pause");
            system("cls");
            return;
        }
        for (i = 0; i < 27; i++)
            fscanf(fp, "%c%d\n", &temp, &filenums[i]);
        fclose(fp);
        printf("\n������N����ͬ�Ĵ�д��ĸ��ո�,����һ����һ�»س�\n");
        for (i = 0; i < N; i++)
        {
            fflush(stdin);
            ABC[i] = getc(stdin);
            while ((ABC[i] > 'Z' || ABC[i] < 'A') && ABC[i] != ' ')
            {
                printf("����Ĳ��Ǵ�д��ĸ��ո�,����������\n");
                fflush(stdin);
                ABC[i] = getc(stdin);
            }
            if (ABC[i] == ' ')
                ABCnums[i] = filenums[0];
            else
                ABCnums[i] = filenums[ABC[i] - 64];
        }
    }
    else if (com == 2)
    {
        printf("\n�����д��ĸ��ո��Ƶ������\nA12\nC23\n\n");
        for (i = 0; i < N; i++)
        {
            fflush(stdin);
            ABC[i] = getc(stdin);
            scanf("%d", &ABCnums[i]);
        }
    }
    printf("�ַ�  ");
    for (i = 0; i < N; i++)
    {
        if (ABC[i] == ' ')
            printf("�ո� ");
        else
            printf("%-4c ", ABC[i]);
    }
    printf("\nƵ��  ");
    for (i = 0; i < N; i++)
        printf("%-4d ", ABCnums[i]);
    printf("\n");
    CreateHTree(ABC, ABCnums); //������������
    PutHuffmanTree();          //�������������
    fp = fopen("hfmTree.txt", "w");
    if (fp == NULL)
    {
        printf("hfmTree.txt�ļ���������\n");
        system("pause");
        system("cls");
        return;
    }
    fprintf(fp, "%-6s%-6s%-6s%-8s%-8s%-6s\n", "���", "�ַ�", "Ȩֵ", "����", "�Һ���", "����");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ') //�ո���@����,������ļ�
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, '@', HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= 2 * N - 1; i++)
        fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    fclose(fp);
    printf("\n�����������Ѿ�д��hfmTree.txt��\n");
    CreateHuffmanCode(); //����������
    Puteverycode();      //���ÿ���ַ���������
    system("pause");
    system("cls");
    fflush(stdin);
}

void CreateHTree(char a[], int w[])
{ //������������
    struct HuffmanTree *pt;
    int m, i, s1, s2;
    m = 2 * N - 1;
    s1 = 1;
    s2 = 2;
    HT = (struct HuffmanTree *)malloc(sizeof(struct HuffmanTree) * (m + 1));
    //0�ŵ�Ԫδʹ��
    pt = HT;                                 /*HTָ��0�ŵ�Ԫ*/
    pt++;                                    //ptָ���±�Ϊ1�ĵ�Ԫ
    for (i = 1; i <= N; i++, pt++, w++, a++) //����1-n������ʼ��
    {
        pt->weight = *w;
        pt->Lchild = 0;
        pt->Rchild = 0;
        pt->Parent = 0;
        pt->letter = *a;
    }
    for (i; i <= m; i++, pt++) //����n+1~2n-1������ʼ��
    {
        pt->weight = 0;
        pt->Lchild = 0;
        pt->Rchild = 0;
        pt->Parent = 0;
        pt->letter = 0;
    }
    for (i = N + 1; i <= m; i++) //�����������
    {
        Select(i - 1, &s1, &s2); //��HT[1..i-1]��ѡ��parentΪ0��weight��С���������,���Ϊs1,s2
        HT[i].Lchild = s1;
        HT[i].Rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[s1].Parent = i;
        HT[s2].Parent = i;
    }
}

void Select(int n, int *s1, int *s2)
{ //��1~n֮��ѡ��Ȩֵ��С������Ԫ���±�
    int i = 1, temp;
    while (HT[i].Parent != 0 && i <= n) //Ѱ�ҵ�һ��δ���ʵ�Ԫ���±�
        i++;
    if (i == n + 1)
        return;
    *s1 = i++;
    while (HT[i].Parent != 0 && i <= n) //Ѱ�ҵڶ���δ���ʵ�Ԫ���±�
        i++;
    if (i == n + 1)
        return;
    *s2 = i++;
    if (HT[*s1].weight > HT[*s2].weight)
    {
        temp = *s1;
        *s1 = *s2;
        *s2 = temp;
    }
    for (; i <= n; i++) //ѡȡ������СȨֵ
    {
        if (HT[i].Parent == 0)
        {
            if (HT[i].weight < HT[*s1].weight)
            {
                *s2 = *s1;
                *s1 = i;
            }
            else if (HT[i].weight < HT[*s2].weight)
                *s2 = i;
        }
    }
}

void PutHuffmanTree()
{ //��ӡ����������
    int i, m = 2 * N - 1;
    printf("\n�������������\n");
    printf("\n%-6s%-6s%-6s%-8s%-8s%-6s\n", "���", "�ַ�", "Ȩֵ", "����", "�Һ���", "����");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ')
            printf("%-6d%-6s%-6d%-8d%-8d%-6d\n", i, "�ո�", HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= m; i++)
        printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    printf("\n");
}

void CreateHuffmanCode()
{ //����������
    int start, i, p, f;
    char col[28];
    memset(HC, 0, sizeof(struct code) * 28);
    for (i = 1; i <= N; i++) //����ַ������
    {
        memset(col, 0, sizeof(col));
        start = N - 1; //���������λ��
        p = f = i;
        while (HT[f].Parent != 0) //��Ҷ�ӵ������������
        {
            f = HT[f].Parent;
            if (HT[f].Lchild == p)
                col[--start] = '0';
            else if (HT[f].Rchild == p)
                col[--start] = '1';
            p = f;
        }
        HC[i].letter = HT[i].letter;
        strcpy(HC[i].col, col + start);
    }
}

void Puteverycode()
{ //���ÿ���ַ��ı������
    int i;
    printf("%-6s%-8s\n", "�ַ�", "����");
    for (i = 1; i <= N; i++)
    {
        if (HC[i].letter == ' ')
            printf("%-6s%-8s\n", "�ո�", HC[i].col);
        else
            printf("%-6c%-8s\n", HC[i].letter, HC[i].col);
    }
}

int FILEhfmtree()
{ //���ļ��ж�ȡ��������
    FILE *fp;
    int i, temp;
    char a;
    fp = fopen("hfmTree.txt", "r");
    if (fp == NULL)
        return 0;
    getc(fp);
    if (feof(fp))
        return 0;
    i = 1;
    while (1)
    {
        fseek(fp, 42 * i + 6, SEEK_SET);
        a = fgetc(fp);
        if (!a)
            break;
        i++;
    }
    N = i - 1;
    HT = (struct HuffmanTree *)malloc(sizeof(struct HuffmanTree) * (2 * N));
    for (i = 1; i <= 2 * N - 1; i++)
    {
        fseek(fp, 42 * i + 6, SEEK_SET);
        a = fgetc(fp);
        fscanf(fp, "%d%d%d%d", &HT[i].weight, &HT[i].Lchild, &HT[i].Rchild, &HT[i].Parent);
        if (a == '@')
            HT[i].letter = ' ';
        else
            HT[i].letter = a;
    }
    fclose(fp);
    return 1;
}

void Codetxt()
{ //�����ļ�
    char str[1024];
    char codehf[2048];
    int i, j;
    FILE *fp;
    system("cls");
    if (NULL == HT)
    {
        printf("\n��ǰ�ڴ���û�й�������,�Ƿ��hfmTree.txt�ļ���ȡ(Y/N)\n");
        fflush(stdin);
        if ('Y' == getc(stdin))
        {
            if (FILEhfmtree() == 0)
            {
                printf("\nhfmTree.txt��û�й�������,��ʹ�ù���I��ʼ��\n");
                system("pause");
                system("cls");
                fflush(stdin);
                return;
            }
        }
        else
        {
            printf("\nû�й�����������,�޷����б���\n");
            system("pause");
            system("cls");
            fflush(stdin);
            return;
        }
    }
    CreateHuffmanCode();
    if (NULL == (fp = fopen("ToBeTran.txt", "w")))
    {
        printf("\nToBeTran.txt�ļ���������\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\n��ʹ����Щ�ַ���  ");
    for (i = 1; i <= N; i++)
    {
        if (HC[i].letter == ' ')
            printf("%-5s", "�ո�");
        else
            printf("%-5c", HC[i].letter);
    }
    printf("\n\n������һ��Ҫ������ı�\n");
    fflush(stdin);
    gets(str);
    fputs(str, fp);
    fclose(fp);
    printf("\n������ı��Ѿ�����ToBeTran.txt�ļ�\n");
    memset(codehf, 0, sizeof(codehf));
    for (i = 0; str[i]; i++)
    {
        for (j = 1; j <= N; j++)
            if (str[i] == HC[j].letter)
            {
                strcat(codehf, HC[j].col);
                break;
            }
        if (j == N + 1)
        {
            printf("\n�в��ܱ�����ַ�:%c\n�˳�������\n", str[i]);
            system("pause");
            system("cls");
            return;
        }
    }
    printf("\n��������\n");
    for (i = 0; codehf[i]; i++)
    {
        printf("%c", codehf[i]);
        if (i % 50 == 49)
            printf("\n");
    }
    if (NULL == (fp = fopen("CodeFile.txt", "w")))
    {
        printf("\nCodeFile.txt�ļ���������\n");
        system("pause");
        system("cls");
        return;
    }
    fputs(codehf, fp);
    fclose(fp);
    printf("\n�������Ѿ�����CodeFile.txt�ļ�\n");
    system("pause");
    system("cls");
    fflush(stdin);
}

void DeCodetxt()
{ //�����ļ�
    char str[1024];
    char codehf[2048];
    int i, j, start, temp;
    FILE *fp;
    system("cls");
    if (NULL == HT)
    {
        printf("\n��ǰ�ڴ���û�й�������,�Ƿ��hfmTree.txt�ļ���ȡ(Y/N)\n");
        fflush(stdin);
        if ('Y' == getc(stdin))
        {
            if (FILEhfmtree() == 0)
            {
                printf("\nhfmTree.txt��û�й�������,��ʹ�ù���I��ʼ��\n");
                system("pause");
                system("cls");
                fflush(stdin);
                return;
            }
        }
        else
        {
            printf("\nû�й�����������,�޷���������\n");
            system("pause");
            system("cls");
            fflush(stdin);
            return;
        }
    }
    CreateHuffmanCode();
    printf("\n��ǰ�Ĺ���������:\n");
    Puteverycode();
    if (NULL == (fp = fopen("CodeFile.txt", "r")))
    {
        printf("\nCodeFile.txt�ļ���ȡ����\n");
        system("pause");
        system("cls");
        return;
    }
    fgets(codehf, 2048, fp);
    fclose(fp);
    printf("\nCodeFile.txt�ļ�Դ����: \n");
    for (i = 0; codehf[i]; i++)
    {
        printf("%c", codehf[i]);
        if (i % 50 == 49)
            printf("\n");
    }
    memset(str, 0, sizeof(str));
    i = 0;
    for (j = 0;; j++)
    {
        start = 2 * N - 1;
        for (i; codehf[i]; i++)
        {
            if (codehf[i] == '0')
                temp = HT[start].Lchild;
            else if (codehf[i] == '1')
                temp = HT[start].Rchild;
            start = temp;
            if (HT[start].Lchild == 0 && HT[start].Rchild == 0)
            {
                i++;
                break;
            }
        }
        str[j] = HT[start].letter;
        if (codehf[i] == 0)
            break;
    }
    printf("\n\n��������\n");
    for (i = 0; str[i]; i++)
    {
        printf("%c", str[i]);
        if (i % 50 == 49)
            printf("\n");
    }
    if (NULL == (fp = fopen("TextFile.txt", "w")))
    {
        printf("\nTextFile.txt�ļ���������\n");
        system("pause");
        system("cls");
        return;
    }
    fputs(str, fp);
    fclose(fp);
    printf("\n\n�������Ѿ�����TextFile.txt�ļ���\n");
    system("pause");
    system("cls");
    fflush(stdin);
}

void Printcodetxt()
{
    char codehf[2048];
    int i;
    FILE *fp;
    if (NULL == (fp = fopen("CodeFile.txt", "r")))
    {
        printf("\nCodeFile.txt�ļ���ȡ����\n");
        system("pause");
        system("cls");
        return;
    }
    fgets(codehf, 2048, fp);
    fclose(fp);
    if (NULL == (fp = fopen("CodePrin.txt", "w")))
    {
        printf("\nCodePrin.txt�ļ����ɴ���\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\nCodeFile.txt�ļ����ݣ�\n");
    for (i = 0; codehf[i]; i++)
    {
        fputc(codehf[i], fp);
        printf("%c", codehf[i]);
        if (i % 50 == 49)
        {
            printf("\n");
            fputc('\n', fp);
        }
    }
    fclose(fp);
    printf("\n\nÿ��50��������ļ��Ѿ�д��CodePrin.txt�ļ�\n");
    system("pause");
    system("cls");
}

void Printhftree()
{ //��ӡ�����������ļ�
    int i, m = 2 * N - 1;
    FILE *fp;
    if (HT == NULL)
    {
        printf("\n��ǰ�ڴ���û�й�������\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\n�������������\n");
    printf("\n%-6s%-6s%-6s%-8s%-8s%-6s\n", "���", "�ַ�", "Ȩֵ", "����", "�Һ���", "����");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ')
            printf("%-6d%-6s%-6d%-8d%-8d%-6d\n", i, "�ո�", HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= m; i++)
        printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    printf("\n");

    if (NULL == (fp = fopen("TreePrint.txt", "w")))
    {
        printf("TreePrint.txt�ļ���������\n");
        system("pause");
        system("cls");
        return;
    }
    fprintf(fp, "%-6s%-6s%-6s%-8s%-8s%-6s\n", "���", "�ַ�", "Ȩֵ", "����", "�Һ���", "����");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ') //�ո���@����,������ļ�
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, '@', HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= 2 * N - 1; i++)
        fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    fclose(fp);
    printf("\n�����������Ѿ�д��TreePrint.txt��\n");
    system("pause");
    system("cls");
}