#include "BinaryTree.h"

BSTNode* FindMin(BSTNode* node) {
    // There is no element in the tree
    if (node == NULL) {
        return NULL;
    }

    // Go to the left sub tree to find the min element
    if (node->left) {
        return FindMin(node->left);
    }

    return node;
}

BSTNode* FindMax(BSTNode* node) {
    // There is no element in the tree
    if (node == NULL) {
        return NULL;
    }

    // Go to the right sub tree to find the max element
    if (node->right) {
        FindMax(node->right);
    }

    return node;
}

void FreeObject(BSTNode* node) {
    free(node->data->OBJECT_FEATURE_2);
    free(node->data->OBJECT_FEATURE_4);
    free(node->data->OBJECT_FEATURE_5);
    free(node->data->OBJECT_FEATURE_6);
    free(node->data);
    free(node);
}

void ClearTree(BSTNode* node) {
    if (node == NULL){
        return;
    } else if (node->left != NULL) {
        ClearTree(node->left);
    } else if (node->right != NULL) {
        ClearTree(node->right);
    }

    FreeObject(node);

    return;
}

BSTNode* Insert(BSTNode* node, Object* data) {
    if (node == NULL) {
        BSTNode* temp = (BSTNode*) malloc(sizeof(BSTNode));
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }

    if (strcmp(data->OBJECT_FEATURE_2, node->data->OBJECT_FEATURE_2) > 0) {
        node->right = Insert(node->right, data);
    } else if (strcmp(data->OBJECT_FEATURE_2, node->data->OBJECT_FEATURE_2) < 0) {
        node->left = Insert(node->left, data);
    }

    // Else there is nothing to do as the data is already in the tree.
    return node;
}

BSTNode* Delete(BSTNode* node, Object* data) {
    BSTNode* temp;

    if (node == NULL) {
        fprintf(stdout, "Element Not Found\n");
    } else if (strcmp(data->OBJECT_FEATURE_2, node->data->OBJECT_FEATURE_2) < 0) {
        node->left = Delete(node->left, data);
    } else if (strcmp(data->OBJECT_FEATURE_2, node->data->OBJECT_FEATURE_2) > 0) {
        node->right = Delete(node->right, data);
    } else {
        /* Now We can delete this node and replace with either minimum element 
           in the right sub tree or maximum element in the left subtree */
        if (node->right && node->left) {
            /* Here we will replace with minimum element in the right sub tree */
            temp = FindMin(node->right);
            node->data = temp->data; 
            /* As we replaced it with some other node, we have to delete that node */
            node->right = Delete(node->right, temp->data);
        } else {
            /* If there is only one or zero children then we can directly 
               remove it from the tree and connect its parent to its child */
            temp = node;

            if (node->left == NULL) {
                node = node->right;
            } else if (node->right == NULL) {
                node = node->left;
            }

            FreeObject(temp);
        }
    }

    return node;
}

BSTNode* Find(BSTNode* node, char* value) {
    // Element is not found
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(value, node->data->OBJECT_FEATURE_2) > 0) {
        // Search in the right sub tree.
        return Find(node->right, value);
    } else if(strcmp(value, node->data->OBJECT_FEATURE_2) < 0) {
        // Search in the left sub tree.
        return Find(node->left, value);
    } else {
        // Element Found
        return node;
    }
}

void PrintObject(BSTNode* node, FILE* out) {
    fprintf(out, "%d\n", node->data->OBJECT_FEATURE_1);
    fprintf(out, "%s\n", node->data->OBJECT_FEATURE_2);
    fprintf(out, "%d\n", node->data->OBJECT_FEATURE_3);
    fprintf(out, "%s\n", node->data->OBJECT_FEATURE_4);
    fprintf(out, "%s\n", node->data->OBJECT_FEATURE_5);
    fprintf(out, "%s\n", node->data->OBJECT_FEATURE_6);
    fprintf(out, "%lf\n\n", node->data->OBJECT_FEATURE_7);
}

void PrintInorder(BSTNode* node, FILE* out) {
    if (node == NULL) {
        return;
    }

    PrintInorder(node->left, out);
    PrintObject(node, out);
    PrintInorder(node->right, out);
}

void PrintPreorder(BSTNode* node, FILE* out) {
    if (node == NULL) {
        return;
    }

    PrintObject(node, out);
    PrintPreorder(node->left, out);
    PrintPreorder(node->right, out);
}

void PrintPostorder(BSTNode* node, FILE* out) {
    if(node == NULL) {
        return;
    }

    PrintPostorder(node->left, out);
    PrintPostorder(node->right, out);
    PrintObject(node, out);
}