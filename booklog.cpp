/*
Book Database Program
Salam Bouso
CIS 2541 - Spring 2025

About: This program allows users to manage books in a database. 
Users can add, update, delete, search, and sort the books. Each 
books has a name, author, year, genre, and a 1-10 rating. Each
user's data is written to and read from a personal file. 
*/

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std; 

/*
Class book, representing a musical book with attributes like name, author,
year released, genre, and rating, each having getter and setter methods.
*/

class Book
{

//initialize variables
private:
	string name;
	string author;
	int year;
	string genre;
	int rating;

public:
	//assign default values
	Book()
	{
		name = "Unnamed Book";
		author = "Unknown Author";
		year = -1;
		genre = "Unknown Genre";
		rating = -1;
	}

	//setters and getters
	//get & set name
	string getName()
	{
		return name;
	}

	void setName(string bookName)
	{
			name = bookName;
	}

	//get & set author
	string getAuthor()
	{
		return author;
	}

	void setAuthor(string authorName)
	{
			author = authorName;
	}

	//get & set year
	int getYear()
	{
		return year;
	}

	void setYear(int yearRel)
	{
			year = yearRel;
	}

	//get & set genre
	string getGenre()
	{
		return genre;
	}

	void setGenre(string genreName)
	{
			genre = genreName;
	}

	//get & set rating
	int getRating()
	{
		return rating;
	}

	void setRating(int rate)
	{
		rating = rate;
	}

	//Displays an book's information
	void displayBook()
	{
		cout << left
			<< setw(30) << "Book"
			<< setw(25) << "Author"
			<< setw(10) << "Year"
			<< setw(20) << "Genre"
			<< setw(10) << "Rating" << endl;

		cout << string(90, '-') << endl;

		
		cout << left
			<< setw(30) << name
			<< setw(25) << author
			<< setw(10) << to_string(year)
			<< setw(20) << genre
			<< to_string(rating) << "/10"
			<< endl;
		cout << endl;
		
	}
};

//Displays all of the books in a vector
void displayAllBooks(vector<Book>& books) 
{
	if (books.empty())
	{
		cout << "No books logged." << endl;
		return;
	}

	//header
	cout << left
		<< setw(30) << "Book"
		<< setw(25) << "Author"
		<< setw(10) << "Year"
		<< setw(20) << "Genre"
		<< setw(10) << "Rating" << endl;

	cout << string(90, '-') << endl;

	for (Book& book : books) //for every book in the books vector
	{
		cout << left
			//uses getter functions to return book info
			<< setw(30) << book.getName()                
			<< setw(25) << book.getAuthor()
			<< setw(10) << to_string(book.getYear())
			<< setw(20) << book.getGenre()
			<< to_string(book.getRating()) << "/10"
			<< endl;
	}
}

//Returns true if a string consists of only integers
bool isInt(string str) {
	if (str.empty()) return false;
	for (int i = 0; i < str.length(); i++) //for every character in the string
	{
		if (!isdigit(str[i])) //checks if the character is not a digit
		{
			return false; //if not a digit, returns false
		}
	}
	return true; //if all the characters are digits, returns true
}

//Returns a lowercase version of a string
string tolowerstr(string str)
{
	for (int i = 0; i < str.length(); i++) //for every character in the string
	{
		str[i] = tolower(str[i]); //sets every character to lowercase
	}
	return str;
}

