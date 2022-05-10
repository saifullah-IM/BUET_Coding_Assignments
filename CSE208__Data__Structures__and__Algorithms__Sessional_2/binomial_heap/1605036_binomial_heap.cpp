#include<bits/stdc++.h>
using namespace std;

const int sz=12;
const int mx=2005;
class PII {
public:
    int first,second;
    void make_pair(int x,int y) {
        first=x,    second=y;
    }
};
class binomialTree {
    int order;
    int data;
    binomialTree* parent;
public:
    binomialTree* children[sz];
    binomialTree () {
        order=-1;
        data=0;
        parent=NULL;
        for (int i=0;i<sz;i++) children[i]=NULL;
    }
    int getOrder () {
        return order;
    }
    int getData () {
        return data;
    }
    void setData (int data) {
        order=max(0,order);
        this->data=data;
    }
    binomialTree* getParent () {
        return parent;
    }
    binomialTree* merge (binomialTree* A) {
        if (A->order!=order) {
            cout<<"tree merge error"<<endl;
            exit(-1);
        }
        binomialTree* B=this;
        if (A->data>B->data) swap(A,B);
        A->children[order]=B;
        A->order++;
        B->parent=A;
        return A;
    }
    void print () {
        binomialTree* ara[mx],* aux[mx];
        ara[0]=this;
        PII output[mx];
        output[0].make_pair(data,0);
        int cnt=1,axcnt;
        for (int i=0;i<=order;i++) {    ///cout<<"---"<<i<<' '<<cnt<<endl;
            printf ("Level %d: ",i);
            axcnt=0;
            int x=0;
            for (int j=0;j<cnt;j++) {
                while (x<output[j].second) {
                    cout<<" ";
                    x++;
                }
                cout<<output[j].first<<"  ";
                for (int k=0;k<=ara[j]->getOrder()-1;k++) {
                    aux[axcnt]=ara[j]->children[k];
                    output[axcnt].make_pair(aux[axcnt]->getData(),x);
                    axcnt++;
                    ///x=max(x,(1<<k)+k-1);
                }
                x+=(order-i+1);
                //x+=max((order-i+1),3);
            }
            cout<<endl;
            cnt=axcnt;
            for (int j=0;j<cnt;j++) ara[j]=aux[j];
        }
    }
};

class binomialHeap {
    int SIZE;
    int minTree;
    binomialTree* trees[sz];
public:
    binomialHeap () {
        SIZE=0;
        minTree=-1;
        for (int i=0;i<sz;i++) trees[i]=NULL;
    }
    int findMin () {
        if (minTree<0) {
            cout<<"findMin error"<<endl;
            exit(-1);
        }
        return trees[minTree]->getData();
    }
    void fixMin () {
        minTree=-1;
        int data=INT_MAX;
        for (int i=0;i<sz;i++) {
            if (trees[i]==NULL) continue;
            if (data>trees[i]->getData()) {
                data=trees[i]->getData();
                minTree=i;
            }
        }
        if (minTree<0) {
            cout<<"fixMin error"<<endl;
            exit(-1);
        }
    }
    void insert (int data) {///cout<<data<<"  ------  "<<minTree<<endl;
        binomialTree* A;
        A=new binomialTree;
        A->setData(data);
        for (int i=0;i<sz;i++) {
            if (A->getOrder()!=i) {
                cout<<"insert error"<<endl;
                exit(-1);
            }
            if (trees[i]==NULL) {
                trees[i]=A;
                break;
            }
            else {
                A=A->merge(trees[i]);
                trees[i]=NULL;
            }
        }
        fixMin();
        ///cout<<data<<"  ******  "<<minTree<<endl;
    }
    void merge (binomialHeap H) {   ///cout<<"inmerge"<<endl;
        SIZE+=H.SIZE;
        binomialTree* carry=NULL;
        for (int i=0;i<sz;i++) {
            if (carry!=NULL && carry->getOrder()!=i) {
                cout<<"heap merge error"<<endl;
                exit(-1);
            }
            if (carry==NULL) {
                if (trees[i]==NULL) trees[i]=H.trees[i];
                else if (H.trees[i]!=NULL) {
                    carry=trees[i]->merge(H.trees[i]);
                    trees[i]=NULL;
                }
            }
            else {
                if (trees[i]==NULL && H.trees[i]==NULL) {
                    trees[i]=carry;
                    carry=NULL;
                }
                else if (trees[i]!=NULL && H.trees[i]==NULL) {
                    carry=carry->merge(trees[i]);
                    trees[i]=NULL;
                }
                else carry=carry->merge(H.trees[i]);
            }
        }
        fixMin();
    }
    void pop () {   ///cout<<"inpop"<<endl;
        binomialTree* T=trees[minTree];
        trees[minTree]=NULL;
        SIZE-=(1<<minTree);
        if (minTree==0) {
            fixMin();
            return;
        }
        binomialHeap H;
        H.SIZE=(1<<minTree)-1;
        for (int i=0;i<sz;i++) H.trees[i]=T->children[i];
        H.fixMin();
        merge(H);
        ///cout<<"----"<<minTree<<endl;
    }
    int extractMin () {
        int ans=findMin();
        pop();
        return ans;
    }
    void print () {
        for (int i=0;i<sz;i++) {
            if (trees[i]!=NULL) {   ///cout<<i<<endl;
                trees[i]->print();
                cout<<endl;
            }
        }
    }
};

void test (int n)
{
    vector<int> vec;
    for (int i=1;i<=n;i++) vec.push_back(i);
    random_shuffle(vec.begin(),vec.end());
    binomialHeap bh;
    for (int i=0;i<n;i++) {
        ///cout<<i<<' '<<vec[i]<<endl;
        bh.insert(vec[i]);
    }
    bh.print();
}

int main ()
{
    ///test(11);
    binomialHeap bh;
    cout<<"1. Insert   2. FindMin   3.ExtractMin   4.Print   5.Exit"<<endl;
    while (true) {
        int cmd;
        cin>>cmd;
        if (cmd==1) {
            cout<<"Enter data"<<endl;
            int data;
            cin>>data;
            bh.insert(data);
        }
        else if (cmd==2) {
            int ans=bh.findMin();
            cout<<"Minimum value is "<<ans<<endl;
        }
        else if (cmd==3) {
            int ans=bh.extractMin();
            cout<<"Minimum value is "<<ans<<endl;
        }
        else if (cmd==4) {
            bh.print();
        }
        else if (cmd==5) {
            break;
        }
        else {
            cout<<"Invalid command!"<<endl;
        }
    }

    return 0;
}
