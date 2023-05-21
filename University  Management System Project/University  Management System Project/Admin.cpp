#include "Admin.h"
#include "Course.h"
#include "Student.h"
#include<iostream>
#include <string>
#include<fstream>
#include<algorithm>
using namespace std;
Admin::Admin()
{
    userName = " ";
    Password = " ";
}

Admin::Admin(string username, string password)
{
    userName = username;
    Password = password;
}

bool Admin::Login(vector<Admin> ADMINS, string username, string password)
{

    system("CLS");
    // Hash table to store admin usernames and hashed passwords
    unordered_map<string, string, StringHasher> admin_passwords_;

    //saving the data in file in the hashtable
    for (int i = 0; i < ADMINS.size(); i++)
    {
        admin_passwords_[ADMINS[i].userName] = ADMINS[i].Password;
    }

    // Checks if the given username is in the hash table
    auto it = admin_passwords_.find(username);
    if (it == admin_passwords_.end())
    {
        return false; // Username not found
    }

    return password == it->second;
}

void Admin::AddCourse(vector<Course>& courseVector)
{

    system("CLS");
    Course c;
    string Name;
    string Code;
    string RequirementOrElective;
    int MaximumNumberofStudents;
    vector<string>ListofPreRequiredCourses;
    int Hours;
    string Instructor;

    cout << "***Adding a course***" << endl

        << "Enter course name: ";
    cin.ignore();
    getline(cin, Name);
    c.Name = Name;

    cout << "Enter course code: ";
    getline(cin, Code);
    c.Code = Code;

    cout << "Enter course Required or elective: ";
    getline(cin, RequirementOrElective);
    c.RequirementOrElective = RequirementOrElective;

    cout << "Enter course maximum number of students: ";
    cin >> MaximumNumberofStudents;
    c.MaximumNumberofStudents = MaximumNumberofStudents;

    char choice = 'y';
    while (choice == 'y' || choice == 'Y')
    {
        cout << "Enter course prerequired course: ";
        string preRequired;
        cin.ignore();
        getline(cin, preRequired);

        c.ListofPreRequiredCourses.push_back(preRequired);
        cout << "do you want to add another prerequirement? (y/n) ";
        cin >> choice;
    }

    cout << "Enter course hours: ";
    cin >> Hours;
    c.Hours = Hours;

    cout << "Enter course instructor: ";
    cin.ignore();
    getline(cin, Instructor);
    c.Instructor = Instructor;

    courseVector.push_back(c);

    //View all courses
    cout << "** ALL COURSES **" << endl;
    for (int i = 0; i < courseVector.size(); i++)
    {
        cout << "Name: " << courseVector[i].Name << endl
            << "Code: " << courseVector[i].Code << endl
            << "Hours: " << courseVector[i].Hours << endl
            << "Instructor: " << courseVector[i].Instructor << endl
            << "Maximum nuber of students: " << courseVector[i].MaximumNumberofStudents << endl;
        cout << "Prerequired courses: " << endl;
        for (int j = 0; j < courseVector[i].ListofPreRequiredCourses.size(); j++)
        {
            cout << courseVector[i].ListofPreRequiredCourses[j] << endl;
        }
        cout << "Requirement or Elective : " << courseVector[i].RequirementOrElective << endl;
    }
}

void Admin::StudentsInASpecificCourse(vector<Student>student, char CourseType, string CourseName)
{

    system("CLS");
    vector<Course> studentCourses;
    bool courseIsEmpty = true;

    for (int j = 0; j < student.size(); j++)
    {
        string studentName = student[j].Name;
        //when choose course type active
        if (CourseType == 'a' || CourseType == 'A')
        {
            studentCourses = student[j].CoursesInProgress;
        }
        //when choose course type finished
        else if (CourseType == 'f' || CourseType == 'F')
        {
            studentCourses = student[j].FinishedCourses;
        }
        for (int i = 0; i < studentCourses.size(); i++)
        {
            string studentCourseName = studentCourses[i].Name;
            if (studentCourseName.compare(CourseName) == 0)
            {
                cout << studentName << endl;
                courseIsEmpty = false;
            }
        }
    }
    if (courseIsEmpty)
    {
        cout << "The course " << CourseName << " has no students" << endl;
    }
}

