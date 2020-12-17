//date:2020.12.17
//path:/home/Lego/Code/DS

#include <iostream>
using namespace std;

int height(int *preorder, int *inorder, int n)
{
    if (!n)
        return 0; //base case
    int root = 0;
    while (inorder[root] != *preorder)
    {
        root++; //find root's position in preorder travelsal
    }
    int leftHeight = height(preorder, inorder + 1, root);
    int rightHeight = height(preorder + root + 1, inorder + root + 1, n - root - 1);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int main(){
    int n;
    cin >> n;
    int preorder[n];
    int inorder[n];
    for (int i = 0; i < n; i++)
    {
        cin >> preorder[i];
    }
    for (int j = 0; j < n; j++)
    {
        cin >> inorder[j];
    }
    cout << height((int *)preorder, (int *)inorder, n) << endl;
    return 0;
}
