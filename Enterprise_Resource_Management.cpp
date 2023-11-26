#define _CRT_SECURE_NO_WARNINGS
#include "Enterprise_Resource_Management.h"

MYSQL* Database::getinstance()
{
	static Database Dbase;
	return Dbase.connect;
}

Database::~Database()
{
	mysql_close(connect);
}

Database::Database()
{
	connect = mysql_init(NULL);
	//ÉèÖÃ×Ö·û±àÂë
	mysql_options(connect, MYSQL_SET_CHARSET_NAME, "GBK");

	if (!mysql_real_connect(connect, host, user, pw, database_name, port, NULL, 0)) {
		fprintf(stderr, "Fail to conect to database : \nError :%s\n", mysql_error(connect));
		exit(1);
	}
}

bool general_ledger::insert_data(general_ledger_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into general_ledger(%s,%s,%s) values(%d,'%s',%d)",
		col1,col2,col3,row.account_id,row.transaction_type.c_str(), row.amount);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool general_ledger::updata_data(general_ledger_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE general_ledger SET transaction_type='%s',amount=%d "
		"where account_id=%d", row.transaction_type.c_str(), row.amount, row.account_id );
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool general_ledger::delete_data(int account_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from general_ledger WHERE account_id=%d", account_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<general_ledger_data> general_ledger::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from general_ledger WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<general_ledger_data> dataList;
	while (row = mysql_fetch_row(res)) {
		general_ledger_data data;
		data.account_id = std::stoi(row[0]);
		data.transaction_type = row[1];
		data.amount = std::stoi(row[2]);
		dataList.push_back(data);
	}
	return dataList;
}

