#pragma once
#include<iostream>
#include <string>
#include<vector>
#include<map>
#include<unordered_map>
#include "Course.h"
using namespace std;
struct Feedback
{
	string StudentName;
	string CourseName;
	string suggestion;
	string code;
	int content, TA, skills, doctor, exam, reallife, courserate;
	float avg;
};
class Student
{
public:
	string Name;
	int ID;
	string Email;
	string Password;
	int MaximumHoursAllowed;
	vector<Course>FinishedCourses;
	vector<Course>CoursesInProgress;
	int AcademicYear;
	float GPA;
	Student(string name, int id, string email, string password, int maxhours, int academicYear, float gpa, vector<Course>finishedcourses, vector<Course>coursesinprogress);
	Student();
	void studentmenu(vector<Student>& students, vector<Course>& courses, vector<Feedback>& feedback, int index);
	int Login(vector<Student>student, string username, string password);
	bool ViewListOfAllAvailableCourses(Student s, vector<Course> c); //cls
	void FilterCourses(vector<Course> c);
	void FilterStudentCourses(Student std);
	void ViewCourseDetails(vector<Course>c); //cls
	void Register(Student& s, vector<Course> c); //cls
	void ViewAllStudentCourses(Student s);
	void ViewGradesAndCGPA(Student& s);
	void EditData(Student& s);
	void FillFeedback(Student s, vector<Feedback>& fb,vector<Course> c);
};


