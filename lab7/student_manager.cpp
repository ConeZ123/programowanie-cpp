#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;

struct Student {
    int id;
    std::string firstName;
    std::string lastName;
    double score;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, id, firstName, lastName, score);

    std::string getGrade() const {
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

void loadStudents(std::vector<Student>& students, const std::string& filename) {
    std::ifstream i(filename);

    if (!i) {
        std::cerr << "Nie mozna otworzyc pliku: " << filename;
        return;
    }

    json data = json::parse(i);
    students = data.get<std::vector<Student>>();
}

void saveStudents(std::vector<Student>& students, const std::string& filename) {
    std::ofstream i(filename);

    if (!i) {
        std::cerr << "Nie mozna zapisac do pliku: " << filename;
        return;
    }

    json j = students;
    i << j.dump(4);
}

void printStudents(const std::vector<Student>& students) {
    for (const auto& student : students) {
        std::cout << student.id << " | " 
                  << student.firstName << " " << student.lastName << " | "
                  << student.score << "% | " << student.getGrade() << std::endl;
    }
}

double calculateAverageStudentScore(const std::vector<Student>& students) {
    double sum = std::accumulate(students.begin(), students.end(), 0.0, [](double total, const Student& student) {
        return total + student.score;
    });
    return sum / students.size();
}

void findStudentById(const std::vector<Student>& students, int id) {
    auto it = std::find_if(students.begin(), students.end(), [id](const Student& student) {
        return student.id == id;
    });

    if (it != students.end()) {
        const Student& student = *it;
        std::cout << student.id << " | "
                  << student.firstName << " " << student.lastName << " | "
                  << student.score << "% | " << student.getGrade() << std::endl;
    } else {
        std::cout << "Student with ID " << id << " not found!" << std::endl;
    }
}

void countPassFail(const std::vector<Student>& students) {
    int passed = std::count_if(students.begin(), students.end(),[](const Student& student) {
        return student.score >= 50;
    });

    int failed = students.size() - passed;

    std::cout << "Passed: " << passed << ", Failed: " << failed << std::endl;
}

void removeFailingStudents(std::vector<Student>& students) {
    students.erase(std::remove_if(students.begin(), students.end(), [](const Student& student) {
        return student.score < 50;
    }),
    students.end());
}

int main() {
    std::vector<Student> students;

    loadStudents(students, "students.json");

    std::cout << "## Lista studentów ##" << std::endl;
    printStudents(students);

    std::cout << "## Średni wynik ##" << std::endl;
    std::cout << "Średnia: " << calculateAverageStudentScore(students);

    std::cout << "## Zaliczenia ##" << std::endl;
    countPassFail(students);

    removeFailingStudents(students);

    std::cout << "## Po usunięciu niezdanych ##" << std::endl;
    printStudents(students);

    int studentId;
    while (true) {
        std:: cout << "\nPodaj ID studenta: ";
        std::cin >> studentId;

        if (studentId == 0) {
            break;
        }

        findStudentById(students, studentId);
    }

    saveStudents(students, "students.json");

    return 0;
}