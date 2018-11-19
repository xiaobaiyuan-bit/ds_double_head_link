#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//双向带头循环  链表(如果要改变链表的头指针指向，就要传入二级指针)
typedef int DataType;

typedef struct DListNode
{
	DataType data;
	struct DListNode *prev;
	struct DListNode *next;

}DListNode;

//初始化   销毁   清空链表   插入节点   删除节点

void DListInit(DListNode **ppHead, DataType data)
{
	assert(ppHead);
	DListNode *pHead = (DListNode *)malloc(sizeof(DListNode));
	pHead->data = data;
	assert(pHead != NULL);
	//初始化时，创建一个头结点，有时候会让头结点的data存一些有效信息（长度）
	pHead->next = pHead;//指向自己
	pHead->prev = pHead;//指向自己

	*ppHead = pHead;
}

// 销毁链表   但是要保留头结点
void DListClear(DListNode *pHead)
{
	DListNode *cur = pHead->next;
	DListNode *next = NULL;
	while (cur != pHead)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	pHead->next = pHead;
	pHead->prev = pHead;
}

// 销毁链表   不保留头结点
void DListDestroy(DListNode **ppHead)
{
	assert(ppHead);
	DListClear(*ppHead);
	free(*ppHead);
	*ppHead = NULL;
}

DListNode*  DListFind(DListNode *pHead, DataType data)
{
	assert(pHead);
	DListNode *pcur = pHead->next;
	while (pcur != pHead)
	{
		if (pcur->data == data)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	printf("have no data!!!\n");
	return NULL;
}

//插入(pos前面插入)
void DListInsert(DListNode *pHead, DListNode *pos, DataType data)
{
	assert(pHead);
	assert(pos);
	DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
	newNode->data = data;

	newNode->prev = pos->prev;
	newNode->next = pos;
	pos->prev->next = newNode;
	pos->prev = newNode;
}


//删除（删除pos节点）
void DListErase(DListNode *pHead, DListNode *pos)
{
	assert(pos != pHead);
	assert(pos != NULL);

	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}


void DListPrint(DListNode *pHead)
{
	assert(pHead);
	DListNode *cur = pHead;
	while (cur->next != pHead)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("%d->", cur->data);
	printf("%d\n", cur->next->data);
}


void Test()
{
	DListNode *pHead = NULL;
	DListInit(&pHead, 0);

	DListInsert(pHead, pHead, 1);
	DListInsert(pHead, pHead, 2);
	DListInsert(pHead, pHead, 3);
	DListInsert(pHead, pHead, 4);
	DListInsert(pHead, pHead, 5);


	DListErase(pHead, DListFind(pHead, 1));//头删
	DListErase(pHead, DListFind(pHead, 2));
	DListErase(pHead, DListFind(pHead, 3));//任意位置删除
	DListErase(pHead, DListFind(pHead, 4));
	DListErase(pHead, DListFind(pHead, 5));//尾删

	DListPrint(pHead);

	DListDestroy(&pHead);
}