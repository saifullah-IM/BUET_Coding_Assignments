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

int main(void)
{
    LinkedListWithTail ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. InsertLast. 5. GetItemAt.  6.DeleteLast.  \n");
        printf("7. Print. 8. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            ll.deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if (ch==4)
        {
            int item;
            scanf ("%d",&item);
            ll.insertLast(item);
        }
        else if (ch==5)
        {
            int pos;
            scanf ("%d",&pos);
            ListNode * res=ll.getItemAt(pos);
            if (res==0) printf ("Not Found.\n");
            else printf ("Item found: %d\n",res->item);
        }
        else if (ch==6)
        {
            ll.deleteLast();
        }
        else if(ch==7)
        {
            ll.printList();
        }
        else if(ch==8)
        {
            break;
        }
    }

    return 0;
}
