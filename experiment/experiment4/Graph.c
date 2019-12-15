/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define NUM 10  //多图的数量

typedef int status;
typedef char VertexType;
bool visited[MAX_VERTEX_NUM];

//表结点结构
typedef struct ArcBox
{
    int tailvex, headvex;          //该弧所指向的顶点的位置
    struct ArcBox *hlink, *tlink; //分别为弧头相同和弧尾相同的弧的链域
} ArcBox;

//头结点结构
typedef struct VexNode
{
    VertexType data;            //顶点信息，节点的名称
    int key;                    //关键字key用来标记顶点,便于查询
    ArcBox *firstin, *firstout; //分别指向该顶点的第一条入弧和出弧
} VexNode;

//图的结构
typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];
    int vexnum, arcnum; //有向图的当前顶点数,边数
} OLGraph;

//辅助队列
typedef struct _QUEUENODE_
{
    int data;
    struct _QUEUENODE_ *next;
} QueueNode;
typedef struct _QUEUE_
{
    QueueNode *pHead;
    QueueNode *pTail;
    int size;
} Queue;
bool InitQueue(Queue *Q);
bool DestroyQueue(Queue *Q);
bool DeQueue(Queue *Q, int *e);
bool EnQueue(Queue *Q, int e);
bool QueueEmpty(Queue Q);


//需实现的函数
status CreateOLGraph(OLGraph *G);                               //采用十字链表储存表示，构造有向图G
status DestroyOLGraph(OLGraph *G);                              //销毁有向图G
int LocateVex(OLGraph *G, int u);
int LocateVex_OL(OLGraph *G, VertexType u);                           //查找顶点
status PutVex(OLGraph *G, int u, VertexType value);         //顶点赋值
int FirstAdjVex(OLGraph *G, int u);                         //获得第一邻接点
int NextAdjVex(OLGraph *G, int v, int w);                   //获得下一邻接点
status InsertVex(OLGraph *G, VertexType v);                 //插入顶点
status DeleteVex(OLGraph *G, VertexType v);                 //删除顶点
status InsertArc(OLGraph *G, VertexType v, VertexType w);   //插入弧
status DeleteArc(OLGraph *G, VertexType v, VertexType w);   //删除弧
status DFSTraverse(OLGraph *G);                             //深度优先搜索
status BFSTraverse(OLGraph *G);                             //广度优先搜索
status SaveOLGraph(OLGraph *G);                             //将图存储到二进制文件
status LoadOLGraph(OLGraph *G);                             //从二进制文件中加载图

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
    return (id - 1);
}

