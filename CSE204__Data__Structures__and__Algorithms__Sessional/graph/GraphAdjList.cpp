#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); ///insert item in the queue
    int dequeue(); ///returns the item according to FIFO
    bool empty(); ///return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; ///allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		///allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; ///copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; ///copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; ///free the memory allocated before
		data = tempData ; ///make list to point to new memory
	}

	data[front] = item ; ///store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; ///deallocate memory
    data = 0; ///set to NULL
}

///****************Queue class ends here************************

///****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		///allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; ///copy all items from list to tempList
        }
        delete[] list ; ///free the memory allocated before
        list = tempList ; ///make list to point to new memory
	};

	list[length] = newitem ; ///store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) ///do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; ///nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; ///nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete[] list;
    list = 0 ;
}

///******************ArrayList class ends here*************************

///******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
    int * color, * parent, * dist, * dTime, * fTime;
    int timer;
    bool flag;
	///define other variables required for bfs such as color, parent, and dist
	///you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); ///will run bfs in the graph
	void initDfs();
	void dfs(int source); ///will run dfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; ///set direction of the graph
    parent=0;
    color=0;
    dist=0;
    dTime=0;
    fTime=0;
    timer=0;
    flag=false;
	///define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; ///delete previous list
	adjList = new ArrayList[nVertices] ;

	if(parent!=0) delete[] parent ;
	parent=new int[nVertices];

	if(color!=0) delete[] color ;
	color=new int[nVertices];

	if(dist!=0) delete[] dist ;
	dist=new int[nVertices];

	if(dTime!=0) delete[] dTime ;
	dTime=new int[nVertices];

	if(fTime!=0) delete[] fTime ;
	fTime=new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; ///vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; ///vertex out of range
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
	if(!directed) adjList[v].removeItem(u) ;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
	int position=adjList[u].searchItem(v) ;
	return (position!=NULL_VALUE);
}

int Graph::getDegree(int u)
{
    int ans=adjList[u].getLength();
    for (int i=0;i<nVertices;i++) {
        int position=adjList[i].searchItem(u);
        if (position!=NULL_VALUE) ans++;
    }
    return ans;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    int n=adjList[u].getLength();
    for (int i=0;i<n;i++) {
        int x=adjList[u].getItem(i);
        int position=adjList[v].searchItem(x);
        if (position!=NULL_VALUE) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    parent[source]=NULL_VALUE;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u=q.dequeue();
        assert(u>=0 && u<nVertices);
        int n=adjList[u].getLength();
        for (int i=0;i<n;i++) {
            int v=adjList[u].getItem(i);
            assert(v>=0 && v<nVertices);
            if (color[v]!=WHITE) continue;
            color[v]=BLACK;
            dist[v]=1+dist[u];
            parent[v]=u;
            q.enqueue(v);
        }
    }
}

void Graph::initDfs()
{
    timer=0;
    for (int i=0;i<nVertices;i++) {
        dTime[i]=fTime[i]=NULL_VALUE;
        parent[i]=NULL_VALUE;
        color[i]=WHITE;
    }
}

void Graph::dfs(int u)
{
    if (!flag) {
        initDfs();
        flag=true;
    }
    ++timer;
    dTime[u]=timer;
    color[u]=GREY;

    int n=adjList[u].getLength();
    for (int i=0;i<n;i++) {
        int v=adjList[u].getItem(i);
        if (color[v]==WHITE) {
            parent[v]=u;
            dfs(v);
        }
    }

    ++timer;
    fTime[u]=timer;
    if (dTime[u]==1) flag=false;
}

int Graph::getDist(int u, int v)
{
    bfs(u);
    return dist[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
	if(adjList!=0) delete[] adjList ;
	adjList = 0 ;

	if(parent!=0) delete[] parent ;
	parent=0;

	if(color!=0) delete[] color ;
	color=0;

	if(dist!=0) delete[] dist ;
	dist=0;

	if(dTime!=0) delete[] dTime ;
	dTime=0;

	if(fTime!=0) delete[] fTime ;
	fTime=0;
}


///**********************Graph class ends here******************************


///******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2.Remove Edge 3. Is Edge\n");
        printf("4. Degree. 5.HasCommonAdjacent 6.BFS");
        printf("7.Distance 8.DFS 9. Print Graph  10. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            scanf ("%d %d",&u,&v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u,v;
            scanf ("%d %d",&u,&v);
            bool ans=g.isEdge(u,v);
            if (ans) printf("There is edge.\n");
            else printf("There is no such edge.\n");
        }
        else if (ch==4)
        {
            int u;
            scanf ("%d",&n);
            int ans=g.getDegree(u);
            printf("Count of degree is %d\n",ans);
        }
        else if(ch==5)
        {
            int u,v;
            scanf ("%d %d",&u,&v);
            bool ans=g.hasCommonAdjacent(u,v);
            if (ans) printf("There is common adjacent.\n");
            else printf("There is no common adjacent.\n");
        }
        else if(ch==6)
        {
            int u;
            scanf ("%d",&n);
            g.bfs(u);
        }
        else if (ch==7)
        {
            int u,v;
            scanf ("%d %d",&u,&v);
            int ans=g.getDist(u,v);
            printf("Distance is %d.\n",ans);
        }
        else if (ch==8)
        {
            int u;
            scanf ("%d",&n);
            g.dfs(u);
        }
        else if (ch==9)
        {
            g.printGraph();
        }
        else {
            break;
        }
    }

    return 0;
}
