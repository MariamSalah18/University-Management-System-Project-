#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include "Student.h"
#include "Course.h"
#include "Admin.h"
using namespace std;
void readFromFile();
void readCourses();
void readStudents();
void readAdmins();
void readFeedback();
void writeStudent();
void writeCourses();
vector<Course>courses;
vector<Student> students;
vector <Feedback> feedback;
vector<Admin> admins;

int main()
{
	readFromFile();
	char n;
	int index;
	string email, password;
	cout << "                                     Welcome To University Management System\n\n";
	while (true)
	{


		cout << "press A for admin or S for student(Q for Quit)\n";
		cin >> n;
		if (n == 'a' || n == 'A')
		{
			Admin a;
			a.AdminMenu(admins, students, courses, feedback);
			writeCourses();
			writeStudent();
		}
		else if (n == 'S' || n == 's')
		{
			Student s;
			cout << "LOGIN as STUDENT\n";
			cout << "Enter your Email\n";
			cin >> email;
			cout << "Enter your Password\n";
			cin >> password;
			index = s.Login(students, email, password);
			if (index > -1)
				s.studentmenu(students, courses, feedback, index);
			writeCourses();
			writeStudent();
		}
		else if (n == 'Q' || n == 'q')
		{
			break;
		}
		else
		{
			cout << "Enter Vaild Character\n";
		}

	}
}
void readFromFile()
{
	readCourses();
	readStudents();
	readAdmins();
	readFeedback();
}
void readStudents()
{
	ifstream input;
	input.open("Students.txt");
	string name, email, password;
	string cname, code, req, instructor, prereq, str;
	int hours, max;
	long long id;
	int max_hours_allowed, academic_year;
	float gpa, grade;
	while (getline(input, name))
	{
		Student s;
		while (getline(input, cname))
		{
			if (cname.empty())
				break;
			Course c;
			getline(input, code);
			getline(input, req);
			input >> max >> grade;
			input.ignore();
			getline(input, prereq);
			stringstream ss(prereq);
			while (getline(ss, str, ','))
			{
				c.ListofPreRequiredCourses.push_back(str);
			}
			input >> hours;
			input.ignore();
			getline(input, instructor);
			c.Name = cname;
			c.Code = code;
			c.RequirementOrElective = req;
			c.MaximumNumberofStudents = max;
			c.Hours = hours;
			c.Instructor = instructor;
			c.grade = grade;
			s.CoursesInProgress.push_back(c);
		}
		input >> id;
		input.ignore();
		getline(input, email);
		getline(input, password);
		input >> max_hours_allowed;
		input.ignore();
		while (getline(input, cname))
		{
			if (cname.empty())
				break;
			Course c;
			getline(input, code);
			getline(input, req);
			input >> max >> grade;
			input.ignore();
			getline(input, prereq);
			stringstream ss(prereq);

			while (getline(ss, str, ','))
			{
				c.ListofPreRequiredCourses.push_back(str);
			}
			input >> hours;
			input.ignore();
			getline(input, instructor);
			c.Name = cname;
			c.Code = code;
			c.RequirementOrElective = req;
			c.MaximumNumberofStudents = max;
			c.Hours = hours;
			c.Instructor = instructor;
			c.grade = grade;
			s.FinishedCourses.push_back(c);
		}
		input >> academic_year >> gpa;
		input.ignore();
		s.Name = name;
		s.ID = id;
		s.Email = email;
		s.Password = password;
		s.MaximumHoursAllowed = max_hours_allowed;
		s.AcademicYear = academic_year;
		s.GPA = gpa;
		students.push_back(s);
	}
	input.close();
}
void readCourses()
{
	ifstream input;
	input.open("Courses.txt");
	string name, req_or_elective, instructor, code, list, line, prereq;
	int hours;
	long long max_no;

	while (getline(input, name))
	{
		Course c;
		getline(input, code);
		getline(input, req_or_elective);
		input >> max_no;
		input.ignore();
		getline(input, line);
		stringstream ss(line);
		while (getline(ss, prereq, ','))
		{
			c.ListofPreRequiredCourses.push_back(prereq);

		}
		input >> hours;
		input.ignore();
		getline(input, instructor);
		c.Name = name;
		c.Code = code;
		c.RequirementOrElective = req_or_elective;
		c.MaximumNumberofStudents = max_no;
		c.Hours = hours;
		c.Instructor = instructor;
		courses.push_back(c);
	}
	input.close();
}
void readAdmins()
{
	ifstream input;
	input.open("Admins.txt");
	string adminname, password;
	while (getline(input, adminname))
	{
		Admin a;
		getline(input, password);
		a.userName = adminname;
		a.Password = password;
		admins.push_back(a);
	}
	input.close();
}

