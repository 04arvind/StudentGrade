#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iomanip>

class Student {
public:
    std::string name;
    int student_id;
    std::vector<double> grades;
    Student(std::string name, int student_id) : name(std::move(name)), student_id(student_id){}
    double getOverallGrade() const {
        if (grades.empty()) return 0.0;
        double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
        return sum / grades.size();
    }
};
class Classroom {
private:
    std::vector<Student> students;
public:
    void addStudent(const std::string& name, int student_id) {
        students.emplace_back(name, student_id);
    }
    void addGrade(int student_id, double grade) {
        for (auto& student : students) {
            if (student.student_id == student_id) {
                student.grades.push_back(grade);
                return;
            }
        }
        std::cerr << "Student ID not found.\n";
    }
    void displayOverallGrades() const {
        for (const auto& student : students) {
            std::cout << "Student: " << student.name << ", ID: " << student.student_id << ", Overall Grade: " << student.getOverallGrade() << "\n";
        }
    }
    double getClassAverage() const {
        if (students.empty()) return 0.0;
        double sum = 0;
        for (const auto& student : students) {
            sum += student.getOverallGrade();
        }
        return sum / students.size();
    }
    void displayClassAverage() const {
        std::cout << "Class Average: " << getClassAverage() << "\n";
    }
    double getClassMedian() const {
        if (students.empty()) return 0.0;
        std::vector<double> overall_grades;
        for (const auto& student : students) {
            overall_grades.push_back(student.getOverallGrade());
        }
        std::sort(overall_grades.begin(), overall_grades.end());
        size_t size = overall_grades.size();
        if (size % 2 == 0) {
            return (overall_grades[size / 2 - 1] + overall_grades[size / 2]) / 2;
        } else {
            return overall_grades[size / 2];
        }
    }
    double getClassStandardDeviation() const {
        if (students.empty()) return 0.0;
        double mean = getClassAverage();
        double sum_of_squares = 0;
        for (const auto& student : students) {
            double diff = student.getOverallGrade() - mean;
            sum_of_squares += diff * diff;
        }
        return std::sqrt(sum_of_squares / students.size());
    }
    void displayClassStatistics() const {
        std::cout << "Class Average: " << getClassAverage() << "\n";
        std::cout << "Class Median: " << getClassMedian() << "\n";
        std::cout << "Class Standard Deviation: " << getClassStandardDeviation() << "\n";
    }
    void displayTopStudents(int top_n = 3) const {
        std::vector<Student> sorted_students = students;
        std::sort(sorted_students.begin(), sorted_students.end(), [](const Student& a, const Student& b) {
            return a.getOverallGrade() > b.getOverallGrade();
        });
        std::cout << "Top " << top_n << " Students:\n";
        for (int i = 0; i < std::min(top_n, static_cast<int>(sorted_students.size())); ++i) {
            std::cout << i + 1 << ". " << sorted_students[i].name << " (ID: " << sorted_students[i].student_id 
                      << ") - Overall Grade: " << sorted_students[i].getOverallGrade() << "\n";
        }
    }
    void inputStudentData() {
        int num_students;
        std::cout << "Enter the toal number of students in the class: ";
        std::cin >> num_students;
        for (int i = 0; i < num_students; ++i) {
            std::string name;
            int student_id;
            int num_grades;
            std::cout << "Enter name of student " << i + 1 << ": ";
            std::cin >> name;
            std::cout << "Enter ID of student " << i + 1 << ": ";
            std::cin >> student_id;
            addStudent(name, student_id);
            std::cout << "Enter the total number of grades for " << name << ": ";
            std::cin >> num_grades;
            for (int j = 0; j < num_grades; ++j) {
                double grade;
                std::cout << "Enter grade " << j + 1 << ": ";
                std::cin >> grade;
                addGrade(student_id, grade);
            }
        }
    }
};
int main() {
    Classroom classroom;
    classroom.inputStudentData();
    classroom.displayOverallGrades();
    classroom.displayClassStatistics();
    classroom.displayTopStudents();
    return 0;
}
