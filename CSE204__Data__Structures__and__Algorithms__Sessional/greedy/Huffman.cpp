#include<iostream>
#include<assert.h>
#include<string>
#include<queue>
#include<vector>

using namespace std;

const int mx=1e5+5;
const int mxcr=55;

class node {
public:
    char ch;
    int freq;
    int id;

    node () {
        ch=0;
        freq=0;
        id=-1;
    }
};

class comparator {
public:
    bool operator() (node A,node B) {
        return A.freq>B.freq;
    }
};

char characters[mxcr];
int frequency[mxcr];
node tree[mx][2];

node huffman (int n)
{
    priority_queue<node, vector<node>, comparator> myPQ;
    for (int i=0;i<n;i++) {
        node A;
        A.ch=characters[i];
        A.freq=frequency[i];
        A.id=i;
        myPQ.push(A);
    }

    int cnt=n;
    while (myPQ.size()>1) {
        node A=myPQ.top();
        myPQ.pop();
        node B=myPQ.top();
        myPQ.pop();

        node C;
        C.ch='.';
        C.freq=A.freq+B.freq;
        C.id=++cnt;

        myPQ.push(C);
        tree[cnt][0]=A;
        tree[cnt][1]=B;
    }

    assert(!myPQ.empty());
    return myPQ.top();
}

string code[mxcr];

void dfs (node u,string str)
{
    assert(u.id!=-1);
    ///cout<<"------"<<u.id<<"      "<<tree[u.id][0].id<<' '<<tree[u.id][1].id<<endl;
    if (u.ch!='.') code[u.id]=str;
    if (tree[u.id][0].id!=-1) dfs(tree[u.id][0],str+'0');
    if (tree[u.id][1].id!=-1) dfs(tree[u.id][1],str+'1');
}

int main ()
{
    int n;

    cin>>n;
    for (int i=0;i<n;i++) {
        cin>>characters[i]>>frequency[i];
    }

    node root=huffman(n);
    dfs(root,"");

    cout<<'\n'<<"Huffman codes are:"<<'\n';
    for (int i=0;i<n;i++) {
        cout<<characters[i]<<' '<<code[i]<<'\n';
    }

    return 0;
}

