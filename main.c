#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/*

- Book title (string)
- Author name (string)
- Publication year (integer)
- Number of copies (integer)
- Price (floating-point number)
- Status (string)

*/

#define BOOK_THRESHOLD 100

typedef struct{
	char title[100];
	char name[100];
	int year;
	int copies;
	float price;
	char status[50];
	char borrowedCopies;
	char boughtCopies;
}book;

enum Choices{
	Add = 1,
	Display,
	Borrow,
	Return,
	Delete,
	Sell,
	Buy,
	Exit,
};

char currentNumOfBooks = 0;
char currentNumOfBoughtBooks = 0;
char libFull = 0;
book allBooks[BOOK_THRESHOLD];

void Addbook();
void DisplayBooks();
void BorrowBook();
void SellBook();
void BuyBook();
char CheckDuplicateBook(char title[BOOK_THRESHOLD]);
void DeleteBook();
char AdjustIndex();
void ReturnBook();

void main(){
	char choice;
	do{
		system("cls");
		printf("\t-------Main Menu-------\n");
		printf("\t1.Add book\n\t2.Display books\n\t3.Borrow book\n\t4.Return book\n\t5.Delete book\n\t6.Sell book\n\t7.Buy book\n\t8.Exit\n");
		printf("--------------------------------------------------------------\n");
		printf("Please enter your choice: ");
		scanf("%d", &choice);
		switch(choice){
			case Add:
				Addbook();
				break;	
			case Display:
				DisplayBooks();
				break;
			case Borrow:
				BorrowBook();
				break;
			case Return:
				ReturnBook();
				break;
			case Delete:
				DeleteBook();
				break;
			case Sell:
				SellBook();
				break;
			case Buy:
				BuyBook();
				break;
			case Exit:
				return;
			default:
				printf("Wrong choice please try again!\n");
				printf("Press any key to continue...");
				getch();
		}
	}while(1);
}

void Addbook(){
	system("cls");
	char index = 0;
	char title[BOOK_THRESHOLD];
	char tempSize = currentNumOfBooks;
	char copies = 0;
	if(currentNumOfBooks < BOOK_THRESHOLD){
		printf("Please enter the book's title: ");
		scanf(" %[^\n]", &title);
		index = CheckDuplicateBook(title);
		if(index == -1){
			index = AdjustIndex();
			printf("This is a new book\n");
			strcpy(allBooks[index].title, title);
			printf("Please enter the author's name: ");
			scanf(" %[^\n]", &allBooks[index].name);
			printf("Please enter the book's publishing year: ");
			scanf("%d", &allBooks[index].year);
			printf("Please enter the number of book copies: ");
			scanf("%d", &copies);
			printf("Please enter the book's price: ");
			scanf("%f", &allBooks[index].price);
			allBooks[index].borrowedCopies = 0;
			allBooks[index].boughtCopies = 0;
			tempSize += copies;
		}
		else{
			printf("Book already found\n");
			printf("Please edit the number of book copies: ");
			scanf("%d", &copies);
			tempSize -= allBooks[index].copies;
			tempSize += copies;
		}
		if(copies > 0){
				strcpy(allBooks[index].status , "Available"); 
		}
		else if(copies == 0){
			strcpy(allBooks[index].status , "Sold Out"); 
		}
		
		else{
			printf("Error: Invalid number of copies!\n");
			printf("Press any key to continue...");
			getch();
			return;
		}
		if(tempSize <= BOOK_THRESHOLD){
			allBooks[index].copies = copies;
			currentNumOfBooks = tempSize;
			printf("Done successfully!\n");
			printf("Press any key to continue...");
			getch();
		}
		else{
			printf("Error: total number of copies will exceed the threshold!\n");
			printf("Press any key to continue...");
			getch();
		}
	}
	else{
		printf("Maximum number of books reached\n");
		printf("Press any key to continue...");
		getch();
	}
}

