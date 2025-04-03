#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <json.hpp>

using json = nlohmann::json;

struct Student {
    int id;
    std::string firstName;
    std::string lastName;
    double score;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, id, firstName, lastName, score);

    std::string getGrade() const {
        if (score >= 90) return "5";
        if (score >= 80) return "4+";
        if (score >= 70) return "4";
        if (score >= 60) return "3+";
        if (score >= 50) return "3";
        if (score < 50) return "2";
    };
};

void loadStudents(std::vector<Student>& students, const std::string& filename) {
    std::ifstream i(filename);

    if (!i) {
        std::cerr << "Nie mozna otworzyc pliku: " << filename;
        return;
    }

    json data = json::parse(i);

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

    printStudents(students);

    std::cout << "Average score: " << calculateAverageStudentScore(students) << "%" << std::endl;

    countPassFail(students);

    removeFailingStudents(students);
    std::cout << "After removing failing students:" << std::endl;
    printStudents(students);

    
    int searchId = 12345;  
    std::cout << "Searching for student with ID " << searchId << ":" << std::endl;
    findStudentById(students, searchId);

    saveStudents(students, "students.json");

    return 0;
}