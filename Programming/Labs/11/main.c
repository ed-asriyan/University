#include <stdio.h>

#include "BinaryTree.h"
#include "ParseXML.h"

#define NOT_ENOUGH_ARGUMENTS 0
#define INVALID_ARGUMENT     0

int main(const int argc, const char** argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: NOT_ENOUGH_ARGUMENTS!!!\n");
		return NOT_ENOUGH_ARGUMENTS;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f) {
		fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
		return INVALID_ARGUMENT;
	}

	BSTNode* root = FillTree(f);
	fclose(f);

	FILE* inorder = fopen("inorder.txt", "w");
	PrintInorder(root, inorder);
	fclose(inorder);

	FILE* preorder = fopen("preorder.txt", "w");
	PrintPreorder(root, preorder);
	fclose(preorder);

	FILE* postorder = fopen("postorder.txt", "w");
	PrintPostorder(root, postorder);
	fclose(postorder);

	BSTNode* maximum = FindMax(root);
	PrintObject(maximum, stdout);

	BSTNode* minimum = FindMin(root);
	PrintObject(minimum, stdout);

	char name[6];
	fprintf(stdout, "Enter the name of employee to find: ");
	fscanf(stdin, "%s", name);

	BSTNode* object = Find(root, name);

	if (object == NULL) {
		fprintf(stderr, "Employee not found.\n");
		return 0;
	}

	PrintObject(object, stdout);

	ClearTree(root);

	return 0;
}