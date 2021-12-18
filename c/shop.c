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

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer {
	char* name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
};

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}

void printCustomer(struct Customer c)
{
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printf("-------------\n");
	for(int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
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
	char additional_items[] = "Y"; // Create starting condition to open while loop
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
				liveMode(&(*shop));
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
int main(void)
{
	struct Shop shop = createAndStockShop();
	printShop(shop);

    return 0;
}