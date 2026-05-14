#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

// ===============================
//      COURSE STRUCTURE
// ===============================
struct Course {
    string name;
    string grade;
    int credit;
    double gradePoint;
    double totalPoint;
};

// ===============================
//   FUNCTION TO GET GRADE POINT
// ===============================
double getGradePoint(string grade) {
    transform(grade.begin(), grade.end(), grade.begin(), ::toupper);

    if (grade == "O") return 10.0;
    if (grade == "A+") return 9.0;
    if (grade == "A") return 8.0;
    if (grade == "B+") return 7.0;
    if (grade == "B") return 6.0;
    if (grade == "C") return 5.0;
    return 0.0; // RA / Fail
}

// ===============================
//        MAIN FUNCTION
// ===============================
int main() {

    system("color 0B"); // Stylish Console Color (Windows)

    cout << "\n";
    cout << "========================================================\n";
    cout << "          SMART AI-STYLE CGPA ANALYZER SYSTEM           \n";
    cout << "========================================================\n";

    int n;

    cout << "\n📚 Enter Number of Courses : ";
    cin >> n;

    vector<Course> courses;

    double totalCredits = 0;
    double totalGradePoints = 0;

    // ===============================
    //      INPUT COURSE DETAILS
    // ===============================
    for (int i = 0; i < n; i++) {

        Course c;

        cout << "\n--------------------------------------------------\n";
        cout << "               COURSE " << i + 1 << " ENTRY\n";
        cout << "--------------------------------------------------\n";

        cin.ignore();

        cout << "📘 Course Name     : ";
        getline(cin, c.name);

        cout << "🏆 Grade (O/A+/A/B+/B/C/RA) : ";
        cin >> c.grade;

        cout << "⏳ Credit Hours    : ";
        cin >> c.credit;

        c.gradePoint = getGradePoint(c.grade);
        c.totalPoint = c.gradePoint * c.credit;

        totalCredits += c.credit;
        totalGradePoints += c.totalPoint;

        courses.push_back(c);
    }

    // ===============================
    //         CGPA CALCULATION
    // ===============================
    double cgpa = totalGradePoints / totalCredits;

    // ===============================
    //        PERFORMANCE LEVEL
    // ===============================
    string performance;
    string emoji;

    if (cgpa >= 9) {
        performance = "OUTSTANDING";
        emoji = "🏆";
    }
    else if (cgpa >= 8) {
        performance = "EXCELLENT";
        emoji = "🎯";
    }
    else if (cgpa >= 7) {
        performance = "VERY GOOD";
        emoji = "🔥";
    }
    else if (cgpa >= 6) {
        performance = "GOOD";
        emoji = "👍";
    }
    else {
        performance = "NEEDS IMPROVEMENT";
        emoji = "📚";
    }

    // ===============================
    //      FIND TOP SUBJECT
    // ===============================
    int topIndex = 0;

    for (int i = 1; i < n; i++) {
        if (courses[i].gradePoint > courses[topIndex].gradePoint) {
            topIndex = i;
        }
    }

    // ===============================
    //          OUTPUT SECTION
    // ===============================

    cout << "\n\n";
    cout << "===============================================================\n";
    cout << "                    FINAL GRADE REPORT                         \n";
    cout << "===============================================================\n";

    cout << left
         << setw(22) << "Course"
         << setw(12) << "Grade"
         << setw(12) << "Credits"
         << setw(15) << "G.Point"
         << setw(15) << "Total" << endl;

    cout << "---------------------------------------------------------------\n";

    for (auto c : courses) {
        cout << left
             << setw(22) << c.name
             << setw(12) << c.grade
             << setw(12) << c.credit
             << setw(15) << c.gradePoint
             << setw(15) << c.totalPoint
             << endl;
    }

    cout << "===============================================================\n";

    cout << fixed << setprecision(2);

    cout << "\n🎓 TOTAL CREDITS       : " << totalCredits << endl;
    cout << "💯 TOTAL GRADE POINTS  : " << totalGradePoints << endl;
    cout << "📈 FINAL CGPA          : " << cgpa << endl;

    cout << "\n" << emoji << " PERFORMANCE STATUS : " << performance << endl;

    cout << "\n🌟 BEST PERFORMED SUBJECT : "
         << courses[topIndex].name
         << " (" << courses[topIndex].grade << ")"
         << endl;

    // ===============================
    //      SCHOLARSHIP ELIGIBILITY
    // ===============================
    cout << "\n--------------------------------------------------\n";

    if (cgpa >= 9) {
        cout << "🎉 Congratulations! You are eligible for Academic Scholarship!\n";
    }
    else if (cgpa >= 8) {
        cout << "✨ Great Work! You are close to scholarship level!\n";
    }
    else {
        cout << "🚀 Keep improving to unlock scholarship opportunities!\n";
    }

    // ===============================
    //         CGPA VISUAL BAR
    // ===============================

    cout << "\n📊 CGPA VISUAL INDICATOR : ";

    int bars = cgpa * 2;

    for (int i = 0; i < bars; i++) {
        cout << "█";
    }

    cout << " " << cgpa << "/10\n";

    cout << "\n===============================================================\n";
    cout << "         THANK YOU FOR USING SMART CGPA ANALYZER               \n";
    cout << "===============================================================\n";

    return 0;
}