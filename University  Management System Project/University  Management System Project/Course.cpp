#include "Course.h"

Course::Course()
{
	Name = Code = Instructor = " ";
	MaximumNumberofStudents = Hours = grade = 0;
	number_of_filled_feedbacks = sum_of_rates = avg_rate = 0;

}
Course::Course(string name, string code, bool reqorelec, int maxofstudents, float Grade, vector<string> listsofcourses, int hours, string instructor)
{
	Name = name;
	Code = code;
	RequirementOrElective = reqorelec;
	MaximumNumberofStudents = maxofstudents;
	grade = Grade;
	for (int i = 0; i < listsofcourses.size(); i++)
		ListofPreRequiredCourses.push_back(listsofcourses[i]);
	Hours = hours;
	Instructor = instructor;
	number_of_filled_feedbacks = sum_of_rates = avg_rate = 0;
}
