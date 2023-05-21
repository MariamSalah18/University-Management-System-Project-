#include "Student.h"
#include<iostream>
#include<string>
#include <fstream>
#include<map>
#include "Course.h"
using namespace std;
Student::Student(string name, int id, string email, string password, int maxhours, int academicYear, float gpa, vector<Course>finishedcourses, vector<Course>coursesinprogress)
{
	Name = name;
	ID = id;
	Email = email;
	Password = password;
	MaximumHoursAllowed = maxhours;
	AcademicYear = academicYear;
	GPA = gpa;
	CoursesInProgress.clear(); // Clear the vector to remove any existing elements
	for (int i = 0; i < coursesinprogress.size(); i++)
	{
		CoursesInProgress.push_back(coursesinprogress[i]);
	}
	FinishedCourses.clear(); // Clear the vector to remove any existing elements
	for (int i = 0; i < finishedcourses.size(); i++)
	{
		FinishedCourses.push_back(finishedcourses[i]);
	}
}

Student::Student()
{
	Name = Email = Password = " ";
	ID = MaximumHoursAllowed = AcademicYear = GPA = 0;
}

void Student::studentmenu(vector<Student>& students, vector<Course>& courses, vector<Feedback>& feedback, int index)
{
	system("cls");
	cout << "Welcome " << students[index].Name << endl;
	cout << "\n";
	int num;
	do {
		cout << "SELEECT A NUMBER" << endl;
		cout << "1- View List Of All Available Courses\n2- Filter Courses\n3- Filter Student Courses\n4- View Course Details\n5- Register Course\n";
		cout << "6- View All Student Courses\n7- View Grades And CGPA\n8- Edit Data\n9- FeedBack\n10- Exit\n";
		cin >> num;
		if (num == 1)
		{
			system("CLS");
			students[index].ViewListOfAllAvailableCourses(students[index], courses);

			continue;
		}
		else if (num == 2)
		{
			system("CLS");
			cout << "Filter All Courses\n";
			students[index].FilterCourses(courses);

			continue;
		}
		else if (num == 3)
		{
			system("CLS");

			cout << "Filter Student Courses\n";
			students[index].FilterStudentCourses(students[index]);

			continue;
		}
		else if (num == 4)
		{
			system("CLS");

			students[index].ViewCourseDetails(courses);

			continue;
		}
		else if (num == 5)
		{
			system("CLS");

			students[index].Register(students[index], courses);

			continue;
		}
		else if (num == 6)
		{
			system("CLS");

			students[index].ViewAllStudentCourses(students[index]);

			continue;
		}
		else if (num == 7)
		{
			system("CLS");

			students[index].ViewGradesAndCGPA(students[index]);

			continue;

		}
		else if (num == 8)
		{
			system("CLS");

			students[index].EditData(students[index]);

			continue;
		}
		else if (num == 9)
		{
			system("CLS");

			students[index].FillFeedback(students[index], feedback, courses);

			continue;
		}
		else if (num == 10)
		{
			break;
		}
		else if (num > 10)
		{
			system("cls");
			cout << "Enter Correct Number from 1 to 10\n";

			continue;
		}
	} while (num != 10);
}

int Student::Login(vector<Student> students, string username, string password)
{
	unordered_map<string, string> student_passwords;

	// Populate map with student emails and passwords
	for (int i = 0; i < students.size(); i++)
	{
		student_passwords[students[i].Email] = students[i].Password;
	}

	// Check if given email exists in the map
	auto it = student_passwords.find(username);
	if (it == student_passwords.end())
	{
		cout << "Wrong Username or Password\n";
		return -1;
	}

	// Check if given password matches the password in the map
	if (it->second == password)
	{
		// Return the index of the student in the vector
		cout << "Login successfully\n";
		for (int i = 0; i < students.size(); i++)
		{
			if (students[i].Email == username && students[i].Password == password)
			{
				return i;
			}
		}
	}

	cout << "Wrong Username or Password\n";
	return -1;
}