void writeStudent() {
	std::ofstream file("Students.txt");
	if (file.is_open())
	{


		for (int i = 0; i < students.size(); i++) {
			file << students[i].Name << "\n";
			for (auto j = 0; j < students[i].CoursesInProgress.size(); j++)
			{
				file << students[i].CoursesInProgress[j].Name << endl;
				file << students[i].CoursesInProgress[j].Code << endl;
				file << students[i].CoursesInProgress[j].RequirementOrElective << endl;
				file << students[i].CoursesInProgress[j].MaximumNumberofStudents << endl;
				file << students[i].CoursesInProgress[j].grade << endl;
				for (auto k = 0; k < students[i].CoursesInProgress[j].ListofPreRequiredCourses.size(); k++)
				{
					file << students[i].CoursesInProgress[j].ListofPreRequiredCourses[k];
					if (k != students[i].CoursesInProgress[j].ListofPreRequiredCourses.size() - 1)
						file << ",";
				}
				file << endl;
				file << students[i].CoursesInProgress[j].Hours << endl;
				file << students[i].CoursesInProgress[j].Instructor << endl;
			}
			file << endl;
			file << students[i].ID << "\n"
				<< students[i].Email << "\n"
				<< students[i].Password << "\n"
				<< students[i].MaximumHoursAllowed << "\n";
			for (auto j = 0; j < students[i].FinishedCourses.size(); j++)
			{
				file << students[i].FinishedCourses[j].Name << endl;
				file << students[i].FinishedCourses[j].Code << endl;
				file << students[i].FinishedCourses[j].RequirementOrElective << endl;
				file << students[i].FinishedCourses[j].MaximumNumberofStudents << endl;
				file << students[i].FinishedCourses[j].grade << endl;
				for (auto k = 0; k < students[i].FinishedCourses[j].ListofPreRequiredCourses.size(); k++)
				{
					file << students[i].FinishedCourses[j].ListofPreRequiredCourses[k];
					if (k != students[i].FinishedCourses[j].ListofPreRequiredCourses.size() - 1)
						file << ",";
				}
				file << endl;
				file << students[i].FinishedCourses[j].Hours << endl;
				file << students[i].FinishedCourses[j].Instructor << endl;
			}
			file << endl;
			file << students[i].AcademicYear << endl;
			file << students[i].GPA << endl;
		}
		file.close();

	}
	else
		cout << "Error\n";
}
void writeCourses() {
	std::ofstream file("Courses.txt");
	if (file.is_open())
	{
		for (int i = 0; i < courses.size(); i++) {
			file << courses[i].Name << "\n"
				<< courses[i].Code << "\n"
				<< courses[i].RequirementOrElective << "\n"
				<< courses[i].MaximumNumberofStudents << "\n";
			for (auto j = 0; j < courses[i].ListofPreRequiredCourses.size(); j++)
			{
				//sp,ds 
				file << courses[i].ListofPreRequiredCourses[j];
				if (j != courses[i].ListofPreRequiredCourses.size() - 1)
					file << ",";
			}
			file << endl;
			file << courses[i].Hours << endl;
			file << courses[i].Instructor << endl;
		}
		file.close();

	}
	else
		cout << "Error\n";
}
void readFeedback()
{
	ifstream input;
	string studentname, coursename, suggestion;
	int content, TA, skills, doctor, exam, reallife;
	float avg;
	input.open("fb.txt");
	if (input)
	{
		while (getline(input, studentname))
		{
			Feedback fb;
			getline(input, coursename);
			input >> content >> TA >> skills >> doctor >> exam >> reallife >> avg;
			input.ignore();
			getline(input, suggestion);
			fb.StudentName = studentname;
			fb.CourseName = coursename;
			fb.content = content;
			fb.TA = TA;
			fb.skills = skills;
			fb.doctor = doctor;
			fb.exam = exam;
			fb.reallife = reallife;
			fb.suggestion = suggestion;
			fb.avg = avg;
			feedback.push_back(fb);
		}
	}
	else
		cout << "Error opening file fb.txt" << endl;
	input.close();
}
