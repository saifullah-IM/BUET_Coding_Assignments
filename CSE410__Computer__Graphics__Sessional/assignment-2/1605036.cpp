#include<bits/stdc++.h>
using namespace std;

class point {
public:
    double ara[4];
    point(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0) {
        ara[0] = x;
        ara[1] = y;
        ara[2] = z;
        ara[3] = w;
    }
    void setPoint(double arr[4]) {
        for (int i = 0; i < 4; i++)
            ara[i] = arr[i];
    }
    void pointNorm() {
        for (int i = 0; i < 4; i++)
            ara[i] /= ara[3];
    }
    double getX () {
        return ara[0];
    }
    double getY () {
        return ara[1];
    }
    double getZ () {
        return ara[2];
    }
    double getW () {
        return ara[3];
    }
};

class vector4D {
public:
    double ara[4];
    vector4D(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0) {
        ara[0] = x;
        ara[1] = y;
        ara[2] = z;
        ara[3] = w;
    }
    void setVector(double arr[4]) {
        for (int i = 0; i < 4; i++)
            ara[i] = arr[i];
    }
    void vecNorm() {
        double val = sqrt(ara[0]*ara[0] + ara[1]*ara[1] + ara[2]*ara[2]);
        for (int i = 0; i < 3; i++) ara[i] /= val;
    }
    double getX () {
        return ara[0];
    }
    double getY () {
        return ara[1];
    }
    double getZ () {
        return ara[2];
    }
    double getW () {
        return ara[3];
    }
    vector4D scalarProduct (double val) {
        vector4D ans;
        double temp[4];
        for (int i = 0; i < 3; i++)
            temp[i] = ara[i] * val;
        temp[3] = 1.0;
        ans.setVector(temp);
        return ans;
    }
    vector4D crossProduct (vector4D V) {
        vector4D ans;
        double temp[4];
        temp[0] = ara[1] * V.ara[2] - V.ara[1] * ara[2];
        temp[1] = ara[2] * V.ara[0] - V.ara[2] * ara[0];
        temp[2] = ara[0] * V.ara[1] - V.ara[0] * ara[1];
        temp[3] = 1.0;
        ans.setVector(temp);
        return ans;
    }
    vector4D add (vector4D V) {
        vector4D ans;
        double temp[4];
        for (int i = 0; i < 3; i++)
            temp[i] = ara[i] + V.ara[i];
        temp[3] = 1.0;
        ans.setVector(temp);
        return ans;
    }
    double dotProduct (vector4D V) {
        double ans = 0;
        for (int i = 0; i < 3; i++)
            ans += V.ara[i] * ara[i];
        return ans;
    }
};

