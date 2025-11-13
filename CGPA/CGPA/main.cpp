#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits> // for input validation

using namespace std;

// ---------- Course Class ----------
class Course {
public:
    string name;
    double grade;
    double credit;

    Course(string n, double g, double c) {
        name = n;
        grade = g;
        credit = c;
    }
};

// ---------- Function to Calculate GPA ----------
double calculateGPA(const vector<Course>& courses) {
    double totalGradePoints = 0, totalCredits = 0;

    for (auto &course : courses) {
        totalGradePoints += course.grade * course.credit;
        totalCredits += course.credit;
    }

    if (totalCredits == 0)
        return 0;

    return totalGradePoints / totalCredits;
}

// ---------- Function to Take Valid Number Input ----------
double getValidDouble(string prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;

        // Check if input failed (not a number)
        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input! Please enter a numeric value.\n";
            continue;
        }

        // Check if in valid range
        if (value < minVal || value > maxVal) {
            cout << "❌ Please enter a value between " << minVal << " and " << maxVal << ".\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
        return value;
    }
}

// ---------- Main Function ----------
int main() {
    int numCourses;
    vector<Course> allCourses;

    cout << "========== CGPA CALCULATOR ==========\n\n";

    // Input number of courses
    while (true) {
        cout << "Enter number of courses: ";
        cin >> numCourses;

        if (cin.fail() || numCourses <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Please enter a positive integer for number of courses.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    // Input each course
    for (int i = 0; i < numCourses; i++) {
        string name;
        cout << "\nEnter details for course " << i + 1 << ":\n";
        cout << "Course name: ";
        getline(cin, name);

        double grade = getValidDouble("Grade points (0 - 10): ", 0, 10);
        double credit = getValidDouble("Credit hours (> 0): ", 0.1, 50); // limit credit hours

        allCourses.push_back(Course(name, grade, credit));
    }

    // Calculate CGPA
    double cgpa = calculateGPA(allCourses);

    // Display Results
    cout << "\n\n========== RESULT ==========\n";
    cout << left << setw(20) << "Course"
         << setw(10) << "Grade"
         << setw(10) << "Credits" << endl;
    cout << "-----------------------------------------\n";

    for (auto &course : allCourses) {
        cout << left << setw(20) << course.name
             << setw(10) << course.grade
             << setw(10) << course.credit << endl;
    }

    cout << "\nTotal Courses: " << numCourses;
    cout << "\nFinal CGPA: " << fixed << setprecision(2) << cgpa << endl;
    cout << "=========================================\n";

    return 0;
}

