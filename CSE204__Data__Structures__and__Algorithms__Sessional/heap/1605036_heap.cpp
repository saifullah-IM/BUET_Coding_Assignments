#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int err=-1e9;

class maxHeap {
    int N,Size;
    vector<int> ara;
public:
    maxHeap () {
        N=16;
        Size=0;
        ara.resize(16);
    }
    maxHeap (int data[],int n) {
        N=16;
        Size=0;
        ara.resize(16);
        for (int i=0;i<n;i++) insert(data[i]);
    }
    void clear () {
        N=16;
        Size=0;
        ara.clear();
        ara.resize(16);
    }
    void insert (int val) {
        Size++;
        if (Size>=N) {
            N*=2;
            ara.resize(N);
        }

        ara[Size]=val;
        int node=Size;
        while (node>1) {
            int parent=node/2;
            if (ara[node]>ara[parent]) {
                swap(ara[node],ara[parent]);
                node=parent;
            }
            else break;
        }
    }
    void deleteMax () {
        if (Size==0) return;

        ara[1]=ara[Size];
        Size--;
        if (Size<N/2) {
            N=max(16,N/2);
            ara.resize(N);
        }

        int node=1;
        while (2*node<=Size) {
            int child=2*node;
            if (child+1<=Size) {
                if (ara[child]<ara[child+1]) {
                    child++;
                }
            }

            if (ara[node]<ara[child]) {
                swap(ara[node],ara[child]);
                node=child;
            }
            else break;
        }
    }
    int findMax () {
        if (Size==0) return err;
        return ara[1];
    }
    int extractMax () {
        int ans;
        if (Size==0) ans=err;
        else {
            ans=ara[1];
            deleteMax();
        }
        return ans;
    }
    int replace (int val) {
        int ans;
        if (Size==0) ans=err;
        else ans=ara[1];

        ara[1]=val;
        int node=1;
        while (2*node<=Size) {
            int child=2*node;
            if (child+1<=Size) {
                if (ara[child]<ara[child+1]) {
                    child++;
                }
            }

            if (ara[node]<ara[child]) {
                swap(ara[node],ara[child]);
                node=child;
            }
            else break;
        }

        return ans;
    }
    int size () {
        return Size;
    }
    bool isEmpty () {
        return (Size==0);
    }
    void remove (int node) {
        if (node>Size || node<1) return;

        ara[node]=ara[Size];
        Size--;
        if (Size<N/2) {
            N=max(16,N/2);
            ara.resize(N);
        }

        while (2*node<=Size) {
            int child=2*node;
            if (child+1<=Size) {
                if (ara[child]<ara[child+1]) {
                    child++;
                }
            }

            if (ara[node]<ara[child]) {
                swap(ara[node],ara[child]);
                node=child;
            }
            else break;
        }
    }
    void increaseKey (int node,int val) {
        if (val<=0) return;
        if (node>Size || node<1) return;

        ara[node]+=val;
        while (node>1) {
            int parent=node/2;
            if (ara[node]>ara[parent]) {
                swap(ara[node],ara[parent]);
                node=parent;
            }
            else break;
        }
    }
    void decreaseKey (int node,int val) {
        if (val<=0) return;
        if (node>Size || node<1) return;

        ara[node]-=val;
        while (2*node<=Size) {
            int child=2*node;
            if (child+1<=Size) {
                if (ara[child]<ara[child+1]) {
                    child++;
                }
            }

            if (ara[node]<ara[child]) {
                swap(ara[node],ara[child]);
                node=child;
            }
            else break;
        }
    }
    void updateKey (int node,int val) {
        if (node>Size || node<1) return;

        if (val>0) increaseKey(node,val);
        else if (val<0) decreaseKey(node,-val);
    }
    maxHeap merge (maxHeap& mh1, maxHeap& mh2) {
        maxHeap ans;
        for (int i=1;i<=mh1.Size;i++) ans.insert(mh1.ara[i]);
        for (int i=1;i<=mh2.Size;i++) ans.insert(mh2.ara[i]);
        return ans;
    }
    maxHeap meld (maxHeap& mh1, maxHeap& mh2) {
        for (int i=1;i<=mh2.Size;i++) mh1.insert(mh2.ara[i]);
        mh2.clear();
        return mh1;
    }

    void print () {
        cout<<"Heap Size = "<<Size<<endl;
        for (int i=1;i<=Size;i++) cout<<ara[i]<<' ';
        cout<<endl;
    }
};

int main ()
{
    maxHeap mh;
    while (1) {
        printf ("\n1.insert  2.findMax  3.extractMax  4.deleteMax  5.replace\n");
        printf ("6.size  7.increaseKey  8.decreaseKey  9.merge  10.meld\n");
        printf ("11.deleteKey  12.isEmpty  13.clear  14.print  15.Exit\n\n");

        int command;
        cin>>command;
        if (command==1) {
            int val;
            cout<<"Enter value"<<endl;
            cin>>val;
            mh.insert(val);
        }
        else if (command==2) {
            int ans=mh.findMax();
            printf ("Max element: %d\n",ans);
        }
        else if (command==3) {
            int ans=mh.extractMax();
            printf ("Max element: %d\n",ans);
        }
        else if (command==4) {
            mh.deleteMax();
        }
        else if (command==5) {
            int val;
            cout<<"Enter value"<<endl;
            cin>>val;
            mh.replace(val);
        }
        else if (command==6) {
            int ans=mh.size();
            printf ("Heap size is %d\n",ans);
        }
        else if (command==7) {
            int node,val;
            cout<<"Enter node and value"<<endl;
            cin>>node>>val;
            mh.increaseKey(node,val);
        }
        else if (command==8) {
            int node,val;
            cout<<"Enter node and value"<<endl;
            cin>>node>>val;
            mh.decreaseKey(node,val);
        }
        else if (command==9) {
            maxHeap mh1,mh2,mh3;
            cout<<"Enter first heap size and values"<<endl;
            int n;
            cin>>n;
            for (int i=1;i<=n;i++) {
                int val;
                cin>>val;
                mh1.insert(val);
            }

            cout<<"Enter second heap size and values"<<endl;
            cin>>n;
            for (int i=1;i<=n;i++) {
                int val;
                cin>>val;
                mh2.insert(val);
            }
            mh3=mh3.merge(mh1,mh2);
            mh3.print();
        }
        else if (command==10) {
            maxHeap mh1,mh2,mh3;
            cout<<"Enter first heap size and values"<<endl;
            int n;
            cin>>n;
            for (int i=1;i<=n;i++) {
                int val;
                cin>>val;
                mh1.insert(val);
            }

            cout<<"Enter second heap size and values"<<endl;
            cin>>n;
            for (int i=1;i<=n;i++) {
                int val;
                cin>>val;
                mh2.insert(val);
            }
            mh3=mh3.meld(mh1,mh2);
            mh3.print();
        }
        else if (command==11) {
            int node;
            cin>>node;
            mh.remove(node);
        }
        else if (command==12) {
            if (mh.isEmpty()) cout<<"Heap is empty"<<endl;
            else cout<<"Heap is not empty"<<endl;
        }
        else if (command==13) {
            mh.clear();
        }
        else if (command==14) {
            mh.print();
        }
        else if (command==15) break;
    }

    return 0;
}
