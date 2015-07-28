#include <stdio.h>

struct Node
{
    Node* left;
    Node* right;
    Node* parent;
    int value;
};

struct Tree
{
    Node* root;
};


int CountAllNode(Tree* tree, Node* node)
{
    if (!tree || !node)
        return 0;

    int left = CountAllNode(tree, node->left);
    int right = CountAllNode(tree, node->right);

    return left + right + 1;
}

void CreateNode(Tree* tree, Node* node, int num)
{
    if (!tree || !node || num < 1)
        return;

    node->left = new Node();
    node->right = new Node();
    node->left->parent = node;
    node->right->parent = node;

    CreateNode(tree, node->left, num - 2);
}

int main()
{
    Tree tree;
    tree.root = new Node();
    
    CreateNode(&tree, tree.root, 10);
    int num = CountAllNode(&tree, tree.root);
    
    printf("NodeNum = %d\n", num);
    getchar();
}