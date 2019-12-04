#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define NOTFOUND -3
#define NUM 10  //二叉树的数量

typedef int status;
typedef int ElemType;
typedef char TElemType;

typedef struct BiTNode
{
    ElemType key;   //关键字
    TElemType data;  
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;  //二叉树的二叉链表存储表示

typedef struct
{
    char name[30];  //用于储存二叉树的名称
    BiTNode *root;
}BinaryTree;  

typedef struct
{
    BinaryTree Tree[NUM];
    int length;
    int listsize;
}SqList;  //储存多个二叉树

typedef struct SNode
{
    BiTree temp;
    struct SNode *next;
}SNode, *Stack;  //堆栈的定义

//所需实现的功能
status visit(BiTree T);
status CreateKey(BiTree T, ElemType e);
status CreateBiTree(BiTree *T);
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree T);
status BiTreeEmpty(BiTree T);
status BiTreeDepth(BiTree T);
BiTree LocateNode(BiTree T, ElemType e);
status Assign(BiTree T, ElemType e, TElemType value);
BiTree GetSibling(BiTree T, ElemType e);
status InsertNode(BiTree T, ElemType e, int LR, TElemType ch);
status DeleteNode(BiTree T, ElemType e);
status PreOrderTraverse(BiTree T, status (* visit)(BiTree T));
status InOrderTraverse(BiTree T, status (* visit)(BiTree T));
status PostOrderTraverse(BiTree T, status (* visit)(BiTree T));
status LevelOrderTraverse(BiTree T);
status SaveBiTree(BinaryTree T);
status LoadBiTree(BiTree T);
status InitBiTree(BiTree *T)
{
    // 初始化
    (*T) = (BiTNode *)malloc(sizeof(BiTNode));
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    (*T)->key = 0;
    (*T)->data = '#'; //左右子树为空
    return OK;
}
int GetID()
{
    // 输入ID
    int id = 0;
    printf("请输入id(1-%d)：", NUM);
    scanf("%d", &id);
    while (id < 1 || id > NUM)
    {
        printf("id值无效，请重新输入id(1-%d)：", NUM);
        scanf("%d", &id);
    }
    return id;
}

