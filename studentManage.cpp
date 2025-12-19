#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Student {
    string name;
    int age;
    int id;
    char grade;

    friend ostream& operator<<(ostream& os, Student& s) {
        os << "------------------\n";
        os << s.name << endl;
        os << "------------------\n";
        os << "Age: " << s.age << endl;
        os << "ID: " << s.id << endl;
        os << "Overall Grade: " << s.grade << endl;

        return os;
    }
};

class School {
    private:
        vector<Student> students;
    public:
        void addStudent(Student s) {students.push_back(s);}
        void findById(int id_num) {
            for (int i = 0; i < students.size(); i++) {
                if (students[i].id == id_num) {
                    cout << students[i];
                    return;
                }
            }

            cerr << "Could not find student by that ID\n";
            return;
        }
        void findByGrade(char g) {
            for (int i = 0; i < students.size(); i++) {
                if (students[i].grade == g) {
                    cout << students[i];
                    cout << "=======================\n";
                }
            }
        }
        void removeStudent(int id_num) {
            for (int i{}; i < students.size(); i++) if (students[i].id == id_num) {students.erase(students.begin() + i); break;}
        }
        void listStudents() {for (auto s : students) cout << s << endl;}
};


int main() {
    School rock;
    rock.addStudent({"John Doe", 15, 123456, 'A'});
    rock.addStudent({"Micheal Wilson", 17, 122345, 'B'});
    rock.addStudent({"Dean Johnson", 17, 125983, 'A'});
    

    while (true) {
        string input, token;
        vector<string> args;

        cout << "> ";
        restart:;
        getline (cin, input);
        istringstream stream(input);
        while (getline(stream, token, ' ')) args.push_back(token);
        if (args.size() == 0) goto restart;

        if (args[0] == "findById" || args[0] == "fbi") {
            if (args.size() == 1) {
                cout << "id> ";
                int id; cin >> id;
                rock.findById(id);
            } else rock.findById(stoi(args[1]));
        } else if (args[0] == "findByGrade" || args[0] == "fbg") {
            if (args.size() == 1) {
                cout << "grade> ";
                char grade; cin >> grade;
                rock.findByGrade(grade);
            } else rock.findByGrade(args[1][0]);
        } else if (args[0] == "newStudent" || args[0] == "ns") {
            Student s{};
            
            cout << "name> ";
            getline (cin, s.name);

            cout << "age> ";
            cin >> s.age;

            cout << "id> ";
            cin >> s.id;

            cout << "grade> ";
            cin >> s.grade;
            
            rock.addStudent(s);
        } else if (args[0] == "removeStudent" || args[0] == "rms") {
            if (args.size() == 1) {
                cout << "id> ";
                int id; cin >> id;
                rock.removeStudent(id);
            } else rock.removeStudent(stoi(args[1]));
        } else if (args[0] == "q") {break;} else if (args[0] == "ls") {rock.listStudents();}
    }
}