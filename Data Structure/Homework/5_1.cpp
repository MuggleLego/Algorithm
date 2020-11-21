//date:2020.11.21
//path:~/Code/DS/5_1.cpp

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct bstNode
{
    int value;
    bstNode *left;
    bstNode *right;
};

struct BST
{
    bstNode *root;
};

bstNode *newNode(int data)
{
    bstNode *n = new bstNode();
    n->value = data;
    n->left = n->right = NULL;
    return n;
}

BST *newTree()
{
    BST *tree = new BST();
    tree->root = NULL;
    return tree;
}

//insert a node into a (sub)bst in a recursive way
bstNode *insertNode(bstNode *node, int target)
{
    if (!node)
        return newNode(target);
    if (target < node->value)
    {
        node->left = insertNode(node->left, target);
    }
    else
    {
        node->right = insertNode(node->right, target);
    }
    return node;
}

void insert(BST *tree, int data)
{
    tree->root = insertNode(tree->root, data);
}

//find a successor of a node in a bst
//default successor is the greatest element in the left subtree
bstNode *successor(bstNode *node)
{
    bstNode *suc;
    if (node->left)
    { //node has a predeccessor
        suc = node->left;
        while (suc->right)
        {
            suc = suc->right;
        }
        return suc;
    }
    if (node->right)
    { //node has a successor
        suc = node->right;
        while (suc->left)
        {
            suc = suc->left;
        }
        return suc;
    }
    return NULL; //node is a leaf in the bst
}

//delete a node in a bst which rooted at node,return the root
bstNode *_delete(bstNode *node, int target)
{
    if (!node)
        return NULL;
    if (target < node->value)
    {
        node->left = _delete(node->left, target);
    }
    else if (target > node->value)
    {
        node->right = _delete(node->right, target);
    }
    else
    {
        bstNode *suc = successor(node);
        if (!suc)
            return NULL; //delete a single node bst
        int tmp = node->value;
        node->value = suc->value;
        if (suc->value < tmp)
        {
            node->left = _delete(node->left, suc->value);
        }
        else
        {
            node->right = _delete(node->right, suc->value);
        }
    }
    return node;
}

void deleteNode(BST *tree, int target)
{
    tree->root = _delete(tree->root, target);
}


//exchange the left right subtree of a node
bstNode *exchangeSubtree(bstNode *node)
{
    bstNode *tmp = node->left;
    node->left = node->right;
    node->right = tmp;
    return node;
}

//make a subtree into a reverse sub bst
bstNode *reverse(bstNode *node)
{
    if (!node)
        return NULL;
    node = exchangeSubtree(node);
    node->left = reverse(node->left);
    node->right = reverse(node->right);
    return node;
}

void reverseBST(BST *tree)
{
    tree->root = reverse(tree->root);
}

//in recursive way
void inorderTravelsal(bstNode *node)
{
    if (!node)
        return;
    inorderTravelsal(node->left);
    printf("%d ", node->value);
    inorderTravelsal(node->right);
}

void inorder(BST *tree)
{
    inorderTravelsal(tree->root);
    printf("\n");
}


//dfs
//an iterarion way to inorder travelsal
void inorderIter(BST *tree)
{
    stack<bstNode *> Stack;
    bstNode *walker = tree->root;
    while (walker)
    {
        Stack.push(walker);
        walker = walker->left;
    }
    while (!Stack.empty())
    {
        walker = Stack.top();
        printf("%d ", walker->value);
        Stack.pop();
        if (walker->right)
        {
            walker = walker->right;
            Stack.push(walker);
            while (walker->left)
            {
                Stack.push(walker->left);
                walker = walker->left;
            }
        }
    }
    printf("\n");
}

bool isBSTNode(bstNode *node)
{
    if (!node)
        return true; //empty tree is bst
    bool flag_r = true;
    bool flag_l = true;
    if (node->left && node->left->value >= node->value)
        flag_l = false;
    if (node->right && node->right->value < node->value)
        flag_r = false;
    return isBSTNode(node->left) && isBSTNode(node->right) && flag_l && flag_r;
}

int isBST(BST *tree)
{
    return isBSTNode(tree->root);
}

