#生产计划与控制模块生成
from faker import Faker
import random
import pandas as pd
from datetime import datetime,timedelta

fake=Faker()

#生成生产计划数据
#生成生产资源调度数据

production_plans_data = [] #生产计划表 (Production Plans)
resource_scheduling_data = [] #资源调度表 (Resource Scheduling)

product=[]
resource_id=[]
for i in range(1,11):
    product.append (fake.unique.random_number(digits=3))

for i in range(1,21):
    resource_id.append (fake.unique.random_number(digits=3))

for i in range(1, 101):
        production_plans_data.append({
            '计划ID': i,
            '产品ID': random.choice(product),
            '计划日期': fake.date_between(start_date='-5m', end_date='+1m'),
            '生产数量': random.randint(100, 300),
            '生产状态': random.choice(["进行中", "已完成"])
        })

for i in range(1,1001):
        resource_scheduling_data.append({
            '资源ID': random.choice(resource_id),
            '计划ID': random.choice(production_plans_data)['计划ID'],
            '资源类型': random.choice(["生产设备", "生产人力"])
        })


production_plans=pd.DataFrame(production_plans_data)
resource_scheduling=pd.DataFrame(resource_scheduling_data)
production_plans.to_csv('production_plans.csv',index=False)
resource_scheduling.to_csv('resource_scheduling.csv',index=False)