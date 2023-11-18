#人力资源管理模块数据生成
from faker import Faker
import random
import pandas as pd
from datetime import datetime,timedelta

fake=Faker()

#生成员工信息数据
#生成薪酬数据
#生成绩效数据

employee_profiles_data = [] #员工档案表 (Employee Profiles)数据
payroll_data = [] #薪酬表 (Payroll)
performance_data = [] #绩效表 (Performance)

for i in range(1,5001):
    # 生成唯一的员工ID，姓名和联系信息
    employee_id = fake.unique.random_number(digits=5)
    name = fake.name()
    contact_info = fake.phone_number()

    # 生成雇佣日期、部门和培训日期、培训类型
    hire_date = fake.date_this_decade()
    department = random.choice(["销售部", "生产部", "人力资源部","市场部门","研发/技术部门","客户服务部门","行政部门","法务部门","IT部门"])

    training_date = fake.date_between(start_date=hire_date, end_date='today')
    training_type = random.choice(["产品知识培训", "安全培训", "管理培训","技术培训","法规和合规培训"])

    employee_profiles_data.append({
        '员工ID': employee_id,
        '姓名': name,
        '联系信息': contact_info,
        '雇佣历史': f'{hire_date} ~ 在职，{department}',
        '培训记录': f'{training_date} ~ {training_type}'
    })

    payroll_data.append({
        '薪酬ID': i,
        '员工ID': employee_id,
        '工资': round(fake.random.uniform(4000, 8000), 2),
        '津贴': round(fake.random.uniform(100, 500), 2),
        '奖金': round(fake.random.uniform(100, 500), 2)
    })

    performance_data.append({
        '绩效ID': i,
        '员工ID': employee_id,
        '目标设定': random.choice(["达到销售目标", "提高工作效率", "提升团队合作"]),
        '评估结果': random.choice(["优秀", "良好", "一般"]),
    })

employee_profiles=pd.DataFrame(employee_profiles_data)
payroll=pd.DataFrame(payroll_data)
performance=pd.DataFrame(performance_data)

employee_profiles.to_csv('employee_profiles.csv',index=False)
payroll.to_csv('payroll.csv',index=False)
performance.to_csv('performance.csv',index=False)

#生成招聘和录用数据

recruitment_data = [] #招聘信息表 (Recruitment)数据
for i in range(1,101):
    recruitment_data.append({
        '招聘ID': i,
        '职位ID': fake.unique.random_number(digits=3),
        '候选人ID': fake.unique.random_number(digits=3),
        '候选人姓名': fake.name(),
        '面试时间': fake.date_between(start_date='-1m', end_date='+1m'),
        '招聘状态': random.choice(["进行中", "已结束"])
    })

recruitment=pd.DataFrame(recruitment_data)
recruitment.to_csv('recruitment.csv',index=False)