void DisplayBooks(){
	system("cls");
	char totalBookCount = 0;
	char boughtBookCount = 0;
	char index = 0;
	char tempBookCount = 1;
	if(currentNumOfBooks > 0 || currentNumOfBoughtBooks > 0){
		printf("--------------------------------------------------------------\n");
		while((totalBookCount < currentNumOfBooks || boughtBookCount < currentNumOfBoughtBooks) && index < BOOK_THRESHOLD){
			if(allBooks[index].title[0] != '\0'){
				printf("\tBook %d is called \"%s\" was published by \"%s\"\n", tempBookCount, allBooks[index].title, allBooks[index].name);
				printf("\tThe book was published in %d and remaining copies are %d for %0.2f$ each\n", allBooks[index].year, allBooks[index].copies, allBooks[index].price);
				printf("\tThe book is currently %s with %d copies borrowed\n", allBooks[index].status, allBooks[index].borrowedCopies);
				printf("--------------------------------------------------------------\n");
				totalBookCount+=(allBooks[index].copies + allBooks[index].borrowedCopies);
				tempBookCount++;
				boughtBookCount += allBooks[index].boughtCopies;
			}
			index++;		
		}
	}
	else{
		printf("No books found\n");
	}
	printf("Press any key to continue...");
	getch();
}

void BorrowBook(){
	char title[BOOK_THRESHOLD];
	char index = 0;
	if(currentNumOfBooks > 0){
		printf("Please enter the book name you want to borrow: ");
		scanf(" %[^\n]", &title);
		index = CheckDuplicateBook(title);
		if(index != -1){
			if(allBooks[index].status[0] == 'A'){
				allBooks[index].copies--;
				if(allBooks[index].copies == 0){
					strcpy(allBooks[index].status , "Sold Out"); 
				}
				allBooks[index].borrowedCopies++;
				printf("Book borrowed successfully!\n");
				printf("Press any key to continue...");
				getch();;
			}
			else{
				printf("Book is sold out!\n");
				printf("Press any key to continue...");
				getch();;
			}
		}
		else{
			printf("Book was not found!\n");
			printf("Press any key to continue...");
			getch();
		}
	}
	else{
		printf("No books are available\n");
		printf("Press any key to continue...");
		getch();
	}
	
}

void SellBook(){
	char title[BOOK_THRESHOLD];
	char index = 0;
	char copies = 0;
	if(currentNumOfBooks < BOOK_THRESHOLD){
		printf("Please enter the book name you want to sell: ");
		scanf(" %[^\n]", &title);
		index = CheckDuplicateBook(title);
		if(index != -1){
			printf("Book already found\n");
			allBooks[index].copies++;
			strcpy(allBooks[index].status , "Available");
		}
		else{
			index = AdjustIndex();
			printf("This is a new book\n");
			strcpy(allBooks[index].title, title);
			printf("Please enter the author's name: ");
			scanf(" %[^\n]", &allBooks[index].name);
			printf("Please enter the book's publishing year: ");
			scanf("%d", &allBooks[index].year);
			printf("Please enter the book's price: ");
			scanf("%f", &allBooks[index].price);
			strcpy(allBooks[index].status , "Available"); 
			allBooks[index].copies = 1;
			allBooks[index].borrowedCopies = 0;
			allBooks[index].boughtCopies = 0;
		}
		currentNumOfBooks++;
		printf("Sold successfully!\n");
		printf("Press any key to continue...");
		getch();
	}
	else{
		printf("Maximum number of books reached\n");
		printf("Press any key to continue...");
		getch();
	}
}

char CheckDuplicateBook(char title[BOOK_THRESHOLD]){
	char index = 0;
	char totalBookCount = 0;
	char boughtBookCount = 0;
	while((totalBookCount < currentNumOfBooks || boughtBookCount < currentNumOfBoughtBooks)&& index < BOOK_THRESHOLD){
		if(allBooks[index].title[0] != '\0'){
			if(strcmp(title, allBooks[index].title) == 0){
				return index;
			}
			totalBookCount += (allBooks[index].copies + allBooks[index].borrowedCopies);
			boughtBookCount += allBooks[index].boughtCopies;
		}
		index++;
	}
	return -1;
}

