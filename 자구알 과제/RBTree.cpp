#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define MAX_WIDTH   135
#define MAX_HEIGHT  45
#define SLIDE_TIME  100

enum Color
{
    RED = 207,
    BLACK = 15,
    BG = 240,
};

struct Node
{
    Color   color;
    int     key;
    Node*   parent;
    Node*   left;
    Node*   right;
};

struct Tree
{
    Node* root;
    Node* nil;
};

Node*   CreateNewNode(int key);
void    Insert(Tree* tree, Node* newNode);
void    InsertFixup(Tree* tree, Node* fixupNode);
void    LeftRotate(Tree* tree, Node* node);
void    RightRotate(Tree* tree, Node* node);

void    Delete(Tree* tree, Node* node);
void    DeleteFixup(Tree* tree, Node* fixupNode);
void    Transplant(Tree* tree, Node* oldNode, Node* plantNode);
Node*   TreeMinimum(Tree* tree, Node* node);

void    PrintTree(Tree* tree);
void    PrintNode(Tree* tree, Node* node, COORD pos);
Node*   SearchNode(Tree* tree, int key);

void    Init(Tree* tree);
void    Release(Tree* tree);
void    DeleteTree(Tree* tree, Node* node);
int     GetKey();
void    InitDialog();
void    Gotoxy(int x, int y);
void    Setcolor(int color);



int main()
{
    Tree tree;
    Init(&tree);

    bool loop = true;
    while (loop)
    {
        PrintTree(&tree);
        InitDialog();
        int key = 0;
        int input = _getch();
        switch (input)
        {
        case 'i':
            key = GetKey();
            Insert(&tree, CreateNewNode(key));
            break;
        case 'd':
            key = GetKey();
            Delete(&tree, SearchNode(&tree, key));
            break;
        case 'q':
            loop = false;
            break;
        }
    }
    Release(&tree);
}



Node* CreateNewNode(int key)
{
    Node* newNode = new Node();
    newNode->key = key;
    return newNode;
}

void Insert(Tree* tree, Node* newNode)
{
    if (!tree || !newNode)
        return;

    Node* parentNode = tree->nil;
    Node* curNode = tree->root;
    while (curNode != tree->nil)
    {
        parentNode = curNode;
        if (newNode->key < curNode->key)
            curNode = curNode->left;
        else
            curNode = curNode->right;
    }
    newNode->parent = parentNode;

    if (parentNode == tree->nil)
        tree->root = newNode;
    else if (newNode->key < parentNode->key)
        parentNode->left = newNode;
    else
        parentNode->right = newNode;

    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->color = RED;

    PrintTree(tree);
    Beep(512, SLIDE_TIME);
    
    InsertFixup(tree, newNode);
}

void InsertFixup(Tree* tree, Node* fixupNode)
{
    while (fixupNode->parent->color == RED)
    {
        if (fixupNode->parent == fixupNode->parent->parent->left)
        {
            Node* uncleNode = fixupNode->parent->parent->right;
            if (uncleNode->color == RED)
            {
                fixupNode->parent->color = BLACK;
                uncleNode->color = BLACK;
                fixupNode->parent->parent->color = RED;
                fixupNode = fixupNode->parent->parent;
                PrintTree(tree);
                Beep(512, SLIDE_TIME);
            }
            else
            {
                if (fixupNode == fixupNode->parent->right)
                {
                    fixupNode = fixupNode->parent;
                    LeftRotate(tree, fixupNode);
                }
                fixupNode->parent->color = BLACK;
                fixupNode->parent->parent->color = RED;
                RightRotate(tree, fixupNode->parent->parent);
            }
        }
        else
        {
            Node* uncleNode = fixupNode->parent->parent->left;
            if (uncleNode->color == RED)
            {
                fixupNode->parent->color = BLACK;
                uncleNode->color = BLACK;
                fixupNode->parent->parent->color = RED;
                fixupNode = fixupNode->parent->parent;
                PrintTree(tree);
                Beep(512, SLIDE_TIME);
            }
            else
            {
                if (fixupNode == fixupNode->parent->left)
                {
                    fixupNode = fixupNode->parent;
                    RightRotate(tree, fixupNode);
                }
                fixupNode->parent->color = BLACK;
                fixupNode->parent->parent->color = RED;
                LeftRotate(tree, fixupNode->parent->parent);
            }
        }
    }
    if (tree->root->color == RED)
    {
        tree->root->color = BLACK;
        PrintTree(tree);
        Beep(512, SLIDE_TIME);
    }
}

void LeftRotate(Tree* tree, Node* node)
{
    if (!tree || node == tree->nil)
        return;

    Node* target = node->right;
    node->right = target->left;
    if (target->left)
        target->left->parent = node;

    target->parent = node->parent;
    if (node->parent == tree->nil)
        tree->root = target;
    else if (node == node->parent->left)
        node->parent->left = target;
    else
        node->parent->right = target;

    target->left = node;
    node->parent = target;
    PrintTree(tree);
    Beep(512, SLIDE_TIME);
}

void RightRotate(Tree* tree, Node* node)
{
    if (!tree || node == tree->nil)
        return;

    Node* target = node->left;
    node->left = target->right;
    if (target->right)
        target->right->parent = node;

    target->parent = node->parent;
    if (node->parent == tree->nil)
        tree->root = target;
    else if (node == node->parent->right)
        node->parent->right = target;
    else
        node->parent->left = target;

    target->right = node;
    node->parent = target;
    PrintTree(tree);
    Beep(512, SLIDE_TIME);
}



