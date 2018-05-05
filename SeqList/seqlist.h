/*************************************************************************
	> File Name: seqlist.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 09 Mar 2018 07:11:05 AM PST
 ************************************************************************/
#pragma once

#include<stddef.h>

#define seqlistMaxNum 10

typedef struct SeqList 
{
	int data[seqlistMaxNum];
	size_t size;
}SeqList;

SeqList seqlist;

void seqlistInit(SeqList *seqlist);

void ifFull(SeqList *seqlist);
void ifEmpty(SeqList *seqlist);
void seqlistPrint(SeqList *seqlist);

void seqlistPushBack(SeqList *seqlist,int data);
void seqlistPopBack(SeqList *seqlist);

void seqlistPushFront(SeqList *seqlist,int data);
void seqlistPopFront(SeqList *seqlist);

void seqlistInsert(SeqList *seqlist,int pos,int data);
void seqlistErase(SeqList *seqlist,int pos);

void seqlistSet(SeqList *seqlist,int pos,int data);
void seqlistGet(SeqList *seqlist,int pos);

void seqlistFind(SeqList *seqlist,int data);

void seqlistRemove(SeqList *seqlist,int to_delete);
void seqlistRemoveAll(SeqList *seqlist,int to_delete);

size_t seqlistSize(SeqList *seqlist);

void seqlistBubbleSort(SeqList *seqlist);

