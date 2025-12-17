#include <iostream>
#include <vector>

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
};


int main() {
    School rock;
    rock.addStudent({"John Doe", 15, 123456, 'A'});
    rock.addStudent({"Micheal Wilson", 17, 122345, 'B'});
    rock.addStudent({"Dean Johnson", 17, 125983, 'A'});
    rock.findByGrade('A');
}