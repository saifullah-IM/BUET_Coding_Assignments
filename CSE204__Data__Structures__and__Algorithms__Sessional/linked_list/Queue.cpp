#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
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
    int insertItem(int item) ///insert at the beginning
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
    int deleteItem(int item)
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
    ListNode * searchItem(int item)
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

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",getLength());
    }

    ///------------write code for the functions below-----------
    int insertLast(int item)
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
};

class Queue
{
    LinkedListWithTail ll;
public:
    Queue()
    {
        ll = *new LinkedListWithTail();
    }

    void enqueue(int item)
    {
        ll.insertLast(item);
    }

    int dequeue()
    {
        if (ll.getLength()==0) return NULL_VALUE;
        int ans=ll.getItemAt(1)->item;
        ll.deleteItem(ans);
        return ans;
    }
};

int main(void)
{
    Queue qu;

    while(1)
    {
        printf("1. Enque. 2. Deque. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);
        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
    }

    return 0;
}

