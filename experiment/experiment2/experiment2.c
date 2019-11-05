#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define NOTFOUND -3

typedef int status; 
typedef int ElemType; //数据元素类型定义
//线性表的单链表存储结构
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode , *LinkList;



//单链表操作
status InitList(LinkList *L);
status DestroyList(LinkList *L);
status ClearList(LinkList *L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType* e);
status LocateElem(LinkList L,ElemType e); 
status PriorElem(LinkList L,ElemType cur,ElemType* pre_e);
status NextElem(LinkList L,ElemType cur,ElemType* next_e);
status ListInsert(LinkList *L,int i,ElemType e);
status ListDelete(LinkList *L,int i,ElemType *e);
status ListTrabverse(LinkList L);
status InputData(LinkList *L);  //手动输入数据
status SaveList(LinkList L);  //将当前表保存到文件
status LoadList(LinkList *L);  //从文件加载表

//主函数
int main(void)
{
    LinkList L = NULL;
    status a = 1; //用于储存函数的返回值
    // 此处为定义的一些临时变量用于不同的case
	int i , j , e , pre_e , next_e;
    int op = 1;
    while(op)
    {
	    system("clear");	printf("\n\n");
	    printf("      Menu for Linear Table On Sequence Structure \n");
	    printf("-------------------------------------------------\n");
	    printf("    	  1. InitList       9. NextElem\n");
	    printf("    	  2. DestroyList    10. ListInsert\n");
	    printf("    	  3. ClearList      11. ListDelete\n");
	    printf("    	  4. ListEmpty      12. ListTrabverse\n");
	    printf("    	  5. ListLength     13. InputData\n");
	    printf("    	  6. GetElem        14. SavaList\n");
        printf("    	  7. LocateElem     15. LoadList\n");
        printf("    	  8. PriorElem      0. Exit\n");
	    
	    printf("-------------------------------------------------\n");
	    printf("    请选择你的操作[0~15]:");
	    scanf("%d",&op);
        switch (op)
        {
        case 1:  //创建一个空的线性链表
            a = InitList(&L);
            if(a==ERROR)
                printf("线性表已存在，请勿重复创建! \n");
            else if(a==OK)
                printf("线性表创建成功！\n");
            else 
                printf("线性表创建失败！\n");
            printf("按Enter键继续");
		    getchar();
            getchar();
            break;
        case 2:  //销毁一个线性链表
            a = DestroyList(&L);
            if(a == OK) 
                    printf("线性表销毁成功！\n");
		    else 
                printf("线性表未创建，销毁失败！\n");
            printf("按Enter键继续 ");
		    getchar();
            getchar();
		    break;
        case 3:  //将线性表重置为空表
            a = ClearList(&L);
            if (a == OK)
				    printf("线性表清空成功！\n");
			else
			    printf("线性表未创建，清空失败！\n");
		    printf("按Enter键继续");     
	        getchar();                
            getchar();
		    break;
        case 4:  // 判断线性表是否为空
            a = ListEmpty(L);
            if (a == INFEASTABLE)
				    printf("线性表未创建！\n");
			else if (a == FALSE)
				printf("线性表不为空！\n");
			else
				printf("线性表为空！\n");
			printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 5:  //返回线性表L中数据元素的个数
            a = ListLength(L);
            if(a == INFEASTABLE)
                printf("线性表未创建! \n");
            else
            {
                printf("线性表的长度为%d\n",a);
            }
            printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 6:  //用e返回L中第i个数据元素的值
            printf("请输入要取得线性表中的第几个元素： ");
			scanf("%d", &i);
            a = GetElem(L, i, &e);
            if(a!=OK)
            {
                if(a==INFEASTABLE)
                    printf("线性表未创建! \n");
                if(a==ERROR)
                    printf("i值不合法! \n");
            }
            else
            {
                printf("第%d个元素的值为%d\n",i,e);
            }
            printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 7:  //输入一个元素值返回它在表中的位置
            printf("输入线性表中的一个数: ");
			scanf("%d", &e);
            a = LocateElem(L, e);
            if (a == INFEASTABLE)
			{
				printf("线性表未创建\n");
			}
			else if (a == ERROR)
			{
				printf("表中没有这个元素\n");
			}
			else
			{
				printf("%d的位置是%d\n", e, a);
			}
			printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 8:  //用pre_e返回线性表中某个元素的前驱
            printf("输入线性表中的一个数: ");
			scanf("%d", &e);
            a = PriorElem(L, e, &pre_e);
            if (a == OK)
				printf("%d的前驱是%d\n", e, pre_e);
			else if (a == INFEASTABLE)
				printf("线性表未创建\n");
			else if (a == ERROR)
				printf("%d为第一个元素,没有前驱\n", e);
			else if (a == NOTFOUND)
				printf("表中不存在元素%d\n", e);
			printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 9:  //用next_e返回线性表中某个元素的后继
            printf("输入线性表中的一个数: ");
			scanf("%d", &e);
            a = NextElem(L, e, &next_e);
            if (a == OK)
				printf("%d的后继是%d\n", e, next_e);
			else if (a == INFEASTABLE)
				printf("线性表未创建\n");
			else if (a == ERROR)
				printf("%d为最后一个元素,没有后继\n", e);
			else if (a == NOTFOUND)
				printf("表中不存在元素%d\n", e);
			printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 10:  //在L的第i个位置之前插入新的数据元素e
            printf("输入插入的位置i（从1开始计数）\n");
			scanf("%d", &i);
			printf("输入插入的值e\n");
			scanf("%d", &e);
            a = ListInsert(&L, i, e);
            if (a == OK)
				printf("插入成功！\n");
			else if (a == INFEASTABLE)
				printf("线性表未创建\n");
			else if (a == ERROR)
				printf("插入位置不合法\n");
            else
            {
                printf("内存不足! \n");
            }
			printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 11:  //删除L的第i个数据元素，用e返回其值
            printf("输入删除的位置i（从1开始计数）\n");
			scanf("%d", &i);
            a = ListDelete(&L, i, &e);
            if (a == OK)
			{
				printf("删除%d成功！\n", e);
			}
			else if (a == INFEASTABLE)
				printf("线性表未创建\n");
            else if (a == ERROR)
				printf("删除位置不合法\n");
			printf("按Enter键继续");     
		    getchar();
            getchar();
		    break;
        case 12:  //遍历线性表
            a = ListTrabverse(L);
            if(a==INFEASTABLE) 
                printf("线性表未创建！\n");
            else if(a==ERROR)
                printf("线性表为空表! \n");
            printf("按Enter键继续");
		    getchar();
            getchar();
		    break;
        case 13:  //手动输入数据
            a = InputData(&L);
            if(a == INFEASTABLE)
                printf("线性表未创建! \n");
            printf("按Enter键继续");
            getchar();
            getchar();
            break;
        case 14:  //将当前表保存到文件
            a = SaveList(L);
            if(a==INFEASTABLE)
                printf("线性表未创建! \n");
            else if(a==ERROR)
                printf("文件打开失败! \n");
            else
                printf("保存成功! \n");
            printf("按Enter键继续");
		    getchar();
            getchar();
		    break;
        case 15:  //从文件中加载表
            a = LoadList(&L);
            if(a==INFEASTABLE)
                printf("线性表未创建! \n");
            else if(a==ERROR)
                printf("文件打开失败! \n");
            else
                printf("加载成功! \n");
            printf("按Enter键继续");
		    getchar();
            getchar();
		    break;
        case 0:
            break;
        default:
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

//操作函数的实现

//创建一个空的线性链表
status InitList(LinkList *L)
{
    if(*L)
        return ERROR;  //线性链表已存在
    *L = (LinkList)malloc(sizeof(LNode));
    if(!*L)
        return OVERFLOW;
    (*L)->data = 0;
    (*L)->next = NULL;
    return OK;
}

//销毁一个线性链表
status DestroyList(LinkList *L)
{
    if(!*L)
        return INFEASTABLE;  //线性链表未创建
    LinkList p = *L;
    LinkList pNext = p;
    while(p)
    {
        pNext = p->next;
        free(p);
        p = pNext;
    }
    *L = NULL;
    return OK;
}

//清空线性链表
status ClearList(LinkList *L)
{
    if(!*L)
        return INFEASTABLE;  //线性链表未创建
    LinkList p = (*L)->next;
    LinkList pNext = p;
    while(p)
    {
        pNext = p->next;
        free(p);
        p = pNext;
    }
    (*L)->data = 0;
    (*L)->next = NULL;
    return OK;
}

//判定线性链表是否为空表
status ListEmpty(LinkList L)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    if(L->next == NULL)
        return TRUE;  //线性链表为空
    else
        return FALSE;  //线性链表不为空
}

//返回线性链表L中数据元素的个数
int ListLength(LinkList L)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    else
        return L->data;
}

//用e返回L中第i个元素的值
status GetElem(LinkList L, int i, ElemType *e)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    if(i<=0||i>L->data)
        return ERROR;  //i值不合法
    LinkList p = L;
    int j ;
    for(j=1; j<=i; j++)
    {
        p = p->next;
    }
    *e = p->data;
    return OK;
}

