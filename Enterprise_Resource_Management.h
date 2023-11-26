#ifndef _ENTERPRISE_RESOURCE_MANAGEMENT_H
#define _ENTERPRISE_RESOURCE_MANAGEMENT_H

#include<iostream>
#include<mysql.h>
#include<string>
#include<vector>

//链接数据库
class Database
{
public:
	static MYSQL* getinstance();
	~Database();
	MYSQL* connect;
private:
	Database();
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* pw = "123456";
	const char* database_name = "enterprise_resource_planning";
	const int port = 3306;
};

//总账表 (General Ledger)

struct general_ledger_data {
	int account_id;
	std::string transaction_type;
	int amount;
};

class general_ledger {
public:
	general_ledger() :con(Database::getinstance()) {};
	bool insert_data(general_ledger_data& row);
	bool updata_data(general_ledger_data& row);
	bool delete_data(int account_id);
	std::vector<general_ledger_data> get_data(std::string condition = "");

private:
	MYSQL* con;
	const char* col1 = "account_id";
	const char* col2 = "transaction_type";
	const char* col3 = "amount";
};

//明细账表 (Ledger Details)           
struct ledger_details_data {
	int detail_id;
	std::string transaction_date;
	int account_id;
	std::string transaction_type;
	int amount;
};

class ledger_details {
public:
	ledger_details() :con(Database::getinstance()) {};
	bool insert_data(ledger_details_data& row);
	bool updata_data(ledger_details_data& row);
	bool delete_data(int detail_id);
	std::vector<ledger_details_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "detail_id";
	const char* col2 = "transaction_date";
	const char* col3 = "account_id";
	const char* col4 = "transaction_type";
	const char* col5 = "amount";
};

//损益表 (Income Statement)
struct Income_Statement_data {
	std::string date;
	int income;
	int cost;
	int profit;
};

class Income_Statement {
public:
	Income_Statement():con(Database::getinstance()) {};
	bool insert_data(Income_Statement_data& row);
	bool updata_data(Income_Statement_data& row);
	bool delete_data(std::string date);
	std::vector<Income_Statement_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "date";
	const char* col2 = "income";
	const char* col3 = "cost";
	const char* col4 = "profit";
};

//成本项目表 (Cost Items)    
struct Cost_Items_data {
	int cost_item_id;
	std::string cost_type;
	int amount;
	int related_project_id;
};

class Cost_Items {
public:
	Cost_Items():con(Database::getinstance()) {};
	bool insert_data(Cost_Items_data& row);
	bool updata_data(Cost_Items_data& row);
	bool delete_data(std::string cost_item_id);
	std::vector<Cost_Items_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "cost_item_id";
	const char* col2 = "cost_type";
	const char* col3 = "amount";
	const char* col4 = "related_project_id";
};

//预算表 (Budget)
struct Budget_data {
	int budget_id;
	int department_id;
	int budget_amount;
	int actual_expense;
	int budget_difference;
};

class Budget {
public:
	Budget() :con(Database::getinstance()) {};
	bool insert_data(Budget_data& row);
	bool updata_data(Budget_data& row);
	bool delete_data(std::string budget_id);
	std::vector<Budget_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "budget_id";
	const char* col2 = "department_id";
	const char* col3 = "budget_amount";
	const char* col4 = "actual_expense";
	const char* col5 = "budget_difference";
};

//员工档案表 (Employee Profiles)
struct employee_profiles_data {
	int employee_id;
	std::string name;
	std::string contact_info;
	std::string employment_history;
	std::string training_records;
};

class employee_profiles {
public:
	employee_profiles() :con(Database::getinstance()) {};
	bool insert_data(employee_profiles_data& row);
	bool updata_data(employee_profiles_data& row);
	bool delete_data(std::string employee_id);
	std::vector<employee_profiles_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "employee_id";
	const char* col2 = "name";
	const char* col3 = "contact_info";
	const char* col4 = "employment_history";
	const char* col5 = "training_records";
};

//招聘信息表 (Recruitment)   
struct recruitment_data {
	int recruitment_id;
	int position_id;
	int candidate_id;
	std::string candidate_name;
	std::string interview_time;
	std::string recruitment_status;
};

class recruitment {
public:
	recruitment() :con(Database::getinstance()) {};
	bool insert_data(recruitment_data& row);
	bool updata_data(recruitment_data& row);
	bool delete_data(std::string recruitment_id);
	std::vector<recruitment_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "recruitment_id";
	const char* col2 = "position_id";
	const char* col3 = "candidate_id";
	const char* col4 = "candidate_name";
	const char* col5 = "interview_time";
	const char* col6 = "recruitment_status";
};

//薪酬表 (Payroll)                    
struct payroll_data {
	int compensation_id;
	int employee_id;
	double base_salary;
	double allowance;
	double bonus;
};
class payroll {
public:
	payroll() :con(Database::getinstance()) {};
	bool insert_data(payroll_data& row);
	bool updata_data(payroll_data& row);
	bool delete_data(int conpensation_id);
	std::vector<payroll_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "compensation_id";
	const char* col2 = "employee_id";
	const char* col3 = "base_salary";
	const char* col4 = "allowance";
	const char* col5 = "bonus";
};