//Allows users to add books
void addBook(vector<Book>& books)
{
		Book newBook;

		string input;

		cout << "\n --- Add New Book --- \n";

		//adds book's name
		cout << "Book Name: ";
		getline(cin, input);
		while (input.length() < 1) 
		{
			cout << "Error! Please enter a valid input." << endl;  //prints error if left blank
			cout << "Book Name: ";
			getline(cin, input);
		}
		newBook.setName(input); //sets book name
		
		//add author
		cout << "Author name: ";
		getline(cin, input);
		while (input.length() < 1)
		{
			cout << "Error! Please enter a valid input." << endl; //prints error if left blank
			cout << "Author Name: ";
			getline(cin, input);
		}
		newBook.setAuthor(input); //sets author
		
		//add year
		bool isValid = false;
		while (!isValid)
		{
			cout << "Year Released: ";
			getline(cin, input);

			if (isInt(input) && input.length() == 4) //only takes 4 digit integer inputs
			{
				newBook.setYear(stoi(input)); //sets year
				isValid = true;
			}
			else
			{
				cout << "Error! Please enter a 4 digit year." << endl; //prints error if input is not an integer or is not 4 digits
			}
		}

		//add genre
		cout << "Genre: ";
		getline(cin, input);
		while (input.length() < 1)
		{
			cout << "Error! Please enter a valid input." << endl; //prints error if left blank
			cout << "Genre: ";
			getline(cin, input);
		}
		newBook.setGenre(input); //sets genre

		//add rating
		int rating;
		bool inRange = false;
		while (!inRange)
		{
			cout << "Rating (Please enter a whole number from 1-10): ";
			getline(cin, input);

			if (isInt(input)) //checks if input is only integers
			{
				rating = stoi(input);
				if (rating >= 1 && rating <= 10) //only takes integers between 1 and 10
				{
					newBook.setRating(rating); //sets rating
					inRange = true;
				}
				else
				{
					cout << "Error! Please enter a whole number between 1 and 10." << endl; //prints error if number not between 1 and 10
				}
			}
			else
			{
				cout << "Error! Please enter a whole number between 1 and 10." << endl; //prints error if input is not an integer
			}
		}

		books.push_back(newBook); //adds new book to vector

		cout << "Book successfully added!" << endl;
	}


//allows users to update an existing book
void updateBook(vector<Book>& books)
{
	string nameinput, authorinput;
	cout << "\n --- Update Book --- \n";
	cout << "Enter the name of the book you wish to update: ";
	getline(cin, nameinput);
	cout << "Enter the author of the book: ";
	getline(cin, authorinput);
	cout << endl;

	bool found = false;

	for (Book& book : books) //for every book in the books vector
	{
		if (tolowerstr(book.getName()) == tolowerstr(nameinput) && tolowerstr(book.getAuthor()) == tolowerstr(authorinput)) //checks if input matches any book names
		{
			found = true; //if book found, found is true
			cout << "\n Current Book Info:\n";
			book.displayBook(); //shows current book info
			cout << "Leave answers blank to keep existing info." << endl; 

			string input2;

			cout << "Book Name: ";
			getline(cin, input2);
			if (!input2.empty())
				book.setName(input2); //sets new name if input is not empty

			cout << "Author name: ";
			getline(cin, input2);
			if (!input2.empty())
				book.setAuthor(input2); //sets new author if input is not empty

			bool isValid = false;
			while (!isValid)
			{
				cout << "Year Released: ";
				getline(cin, input2); 

				if (input2.empty()) //doesn't update if input is empty
				{
					isValid = true;
				}

				else if (isInt(input2) && input2.length() == 4)
				{
					book.setYear(stoi(input2)); //sets new year if input is a 4 digit integer
					isValid = true;
				}
				else
				{
					cout << "Error! Please enter a 4 digit year." << endl; //prints error if input is not empty and not an integer or not 4 digits
				}
			}

			cout << "Genre: ";
			getline(cin, input2);
			if (!input2.empty())
				book.setGenre(input2); //sets new genre if input is not empty

			bool inRange = false;
			int rating;
			while (!inRange)
			{
				cout << "Rating (Please enter a whole number from 1-10): ";
				getline(cin, input2);

				if (input2.empty()) //doesn't update if input is empty
				{
					inRange = true;
				}

				else if (isInt(input2)) //checks if input is an integer
				{
					rating = stoi(input2); //sets rating equal to the input
					if (rating >= 1 && rating <= 10) //checks if rating is between 1 and 10
					{
						book.setRating(rating); //sets new rating
						inRange = true;
					}
					else
					{
						cout << "Error! Please enter a whole number between 1 and 10." << endl; //prints error if not between 1 and 10
					}
				}
				else
				{
					cout << "Error! Please enter a whole number between 1 and 10." << endl; //prints error if input is not an integer
				}
			}

			cout << "Book successfully updated!" << endl;

		}
	}

	if (!found) //if book is not found in vector, prints not found
	{
		cout << "Book not found." << endl; 
	}
}
			