void Admin::AddStudent(vector <Student>& students, string name)
{
    system("cls");
    int ID;
    if (students.empty())
    {
        ID = 2022170000;
    }
    //increment the last ID by 1
    else
    {
        ID = students.back().ID + 1;
    }
    string Name = name;
    //concatenate ID by @cis.asu.edu.eg to generate email
    string Email = to_string(ID) + "@cis.asu.edu.eg";
    //concatenate pass by ID by to generate password
    string password = "pass" + to_string(ID);
    Student newstudent(Name, ID, Email, password, 14, 2023, 0, {}, {});
    students.push_back(newstudent);
    //print the new student data
    cout << "** ADDED STUDENT **" << endl;
    cout << "Name: " << students[((students.size()) - 1)].Name << endl
        << "ID: " << students[((students.size()) - 1)].ID << endl
        << "Email: " << students[((students.size()) - 1)].Email << endl
        << "Password: " << students[((students.size()) - 1)].Password << endl
        << "Maximum hours: " << students[((students.size()) - 1)].MaximumHoursAllowed << endl
        << "Acadimic year: " << students[((students.size()) - 1)].AcademicYear << endl
        << "GPA: " << students[((students.size()) - 1)].GPA << endl;
}

void Admin::AddGrades(vector <Student>& students)
{
    int StudentID;
    int NewGrade;
    bool flag = false;
    char ans = 'n';
    do {
        cout << "Enter student ID: ";
        cin >> StudentID;
        for (int i = 0; i < students.size(); i++)
        {
            //check if student name is in vector or not & if has courses in progress or not
            if (students[i].ID == StudentID && !(students[i].CoursesInProgress.empty()))
            {
                cout << "Student name: " << students[i].Name << endl;
                cout << endl << "Student Courses In Progress " << endl;
                //print courses in progress for that student
                for (int j = 0, x = 1; j < students[i].CoursesInProgress.size(); j++, x++)
                {
                    cout << x << ") " << students[i].CoursesInProgress[j].Name << endl;
                }

                cout << endl << "Adding grades" << endl;
                cout << "Choose Course To Add Grade To :" << endl;
                int n;
                cin >> n;
                cout << "Enter grade of " << students[i].CoursesInProgress[n - 1].Name << ": ";
                cin >> NewGrade;
                students[i].CoursesInProgress[n - 1].grade = NewGrade;
                //add the course to the finished courses
                students[i].FinishedCourses.push_back(students[i].CoursesInProgress[n - 1]);
                //delete the course from courses in progress
                students[i].CoursesInProgress.erase(students[i].CoursesInProgress.begin() + n - 1);
                cout << endl << "Grades after adding " << endl;
                for (int j = 0; j < students[i].FinishedCourses.size(); j++)
                {
                    cout << students[i].FinishedCourses[j].Name << ": " << students[i].FinishedCourses[j].grade << endl;
                }
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            cout << "Student id not found! or student isn't enrolled in a course \n";
        }
        flag = false;
        cout << endl << "Do you want to add grades to another student? (y/n) ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}
void Admin::view_student_details(vector<Student>s)
{

    system("CLS");
    int id = 0;
    char ans = 'n';
    bool flag = false;

    do {
        //displaying all student names, so admin chooses one of them to view his data
        flag = false;
        cout << "Enter student ID to view his information" << endl;
        for (int i = 0; i < s.size(); i++)
        {
            cout << "student name:" << s[i].Name << endl;
            cout << "student ID:" << s[i].ID << endl;
            cout << endl;
        }
        cin >> id;
        system("CLS");
        for (int j = 0; j < s.size(); j++)
        {

            if (id == s[j].ID) {
                flag = true;
                cout << "student name:" << s[j].Name << endl;
                cout << "student ID:" << s[j].ID << endl;
                cout << "GPA:" << s[j].GPA << endl;
                cout << endl;
                if (s[j].FinishedCourses.size() == 0)
                {
                    cout << "No Finsihed Courses\n";

                }
                else
                {
                    cout << "Finished Courses:" << endl;
                    for (int m = 0; m < s[j].FinishedCourses.size(); m++)
                    {
                        cout << s[j].FinishedCourses[m].Name << endl;
                        if (s[j].FinishedCourses[m].grade < 60)
                            cout << "Failed\n";
                        else
                            cout << "Passed\n";

                    }
                    cout << endl;
                }
                if (s[j].CoursesInProgress.size() == 0)
                {
                    cout << "No Courses in Progress\n";

                }
                else {
                    cout << "courses in progress:" << endl;
                    for (int n = 0; n < s[j].CoursesInProgress.size(); n++)
                    {
                        cout << s[j].CoursesInProgress[n].Name << endl;

                    }
                }

            }

        }
        if (!flag) { cout << "ID not found,please enter correct one" << endl; }
        cout << endl;
        cout << "do you want to view another student? (y/n)";
        cin >> ans;
        system("CLS");
    } while (ans == 'y' || ans == 'Y');

}

void Admin::EditCourse(vector<Course>& courses)
{

    system("CLS");
    string CourseName;

    bool flag = false;
    char ans = 'n';
    do {
        int cinFLag = -1;
        cout << "Enter course name: ";

        getline(cin, CourseName);

        for (int i = 0; i < courses.size(); i++)
        {
            if ((courses[i].Name.compare(CourseName)) == 0)
            {
                cout << "*******Course details******* " << endl;
                cout << "Course name:" << courses[i].Name << endl;
                cout << "Course code:" << courses[i].Code << endl;
                cout << "Course hours:" << courses[i].Hours << endl;
                cout << "Course instructor:" << courses[i].Instructor << endl;
                cout << "Course maximum number of students:" << courses[i].MaximumNumberofStudents << endl;
                cout << "Course type:" << courses[i].RequirementOrElective << endl;
                cout << "Course requirements:" << endl;
                for (int j = 0; j < courses[i].ListofPreRequiredCourses.size(); j++) {
                    cout << courses[i].ListofPreRequiredCourses[j] << endl;
                }

                cout << endl << "*******Editing details*******" << endl;
                cout << "Which course data do you want to edit?" << endl;
                cout << "1: Course Name" << endl;
                cout << "2: Course code" << endl;
                cout << "3: Course hours" << endl;
                cout << "4: Course instructor" << endl;
                cout << "5: Course maximum number of students" << endl;
                cout << "6: Course type" << endl;
                cout << "7: Course requirments" << endl;
                int choiseNumber;
                cin >> choiseNumber;
                if (choiseNumber == 1) {
                    string name;
                    cout << "Enter new name:";
                    cin.ignore();
                    getline(cin, name);
                    courses[i].Name = name;
                }
                else if (choiseNumber == 2) {
                    string code;
                    cout << "Enter new code:";
                    cin.ignore();
                    getline(cin, code);
                    courses[i].Code = code;
                }
                else if (choiseNumber == 3) {
                    int hrs;
                    cout << "Enter new hours:";
                    cin >> hrs;
                    courses[i].Hours = hrs;
                }
                else if (choiseNumber == 4) {
                    string instructor;
                    cout << "Enter new instructor:";
                    cin >> instructor;
                    courses[i].Instructor = instructor;
                }
                else if (choiseNumber == 5) {
                    int maxStuds;
                    cout << "Enter new maximum number of students:";
                    cin >> maxStuds;
                    courses[i].MaximumNumberofStudents = maxStuds;
                }
                else if (choiseNumber == 6) {
                    string ReqOrElective;
                    cout << "Enter new type:";
                    cin >> ReqOrElective;
                    courses[i].RequirementOrElective = ReqOrElective;
                }
                else if (choiseNumber == 7) {
                    int y;
                    cout << "do you want to:" << endl;
                    cout << "1:add requirement" << endl;
                    cout << "2:delete requirement" << endl;
                    cin >> y;
                    if (y == 1) {
                        string req;
                        cout << "enter new requirement:";
                        cin >> req;
                        courses[i].ListofPreRequiredCourses.push_back(req);
                    }
                    else if (y == 2) {
                        string DeleteReq;
                        cout << "enter requirement you want to delete:";
                        cin.ignore();
                        getline(cin, DeleteReq);
                        for (auto it = courses[i].ListofPreRequiredCourses.begin(); it != courses[i].ListofPreRequiredCourses.end(); ++it) {
                            if (*it == DeleteReq) {
                                courses[i].ListofPreRequiredCourses.erase(it);
                                break; // exit the loop after the first occurrence is removed
                            }
                            else {
                                std::cout << "\"" << DeleteReq << "\" was not found in the vector." << std::endl;
                            }
                        }

                    }
                }
                cout << endl << "*******Course after editing******* " << endl;

                cout << "Course name:" << courses[i].Name << endl;
                cout << "Course code:" << courses[i].Code << endl;
                cout << "Course hours:" << courses[i].Hours << endl;
                cout << "Course instructor:" << courses[i].Instructor << endl;
                cout << "Course maximum number of students:" << courses[i].MaximumNumberofStudents << endl;
                cout << "Course type:" << courses[i].RequirementOrElective << endl;
                cout << "Course requirements:" << endl;
                for (int j = 0; j < courses[i].ListofPreRequiredCourses.size(); j++) {
                    cout << courses[i].ListofPreRequiredCourses[j] << endl;
                }

                flag = true;
                break;
            }
        }
        if (!flag)
        {
            cout << "course not found! \n";
        }
        flag = false;
        cout << endl << "Do you want to edit another course? (y/n) ";

        cin >> ans;
        cin.ignore();

    } while (ans == 'y' || ans == 'Y');


};

//Bonus (Extra functionality)
void Admin::RemoveStudent(vector<Student>& student)
{

    system("CLS");
    char ans;
    do {
        cout << "Enter The ID Of The Student You Want To Remove :";
        long long id;
        cin >> id;
        unordered_map<long long, int> search;
        for (int i = 0; i < student.size(); i++)
        {
            search[student[i].ID] = i;
        }
        auto it = search.find(id);
        if (it == search.end()) {
            cout << "Student Not Found." << endl;
            break;
        }
        int element_to_remove = it->second;

        student.erase(student.begin() + element_to_remove);
        cout << "Student Removed Successfuly" << endl;
        cout << "Do you want to remove another student? (y/n) ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}
void Admin::RemoveCourse(vector<Student>& student, vector<Course>& courses)
{

    system("CLS");
    char ans;
    do
    {
        unordered_map<string, int> search;
        for (int i = 0; i < courses.size(); i++)
        {
            cout << i + 1 << ")" << courses[i].Name << endl;
            search[courses[i].Name] = i;
        }
        cout << "**********" << endl;
        cout << "Enter The Name Of The Course You Want To Remove: ";
        string name;
        getline(cin, name);
        auto it = search.find(name);
        if (it == search.end())
        {
            cout << "Course Not Found." << endl;

        }
        else {
            int element_to_remove = it->second;
            //this loop pushes the list of prerequired courses of the course you want to delete into the parent class
            for (int i = 0; i < courses.size(); i++)
            {
                for (int j = 0; j < courses[i].ListofPreRequiredCourses.size(); j++)
                {
                    if (courses[i].ListofPreRequiredCourses[j] == courses[element_to_remove].Name)
                    {
                        if (!courses[element_to_remove].ListofPreRequiredCourses.empty() && (courses[element_to_remove].ListofPreRequiredCourses[0].compare("No pre-required courses")) != 0)
                        {
                            for (int k = 0; k < courses[element_to_remove].ListofPreRequiredCourses.size(); k++)
                            {
                                courses[i].ListofPreRequiredCourses.push_back(courses[element_to_remove].ListofPreRequiredCourses[j]);
                            }
                        }
                    }
                }
            }
            //this loop removes the course you want to remove from the list of prerequired courses in the parent class
            for (int i = 0; i < courses.size(); i++)
            {
                for (int j = 0; j < courses[i].ListofPreRequiredCourses.size(); j++)
                {
                    if (courses[i].ListofPreRequiredCourses[j] == courses[element_to_remove].Name)
                        courses[i].ListofPreRequiredCourses.erase(courses[i].ListofPreRequiredCourses.begin() + j);
                }
            }

            // this loop removes the course you want to delete from the courses in progress of the students 
            for (int i = 0; i < student.size(); i++)
            {
                for (int j = 0; j < student[i].CoursesInProgress.size(); j++)
                {
                    if (student[i].CoursesInProgress[j].Name == courses[element_to_remove].Name)
                        student[i].CoursesInProgress.erase(student[i].CoursesInProgress.begin() + j);
                }
            }

            courses.erase(courses.begin() + element_to_remove); // erase course from courses vector 

            // this loop pushes the string "No pre-required courses" if the parent's course list of prerequired courses is empty 
            for (int i = 0; i < courses.size(); i++)
            {
                if (courses[i].ListofPreRequiredCourses.empty())
                    courses[i].ListofPreRequiredCourses.push_back("No pre-required courses");
            }
        }

        cout << "Do you want to remove another course? (Y/N) ";
        cin >> ans;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (ans == 'y' || ans == 'Y');
}
void Admin::AdminMenu(vector<Admin>& admins, vector<Student>& students, vector<Course>& courses, vector<Feedback>& feedback)
{

    system("CLS");
    Admin a;
    string Adminusername;
    string Adminpassword;
    string CourseStudentsToBeViewd;
    char CourseType;
    bool FinishedOrActiveStatus = true;
    int num;

    // Get username and password from user input
    cout << "LOGIN as ADMIN\n";
    cout << "Enter username: \n";
    cin >> Adminusername;
    //system("pause");
    cout << "Enter password: \n";
    cin >> Adminpassword;
    // Verify login

    if (a.Login(admins, Adminusername, Adminpassword))
    {
        cout << "Admin login successful!" << endl;
        do {

            cout << "SELEECT A NUMBER" << endl;
            cout << "1- See a list of students in a specific course " << endl
                << "2- Add new student " << endl
                << "3- Add Grades of all courses to the students " << endl
                << "4- Add new course " << endl
                << "5- View student details " << endl
                << "6- Edit course " << endl
                << "7- Remove student " << endl
                << "8- Remove course " << endl
                << "9- View FeedBack" << endl
                << "10- Courses Reports" << endl
                << "11- Exit" << endl;

            cin >> num;

            //Students In A Specific Course
            if (num == 1)
            {
                char choice = 'x';
                do
                {
                    cout << "Enter the name of the course ";
                    //cin >> CourseStudentsToBeViewd;
                    getline(cin >> ws, CourseStudentsToBeViewd);
                    cout << "enter 'f' for display students who finsihed the course \nenter 'a' for display students who currently attending the course \n";
                    cin >> CourseType;
                    while (CourseType != 'a' && CourseType != 'A' && CourseType != 'F' && CourseType != 'f')
                    {
                        cout << "Please enter an approriate value \n";
                        cin >> CourseType;
                    }
                    a.StudentsInASpecificCourse(students, CourseType, CourseStudentsToBeViewd);
                    cout << "Do you want to see another course?(y/n)\n";
                    cin >> choice;
                } while (choice == 'y' || choice == 'Y');
            }

            //Add Student
            else if (num == 2)
            {
                char choice;
                do {
                    string name;
                    cout << "Enter name of student: ";
                    cin.ignore();
                    getline(cin, name);
                    a.AddStudent(students, name);
                    cout << "Do you want to add another student?(y/n)\n";
                    cin >> choice;
                } while (choice == 'Y' || choice == 'y');
            }

            //Add Grades
            else if (num == 3)
            {
                a.AddGrades(students);
            }

            //Add Course
            else if (num == 4)
            {
                char answer = 'n';
                do {
                    a.AddCourse(courses);

                    cout << "do you want to add another course?(y/n)";
                    cin >> answer;
                } while (answer == 'y' || answer == 'Y');
            }

            //View student details
            else if (num == 5)
            {
                a.view_student_details(students);
            }

            //Edit courses
            else if (num == 6)
            {
                cin.ignore();
                a.EditCourse(courses);
            }

            //Remove Student
            else if (num == 7)
            {
                a.RemoveStudent(students);
            }

            //Remove course
            else if (num == 8)
            {
                cin.ignore();
                a.RemoveCourse(students, courses);
            }
            else if (num == 9)
            {
                a.view_feedback(feedback, courses);
            }
            else if (num == 10)
            {
                a.CoursesReport(students, courses);
            }
            else if (num == 11)
            {
                break;
            }
            else
            {
                cout << "Invalid number";
            }


        } while (true);
    }
    else
    {
        cout << "Admin login failed." << endl;
    }


}

void Admin::CoursesReport(vector<Student> student, vector<Course> course)
{
    system("CLS");
    float marks = 0, avg = 0, maxgrade = 0, mingrade = 100;
    int numoftotalstudents = 0;
    int  numberofsuccessfulstudents = 0;
    float percentage = 0;
    bool found = false;
    for (int i = 0; i < course.size(); i++)
    {
        for (int j = 0; j < student.size(); j++)
        {
            for (int k = 0; k < student[j].FinishedCourses.size(); k++)
                if (course[i].Name == student[j].FinishedCourses[k].Name)
                {
                    maxgrade = max(maxgrade, student[j].FinishedCourses[k].grade);
                    mingrade = min(mingrade, student[j].FinishedCourses[k].grade);
                    marks += student[j].FinishedCourses[k].grade;
                    numoftotalstudents++;
                    if (student[j].FinishedCourses[k].grade >= 60)
                        numberofsuccessfulstudents++;
                    found = true;
                }
        }
        if (found)
        {
            avg = marks / numoftotalstudents;
            percentage = numberofsuccessfulstudents / numoftotalstudents;
            cout << "The Average for " << course[i].Name << "\t";
            cout << avg << endl;
            cout << "The Maximum grade for " << course[i].Name << "\t" << maxgrade << endl;
            cout << "The Minimum grade for " << course[i].Name << "\t" << mingrade << endl;
            cout << " The percentage of success for " << course[i].Name << "\t" << percentage * 100 << " %" << endl;
            cout << " The percentage of fall for " << course[i].Name << "\t" << (1 - percentage) * 100 << " %" << endl;
            cout << "================================================================\n";
        }
        marks = avg = numoftotalstudents = maxgrade = percentage = numberofsuccessfulstudents = 0;
        mingrade = 100;
        found = false;
    }
}

void Admin::view_feedback(vector<Feedback>fb, vector<Course>c)
{
    system("CLS");
    cout << "number of filled feedbacks : ";
    cout << fb.size() << endl;
    for (int i = 0; i < fb.size(); i++)
    {
        cout << "feedback: " << i + 1 << endl;
        cout << "course name: " << fb[i].CourseName << endl;
        cout << "student name: " << fb[i].StudentName << endl;
        cout << "1)Course content was informative and well organized " << endl;
        cout << fb[i].content << endl; cout << endl;
        cout << "2)Course TAs were accessible & provided enough support" << endl;
        cout << fb[i].TA << endl;  cout << endl;
        cout << "3)Course helped me improve my technicalities and critical thinking" << endl;
        cout << fb[i].skills << endl;  cout << endl;
        cout << "4)Course doctor delivered information to be easily understood and recalled" << endl;
        cout << fb[i].doctor << endl;  cout << endl;
        cout << "5)Examinations fairly evaluated my well studied and revised information" << endl;
        cout << fb[i].exam << endl;  cout << endl;
        cout << "6)Course was well bounded to reallife requirements in the field" << endl;
        cout << fb[i].reallife << endl;  cout << endl;
        cout << "Student Suggestion for the Course\n";
        cout << fb[i].suggestion << endl;
        cout << "average rate for this course : " << fb[i].avg << endl;
        cout << endl;
        cout << "\t ***********************************" << endl;
    }
}