//绩效表 (Performance)  
struct performance_data {
	int performance_id;
	int employee_id;
	std::string goal_setting;
	std::string assessment_result;
};
class performance {
public:
	performance() :con(Database::getinstance()) {};
	bool insert_data(performance_data& row);
	bool updata_data(performance_data& row);
	bool delete_data(int performance_id);
	std::vector<performance_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "performance_id";
	const char* col2 = "employee_id";
	const char* col3 = "goal_setting";
	const char* col4 = "assessment_result";
};

//客户信息表 (Customer Information)     
struct customer_data {
	int customer_id;
	std::string name;
	std::string contact_info;
	std::string purchase_history;
};
class customer {
public:
	customer() :con(Database::getinstance()) {};
	bool insert_data(customer_data& row);
	bool updata_data(customer_data& row);
	bool delete_data(int customer_id);
	std::vector<customer_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "customer_id";
	const char* col2 = "name";
	const char* col3 = "contact_info";
	const char* col4 = "purchase_history";
};

//销售订单表 (Sales Orders) 
struct sales_orders_data {
	int order_id;
	int customer_id;
	int product_id;
	int quantity;
	double price;
};
class sales_orders {
public:
	sales_orders() :con(Database::getinstance()) {};
	bool insert_data(sales_orders_data& row);
	bool updata_data(sales_orders_data& row);
	bool delete_data(int order_id);
	std::vector<sales_orders_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "order_id";
	const char* col2 = "customer_id";
	const char* col3 = "product_id";
	const char* col4 = "quantity";
	const char* col5 = "price";
};

//库存表 (Inventory)    
struct inventory_data {
	int product_id;
	int stock_quantity;
	std::string entry_date;
	int supplier_id;
};
class inventory {
public:
	inventory() :con(Database::getinstance()) {};
	bool insert_data(inventory_data& row);
	bool updata_data(inventory_data& row);
	bool delete_data(int product_id);
	std::vector<inventory_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "product_id";
	const char* col2 = "stock_quantity";
	const char* col3 = "entry_date";
	const char* col4 = "supplier_id";
};

//渠道合作伙伴表 (Channel Partners)  
struct channel_partners_data {
	int partner_id;
	std::string channel_type;
	std::string coordinate_promotions;
};
class channel_partners {
public:
	channel_partners() :con(Database::getinstance()) {};
	bool insert_data(channel_partners_data& row);
	bool updata_data(channel_partners_data& row);
	bool delete_data(int partner_id);
	std::vector<channel_partners_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "partner_id";
	const char* col2 = "channel_type";
	const char* col3 = "coordinate_promotions";
};

//供应商表 (Suppliers)                       
struct suppliers_data {
	int supplier_id;
	std::string name;
	std::string contact_info;
	std::string contract_history;
};
class suppliers {
public:
	suppliers() :con(Database::getinstance()) {};
	bool insert_data(suppliers_data& row);
	bool updata_data(suppliers_data& row);
	bool delete_data(int supplier_id);
	std::vector<suppliers_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "supplier_id";
	const char* col2 = "name";
	const char* col3 = "contact_info";
	const char* col4 = "contract_history";
};

//采购订单表 (Purchase Orders) 
struct purchase_orders_data {
	int order_id;
	int supplier_id;
	int product_id;
	int quantity;
	double price;
};
class purchase_orders {
public:
	purchase_orders() :con(Database::getinstance()) {};
	bool insert_data(purchase_orders_data& row);
	bool updata_data(purchase_orders_data& row);
	bool delete_data(int order_id);
	std::vector<purchase_orders_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "order_id";
	const char* col2 = "supplier_id";
	const char* col3 = "product_id";
	const char* col4 = "quantity";
	const char* col5 = "price";
};

//生产计划表 (Production Plans)                      
struct production_plans_data {
	int plan_id;
	int product_id;
	std::string plan_date;
	int production_quantity;
	std::string production_status;
};
class production_plans {
public:
	production_plans() :con(Database::getinstance()) {};
	bool insert_data(production_plans_data& row);
	bool updata_data(production_plans_data& row);
	bool delete_data(int plan_id);
	std::vector<production_plans_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "plan_id";
	const char* col2 = "product_id";
	const char* col3 = "plan_date";
	const char* col4 = "production_quantity";
	const char* col5 = "production_status";
};

//资源调度表 (Resource Scheduling)
struct resource_scheduling_data {
	int resource_id;
	int plan_id;
	std::string resource_type;
};
class resource_scheduling {
public:
	resource_scheduling() :con(Database::getinstance()) {};
	bool insert_data(resource_scheduling_data& row);
	bool updata_data(resource_scheduling_data& row);
	bool delete_data(int resource_id);
	std::vector<resource_scheduling_data> get_data(std::string condition = "");
private:
	MYSQL* con;
	const char* col1 = "resource_id";
	const char* col2 = "plan_id";
	const char* col3 = "resource_type";
};

#endif