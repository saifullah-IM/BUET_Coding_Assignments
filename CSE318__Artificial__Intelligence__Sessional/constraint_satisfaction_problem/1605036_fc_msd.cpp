#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef pair <double, int> PDI;
typedef vector <vector <int>> VVI;


int node_count;
int fail_count;
int checkpoint = 1;
int N;
VVI original_square;
VVI current_square;
VVI domain_matrix;
vector <int> forward_degree;
int unasigned;
// vector <bool> assigned;

void preprocess(int N)
{
    unasigned = 0;
    current_square.clear();
    domain_matrix.clear();
    forward_degree.clear();
    // assigned.clear();
    // assigned.resize(N);
    // fill(assigned.begin(),assigned.end(),false);
}

// --------------- functions for FC + msd ---------------------------


void msd ()
{
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (original_square[i][j] != 0) continue;
            unasigned++;
            int var = i * N + j;
            int dom_size = 0;
            int degree = 2*N - 2;
            for (int k = 0; k < N; k++) if (original_square[i][k] != 0) {
                domain_matrix[var][original_square[i][k] - 1] += 1;
                degree--;
            }
            for (int k = 0; k < N; k++) if (original_square[k][j] != 0) {
                domain_matrix[var][original_square[k][j] - 1] += 1;
                degree--;
            }
            for (int k = 0; k < N; k++) if (domain_matrix[var][k] == 0) dom_size++;
            domain_matrix[var][N] = dom_size;
            forward_degree[var] = degree;

            // double ratio;
            
            // if (degree > 0) ratio = (dom_size * 1.0) / (degree * 1.0);
            // else ratio = 1e9;
            // domdeg_vector.push_back(make_pair(ratio,var));
        }
    }
    // sort(domdeg_vector.begin(),domdeg_vector.end());
    // cout << "SIZE " << domdeg_vector.size() << '\n';
    // for (auto it:domdeg_vector) {
    //     cout << it.first << ' ' << it.second << '\n';
    // }
}

bool forward_check (int var, int value, int add)
{
    bool res = true;
    int row = var / N;
    int col = var % N;
    for (int i = 0; i < N; i++) {
        int temp_var = row * N + i;
        if (temp_var == var) continue;
        domain_matrix[temp_var][value - 1] += add;
        //forward_degree[temp_var] -= add;
        assert(domain_matrix[temp_var][value - 1] >= 0);
        if (add == 1 && domain_matrix[temp_var][value - 1] == 1) domain_matrix[temp_var][N]--;
        if (add == -1 && domain_matrix[temp_var][value - 1] == 0) domain_matrix[temp_var][N]++;
        if (add == 1 && domain_matrix[temp_var][N] == 0) {
            if (current_square[row][i] == 0) res = false;
        }
    }
    for (int i = 0; i < N; i++) {
        int temp_var = i * N + col;
        if (temp_var == var) continue;
        domain_matrix[temp_var][value - 1] += add;
        //forward_degree[temp_var] -= add;
        assert(domain_matrix[temp_var][value - 1] >= 0);
        if (add == 1 && domain_matrix[temp_var][value - 1] == 1) domain_matrix[temp_var][N]--;
        if (add == -1 && domain_matrix[temp_var][value - 1] == 0) domain_matrix[temp_var][N]++;
        if (add == 1 && domain_matrix[temp_var][N] == 0) {
            if (current_square[i][col] == 0) res = false;
        }
    }
    return res;
}

bool solve_using_fc_msd(int idx)
{
    if (idx == unasigned) return true;

    if (node_count >= checkpoint) {
        cout << "check at " << checkpoint << '\n';
        cout << "fail_count " << fail_count << '\n';
        checkpoint *= 10;
    }
    int var = -1;
    int mfd = -1;

    for (int i = 0; i < N * N; i++) {
        if (current_square[i/N][i%N] != 0) continue;
        if (mfd < forward_degree[i]) {
            mfd = forward_degree[i];
            var = i;
        }
    }

    assert(var != -1);

    assert(current_square[var/N][var%N] == 0);
    int value = -1;
    for (int i = 0; i < N; i++) if (domain_matrix[var][i] == 0) {
        node_count++;
        value = i + 1;
        bool res = forward_check(var, value, 1);
        if (!res) {
            forward_check(var, value, -1);
            fail_count++;
            continue;
        }

        // cout << var << ' ' << value << '\n';
        // if (node_count >= 110) exit(0);

        current_square[var/N][var%N] = value;
        res = solve_using_fc_msd(idx+1);
        if (res) return true;
        else {
            //cout << "next input domain\n";
            current_square[var/N][var%N] = 0;
            forward_check(var, value, -1);
        }
    }
    if (value == -1) { cout << "ffffffffffffffffffffffffffffffffffff\n";
        fail_count++;
    }
    return false;
}

// ------------------ end of functions for FC + DOMDEG ---------------------



int main ()
{
    freopen ("d-10-01.txt","r",stdin);
    string str;

    getline(cin, str);
    str.erase(0,2);
    N = stoi(str);
    // cout << N << '\n';
    original_square.resize(N);

    getline(cin, str);
    getline(cin, str);

    for (int i = 0; i < N; i++) {
        getline(cin, str);
        stringstream ss(str);
        string token;
        while (getline(ss, token, ',')) {
            original_square[i].push_back(stoi(token));
        }
        assert(original_square[i].size() == N);
        // for (int v : original_square[i]) {
        //     cout << v << ' ';
        // }
        // cout << '\n';
    }
// -------------------- end of input ----------------------

// -------------------- call of FC + msd ---------------

    preprocess(N);
    forward_degree.resize(N);
    domain_matrix.resize(N*N);
    for (int i = 0; i < N*N; i++) {
        domain_matrix[i].resize(N + 1);
        fill(domain_matrix[i].begin(), domain_matrix[i].end(), 0);
    }
    msd();

    current_square = original_square;
    node_count = 1;
    fail_count = 0;
    solve_using_fc_msd(0);

    cout << "Node count " << node_count << '\n';
    cout << "Fail count " << fail_count << '\n';
    for (int i = 0 ; i < N; i++) {
        for (int j = 0; j < N; j++) cout << current_square[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}