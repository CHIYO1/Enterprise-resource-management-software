#include "StudentManager.h"

int main() {
	StudentManager* SManager = StudentManager::getinstance();
	vector<Student> Stu;
	Student stu1 = { 1233,"����","��2��" };
	Student stu2 = { 2222,"Ҧ��","��3��" };
	Student stu3 = { 2222,"���Ͱ���","��5��" };
	//SManager->insert_student(stu1);
	//SManager->delete_student(1233);
	//SManager->insert_student(stu2);
	//SManager->updata_student(stu3);
	Stu=SManager->get_students();
	for (auto i : Stu) {
		cout << i.id << " " << i.name << " " << i.Class << endl;
	}
	return 0;
}