//输入一个元素值返回它在表中的位置
status LocateElem(LinkList L, ElemType e)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    LinkList p = L;
    int i;
    for(i=1; i<=L->data; i++)
    {
        p = p->next;
        if(p->data == e)
            return i;  //返回i的值，即为该元素的位置
    }
    return ERROR;  //表中没有该元素
}

//用pre_e返回线性表中某个元素的前驱
status PriorElem(LinkList L, ElemType cur, ElemType *pre_e)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    LinkList p = L;
    if(LocateElem(L,cur)==ERROR)
        return NOTFOUND;  //表中没有该元素
    else if (LocateElem(L,cur)==1)
    {
        return ERROR;  //cur为第一个元素，无前驱
    }
    else
    {
        int i;
        for(i=1; i<LocateElem(L,cur); i++)
            p = p->next;
        *pre_e = p->data;
        return OK;
    }
}

//用next_e返回线性表中某个元素的后继
status NextElem(LinkList L, ElemType cur, ElemType* next_e)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    LinkList p = L;
    if(LocateElem(L,cur)==ERROR)
        return NOTFOUND;  //表中没有该元素
    else if (LocateElem(L,cur)==L->data)
    {
        return ERROR;  //cur为最后个元素，无后继
    }
    else
    {
        int i;
        for(i=1; i<=(LocateElem(L,cur) + 1); i++)
            p = p->next;
        *next_e = p->data;
        return OK;
    }
}

