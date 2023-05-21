#pragma once
#include<iostream>
#include <string>
#include<vector>
using namespace std;
class Course
{
public:
	string Name;
	string Code;
	string RequirementOrElective;
	int MaximumNumberofStudents;
	vector<string>ListofPreRequiredCourses;
	int Hours;
	float grade;
	int total_grade = 100;
	string Instructor;
	float number_of_filled_feedbacks;
	float sum_of_rates;
	float avg_rate;
	Course();
	Course(string name, string code, bool reqorelec, int maxofstudents, float Grade, vector<string>listsofcourses, int hours, string instructor);
};
