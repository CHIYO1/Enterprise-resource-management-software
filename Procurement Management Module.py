#采购管理模块生成
from faker import Faker
import random
import pandas as pd
from datetime import datetime,timedelta

fake=Faker()

#生成供应商数据
#生成采购订单数据

suppliers_data = [] #供应商表 (Suppliers)
purchase_orders_data = [] #采购订单表 (Purchase Orders)

product=[]
for i in range(1,10):
    product.append (fake.unique.random_number(digits=3))

for i in range(1,51):
        suppliers_data.append({
            '供应商ID': i,
            '名称': fake.company(),
            '联系信息': fake.phone_number(),
            '合同历史': f"{fake.date_this_decade()} ~ {random.choice(['提供原材料','供应零件'])}"
        })

for i in range(1, 100001):
        purchase_orders_data.append({
            '订单ID': i,
            '供应商ID': random.choice(suppliers_data)['供应商ID'],
            '产品ID': random.choice(product),
            '数量': random.randint(10, 100),
            '价格': round(random.uniform(100, 1000), 2)
        })

suppliers=pd.DataFrame(suppliers_data)
purchase_orders=pd.DataFrame(purchase_orders_data)

purchase_orders.to_csv('purchase_orders.csv',index=False)
suppliers.to_csv('suppliers.csv',index=False)