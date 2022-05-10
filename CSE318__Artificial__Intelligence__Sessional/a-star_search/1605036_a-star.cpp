#include <iostream>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <stack>

using namespace std;

class Grid
{
public:
    int ara[4][4];
    bool even;
    int disp,man;
    int x0,y0;

    Grid () {
        memset(ara,0,sizeof(ara));
        even=false;
        disp=man=-1;
        x0=y0=-1;
    }

    bool solvable () {
        int list[16];
        int count=0;

        if (y0%2==0) even=false;
        else even=true;

        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) list[4*i+j]=ara[i][j];
        }
        for (int i=0;i<16;i++) {
            if (list[i]==0) continue;
            for (int j=i+1;j<16;j++) {
                if (list[j]==0) continue;
                if (list[i]>list[j]) count+=1;
            }
        }

        if (even & count%2==0) return true;
        else if (!even & count%2==1) return true;
        else return false;
    }

    void manhattan () {
        int ans=0;
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                if (ara[i][j]==0) continue;
                int x,y,num;
                num=ara[i][j]-1;
                x=num%4;
                y=num/4;
                ans+=abs(y-i)+abs(x-j);
            }
        }
        man=ans;
    }

    void displacement () {
        int ans=0;
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                if (ara[i][j]==0) continue;
                int num=ara[i][j];
                int pos=4*i+j+1;
                if (pos!=num) ans+=1;
            }
        }
        disp=ans;
    }

    void setup() {
        manhattan();
        displacement();
    }

    void printGrid() {
        cout<<endl;
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                cout<<ara[i][j]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }
    // end of grid class
};
typedef pair<Grid,int> PGI;

//compare functions for sorting

bool compareman (PGI A,PGI B) {
    assert (A.first.man!=-1 && B.first.man!=-1);
    return A.first.man<B.first.man;
}

bool comparedisp (PGI A,PGI B) {
    assert (A.first.disp!=-1 && B.first.disp!=-1);
    return A.first.disp<B.first.disp;
}


//global variables
int nodeCount=0;
stack<Grid> solution;
const string moves = "LRUD";
int arax[]={-1,1,0,0};
int aray[]={0,0,-1,1};
int invmove[]={1,0,3,2};



// solving using displacement heuristic
int call=0,cycle=0;
bool solveDisplacement (int prevMove, Grid currentGrid) {
    if (currentGrid.disp==0) return true;

    vector<PGI> toGo;

    for (int i=0;i<4;i++) {
        if (invmove[i]==prevMove) continue;
        int prev_x=currentGrid.x0;
        int prev_y=currentGrid.y0;
        int new_x=prev_x+arax[i];
        int new_y=prev_y+aray[i];
        if (new_x>=0 && new_x<4 && new_y>=0 && new_y<4) {
            Grid newGrid;
            for (int j=0;j<4;j++) {
                for (int k=0;k<4;k++) {
                    newGrid.ara[j][k]=currentGrid.ara[j][k];
                }
            }
            swap(newGrid.ara[new_y][new_x],newGrid.ara[prev_y][prev_x]);
            newGrid.x0=new_x;
            newGrid.y0=new_y;
            newGrid.setup();
            toGo.push_back(make_pair(newGrid,i));
        }
    }

    sort(toGo.begin(),toGo.end(),comparedisp);
    nodeCount+=toGo.size();

    for (int i=0;i<toGo.size();i++) {
        bool temp=solveDisplacement(toGo[i].second,toGo[i].first);
        if (temp) {
            solution.push(toGo[i].first);
            return true;
        }
    }

    return false;
}


// solving using manhattan heuristic

bool solveManhattan (int prevMove, Grid currentGrid) {
    if (currentGrid.man==0) return true;

    vector<PGI> toGo;

    for (int i=0;i<4;i++) {
        if (invmove[i]==prevMove) continue;
        int prev_x=currentGrid.x0;
        int prev_y=currentGrid.y0;
        int new_x=prev_x+arax[i];
        int new_y=prev_y+aray[i];
        if (new_x>=0 && new_x<4 && new_y>=0 && new_y<4) {
            Grid newGrid;
            for (int j=0;j<4;j++) {
                for (int k=0;k<4;k++) {
                    newGrid.ara[j][k]=currentGrid.ara[j][k];
                }
            }
            swap(newGrid.ara[new_y][new_x],newGrid.ara[prev_y][prev_x]);
            newGrid.x0=new_x;
            newGrid.y0=new_y;
            newGrid.setup();
            toGo.push_back(make_pair(newGrid,i));
        }
    }

    sort(toGo.begin(),toGo.end(),compareman);
    nodeCount+=toGo.size();

    for (int i=0;i<toGo.size();i++) {
        bool temp=solveManhattan(toGo[i].second,toGo[i].first);
        if (temp) {
            solution.push(toGo[i].first);
            return true;
        }
    }

    return false;
}


int main ()
{
    int N;
    cin>>N;
    for (int i=1;i<=16;i++) {
        int x;
        cin>>x;
        assert(x==i%16);
    }
    N--;
    while(N--) {
        Grid original;

        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                int num;
                cin>>num;
                original.ara[i][j]=num;
                if (num==0) {
                    original.x0=j;
                    original.y0=i;
                }
            }
        }

        if (original.solvable()) {
            int answer;

            nodeCount=0;
            solveDisplacement(-1,original);
            solution.push(original);
            answer=solution.size();

            cout<<"Displacement Solution"<<endl;
            cout<<"Path Cost: "<<answer<<endl;
            cout<<"Nodes visited: "<<nodeCount<<endl<<endl;
            while(!solution.empty()) {
                Grid currentGrid=solution.top();
                solution.pop();
                currentGrid.printGrid();
            }


            nodeCount=0;
            solveManhattan(-1,original);
            solution.push(original);
            answer=solution.size();

            cout<<endl<<"Manhattan Distance Solution"<<endl;
            cout<<"Path Cost: "<<answer<<endl;
            cout<<"Nodes visited: "<<nodeCount<<endl<<endl;
            while(!solution.empty()) {
                Grid currentGrid=solution.top();
                solution.pop();
                currentGrid.printGrid();
            }
        }
        else {
            cout<<endl<<"Not Solvable"<<endl<<endl;
        }
    }

    return 0;
}