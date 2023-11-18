#销售与分销管理模块生成
from faker import Faker
import random
import pandas as pd
from datetime import datetime,timedelta

fake=Faker()

#生成客户关系数据
#生成销售订单数据
#生成库存数据

customer_data = [] #客户信息表 (Customer Information)
sales_orders_data = [] #销售订单管理
inventory_data = [] #库存表 (Inventory)

product=[]
customer_id=[]

for i in range(1,10):
    product.append ({
        fake.unique.random_number(digits=3):round(random.uniform(100, 1000), 2)
    })

for i in range(1,100):
    customer_id.append(fake.unique.random_number(digits=3))

for i in customer_id:
    customer_data.append({
        '客户ID': i,
        '姓名': fake.name(),
        '联系信息': fake.phone_number(),
        '购买历史': f"{fake.date_this_decade()} ~ 购买产品{list(random.choice(product).keys())[0]}"
    })

for i in range(1,100001):
    tmp=random.choice(product)
    sales_orders_data.append({
        '订单ID': i,
        '客户ID': random.choice(customer_id),
        '产品ID': list(tmp.keys())[0],
        '数量': random.randint(10, 100),
        '价格': list(tmp.values())[0]
    })

for i in product:
    inventory_data.append({
        '产品ID': list(i.keys())[0],
        '库存数量': random.randint(50, 150),
        '入库日期': fake.date_this_decade(),
        '供应商ID': fake.unique.random_number(digits=3)
    })


customer=pd.DataFrame(customer_data)
sales_orders=pd.DataFrame(sales_orders_data)
inventory=pd.DataFrame(inventory_data)

customer.to_csv('customer.csv',index=False)
sales_orders.to_csv('sales_orders.csv',index=False)
inventory.to_csv('inventory.csv',index=False)

#生成渠道合作伙伴数据

channel_partners_data = [] #渠道合作伙伴表 (Channel Partners)

for i in range(1, 101):
    channel_partners_data.append({
        '合作伙伴ID': i,
        '渠道类型': random.choice(["零售", "分销商"]),
        '协调促销活动': fake.bs()
    })

channel_partners=pd.DataFrame(channel_partners_data)

channel_partners.to_csv('channel_partners.csv',index=False)