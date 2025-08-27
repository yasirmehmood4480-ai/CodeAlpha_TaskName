#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Structure to hold course information
struct Course {
    string name;
    double grade;
    double creditHours;
    double gradePoints;
};

int main() {
    int numCourses;
    double totalCredits = 0.0, totalGradePoints = 0.0;
    vector<Course> courses;

    cout << "Enter the number of courses taken: ";
    cin >> numCourses;

    for (int i = 0; i < numCourses; ++i) {
        Course c;
        cout << "\nCourse " << i + 1 << " name: ";
        cin.ignore(); // Clear newline from previous input
        getline(cin, c.name);

        cout << "Enter grade (e.g., 4.0 for A): ";
        cin >> c.grade;

        cout << "Enter credit hours: ";
        cin >> c.creditHours;

        c.gradePoints = c.grade * c.creditHours;

        totalCredits += c.creditHours;
        totalGradePoints += c.gradePoints;

        courses.push_back(c);
    }

    double gpa = (totalCredits > 0) ? totalGradePoints / totalCredits : 0.0;
    double cgpa = gpa; // Assuming CGPA = GPA for this semester

    // Display results
    cout << fixed << setprecision(2);
    cout << "\n--- Individual Course Grades ---\n";
    for (const auto& c : courses) {
        cout << c.name << ": Grade = " << c.grade
             << ", Credit Hours = " << c.creditHours
             << ", Grade Points = " << c.gradePoints << endl;
    }

    cout << "\nTotal Credit Hours: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Semester GPA: " << gpa << endl;
    cout << "Overall CGPA: " << cgpa << endl;

    return 0;
}
