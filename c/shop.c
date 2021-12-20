#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
	char* name;
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};


struct CustQuant {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

void display_menu(struct Shop *shop);  
void display_custmenu(struct Shop *shop);


struct Customer {
	char *name;
	double budget;
	struct CustQuant shoppingBasket[20];
	int index;
	double totalCost;

};

struct Customer custOrder(struct Shop *shop, char *file_path)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

	// Reading csv file
		fp = fopen(file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

		read = getline(&line, &len, fp); 
		// Customer name
		char *c_name = strtok(line, ","); 
		// Customer budget  
		char *c_bud = strtok(NULL, ","); 
		// Assigning memory space to max 50 characters
		char *custName = malloc(sizeof(char) * 50); 
		// Converting budget to float from string 
		double custBudget = atof(c_bud); 
		// Converting price to float 
		strcpy(custName, c_name); 
		// Entering customer details 
		struct  Customer customer = {custName, custBudget}; 
		printf("Customer name: %s Customer budget: €%.2f\n\n", customer.name, customer.budget);
		while ((read = getline(&line,  &len, fp)) != -1) {
			// Shopping list item name 
			char *c_prod = strtok(line, ","); 
			// Shopping list quantity
			char *c_quant = strtok(NULL, ","); 
			// Convert quantity to integer  
			int quantity = atoi(c_quant); 
			// Assigning memory space for shopping list
			char *name = malloc(sizeof(char)* 50); 
			// Copy string customer item c
			strcpy(name, c_prod); 
			// Assigning name variable to Product struct
			struct Product product = {name}; 
			// Assigning product and quantity variables to basket
			struct CustQuant basket = {product, quantity}; 
			// Copy to customers shopping basket 
			customer.shoppingBasket[customer.index++] = basket; 
		}

	
		for (int i = 0; i < customer.index; i++)  
		{
			for (int j = 0; j < shop->index; j++)
			{
				if  (strcmp(customer.shoppingBasket[i].product.name, shop->stock[j].product.name)== 0){ 
					customer.shoppingBasket[i].product.price = shop->stock[j].product.price;
					if (customer.shoppingBasket[i].quantity > shop->stock[j].quantity){ 
						printf("Unfortunatelly you can not buy %s, as there is not enough %s in shop stock. Please select again.\n", customer.shoppingBasket[i].product.name);
						display_custmenu(&(*shop));
					} 
				}
			}
		
			// Printing costs
			printf("%s orders %i of the product\n", customer.name, customer.shoppingBasket[i].quantity);
			double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;

			//Adjust total cost of new order for each item added.
			customer.totalCost += cost;
			printf("The cost to %s will be €%.2f\n\n", customer.name, cost);	 
			}

			// Check if customer has enough in their budget to afford the purchase
					if (customer.budget < customer.totalCost){
						printf("The total price of this purchase for %s is €%.2f. Unfortunatelu %s has insufficient funds to complete the transaction.\n", customer.name, customer.totalCost, customer.name);
						return customer;
			}

			// Adjust shop quantities 
			for (int i = 0; i < customer.index; i++){
					shop->stock[i].quantity -= customer.shoppingBasket[i].quantity;
			}

			// Add customer purchase price to shop cash 
			shop->cash +=  customer.totalCost;
			customer.budget -= customer.totalCost;

			printf("The total price of this purchase for %s is €%.2f. Transaction sucessful. %s now has €%.2f in the budget. Shop cash is now €%.2f\n", customer.name, customer.totalCost, customer.name, customer.budget, shop->cash);
		return customer;
}


void printProduct(struct Product prod)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", prod.name, prod.price);
	printf("-------------\n");
}



struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

		read = getline(&line, &len, fp);
		float cash = atof(line);
		// printf("cash in shop is %.2f\n", cash);
	
		struct Shop shop = { cash };

    while ((read = getline(&line, &len, fp)) != -1) {
        	// printf("Retrieved line of length %zu:\n", read);
        	// printf("%s IS A LINE", line);
			char *nam = strtok(line, ",");
			char *pri = strtok(NULL, ",");
			char *qua = strtok(NULL, ",");
			int quantity = atoi(qua);
			double price = atof(pri);
			char *name = malloc(sizeof(char) * 50);
			strcpy(name, nam);
			struct Product product = { name, price };
			struct ProductStock stockItem = { product, quantity };
			shop.stock[shop.index++] = stockItem;
			// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
}

void printShop(struct Shop *shop)
{
	printf("Shop has %.2f in cash\n\n", shop->cash);
	for (int i = 0; i < shop->index; i++)
	{
		printProduct(shop->stock[i].product);
		printf("The shop has %d of the above\n\n", shop->stock[i].quantity);
	}
}