void DeleteBook(){
	char title[BOOK_THRESHOLD];
	char index = 0;
	char totalBookCount = 0;
	char boughtBookCount = 0;
	if(currentNumOfBooks > 0 || currentNumOfBoughtBooks > 0){
		printf("Please Enter the book name you want to delete: ");
		scanf(" %[^\n]", &title);
		while((totalBookCount < currentNumOfBooks || boughtBookCount < currentNumOfBoughtBooks) && index < BOOK_THRESHOLD){	
			if(allBooks[index].title[0] != '\0'){
				if(strcmp(title, allBooks[index].title) == 0){
					allBooks[index].title[0] = '\0';
					currentNumOfBooks -= (allBooks[index].copies + allBooks[index].borrowedCopies);
					currentNumOfBoughtBooks -= allBooks[index].boughtCopies;
					libFull = 0;
					printf("Book deleted successfully!\n");
					printf("Press any key to continue...");
					getch();
					return;
				}
				totalBookCount+=(allBooks[index].copies + allBooks[index].borrowedCopies);
				boughtBookCount += allBooks[index].boughtCopies;
			}
			index++;
		}	
		printf("Book was not found!\n");
		printf("Press any key to continue...");
		getch();;
	}
	else{
		printf("No books are available\n");
		printf("Press any key to continue...");
		getch();
	}
}

char AdjustIndex(){
	char count = 0;
	char totalBookCount = 0;
	char boughtBookCount = 0;
	if(libFull == 0){
		while(allBooks[count].title[0] != '\0' && (totalBookCount < currentNumOfBooks || boughtBookCount < currentNumOfBooks) && count < BOOK_THRESHOLD){
			count++;
			totalBookCount += (allBooks[count].copies + allBooks[count].borrowedCopies);
			boughtBookCount += allBooks[count].boughtCopies;
		}
	}
	if(count == BOOK_THRESHOLD || libFull == 1){
		libFull == 1;
		//We have reached the maximum number of elements in the array, so we have to replace the books that are sold out and were not borrowed
		count = 0;
		while(allBooks[count].copies != 0 || allBooks[count].borrowedCopies != 0){
			count++;
		}
	}
	return count;
}

void ReturnBook(){
	char title[BOOK_THRESHOLD];
	char index = 0;
	printf("Please Enter the book name you want to return: ");
	scanf(" %[^\n]", &title);
	index = CheckDuplicateBook(title);
	if(index != -1){
		if(allBooks[index].borrowedCopies > 0){
			allBooks[index].copies++;
			allBooks[index].borrowedCopies--;
			strcpy(allBooks[index].status , "Available");
			printf("Book returned successfully!\n");
			printf("Press any key to continue...");
			getch();
		}
		else{
			printf("Book was not borrowed before!\n");
			printf("Press any key to continue...");
			getch();
		}
	}
	else{
		printf("Book was not found!\n");
		printf("Press any key to continue...");
		getch();
	}
}

void BuyBook(){
	char title[BOOK_THRESHOLD];
	char index = 0;
	if(currentNumOfBooks > 0){
		printf("Please enter the book name you want to buy: ");
		scanf(" %[^\n]", &title);
		index = CheckDuplicateBook(title);
		if(index != -1){
			if(allBooks[index].status[0] == 'A'){
				allBooks[index].copies--;
				if(allBooks[index].copies == 0){
					strcpy(allBooks[index].status , "Sold Out"); 
				}
				allBooks[index].boughtCopies++;
				currentNumOfBoughtBooks++;
				currentNumOfBooks--;
				printf("Book purchased successfully!\n");
				printf("Press any key to continue...");
				getch();;
			}
			else{
				printf("Book is sold out!\n");
				printf("Press any key to continue...");
				getch();;
			}
		}
		else{
			printf("Book was not found!\n");
			printf("Press any key to continue...");
			getch();
		}
	}
	else{
		printf("No books are available\n");
		printf("Press any key to continue...");
		getch();
	}
}