//allows users to delete an book
void deleteBook(vector<Book>& books)
{
	string nameinput, authorinput;
	cout << "\n --- Delete Book --- \n";
	cout << "Enter the name of the book you wish to delete: ";
	getline(cin, nameinput);
	cout << "Enter the author of the book: ";
	getline(cin, authorinput);
	cout << endl;

	bool found = false;
	for (int i = 0; i < books.size(); ++i)
	{
		if (tolowerstr(books[i].getName()) == tolowerstr(nameinput) && tolowerstr(books[i].getAuthor()) == tolowerstr(authorinput))
		{
			found = true;
			char answer;
			books[i].displayBook();
			cout << endl;
			cout << "Are you sure you want to delete this book? <y/n> ";
			cin >> answer;
			cin.ignore(1000, '\n');
			if (tolower(answer) == 'y')
			{
				books.erase(books.begin() + i);
				cout << "Book deleted." << endl;
			}
			else
			{
				cout << "Action cancelled." << endl;
			}
		}
	}
	if (!found)
	{
		cout << "Book not found." << endl;
	}
}

//Functions that allow user to search through books based on each variable
void searchByName(vector<Book>& books)
{
	vector<Book> match;
	bool found = false;
	string input;
	cout << "Enter book name: ";
	getline(cin, input);
	cout << endl;

	for (Book& book : books) //for every book
	{
		if (tolowerstr(book.getName()) == tolowerstr(input)) //if name matches
		{
			match.push_back(book);              //display the book's info
			found = true;
		}
	}
	if (!found)
	{
		cout << "Book not found." << endl;
	}

	displayAllBooks(match);
}

void searchByAuthor(vector<Book>& books)
{
	vector<Book> match;
	bool found = false;
	string input;
	cout << "Enter author name: ";
	getline(cin, input);
	cout << endl;

	cout << "Showing all books by " << input << ":" << endl;
	for (Book& book : books)
	{
		if (tolowerstr(book.getAuthor()) == tolowerstr(input))
		{
			match.push_back(book);
			found = true;
		}
	}
	if (!found)
	{
		cout << "No books by " << input << " found" << endl;
	}

	displayAllBooks(match);

}

void searchByYear(vector<Book>& books)
{
	vector<Book> match;
	bool found = false;
	string input;

	while (!found)
	{
		cout << "Enter year released: ";
		getline(cin, input);
		cout << endl;

		if (isInt(input) && input.length() == 4)
		{
			cout << "Showing all books released in " << input << ":" << endl;
			for (Book& book : books)
			{
				if (book.getYear() == stoi(input))
				{
					match.push_back(book);
					found = true;
				}
			}
			if (!found)
			{
				cout << "No books released in " << input << " found." << endl;
			}
			found = true;
		}
		else
		{
			cout << "Error! Please enter a 4 digit year." << endl;
		}
		
	}

	displayAllBooks(match);
}

void searchByGenre(vector<Book>& books)
{
	vector<Book> match;
	bool found = false;
	string input;
	cout << "Enter genre: ";
	getline(cin, input);
	cout << endl;

	cout << "Showing all " << input << " books:" << endl;
	for (Book& book : books)
	{
		if (tolowerstr(book.getGenre()) == tolowerstr(input))
		{
			match.push_back(book);
			found = true;
		}
	}
	if (!found)
	{
		cout << "No " << input << " books found." << endl;
	}
	displayAllBooks(match);
}

void searchByRating(vector<Book>& books)
{
	vector<Book> match;
	bool found = false;
	string input;

	while (!found)
	{
		cout << "Enter rating: ";
		getline(cin, input);
		cout << endl;

		if (isInt(input) && stoi(input) >= 1 && stoi(input) <= 10)
		{
			cout << "Showing all books you rated " << input << "/10:" << endl;
			for (Book& book : books)
			{
				if (book.getRating() == stoi(input))
				{
					match.push_back(book);
					found = true;
				}
			}
			if (!found)
			{
				cout << "No books rated " << input << "/10 found." << endl;
			}
			found = true;
		}
		else
		{
			cout << "Error! Please enter a whole number between 1 and 10" << endl;
		}

	}
	displayAllBooks(match);
}