void live_Mode(struct Shop *shop)
{
	printf("----------------------------------------------------\n");
    printf("----------------------------------------------------\n");
    printf("       Welcome to our Live Shop  \n");
    printf("----------------------------------------------------\n");
    printf("----------------------------------------------------\n");
    
    char *custName;
	double custBudget;
	char additional_items[] = "Y"; 
	char *prod;
	int quantity;

    
	
    // End user is asked to enter thier name
	printf("Please enter your name: ");
	fflush(stdin);
	scanf("\n%[^\n]%*c", &custName);
	
	printf("Please enter your budget %s: €", &custName);
	scanf("%lf", &custBudget);

	struct Customer customer = {custName, custBudget};

	printf("Products available in our shop:");
	printShop(&(*shop));

	// System to loop  through adding additional items to the order unless customer types N to indicate they have  no more items to add
	while (strcmp(additional_items, "N") != 0)
	{
		printf("What product would you like to buy?: ");
		fflush(stdin); // Clear output buffer
		scanf("\n%[^\n]%*c", &prod); // \n%[^\n]%*c used to have spaces in input

		printf("Quantity: ");
		fflush(stdin); // Clear output buffer
		scanf("%i", &quantity);

		//char *name = malloc(sizeof(char)* 50);
		//strcpy(name, nam);
		
		struct Product product = {prod};
		struct CustQuant basket = {product, quantity};
		customer.shoppingBasket[customer.index++] = basket;
		
		printf("Would you like to buy any other items? Y/N \n");
		fflush(stdin); // Clear output buffer
		scanf("\n%[^\n]%*c", additional_items);
	}	

	// for loop to iterate customer shopping list items through the shop stock items 
	for (int i = 0; i < customer.index; i++)  
	{
		// nested for loop for checking item pulled f rom customer shopping list against all items in the shop to find a match
		for (int j = 0; j < shop->index; j++)
		{
			// If names match on lists then take price value from shop list and add to customer products for  prices calcs
				if  (strcmp(customer.shoppingBasket[i].product.name, shop->stock[j].product.name)== 0){ 
						customer.shoppingBasket[i].product.price = shop->stock[j].product.price;

					// Check customers order  hasn't gone over what shop has available. If it has inform the customer and re display the selection menu
						if (customer.shoppingBasket[i].quantity > shop->stock[j].quantity){ 
							printf("We do not have enough stock of %s.\n\n", customer.shoppingBasket[i].product.name);
							display_custmenu(&(*shop));
						} 
				}
		}
		// Print off what customer wants and how much it will cost
		printf("%s wants %i of the product %s\n", customer.name, customer.shoppingBasket[i].quantity, customer.shoppingBasket[i].product.name);
		double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;
		
		//Adjust total cost of new order for each item added. Display the cost of the individual item in a summary fashion
		customer.totalCost += cost;
		printf("The cost to %s will be €%.2f\n\n", customer.name, cost);

		// Adjust shop quantities for items purchased
		shop->stock[i].quantity -= customer.shoppingBasket[i].quantity; 
		}

		// Check customer has enough in their budget to afford the purchase
		if (customer.budget < customer.totalCost){
			printf("The total price of the order for %s is €%.2f. %s has insufficient funds to complete the transaction.\n\n", &customer.name, customer.totalCost, &customer.name);
			display_custmenu(&(*shop));
	}

		// Add customer purchase price to shop cash and reduce customers budget
		shop->cash +=  customer.totalCost;
		customer.budget -= customer.totalCost;
		printf("The total price for this purchase for %s is €%.2f. Transaction successful. %s now has €%.2f  in their budget. Shop cash is now €%.2f\n", &customer.name, customer.totalCost, &customer.name, customer.budget, shop->cash);

}




void display_custmenu(struct Shop *shop)
{
	int choice2;
	char * file_path;

	while(1)
	{
		puts("1- Sufficient funds");
		puts("2- Insufficient funds");
		puts("3- Not in stock");
		puts("4- Exit");
		printf("Choice: ");
		fflush(stdin);
		scanf("%i", &choice2);

		switch(choice2){
			case 1:			 
				file_path = "sufficient_funds.csv";
				custOrder(&(*shop), file_path);
				break;
			case 2:
				file_path = "insufficient_funds.csv";
				custOrder(&(*shop), file_path);
				break;
			case 3:
				file_path = "not_enough_stock.csv";
				custOrder(&(*shop), file_path);
				break;
			case 4:
				exit(1);
				break;
		}
	}
}
void display_menu(struct Shop *shop)
{
	int choice;

	while(1)
	{
			puts("\nMENU");
			puts("----------------------------------------------------");
			puts("1- Test menu");
			puts("2- Live mode");
			puts("3- Check shop cash");
			puts("4- Check shop cash & stock");
			puts("X- Exit");
			fflush(stdin);
			scanf("%i", &choice);

			switch(choice){
					case 1: 
							puts("\nCustomer test csv files available-");
							display_custmenu(&(*shop));
							break;
					case 2:
							live_Mode(&(*shop));
							break;
					case 3:
							printf("The shop has €%.2f\n", shop->cash);
							break;
					case 4:
							exit(1);
				
					default:
							puts("Please choose from 1 to 4 or X to exit the app\n");
				
			}
		} 

	}
	int main(void)
	{
			struct Shop shop = createAndStockShop();
			printShop(&shop);
    		display_menu(&shop);

    return 0;
}