bool equivalentNode(bstNode *n1, bstNode *n2)
{
    if (!n1 && !n1)
        return true; //base case
    return (n1->value == n2->value) && equivalentNode(n1->left, n2->left) && equivalentNode(n1->right, n2->right);
}

bool equivalent(BST *T1, BST *T2)
{
    return equivalentNode(T1->root, T2->root);
}

bstNode *copyNode(bstNode *node)
{
    if (!node)
        return NULL;
    bstNode *n = newNode(node->value);
    n->left = copyNode(node->left);
    n->right = copyNode(node->right);
    return n;
}

//return a copy of a bst
BST *copy(BST *tree)
{
    BST *ret = newTree();
    ret->root = copyNode(tree->root);
    return ret;
}

struct listNode
{
    int value;
    listNode *next;
};

struct list
{
    listNode *dummy;
    listNode *rear;
};

listNode *newListNode(int data)
{
    listNode *n = new listNode();
    n->value = data;
    n->next = NULL;
    return n;
}

list *newList()
{
    list *l = new list();
    l->dummy = newListNode(0);
    l->rear = NULL;
    return l;
}

void append(list *l, int data)
{
    listNode *n = newListNode(data);
    if (!l->rear)
    {
        l->dummy->next = n;
        l->rear = n;
        return;
    }
    l->rear->next = n;
    l->rear = n;
}

void printList(list *l)
{
    listNode *walker = l->dummy->next;
    while (walker)
    {
        cout << walker->value << " ";
        walker = walker->next;
    }
    cout << endl;
}

//put all the leaf of a path that contain node into a list
void leaf(list *l, bstNode *node)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        append(l, node->value);
        return;
    }
    leaf(l, node->left);
    leaf(l, node->right);
}

list *leafList(BST *tree)
{
    list *ret = newList();
    leaf(ret, tree->root);
    return ret;
}

int leftIndex(int i)
{
    return ((i + 1) << 1) - 1;
}

int rightIndex(int i)
{
    return (i + 1) << 1;
}

//return a complete bst
BST *arrayToTree(int *a, int size)
{
    BST *tree = newTree();
    if (!size)
    {
        return tree;
    }
    bstNode *array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = newNode(a[i]);
    }
    int i = 0;
    bstNode *walker;
    while (leftIndex(i) < size)
    {
        walker = array[i];
        walker->left = array[leftIndex(i)];
        if (rightIndex(i) < size)
        {
            walker->right = array[rightIndex(i)];
        }
        i++;
    }
    tree->root = *array;
    return tree;
}

//given a complete bst with n nodes
//bsf
int *treeToArray(BST *tree, int n)
{
    if (!n)
        return NULL;
    int *array = new int[n];
    queue<bstNode *> node;
    node.push(tree->root);
    int i = 0;
    while (i < n)
    {
        array[i] = node.front()->value;
        if (leftIndex(i) < n)
        {
            node.push(node.front()->left);
        }
        if (rightIndex(i) < n)
        {
            node.push(node.front()->right);
        }
        node.pop();
        i++;
    }
    return array;
}

int main()
{
    BST *tree = newTree();
    insert(tree, 5);
    insert(tree, 4);
    insert(tree, 9);
    insert(tree, 7);
    insert(tree, 12);
    insert(tree, 23);
    insert(tree, 1);
    insert(tree, 2);
    insert(tree, 0);
    insert(tree, 11);
    insert(tree, 18);
    cout << "inorder traversal of the bst:" << endl;
    inorder(tree);
    cout << "the tree is bst:" << isBST(tree) << endl;
    reverseBST(tree);
    cout << "the reverse tree:" << endl;
    inorder(tree);
    cout << "the reverse tree is bst:" << isBST(tree) << endl;
    reverseBST(tree);
    BST *t = copy(tree);
    cout << "the copy of bst:" << endl;
    inorder(t);
    cout << "the leaf of bst:" << endl;
    list *l = leafList(t);
    printList(l);
    int array[6] = {6, 4, 9, 2, 5, 7};
    BST *toTree = arrayToTree((int *)array, 6);
    cout << "array to tree:" << endl;
    inorder(toTree);
    cout << "the tree from array is bst:" << isBST(toTree) << endl;
    int *a = treeToArray(toTree, 6);
    cout << "tree to array:" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