//Allows users to save their books onto a personal file, copies all the book's info onto the file
void saveBooks(vector<Book>& books, string& username)
{
	ofstream outFile(username + "_books.txt");
	for (Book& book : books)
	{
		outFile << book.getName() << endl;
		outFile << book.getAuthor() << endl;
		outFile << book.getYear() << endl;
		outFile << book.getGenre() << endl;
		outFile << book.getRating() << endl;
	}
	outFile.close();
}

//Reads info from the user's existing file into an book vector
void loadBooks(vector<Book>& books, string& username)
{
	ifstream inFile(username + "_books.txt"); //opens the user's file
	if (!inFile) return;

	Book book;
	string name;
	string author;
	int year;
	string genre;
	int rating;

	while (getline(inFile, name)) //runs for each book stored in the file
	{
		//reads each line and inputs it into a variable
		getline(inFile, author);
		inFile >> year;
		inFile.ignore(); 
		getline(inFile, genre);
		inFile >> rating;
		inFile.ignore(); 

		//sets each variable as an book's attribute
		book.setName(name);
		book.setAuthor(author);
		book.setYear(year);
		book.setGenre(genre);
		book.setRating(rating);
		books.push_back(book); //adds the book to the vector
	}
	inFile.close();
}

//Functions that allow users to sort through all the books and display them according to each option
vector<Book> sortBooksByRating(const vector<Book>& books)
{
	vector<Book> sortedBooks = books; //copying all books onto a new vector
	int i = 1;
	int j = i - 1;

	for (int i = 1; i < sortedBooks.size(); ++i) //insertion sort
	{
		Book key = sortedBooks[i];
		int j = i - 1;
		while (j >= 0 && sortedBooks[j].getRating() > key.getRating())
		{
			sortedBooks[j + 1] = sortedBooks[j];
			j = j - 1;
		}
		sortedBooks[j + 1] = key;
	}
	return sortedBooks; //returns the sorted vector
}

vector<Book> sortBooksByYear(const vector<Book>& books)
{
	vector<Book> sortedBooks = books;
	int i = 1;
	int j = i - 1;

	for (int i = 1; i < sortedBooks.size(); ++i)
	{
		Book key = sortedBooks[i];
		int j = i - 1;
		while (j >= 0 && sortedBooks[j].getYear() > key.getYear())
		{
			sortedBooks[j + 1] = sortedBooks[j];
			j = j - 1;
		}
		sortedBooks[j + 1] = key;
	}
	return sortedBooks;
}

vector<Book> sortBooksByName(const vector<Book>& books)
{
	vector<Book> sortedBooks = books; 
	int i = 1;
	int j = i - 1;

	for (int i = 1; i < sortedBooks.size(); ++i) 
	{
		Book key = sortedBooks[i];
		int j = i - 1;
		while (j >= 0 && sortedBooks[j].getName() > key.getName()) 
		{
			sortedBooks[j + 1] = sortedBooks[j];
			j = j - 1;
		}
		sortedBooks[j + 1] = key;
	}
	return sortedBooks;
}

vector<Book> sortBooksByAuthor(const vector<Book>& books)
{
	vector<Book> sortedBooks = books;
	int i = 1;
	int j = i - 1;

	for (int i = 1; i < sortedBooks.size(); ++i)
	{
		Book key = sortedBooks[i];
		int j = i - 1;
		while (j >= 0 && sortedBooks[j].getAuthor() > key.getAuthor())
		{
			sortedBooks[j + 1] = sortedBooks[j];
			j = j - 1;
		}
		sortedBooks[j + 1] = key;
	}
	return sortedBooks;
}

vector<Book> sortBooksByGenre(const vector<Book>& books)
{
	vector<Book> sortedBooks = books;
	int i = 1;
	int j = i - 1;

	for (int i = 1; i < sortedBooks.size(); ++i)
	{
		Book key = sortedBooks[i];
		int j = i - 1;
		while (j >= 0 && sortedBooks[j].getGenre() > key.getGenre())
		{
			sortedBooks[j + 1] = sortedBooks[j];
			j = j - 1;
		}
		sortedBooks[j + 1] = key;
	}
	return sortedBooks;
}

