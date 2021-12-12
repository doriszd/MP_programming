import csv

class Product:

    def __init__(self, name, price=0):
        self.name = name
        self.price = price
    
    def __repr__(self):
        return f'PRODUCT NAME: {self.name} PRODUCT PRICE: {self.price:.2f}'

class ProductStock:
    
    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity
    
    def name(self):
        return self.product.name;
    
    def unit_price(self):
        return self.product.price;
        
    def cost(self):
        return self.unit_price() * self.quantity
        
    def __repr__(self):
        return f"{self.product} \nThe Shop has: {self.quantity:.0f} of the above "

class Customer:

    def __init__(self, path):
        self.shopping_list = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.name = first_row[0]
            self.budget = float(first_row[1])
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                p = Product(name)
                ps = ProductStock(p, quantity)
                self.shopping_list.append(ps) 

    def __repr__(self):
        
        str = f""
        Customer.check_stock(self)                  # Check stock levels are adequate to cover customers order
        Customer.calculate_costs(self, s.stock)
        str += f"Customer name: {self.name} \nCustomer budget: {self.budget:.2f}\n"

        for item in self.shopping_list:
            cost = item.cost()
            #str += f"\n{item}"
            if (cost == 0):
                print(f"We do not offer {item.product.name} in our shop. Please enter a product from the list above.")
                Menu().main()
            else:
                str += f"The cost to {self.name} will be €{cost:.2f}.\n"
                
        if Customer.order_cost(self)<= self.budget:
            s.cash += Customer.order_cost(self)
            # Succesfull transaction
            str +=f"The total price of this purchase for {self.name} is €{Customer.order_cost(self):.2f}. Transaction successful. {self.name} now has €{self.budget-order_cost:.2f}  in the budget. Shop cash is now €{s.cash}.\n"
            # Iterate through all items in shopping list
            for item in self.shopping_list: 
            # Iterate the item from shopping list through the shop stock    
                for pr in s.stock:        
                    if item.product.name == pr.product.name:  
                    # Update shop quantities accordingly       
                        pr.quantity = pr.quantity - item.quantity   
    # insufficient funds
        else:
            str += f"The total price of the order for {self.name} is €{Customer.order_cost(self):.2f}. Unfortunatelly {self.name} has insufficient funds to complete the transaction.\n"
        return str
                
    def calculate_costs(self, price_list):
        for shop_item in price_list:
            for list_item in self.shopping_list:
                if (list_item.name() == shop_item.name()):
                    list_item.product.price = shop_item.unit_price()
    
    def order_cost(self):
        total_order = 0
        
        for list_item in self.shopping_list:
            total_order += list_item.cost()
        
        return total_order

    # Check shop has adequate stocks to fulfill order
    def check_stock(self):
    # Iterate through all items in shopping list
        for item in self.shopping_list:
        # Iterate the item from shopping list through the shop stock  
            for pr in s.stock:
                if item.product.name == pr.product.name and item.quantity > pr.quantity:
                    print(f"Unfortunatelly you can not buy {item.product.name}, as there is not enough {item.product.name} in shop stock. Please select again. ")
                    Menu().custmenu()


class live_mode():
    
    print("----------------------------------------------------\n")
    print("----------------------------------------------------\n")
    print("       Welcome to our Live Shop  \n")
    print("----------------------------------------------------\n")
    print("----------------------------------------------------\n")
    
    # end user is asked to enter their name 
    def __init__(self):
        self.name = input("What is your name? ")

    # end user is asked to enter their budget 
        try:
            self.budget= float(input(f"Please enter your budget {cust_name}: "))
    
        except ValueError:
            print("\nPlease enter a float value for the budget.\n")
            live_mode()

    
    print("Products available in our shop:")
    print(s)
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
        additional_items = input("Would you like to buy any other items? Y/N \n")

    def __repr__(self):    
        return Customer.__repr__(self)   
        
class Shop:
    
    def __init__(self, file_path):
        self.stock = []
        with open(file_path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.cash = float(first_row[0])
            for row in csv_reader:
                p = Product(row[0], float(row[1]))
                ps = ProductStock(p, float(row[2]))
                self.stock.append(ps)
    
    def __repr__(self):
        str = ""
        str += f'Shop has {self.cash} in cash\n'
        for item in self.stock:
            str += f"{item}\n"
        return str


class Menu:

    # printing menu options
    def display_menu(self):
        print("MENU")
        print("----------------------------------------------------\n")
        print("1- Test menu")
        print("2- Live mode")
        print("3- Check shop cash")
        print("4- Check shop cash & stock")
        print("X- Exit")
        print("----------------------------------------------------\n")

# Main menu options
    def main():
        while True:
        # printing menu options
            self.display_menu()
            choice = input("Choice: ")
            # if end user chooses 1 it will lead him to test menu
            if (choice == "1"):
                self.custmenu()
            # if end user chooses 2 it will lead him to live mode
            elif (choice == "2"):
                c= live_mode()
                print_customer(c)
            # if end user chooses 3 it will print shop cash
            elif (choice == "3"):
                print(f"\nThe shop has €{s.cash:.2f}\n")
            # if end user chooses 4 if will print shop cash and stock    
            elif (choice == "4"):
                print(s) 
            # end user will enter X to exit the app
            elif (choice == "X"):
                exit()

            else:
                print("Please choose from 1 to 4 or X to exit the app\n")


# Test menu 
    def display_custmenu(self):
        print("1- Sufficient funds")
        print("2- Insufficient funds")
        print("3- Not in stock")
        print("X- Exit")

    # Test menu options
    def custmenu(self):
        while True:
                print("\nCustomer test csv files available-")
                self.display_custmenu()
                customer_type = input("Choice: ")
                if (customer_type == "1"):
                    c = Customer("../sufficient_funds.csv")
                    print(c)
                elif (customer_type == "2"):
                    c = Customer("../insufficient_funds.csv")
                    print(c)
                elif (customer_type == "3"):
                    c = Customer("../not_enough_stock.csv")
                    print(c)
            
        
                elif (customer_type == "X"):
                    exit()
                else:
                    print("This is not a valid selection. Please re-select.\n")





if __name__=="__main__":
    s = Shop("../stock.csv")
    print(s)

    Menu().main()