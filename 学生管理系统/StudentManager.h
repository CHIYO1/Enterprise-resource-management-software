#pragma once
#ifndef _StudentManger_H
#define _StudentManager_H

#include<iostream>
#include<mysql.h>
#include<string>
#include<vector>
using namespace std;

struct Student {
	int id;
	string name;
	string Class;
};

class StudentManager
{
public:
	static StudentManager* getinstance();
	~StudentManager();
	bool insert_student(Student& stu);
	bool updata_student(Student& stu);
	bool delete_student(int Student_id);
	vector<Student> get_students(string condition = "");
private:
	StudentManager();
	MYSQL* con;
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* pw = "123456";
	const char* database_name = "test";
	const int port = 3306;
};

#endif