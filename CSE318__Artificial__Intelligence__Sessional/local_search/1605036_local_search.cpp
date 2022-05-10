#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <queue>

using namespace std;

typedef pair <int, int> PII;
typedef pair <double, double> PDD;



class exam_scheduling {

private:

    vector < vector <int> > student_have_courses;
    vector < vector <int> > graph;
    vector <int> largest_degree_color_ID, dSatur_color_ID, largest_enrollment_color_ID;
    vector <int> kempe_largest_degree_color_ID, kempe_dSatur_color_ID, kempe_largest_enrollment_color_ID;
    vector <int> num_of_students;
    vector < vector <bool> > adj_matrix;
    vector <PII> degrees, enrollment;
    vector < unordered_set <int> > saturation_degree;
    int student_count, course_count;
    int largest_degree_color_count, dSatur_color_count, largest_enrollment_color_count;
    int penalty[7] = {-1000000,16,8,4,2,1,0};
    string file_name;

public:

    exam_scheduling () {
        student_count = course_count = 0;
    }

    exam_scheduling (string file_name) {
        set_file_name(file_name);
    }

    void set_file_name (string file_name) {
        this->file_name = file_name;
        get_course_file(file_name);
        get_student_file(file_name);
        sort_degrees();
        sort_enrollment();
        largest_degree_color_count = 0;
        dSatur_color_count = 0;
        largest_enrollment_color_count = 0;
    }

    string get_file_name () {
        return file_name;
    }

    int get_course_count() {
        return course_count;
    }

    int get_student_count() {
        return student_count;
    }


private:

    void get_course_file (string file_name) {
        course_count = 0;
        num_of_students.clear();
        vector <PII> course_info;
        int check = -1;

        string line;
        ifstream myfile (file_name + ".crs");
        if (myfile.is_open())
        {
            while (getline(myfile,line)) {
                vector <int> tokens; 
                stringstream line_stream(line); 
                
                string intermediate;
                
                while(getline(line_stream, intermediate, ' ')) { 
                    tokens.push_back(stoi(intermediate));
                } 
                
                assert(tokens.size() == 2);
                course_info.push_back(make_pair(tokens[0],tokens[1]));
                check = max(check,tokens[0]);
                course_count++;
            }
            myfile.close();
        }
        else cout << "Unable to open course file\n";

        assert(check == course_count);
        num_of_students.resize(course_count + 2);
        for (auto it : course_info) {
            num_of_students[it.first] = it.second;
        }

        return;
    }



