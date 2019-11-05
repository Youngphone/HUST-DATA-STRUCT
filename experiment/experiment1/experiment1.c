/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define NOTFOUND -3

typedef int status; 
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType *elem;
	int length;
	int listsize;
}SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList **L);
status DestroyList(SqList **L);
status ClearList(SqList *L);
status ListEmpty(SqList *L);
int ListLength(SqList *L);
status GetElem(SqList *L,int i,ElemType* e);
status LocateElem(SqList *L,ElemType e); 
status PriorElem(SqList *L,ElemType cur,ElemType* pre_e);
status NextElem(SqList *L,ElemType cur,ElemType* next_e);
status ListInsert(SqList *L,int i,ElemType e);
status ListDelete(SqList *L,int i,ElemType *e);
status ListTrabverse(SqList *L);
/*--------------------------------------------*/
status InputData(SqList *L);  // 手动输入数据
status SaveList(SqList *L);  // 保存数据到文件
status LoadList(SqList *L);  // 从文件加载数据
int main(void)
{
    int list;
    printf("输入表的个数: \n");
    scanf("%d",&list);
    while (list<=0)
    {
        printf("输入值不合法，请重新输入: \n");
        scanf("%d",&list);
    }
    
    SqList *L[list];  //创建一个结构指针数组
    int b;
    for(b = 0; b<list; b++)
        L[b]=NULL;
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
        switch(op)
        {
	        case 1:  //创建一个空的线性表
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        if(InitList(&L[j-1])==OK) 
                    printf("线性表创建成功！\n");
                else if(InitList(&L[j-1])==ERROR)
                    printf("线性表已存在，请勿重复创建! \n");
		        else 
                    printf("线性表创建失败！\n");
                printf("按Enter键继续");
		        getchar();
                getchar();
		        break;
	        case 2:  //销毁线性表
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
                if(DestroyList(&L[j-1])==OK) 
                    printf("线性表销毁成功！\n");
		        else 
                    printf("线性表未创建，销毁失败！\n");
                printf("按Enter键继续 ");
		        getchar();
                getchar();
		        break;
	        case 3:  //将线性表重置为空表
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        if (ClearList(L[j-1]) == OK)
				    printf("线性表清空成功！\n");
			    else
				    printf("线性表未创建，清空失败！\n");
			    printf("按Enter键继续");     
		        getchar();
                getchar();
		        break;
	        case 4:  // 判断线性表是否为空
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
			    if (ListEmpty(L[j-1]) == INFEASTABLE)
				    printf("线性表未创建！\n");
			    else if (ListEmpty(L[j-1]) == TRUE)
				    printf("线性表不为空！\n");
			    else
				    printf("线性表为空！\n");
			    printf("按Enter键继续");     
		        getchar();
                getchar();
		        break;
	        case 5:  //返回线性表L中数据元素的个数
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        if(ListLength(L[j-1])==INFEASTABLE)
                    printf("线性表未创建! \n");
                else
                {
                    printf("线性表的长度为%d\n",ListLength(L[j-1]));
                }
                printf("按Enter键继续");     
		        getchar();
                getchar();
		        break;
	        case 6:  //用e返回L中第i个数据元素的值
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        printf("请输入要取得线性表中的第几个元素(i)： ");
			    scanf("%d", &i);
                
                a = GetElem(L[j-1],i,&e);
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        printf("输入线性表中的一个数: ");
			    scanf("%d", &e);
                a = LocateElem(L[j-1],e);
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        printf("输入线性表中的一个数: ");
			    scanf("%d", &e);
			    a = PriorElem(L[j-1], e, &pre_e); // a表示函数返回值
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        printf("输入线性表中的一个数: ");
			    scanf("%d", &e);
			    a = NextElem(L[j-1], e, &next_e); // a表示函数返回值
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        printf("输入插入的位置i（从1开始计数）\n");
			    scanf("%d", &i);
			    printf("输入插入的值e\n");
			    scanf("%d", &e);
			    a = ListInsert(L[j-1], i, e);
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
		        printf("输入删除的位置i（从1开始计数）\n");
			    scanf("%d", &i);
			    a = ListDelete(L[j-1], i, &e);
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
                a = ListTrabverse(L[j-1]);   
		        if(a==INFEASTABLE) 
                    printf("线性表未创建！\n");
                else if(a==ERROR)
                    printf("线性表为空表! \n");
                printf("按Enter键继续");
		        getchar();
                getchar();
		        break;
            case 13:  //手动输入数据
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
                if(InputData(L[j-1])==INFEASTABLE)
                    printf("线性表未创建! \n");
                printf("按Enter键继续");
                getchar();
                getchar();
                break;
            case 14:  //将当前表保存到文件
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
                a = SaveList(L[j-1]);
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
                printf("输入表的序号[1~%d]: \n",list);
                scanf("%d",&j);
                while(j<=0||j>list)
                {
                    printf("表的序号不合法,请重新输入: \n");
                    scanf("%d",&j);
                }
                a = LoadList(L[j-1]);
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
	    }//end of switch
  }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
//创建一个空的线性表

