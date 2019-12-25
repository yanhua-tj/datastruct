#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct HuffmanTree
{
    int weight;                 //结点的权值
    int Lchild, Rchild, Parent; //存放左右结点,父结点下标
    char letter;                //存放所表示的字符
};

struct code
{
    char col[28]; //存放编码
    char letter;  //存放所表示的字符
} HC[28];         //0号单元无用

struct HuffmanTree *HT = NULL; //哈夫曼树结点
int N;                         //全局变量存字符个数

void Input();                         //输入字符函数声明
void Init();                          //初始化函数声明
void CreateHTree(char a[], int w[]);  //建立哈夫曼树声明
void Select(int n, int *s1, int *s2); //从1-n选择权值最小的两个元素下标
void PutHuffmanTree();                //打印哈夫曼树表
void CreateHuffmanCode();             //哈夫曼编码
void Puteverycode();                  //输出每个字符的编码情况
int FILEhfmtree();                    //从文件中读取哈夫曼树
void Codetxt();                       //编码文件
void DeCodetxt();                     //译码文件
void Printcodetxt();                  //打印编码生成的文件
void Printhftree();                   //打印哈夫曼树表

int main()
{
    int i, j;
    char command;
    system("color 0f");
    while (1)
    {
        printf("哈夫曼编译码器\n\n");
        printf("O: 输入一段字符(包含26个大写字母和空格),统计出各个字符出现的次数\n\n");
        printf("I：初始化,建立哈夫曼树\n\n");
        printf("E：编码(Encoding)\n\n");
        printf("D：译码(Decoding)\n\n");
        printf("P：打印代码文件(Print)\n\n");
        printf("T：打印哈夫曼树(Tree Printing)\n\n");
        printf("Q：退出程序\n\n");
        printf("请输入一个字母选择功能:");
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
            printf("输入的命令有误！\n");
            system("pause");
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}
void Input()
{ //输入字符串函数
    char str[1024], a[27] = " ";
    int Alph[27], i, j, flag = 1;
    FILE *fp;
    memset(Alph, 0, 27 * sizeof(int));
    printf("请输入一串必须包含26个大写英文字母和空格的字符串\n");
    printf("Tip:输入以回车结束\n");
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
            printf("输入字符串有不合条件的字符,请退出后重试！\n");
            break;
        }
        i++;
    }
    if (flag)
    {
        if (!Alph[0])
        {
            flag = 0;
            printf("输入的字符串不包含  空格\n");
        }
        for (i = 1; i < 27; i++)
            if (!Alph[i])
            {
                flag = 0;
                printf("输入的字符串不包含  %c\n", i + 64);
            }
        if (!flag)
            printf("请退出后重新输入\n");
    }
    if (flag)
    {
        fp = fopen("chartexfile.txt", "w");
        if (fp == NULL)
        {
            printf("创建文件chartexfile.txt错误\n");
            system("pause");
            system("cls");
            return;
        }
        fputs(str, fp);
        fclose(fp);
        printf("\n字符串已经写入chartexfile.txt文件\n\n");
        fp = fopen("charsumfile.txt", "w");
        if (fp == NULL)
        {
            printf("创建文件charsumfile.txt错误\n");
            system("pause");
            system("cls");
            return;
        }
        fprintf(fp, "%c%d", '@', Alph[0]); //用@代替空格方便后面读数据
        printf("字符  空格");
        for (i = 1; i < 27; i++)
            printf("%3c", i + 64);
        printf("\n频度  %4d", Alph[0]);
        for (i = 1; i < 27; i++)
        {
            fprintf(fp, "\n%c%d", i + 64, Alph[i]);
            printf("%3d", Alph[i]);
        }
        printf("\n\n各字符出现次数已经写入charsumfile.txt文件\n");
        fclose(fp);
        printf("\n是否使用上面的字符和频度生产哈夫曼树?(Y/N)");
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
{ //初始化函数
    int i, flag, com;
    FILE *fp;
    char ABC[27], temp;
    int ABCnums[27];
    int filenums[27];
    system("cls");
    printf("1.输入字符从charsumfile.txt中读取频度\n\n");
    printf("2.输入字符和频度\n\n");
    printf("输入一个数选择功能:");
    flag = scanf("%d", &com);
    while (flag != 1 || com > 2 || com < 1)
    {
        printf("输入指令不对，请重新输入\n");
        fflush(stdin);
        flag = scanf("%d", &com);
    }
    printf("\n请输入字符集大小N, 1<= N <=27\n");
    flag = scanf("%d", &N);
    while (flag != 1 || N < 1 || N > 27)
    {
        printf("输入指令不对，请重新输入\n");
        fflush(stdin);
        flag = scanf("%d", &N);
    }
    if (com == 1)
    {
        fp = fopen("charsumfile.txt", "r");
        if (fp == NULL)
        {
            printf("charsumfile.txt读取错误\n");
            system("pause");
            system("cls");
            return;
        }
        for (i = 0; i < 27; i++)
            fscanf(fp, "%c%d\n", &temp, &filenums[i]);
        fclose(fp);
        printf("\n请输入N个不同的大写字母或空格,输入一个按一下回车\n");
        for (i = 0; i < N; i++)
        {
            fflush(stdin);
            ABC[i] = getc(stdin);
            while ((ABC[i] > 'Z' || ABC[i] < 'A') && ABC[i] != ' ')
            {
                printf("输入的不是大写字母或空格,请重新输入\n");
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
        printf("\n输入大写字母或空格和频度例如\nA12\nC23\n\n");
        for (i = 0; i < N; i++)
        {
            fflush(stdin);
            ABC[i] = getc(stdin);
            scanf("%d", &ABCnums[i]);
        }
    }
    printf("字符  ");
    for (i = 0; i < N; i++)
    {
        if (ABC[i] == ' ')
            printf("空格 ");
        else
            printf("%-4c ", ABC[i]);
    }
    printf("\n频度  ");
    for (i = 0; i < N; i++)
        printf("%-4d ", ABCnums[i]);
    printf("\n");
    CreateHTree(ABC, ABCnums); //建立哈夫曼树
    PutHuffmanTree();          //输出哈夫曼树表
    fp = fopen("hfmTree.txt", "w");
    if (fp == NULL)
    {
        printf("hfmTree.txt文件创建错误\n");
        system("pause");
        system("cls");
        return;
    }
    fprintf(fp, "%-6s%-6s%-6s%-8s%-8s%-6s\n", "编号", "字符", "权值", "左孩子", "右孩子", "父亲");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ') //空格用@代替,方便读文件
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, '@', HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= 2 * N - 1; i++)
        fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    fclose(fp);
    printf("\n哈夫曼树表已经写入hfmTree.txt中\n");
    CreateHuffmanCode(); //哈夫曼编码
    Puteverycode();      //输出每个字符编码的情况
    system("pause");
    system("cls");
    fflush(stdin);
}

void CreateHTree(char a[], int w[])
{ //建立哈夫曼树
    struct HuffmanTree *pt;
    int m, i, s1, s2;
    m = 2 * N - 1;
    s1 = 1;
    s2 = 2;
    HT = (struct HuffmanTree *)malloc(sizeof(struct HuffmanTree) * (m + 1));
    //0号单元未使用
    pt = HT;                                 /*HT指向0号单元*/
    pt++;                                    //pt指向下标为1的单元
    for (i = 1; i <= N; i++, pt++, w++, a++) //数组1-n分量初始化
    {
        pt->weight = *w;
        pt->Lchild = 0;
        pt->Rchild = 0;
        pt->Parent = 0;
        pt->letter = *a;
    }
    for (i; i <= m; i++, pt++) //数组n+1~2n-1分量初始化
    {
        pt->weight = 0;
        pt->Lchild = 0;
        pt->Rchild = 0;
        pt->Parent = 0;
        pt->letter = 0;
    }
    for (i = N + 1; i <= m; i++) //构造哈夫曼树
    {
        Select(i - 1, &s1, &s2); //在HT[1..i-1]中选择parent为0且weight最小的两个结点,序号为s1,s2
        HT[i].Lchild = s1;
        HT[i].Rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[s1].Parent = i;
        HT[s2].Parent = i;
    }
}

void Select(int n, int *s1, int *s2)
{ //从1~n之间选择权值最小的两个元素下标
    int i = 1, temp;
    while (HT[i].Parent != 0 && i <= n) //寻找第一个未访问的元素下标
        i++;
    if (i == n + 1)
        return;
    *s1 = i++;
    while (HT[i].Parent != 0 && i <= n) //寻找第二个未访问的元素下标
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
    for (; i <= n; i++) //选取两个最小权值
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
{ //打印哈夫曼树表
    int i, m = 2 * N - 1;
    printf("\n输出哈夫曼树表\n");
    printf("\n%-6s%-6s%-6s%-8s%-8s%-6s\n", "编号", "字符", "权值", "左孩子", "右孩子", "父亲");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ')
            printf("%-6d%-6s%-6d%-8d%-8d%-6d\n", i, "空格", HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= m; i++)
        printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    printf("\n");
}

void CreateHuffmanCode()
{ //哈夫曼编码
    int start, i, p, f;
    char col[28];
    memset(HC, 0, sizeof(struct code) * 28);
    for (i = 1; i <= N; i++) //逐个字符求编码
    {
        memset(col, 0, sizeof(col));
        start = N - 1; //编码结束符位置
        p = f = i;
        while (HT[f].Parent != 0) //从叶子到根逆向求编码
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
{ //输出每个字符的编码情况
    int i;
    printf("%-6s%-8s\n", "字符", "编码");
    for (i = 1; i <= N; i++)
    {
        if (HC[i].letter == ' ')
            printf("%-6s%-8s\n", "空格", HC[i].col);
        else
            printf("%-6c%-8s\n", HC[i].letter, HC[i].col);
    }
}

int FILEhfmtree()
{ //从文件中读取哈夫曼树
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
{ //编码文件
    char str[1024];
    char codehf[2048];
    int i, j;
    FILE *fp;
    system("cls");
    if (NULL == HT)
    {
        printf("\n当前内存中没有哈夫曼树,是否从hfmTree.txt文件读取(Y/N)\n");
        fflush(stdin);
        if ('Y' == getc(stdin))
        {
            if (FILEhfmtree() == 0)
            {
                printf("\nhfmTree.txt中没有哈夫曼树,请使用功能I初始化\n");
                system("pause");
                system("cls");
                fflush(stdin);
                return;
            }
        }
        else
        {
            printf("\n没有构建哈夫曼树,无法进行编码\n");
            system("pause");
            system("cls");
            fflush(stdin);
            return;
        }
    }
    CreateHuffmanCode();
    if (NULL == (fp = fopen("ToBeTran.txt", "w")))
    {
        printf("\nToBeTran.txt文件创建错误\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\n请使用这些字符：  ");
    for (i = 1; i <= N; i++)
    {
        if (HC[i].letter == ' ')
            printf("%-5s", "空格");
        else
            printf("%-5c", HC[i].letter);
    }
    printf("\n\n请输入一串要编码的文本\n");
    fflush(stdin);
    gets(str);
    fputs(str, fp);
    fclose(fp);
    printf("\n输入的文本已经存入ToBeTran.txt文件\n");
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
            printf("\n有不能编码的字符:%c\n退出后重试\n", str[i]);
            system("pause");
            system("cls");
            return;
        }
    }
    printf("\n编码结果：\n");
    for (i = 0; codehf[i]; i++)
    {
        printf("%c", codehf[i]);
        if (i % 50 == 49)
            printf("\n");
    }
    if (NULL == (fp = fopen("CodeFile.txt", "w")))
    {
        printf("\nCodeFile.txt文件创建错误\n");
        system("pause");
        system("cls");
        return;
    }
    fputs(codehf, fp);
    fclose(fp);
    printf("\n编码结果已经存入CodeFile.txt文件\n");
    system("pause");
    system("cls");
    fflush(stdin);
}

void DeCodetxt()
{ //译码文件
    char str[1024];
    char codehf[2048];
    int i, j, start, temp;
    FILE *fp;
    system("cls");
    if (NULL == HT)
    {
        printf("\n当前内存中没有哈夫曼树,是否从hfmTree.txt文件读取(Y/N)\n");
        fflush(stdin);
        if ('Y' == getc(stdin))
        {
            if (FILEhfmtree() == 0)
            {
                printf("\nhfmTree.txt中没有哈夫曼树,请使用功能I初始化\n");
                system("pause");
                system("cls");
                fflush(stdin);
                return;
            }
        }
        else
        {
            printf("\n没有构建哈夫曼树,无法进行译码\n");
            system("pause");
            system("cls");
            fflush(stdin);
            return;
        }
    }
    CreateHuffmanCode();
    printf("\n当前的哈夫曼树中:\n");
    Puteverycode();
    if (NULL == (fp = fopen("CodeFile.txt", "r")))
    {
        printf("\nCodeFile.txt文件读取错误\n");
        system("pause");
        system("cls");
        return;
    }
    fgets(codehf, 2048, fp);
    fclose(fp);
    printf("\nCodeFile.txt文件源码中: \n");
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
    printf("\n\n译码结果：\n");
    for (i = 0; str[i]; i++)
    {
        printf("%c", str[i]);
        if (i % 50 == 49)
            printf("\n");
    }
    if (NULL == (fp = fopen("TextFile.txt", "w")))
    {
        printf("\nTextFile.txt文件创建错误\n");
        system("pause");
        system("cls");
        return;
    }
    fputs(str, fp);
    fclose(fp);
    printf("\n\n译码结果已经存入TextFile.txt文件中\n");
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
        printf("\nCodeFile.txt文件读取错误\n");
        system("pause");
        system("cls");
        return;
    }
    fgets(codehf, 2048, fp);
    fclose(fp);
    if (NULL == (fp = fopen("CodePrin.txt", "w")))
    {
        printf("\nCodePrin.txt文件生成错误\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\nCodeFile.txt文件内容：\n");
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
    printf("\n\n每行50个编码的文件已经写入CodePrin.txt文件\n");
    system("pause");
    system("cls");
}

void Printhftree()
{ //打印哈夫曼树到文件
    int i, m = 2 * N - 1;
    FILE *fp;
    if (HT == NULL)
    {
        printf("\n当前内存中没有哈夫曼树\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\n输出哈夫曼树表\n");
    printf("\n%-6s%-6s%-6s%-8s%-8s%-6s\n", "编号", "字符", "权值", "左孩子", "右孩子", "父亲");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ')
            printf("%-6d%-6s%-6d%-8d%-8d%-6d\n", i, "空格", HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= m; i++)
        printf("%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    printf("\n");

    if (NULL == (fp = fopen("TreePrint.txt", "w")))
    {
        printf("TreePrint.txt文件创建错误\n");
        system("pause");
        system("cls");
        return;
    }
    fprintf(fp, "%-6s%-6s%-6s%-8s%-8s%-6s\n", "编号", "字符", "权值", "左孩子", "右孩子", "父亲");
    for (i = 1; i <= N; i++)
    {
        if (HT[i].letter == ' ') //空格用@代替,方便读文件
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, '@', HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
        else
            fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    }
    for (i; i <= 2 * N - 1; i++)
        fprintf(fp, "%-6d%-6c%-6d%-8d%-8d%-6d\n", i, HT[i].letter, HT[i].weight, HT[i].Lchild, HT[i].Rchild, HT[i].Parent);
    fclose(fp);
    printf("\n哈夫曼树表已经写入TreePrint.txt中\n");
    system("pause");
    system("cls");
}