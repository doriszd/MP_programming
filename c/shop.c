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
	struct ProductStock stock[50];
	int index;
};

void display_menu(struct Shop *shop);  
void display_custmenu(struct Shop *shop);


struct Customer {
	char* name;
	double budget;
	struct CustQuant shoppingBasket[50];
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

	read = getline(&line, &len, fp); // reading lines of csv file
	char *c_name = strtok(line, ","); // Customer name 
	char *c_bud = strtok(NULL, ","); // Customer budget 
	char *custName = malloc(sizeof(char) * 50); // Assigning memory space to max 50 characters
	double custBudget = atof(c_bud); // Converting budget to float from string 
	strcpy(custName, c_name); // Converting price to float 
	struct  Customer customer = {custName, custBudget}; // Entering customer details 
	printf("Customer name: %s Customer budget: €%.2f\n\n", customer.name, customer.budget);
	while ((read = getline(&line,  &len, fp)) != -1) {
		char *c_prod = strtok(line, ","); // Shopping list item name 
		char *c_quant = strtok(NULL, ","); // Shopping list quantity 
		int quantity = atoi(c_quant); // Convert quantity to integer 
		char *name = malloc(sizeof(char)* 50); // Assigning memory space for shopping list
		strcpy(name, c_prod); // Copy string customer item c
		struct Product product = {name}; // Assigning name variable to Product struct
		struct CustQuant basket = {product, quantity}; // Assigning product and quantity variables to basket
		customer.shoppingBasket[customer.index++] = basket; // Copy to customers shopping basket 
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
		printf("%s wants %i of the product %s\n", customer.name, customer.shoppingBasket[i].quantity, customer.shoppingBasket[i].product.name);
		double cost = customer.shoppingBasket[i].product.price * customer.shoppingBasket[i].quantity;

		//Adjust total cost of new order for each item added.
		customer.totalCost += cost;
		printf("The cost to %s will be €%.2f\n\n", customer.name, cost);	 
		}

		// Check if customer has enough in their budget to afford the purchase
		if (customer.budget < customer.totalCost){
			printf("The total price of the order for %s is €%.2f. %s has insufficient funds to complete the transaction.\n\n", customer.name, customer.totalCost, customer.name);
			return customer;
		}

		// Adjust shop quantities 
		for (int i = 0; i < customer.index; i++){
				shop->stock[i].quantity -= customer.shoppingBasket[i].quantity;
		}

		// Add customer purchase price to shop cash 
		shop->cash +=  customer.totalCost;
		customer.budget -= customer.totalCost;

		printf("The total price for the order for %s will be €%.2f. Transaction complete. %s now has €%.2f remaining in their budget. Shop cash is now €%.2f\n", customer.name, customer.totalCost, customer.name, customer.budget, shop->cash);
	return customer;
}


void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
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
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name, price };
		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
}

void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n", s.stock[i].quantity);
	}
}

void live_Mode(struct Shop *shop)
{

    char *custName;
	double custBudget;
	char additional_items[] = "Y"; 
	char *prod;
	int quantity;

    printf("----------------------------------------------------\n");
    printf("----------------------------------------------------\n");
    printf("       Welcome to our Live Shop  \n");
    printf("----------------------------------------------------\n");
    printf("----------------------------------------------------\n");
    
	
    // End user is asked to enter thier name
	printf("Please enter your name? ");
	fflush(stdin);
	scanf("\n%[^\n]%*c", &custName);
	
	printf("Please enter your budget %s: €", &custName);
	scanf("%lf", &custBudget);

	struct Customer customer = {custName, custBudget};

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
		puts("X- Exit");
		printf("Choice: ");
		fflush(stdin);
		scanf("%i", &choice2);

		switch(choice2){
			case 1:			 
				file_path = "../sufficient_funds.csv";
				custOrder(&(*shop), file_path);
				break;
			case 2:
				file_path = "../insufficient_funds.csv";
				custOrder(&(*shop), file_path);
				break;
			case 3:
				file_path = "../not_enough_stock.csv";
				custOrder(&(*shop), file_path);
				break;
			case 5:
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
		puts("5- Exit");
		fflush(stdin);
		scanf("%i", &choice);

		switch(choice){
			case 1: puts("\nChoice:");
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
	printShop(shop);
    display_menu(&shop);

    return 0;
}