#include <bits/stdc++.h>
#define ll long long
#define size 100
#define prime 31
using namespace std;
template<typename T1, typename T2> class Unordered_map
{
    public:
    class Node
    {
        public:
        T1 key;
        T2 value;
        Node* next;
        Node(T1 k, T2 v)
        {
            key=k;
            value=v;
            next=NULL;
        }
    };
    Node* umap[size];
    Unordered_map()
    {
        for(ll i=0; i<size; i++)
            umap[i]=NULL;
    }
    ll hash(T1 k)
    {
        ll hashval=0,m=1;
        ostringstream ss;
        ss << k;
        string key=ss.str();
        for(ll i=0; i<key.length(); i++)
        {
            char ch=key[i];
            hashval=hashval+(ch*m);
            hashval=hashval%size;
            m=m*prime;
        }
        return hashval;
    }
    void insert(T1 key, T2 value)
    {
        ll index=hash(key);
        Node* head=umap[index];
        if(!head)
        {
            Node* newNode= new Node(key, value);
            umap[index]=newNode;
        }
        else
        {
            Node* temp=head;
            while(temp->key!=key && temp->next)
                temp=temp->next;
            if(temp->next==NULL && temp->key!=key)
                temp->next=new Node(key, value);
            else if(temp->key==key)
                temp->value=value;
        }
    }
    bool find(T1 key)
    {
        ll index=hash(key);
        Node* head=umap[index];
        while(head)
        {
            if(head->key==key)
                return true;
            head=head->next;
        }
        return false;
    }
    void erase(T1 key)
    {
        ll index=hash(key);
        Node* head=umap[index];
        if(head)
        {
            if(head->key==key)
            {
                umap[index]=NULL;
                free(head);
            }
            else
            {
                Node* temp1=head, *temp2=head;
                while(temp1 && temp1->next)
                {
                    if(temp1->next->key==key)
                    {
                        temp1->next=temp1->next->next;
                        free(temp2->next);
                        return;
                    }
                    temp1=temp1->next;
                    temp2=temp1;
                }
            }
        }
    }
    T2& operator[](T1 key)
    {
        ll index=hash(key);
        Node* head=umap[index];
        while(head)
        {
            if(head->key==key)
                return head->value;
            head=head->next;
        }
        // return 0;
    }
};
int main()
{
    Unordered_map<int,int> um;
    um.insert(2,3);
    um.insert(1,5);
    cout<<um.find(5)<<endl;
    cout<<um[1]<<endl;
    return 0;
}