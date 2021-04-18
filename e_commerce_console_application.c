#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// Sinan Dumansız 


// First of all we have struct for the Customer , Basket and Product
typedef struct Customer{
    int id;
    char name[50];
    char surname[50];
    struct Basket *basket;
    struct Customer *next;

} Customer;

typedef struct Basket{
    int id;
    struct Product *product_list;
    int amount;
    struct Basket *next;
} Basket;

typedef struct Product{
    int id;
    int price;
    char name[50];
    char category[50];
    struct Product *next;
} Product;

// Head pointers for the structs and set all of them to NULL
Customer *root = NULL;
Product * product_root = NULL;
Basket * basket_root = NULL;


void read_customer_txt();
void read_basket_txt();
void read_product_txt();
void print_customer();
void  create_customer( int id, char*name ,char*surname);
int find_price_of_product(int product_id);
const char * find_product_name(int product_id);
const char * find_product_catagory(int product_id);
void create_basket(int customer_id,int basket_id,int product_id);
void add_customer();
void remove_customer();
void create_products(int txt_product_id,char*p_name,char*p_category,int price);
void product_print();
int product_list_lenght();
void add_basket();
void print_specific_product();
void print_all_amount();



void read_customer_txt(){
    char name[50], surname[50];
    int id;
    FILE *customerText = fopen("customer.txt", "r");
    while(!feof(customerText)){
        fscanf(customerText,"%d %s %s", &id, name, surname);
        //printf("%d %s %s\n",id,name,surname);
        if(feof(customerText)){
            break;
        }
        create_customer(id, name, surname);
    }
}


void read_basket_txt(){
    int customer_id, basket_id, productID;
    FILE *basketText = fopen("basket.txt", "r");
    while(!feof(basketText)){
        fscanf(basketText, "%d %d %d", &customer_id, &basket_id, &productID);
        if(feof(basketText)){
            break;
        }
        create_basket(customer_id, basket_id, productID);
    }

}

void read_product_txt(){

    char p_name[50], p_category[50];
    int txt_product_id, price;
    FILE *productText = fopen("product.txt", "r");
    while(!feof(productText)){
        fscanf(productText, "%d %s %s %d", &txt_product_id, p_name, p_category, &price);
        if(feof(productText)){
            break;}
        create_products(txt_product_id, p_name, p_category, price);
    }
}


void print_customer(){

    Customer *r = root;
    printf("\n");
    printf("ID  Name  Surname\n");
    printf("--  ----  --------\n");
    while ( r != NULL){
        printf("%d  %s  %s\n",r->id,r->name, r->surname);
        r = r->next;
    }
    printf("\n");
}



void  create_customer( int id, char*name ,char*surname){


    if(root == NULL){ //if its empty
        root = (Customer*)malloc(sizeof (Customer));
        root->id = id;
        strcpy(root->name ,name);
        strcpy(root->surname ,surname);
        root->basket =  NULL;
        root->next =NULL;
        return;
    }

    Customer * iter = root;
    while(iter->next != NULL ){
        iter = iter->next;
    }

    iter->next = (Customer*)malloc(sizeof (Customer));
    iter = iter->next;
    iter->id = id;
    strcpy(iter->name ,name);
    strcpy(iter->surname ,surname);

    iter->basket = NULL;
    iter->next = NULL;
}

int find_price_of_product(int product_id){

    Product * p_iter = product_root;
    int price = 0;

    while (p_iter != NULL){
        if(p_iter->id == product_id){
            price =  p_iter->price;
        }
        p_iter = p_iter->next;
    }
    return price;
}


const char * find_product_name(int product_id){

    Product * p_iter = product_root;
    char *name;

    while (p_iter != NULL){
        if(p_iter->id == product_id){
            name =  p_iter->name;
            //printf("product name is : %s\n",p_iter->name);
        }
        p_iter = p_iter->next;
    }
    return name;
}


const char * find_product_catagory(int product_id){
    Product * p_iter = product_root;
    char* catagory;

    while (p_iter != NULL){
        if(p_iter->id == product_id){
            catagory =  p_iter->category;
        }
        p_iter = p_iter->next;
    }
    return catagory;
}