bool ledger_details::insert_data(ledger_details_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into ledger_details(%s,%s,%s,%s,%s) values(%d,'%s',%d,'%s',%d)", 
		col1, col2, col3,col4,col5,row.detail_id,row.transaction_date.c_str(),row.account_id ,row.transaction_type.c_str(),row.amount);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool ledger_details::updata_data(ledger_details_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE ledger_details SET transaction_date='%s',account_id=%d ,transaction_type='%s',amount=%d"
		"where detail_id=%d", row.transaction_date.c_str(), row.account_id, row.transaction_type.c_str(),row.amount,row.detail_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool ledger_details::delete_data(int detail_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from ledger_details WHERE detail_id=%d", detail_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<ledger_details_data> ledger_details::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from ledger_details WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<ledger_details_data> dataList;
	while (row = mysql_fetch_row(res)) {
		ledger_details_data data;
		data.detail_id = std::stoi(row[0]);
		data.transaction_date = row[1];
		data.account_id = std::stoi(row[2]);
		data.transaction_type = row[3];
		data.amount = std::stoi(row[4]);
		dataList.push_back(data);
	}
	return dataList;
}

bool Income_Statement::insert_data(Income_Statement_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into Income_Statement(%s,%s,%s,%s) values('%s',%d,%d,%d)",
		col1, col2, col3, col4, row.date.c_str(),row.income,row.cost,row.profit);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool Income_Statement::updata_data(Income_Statement_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE Income_Statement SET income=%d,cost=%d ,profit=%d"
		"where date='%s'", row.income,row.cost,row.profit,row.date.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool Income_Statement::delete_data(std::string date)
{
	char sql[1024];
	sprintf(sql, "DELETE from Income_Statement WHERE date='%s'", date.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<Income_Statement_data> Income_Statement::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from Income_Statement WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<Income_Statement_data> dataList;
	while (row = mysql_fetch_row(res)) {
		Income_Statement_data data;
		data.date = row[0];
		data.income = std::stoi(row[1]);
		data.cost = std::stoi(row[2]);
		data.profit = std::stoi(row[3]);
		dataList.push_back(data);
	}
	return dataList;
}

bool Cost_Items::insert_data(Cost_Items_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into Cost_Items(%s,%s,%s,%s) values(%d,'%s',%d,%d)",
		col1, col2, col3, col4,row.cost_item_id,row.cost_type.c_str(),row.amount,row.related_project_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool Cost_Items::updata_data(Cost_Items_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE Cost_Items SET cost_type='%s',amount=%d ,related_project_id=%d"
		"where cost_item_id='%s'", row.cost_type.c_str(),row.amount,row.related_project_id,row.cost_item_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool Cost_Items::delete_data(std::string cost_item_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from Cost_Items WHERE cost_item_id=%d", cost_item_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<Cost_Items_data> Cost_Items::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from Cost_Items WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<Cost_Items_data> dataList;
	while (row = mysql_fetch_row(res)) {
		Cost_Items_data data;
		data.cost_item_id = std::stoi(row[0]);
		data.cost_type = row[1];
		data.amount = std::stoi(row[2]);
		data.related_project_id = std::stoi(row[3]);
		dataList.push_back(data);
	}
	return dataList;
}

bool Budget::insert_data(Budget_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into Budget(%s,%s,%s,%s,%s) values(%d,%d,%d,%d,%d)",
		col1, col2, col3, col4,col5, row.budget_id,row.department_id,row.budget_amount,row.actual_expense,row.budget_difference);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool Budget::updata_data(Budget_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE Budget SET department_id=%d,budget_amount=%d ,actual_expense=%d,budget_difference=%d"
		"where budget_id=%d", row.department_id,row.budget_amount,row.actual_expense,row.budget_difference,row.budget_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool Budget::delete_data(std::string budget_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from Budget WHERE budget_id=%d", budget_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<Budget_data> Budget::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from Budget WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<Budget_data> dataList;
	while (row = mysql_fetch_row(res)) {
		Budget_data data;
		data.budget_id = std::stoi(row[0]);
		data.department_id = std::stoi(row[1]);
		data.budget_amount = std::stoi(row[2]);
		data.actual_expense = std::stoi(row[3]);
		data.budget_difference = std::stoi(row[4]);
		dataList.push_back(data);
	}
	return dataList;
}

bool employee_profiles::insert_data(employee_profiles_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into employee_profiles(%s,%s,%s,%s,%s) values(%d,'%s','%s','%s','%s')",
		col1, col2, col3, col4, col5, row.employee_id,row.name.c_str(),row.contact_info.c_str(),row.employment_history.c_str(),row.training_records.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool employee_profiles::updata_data(employee_profiles_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE employee_profiles SET name='%s',contact_info='%s' ,employment_history='%s',training_records='%s'"
		"where employee_id=%d", row.name.c_str(),row.contact_info.c_str(),row.employment_history.c_str(),row.training_records.c_str(),row.employee_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool employee_profiles::delete_data(std::string employee_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from employee_profiles WHERE employee_id=%d", employee_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<employee_profiles_data> employee_profiles::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from employee_profiles WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<employee_profiles_data> dataList;
	while (row = mysql_fetch_row(res)) {
		employee_profiles_data data;
		data.employee_id = std::stoi(row[0]);
		data.name = row[1];
		data.contact_info = row[2];
		data.employment_history = row[3];
		data.training_records = row[4];
		dataList.push_back(data);
	}
	return dataList;
}

bool recruitment::insert_data(recruitment_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into recruitment(%s,%s,%s,%s,%s,%s) values(%d,%d,%d,'%s','%s','%s')",
		col1, col2, col3, col4, col5,col6,
		row.recruitment_id,row.position_id,row.candidate_id,row.candidate_name.c_str(),row.interview_time.c_str(),row.recruitment_status.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool recruitment::updata_data(recruitment_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE recruitment SET position_id=%d,candidate_id=%d ,candidate_name='%s',interview_time='%s',recruitment_status='%s'"
		"where recruitment_id=%d", row.position_id,row.candidate_id,row.candidate_name.c_str(),
		row.interview_time.c_str(),row.recruitment_status.c_str(),row.recruitment_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool recruitment::delete_data(std::string recruitment_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from recruitment WHERE employee_id=%d", recruitment_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<recruitment_data> recruitment::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from recruitment WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<recruitment_data> dataList;
	while (row = mysql_fetch_row(res)) {
		recruitment_data data;
		data.recruitment_id = std::stoi(row[0]);
		data.position_id = std::stoi(row[1]);
		data.candidate_id = std::stoi(row[2]);
		data.candidate_name = row[3];
		data.interview_time = row[4];
		data.recruitment_status = row[5];
		dataList.push_back(data);
	}
	return dataList;
}

bool payroll::insert_data(payroll_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into payroll(%s,%s,%s,%s,%s) values(%d,%d,%.2lf,%.2lf,%.2lf)",
		col1, col2, col3, col4, col5,
		row.compensation_id,row.employee_id,row.base_salary,row.allowance,row.bonus);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool payroll::updata_data(payroll_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE payroll SET employee_id=%d,base_salary=%.2lf ,allowance=%.2lf,bonus=%.2lf"
		"where compensation_id=%d", row.employee_id,row.base_salary,row.allowance,row.bonus,row.compensation_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool payroll::delete_data(int conpensation_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from payroll WHERE conpensation_id=%d", conpensation_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<payroll_data> payroll::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from payroll WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<payroll_data> dataList;
	while (row = mysql_fetch_row(res)) {
		payroll_data data;
		data.compensation_id = std::stoi(row[0]);
		data.employee_id = std::stoi(row[1]);
		data.base_salary = std::stod(row[2]);
		data.allowance = std::stod(row[3]);
		data.bonus = std::stod(row[4]);
		dataList.push_back(data);
	}
	return dataList;
}

bool performance::insert_data(performance_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into performance(%s,%s,%s,%s) values(%d,%d,'%s','%s')",
		col1, col2, col3, col4,row.performance_id, row.employee_id, row.goal_setting.c_str(), row.assessment_result.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool performance::updata_data(performance_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE performance SET employee_id=%d,goal_setting='%s' ,assessment_result= '%s'"
		"where performance_id=%d", row.employee_id, row.goal_setting.c_str() , row.assessment_result.c_str() , row.performance_id );
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool performance::delete_data(int performance_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from performance WHERE performance_id=%d", performance_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<performance_data> performance::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from performance WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<performance_data> dataList;
	while (row = mysql_fetch_row(res)) {
		performance_data data;
		data.performance_id = std::stoi(row[0]);
		data.employee_id = std::stoi(row[1]);
		data.goal_setting = row[2];
		data.assessment_result = row[3];
		dataList.push_back(data);
	}
	return dataList;
}

bool customer::insert_data(customer_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into customer(%s,%s,%s,%s) values(%d,'%s','%s','%s')",
		col1, col2, col3, col4, row.customer_id, row.name.c_str(), row.contact_info.c_str(), row.purchase_history.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool customer::updata_data(customer_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE customer SET name='%s',contact_info='%s' ,purchase_history= '%s'"
		"where customer_id=%d", row.name.c_str(), row.contact_info.c_str(), row.purchase_history.c_str(), row.customer_id );
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool customer::delete_data(int customer_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from customer WHERE customer_id=%d", customer_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<customer_data> customer::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from customer WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<customer_data> dataList;
	while (row = mysql_fetch_row(res)) {
		customer_data data;
		data.customer_id = std::stoi(row[0]);
		data.name = row[1];
		data.contact_info = row[2];
		data.purchase_history = row[3];
		dataList.push_back(data);
	}
	return dataList;
}

bool sales_orders::insert_data(sales_orders_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into sales_orders(%s,%s,%s,%s,%s) values(%d,%d,%d,%d,%.2lf)",
		col1, col2, col3, col4,col5, row.order_id, row.customer_id, row.product_id, row.quantity,row.price);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool sales_orders::updata_data(sales_orders_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE sales_orders SET customer_id=%d ,product_id=%d ,quantity= %d,price=%.2lf"
		"where order_id=%d", row.customer_id, row.product_id, row.quantity, row.price,row.order_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool sales_orders::delete_data(int order_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from sales_orders WHERE order_id=%d", order_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<sales_orders_data> sales_orders::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from sales_orders WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<sales_orders_data> dataList;
	while (row = mysql_fetch_row(res)) {
		sales_orders_data data;
		data.order_id = std::stoi(row[0]);
		data.customer_id = std::stoi(row[1]);
		data.product_id = std::stoi(row[2]);
		data.quantity = std::stoi(row[3]);
		data.price = std::stod(row[4]);
		dataList.push_back(data);
	}
	return dataList;
}

bool inventory::insert_data(inventory_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into inventory(%s,%s,%s,%s) values(%d,%d,'%s',%d)",
		col1, col2, col3, col4 , row.product_id,row.stock_quantity,row.entry_date,row.supplier_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool inventory::updata_data(inventory_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE inventory SET stock_quantity=%d ,entry_date='%s' ,supplier_id= %d"
		"where product_id=%d", row.stock_quantity, row.entry_date.c_str(), row.supplier_id, row.product_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool inventory::delete_data(int product_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from inventory WHERE product_id=%d", product_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<inventory_data> inventory::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from inventory WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<inventory_data> dataList;
	while (row = mysql_fetch_row(res)) {
		inventory_data data;
		data.product_id = std::stoi(row[0]);
		data.stock_quantity = std::stoi(row[1]);
		data.entry_date = row[2];
		data.supplier_id = std::stoi(row[3]);
		dataList.push_back(data);
	}
	return dataList;
}

bool channel_partners::insert_data(channel_partners_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into channel_partners(%s,%s,%s) values(%d,'%s','%s')",
		col1, col2, col3, row.partner_id, row.channel_type.c_str(), row.coordinate_promotions.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool channel_partners::updata_data(channel_partners_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE channel_partners SET channel_type='%s' ,coordinate_promotions='%s' "
		"where partner_id=%d", row.channel_type.c_str(), row.coordinate_promotions.c_str(), row.partner_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool channel_partners::delete_data(int partner_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from channel_partners WHERE partner_id=%d", partner_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<channel_partners_data> channel_partners::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from channel_partners WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<channel_partners_data> dataList;
	while (row = mysql_fetch_row(res)) {
		channel_partners_data data;
		data.partner_id = std::stoi(row[0]);
		data.channel_type = row[1];
		data.coordinate_promotions = row[2];
		dataList.push_back(data);
	}
	return dataList;
}

bool suppliers::insert_data(suppliers_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into suppliers(%s,%s,%s,%s) values(%d,'%s','%s','%s')",
		col1, col2, col3, col4, row.supplier_id, row.name.c_str(), row.contact_info.c_str(), row.contract_history.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool suppliers::updata_data(suppliers_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE suppliers SET name='%s' ,contact_info='%s' ,contract_history='%s'"
		"where supplier_id=%d", row.name.c_str(), row.contact_info.c_str(), row.contract_history.c_str(), row.supplier_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool suppliers::delete_data(int supplier_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from suppliers WHERE supplier_id=%d", supplier_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<suppliers_data> suppliers::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from suppliers WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<suppliers_data> dataList;
	while (row = mysql_fetch_row(res)) {
		suppliers_data data;
		data.supplier_id = std::stoi(row[0]);
		data.name = row[1];
		data.contact_info = row[2];
		data.contract_history = row[3];
		dataList.push_back(data);
	}
	return dataList;
}

bool purchase_orders::insert_data(purchase_orders_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into purchase_orders(%s,%s,%s,%s,%s) values(%d,%d,%d,%d,%.2lf)",
		col1, col2, col3, col4, col5, row.order_id, row.supplier_id, row.product_id, row.quantity,row.price);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool purchase_orders::updata_data(purchase_orders_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE purchase_orders SET supplier_id=%d ,product_id=%d ,quantity=%d,price=%.2lf"
		"where order_id=%d", row.supplier_id, row.product_id, row.quantity, row.price, row.order_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool purchase_orders::delete_data(int order_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from purchase_orders WHERE order_id=%d", order_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<purchase_orders_data> purchase_orders::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from purchase_orders WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<purchase_orders_data> dataList;
	while (row = mysql_fetch_row(res)) {
		purchase_orders_data data;
		data.order_id = std::stoi(row[0]);
		data.supplier_id = std::stoi(row[1]);
		data.product_id = std::stoi(row[2]);
		data.quantity = std::stoi(row[3]);
		data.price = std::stod(row[4]);
		dataList.push_back(data);
	}
	return dataList;
}

bool production_plans::insert_data(production_plans_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into production_plans(%s,%s,%s,%s,%s) values(%d,%d,'%s',%d,'%s')",
		col1, col2, col3, col4, col5, row.plan_id, row.product_id, row.plan_date.c_str(), row.production_quantity, row.production_status.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool production_plans::updata_data(production_plans_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE production_plans SET product_id=%d ,plan_date='%s' ,production_quantity=%d,production_status='%s'"
		"where plan_id=%d", row.product_id, row.plan_date.c_str(), row.production_quantity, row.production_status.c_str() , row.plan_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool production_plans::delete_data(int plan_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from production_plans WHERE plan_id=%d", plan_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<production_plans_data> production_plans::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from production_plans WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<production_plans_data> dataList;
	while (row = mysql_fetch_row(res)) {
		production_plans_data data;
		data.plan_id = std::stoi(row[0]);
		data.product_id = std::stoi(row[1]);
		data.plan_date = row[2];
		data.production_quantity = std::stoi(row[3]);
		data.production_status = row[4];
		dataList.push_back(data);
	}
	return dataList;
}

bool resource_scheduling::insert_data(resource_scheduling_data& row)
{
	char sql[1024];
	sprintf(sql, "INSERT into production_plans(%s,%s,%s) values(%d,%d,'%s')",
		col1, col2, col3 , row.resource_id, row.plan_id, row.resource_type.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool resource_scheduling::updata_data(resource_scheduling_data& row)
{
	char sql[1024];
	sprintf(sql, "UPDATE resource_scheduling SET plan_id=%d ,resource_type='%s'"
		"where resource_id=%d",row.plan_id, row.resource_type.c_str() , row.resource_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to updata data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool resource_scheduling::delete_data(int resource_id)
{
	char sql[1024];
	sprintf(sql, "DELETE from resource_scheduling WHERE resource_id=%d", resource_id);
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data.\nError:%s\n", mysql_error(con));
		return false;
	}
	return true;
}

std::vector<resource_scheduling_data> resource_scheduling::get_data(std::string condition)
{
	char sql[1024];
	sprintf(sql, "SELECT * from resource_scheduling WHERE %s", condition.c_str());
	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to select data.\nError:%s\n", mysql_error(con));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	std::vector<resource_scheduling_data> dataList;
	while (row = mysql_fetch_row(res)) {
		resource_scheduling_data data;
		data.resource_id = std::stoi(row[0]);
		data.plan_id = std::stoi(row[1]);
		data.resource_type = row[2];
		dataList.push_back(data);
	}
	return dataList;
}