bool Student::ViewListOfAllAvailableCourses(Student s, vector<Course> c)//to be updated
{
	int number = 1;
	int availableCourses = 0;
	bool FoundProgress = false, FoundFinished = false;
	cout << "list of available courses :" << endl;
	for (int i = 0; i < c.size(); i++)
	{
		bool flag = false;
		FoundProgress = FoundFinished = false;
		int counter = 0;
		for (int k = 0; k < c[i].ListofPreRequiredCourses.size(); k++)
		{
			for (int j = 0; j < s.FinishedCourses.size(); j++)
			{
				if (s.FinishedCourses[j].Name == c[i].ListofPreRequiredCourses[k])
				{
					counter++;
				}

			}
		}
		for (int m = 0; m < s.CoursesInProgress.size(); m++)
		{
			if (c[i].Code == s.CoursesInProgress[m].Code)
				FoundProgress = true;
		}
		for (int n = 0; n < s.FinishedCourses.size(); n++)
		{
			if (c[i].Code == s.FinishedCourses[n].Code)
				FoundFinished = true;
		}
		if ((counter == c[i].ListofPreRequiredCourses.size()) ||
			(c[i].ListofPreRequiredCourses[0].compare("No pre-required courses") == 0))
		{
			flag = true;
			availableCourses++;
		}
		if (flag && !FoundFinished && !FoundProgress)
		{
			cout << number++ << "- course name: " << c[i].Name << endl;
			cout << "course code: " << c[i].Code << endl;
			cout << endl;
		}


	}
	if (availableCourses == 0)
	{
		cout << "zero courses available";
		return false;
	}
	else return true;
}
bool Exitflag = false;
void Student::FilterStudentCourses(Student std)
{
	int choise;
	Exitflag = false;
	while (!Exitflag)
	{

		cout << "1)Filter Finished Courses\n";
		cout << "2)Filter Courses In Progress\n3)Exit\n";
		cin >> choise;
		switch (choise)
		{
		case 1:
		{
			std.FilterCourses(std.FinishedCourses);
			break;
		}
		case 2:
		{
			std.FilterCourses(std.CoursesInProgress);
			break;
		}
		case 3:
		{
			Exitflag = true;
			break;
		}
		default:
		{
			cout << "enter correct number\n";
			continue;
		}
		}
	}
}

