#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 50
#define MIN_NUM 1

typedef struct {
  int key;
} NodeData;

typedef struct treeNode {
  NodeData data;
  struct treeNode *left, *right, *parent;
} TreeNode;

typedef struct {
  TreeNode *root;
} BinaryTree;

// BST Construction

TreeNode* newTreeNode(int i) {
  TreeNode *p = (TreeNode *) malloc(sizeof(TreeNode));
  p->data.key = i;
  p->left = p->right = p->parent = NULL;
  return p;
}

TreeNode* insert(TreeNode *node, int i) {
  if (node == NULL)
  {
    return newTreeNode(i);
  }
  else
  {
    if (i <= node->data.key)
    {
      node->left = insert(node->left, i);
      node->left->parent = node;
    }
    else
    {
      node->right = insert(node->right, i);
      node->right->parent = node;
    }
    return node;
  }
}

// BST Traversal

void visit(TreeNode* node) {
  printf("%d ", node->data.key);
}

void preOrder(TreeNode* node) {
  if (node != NULL) {
    visit(node);
    preOrder(node->left);
    preOrder(node->right);
  }
}

void inOrder(TreeNode* node) {
  if (node != NULL) {
    inOrder(node->left);
    visit(node);
    inOrder(node->right);

  }
}

void postOrder(TreeNode* node) {
  if (node != NULL) {
    postOrder(node->left);
    postOrder(node->right);
    visit(node);
  }
}

// BST Successor Functions

TreeNode* minValue(TreeNode* node) {
  TreeNode* n = node;
  while(n->left != NULL)
    n = n->left;
  return n;
}

TreeNode* inOrderSuccessor(TreeNode* node) {
  if (node == NULL) return NULL;
  if (node->right)
    return minValue(node->right);
 
  TreeNode *p = node->parent;
  while (p != NULL && node == p->right)
  {
    node = p;
    p = node->parent;
  }
  return p; 
}

TreeNode* preOrderSuccessor(TreeNode* node) {
  if (node == NULL) return NULL;
  if (node->left) return node->left;
  else if (node->right) return node->right;
  else // Node is a leaf
  {
    TreeNode *p = node->parent;
    while (p != NULL && p->right == NULL)
    {
      node = p;
      p = node->parent;
    }
    return p->right;
  }
}

TreeNode* postOrderSuccessor(TreeNode* node) {
  if (node == NULL || node->parent == NULL) return NULL; // Node does not exist or node is root
  TreeNode *p = node->parent;
  if (node == p->right) return p; // Node is right child
  else // Node is left child
  {
    if (p->right) return minValue(p->right);
    else return p;
  }
}

int main()
{
  BinaryTree bst;
  bst.root = NULL;
    
  srand((unsigned)time(NULL));

  bst.root = insert(bst.root, 13);
  bst.root = insert(bst.root, 3);
  bst.root = insert(bst.root, 4);
  bst.root = insert(bst.root, 12);
  bst.root = insert(bst.root, 14);
  bst.root = insert(bst.root, 10);
  bst.root = insert(bst.root, 5);
  bst.root = insert(bst.root, 1);
  bst.root = insert(bst.root, 8);
  bst.root = insert(bst.root, 2);
  bst.root = insert(bst.root, 7);
  bst.root = insert(bst.root, 9);
  bst.root = insert(bst.root, 11);
  bst.root = insert(bst.root, 6);
  bst.root = insert(bst.root, 18);
     
  printf("\nPre-order: ");
  preOrder(bst.root);

  printf("\nIn-order: ");
  inOrder(bst.root);

  printf("\nPost-order: ");
  postOrder(bst.root);

  return 0;
}