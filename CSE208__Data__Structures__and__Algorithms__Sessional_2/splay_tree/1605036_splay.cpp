#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int COUNT=6;

class node {
public:
    node *L;
    node *R;
    node *P;
    int data;
    node () {
        L=R=P=NULL;
        data=0;
    }
};

class splayTree {
    node *root;
public:
    splayTree () {
        root=NULL;
    }
    void rightRotate (node *Y) {
        node *X=Y->L;
        node *U=X->R;
        node *T=Y->P;

        if (T!=NULL) {
            if (T->R==Y) T->R=X;
            else T->L=X;
        }
        if (U!=NULL) U->P=Y;

        X->P=T;
        Y->L=U;
        X->R=Y;
        Y->P=X;
    }
    void leftRotate(node *Y) {
        node *X=Y->R;
        node *U=X->L;
        node *T=Y->P;

        if (T!=NULL) {
            if (T->R==Y) T->R=X;
            else T->L=X;
        }
        if (U!=NULL) U->P=Y;

        X->P=T;
        Y->R=U;
        X->L=Y;
        Y->P=X;
    }
    void splay (node *X) {
        while (true) {
            node *Y=X->P;
            if (Y==NULL) break;

            node *Z=Y->P;
            if (Z==NULL) { ///Zig. One single rotation is enough.
                if (Y->L==X) rightRotate(Y);
                else leftRotate(Y);
            }
            else if (Z->L==Y) { ///Need a double rotation.
                if (Y->L==X) { ///ZigZig.
                    rightRotate(Z);
                    rightRotate(Y);
                }
                else { ///ZigZag.
                    leftRotate(Y);
                    rightRotate(Z);
                }
            }
            else {
                if (Y->R==X) { ///ZigZig.
                    leftRotate(Z);
                    leftRotate(Y);
                }
                else { ///ZigZag.
                    rightRotate(Y);
                    leftRotate(Z);
                }
            }
        }
        root=X;
    }
    node * search (int data) {
        if (root==NULL) return NULL;
        node *X=root;

        while (true) {
            if (X->data==data) break;
            else if (data<X->data) {
                if (X->L!=NULL) X=X->L;
                else break;
            }
            else {
                if (X->R!=NULL) X=X->R;
                else break;
            }
        }

        splay(X);
        if (X->data==data) return X;
        else return NULL;
    }
    void insert (int data) {
        if (root==NULL) {
            root=new node;
            root->data=data;
            return;
        }

        node *X=root;
        while (true) {
            if (data<X->data) {
                if (X->L!=NULL) X=X->L;
                else {
                    X->L=new node;
                    X->L->P=X;
                    X->L->data=data;
                    X=X->L;
                    break;
                }
            }
            else {
                if (X->R!=NULL) X=X->R;
                else {
                    X->R=new node;
                    X->R->P=X;
                    X->R->data=data;
                    X=X->R;
                    break;
                }
            }
        }
        splay(X);
    }
    void join (node *L, node *R) {
        node *X;
        X=L;
        while (X->R!=NULL) X=X->R;
        if (X==L) {
            root=X;
            root->R=R;
            R->P=root;
            root->P=NULL;
        }
        else {
            X->P->R=NULL;
            root=X;
            root->R=R;
            root->L=L;
            R->P=L->P=root;
            root->P=NULL;
        }
    }
    bool erase (int data) {
        node *X=search(data);
        if (X==NULL) return false;

        node *U=X->L;
        node *V=X->R;
        if (U==NULL) {
            root=V;
            root->P=NULL;
        }
        else if (V==NULL) {
            root=U;
            root->P=NULL;
        }
        else join (U,V);

        delete(X);
        return true;
    }
    void print2DUtil(node *X, int space) {
        if (X==NULL) return;
        space+=COUNT;
        print2DUtil(X->R,space);
        printf("\n");
        for (int i=COUNT;i<space;i++) printf(" ");
        printf("%d\n",X->data);
        print2DUtil(X->L,space);
    }
    void print () {
        print2DUtil(root,0);
    }
};
int main ()
{
    splayTree T;
    while (true) {
        cout<<"1.Insert  2.Search   3.Delete   4.Print   5.Exit"<<endl;
        int cmd;
        cin>>cmd;
        if (cmd==1) {
            cout<<"Enter Number:"<<endl;
            int data;
            cin>>data;
            T.insert(data);
        }
        else if (cmd==2) {
            cout<<"Enter Number:"<<endl;
            int data;
            cin>>data;
            node *X=T.search(data);
            if (X==NULL) cout<<"Not Found"<<endl;
            else cout<<"Found"<<endl;
        }
        else if (cmd==3) {
            cout<<"Enter Number:"<<endl;
            int data;
            cin>>data;
            T.erase(data);
        }
        else if (cmd==4) {
            T.print();
        }
        else break;
    }

    return 0;
}