void Student::FilterCourses(vector<Course>c)
{
	int choise, hours, reqorelective;
	string name;
	Exitflag = false;
	bool found = false;

	while (!Exitflag)
	{
		if (c.size() == 0)
		{
			cout << "Sorry you don't have Courses\n";
			break;
		}
		cout << "1)Filter Courses by Hours\n2)Filter Courses by Requirement or Elective\n";
		cout << "3)Filter Courses by Instrustor Name\n4)Exit\n";
		cin >> choise;
		switch (choise)
		{
		case 1:
		{
			cout << "Filter Course by Hours\n";
			cout << "Enter Hours\n";
			cin >> hours;

			for (Course val : c)
			{
				if (val.Hours == hours)
				{
					int i = 1;
					cout << "Name: " << val.Name << endl;
					cout << "Code: " << val.Code << endl;
					cout << "Requirement or Elective: " << val.RequirementOrElective << endl;
					cout << "Maximum Number of Students: " << val.MaximumNumberofStudents << endl;
					cout << "List of Prerequisite Required Courses:" << endl;
					for (string course : val.ListofPreRequiredCourses)
					{
						cout << i << "- " << course << endl;
						i++;
					}
					cout << "Hours: " << val.Hours << endl;
					cout << "Instructor: " << val.Instructor << endl;
					cout << "***************************************************************************************************************\n";
					found = true;
				}
			}
			if (!found)
				cout << "Sorry, No Courses with this Hours\n";
			cout << endl;
			found = false;
			break;
		}
		case 2:
		{
			cout << "Filter Course by Requirement or Elective\n";
			cout << "1-Show Requirment Courses\n2-Show Elective Courses\n";
			cin >> reqorelective;
			if (reqorelective == 1)
			{
				for (Course val : c)
				{
					if (val.RequirementOrElective == "Requirement" || val.RequirementOrElective == "requirement")
					{
						int i = 1;
						cout << "Name: " << val.Name << endl;
						cout << "Code: " << val.Code << endl;
						cout << "Requirement or Elective: " << val.RequirementOrElective << endl;
						cout << "Maximum Number of Students: " << val.MaximumNumberofStudents << endl;
						cout << "List of Prerequisite Required Courses:" << endl;
						for (string course : val.ListofPreRequiredCourses)
						{
							cout << i << "- " << course << endl;
							i++;
						}
						cout << "Hours: " << val.Hours << endl;
						cout << "Instructor: " << val.Instructor << endl;
						cout << "***************************************************************************************************************\n";
					}
				}
			}
			else
			{
				for (Course val : c)
				{
					if (val.RequirementOrElective == "elective" || val.RequirementOrElective == "Elective")
					{
						int i = 1;
						cout << "Name: " << val.Name << endl;
						cout << "Code: " << val.Code << endl;
						cout << "Requirement or Elective: " << val.RequirementOrElective << endl;
						cout << "Maximum Number of Students: " << val.MaximumNumberofStudents << endl;
						cout << "List of Prerequisite Required Courses:" << endl;
						for (string course : val.ListofPreRequiredCourses)
						{
							cout << i << "- " << course << endl;
							i++;
						}
						cout << "Hours: " << val.Hours << endl;
						cout << "Instructor: " << val.Instructor << endl;
						cout << "***************************************************************************************************************\n";
					}
				}
			}
			break;
		}
		case 3:
		{
			cout << "Filter Courses by Instrustor Name\n";
			cout << "Enter Instrustor Name\n";
			cin.ignore();
			getline(cin, name);
			for (Course val : c)
			{
				if (name == val.Instructor)
				{
					int i = 1;
					cout << "Name: " << val.Name << endl;
					cout << "Code: " << val.Code << endl;
					cout << "Requirement or Elective: " << val.RequirementOrElective << endl;
					cout << "Maximum Number of Students: " << val.MaximumNumberofStudents << endl;
					cout << "List of Prerequisite Required Courses:" << endl;
					for (string course : val.ListofPreRequiredCourses)
					{
						cout << i << "- " << course << endl;
						i++;
					}
					cout << "Hours: " << val.Hours << endl;
					cout << "***************************************************************************************************************\n";
					found = true;
				}
			}
			if (!found)
				cout << "Sorry,No Courses with this Instructor\n";
			cout << endl;
			found = false;
			break;
		}
		case 4:
		{
			Exitflag = true;
			break;
		}
		default:
		{
			cout << "enter correct number\n";
			continue;
		}
		}
	}
}

void Student::ViewCourseDetails(vector<Course>c)
{

	char ans = 'y';
	int choice = 0;

	do {

		cout << "Select course NUMBER to view details \n";
		for (int i = 0; i < c.size(); i++) //displaying all courses 
		{
			cout << i + 1 << "-" << c[i].Name << endl;
		}

		cin >> choice;
		if (choice > c.size() || choice <= 0)
		{
			cout << "---->NOT FOUND! please enter valid number<-------" << endl;
			continue;
		}
		cout << "name: " << c[choice - 1].Name << endl;
		cout << "code: " << c[choice - 1].Code << endl;
		cout << "hourse: " << c[choice - 1].Hours << endl;
		cout << "instructor: " << c[choice - 1].Instructor << endl;
		cout << "List of prerequired courses:" << endl;
		for (int j = 0; j < c[choice - 1].ListofPreRequiredCourses.size(); j++)
		{
			cout << c[choice - 1].ListofPreRequiredCourses[j] << endl;
		}
		cout << "this course is " << c[choice - 1].RequirementOrElective << endl;
		cout << "max number of students: " << c[choice - 1].MaximumNumberofStudents << endl;
		cout << "do you want to view another course details (Y/N)" << endl;
		cin >> ans;
	} while (ans == 'Y' || ans == 'y');
}

