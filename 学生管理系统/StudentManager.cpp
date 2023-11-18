#define _CRT_SECURE_NO_WARNINGS
#include "StudentManager.h"

StudentManager* StudentManager::getinstance()
{
	static StudentManager SManager;
	return &SManager;
}

StudentManager::~StudentManager()
{
	mysql_close(con);
}

bool StudentManager::insert_student(Student& stu)
{
	char sql[1024];
	sprintf(sql, "INSERT into test(student_id,student_name,class_id) values(%d,'%s','%s')", stu.id, stu.name.c_str(), stu.Class.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool StudentManager::updata_student(Student& stu)
{
	char sql[1024];
	sprintf(sql, "UPDATE test SET student_name='%s',class_id='%s' "
		"where student_id=%d", stu.name.c_str(), stu.Class.c_str(), stu.id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool StudentManager::delete_student(int Student_id)
{
	char sql[1024];
	sprintf(sql,"DELETE from test WHERE student_id=%d",Student_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

vector<Student> StudentManager::get_students(string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from test %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	vector<Student> stuList;
	while (row = mysql_fetch_row(res)) {
		Student stu;
		stu.id = stoi(row[0]);
		stu.name = row[1];
		stu.Class = row[2];
		stuList.push_back(stu);
	}
	return stuList;
}

StudentManager::StudentManager()
{
	con = mysql_init(NULL);
	//ÉèÖÃ×Ö·û±àÂë
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

	if (!mysql_real_connect(con, host, user, pw, database_name, port, NULL, 0)) {
		fprintf(stderr, "Fail to conect to database : \nError :%s\n", mysql_error(con));
		exit(1);
	}
}
