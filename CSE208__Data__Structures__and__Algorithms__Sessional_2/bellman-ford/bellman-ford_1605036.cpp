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

const int mx=1e3+5;

/// Graph and Bellman-Ford code starts ///

LinkedListWithTail graph[mx];
int dist[mx];

class edge {
public:
    int u,v,w;
    void setValue(int x,int y,int z)
    {
        u=x, v=y, w=z;
    }
    void getValue (int& x,int& y,int& z)
    {
        x=u, y=v, z=w;
    }
};

edge edgeList[mx];

bool bellman_ford (int s,int n,int m)
{
    memset(dist,63,sizeof(dist));
    dist[s]=0;
    int cnt;
    for (cnt=0;cnt<n;cnt++) {
        bool chk=true;
        for (int i=0;i<m;i++) {
            int u,v,w;
            edgeList[i].getValue(u,v,w);
            if (dist[u]>dist[v]+w) {
                chk=false;
                dist[u]=dist[v]+w;
            }
            if (dist[v]>dist[u]+w) {
                chk=false;
                dist[v]=dist[u]+w;
            }
        }
        if (chk) break;
    }

    return (cnt==n);
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
        graph[u].insertItem(item);
        item.first=u;
        graph[v].insertItem(item);
        edgeList[i].setValue(u,v,w);
    }

    int s;
    bool negative_cycle;
    scanf ("%d",&s);
    negative_cycle=bellman_ford(s,n,m);

    if (negative_cycle) printf("Negative Cycle exists.\n");
    else for (int i=1;i<=n;i++) printf ("%d ",dist[i]);

    return 0;
}
