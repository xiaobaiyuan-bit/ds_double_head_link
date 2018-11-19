#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//˫���ͷѭ��  ����(���Ҫ�ı������ͷָ��ָ�򣬾�Ҫ�������ָ��)
typedef int DataType;

typedef struct DListNode
{
	DataType data;
	struct DListNode *prev;
	struct DListNode *next;

}DListNode;

//��ʼ��   ����   �������   ����ڵ�   ɾ���ڵ�

void DListInit(DListNode **ppHead, DataType data)
{
	assert(ppHead);
	DListNode *pHead = (DListNode *)malloc(sizeof(DListNode));
	pHead->data = data;
	assert(pHead != NULL);
	//��ʼ��ʱ������һ��ͷ��㣬��ʱ�����ͷ����data��һЩ��Ч��Ϣ�����ȣ�
	pHead->next = pHead;//ָ���Լ�
	pHead->prev = pHead;//ָ���Լ�

	*ppHead = pHead;
}

// ��������   ����Ҫ����ͷ���
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

// ��������   ������ͷ���
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

//����(posǰ�����)
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


//ɾ����ɾ��pos�ڵ㣩
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


	DListErase(pHead, DListFind(pHead, 1));//ͷɾ
	DListErase(pHead, DListFind(pHead, 2));
	DListErase(pHead, DListFind(pHead, 3));//����λ��ɾ��
	DListErase(pHead, DListFind(pHead, 4));
	DListErase(pHead, DListFind(pHead, 5));//βɾ

	DListPrint(pHead);

	DListDestroy(&pHead);
}