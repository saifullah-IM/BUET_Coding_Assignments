#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
    if (length<0) initializeList();

	if (length == listMaxSize)
	{
		///allocate new memory space for tempList
		int * tempList ;
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; ///copy all items from list to tempList
        }
        free(list) ; ///free the memory allocated before
        list = tempList ; ///make list to point to new memory
	}

	list[length] = newitem ; ///store new item
	length++ ;
	return SUCCESS_VALUE ;
}

/// my work 16040356
int shrink ()
{
    if (listMaxSize==LIST_INIT_SIZE) return NULL_VALUE;
    if (length>listMaxSize/2) return NULL_VALUE;


    ///allocate new memory space for tempList
    int * tempList ;
    listMaxSize = listMaxSize/2 ;
    tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
    int i;
    for( i = 0; i < length ; i++ )
    {
        tempList[i] = list[i] ; ///copy all items from list to tempList
    }
    free(list) ; ///free the memory allocated before
    list = tempList ; ///make list to point to new memory

    return SUCCESS_VALUE;
}
/// my work done

int deleteItemAt(int position) ///version 2, do not preserve order of items
{
	if ( position >= length || position<0) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("\nCurrent size: %d, current length: %d\n", listMaxSize, length);
}


/// my work 1605036

int getLength()
{
    return length;
}

int insertItemAt (int pos,int item)
{
    if (pos>=length) return NULL_VALUE;
	if (length == listMaxSize)
	{
		///allocate new memory space for tempList
		int * tempList ;
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; ///copy all items from list to tempList
        }
        free(list) ; ///free the memory allocated before
        list = tempList ; ///make list to point to new memory
	}

	list[length]=list[pos];
	list[pos]=item;
	length++;
	return SUCCESS_VALUE;
}

int deleteLast ()
{
    if (length==0) return NULL_VALUE;
    int lastItem=list[length-1];
    length--;
    shrink();
    return lastItem;
}

int clear ()
{
    if (length<=0) return NULL_VALUE;
    while(length>0) deleteLast();
    free(list);
    length=NULL_VALUE;
    return SUCCESS_VALUE;
}

int deleteAll ()
{
    if (length<=0) return NULL_VALUE;
    while(length>0) deleteLast();
    return SUCCESS_VALUE;
}

const int maxn=1e5;

char str[maxn];
void postfixExpressionEvaluation ()
{
    clear();
    printf ("Enter your postfix expression.\n");
    scanf ("%s",str);
    int len=strlen(str);

    for (int i=0;i<len;i++) {
        if (str[i]>='0' && str[i]<='9') {
            int digit=str[i]-'0';
            insertItem(digit);
        }
        else {
            int last2=deleteLast();
            int last1=deleteLast();
            int newItem;

            if (str[i]=='+') newItem=last1+last2;
            else if (str[i]=='-') newItem=last1-last2;
            else if (str[i]=='*') newItem=last1*last2;
            else if (str[i]=='/') newItem=last1/last2;

            insertItem(newItem);
        }
    }

    int ans=deleteLast();
    printf ("Result of Postfix Expression Evaluation is %d\n\n",ans);
    clear();
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Get Length. 5. Insert item at. 6. Delete Last.\n");
        printf("7. Clear. 8.Delete All 9. Print. 10. exit.\n");

        int cmd;
        scanf("%d",&cmd);
        if(cmd==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(cmd==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(cmd==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if (cmd==4)
        {
            int len=getLength();
            printf ("Length of the array list is %d\n",len);
        }
        else if (cmd==5)
        {
            int item,pos;
            scanf("%d %d",&pos,&item);
            insertItemAt(pos,item);
        }
        else if (cmd==6)
        {
            int last=deleteLast();
            printf ("The deleted last item was %d\n",last);
        }
        else if (cmd==7)
        {
            clear();
            printf ("after clear %d\n",length);
        }
        else if (cmd==8)
        {
            deleteAll();
            printf ("after delete all %d\n",length);
        }
        else if(cmd==9)
        {
            printList();
        }
        else if(cmd==10)
        {
            break;
        }
    }

    while (1)
    {
        printf("1. Postfix Expression Evaluation.\n");
        printf("2. Exit.\n");

        int cmd;
        scanf ("%d",&cmd);
        if (cmd==1) postfixExpressionEvaluation();
        else break;
    }

    return 0;
}
