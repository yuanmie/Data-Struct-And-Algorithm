/*
二叉搜索树，好像很久之前写的。

*/

#include <iostream>
#include <cstdio>

struct TreeNode
{
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
};

typedef struct TreeNode BSTNode;

BSTNode* createNode(int value)
{
	BSTNode* pnode = new BSTNode;
	pnode->value = value;
	pnode->left = NULL;
	pnode->right = NULL;
	pnode->parent = NULL;

	return pnode;
}

BSTNode* Tree_Search(BSTNode* root, int key)
{
	if (root == NULL || root->value == key)
		return root;
	if (key > root->value){
		return Tree_Search(root->right, key);
	}else{
		return Tree_Search(root->left, key);
	}
}

BSTNode* Iterative_Tree_Search(BSTNode* root, int key)
{
	BSTNode* node = root;
	while (node != NULL && node->value != key)
	{
		if (key < node->value){
			node = node->left;
		}else{
			node = node->right;
		}
	}
	return node;
}

BSTNode* Tree_Minimum(BSTNode* node){
	while (node->left != NULL){
		node = node->left;
	}
	return node;
}

BSTNode* Tree_Maximum(BSTNode* node){
	while (node->right != NULL){
		node = node->right;
	}
	return node;
}

BSTNode* Tree_Insert(BSTNode** root, int key){
	BSTNode* node = createNode(key);
	BSTNode* rootNode = *root;
	BSTNode* parentNode = NULL;
	while (rootNode != NULL){
		parentNode = rootNode;
		if (key < rootNode->value){
				rootNode = rootNode->left;
		}else{
				rootNode = rootNode->right;
		}
	}

	node->parent = parentNode;
	if (parentNode == NULL){
		*root = node;
	}else if (key < parentNode->value){
		parentNode->left = node;
	}else{
		parentNode->right = node;
	}

	return *root;
}

//把u替换为v
void Transplant(BSTNode** root, BSTNode* u, BSTNode* v)
{
	if (u->parent == NULL){
		*root = v;
	}else if (u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	if (v != NULL)
		v->parent = u->parent;
}

BSTNode* Tree_Delete(BSTNode** root, int key)
{
	BSTNode* deleteNode = Iterative_Tree_Search(*root, key);
	if (deleteNode != NULL)
	{
		if (deleteNode->left == NULL)
			Transplant(root, deleteNode, deleteNode->right);
		else if (deleteNode->right == NULL)
			Transplant(root, deleteNode, deleteNode->left);
		else
		{
			BSTNode* y = Tree_Minimum(deleteNode->right);
			if (y->parent != deleteNode)
			{
				Transplant(root, y, y->right);
				y->right = deleteNode->right;
				y->right->parent = y;
			}
			Transplant(root, deleteNode, y);
			y->left = deleteNode->left;
			y->left->parent = y;
		}

		delete deleteNode;
	}

	return *root;
}

void Tree_Order(BSTNode* root)
{
	if(root == NULL) {return;}

	Tree_Order(root->left);
	printf("\t%d", root->value);
	Tree_Order(root->right);
}

void releaseTree(BSTNode* node){
	if(node == NULL) return;
	releaseTree(node->left);
	releaseTree(node->right);
	delete node;
}

int main()
{
	BSTNode* root = createNode(10);
	Tree_Insert(&root,5);
	Tree_Insert(&root, 20);
	Tree_Insert(&root, 15);
	Tree_Insert(&root, 30);
	Tree_Insert(&root, 25);
	Tree_Insert(&root, 35);
	Tree_Order(root);

	Tree_Delete(&root, 20);
	printf("\nafter delete 20:\n");
	Tree_Order(root);
	releaseTree(root);
	
	return 0;
}
