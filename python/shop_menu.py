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

def print_customer(c, s):
    # to check if there is enough products in the stock. 
    check_stock(c, s)
    # to calculate the cost of the bought items
    calculate_costs(c, s)
    # initial value of variable for total order
    total_order = 0

    # printing customer name and budget
    print(f'--------------------------------------------------------')
    print(f'--------------------------------------------------------\n')
    print(f'Customer name: {c.name} \nCustomer budget: {c.budget}')
    print(f'--------------------------------------------------------\n')
    # iterate through all items in the shopping list to calculate the price of the order
    for item in c.shopping_list:
        # printing name and quantity of the product
        print(f'{c.name} orders {item.quantity} of the product')
        # calculating cost = quantity times product price
        cost = item.quantity * item.product.price
        
        
         # Check if the ordered product exists in the shop
        if  (cost == 0):
            print(f"We do not offer {item.product.name} in our shop. Please enter a product from the list above.")
            main()

        total_order += cost
        print(f"The cost to {c.name} will be €{cost:.2f}.\n")

     # checking if the customer has enough money to fulfill the order. Shop cash and stock level will adjust accordingly
    if total_order <= c.budget:
        s.cash += total_order
        # Succesfull transaction
        print(f"The total price of this purchase for {c.name} is €{total_order:.2f}. Transaction successful. {c.name} now has €{c.budget-total_order:.2f}  in the budget. Shop cash is now €{s.cash}.\n")
        # Iterate through all items in shopping list
        for item in c.shopping_list: 
            # Iterate the item from shopping list through the shop stock    
            for pr in s.stock:        
                if item.product.name == pr.product.name:  
                    # Update shop quantities accordingly       
                    pr.quantity = pr.quantity - item.quantity   
    # insufficient funds
    else:
        print(f"The total price of the order for {c.name} is €{total_order:.2f}. Unfortunatelly {c.name} has insufficient funds to complete the transaction.\n")

# print products and thier quantity 
def print_shop(s):
    print(f'Shop has {s.cash:.2f} in cash')
    for item in s.stock:
        print_product(item.product)
        print(f'The Shop has {item.quantity:.0f} of the above')

# check if there is enough products in the shop
def check_stock(c, s):
    # Iterate through all items in shopping list
    for item in c.shopping_list:
        # Iterate the item from shopping list through the shop stock  
        for pr in s.stock:
                if item.product.name == pr.product.name and item.quantity >= pr.quantity:
                    print(f"Unfortunatelly you can not buy {item.product.name}, as there is not enough {item.product.name} in shop stock. Please select again. ")
                    custmenu()
                
# calculating costs
def calculate_costs(c, s):
    # Iterate the item through the shop stock  
    for shop_item in s.stock:
        # Iterate the item from stock through shopping list
        for list_item in c.shopping_list:
            if (list_item.product.name == shop_item.product.name):
                list_item.product.price = shop_item.product.price

# interactive live mode               
def live_mode():
    
    print("----------------------------------------------------\n")
    print("----------------------------------------------------\n")
    print("       Welcome to our Live Shop  \n")
    print("----------------------------------------------------\n")
    print("----------------------------------------------------\n")
    
    # end user is asked to enter their name 
    cust_name = input("Please enter your name: ") 

    # end user is asked to enter their budget 
    try:
        budget= float(input(f"Please enter your budget {cust_name}: "))
    
    except ValueError:
        print("\nPlease enter a float value for the budget.\n")
        live_mode()

    c = Customer(cust_name, budget)
    print("Products available in our shop:")
    print_shop(s)
    shopping_list=[]
    additional_items = "Y"
    while (additional_items == "Y"):
        name = input("What product would you like to buy?: ")
        
        try:
            quantity = int(input("Quantity: "))
        
        except ValueError:
            print ("\nPlease enter an integer value for the quantity. Restarting order process...\n")
            live_mode()

        p = Product(name)
        ps = ProductStock(p, quantity)
        c.shopping_list.append(ps)
        additional_items = input("Would you like to buy any additional items? Y/N \n")

    return c

def display_menu():
    print("MENU")
    print("----------------------------------------------------\n")
    print("1- Choose pre loaded baskets")
    print("2- Live mode")
    print("3- Check shop cash")
    print("4- Check shop cash & stock")
    print("X- Exit")
    print("----------------------------------------------------\n")

# Main menu options
def main():
    while True:
        display_menu()
        choice = input("Choice: ")

        if (choice == "1"):
            custmenu()

        elif (choice == "2"):
            c= live_mode()
            print_customer(c, s)

        elif (choice == "3"):
            print(f"\nThe shop has €{s.cash:.2f}\n")
            
        elif (choice == "4"):
            print_shop(s) 

        elif (choice == "X"):
            exit()

        else:
            print("This is not a valid selection\n")


# Sub menu for displaying customer pre loaded baskets 
def display_custmenu():
    print("1- Sufficient funds")
    print("2- Insufficient funds")
    print("3- Not in stock")
    print("X- Exit")

# Sub menu options
def custmenu():
    while True:
        print("\nCustomer test csv files available-")
        display_custmenu()
        customer_type = input("Choice: ")
        if (customer_type == "1"):
            c = read_customer("../sufficient_funds.csv")
            print_customer(c, s)
        elif (customer_type == "2"):
            c = read_customer("../insufficient_funds.csv")
            print_customer(c, s)
        elif (customer_type == "3"):
            c = read_customer("../not_enough_stock.csv")
            check_stock(c, s)
            
        
        elif (customer_type == "X"):
            exit()
        else:
            print("This is not a valid selection. Please re-select.\n")






if __name__ == "__main__":
    s = create_and_stock_shop()
    print_shop(s)
    
    main()