void create_basket(int customer_id,int basket_id,int product_id){


    Customer * iter = root;

    int price = find_price_of_product(product_id);

    while( iter != NULL && iter->id != customer_id){ //find the specific customer id and stop
        iter = iter->next;
    }


    if(iter->basket == NULL){

        iter->basket = (Basket *)malloc(sizeof (Basket));
        iter->basket->id = basket_id;
        iter->basket->next = NULL;
        iter->basket->amount = price ;

        iter->basket->amount = find_price_of_product(product_id);
        iter->basket->product_list = (Product *) malloc(sizeof(Product));
        iter->basket->product_list->id = product_id;
        //strcpy(iter->basket->product_list->name , find_product_name(product_id));
        //strcpy(iter->basket->product_list->category , find_product_catagory(product_id));
        iter->basket->product_list->next = NULL;

        return ;
    }


    Basket * b_iter = iter->basket;

    while (b_iter->next != NULL && b_iter->id  != basket_id){
        b_iter = b_iter->next;
    }
    int p_amount = b_iter->amount;
    if(b_iter->id == basket_id){

        Product *p_iter = b_iter->product_list;
        while(p_iter->next != NULL){
            p_iter = p_iter->next;
        }

        p_iter->next = (Product *) malloc(sizeof(Product));
        p_iter = p_iter->next;
        p_iter->id = product_id;
        p_iter->price = price;
        //strcpy(p_iter->name ,find_product_name(product_id));
        //strcpy(p_iter->category ,find_product_catagory(product_id));
        p_iter->next = NULL;

        b_iter->amount = price + p_amount;

        return;
    }else{

        Basket * b2_iter = iter->basket;
        while (b2_iter->next != NULL){
            b2_iter = b2_iter->next;
        }
        b2_iter->next = (Basket *) malloc(sizeof(Basket));
        b2_iter = b2_iter->next;
        b2_iter->id = basket_id;
        b2_iter->amount = price;

        b2_iter->next = NULL;

        b2_iter->product_list = (Product *) malloc(sizeof(Product));
        b2_iter->product_list->id = product_id;
        //strcpy(b2_iter->product_list->name ,find_product_name(product_id);
        //strcpy(b2_iter->product_list->category ,find_product_catagory(product_id));
        b2_iter->product_list->price = price;
        b2_iter->product_list->next = NULL;

        return;
    }

}



void add_customer(){

    print_customer();

    char name[50], surname[50];
    printf("Enter name:");
    scanf("%s", name);
    printf("Enter surname:");
    scanf("%s", surname);


    Customer * iter = root;
    while(iter->next != NULL ){
        if(strcmp(name,iter->name)  == 0 && strcmp(surname,iter->surname) == 0  ){
            printf("--> We have already have a customer in same name as %s %s!\n",name,surname);
            return;
        }
        iter = iter->next;
    }

    int previus_id = iter->id;


    if (root == NULL){
        previus_id = 1;
    }


    iter->next = (Customer*)malloc(sizeof (Customer));
    iter = iter->next;
    iter->id = previus_id+1;
    strcpy(iter->name ,name);
    strcpy(iter->surname ,surname);

    iter->basket = NULL;
    iter->next = NULL;
    printf("Customer with %s %s name-surname added to list.\n",name,surname);
    print_customer();

}


void remove_customer(){

    print_customer();

    char name[50], surname[50];
    printf("Enter name:");
    scanf("%s", name);
    printf("Enter surname:");
    scanf("%s", surname);

    Customer* iter = root;
    Customer *temp;

    if(strcmp(root->name ,name)  == 0 && strcmp(root->surname ,surname)  == 0 ){
        temp = root;
        root = root->next;
        free(temp);
        printf("Customer with %s %s name-surname deleted from list.\n",name,surname);
        print_customer();
        return;
    }

    while (iter->next != NULL && !(strcmp(iter->next->surname ,surname)  == 0) && !(strcmp(iter->next->name ,name) == 0) ) {
        iter = iter->next;
    }

    if (iter->next == NULL){
        printf("--> Couldn't find the user in list. Please try again.\n");
        return;
    }

    if(strcmp(iter->next->surname ,surname)  == 0 && strcmp(iter->next->name ,name) == 0){
        temp = iter->next;
        iter->next = iter->next->next;
        free(temp);

        printf("Customer with %s %s name-surname deleted from list.\n",name,surname);
        print_customer();
    }else{
        printf("--> Couldn't find the user in list. Please try again.\n");
        return;
    }
}




void create_products(int txt_product_id,char*p_name,char*p_category,int price){

    if(product_root == NULL){ //if its empty
        product_root = (Product *)malloc(sizeof (Product));
        product_root->id = txt_product_id;
        product_root->price = price;
        strcpy(product_root->name ,p_name);
        strcpy(product_root->category ,p_category);
        product_root->next =NULL;
        return;
    }

    Product * iter = product_root;
    while(iter->next != NULL ){
        iter = iter->next;
    }

    iter->next = (Product*)malloc(sizeof (Product));
    iter = iter->next;
    iter->id = txt_product_id;
    iter->price = price;
    strcpy(iter->name ,p_name);
    strcpy(iter->category ,p_category);
    iter->next = NULL;

}