void Delete(Tree* tree, Node* node)
{
    if (!tree || node == tree->nil)
        return;

    Color erasedColor = node->color;
    Node* fixupNode = tree->nil;
    Node* successor = tree->nil;

    if (node->left == tree->nil)
    {
        fixupNode = node->right;
        Transplant(tree, node, node->right);
    }
    else if (node->right == tree->nil)
    {
        fixupNode = node->left;
        Transplant(tree, node, node->left);
    }
    else
    {
        successor = TreeMinimum(tree, node->right);
        erasedColor = successor->color;
        fixupNode = successor->right;
        if (successor->parent == node)
            fixupNode->parent = successor;
        else
        {
            Transplant(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        Transplant(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }
    if (erasedColor == BLACK && fixupNode != tree->nil)
        DeleteFixup(tree, fixupNode);

    delete node;
}

void DeleteFixup(Tree* tree, Node* fixupNode)
{
    Node* sibling = tree->nil;

    while (fixupNode != tree->root && fixupNode->color == BLACK)
    {
        if (fixupNode == fixupNode->parent->left)
        {
            sibling = fixupNode->parent->right;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                fixupNode->parent->color = RED;
                LeftRotate(tree, fixupNode->parent);
                sibling = fixupNode->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                fixupNode = fixupNode->parent;
                PrintTree(tree);
                Beep(512, SLIDE_TIME);
            }
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    RightRotate(tree, sibling);
                    sibling = fixupNode->parent->right;
                }
                sibling->color = fixupNode->parent->color;
                fixupNode->parent->color = BLACK;
                sibling->right->color = BLACK;
                LeftRotate(tree, fixupNode->parent);
                fixupNode = tree->root;
            }
        }
        else
        {
            sibling = fixupNode->parent->left;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                fixupNode->parent->color = RED;
                RightRotate(tree, fixupNode->parent);
                sibling = fixupNode->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK)
            {
                sibling->color = RED;
                fixupNode = fixupNode->parent;
                PrintTree(tree);
                Beep(512, SLIDE_TIME);
            }
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    LeftRotate(tree, sibling);
                    sibling = fixupNode->parent->left;
                }
                sibling->color = fixupNode->parent->color;
                fixupNode->parent->color = BLACK;
                sibling->left->color = BLACK;
                RightRotate(tree, fixupNode->parent);
                fixupNode = tree->root;
            }
        }
    }
    fixupNode->color = BLACK;
}

void Transplant(Tree* tree, Node* oldNode, Node* plantNode)
{
    if (oldNode->parent == tree->nil)
        tree->root = plantNode;
    else if (oldNode == oldNode->parent->left)
        oldNode->parent->left = plantNode;
    else
        oldNode->parent->right = plantNode;
    
    if (plantNode != tree->nil)
        plantNode->parent = oldNode->parent;

    PrintTree(tree);
    Beep(512, SLIDE_TIME);
}

Node* TreeMinimum(Tree* tree, Node* node)
{
    if (node->left == tree->nil)
        return node;
    return TreeMinimum(tree, node->left);
}



void PrintTree(Tree* tree)
{
    if (!tree)
        return;

    system("cls");
    COORD pos = { MAX_WIDTH / 2, 1 };
    PrintNode(tree, tree->root, pos);
}

void PrintNode(Tree* tree, Node* node, COORD pos)
{
    if (!tree || node == tree->nil)
        return;

    int space = MAX_WIDTH / (int)(pow(2.0f, pos.Y + 1));
    PrintNode(tree, node->left, { pos.X - space, pos.Y + 1 });
    PrintNode(tree, node->right, { pos.X + space, pos.Y + 1 });

    Setcolor(node->color);
    Gotoxy(pos.X, pos.Y * 5);
    printf("%2d", node->key);
    Setcolor(BG);
}

Node* SearchNode(Tree* tree, int key)
{
    Node* parentNode = tree->nil;
    Node* curNode = tree->root;
    while (curNode != tree->nil)
    {
        if (curNode->key == key)
            return curNode;

        parentNode = curNode;
        if (key < curNode->key)
            curNode = curNode->left;
        else
            curNode = curNode->right;
    }
    return tree->nil;
}



void Init(Tree* tree)
{
    Setcolor(BG);
    system("mode con: lines=45 cols=135");
    tree->nil = new Node();
    tree->nil->color = BLACK;
    tree->nil->key = 0;
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->root = tree->nil;
    PrintTree(tree);
}

void Release(Tree* tree)
{
    DeleteTree(tree, tree->root);
    delete tree->nil;
}

void DeleteTree(Tree* tree, Node* node)
{
    if (node == tree->nil)
        return;
    DeleteTree(tree, node->left);
    DeleteTree(tree, node->right);
    Delete(tree, node);
}

int GetKey()
{
    Gotoxy(1, MAX_HEIGHT - 2);
    printf(":> ");

    int key = 0;
    scanf_s("%d", &key);
    while (getchar() != '\n');
    return key;
}

void InitDialog()
{
    Gotoxy(1, MAX_HEIGHT - 3);
    printf("[ 삽입 : I \t 삭제 : D \t 종료 : Q ]\n");
}

void Gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Setcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