//主函数
int main()
{
	SqList L;  //相当于用数组构建多树操作的框架
	BiTree  p;  //用BiTree构建的BiTNode指针
	int op = 1, e;  
    int i, id = 1, LR;  //num默认为1，即默认在第一棵树进行操作，LR用来表示方向
    char ch;  //用来接收data域的值
    for(i = 0; i<NUM; i++)
        L.Tree[i].root = NULL;
    while (op)
    {
        system("clear");
        printf("\n\n");
        printf("     Menu for Binary Tree On Binary Linked List \n\n");
        printf("-------------------------------------------------\n");
        printf("1.  CreateBiTree        2.  DestroyBiTree\n");
        printf("3.  ClearBiTree         4.  BiTreeEmpty\n");
        printf("5.  BiTreeDepth         6.  LocateNode\n");
        printf("7.  Assign              8.  GetSibling \n");
        printf("9.  InsertNode          10. DeleteNode \n");
        printf("11. PreOrderTraverse    12. InOrderTraverse \n");
        printf("13. PostOrderTraverse   14. LevelOrderTraverse \n");
        printf("15. SaveTree            16. LoadTreee\n");
        printf("0.  Exit\n");
        printf("-------------------------------------------------\n");

        printf("请选择你的操作[0~16]:");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            // 创建树
            id = GetID();
            getchar();
            if(L.Tree[id - 1].root != NULL)
                printf("二叉树已存在!\n");
            else
            {
                InitBiTree(&(L.Tree[id - 1].root));
                printf("input tree name:");
                scanf("%s", L.Tree[id - 1].name);
                getchar();
                printf("以前序遍历的方式输入 \'#\'表示空结点:\n");
                if (CreateBiTree(&(L.Tree[id - 1].root->rchild)) == OK)
                    printf("二叉树创建成功\n");
            }
            CreateKey(L.Tree[id - 1].root->rchild, 1);
            printf("按Enter键继续");
            getchar();
            break;
        case 2:
            // 销毁二叉树
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                DestroyBiTree(&(L.Tree[id - 1].root));
                printf("销毁成功\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 3:
            // 清空二叉树 同时根结点为无效数据
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                ClearBiTree(L.Tree[id - 1].root);
                printf("清空成功\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 4:
            // 判断空树
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                if (BiTreeEmpty(L.Tree[id - 1].root) == TRUE)
                    printf("二叉树为空\n");
                else
                    printf("二叉树不为空\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 5:
            // 求深度 注意空树
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                // 空树处理
                if (BiTreeEmpty(L.Tree[id - 1].root))
                    printf("二叉树是空树 高度为0\n");
                else
                {
                    printf("二叉树的深度是%d\n", BiTreeDepth(L.Tree[id - 1].root->rchild));
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 6:
            // LocateNode
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                printf("请输入要查找的key:");
                scanf("%d", &e);
                p = LocateNode(L.Tree[id - 1].root, e);
                if (p == NULL)
                    printf("不存在key为%d的结点\n", e);
                else
                {
                    printf("key为%d的结点的地址是%p\n", e, p);
                    printf("其结点的值域为:%c\n",p->data);
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 7:
            // Assign
            id = GetID();
            getchar();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                printf("请输入要赋值的结点的key:");
                scanf("%d", &e);
                getchar();
                p = LocateNode(L.Tree[id - 1].root, e);
                if (p == NULL)
                    printf("不存在key为%d的结点\n", e);
                else
                {
                    printf("请输入要赋予的值：");
                    scanf("%c", &ch);
                    Assign(L.Tree[id - 1].root, e, ch);
                    printf("赋值成功\n");
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 8:
            //GetSibling
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                printf("请输入结点的key:");
                scanf("%d", &e);
                p = LocateNode(L.Tree[id - 1].root, e);
                if (p == NULL)
                    printf("不存在key为%d的结点\n", e);
                else
                {
                    p = GetSibling(L.Tree[id - 1].root, e);
                    if (p)
                    {
                        printf("key为%d的结点的兄弟的地址是%p\n", e, p);
                        printf("其结点的值域为:%c\n",p->data);
                    }
                    else
                    {
                        printf("key为%d的结点没有兄弟结点\n", e);
                    }
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 9:
            // InsertNode
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                printf("请输入结点的key:");
                scanf("%d", &e);
                getchar();
                p = LocateNode(L.Tree[id - 1].root, e);
                if (p == NULL)
                    printf("不存在key为%d的结点\n", e);
                else
                {
                    printf("请输入要插入的字符:");
                    scanf("%c", &ch);
                    printf("插入在左树或者右树（左0右1）");
                    scanf("%d", &LR);
                    if (InsertNode(L.Tree[id - 1].root, e, LR, ch) == OK)
                        printf("插入成功\n");
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 10:
            // DeleteNode
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
            {
                printf("请输入要删除的结点的key:");
                scanf("%d", &e);
                p = LocateNode(L.Tree[id - 1].root, e);
                if (p == NULL)
                    printf("不存在key为%d的结点\n", e);
                else
                {
                    DeleteNode(L.Tree[id - 1].root, e);
                    printf("删除成功\n");
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 11:
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else if(L.Tree[id - 1].root->lchild == NULL&&L.Tree[id - 1].root->rchild ==NULL)
                printf("二叉树为空!\n");
            else
                PreOrderTraverse(L.Tree[id - 1].root,visit);
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 12:
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else if(L.Tree[id - 1].root->lchild == NULL&&L.Tree[id - 1].root->rchild ==NULL)
                printf("二叉树为空!\n");
            else
                InOrderTraverse(L.Tree[id - 1].root,visit);
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 13:
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else if(L.Tree[id - 1].root->lchild == NULL&&L.Tree[id - 1].root->rchild ==NULL)
                printf("二叉树为空!\n");
            else
                PostOrderTraverse(L.Tree[id - 1].root,visit);
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 14:
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else if(L.Tree[id - 1].root->lchild == NULL&&L.Tree[id - 1].root->rchild ==NULL)
                printf("二叉树为空!\n");
            else
                LevelOrderTraverse(L.Tree[id - 1].root->rchild);
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 15:
            // Save
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
                SaveBiTree(L.Tree[id - 1]);
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 16:
            id = GetID();
            if (L.Tree[id - 1].root == NULL) // 二叉树未创建！
                printf("二叉树未创建！\n");
            else
                LoadBiTree(L.Tree[id - 1].root);
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        default:
            break;
        }
    }
}

//函数的实现
//堆栈操作
Stack CreateStack()
{ /* 构建一个堆栈的头结点，返回该结点指针 */
    Stack S;

    S = (Stack)malloc(sizeof(struct SNode));
    S->next = NULL;
    return S;
}

status IsEmptyS(Stack S)
{ /* 判断堆栈S是否为空，若是返回true；否则返回false */
    if(S->next == NULL)
        return TRUE;
    else
        return FALSE;
}

status Push(Stack S, BiTree X)
{ /* 将元素X压入堆栈S */
    Stack TempStack;

    TempStack = (Stack)malloc(sizeof(struct SNode));
    TempStack->temp = X;
    TempStack->next = S->next;
    S->next = TempStack;
    return TRUE;
}

BiTree Pop(Stack S)
{ /* 删除并返回堆栈S的栈顶元素 */
    Stack FirstStack;
    BiTree TopElem;

    if (IsEmptyS(S))
    {
        printf("堆栈空");
        return ERROR;
    }
    else
    {
        FirstStack = S->next;
        TopElem = FirstStack->temp;
        S->next = FirstStack->next;
        free(FirstStack);
        return TopElem;
    }
}

//visit函数
status visit(BiTree T)
{
    printf("%c",T->data);
    return 0;
}
//生成关键字
status CreateKey(BiTree T, ElemType e)
{
    if(T)
    {
        T->key = e;
        CreateKey(T->lchild, e * 2);
        CreateKey(T->rchild, e * 2 + 1);
    }
    return OK;
}
//创建二叉树
status CreateBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c",&ch);
    getchar();
    if(ch=='#')
        *T = NULL;
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        if(!*T)
            return OVERFLOW;
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
    return OK;
}

//销毁二叉树
status DestroyBiTree(BiTree *T)
{
    if((*T)->lchild)
        DestroyBiTree(&((*T)->lchild));
    if((*T)->rchild)
        DestroyBiTree(&((*T)->rchild));
    free(*T);
    *T = NULL;
    return OK;
}

//清空二叉树
status ClearBiTree(BiTree T)
{
    if(T->lchild)
        DestroyBiTree(&(T->lchild));
    if(T->rchild)
        DestroyBiTree(&(T->rchild));
    return OK; 
}

//判定空二叉数
status BiTreeEmpty(BiTree T)
{
    if(T->rchild==NULL)
        return TRUE;
    else
        return FALSE;
}

//求二叉树的深度
status BiTreeDepth(BiTree T)
{
    int depth = 0;
    int lchilddepth = 0;
    int rchilddepth = 0;
    if(T)
    {
        if(T->lchild)
            lchilddepth = BiTreeDepth(T->lchild);
        if(T->rchild)
            rchilddepth = BiTreeDepth(T->rchild);
        depth = (lchilddepth >= rchilddepth) ? (lchilddepth + 1) : (rchilddepth + 1);
    }
    return depth;
}

//查找结点
BiTree LocateNode(BiTree T, ElemType e)
{
    int maxleng = BiTreeDepth(T);
    BiTree st[maxleng + 1];
    BiTree t = T;
    int top = 0;
    do
    {
        while (t)
        {
            st[++top] = t;
            t = t->lchild;
        }
        if(top)
        {
            t = st[top--];
            if(t->key == e)
                return t;
            t = t->rchild;
        }
    } while (top||t);
    return NULL;
}

//结点赋值
status Assign(BiTree T, ElemType e, TElemType value)
{
    BiTree t = LocateNode(T, e);
    if(t)
    {
        t->data = value;
        return OK;
    }
    else
        return ERROR;  //树中没有该结点
}

//获得兄弟结点
BiTree GetSibling(BiTree T, ElemType e)
{
    BiTree t = T;
    if(e % 2 ==0)
        t = LocateNode(T, e + 1);
    else
        t = LocateNode(T, e - 1);
    return t;
}

//插入结点
status InsertNode(BiTree T, ElemType e, int LR, TElemType ch)
{
    BiTree t, c = (BiTNode *)malloc(sizeof(BiTNode));
    t = LocateNode(T, e);
    c->data = ch;
    c->lchild = NULL;
    c->rchild = NULL;
    if(!t)
        return ERROR;
    if(LR == 0)
    {
        c->rchild = t->lchild;
        t->lchild = c;
    }
    if(LR == 1)
    {
        c->rchild = t->rchild;
        t->rchild = c;
    }
    CreateKey(t, e);
    return OK;
}

//删除结点
status DeleteNode(BiTree T, ElemType e)
{
    BiTree t, p, q;
    t = LocateNode(T, e/2);
    p = LocateNode(T, e);
    if(p == NULL)
        return ERROR;
    if(p->lchild == NULL&&p->rchild ==NULL)
    {
        if(e % 2 ==0)
            t->lchild = NULL;
        else
            t->rchild = NULL;
        free(p);
    }
    else if(p->lchild != NULL&&p->rchild !=NULL)
    {
        if(e % 2 ==0)
            t->lchild = p->lchild;
        else
            t->rchild = p->lchild;
        q = p->lchild;
        while(q->rchild)
            q = q->rchild;
        q->rchild = p->rchild;
        free(p);
    }
    else if(p->lchild != NULL&&p->rchild ==NULL)
    {
        if(e % 2 ==0)
            t->lchild = p->lchild;
        else
            t->rchild = p->lchild;
        free(p);
    }
    else
    {
        if(e % 2 ==0)
            t->lchild = p->rchild;
        else
            t->rchild = p->rchild;
        free(p);
    }
    if(e != 1)
        CreateKey(t,e/2);
    else
        CreateKey(t->rchild,1);
    return OK;
}

//前序遍历
status PreOrderTraverse(BiTree T, status (* visit)(BiTree T))
{
    if(T)
    {
        if(T->key != 0)
            visit(T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
    }
    return OK;
}

//中序遍历
status InOrderTraverse(BiTree T, status (* visit)(BiTree T))
{
    int maxleng = BiTreeDepth(T);
    BiTree st[maxleng + 1];
    BiTree t = T->rchild;
    int top = 0;
    do
    {
        while (t)
        {
            st[++top] = t;
            t = t->lchild;
        }
        if(top)
        {
            t = st[top--];
            visit(t);
            t = t->rchild;
        }
    } while (top||t);
    return OK;
}

//后序遍历
status PostOrderTraverse(BiTree T, status (* visit)(BiTree T))
{
    if(T)
    {
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
        if(T->key != 0)
            visit(T);
    }
    return OK;
}

//层序遍历辅助函数
void level(BiTree T, int i)
{
	if(T)
	{
		if(i == 1)
		    printf("%c",T->data);  //该函数用来辅助层序遍历
		else
		{
			level(T->lchild, i-1);
			level(T->rchild, i-1);
		}
	}
}
//按层遍历
status LevelOrderTraverse(BiTree T)
{
    if(T)
	{
        int maxleng = BiTreeDepth(T), i;
		for(i=1; i <= maxleng; i++)
		{
			level(T, i);  //对每一层进行访问
            printf("\n");
		}
		return OK;
	}
	else
	return ERROR;
}

status SaveBiTree(BinaryTree T)
{
    FILE *fp;
    char filename[30];
    printf("保存的文件名为二叉树的名称\n");
    strcpy(filename,T.name);
    // 写文件
    if ((fp = fopen(filename, "wb")) == NULL) //文件打开失败
    {
        printf("File open error\n ");
        return ERROR;
    }
    // 使用先序遍历的顺序保存
    Stack S;
    BiTree p, q;
    TElemType ch;
    ElemType key;
    q = T.root;
    S = CreateStack();
    Push(S,q->rchild);
    while (!IsEmptyS(S))
    {
        p = Pop(S);
        ch = p->data;
        key = p->key;
        fwrite(&(ch), sizeof(TElemType), 1, fp);
        fwrite(&(key), sizeof(ElemType), 1, fp);
        if(p->rchild)
            Push(S,p->rchild);
        if(p->lchild)
            Push(S,p->lchild);
    }
    fclose(fp);
    printf("保存成功!\n");
    return OK;
}
status LoadBiTree(BiTree T)
{
    FILE *fp;
    BiTree P = T->rchild;
    BiTree Temp = NULL;
    char filename[30];
    printf("input filename: ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    // 根节点
    Temp = (BiTree)malloc(sizeof(BiTNode));
    fread(&(Temp->data), sizeof(TElemType), 1, fp);
    fread(&(Temp->key), sizeof(ElemType), 1, fp);
    Temp->lchild = Temp->rchild = NULL;
    T->rchild = Temp;

    //其他节点
    Temp = (BiTree)malloc(sizeof(BiTNode));
    while (fread(&(Temp->data), sizeof(TElemType), 1, fp) && fread(&(Temp->key), sizeof(ElemType), 1, fp))
    {
        Temp->lchild = Temp->rchild = NULL;
        P = LocateNode(T, Temp->key / 2);
        if (Temp->key % 2 == 0) // Temp是p的左儿子
            P->lchild = Temp;
        else if (Temp->key % 2 == 1)
            P->rchild = Temp;
        Temp = (BiTree)malloc(sizeof(BiTNode));
    }
    fclose(fp);
    printf("加载成功!\n");
    return OK;
}