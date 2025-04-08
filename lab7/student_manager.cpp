#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Student {
    int id;
    string firstName;
    string lastName;
    double score;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, id, firstName, lastName, score);

    string getGrade() const {
        if (score >= 90) {
            return "5";
        } else if (score >= 80) {
            return "4+";
        } else if (score >= 70) {
            return "4";
        } else if (score >= 60) {
            return "3+";
        } else if (score >= 50) {
            return "3";
        } else {
            return "2";
        }
    }
};

void loadStudents(vector<Student>& students, const string& filename) {
    ifstream i(filename);

    if (!i) {
        cerr << "Nie mozna otworzyc pliku: " << filename;
        return;
    }

    json data = json::parse(i);
    students = data.get<vector<Student>>();
}

void saveStudents(vector<Student>& students, const string& filename) {
    ofstream i(filename);

    if (!i) {
        cerr << "Nie mozna zapisac do pliku: " << filename;
        return;
    }

    json j = students;
    i << j.dump(4);
}

void printStudents(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << student.id << " | " 
                  << student.firstName << " " << student.lastName << " | "
                  << student.score << "% | " << student.getGrade() << endl;
    }
}

double calculateAverageStudentScore(const vector<Student>& students) {
    double sum = accumulate(students.begin(), students.end(), 0.0, [](double total, const Student& student) {
        return total + student.score;
    });
    return sum / students.size();
}

void findStudentById(const vector<Student>& students, int id) {
    auto it = find_if(students.begin(), students.end(), [id](const Student& student) {
        return student.id == id;
    });

    if (it != students.end()) {
        const Student& student = *it;
        cout << student.id << " | "
                  << student.firstName << " " << student.lastName << " | "
                  << student.score << "% | " << student.getGrade() << endl;
    } else {
        cout << "Student with ID " << id << " not found!" << endl;
    }
}

void countPassFail(const vector<Student>& students) {
    int passed = count_if(students.begin(), students.end(),[](const Student& student) {
        return student.score >= 50;
    });

    int failed = students.size() - passed;

    cout << "Passed: " << passed << ", Failed: " << failed << endl;
}

void removeFailingStudents(vector<Student>& students) {
    students.erase(remove_if(students.begin(), students.end(), [](const Student& student) {
        return student.score < 50;
    }),
    students.end());
}

int main() {
    vector<Student> students;

    loadStudents(students, "students.json");

    cout << "## Lista studentów ##" << endl;
    printStudents(students);

    cout << "## Średni wynik ##" << endl;
    cout << "Średnia: " << calculateAverageStudentScore(students);

    cout << "## Zaliczenia ##" << endl;
    countPassFail(students);

    removeFailingStudents(students);

    cout << "## Po usunięciu niezdanych ##" << endl;
    printStudents(students);

    int studentId;
    while (true) {
        cout << "\nPodaj ID studenta: ";
        cin >> studentId;

        if (studentId == 0) {
            break;
        }

        findStudentById(students, studentId);
    }

    saveStudents(students, "students.json");

    return 0;
}