#pragma once

#include <stddef.h>

typedef enum Flag {
  CHILD,
  THREAD,
} Flag;

typedef char ThreadType;

typedef struct ThreadNode {
  ThreadType data;
  struct ThreadNode* left;
  struct ThreadNode* right;
  // 引入两个 flag 来分别表示左右指针指向的是子树还是线索.
  Flag lflag;
  Flag rflag;
} ThreadNode;

ThreadNode* ThreadTreeCreate(ThreadType array[], size_t size,
          ThreadType invalid);

void PreThreading(ThreadNode* root);

void PreOrderByThreading(ThreadNode* root);

void InThreading(ThreadNode* root);

void InOrderByThreading(ThreadNode* root);

void PostThreading(ThreadNode* root);

void PostOrderByThreading(ThreadNode* root);

typedef struct TreeNode {
  char data;
  struct TreeNode* left;
  struct TreeNode* right;
  struct TreeNode* prev;
  struct TreeNode* next;
} TreeNode;
