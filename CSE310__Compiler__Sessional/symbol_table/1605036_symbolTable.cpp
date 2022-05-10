/*
Name: Saifullah Talukder
Student ID: 1605036
*/

#include<bits/stdc++.h>
using namespace std;

int bigMod (long long x,int n,int MOD)
{
    long long res=1;
    while (n>0) {
        if (n&1) res=(res*x)%MOD;
        n/=2;
        x=(x*x)%MOD;
    }
    return (int)res;
}

class SymbolInfo {
     string name,type;
     SymbolInfo* next;
public:
    SymbolInfo () {
        name=type="";
        next=nullptr;
    }
    void setName (string name) {
        this->name=name;
    }
    void setType (string type) {
        this->type=type;
    }
    string getName () {
        return name;
    }
    string getType () {
        return type;
    }
    void setNext (SymbolInfo* next) {
        this->next=next;
    }
    SymbolInfo* getNext () {
        return next;
    }
};

class ScopeTable {
    int bucketSize,ID;
    SymbolInfo** hashTable;
    ScopeTable* parentScope;
public:
    ScopeTable (int bucketSize,int ID,ScopeTable* parentScope) {
        this->ID=ID;
        this->bucketSize=bucketSize;
        this->parentScope=parentScope;
        hashTable=new(nothrow) SymbolInfo*[bucketSize];
        if (hashTable==nullptr) {
            cout<<"Hashtable memory allocation error"<<endl;
            exit(-1);
        }
        for (int i=0;i<bucketSize;i++) hashTable[i]=nullptr;
    }
    ~ScopeTable () {
        delete parentScope;
        parentScope=nullptr;
        for (int i=0;i<bucketSize;i++) {
            SymbolInfo* current=hashTable[i];
            SymbolInfo* prev;
            while (current!=nullptr) {
                prev=current;
                current=current->getNext();
                delete prev;
                prev=nullptr;
            }
        }
        delete[] hashTable;
        hashTable=nullptr;
    }

    int getID () {
        return ID;
    }
    void setParentScope (ScopeTable* parentScope) {
        this->parentScope=parentScope;
    }
    ScopeTable* getParentScope () {
        return parentScope;
    }

    int polynomialHash (string str) {
        long long ans=0;
        int base=257;
        for (int i=0;i<str.size();i++) {
            int val=(int)str[i];
            ans+=bigMod(base,i,bucketSize)*val;
            ans%=bucketSize;
        }
        return (int) ans;
    }

    SymbolInfo* search(string name,bool flag) {
        int pos=polynomialHash(name);
        SymbolInfo* current=hashTable[pos];
        int idx=0;
        while (current!=nullptr) {
            if (name==current->getName()) break;
            current=current->getNext();
            ++idx;
        }

        if (flag) {
            if (current!=nullptr) {
                cout<<"Found in ScopeTable#"<<ID<<" at position "<<pos<<", "<<idx<<endl;
            }
            else cout<<"Not found"<<endl;
        }
        return current;
    }

    bool insert (string name,string type) {
        SymbolInfo* newOne=search(name,false);
        if (newOne!=nullptr) {
            cout<<"Can not insert.Symbol already exists."<<endl;
            return false;
        }
        newOne=new SymbolInfo;
        newOne->setName(name);
        newOne->setType(type);

        int pos=polynomialHash(name);
        int idx=0;
        SymbolInfo* current=hashTable[pos];
        if (current==nullptr) hashTable[pos]=newOne;
        else {
            idx=1;
            while (current->getNext()!=nullptr) {
                current=current->getNext();
                ++idx;
            }
            current->setNext(newOne);
        }

        cout<<"Inserted in ScopeTable#"<<ID<<" at position "<<pos<<", "<<idx<<endl;

        return true;
    }

    bool remove (string name) {
        int pos=polynomialHash(name);
        SymbolInfo* current=hashTable[pos];
        SymbolInfo* prev=nullptr;
        int idx=0;
        while (current!=nullptr) {
            if (name==current->getName()) {
                if (prev==nullptr) {
                    hashTable[pos]=current->getNext();
                }
                else {
                    prev->setNext(current->getNext());
                }
                current->setNext(nullptr);
                delete current;
                current=nullptr;

                cout<<"Deleted entry at "<<pos<<", "<<idx<<" from current ScopeTable#"<<ID<<endl;
                return true;
            }
            prev=current;
            current=current->getNext();
            ++idx;
        }
        cout<<"Can not delete. Entry not found"<<endl;
        return false;
    }

    void printScopeTable () {
        cout<<endl<<"ScopeTable#"<<ID<<endl<<endl;
        for (int i=0;i<bucketSize;i++) {
            cout<<"Bucket position: "<<i<<" --->  ";
            SymbolInfo* current=hashTable[i];
            int idx=0;
            while (current!=nullptr) {
                cout<<"< "<<current->getName()<<" : "<<current->getType()<<" >"<<'\t';
                current=current->getNext();
                ++idx;
            }
            cout<<endl;
        }
        cout<<endl;
    }
};

class SymbolTable {
    int scopeCount,bucketSize;
    ScopeTable* currentScope;
    vector<ScopeTable*> scopeList;
public:
    SymbolTable (int bucketSize) {
        this->bucketSize=bucketSize;
        scopeCount=0;
        currentScope=nullptr;
        scopeList.clear();
    }

    void enterScope () {
        ++scopeCount;
        currentScope=new ScopeTable(bucketSize,scopeCount,currentScope);
        scopeList.push_back(currentScope);
        cout<<"ScopeTable with id "<<scopeCount<<" created"<<endl;
    }

    void exitScope () {
        ScopeTable* prev=currentScope;
        currentScope=currentScope->getParentScope();
        prev->setParentScope(nullptr);
        delete prev;
        prev=nullptr;
        scopeList.pop_back();
        cout<<"ScopeTable with id "<<scopeCount<<" removed"<<endl;
    }

    bool insert (string name,string type) {
        return currentScope->insert(name,type);
    }

    bool remove (string name) {
        return currentScope->remove(name);
    }

    SymbolInfo* search (string name) {
        ScopeTable* currentSearch=currentScope;
        while (currentSearch!=nullptr) {
            SymbolInfo* ans=currentSearch->search(name,true);
            if (ans!=nullptr) return ans;
            else currentSearch=currentSearch->getParentScope();
        }
        return nullptr;
    }

    void printCurrentScopeTable () {
        currentScope->printScopeTable();
    }

    void printAllScopeTable () {
        for (ScopeTable* it:scopeList) {
            it->printScopeTable();
        }
    }
};


int main ()
{
    freopen("input.txt","r",stdin);
    ///freopen("output.txt","w",stdout);
    int bucketSize;
    cin>>bucketSize;
    SymbolTable T(bucketSize);
    T.enterScope();

    string command;
    while (cin>>command) {
        if (command[0]=='I') {
            string name,type;
            cin>>name>>type;
            T.insert(name,type);
        }
        else if (command[0]=='L') {
            string name;
            cin>>name;
            T.search(name);
        }
        else if (command[0]=='D') {
            string name;
            cin>>name;
            T.remove(name);
        }
        else if (command[0]=='P') {
            string ch;
            cin>>ch;
            if (ch[0]=='A') T.printAllScopeTable();
            else if (ch[0]=='C') T.printCurrentScopeTable();
            else cout<<"Invalid command"<<endl;
        }
        else if (command[0]=='S') {
            T.enterScope();
        }
        else if (command[0]=='E') {
            T.exitScope();
        }
        else cout<<"Invalid command"<<endl;
    }

    return 0;
}