//主函数
int main()
{
    OLGraph G[NUM];
    int i = 0;
    int id = 0;
    int v = 0, u = 0, key = 0;
    char ch1, ch2;  // 用来查找
    for(i = 0; i < NUM; i++)
        G[i].xlist[0].data = '\0';
    int op = 1;
    while(op)
    {
        system("clear");
        printf("\n\n");
        printf("     Menu for Binary Tree On Binary Linked List \n\n");
        printf("-------------------------------------------------\n");
        printf("1.  CreateOLGraph   2.  DestroyOLGraph   \n");
        printf("3.  LocateVex       4.  PutVex      \n");
        printf("5.  FirstAdjVex     6.  NextAdjVex  \n");
        printf("7.  InsertVex       8.  DeleteVex   \n");
        printf("9.  InsertArc       10. DeleteArc   \n");
        printf("11. DFSTravers      12. BFSTraverse \n");
        printf("13. SaveOLGraph     14. LoadOLGraph \n");
        printf("0.  Exit\n");
        printf("-------------------------------------------------\n");

        printf("请选择你的操作[0~14]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // 创建
            id = GetID();
            if (CreateOLGraph(G + id) == OK)
                printf("创建成功\n");
            else
                printf("创建失败\n");
            printf("按Enter键继续");
            getchar();
            break;
        case 2:
            // Destroy
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                if (DestroyOLGraph(G + id) == OK)
                    printf("销毁成功!\n");
                else
                    printf("销毁失败!\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 3:
            //LocateVex
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入要查找的顶点的key");
                scanf("%d", &key);
                if (LocateVex(G + id, key) == ERROR)
                    printf("该顶点不存在\n");
                else
                    printf("该顶点为%c的位序为%d\n",G[id].xlist[key].data, LocateVex(G + id, key));
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 4:
            // PutVex
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入所要赋值的顶点的key值: ");
                scanf("%d", &key);
                if (LocateVex(G + id, key) == ERROR)
                    printf("图中不存在该key值的顶点\n");
                else
                {
                    printf("请输入要赋予的值: ");
                    getchar();
                    scanf("%c", &ch1);
                    if (PutVex(G + id, key, ch1) == OK)
                        printf("赋值成功\n");
                    else
                        printf("赋值失败\n");
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 5:
            // FirstAdjVex
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("输入顶点的位序: ");
                scanf("%d", &u);
                if (u < 0 || u > G[id].vexnum - 1)
                    printf("位序值不合法");
                else
                {
                    if (FirstAdjVex(G + id, u) == ERROR)
                        printf("该顶点没有邻接顶点\n");
                    else
                        printf("该顶点的第一邻接点的位置是%d\n", FirstAdjVex(G + id, u));
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 6:
            // NextAdjVex
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("输入两个顶点的位序: ");
                scanf("%d%d", &u, &v);
                if (u < 0 || u > G[id].vexnum - 1)
                    printf("位序值不合法");
                if (v < 0 || v > G[id].vexnum - 1)
                    printf("位序值不合法");
                else if (NextAdjVex(G + id, u, v) == ERROR)
                    printf("该顶点是最后一个邻接顶点\n");
                else
                    printf("该顶点的下一个邻接点的位置是%d\n", NextAdjVex(G + id, u, v));
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 7:
            // InsertVex
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入要插入的顶点的data: ");
                getchar();
                scanf("%c", &ch1);
                if (InsertVex(G + id, ch1) == OK)
                    printf("插入成功\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 8:
            // DeleteVex
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入要删除的顶点的值: ");
                getchar();
                scanf("%c", &ch1);
                if (LocateVex_OL(G + id, ch1) == ERROR)
                    printf("该顶点不存在\n");
                else
                {
                    if (DeleteVex(G + id, ch1) == OK)
                        printf("删除成功\n");
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 9:
            // InserArc
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入弧连接的两个顶点: ");
                getchar();
                scanf("%c%c", &ch1, &ch2);
                if (InsertArc(G + id, ch1, ch2) == OK)
                    printf("插入成功\n");
                else
                    printf("插入失败\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 10:
            //DeleteArc
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入弧连接的两个顶点: ");
                getchar();
                scanf("%c%c", &ch1, &ch2);
                if (LocateVex_OL(G + id, ch1) < 0 || LocateVex_OL(G + id, ch2) < 0)
                    printf("弧不存在\n");
                else
                {
                    if (DeleteArc(G + id, ch1, ch2) == OK)
                        printf("删除成功\n");
                }
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 11:
            // DFS
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("深度优先搜索\n");
                DFSTraverse(G + id);
            }
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 12:
            //BFS
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("广度优先搜索\n");
                BFSTraverse(G + id);
            }
            printf("\n按Enter键继续");
            getchar();
            getchar();
            break;
        case 13:
            id = GetID();
            if (G[id].xlist[0].data == 0)
                printf("该ID的图未创建\n");
            else
            {
                if (SaveOLGraph(G + id) == OK)
                    printf("保存成功\n");
            }
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 14:
            id = GetID();
            if (LoadOLGraph(G + id) == OK)
                printf("加载成功\n");
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        default:
            break;
        }
    }
    return 0;
}

//-----------------------------------------------------------
bool InitQueue(Queue *Q)
{
    Q->pHead = Q->pTail = (QueueNode *)malloc(sizeof(QueueNode));
    if (!Q->pHead)
    {
        return false;
    }
    Q->pHead->next = NULL;
    Q->size = 0;
    return true;
}
bool EnQueue(Queue *Q, int e)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (!newNode)
    {
        return false;
    }
    newNode->data = e;
    newNode->next = NULL;
    Q->pTail->next = newNode;
    Q->pTail = newNode;
    Q->size++;
    return true;
}
bool DeQueue(Queue *Q, int *e)
{
    QueueNode *pDel = Q->pHead->next;
    if (!pDel)
    {
        return false;
    }
    *e = pDel->data;
    if (Q->pTail == pDel)
    {
        Q->pTail = Q->pHead;
    }
    Q->pHead->next = pDel->next;
    free(pDel);
    Q->size--;

    return true;
}
bool QueueEmpty(Queue Q)
{
    return Q.size == 0;
}
bool DestroyQueue(Queue *Q)
{
    QueueNode *p, *q;
    p = Q->pHead->next;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(Q->pHead);
    Q->pHead = NULL;
    Q->size = 0;
    return true;
}

//函数的实现
//采用十字链表储存表示，构造有向图G
status CreateOLGraph(OLGraph *G)
{
    int i, j, k;
    VertexType v1, v2;
    ArcBox *p;
    printf("输入顶点数: ");
    scanf("%d", &(G->vexnum));
    printf("输入弧数: ");
    scanf("%d", &(G->arcnum));
    printf("输入各个顶点值: ");
    getchar();
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%c", &(G->xlist[i].data));
        getchar();
        G->xlist[i].key = i;
        G->xlist[i].firstin = NULL;
        G->xlist[i].firstout = NULL;
    }

    printf("读取各边，构造十字链表\n");
    printf("输入相邻结点:");
    for (k = 1; k <= G->arcnum; k++)
    {
        scanf("%c%c", &v1, &v2);
        getchar();
        i = LocateVex_OL(G, v1); //第i个结点的链表相连
        j = LocateVex_OL(G, v2);
        if (i == -1 || j == -1) //如果输入的弧信息错误 （节点错误）
        {
            printf("ERROR\n");
            return ERROR;
        }
        p = (ArcBox *)malloc(sizeof(ArcBox));
        if (!p)
            exit(OVERFLOW);
        p->tailvex = i;
        p->headvex = j;
        p->hlink = G->xlist[j].firstin; //把p插到第一个结点中去
        G->xlist[j].firstin = p;

        p->tlink = G->xlist[i].firstout;
        G->xlist[i].firstout = p;
    }
    return OK;
}

//销毁有向图G
status DestroyOLGraph(OLGraph *G)
{
    int i;
    ArcBox *pArc1, *pArc2;
    for (i = 0; i < G->vexnum; i++)
    {
        pArc1 = G->xlist[i].firstout;

        while (pArc1)
        {
            pArc2 = pArc1->tlink;
            free(pArc1);
            pArc1 = pArc2;
        }
    }
    G->xlist[0].data = '\0';
    return OK;
}

//查找顶点
int LocateVex_OL(OLGraph *G, VertexType u)
{
    int i;
    for (i = 0; i < G->vexnum; i++)
    {
        if (G->xlist[i].data == u)
            return i;
    }
    return ERROR;
}

int LocateVex(OLGraph *G, int u)
{
    int i;
    for (i = 0; i < G->vexnum; i++)
    {
        if (G->xlist[i].key == u)
            return i;
    }
    return ERROR;
}

//顶点赋值
status PutVex(OLGraph *G, int u, VertexType value)
{
    int i;
    i = LocateVex(G, u);
    G->xlist[i].data = value;
    return OK;
}

//获得第一邻接点
int FirstAdjVex(OLGraph *G, int u)
{
    ArcBox *p = G->xlist[u].firstout;
    if (p)
        return p->headvex;
    else
        return ERROR;
}

//获得下一邻接点
int NextAdjVex(OLGraph *G, int v, int w)
{
    ArcBox *pArc;
    pArc = G->xlist[v].firstout;
    while (pArc->headvex != w)
    {
        pArc = pArc->tlink;
    }
    pArc = pArc->tlink;
    if (pArc)
    {
        return pArc->headvex;
    }
    else
    {
        return ERROR;
    }
}

//插入顶点
status InsertVex(OLGraph *G, VertexType v)
{
    G->xlist[G->vexnum].data = v;
    G->xlist[G->vexnum].key = G->vexnum;
    G->xlist[G->vexnum].firstin = G->xlist[G->vexnum].firstout = NULL;
    G->vexnum++;
    return OK;
}

//删除顶点
status DeleteVex(OLGraph *G, VertexType v)
{
    int j, k;
    ArcBox *p;
    VertexType w;
    k = LocateVex_OL(G, v);
    //删除所有以v为尾或者头顶点的弧
    for(j = 0; j <G->vexnum; j++)
    {
        if(j == k)
            continue;
        w = G->xlist[j].data;
        if(DeleteArc(G, v, w) == ERROR)
            continue;
    }
    for(j = 0; j <G->vexnum; j++)
    {
        if(j == k)
            continue;
        w = G->xlist[j].data;
        if(DeleteArc(G, w, v) == ERROR)
            continue;
    }
    //删除顶点v
    //序号>k的顶点依次向前移
    for (j = k + 1; j < G->vexnum; j++)
    {
        G->xlist[j].key--;
        G->xlist[j - 1] = G->xlist[j];
    }
    G->vexnum--;
    //结点序号>k的要减1
    for (j = 0; j < G->vexnum; j++)
    {
        p = G->xlist[j].firstout;
        while (p)
        {
            if (p->headvex > k)
            {
                p->headvex--;
            }
            if (p->tailvex > k)
            {
                p->tailvex--;
            }
            p = p->tlink;
        }
    }
    return OK;
}

//插入弧
status InsertArc(OLGraph *G, VertexType v, VertexType w)
{
    int i, j;
    ArcBox *pArc;
    i = LocateVex_OL(G, v); //弧尾
    j = LocateVex_OL(G, w); //弧头
    if (i == -1 || j == -1)
        {
            return ERROR;
        }
    pArc = (ArcBox *)malloc(sizeof(ArcBox));
    pArc->tailvex = i;
    pArc->headvex = j;
    //将pArc插入到第一个结点
    pArc->tlink = G->xlist[i].firstout;
    pArc->hlink = G->xlist[j].firstin;
    G->xlist[i].firstout = pArc;
    G->xlist[j].firstin = pArc;
    G->arcnum++;
    return OK;
}

//删除弧
status DeleteArc(OLGraph *G, VertexType v, VertexType w)
{
    int i, j;
    ArcBox *p, *q;
    i = LocateVex_OL(G, v);
    j = LocateVex_OL(G, w);
    if (i == -1 || j == -1)
        {
            printf("ERROR\n");
            return ERROR;
        }
    //先删除顶点v出弧
    p = G->xlist[i].firstout;
    if (p && p->headvex == j) //待删结点为首节点
    {
        G->xlist[i].firstout = p->tlink;
    }
    else
    {
        while (p && p->headvex != j)
        {
            q = p;
            p = p->tlink;
        }
        if (p)
        {
            q->tlink = p->tlink;
        }
        else
            return ERROR; //图中不存在弧<v,w>
    }
    //再删除w入弧
    p = G->xlist[j].firstin;
    if (p->tailvex == i)
    {
        G->xlist[j].firstin = p->hlink;
        free(p);
    }
    else
    {
        while (p->tailvex != i)
        {
            q = p;
            p = p->hlink;
        }
        if (p)
        {
            q->hlink = p->hlink;
        }
    }
    free(p);
    G->arcnum--;
    return OK;
}

//深度优先搜索
void DFS(OLGraph *G, int v)
{
    int i;
    visited[v] = true;
    printf("%c", G->xlist[v].data);
    for (i = FirstAdjVex(G, v); i >= 0; i = NextAdjVex(G, v, i))
    {
        if (!visited[i])
        {
            DFS(G, i);
        }
    }
}

status DFSTraverse(OLGraph *G)
{
    int i;
    for (i = 0; i < G->vexnum; i++)
    {
        visited[i] = false;
    }
    for (i = 0; i < G->vexnum; i++)
    {
        if (!visited[i])
        {
            DFS(G, i);
        }
    }
    return OK;
}

//广度优先搜索
status BFSTraverse(OLGraph *G)
{
    int i, u, w;
    Queue queue;
    InitQueue(&queue);
    for (i = 0; i < G->vexnum; i++)
    {
        visited[i] = false;
    }
    for (i = 0; i < G->vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            printf("%c", G->xlist[i].data);
            EnQueue(&queue, i);
            while (!QueueEmpty(queue))
            {
                DeQueue(&queue, &u);
                for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
                {
                    if (!visited[w])
                    {
                        visited[w] = true;
                        printf("%c", G->xlist[w].data);
                        EnQueue(&queue, w);
                    }
                }
            }
        }
    }
    return OK;
}

//将图存储到二进制文件
status SaveOLGraph(OLGraph *G)
{
    FILE *fp;
	char filename[30];
	printf("input file name: ");
	scanf("%s", filename);

	//写入文件
	if ((fp = fopen(filename, "wb")) == NULL)  //文件打开失败
	{
		printf("File open error\n");
		return ERROR;
	}
    int i;
    ArcBox *p;
    //写入图的信息
    fwrite(&(G->vexnum), sizeof(int), 1, fp);
    fwrite(&(G->arcnum), sizeof(int), 1, fp);
    //写入各个节点
    for(i = 0; i < G->vexnum; i++)
    {
        fwrite(&(G->xlist[i].data), sizeof(VertexType), 1, fp);
        fwrite(&(G->xlist[i].key), sizeof(int), 1, fp);
    }
    //按照顶点出弧的顺序存储弧的信息
    for (i = 0; i < G->vexnum; i++)
    {
        p = G->xlist[i].firstout;
        while (p)
        {
            fwrite(&(p->tailvex), sizeof(int), 1, fp);
            fwrite(&(p->headvex), sizeof(int), 1, fp);
            p = p->tlink;
        }
    }
    fclose(fp);
    return OK;
}

//从二进制文件中加载图
status LoadOLGraph(OLGraph *G)
{
    FILE *fp;
    char filename[41];
    printf("请输入要加载的文件名: ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n");
        return ERROR;
    }
    fread(&(G->vexnum), sizeof(int), 1, fp);
    fread(&(G->arcnum), sizeof(int), 1, fp);
    //恢复各顶点的data和key值
    int m = 0;
    for (m = 0; m < G->vexnum; m++)
    {
        fread(&(G->xlist[m].data), sizeof(VertexType), 1, fp);
        fread(&(G->xlist[m].key), sizeof(int), 1, fp);
        G->xlist[m].firstout = NULL;
        G->xlist[m].firstin = NULL;
    }
    //恢复弧的信息
    ArcBox *p;
    int i = 0;
    int j = 0;
    int n = 0;
    for (n = 0; n < G->arcnum; n++)
    {
        p = (ArcBox *)malloc(sizeof(ArcBox));
        fread(&(i), sizeof(int), 1, fp);
        fread(&(j), sizeof(int), 1, fp);
        p->tailvex = i;
        p->headvex = j;
        p->hlink = G->xlist[j].firstin;  // 弧头
        p->tlink = G->xlist[i].firstout; //弧尾
        G->xlist[j].firstin = p;
        G->xlist[i].firstout = p; //完成入弧和出弧链头的插入
    }
    fclose(fp);
    return OK;
}