void product_print(){

    Product *r = product_root;
    printf("\n");
    printf("ID  Name Category Price\n");
    printf("--  ---- ------   ----\n");
    while ( r != NULL){
        printf("%d  %s  %s  %d\n",r->id,r->name,r->category,r->price);
        r = r->next;
    }
    printf("\n");
}


int product_list_lenght(){

    int counter = 0;
    Product * p_iter = product_root;

    while (p_iter != NULL){
        counter = counter + 1;
        p_iter = p_iter->next;
    }
    return counter;
}


void add_basket(){

    Customer* iter = root;

    print_customer();

    int c_id;
    printf("Enter a customer id: ");
    scanf("%d", &c_id);

    while (iter->next != NULL && iter->id != c_id){
        iter = iter->next;
    }

    if(iter->id == c_id){

        printf("User %s %s with id %d selected for adding basket.\n",iter->name,iter->surname,iter->id);

        int id = 0;
        if (iter->basket == NULL){
            id = 1;
        }else {
            Basket* b_iter = iter->basket;
            while (b_iter->next != NULL){
                b_iter = b_iter->next;
            }
            id = b_iter->id+1;
        }

        int input = 0;
        product_print();

        while(input != -1){

            int p_id_input;
            printf("Enter a product id (to complete shopping press '-1'): ");
            scanf("%d", &p_id_input);

            int counter = product_list_lenght();

            if(p_id_input > 0 && p_id_input <= counter){
                    printf("--> Product id with %d added to basket id: %d for %s %s. \n",p_id_input,id,iter->name,iter->surname);
                    create_basket(c_id,id,p_id_input);
            }else if(p_id_input == -1){
                printf("--> Shopping completed for %s %s. Have a nice day!",iter->name,iter->surname);
            }
            else{
                printf("--> Product is not in list!\n");
            }
            input = p_id_input;
        }
        return;
    }else{
        printf("--> User with %d id not exist!\n",c_id);
    }
}



void print_specific_product(){

    product_print();

    int product_id;

    int max_lenght =  product_list_lenght();

    printf("Enter product id to print specific buyer list: ");
    scanf("%d", &product_id);


    if (product_id > max_lenght || product_id < 0){
        printf("Please give valid Product id, Given id number not in list or invalid!\n");
        return;
    }

    Customer *r = root;
    while ( r != NULL){
        if(r->basket == NULL){

        }else{
            Basket * b_iter = r->basket;
            while(b_iter != NULL){
                Product * p_iter = b_iter->product_list;
                while (p_iter != NULL){
                    if(p_iter->id == product_id){
                        printf("--> Customer %s %s bought product id: %d in his basket id: %d\n",r->name,r->surname,product_id,b_iter->id);
                    }
                    p_iter = p_iter->next;
                }
                b_iter = b_iter->next;
            }
        }
        r = r->next;
    }
}



void print_all_amount(){

    printf("\n");

    Customer *r = root;
    while ( r != NULL){

        if(r->basket == NULL){
            printf("%s %s's basket is empty.\n",r->name,r->surname);
        }else{
            int total = 0;
            Basket * b_iter = r->basket;
            while(b_iter != NULL){
                total += b_iter->amount;
                b_iter = b_iter->next;
            }
            printf("%s %s's total amount is %d.\n",r->name,r->surname,total);
        }
        r = r->next;
    }
}


int main()
{
    read_customer_txt();
    read_basket_txt();
    read_product_txt();


    int menu_option;
    printf("\n");
    printf("===----------------------------------=== \n");
    printf("===        E- COMMERCE SYSTEM        ===\n");
    printf("===----------------------------------=== \n");

    do{
        printf("\n");
        printf("1. Add a customer \n");
        printf("2. Add basket \n");
        printf("3. Remove customer\n");
        printf("4. List the customers who bought a specific product\n");
        printf("5. List the total shopping amounts of each customer\n");
        printf("6. Exit\n");
        printf("--> Please enter an option from the main menu 1 to 6:\t ");
        scanf("%d",&menu_option);

        switch(menu_option){

            case 1:
                add_customer();
                break;
            case 2:
                add_basket();
                break;
            case 3:
                remove_customer();
                break;
            case 4:
                print_specific_product();
                break;
            case 5:
                print_all_amount();
                break;
            case 6:
                printf("\n ...by by... \n");
                break;
            default:
                printf("\ninvalid input......\n");
                break;
        }

    }while(menu_option != 6);

    return 0;
}