    void get_student_file (string file_name) {
        student_count = 0;
        student_have_courses.clear();
        vector <int> current_student_courses;
        current_student_courses.push_back(-1);
        student_have_courses.push_back(current_student_courses);

        string line;
        ifstream myfile (file_name + ".stu");
        if (myfile.is_open())
        {
            while (getline(myfile,line)) {
                current_student_courses.clear();
                student_count++;

                stringstream line_stream(line); 
                string intermediate;
                
                while(getline(line_stream, intermediate, ' ')) { 
                    current_student_courses.push_back(stoi(intermediate));
                }

                student_have_courses.push_back(current_student_courses);
            }
            myfile.close();
        }
        else cout << "Unable to open student file\n";
        
        vector <bool> all_false(course_count + 2, false);
        adj_matrix.clear();
        adj_matrix.resize(course_count + 2);
        fill(adj_matrix.begin(),adj_matrix.end(),all_false);

        for (int i = 1; i <= student_count; i++) {
            int n = student_have_courses[i].size();
            for (int j = 0; j < n; j++) {
                int u = student_have_courses[i][j];
                for (int k = j + 1; k < n; k++) {
                    int v = student_have_courses[i][k];
                    adj_matrix[u][v] = adj_matrix[v][u] = true;
                }
            }
        }

        graph.clear();
        graph.resize(course_count + 2);
        for (int i = 1; i <= course_count; i++) {
            for (int j = i + 1; j <= course_count; j++) {
                if (adj_matrix[i][j]) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        
        return;
    }



    void sort_degrees () {
        degrees.clear();
        degrees.resize(course_count + 2);
        for (int i = 1; i <= course_count; i++) {
            degrees[i - 1] = make_pair(-1 * graph[i].size(), i);
        }
        sort(degrees.begin(), degrees.begin() + course_count);
        for (int i = 0; i < course_count; i++) {
            degrees[i].first *= -1;
        }
    }



    void sort_enrollment() {
        enrollment.clear();
        enrollment.resize(course_count + 2);
        for (int i = 1; i <= course_count; i++) {
            enrollment[i - 1] = make_pair(-1 * num_of_students[i], i);
        }
        sort(enrollment.begin(), enrollment.begin() + course_count);
        for (int i = 0; i < course_count; i++) {
            enrollment[i].first *= -1;
        }
    }



    PDD calculate_penalty (vector <int>& color_ID, bool all_pair = false) {
        PII total_penalties = make_pair(0,0);
        PDD res = make_pair(0.0,0.0);
        for (int i = 1; i <= student_count; i++) {
            int n = student_have_courses[i].size();
            vector <int> exam_dates;
            for (int j = 0; j < n; j++) {
                int u = student_have_courses[i][j];
                if (all_pair) for (int k = j + 1; k < n; k++) {
                    int v = student_have_courses[i][k];
                    int diff = fabs(color_ID[u] - color_ID[v]);
                    if (diff >= 6) continue;
                    assert(diff != 0);
                    total_penalties.first += penalty[diff];
                }
                exam_dates.push_back(color_ID[u]);
            }
            sort(exam_dates.begin(),exam_dates.end());
            for (int j = 1; j < n; j++) {
                int u = exam_dates[j];
                int v = exam_dates[j - 1];
                int diff = fabs(u - v);
                if (diff >= 6) continue;
                assert(diff != 0);
                total_penalties.second += penalty[diff];
            }
        }

        res.first = total_penalties.first / (student_count * 1.0);
        res.second = total_penalties.second / (student_count * 1.0);

        return res;
    }



    bool kempe_chain_interchange (vector <int>& color_ID) {
        int first_vertex;
        while(true) {
            first_vertex = rand() % course_count + 1;
            if (!graph[first_vertex].empty()) break;
        }
        int second_vertex = rand() % graph[first_vertex].size();
        second_vertex = graph[first_vertex][second_vertex];

        int first_color = color_ID[first_vertex];
        int second_color = color_ID[second_vertex];

        vector <bool> visited (course_count + 2, false);
        vector <int> to_interchange;
        queue <int> myQ;
        myQ.push(first_vertex);

        while (!myQ.empty()) {
            int node = myQ.front();
            myQ.pop();
            if (visited[node]) continue;
            visited[node] = true;
            to_interchange.push_back(node);
            int current_color = color_ID[node];
            int next_color;
            if (current_color == first_color) next_color = second_color;
            else {
                assert(current_color == second_color);
                next_color = first_color;
            }
            for (int next_node : graph[node]) {
                if (color_ID[next_node] != next_color || visited[next_node]) continue;
                myQ.push(next_node); 
            }
        }

        vector <int> new_color_ID(color_ID);
        for (int node : to_interchange) {
            if (color_ID[node] == first_color) new_color_ID[node] = second_color;
            else {
                assert(color_ID[node] == second_color);
                new_color_ID[node] = first_color;
            }
        }

        bool ans;
        PDD prev_penalty = calculate_penalty(color_ID);
        PDD new_penalty = calculate_penalty(new_color_ID);
        if (new_penalty.second < prev_penalty.second) {
            ans = true;
            color_ID = new_color_ID;
        }
        else ans = false;

        return ans;
    }



    void kempe_chain_hill_climb (vector <int>& color_ID, int iteration_count) {
        while(iteration_count--) {
            kempe_chain_interchange(color_ID);
        }
    }


public:

    void solve_largest_degree () {
        if (course_count == 0 || student_count == 0) {
            cout << "No course and student information has been provided yet.\n";
            return;
        }

        largest_degree_color_count = 0;
        largest_degree_color_ID.clear();
        largest_degree_color_ID.resize(course_count + 2);
        fill(largest_degree_color_ID.begin(),largest_degree_color_ID.end(),0);

        string output_file_name = file_name + "_largest_degree.sol";
        ofstream myfile (output_file_name);
        if (!myfile.is_open()) cout << "Unable to open " + output_file_name + "\n";

        for (int i = 0; i < course_count; i++) {
            vector <bool> colors_used (largest_degree_color_count + 1, false);
            for (int v : graph[degrees[i].second]) {
                if (largest_degree_color_ID[v] > 0) colors_used[largest_degree_color_ID[v]] = true;
            }

            bool done = false;
            for (int j = 1; j <= largest_degree_color_count; j++) {
                if (!colors_used[j]) {
                    done = true;
                    largest_degree_color_ID[degrees[i].second] = j;
                    break;
                }
            }
            if (!done) {
                largest_degree_color_ID[degrees[i].second] = largest_degree_color_count + 1;
                largest_degree_color_count += 1;
            }

            myfile << setw(4) << degrees[i].second << '\t' << setw(4) << largest_degree_color_ID[degrees[i].second] << '\n';
        }

        myfile.close();

        PDD penalties = calculate_penalty(largest_degree_color_ID, true);
        cout << "Color count = " << largest_degree_color_count << '\n';
        cout << "Penalties(all possible pairs) : ";
        cout << fixed << setprecision(6) << penalties.first << '\n';
        cout << "Penalties(consequtive pairs) : ";
        cout << fixed << setprecision(6) << penalties.second << '\n';


        return;
    }



    void solve_dSatur () {
        if (course_count == 0 || student_count == 0) {
            cout << "No course and student information has been provided yet.\n";
            return;
        }

        dSatur_color_ID.clear();
        dSatur_color_ID.resize(course_count + 2);
        fill(dSatur_color_ID.begin(),dSatur_color_ID.end(),0);

        saturation_degree.clear();
        saturation_degree.resize(course_count + 2);

        PII largest_degree_node = degrees[0];

        dSatur_color_count = 1;
        dSatur_color_ID[largest_degree_node.second] = 1;
        for (int node : graph[largest_degree_node.second]) {
            saturation_degree[node].insert(1);
        }

        string output_file_name = file_name + "_dSatur.sol";
        ofstream myfile (output_file_name);
        if (!myfile.is_open()) cout << "Unable to open " + output_file_name + "\n";
        myfile << setw(4) << largest_degree_node.second << '\t' << setw(4) << 1 << '\n';

        int colored_nodes = 1;
        int check = 1;
        while (colored_nodes < course_count) {
            PII largest_degree_node = make_pair(0,0);
            PII largest_saturation_node = make_pair(0,0);
            for (int i = 1; i <= course_count; i++) {
                if (dSatur_color_ID[i] > 0) continue;
                if (saturation_degree[i].size() == largest_saturation_node.first) {
                    if (graph[i].size() > largest_degree_node.first) {
                        largest_saturation_node = make_pair(saturation_degree[i].size(), i);
                        largest_degree_node = make_pair(graph[i].size(), i);
                    }
                }
                else if (saturation_degree[i].size() > largest_saturation_node.first) {
                    largest_saturation_node = make_pair(saturation_degree[i].size(), i);
                    largest_degree_node = make_pair(graph[i].size(), i);
                }
            }

            vector <bool> colors_used (dSatur_color_count + 1, false);
            for (int v : graph[largest_saturation_node.second]) {
                if (dSatur_color_ID[v] > 0) colors_used[dSatur_color_ID[v]] = true;
            }

            bool done = false;
            for (int j = 1; j <= dSatur_color_count; j++) {
                if (!colors_used[j]) {
                    done = true;
                    dSatur_color_ID[largest_saturation_node.second] = j;
                    colored_nodes++;
                    break;
                }
            }
            if (!done) {
                dSatur_color_ID[largest_saturation_node.second] = dSatur_color_count + 1;
                dSatur_color_count += 1;
                colored_nodes++;
            }
            for (int node : graph[largest_saturation_node.second]) {
                saturation_degree[node].insert(dSatur_color_ID[largest_saturation_node.second]);
            }

            myfile << setw(4) << largest_saturation_node.second << '\t' << setw(4) << dSatur_color_ID[largest_saturation_node.second] << '\n';

            check++;
        }

        assert(check == course_count);
        assert(course_count == colored_nodes);

        myfile.close();

        PDD penalties = calculate_penalty(dSatur_color_ID, true);
        cout << "Color count = " << dSatur_color_count << '\n';
        cout << "Penalties(all possible pairs) : ";
        cout << fixed << setprecision(6) << penalties.first << '\n';
        cout << "Penalties(consequtive pairs) : ";
        cout << fixed << setprecision(6) << penalties.second << '\n';

        return;
    }




    void solve_largest_enrollment () {
        if (course_count == 0 || student_count == 0) {
            cout << "No course and student information has been provided yet.\n";
            return;
        }

        largest_enrollment_color_count = 0;
        largest_enrollment_color_ID.clear();
        largest_enrollment_color_ID.resize(course_count + 2);
        fill(largest_enrollment_color_ID.begin(),largest_enrollment_color_ID.end(),0);

        string output_file_name = file_name + "_largest_enrollment.sol";
        ofstream myfile (output_file_name);
        if (!myfile.is_open()) cout << "Unable to open " + output_file_name + "\n";

        for (int i = 0; i < course_count; i++) {
            vector <bool> colors_used (largest_enrollment_color_count + 1, false);
            for (int v : graph[enrollment[i].second]) {
                if (largest_enrollment_color_ID[v] > 0) colors_used[largest_enrollment_color_ID[v]] = true;
            }

            bool done = false;
            for (int j = 1; j <= largest_enrollment_color_count; j++) {
                if (!colors_used[j]) {
                    done = true;
                    largest_enrollment_color_ID[enrollment[i].second] = j;
                    break;
                }
            }
            if (!done) {
                largest_enrollment_color_ID[enrollment[i].second] = largest_enrollment_color_count + 1;
                largest_enrollment_color_count += 1;
            }
            myfile << setw(4) << enrollment[i].second << '\t' << setw(4) << largest_enrollment_color_ID[enrollment[i].second] << '\n';
        }

        myfile.close();

        PDD penalties = calculate_penalty(largest_enrollment_color_ID, true);
        cout << "Color count = " << largest_enrollment_color_count << '\n';
        cout << "Penalties(all possible pairs) : ";
        cout << fixed << setprecision(6) << penalties.first << '\n';
        cout << "Penalties(consequtive pairs) : ";
        cout << fixed << setprecision(6) << penalties.second << '\n';

        return;
    }



    void solve_kempe_largest_degree(int iteration_count = 1000) {
        if (course_count == 0 || student_count == 0) {
            cout << "No course and student information has been provided yet.\n";
            return;
        }

        if (largest_degree_color_count == 0) {
            solve_largest_degree();
        }

        kempe_largest_degree_color_ID = largest_degree_color_ID;
        kempe_chain_hill_climb(kempe_largest_degree_color_ID, iteration_count);

        PDD penalties = calculate_penalty(kempe_largest_degree_color_ID, true);
        cout << "Color count = " << largest_degree_color_count << '\n';
        cout << "Penalties(all possible pairs) : ";
        cout << fixed << setprecision(6) << penalties.first << '\n';
        cout << "Penalties(consequtive pairs) : ";
        cout << fixed << setprecision(6) << penalties.second << '\n';

        return;
    }



    void solve_kempe_dSatur(int iteration_count = 1000) {
        if (course_count == 0 || student_count == 0) {
            cout << "No course and student information has been provided yet.\n";
            return;
        }

        if (dSatur_color_count == 0) {
            solve_dSatur();
        }

        kempe_dSatur_color_ID = dSatur_color_ID;
        kempe_chain_hill_climb(kempe_dSatur_color_ID, iteration_count);

        PDD penalties = calculate_penalty(kempe_dSatur_color_ID, true);
        cout << "Color count = " << dSatur_color_count << '\n';
        cout << "Penalties(all possible pairs) : ";
        cout << fixed << setprecision(6) << penalties.first << '\n';
        cout << "Penalties(consequtive pairs) : ";
        cout << fixed << setprecision(6) << penalties.second << '\n';

        return;
    } 



    void solve_kempe_largest_enrollment(int iteration_count = 1000) {
        if (course_count == 0 || student_count == 0) {
            cout << "No course and student information has been provided yet.\n";
            return;
        }

        if (largest_enrollment_color_count == 0) {
            solve_largest_enrollment();
        }

        kempe_largest_enrollment_color_ID = largest_enrollment_color_ID;
        kempe_chain_hill_climb(kempe_largest_enrollment_color_ID, iteration_count);

        PDD penalties = calculate_penalty(kempe_largest_enrollment_color_ID, true);
        cout << "Color count = " << largest_enrollment_color_count << '\n';
        cout << "Penalties(all possible pairs) : ";
        cout << fixed << setprecision(6) << penalties.first << '\n';
        cout << "Penalties(consequtive pairs) : ";
        cout << fixed << setprecision(6) << penalties.second << '\n';

        return;
    }
};




void get_test_set (vector <exam_scheduling>& test_set) {
    string line;
    ifstream myfile ("test_set.txt");
    if (myfile.is_open())
    {
        while (getline(myfile,line)) {
            stringstream line_stream(line);   
            string intermediate;
                
            while(getline(line_stream, intermediate, ' ')) { 
                exam_scheduling new_test(intermediate);
                test_set.push_back(new_test);
            } 
        }
    }
    else cout << "Unable to open test_set file\n";

    return;
}



void test_all() {
    vector <exam_scheduling> test_set;
    get_test_set(test_set);
    cout <<'\n';
    for (auto it : test_set) {
        cout << "----------------------------  Solutions for " << it.get_file_name() << " file.\n";
        cout << "Course count : " << it.get_course_count() << '\n';
        cout << "Student count : " << it.get_student_count() << "\n\n";

        cout << "Largest degree\n\n";
        it.solve_largest_degree();
        cout << '\n';
        cout << "Largest degree with kempe\n\n";
        it.solve_kempe_largest_degree();
        cout << '\n';

        cout << "Degree of saturaion\n\n";
        it.solve_dSatur();
        cout << '\n';
        cout << "Degree of saturaion with kempe\n\n";
        it.solve_kempe_dSatur();
        cout << '\n';

        cout << "Largest enrollment\n\n";
        it.solve_largest_enrollment();
        cout << '\n';
        cout << "Largest enrollment with kempe\n\n";
        it.solve_kempe_largest_enrollment();
        cout << '\n';
    }

    return;
}


int main ()
{
    // exam_scheduling test("yor-f-83");
    // test.solve_kempe_dSatur();
    test_all();

    return 0;
}
