#pragma once
#include "Course.h"
#include"Student.h"
#include<iostream>
#include <string>
#include<unordered_map>
#include<vector>
using namespace std;


// Hash function for strings
struct StringHasher
{
	size_t operator()(const string& st) const
	{
		return hash<string>()(st);
	}
};

class Admin
{
public:
	string userName;
	string Password;
	Admin();
	Admin(string username, string password);
	bool Login(vector<Admin>ADMINS, string username, string password);
	void AddCourse(vector<Course>& courseList);
	void StudentsInASpecificCourse(vector<Student>student, char CourseType, string CourseName);
	void AddStudent(vector <Student>& students, string name);
	void AddGrades(vector <Student>& students);
	void view_student_details(vector<Student>s);
	void EditCourse(vector <Course>& courses);
	void RemoveStudent(vector<Student>& student);
	void RemoveCourse(vector<Student>& student, vector <Course>& courses);
	void AdminMenu(vector<Admin>& admins, vector<Student>& students, vector<Course>& courses, vector<Feedback>& feedback);
	void CoursesReport(vector<Student> student, vector<Course> course);
	void view_feedback(vector<Feedback>fb,vector<Course>c);
};