#财务管理模块测试数据生成
from faker import Faker
import random
import pandas as pd
from datetime import datetime,timedelta

fake=Faker()

#生成会计核算数据

general_ledger_data=[] #总账表 (General Ledger)数据
ledger_details_data=[] #明细账表 (Ledger Details)数据
for i in range(1,100000):
    ledger_details_data.append({
        '明细ID': i,
        '日期': fake.date_between(start_date='-5y', end_date='+3m'),
        '账户ID': fake.random_int(min=1000, max=1999),
        '交易类型': random.choice(['收入', '支出']),
        '金额': fake.random_int(min=1000, max=10000),
    })

for dictionary in ledger_details_data:
    row={
        '账户ID':dictionary['账户ID'],
        '交易类型':dictionary['交易类型'],
        '金额':dictionary['金额']
    }
    found=False
    for i in general_ledger_data:
        if i['账户ID']==row['账户ID']:
            found=True
            if row['交易类型']==i['交易类型']:
                i['金额']+=row['金额']
            else:
                i['金额'] -= row['金额']
                if i['金额'] < 0:
                    if i['交易类型'] == '收入':
                        i['交易类型'] = '支出'
                    else:
                        i['交易类型'] = '收入'
                    i['金额'] *=-1
            break

    if not found:
        general_ledger_data.append(row)

#生成CSV文件
general_ledger=pd.DataFrame(general_ledger_data)
ledger_details=pd.DataFrame(ledger_details_data)

general_ledger.to_csv('general_ledger.csv',index=False)
ledger_details.to_csv('ledger_details.csv',index=False)



#生成财务报表数据

Income_Statement_data=[] #损益表（Income Statement）数据

for i in range(2000,2025):
    for j in range(1,13):
        current_date=datetime(i,j,1)
        income=fake.random_int(min=100000, max=1000000)
        cost=fake.random_int(min=100000, max=1000000)
        Income_Statement_data.append({
            '日期': current_date.strftime("%Y-%m"),
            '收入': income,
            '成本': cost,
            '利润': income-cost,
            })

Income_Statement=pd.DataFrame(Income_Statement_data)
Income_Statement.to_csv('Income_Statement.csv',index=False)

#生成成本项目表

Cost_Items_data=[] #成本项目表 (Cost Items)数据

for i in range(1,100001):
    Cost_Items_data.append({
        '成本项目':i,
        '成本类型':random.choice(['生产成本','人力成本','研发成本','行政成本','销售和市场成本','环境和社会责任成本']),
        '金额':fake.random_int(min=1000,max=10000),
        '关联项目/产品ID':fake.random_int(min=100,max=1000)
    })

Cost_Items=pd.DataFrame(Cost_Items_data)
Cost_Items.to_csv('Cost_Items.csv',index=False)

#生成预算表

Budget_data=[] #预算表 (Budget)数据

for i in range(1,100001):
    budget = fake.random_int(min=100000, max=1000000)
    expenditures=fake.random_int(min=100000, max=1000000)
    Budget_data.append({
        '预算ID': i,
        '部门ID':fake.random_int(min=100,max=1000),
        '预算金额': budget,
        '实际支出': expenditures,
        '预算差异': budget-expenditures,
        })

Budget=pd.DataFrame(Budget_data)
Budget.to_csv('Budget.csv',index=False)