void clearBooks(vector<Book>& books)
{
	char answer;
	cout << "Are you sure you want to clear ALL books logged? <y/n> ";
	cin >> answer;
	cin.ignore(1000, '\n');
	if (tolower(answer) == 'y')
	{
		books.clear();
		cout << "All books deleted." << endl;
	}
	else
	{
		cout << "Action cancelled." << endl;
	}


}

int main()
{
	vector<Book> books;
	vector<Book> sortedBooks;  //initialize variables
	string username;
	int choice;
	bool run = true;

	cout << "Please enter your username: ";
	getline(cin, username);
	loadBooks(books, username);  //prompts user for their username and loads their file

	//menu
	do
	{
		cout << "\n --- Welcome to the Book Log! --- \n";
		cout << "1. Add a New Book" << endl;
		cout << "2. Update an Existing Book" << endl;
		cout << "3. Search For a Book" << endl;
		cout << "4. Delete a Book" << endl;
		cout << "5. Sort Books" << endl;
		cout << "6. View All Books" << endl;
		cout << "7. Save Books" << endl;
		cout << "8. Exit and Save" << endl;
		cout << "9. Exit Without Saving" << endl;
		cout << "0. Clear ALL Books" << endl;
		cout << "Choice: ";
		cin >> choice;
		while (cin.fail())  //if the user's input is not an int, returns error
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input" << endl;
			cout << "Choice: ";
			cin >> choice;
		}

		cin.ignore(1000, '\n');

		switch (choice)
		{
		case 1:
			addBook(books);
			break;
		case 2:
			updateBook(books);
			break;
		case 3:
			int choice2;
			cout << "1. Search by Book Name" << endl;
			cout << "2. Search by Author" << endl;
			cout << "3. Search by Year Released" << endl;
			cout << "4. Search by Genre" << endl;
			cout << "5. Search by Rating" << endl;
			cout << "Choice: ";
			cin >> choice2;
			cin.ignore(1000, '\n');

			switch (choice2)
			{
			case 1:
				searchByName(books);
				break;
			case 2:
				searchByAuthor(books);
				break;
			case 3:
				searchByYear(books);
				break;
			case 4:
				searchByGenre(books);
				break;
			case 5:
				searchByRating(books);
				break;
			default: 
				cout << "Invalid Input" << endl;
			}

			break;

		case 4:
			deleteBook(books);
			break;

		case 5:
			int choice3;
			cout << "1. Sort Books Alphabetically by Name" << endl;
			cout << "2. Sort Books Alphabetically by Author" << endl;
			cout << "3. Sort Books by Year Released" << endl;
			cout << "4. Sort Books Alphabetically by Genre" << endl;
			cout << "5. Sort Books by Rating" << endl;
			cout << "Choice: ";
			cin >> choice3;
			cin.ignore(1000, '\n');
			
			switch(choice3)
			{
			case 1:
				sortedBooks = sortBooksByName(books);
				displayAllBooks(sortedBooks);
				break;
			case 2:
				sortedBooks = sortBooksByAuthor(books);
				displayAllBooks(sortedBooks);
				break;
			
			case 3:
				sortedBooks = sortBooksByYear(books);
				displayAllBooks(sortedBooks);
				break;
			case 4:
				sortedBooks = sortBooksByGenre(books);
				displayAllBooks(sortedBooks);
				break;
			case 5:
				sortedBooks = sortBooksByRating(books);
				displayAllBooks(sortedBooks);				
				break;
			default: 
				cout << "Invalid Input" << endl;
			}
			
			break;
		case 6:
			displayAllBooks(books);
			break;

		case 7:
			saveBooks(books, username);
			cout << "Books succesfully saved." << endl;
			break;

		case 8:
			saveBooks(books, username);
			cout << "Books succesfully saved. Goodbye!" << endl;
			run = false;
			break;

		case 9:
			char answer;
			cout << "Are you sure you want to leave without saving? <y/n> ";
			cin >> answer;
			cin.ignore(1000, '\n');
			if (tolower(answer) == 'y')
			{
				cout << "Goodbye!" << endl;
				run = false;
			}
			else
			{
				cout << "Action cancelled" << endl;
			}
			break;

		case 0:
			clearBooks(books);
			break;
		default:
			cout << "Invalid Input" << endl;
		}

	} while (run);
}