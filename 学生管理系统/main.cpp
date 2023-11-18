#include "StudentManager.h"

int main() {
	StudentManager* SManager = StudentManager::getinstance();
	vector<Student> Stu;
	Student stu1 = { 1233,"ÀîËÄ","Èí¹¤2°à" };
	Student stu2 = { 2222,"Ò¦Îå","Èí¹¤3°à" };
	Student stu3 = { 2222,"°¢°Í°¢°Í","Èí¹¤5°à" };
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
