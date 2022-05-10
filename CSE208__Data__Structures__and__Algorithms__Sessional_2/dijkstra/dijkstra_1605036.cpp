#include<cstdio>
#include<cstdlib>
#include<cstring>

const int NULL_VALUE=-1e9;
const int SUCCESS_VALUE=1e9;

/// class to handle pair

class pair {
public:
    int first,second;
    pair ()
    {
        first=second=NULL_VALUE;
    }
    bool operator== (pair obj)
    {
        return (obj.first==first && obj.second==second);
    }
    bool operator> (pair obj)
    {
        return (second>obj.second);
    }
    bool operator< (pair obj)
    {
        return (second<obj.second);
    }
    pair operator= (pair obj)
    {
        first=obj.first;    second=obj.second;
        return *this;
    }
};

/// List code starts ///

class ListNode
{
public:
    pair item;
    ListNode * next;
};

class LinkedListWithTail
{
    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  ///initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    ///add required codes to set up tail pointer
    int insertItem(pair item) ///insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; ///point to previous first node
        list = newNode ; ///set list to point to newnode as this is now the first node
        if (tail==0) tail=newNode;
        length++;
        return SUCCESS_VALUE ;
    }

    ///add required codes to set up tail pointer
    int deleteItem(pair item)
    {
        ListNode *temp, *prev ;
        temp = list ; ///start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; ///move to next node
        }
        if (temp == 0) return NULL_VALUE ; ///item not found to delete
        if (temp == list) ///delete the first node
        {
            list = list->next ;
            delete temp ;
            temp=0;
            if (list==0) tail=0;
        }
        else if (temp == tail)
        {
            prev->next = 0 ;
            tail=prev;
            delete temp;
            temp=0;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            temp=0;
        }
        length--;
        return SUCCESS_VALUE ;
    }

    ///add required codes to set up tail pointer
    ListNode * searchItem(pair item)
    {
        ListNode * temp ;
        temp = list ; ///start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; ///move to next node
        }
        return 0 ; ///0 means invalid pointer in C, also called NULL value in C
    }

    ///------------write code for the functions below-----------
    int insertLast(pair item)
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        if (list==0) list=tail=newNode;
        else {
            tail->next=newNode;
            tail = newNode ; ///set list to point to newnode as this is now the first node
        }
        length++;
        return SUCCESS_VALUE ;
    }

    ListNode * getItemAt(int pos)
    {
        if (pos>length) return 0;
        ListNode * temp;
        temp = list;
        int cnt=1;
        while (cnt!=pos) {
            temp=temp->next;
            cnt++;
        }
        return temp;
    }

    int deleteLast()
    {
        if (length==0) return NULL_VALUE;
        if (length==1) {
            delete list;
            list=tail=0;
            length--;
            return SUCCESS_VALUE;
        }

        ListNode *temp, *prev ;
        temp = list ; ///start at the beginning
        while (temp != tail)
        {
            prev = temp;
            temp = temp->next ; ///move to next node
        }
        prev->next = 0 ;
        tail=prev;
        delete temp;
        temp=0;
        length--;
        return SUCCESS_VALUE;
    }

    ListNode* getList ()
    {
        return list;
    }
};


/// List code complete ///

/// Heap code starts ///

const int mx=1e3+5;

class minHeap {
    int size;
    pair ara[mx];
public:
    minHeap () {
        size=0;
    }
    void clear () {
        size=0;
    }
    void insert (pair val) {
        size++;

        ara[size]=val;
        int node=size;
        while (node>1) {
            int parent=node/2;
            if (ara[node]<ara[parent]) {
                pair temp;
                temp=ara[node];
                ara[node]=ara[parent];
                ara[parent]=temp;
                node=parent;
            }
            else break;
        }
    }
    void deleteMin () {
        if (size==0) return;

        ara[1]=ara[size];
        size--;

        int node=1;
        while (2*node<=size) {
            int child=2*node;
            if (child+1<=size) {
                if (ara[child]>ara[child+1]) {
                    child++;
                }
            }

            if (ara[node]>ara[child]) {
                pair temp;
                temp=ara[node];
                ara[node]=ara[child];
                ara[child]=temp;
                node=child;
            }
            else break;
        }
    }
    pair findMin () {
        pair ans;
        if (size!=0) ans=ara[1];
        return ans;
    }
    pair extractMin () {
        pair ans;
        if (size!=0) {
            ans=ara[1];
            deleteMin();
        }
        return ans;
    }
    bool isEmpty () {
        return (size==0);
    }
    void remove (int node) {
        if (node>size || node<1) return;

        ara[node]=ara[size];
        size--;

        while (2*node<=size) {
            int child=2*node;
            if (child+1<=size) {
                if (ara[child]>ara[child+1]) {
                    child++;
                }
            }

            if (ara[node]>ara[child]) {
                pair temp;
                temp=ara[node];
                ara[node]=ara[child];
                ara[child]=temp;
                node=child;
            }
            else break;
        }
    }
};

/// Heap code ends ///

/// Graph and Dijkstra code starts ///

LinkedListWithTail edges[mx];
int dist[mx];

void dijkstra (int s)
{
    bool vis[mx];
    memset (vis,0,sizeof(vis));
    memset (dist,63,sizeof(dist));
    dist[s]=0;

    minHeap myPQ;
    pair init;
    init.first=s;
    init.second=0;
    myPQ.insert(init);

    while (!myPQ.isEmpty()) {
        pair crnt=myPQ.extractMin();
        int u=crnt.first;
        if (vis[u]) continue;
        vis[u]=true;

        int n=edges[u].getLength();
        ListNode * temp;
        temp=edges[u].getList();
        for (int i=1;i<=n;i++) {
            pair next=(*temp).item;
            int d=crnt.second+next.second;
            int v=next.first;
            if (dist[v]>d) {
                dist[v]=d;
                pair item;
                item.first=v;
                item.second=d;
                myPQ.insert(item);
            }
            temp=temp->next;
        }
    }
}


int main ()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    scanf ("%d %d",&n,&m);
    for (int i=0;i<m;i++) {
        int u,v,w;
        scanf ("%d %d %d",&u,&v,&w);
        pair item;
        item.second=w;
        item.first=v;
        edges[u].insertItem(item);
        item.first=u;
        edges[v].insertItem(item);
    }

    int s;
    scanf ("%d",&s);
    dijkstra(s);

    for (int i=1;i<=n;i++) printf ("%d ",dist[i]);

    return 0;
}
