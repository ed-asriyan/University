#ifndef __BINARYTREE_H_DEF__
#define __BINARYTREE_H_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object.h"

typedef struct BSTNode {
    Object* data;

    struct BSTNode *left;
    struct BSTNode *right;

} BSTNode;

BSTNode* FindMin(BSTNode*);
BSTNode* FindMax(BSTNode*);
BSTNode* Insert(BSTNode*, Object*);
BSTNode* Delete(BSTNode*, Object*);
BSTNode* Find(BSTNode*, char*);
void ClearTree(BSTNode*);

void PrintObject(BSTNode*, FILE*);
void PrintInorder(BSTNode*, FILE*);
void PrintPreorder(BSTNode*, FILE*);
void PrintPostorder(BSTNode*, FILE*);

#endif // __BINARYTREE_H_DEF__