class matrix {
public:
    double ara[4][4];
    matrix() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ara[i][j] = 0.0;
            }
        }
    }
    void setMatrix (double arr[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ara[i][j] = arr[i][j];
            }
        }
    }
    void setMatrix (matrix A) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ara[i][j] = A.ara[i][j];
            }
        }
    }
    matrix multiplyMatrix (matrix A) {
        double temp[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                double res = 0;
                for (int k = 0; k < 4; k++) {
                    res += ara[i][k] * A.ara[k][j];
                }
                temp[i][j] = res;
            }
        }
        matrix ans;
        ans.setMatrix(temp);
        return ans;
    }
    point multiplyPoint (point A) {
        double temp[4];
        for (int i = 0; i < 4; i++) {
            double res = 0;
            for (int j = 0; j < 4; j++) {
                res += ara[i][j] * A.ara[j];
            }
            temp[i] = res;
        }
        point ans;
        ans.setPoint(temp);
        return ans;
    }
    void print() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << ara[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

const double PI = acos(-1.0);

vector4D rotateVec (vector4D V, vector4D axis, double angle)
{
    angle = (angle * PI) / 180.0;
    double temp[4];
    temp[3] = 1.0;
    vector4D vec;
    vec = V.scalarProduct(cos(angle));
    vec = vec.add(axis.scalarProduct((1.0 - cos(angle) * axis.dotProduct(V))));
    vec = vec.add(axis.crossProduct(V).scalarProduct(sin(angle)));
    return vec;
}

int main ()
{
    freopen ("scene.txt","r",stdin);

    vector<vector<point>> stage1;
    vector<vector<point>> stage2;
    vector<vector<point>> stage3;

    stack <matrix> matStk;
    stack <int> szStk;

    matrix identity;
    for (int i = 0; i < 4; i++)
        identity.ara[i][i] = 1.0;

    matStk.push(identity);
    szStk.push(1);

    double fovY, aspectRatio, near, far;
    point eye, look, up;

    double arr[4];
    arr[3] = 1.0;

    for (int i = 0; i < 3; i++)
        cin >> arr[i];
    eye.setPoint(arr);

    for (int i = 0; i < 3; i++)
        cin >> arr[i];
    look.setPoint(arr);

    for (int i = 0; i < 3; i++)
        cin >> arr[i];
    up.setPoint(arr);

    cin >> fovY;
    cin >> aspectRatio;
    cin >> near;
    cin >> far;

    vector<point> triangle;
    triangle.resize(3);
    while(true) {
        string cmd;
        cin >> cmd;
        if (cmd == "triangle") {
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++)
                    cin >> arr[i];
                triangle[j].setPoint(arr);
            }

            matrix M = matStk.top();
            vector<point> newTriangle;
            newTriangle.resize(3);
            for (int i = 0; i < 3; i++) {
                newTriangle[i] = M.multiplyPoint(triangle[i]);
                newTriangle[i].pointNorm();
            }

            stage1.push_back(newTriangle);
        }
        else if (cmd == "translate") {
            matrix translateMatrix;
            for (int i = 0; i < 4; i++)
                translateMatrix.ara[i][i] = 1.0;
            for (int  i = 0; i < 3; i++)
                cin >> translateMatrix.ara[i][3];
            matStk.push(matStk.top().multiplyMatrix(translateMatrix));
        }
        else if (cmd == "scale") {
            matrix scaleMatrix;
            for (int  i = 0; i < 3; i++)
                cin >> scaleMatrix.ara[i][i];
            scaleMatrix.ara[3][3] = 1.0;
            matStk.push(matStk.top().multiplyMatrix(scaleMatrix));
        }
        else if (cmd == "rotate") {
            vector4D axis;
            double angle;
            cin >> angle;
            for (int i = 0; i < 3; i++) cin >> axis.ara[i];
            axis.vecNorm();

            vector4D V;
            double temp[4];
            for (int i = 0; i < 3; i++) temp[i] = 0.0;
            temp[3] = 1.0;

            vector4D C[3];
            V.setVector(temp);
            V.ara[0] = 1.0;
            C[0] = rotateVec(V, axis, angle);

            V.setVector(temp);
            V.ara[1] = 1.0;
            C[1] = rotateVec(V, axis, angle);

            V.setVector(temp);
            V.ara[2] = 1.0;
            C[2] = rotateVec(V, axis, angle);

            matrix rotateMatrix;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    rotateMatrix.ara[i][j] = C[j].ara[i];
                }
            }
            rotateMatrix.ara[3][3] = 1.0;

            matStk.push(matStk.top().multiplyMatrix(rotateMatrix));
            ///matStk.push(rotateMatrix.multiplyMatrix(matStk.top()));
        }
        else if (cmd == "push") {
            szStk.push(matStk.size());
        }
        else if (cmd == "pop") {
            int sz = szStk.top();
            szStk.pop();
            while (matStk.size() > sz)
                matStk.pop();
        }
        else if (cmd == "end") {
            break;
        }
        else {
            cout << "Invalid command\n";
            break;
        }
    }

    freopen ("stage1.txt","w",stdout);
    for (auto it: stage1) {
        for (auto pp: it) {
            for (int i = 0; i < 3; i++)
                cout << fixed << setprecision(6) << pp.ara[i] << ' ';
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
