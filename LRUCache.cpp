/*
Problem Link: https://www.interviewbit.com/problems/lru-cache/
Problem Statement: 
Design and implement a data structure for LRU (Least Recently Used) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least recently used item before inserting the new item.
The LRU Cache will be initialized with an integer corresponding to its capacity. Capacity indicates the maximum number of unique keys it can hold at a time.

Definition of “least recently used” : An access to an item is defined as a get or a set operation of the item. “Least recently used” item is the one with the oldest access time.

NOTE: If you are using any global variables, make sure to clear them in the constructor.

Example :

Input : 
         capacity = 2
         set(1, 10)
         set(5, 12)
         get(5)        returns 12
         get(1)        returns 10
         get(10)       returns -1
         set(6, 14)    this pushes out key = 5 as LRU is full. 
         get(5)        returns -1  
*/
#include <bits/stdc++.h>
using namespace std;
class Node
{
    public:
    int key,data;
    Node *next;
};
class LRUCache
{
    public:
    int capacity,size;
    unordered_map<int,Node*> mp;
    Node *dummy,*tail;
    LRUCache(int capacity)
    {
        this->size=0;
        this->capacity=capacity;
        Node *nn = new Node();
        nn->key=0;
        nn->data=0;
        nn->next=NULL;
        dummy=nn;
        tail=nn;
    }
    int get(int key)
    {
        if(mp.find(key)==mp.end())
            return -1;
        
        if(mp[key]->next!=tail)
        {
            Node *prev=mp[key];
            Node *curr=mp[key]->next;
            prev->next=curr->next;
            mp[curr->next->key]=prev;
            curr->next=NULL;
            tail->next=curr;
            mp[key]=tail;
            tail=tail->next;
        }
        return tail->data;
    }
    void set(int key,int value)
    {
        if(mp.find(key)==mp.end())
        {
            if(size==capacity)
            {
                mp.erase(dummy->next->key);
                dummy->next=dummy->next->next;
                if(dummy->next==NULL)
                tail=dummy;
                else
                mp[dummy->next->key]=dummy;
                Node *nn=new Node();
                nn->key=key;
                nn->data=value;
                nn->next=NULL;
                tail->next=nn;
                mp[key]=tail;
                tail=tail->next;
            }
            else
            {
                Node *nn=new Node();
                nn->key=key;
                nn->data=value;
                nn->next=NULL;
                tail->next=nn;
                mp[key]=tail;
                tail=tail->next;
                size++;
            }
        }
        else
        {
            if(mp[key]->next!=tail)
            {
                Node *prev=mp[key];
                Node *curr=mp[key]->next;
                prev->next=curr->next;
                mp[curr->next->key]=prev;
                curr->next=NULL;
                tail->next=curr;
                mp[key]=tail;
                tail=tail->next;
            }
            tail->data=value;
        }
    }
};
int main() {
    // your code goes here
    int operations,c;
    cin>>operations>>c;
    LRUCache lrucache(c);
    while(operations--)
    {
        string s;
        cin>>s;
        if(s=="S")
        {
            int k,v;
            cin>>k>>v;
            lrucache.set(k,v);
        }
        else if(s=="G")
        {
            int k;
            cin>>k;
            cout<<lrucache.get(k)<<" ";
        }
        else
        break;
    }
    return 0;
}