status InitList(SqList **L)
{
    if(*L)
        return ERROR;
    *L=(SqList*)malloc(sizeof(SqList));
    if(!*L)
        return OVERFLOW;  //内存不足，空间分配失败
	(*L)->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!(*L)->elem) 
        return OVERFLOW;  //内存不足，空间分配失败
    (*L)->length=0;
    (*L)->listsize=LIST_INIT_SIZE;
	return OK;
}
//销毁线性表
status DestroyList(SqList **L)
{
    if(!*L)
        return INFEASTABLE;
    if (!(*L)->elem)
        return INFEASTABLE;
    (*L)->listsize = 0;
    (*L)->length = 0;
    free((*L)->elem);
    free(*L);
    *L=NULL;
    return OK;
}
//将线性表重置为空表
status ClearList(SqList *L)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    L->listsize = 0;
    L->length = 0;
    return OK;
}
//判定线性表是否为空表
status ListEmpty(SqList *L)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    if (L->length)
        return TRUE;
    else
        return FALSE;
}
//返回线性表L中数据元素的个数
int ListLength(SqList *L)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    return L->length;
}
//用e返回L中第i个数据元素的值
status GetElem(SqList *L,int i,ElemType *e)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    if(i<0||i>=L->length)  //i值不合法
        return ERROR;
    *e = L->elem[i-1];
    return OK;
}
//输入一个元素值返回它在表中的位置
status LocateElem(SqList *L,ElemType e)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    int i;
    for (int i = 1; i <= L->length; i++)
	{
		if (e == L->elem[i - 1])
		{
			return i; //返回第位置i  i从1开始
		}
	}
    return ERROR;
}
//用pre_e返回线性表中某个元素的前驱
status PriorElem(SqList *L,ElemType cur,ElemType *pre_e)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    int i;
    for(i=0;i<L->length;i++)
    {
        if(L->elem[i]==cur)
            break;
    }
    if(i==L->length)
        return NOTFOUND;
    
    else if(i==0)  //cur为第一个元素，无前驱
    {
        return ERROR;
    }
    else
    {
        *pre_e = *(L->elem + (i-1));
        return OK;
    }
}
//用next_e返回线性表中某个元素的后继
status NextElem(SqList *L,ElemType cur,ElemType *next_e)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    int i;
    for(i=0;i<L->length;i++)
    {
        if(L->elem[i]==cur)
            break;
    }
    if(i==L->length)
        return NOTFOUND;
    else if(i==(L->length-1))  //cur为最后一个元素，无后继
        return ERROR;
    else
    {
        *next_e = *(L->elem + (i+1));
		return OK;
    }
}
//在L的第i个位置之前插入新的数据元素e
status ListInsert(SqList *L,int i,ElemType e)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    if(i<1||i>L->length+1)  //插入位置不合法
        return ERROR;
    if(L->length>=L->listsize)  //空间不足，重新分配
    {
        L->elem = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!L->elem) 
            return OVERFLOW;
        L->listsize += LISTINCREMENT;
    }
    ElemType *q = &(L->elem[i - 1]); //q为要插入的位置

	for (ElemType *p = &(L->elem[L->length - 1]); p >= q; --p)  // 插入位置及之后的元素右移
		*(p + 1) = *p;
	*q = e;
	L->length++;
	return OK;
}
//删除L的第i个数据元素，用e返回其值
status ListDelete(SqList *L,int i,ElemType *e)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    if(i<1||i>L->length)  //i值不合法
        return ERROR;
    ElemType *p = &(L->elem[i-1]);  //p为要删除的元素的位置
    *e = *p;
    ElemType *q = &(L->elem[L->length-1]);
    for(p++; p<=q; p++)
    {
        *(p-1) = *p;  //删除元素位置之后的元素左移
    }
    L->length--;
    return OK;
}
//遍历线性表
status ListTrabverse(SqList *L)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    if(L->length==0)
        return ERROR;  //线性表为空表
    int i;
    printf("\n-----------all elements -----------------------\n");
    for(i=0; i<L->length; i++) 
        printf("%d\n",L->elem[i]);
    printf("\n------------------ end ------------------------\n");
    return OK;
}
//手动输入数据
status InputData(SqList *L)
{
    if(!L)
        return INFEASTABLE;
    if (!L->elem)
        return INFEASTABLE;
    int x;
    printf("请输入若干整数以任意一个字母结束: \n");
    while((scanf("%d",&x))==1)
    {
        if(L->length>=L->listsize)  //空间不足，重新分配
        {
            L->elem = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
            if(!L->elem) 
            return OVERFLOW;
            L->listsize += LISTINCREMENT;
        }
        L->elem[L->length++] = x;  //写入数据
    }
    return OK;
}
//将当前表保存到文件
status SaveList(SqList *L)
{
    if(!L)
        return INFEASTABLE;
	if (!L->elem)
		return INFEASTABLE;

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
	fwrite(L->elem, sizeof(ElemType), L->length, fp);
	fclose(fp);
	return OK;
}
//从文件加载表
status LoadList(SqList *L)
{
    if(!L)
        return INFEASTABLE;
	if (!L->elem)
		return INFEASTABLE;

	//读取文件
	FILE *fp;
	char filename[30];
	printf("input file name: ");
	scanf("%s", filename);
	L->length = 0;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
	while (fread(&(L->elem[L->length]), sizeof(ElemType), 1, fp))
		L->length++;
	fclose(fp);
	return OK;
}
