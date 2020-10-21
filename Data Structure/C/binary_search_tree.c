//function:create_new_node,search,insert,delete,find_maximum,find_minimum,find_successor;

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

//search
struct TreeNode* searchBST(struct TreeNode* root, int val){
    while(root!=NULL && val!=root->val){
        if(val<root->val)
            root=root->left;
        else
            root=root->right;
    }
    return root;
}

//create a new node
struct TreeNode* new_node(int key){
    struct TreeNode* node=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val=key;
    node->left=node->right=NULL;
    return node;
}

//insert
struct TreeNode* insertIntoBST(struct TreeNode* root, int val){
    struct TreeNode* node=new_node(val);
    struct TreeNode* tmp=root;
    struct TreeNode* par;
    if(root==NULL)
        return node;
    while(tmp!=NULL){
        if(val<tmp->val){
            par=tmp;
            tmp=tmp->left;
        }
        else{
            par=tmp;
            tmp=tmp->right;
        }
    }
    if(val<par->val)
        par->left=node;
    else
        par->right=node;
    return root;
}

//find minimum in a subtree
struct TreeNode* minimum(struct TreeNode* node){
        while(node->left)
                node = node->left;
        return node;
}

//find maximum in a subtree
struct TreeNode* maximum(struct TreeNode* node){
        while(node->right)
                node = node->right;
        return node;
}

//find successor of a node
struct TreeNode* succeed(struct TreeNode* node){
        if(!(node->right))
                return maximum(node->left);
          else
                return minimum(node->right);
}

//input a key
//delete the node with that key in the bst
//in a iterative way
struct TreeNode* deleteNode(struct TreeNode* root, int key){
        if(!root)
                return NULL;
        struct TreeNode *del,*par,*suc,*tmp;
        par = root;
        del = root;
        while(del && del->val != key){
                par=del;
                if(key < del->val)
                        del = del->left;
                else
                        del = del->right;
        }
        if(!del) return root;                 //no node to be deleted
        if( !(del->left) && !(del->right)){           //node have no child
                if(del->val == root->val)
                        return NULL;              //delete root
                if(del == par->left).            //delete leaf
                          par->left = NULL;
                  else
                          par->right = NULL;
                  return root;
          }
     if(del->left && !(del->right)){.       //node only have l. subtree
                if(del == root)
                        return root->left;
                if(del == par->left)
                        par->left = del->left;
                else
                        par->right = del->left;         //skip
        }
        else if(del->right && !(del->left)){.       //node only have r. subtre  e
                if(del == root)
                        return root->right;
                if(del == par->left)
                        par->left = del->right;
                else
                        par->right = del->right;       //skip
        }
         else{                       //node have two subtrees
                suc = succeed(del);
                if(del->right == suc){               //del->right->left == NUL  L
                        if(del == root){
                                suc->left = del->left;    //succeed root'  s l. subtree
                                return suc;
                        }
                        if(del == par->left){
                                par->left = suc; //skip
                        }
                        else
                                par->right = suc; //skip
                        suc->left = del->left; //succeed node's l. subtree
                }
             else{   //normal case
                        del->val = suc->val;
                        tmp = del->right;
                        while(tmp->left && tmp->left != suc)
                                tmp = tmp->left;     //find successor's parent
                        if(suc->right)
                                tmp->left =suc->right;
                        else                //successor has no child;
                        tmp->left=NULL;
                }
        }
        return root;
}

//input a key
//delete the node with that key in the bst
//in a recursion way
struct TreeNode* deleteNode_recur(struct TreeNode* root, int key){
       if (!root)
                return NULL;
        if(key<root->val)
                root->left=deleteNode(root->left,key);
        else if(key>root->val)
                root->right=deleteNode(root->right,key);
        else{
            if(!(root->left)){
                struct TreeNode* base=root->right;
                root = NULL;
                return base;
            }
            else if(!(root->right)){
                struct TreeNode* base=root->left;
                root = NULL;
                return base;
            }
            else{
                struct TreeNode* base=minimum(root->right);
                root->val=base->val;
                root->right=deleteNode(root->right,base->val);
            }
        }
    return root;
}
