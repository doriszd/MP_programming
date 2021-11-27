#Multiparadigm programming
# Shop Assignment
# Student: Doris Zdravkovic

from dataclasses import dataclass, field
from typing import List
import csv

# Data class is similar to data container
@dataclass
# Data class Product contains data about its name and price
class Product:
    name: str
    price: float = 0.0

@dataclass 
# Data class ProductStock contains data about its data and quantity
class ProductStock:
    product: Product
    quantity: int

@dataclass 
# Data class Shop contains data about cash and stock
class Shop:
    cash: float = 0.0
    stock: List[ProductStock] = field(default_factory=list)

@dataclass
# Data class Customer contains data - Date, budget and shopping list
class Customer:
    name: str = ""
    budget: float = 0.0
    shopping_list: List[ProductStock] = field(default_factory=list)

# Method to read stock.csv and loop it through the stock
def create_and_stock_shop():
    s = Shop()
    with open('../stock.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        s.cash = float(first_row[0])
        for row in csv_reader:
            p = Product(row[0], float(row[1]))
            ps = ProductStock(p, float(row[2]))
            s.stock.append(ps)
            #print(ps)
    return s
    
# Method to read customer.csv and loop it through the customer
def read_customer(file_path):
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        c = Customer(first_row[0], float(first_row[1]))
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            p = Product(name)
            ps = ProductStock(p, quantity)
            c.shopping_list.append(ps)
        return c 
        

def print_product(p):
    print(f'\nPRODUCT NAME: {p.name} \nPRODUCT PRICE: {p.price}')

def print_customer(c):
    print(f'CUSTOMER NAME: {c.name} \nCUSTOMER BUDGET: {c.budget}')
    
    for item in c.shopping_list:
        print_product(item.product)
        
        print(f'{c.name} ORDERS {item.quantity} OF ABOVE PRODUCT')
        cost = item.quantity * item.product.price
        print(f'The cost to {c.name} will be €{cost}')
        
def print_shop(s):
    print(f'Shop has {s.cash} in cash')
    for item in s.stock:
        print_product(item.product)
        print(f'The Shop has {item.quantity} of the above')

#s = create_and_stock_shop()
#print_shop(s)

c = read_customer("../customer.csv")
print_customer(c)