void Student::Register(Student& s, vector<Course> c)
{
	char ans = 'y'; bool done = false;
	do
	{
		//system("CLS");
		done = false;
		int currenthours = 0; int availablehours = 0;
		string code;
		for (int i = 0; i < s.CoursesInProgress.size(); i++)
		{
			currenthours += s.CoursesInProgress[i].Hours;
		}
		if (s.GPA < 2)
		{
			availablehours = 14 - currenthours;
		}
		if (s.GPA > 2 && s.GPA < 3)
		{
			availablehours = 18 - currenthours;
		}
		if (s.GPA > 3 || s.GPA == 3)
		{
			availablehours = 21 - currenthours;
		}
		// for testing calculations 
		cout << "current hours:" << currenthours << endl;
		cout << "available hours:" << availablehours << endl;
		cout << "GPA:" << s.GPA << endl;
		bool availablecourses = s.ViewListOfAllAvailableCourses(s, c);
		if (availablecourses)
		{
			cout << "enter course code to register" << endl;

			cin >> code;
			for (int j = 0; j < c.size(); j++)
			{
				if (c[j].Code == code && availablehours - c[j].Hours > 0)
				{
					s.CoursesInProgress.push_back(c[j]);
					cout << "course registered" << endl;
					done = true;
				}

			}
			if (done == false)
			{
				cout << "no enough hours or code not found" << endl;
			}
		}
		else
			cout << "no courses to register" << endl;
		cout << endl;

		cout << "courses currently in progress:" << endl;
		for (int k = 0; k < s.CoursesInProgress.size(); k++)
		{
			cout << s.CoursesInProgress[k].Name << endl;
		}

		cout << "do you want to register for another course (y/n)?" << endl;
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');
}

void Student::ViewAllStudentCourses(Student s)
{
	int choice;
	do {
		cout << "1) View Finished Courses." << endl;
		cout << "2) View In Progress Courses." << endl;
		cout << "3) Exit" << endl;
		cin >> choice;
		if (choice == 1)
		{
			if (s.FinishedCourses.size() == 0)
			{
				cout << "you don't have finsihed courses\n";
				break;
			}
			for (int i = 0; i < s.FinishedCourses.size(); i++)
			{
				cout << "Name:" << " " << s.FinishedCourses[i].Name << endl;
				cout << "Code:" << " " << s.FinishedCourses[i].Code << endl;
				cout << "Requirement or Elective:" << " " << s.FinishedCourses[i].RequirementOrElective << endl;
				cout << "List of Prerequisite Required Courses:" << endl;
				for (int k = 0; k < s.FinishedCourses[i].ListofPreRequiredCourses.size(); k++)
				{
					cout << " - " << s.FinishedCourses[i].ListofPreRequiredCourses[k] << endl;
				}
				cout << "Hours:" << " " << s.FinishedCourses[i].Hours << endl;
				cout << "Instructor:" << " " << s.FinishedCourses[i].Instructor << endl;
				cout << "****************************************************" << endl;
			}

		}

		else if (choice == 2)

		{

			if (s.CoursesInProgress.size() == 0)
			{
				cout << "you don't have courses in progress\n";
				break;
			}
			for (int i = 0; i < s.CoursesInProgress.size(); i++)
			{
				cout << "Name:" << " " << s.CoursesInProgress[i].Name << endl;
				cout << "Code:" << " " << s.CoursesInProgress[i].Code << endl;
				cout << "Requirement or Elective:" << " " << s.CoursesInProgress[i].RequirementOrElective << endl;
				cout << "List of Prerequisite Required Courses:" << endl;
				for (int k = 0; k < s.CoursesInProgress[i].ListofPreRequiredCourses.size(); k++)
				{
					cout << " - " << s.CoursesInProgress[i].ListofPreRequiredCourses[k] << endl;
				}
				cout << "Hours:" << " " << s.CoursesInProgress[i].Hours << endl;
				cout << "Instructor:" << " " << s.CoursesInProgress[i].Instructor << endl;
				cout << "****************************************************" << endl;

			}

		}
		else if (choice > 3)
		{
			cout << "Enter Correct Number" << endl;
			continue;
		}
	} while (choice != 3);
}


void Student::ViewGradesAndCGPA(Student& s)
{
	float* grades = new float[s.FinishedCourses.size()];
	float total_grades_points = 0;
	float total_hours = 0;
	//converting grades from 100 scale to 4 scale 
	for (int i = 0; i < s.FinishedCourses.size(); i++)
	{
		if (s.FinishedCourses[i].grade < 60)
		{
			grades[i] = 0;
		}
		else
			grades[i] = (s.FinishedCourses[i].grade / 100) * 4;
	}
	//checking for Grade letters for each course
	cout << "Your grades in each course:" << endl;

	for (int i = 0; i < s.FinishedCourses.size(); i++)
	{
		if (s.FinishedCourses[i].grade > 93)
			cout << s.FinishedCourses[i].Name << ":" << " " << 4.0 << " ";
		else
			cout << s.FinishedCourses[i].Name << ":" << " " << grades[i] << " ";
		if (s.FinishedCourses[i].grade >= 97)
			cout << "A+" << endl;
		else if (s.FinishedCourses[i].grade < 97 && s.FinishedCourses[i].grade >= 93)
			cout << "A" << endl;
		else if (s.FinishedCourses[i].grade < 93 && s.FinishedCourses[i].grade >= 89)
			cout << "A-" << endl;
		else if (s.FinishedCourses[i].grade < 89 && s.FinishedCourses[i].grade >= 84)
			cout << "B+" << endl;
		else if (s.FinishedCourses[i].grade < 84 && s.FinishedCourses[i].grade >= 80)
			cout << "B" << endl;
		else if (s.FinishedCourses[i].grade < 80 && s.FinishedCourses[i].grade >= 76)
			cout << "B-" << endl;
		else if (s.FinishedCourses[i].grade < 76 && s.FinishedCourses[i].grade >= 73)
			cout << "C+" << endl;
		else if (s.FinishedCourses[i].grade < 73 && s.FinishedCourses[i].grade >= 70)
			cout << "C" << endl;
		else if (s.FinishedCourses[i].grade < 70 && s.FinishedCourses[i].grade >= 67)
			cout << "C-" << endl;
		else if (s.FinishedCourses[i].grade < 67 && s.FinishedCourses[i].grade >= 64)
			cout << "D+" << endl;
		else if (s.FinishedCourses[i].grade < 64 && s.FinishedCourses[i].grade >= 60)
			cout << "D" << endl;
		else
			cout << "F" << endl;
	}
	cout << "********************************************************" << endl;
	//calculating Cummulative GPA
	if (s.FinishedCourses.empty()) {
		cout << "You didn't finish any course!!!" << endl;
	}
	else
	{
		for (int i = 0; i < s.FinishedCourses.size(); i++)
		{
			total_grades_points += grades[i] * s.FinishedCourses[i].Hours;
			total_hours += s.FinishedCourses[i].Hours;
		}


		float cgpa = total_grades_points / total_hours;

		cout << "CGPA:" << " " << cgpa << "\n";
		s.GPA = cgpa;
		//calculating total percentage to get the Final grade 
		float totalpercentage = 0;
		for (int i = 0; i < s.FinishedCourses.size(); i++)
		{
			totalpercentage += s.FinishedCourses[i].grade;
		}
		totalpercentage = (totalpercentage / (100 * s.FinishedCourses.size())) * 100;


		if (totalpercentage >= 97)
			cout << "Grade: A+";
		else if (totalpercentage < 97 && totalpercentage >= 93)
			cout << "Grade: A" << endl;
		else if (totalpercentage < 93 && totalpercentage >= 89)
			cout << "Grade: A-" << endl;
		else if (totalpercentage < 89 && totalpercentage >= 84)
			cout << "Grade: B+" << endl;
		else if (totalpercentage < 84 && totalpercentage >= 80)
			cout << "Grade: B" << endl;
		else if (totalpercentage < 80 && totalpercentage >= 76)
			cout << "Grade: B-" << endl;
		else if (totalpercentage < 76 && totalpercentage >= 73)
			cout << "Grade: C+" << endl;
		else if (totalpercentage < 73 && totalpercentage >= 70)
			cout << "Grade: C" << endl;
		else if (totalpercentage < 70 && totalpercentage >= 67)
			cout << "Grade: C-" << endl;
		else if (totalpercentage < 67 && totalpercentage >= 64)
			cout << "Grade: D+" << endl;
		else if (totalpercentage < 64 && totalpercentage >= 60)
			cout << "Grade: D" << endl;
		else
			cout << "Grade: F" << endl;
	}
}

void Student::EditData(Student& s)
{
	char ans;
	bool flag = false;
	string oldpassword, newpassword;
	do
	{
		cout << "Enter Your Old Password\n";
		cin >> oldpassword;
		if (oldpassword == s.Password)
		{
			cout << "Enter Your New Password\n";
			cin >> newpassword;
			s.Password = newpassword;
			flag = true;
			break;
		}
		else
		{
			cout << "Incorrect Password\n";
			cout << "do you want to try again (Y\y)\n";
			cin >> ans;
		}
	} while (ans == 'y' || ans == 'Y' && flag == false);
}

void Student::FillFeedback(Student s, vector<Feedback>& fb, vector<Course>c)
{
	Feedback temp;  int num = 0;
	char suggest;
	cout << endl;
	char ans = 'n';
	int counter = 0;
	cout << "\t \t Feedback Form" << endl;
	do {
		if (s.FinishedCourses.size() == 0)
		{
			cout << "You don't have finished Courses\n";
			break;
		}
		temp.StudentName = "Anonymous";
		cout << "choose course to fill its feedback form" << endl;
		for (int i = 0; i < s.FinishedCourses.size(); i++)
		{
			cout << i + 1 << ")" << s.FinishedCourses[i].Name << endl;
		}
		cin >> num;
		num = num - 1;
		temp.CourseName = s.FinishedCourses[num].Name;
		temp.code = s.FinishedCourses[num].Code;
		system("CLS");
		cout << "\t \t Feedback Form for " << temp.CourseName << endl;
		//questions
		cout << "please rate these criteria in a scale from 1 to 10" << endl;
		cout << endl;
		cout << "1)Course content was informative and well organized" << endl;
		cin >> temp.content;
		cout << "2)Course TAs were accessible & provided enough support" << endl;
		cin >> temp.TA;
		cout << "3)Course helped me improve my technicalities and critical thinking" << endl;
		cin >> temp.skills;
		cout << "4)Course doctor delivered information to be easily understood and recalled" << endl;
		cin >> temp.doctor;
		cout << "5)Examinations fairly evaluated my well studied and revised information" << endl;
		cin >> temp.exam;
		cout << "6)Course was well bounded to reallife requirements in the field" << endl;
		cin >> temp.reallife;
		cout << "7)LAST QUESTION: rate course out of 10" << endl;
		cin >> temp.courserate;
		cout << "Do you have ans Suggestions for us ?(y/n)\n";
		cin >> suggest;
		if (suggest == 'y' || suggest == 'Y')
		{
			cin.ignore();
			getline(cin, temp.suggestion);

		}
		else
			temp.suggestion = "No suggestion";
		for (int m = 0; m < c.size(); m++)
		{
			if (temp.code == c[m].Code)
			{
				c[m].number_of_filled_feedbacks++;
				c[m].sum_of_rates += temp.courserate;
				c[m].avg_rate = c[m].sum_of_rates / c[m].number_of_filled_feedbacks;
				break;
			}

		}
		fb.push_back(temp);
		for (int k = 0; k < c.size(); k++)
		{
			for (int m = 0; m < fb.size(); m++)
			{
				if (c[k].Code == fb[m].code)
				{
					fb[m].avg = c[k].avg_rate;

				}
			}
		}
		counter++;
		if (counter < s.FinishedCourses.size())
		{
			cout << "do you want to fill another feedback? (y/n)" << endl;
			cin >> ans;
		}
		else
			break;
	} while (ans == 'y' || ans == 'Y');
	//write vector to file
	std::ofstream
		file("fb.txt");
	if (file.is_open())
	{
		for (int j = 0; j < fb.size(); j++)
		{
			file << fb[j].StudentName << endl;
			file << fb[j].CourseName << endl;
			file << fb[j].content << endl;
			file << fb[j].TA << endl;
			file << fb[j].skills << endl;
			file << fb[j].doctor << endl;
			file << fb[j].exam << endl;
			file << fb[j].reallife << endl;
			file << fb[j].avg << endl;
			file << fb[j].suggestion << endl;
		}
	}
}
