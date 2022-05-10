#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


/// Linked List Class ///

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; ///initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertItem(int item) ///insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; ///point to previous first node
        list = newNode ; ///set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

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
            delete temp;
            temp=0;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            temp=0;
            length--;
        }
        return SUCCESS_VALUE ;
    }


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
        printf("Length: %d\n",length);
    }

    ///------------write code for the functions below-----------

    int insertLast(int item)
    {
        ListNode * newNode = new ListNode();
        newNode->item = item ;

        if (list==0) list=newNode;
        else {
            ListNode * temp;
            temp = list;
            while(temp->next!=0)
            {
                temp = temp->next;
            }
            temp->next=newNode;
        }
        length++;
        return SUCCESS_VALUE;
    }

    int insertAfter(int oldItem, int newItem)
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            if (temp->item==oldItem) {
                ListNode * newNode = new ListNode() ;
                newNode->item = newItem ;
                newNode->next = temp->next;
                temp->next = newNode;
                length++;
                return SUCCESS_VALUE;
            }
            temp = temp->next;
        }
        return NULL_VALUE;
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

    int deleteFirst()
    {
        if (list==0) return NULL_VALUE;
        ListNode * temp;
        temp = list;
        list=temp->next;
        delete temp;
        temp=0;
        length--;
        return SUCCESS_VALUE;
    }

    ~LinkedList()
    {
        while(list!=0)
        {
            ListNode * temp;
            temp=list;
            list = list->next;
            delete temp;
            temp=0;
        }
        length=0;
    }
};

/// End of Linked List Class ///

class Stack
{
    LinkedList ll;
public:
    Stack()
    {
        ll = *new LinkedList();
    }
    void push(int item)
    {
        ll.insertItem(item);
    }
    int pop()
    {
        if (ll.getLength()==0) return NULL_VALUE;
        int ans=ll.getItemAt(1)->item;
        ll.deleteFirst();
        return ans;
    }
};

int main(void)
{
    Stack st;

    while(1)
    {
        printf("1. Push. 2. Pop. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            st.push(item);
        }
        else if(ch==2)
        {
            int item=st.pop();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
    }

    return 0;
}