//在L的第i个位置之前插入新的数据元素e
status ListInsert(LinkList *L, int i, ElemType e)
{
    if(!*L)
        return INFEASTABLE;  //线性链表未创建
    if(i<=0||i>(*L)->data+1)
        return ERROR;  //i值不合法
    LinkList p, q, f;
    f = (LinkList)malloc(sizeof(LNode));
    if(!f)
        return OVERFLOW;  //内存不足，插入失败
    f->data = e;
    p = *L;
    int j;
    for(j=1; j<=i; j++)
    {
        q = p;
        p = p->next;
    }
    q->next = f;
    f->next = p;
    (*L)->data++;
    return OK;
}

//删除L的第i个数据元素，用e返回其值
status ListDelete(LinkList *L,int i,ElemType *e)
{
    if(!*L)
        return INFEASTABLE;  //线性链表未创建
    if(i<=0||i>(*L)->data)
        return ERROR;  //i值不合法
    LinkList p, q, f;
    p = *L;
    int j;
    for(j=1; j<=i; j++)
    {
        q = p;
        p = p->next;
    }
    f = p;
    *e = f->data;
    p = p->next;
    q->next = p;
    free(f);
    (*L)->data--;
    return OK;
}

//遍历线性链表
status ListTrabverse(LinkList L)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    if(L->data == 0)
        return ERROR;  //线性链表为空表
    LinkList p = L;
    int i;
    for(i=1; i<L->data; i++)
    {
        p = p->next;
        printf("%d-->", p->data);
    }
    p = p->next;
    printf("%d\n",p->data);
    return OK;
}

//手动输入数据
status InputData(LinkList *L)
{
    if(!*L)
        return INFEASTABLE;  //线性链表未创建
    LinkList p, q;
    p = *L;
    int x;
    printf("请输入若干整数以任意一个字母结束: \n");
    while((scanf("%d",&x))==1)
    {
        q = (LinkList)malloc(sizeof(LNode));
        if(!q)
            return OVERFLOW;  //内存不足
        q->data = x;
        q->next = NULL;
        p->next = q;
        p = p->next;
        (*L)->data++;
    }
    return OK;
}

//将当前表保存到文件
status SaveList(LinkList L)
{
    if(!L)
        return INFEASTABLE;  //线性链表未创建
    FILE *fp;
	char filename[30];
	printf("input file name: ");
	scanf("%s", filename);

	//写入文件
	if ((fp = fopen(filename, "wb")) == NULL)  //文件打开失败
	{
		printf("File open error\n ");
		return ERROR;
	}
    LinkList p = L->next;
    while(p)
    {
        fwrite(&(p->data), sizeof(ElemType), 1, fp);
        p = p->next;
    }
    fclose(fp);
    return OK;
}

//从文件加载表
status LoadList(LinkList *L)
{
    if(!*L)
        return INFEASTABLE;  //线性链表未创建
    FILE *fp;
	char filename[30];
	printf("input file name: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
    LinkList p, q;
    p = *L;
    q = (LinkList)malloc(sizeof(LNode));
    if(!q)
        return OVERFLOW;  //内存不足
    while (fread(&(q->data), sizeof(ElemType), 1, fp))
    {
        q->next = NULL;
        p->next = q;
        p = p->next;
        (*L)->data++;
        q = (LinkList)malloc(sizeof(LNode));
        if(!q)
            return OVERFLOW;  //内存不足
    }
    fclose(fp);
    return OK;
}