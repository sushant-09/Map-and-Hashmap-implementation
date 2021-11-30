#include<bits/stdc++.h>
using namespace std;
template <typename T1, typename T2>
class OrderedMap
{
    public:
    class Node
    {
        public:
        T1 key;
        T2 value;
        Node* left;
        Node* right;
        int height;
        Node()
        {
            left=NULL;
            right=NULL;
            height=0;
        }
    };
    Node* root;
    int count;
    OrderedMap()
    {
        root=NULL;
        count=0;
    }
    Node* createNode(T1 key,T2 value)
    {
        Node* node=new Node();
        node->key=key;
        node->value=value;
        node->left=NULL;
        node->right=NULL;
        node->height=1;
        return(node);
    }
    Node* insertNode(Node* root, T1 key, T2 value)
    {
        if(root==NULL)
        {
            count++;
            return createNode(key,value);
        }
        if(root->key==key)
        {
            root->value=value;
            return root;
        }
        if(key<root->key)
            root->left=insertNode(root->left,key,value);
        else if(key>root->key)
            root->right=insertNode(root->right,key,value);
        int lheight=root->left?root->left->height:0;
        int rheight=root->right?root->right->height:0;
        root->height=1+max(lheight,rheight);
        if((lheight-rheight)>1 && key<root->left->key)
            return ll(root);
        if((rheight-lheight)>1 && key>root->right->key)
            return rr(root);
        if((lheight-rheight)>1 && key>root->left->key)
            return lr(root);
        if((rheight-lheight)>1 && key<root->right->key)
            return rl(root);
        return root;
    }
    Node* lr(Node *node)
    {
        node->left=rr(node->left);
        return ll(node);
    }
    Node* rl(Node *node)
    {
        node->right=ll(node->right);
        return rr(node);
    }
    Node* ll(Node *node)
    {
        Node* leftnode=node->left;
        Node* temp=leftnode->right;
        leftnode->right=node;
        node->left=temp;
        node->height=1+max(node->left?node->left->height:0,node->right?node->right->height:0);
        leftnode->height=1+max(leftnode->left?leftnode->left->height:0,leftnode->right?leftnode->right->height:0);
        return leftnode;
    }
    Node* rr(Node* node)
    {  
        Node*rightnode=node->right;
        Node*temp=rightnode->left;
        rightnode->left=node;
        node->right=temp;
        node->height=1+max(node->left?node->left->height:0,node->right?node->right->height:0);
        rightnode->height=1+max(rightnode->left?rightnode->left->height:0,rightnode->right?rightnode->right->height:0);
        return rightnode;  
    }
    void insert(T1 key, T2 value)
    {
        root=insertNode(root,key,value);
    }
    bool search(Node* root, T1 key)
    {
        if(root)
        {
            if(root->key==key)
                return true;
            else if(key<root->key)
                return search(root->left,key);
            else
                return search(root->right,key);
        }
        return false;
    }
    Node* _search(Node* root, T1 key)
    {
        if(root)
        {
            if(root->key==key)
                return root;
            else if(key<root->key)
                return _search(root->left,key);
            else
                return _search(root->right,key);
        }
        return NULL;
    }
    bool find(T1 key)
    {
        return search(root,key);
    }
    int checkBalance(Node* root)
    {
        if(root)
        {
            int lheight=root->left?root->left->height:0;
            int rheight=root->right?root->right->height:0;
            return (lheight-rheight);
        }
        return 0;
    }
    Node* deleteNode(Node* root,T1 key)
    {
        if(!root)
            return root;
        if(key<root->key)
            root->left=deleteNode(root->left,key);
        else if(key>root->key)
            root->right=deleteNode(root->right,key);
        else
        {
            if(root->left==NULL && root->right==NULL)
            {
                free(root);
                count--;
                return NULL;
            }
            else if(root->left==NULL)
            {
                Node* temp=root->right;
                free(root);
                count--;
                return temp;
            }
            else if(root->right==NULL)
            {
                Node* temp=root->left;
                free(root);
                count--;
                return temp;
            }
            else
            {
                Node* temp=root->right;
                while(temp->left!=NULL)
                    temp=temp->left;
                root->key=temp->key;
                root->right=deleteNode(root->right,temp->key);
            }
        }
        int lheight=root->left?root->left->height:0;
        int rheight=root->right?root->right->height:0;
        root->height=1+max(lheight,rheight);
        if((lheight-rheight)>1 && checkBalance(root->left)>=0)
            return ll(root);
        if((rheight-lheight)>1 && checkBalance(root->right)<=0)
            return rr(root);
        if((lheight-rheight)>1 && checkBalance(root->left)<0)
            return lr(root);
        if((rheight-lheight)>1 && checkBalance(root->right)>0)
            return rl(root);
        return root;
    }
    void erase(T1 key)
    {
        root=deleteNode(root,key);
    }
    int size()
    {
        return count;
    }
    void deleteTree(Node* root)
    {
        if(!root)
            return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        count--;
    }
    void clear()
    {
        deleteTree(root);
        root=NULL;
    }
    T2& operator[](T1 key)
    {
        Node* temp=_search(root,key);
        if(temp)
        {
            return temp->value;
        }
        else
        {
            root=insertNode(root,key,0);
            return (_search(root,key))->value;
        }
    }
};
int main()
{
    OrderedMap<string,int> om;
    om.insert("abc",3);
    cout<<om.size();
    om["abc"]=3;
    cout<<om.size();
    return 0;
}