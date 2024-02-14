#include <iostream>

using std::cout;
using std::cin;

//in the header file we declare all the classes and methods and also functions

void registerLogin();
void callExceptionMethods();
void updateTablesInDatabase(std::vector<std::vector<std::string>> &updatedTable, int tablePosition, std::string database, int rows);
void extractTableData(std::string tableRowContent, std::vector<std::string> &eachTableRow);
void positionDataToMiddle(std::string& currentTableCell, std::string newData);


//The purpose of this class is to validate user input before sending it to a data base
class Exceptions {
public:
   
    //The only class method, used to make the user validate the input
    void checkIfInputValid(void* input, char dataType);
    
};
//This class will represent a blueprint for creating and deleting databases
class DataBase {
     
//using the access modifier 'private' to restrict the access to the methids/members of this class
private: //(in other words, encapsulation)
    
    //function to create databases which will be represented by notepad files
    void createDeleteDatabase();
        
    //declaring the child class as a friend so that it can access the methods of the parent class
    friend class handleDatabases;
};

/*creating an abstract class which will contain only one pure virtual function and will serve
 as a blueprint for the class handleDatabases*/
class forStringFormatting {
public:

    //creating a pure virtual function that will need to be implemented by another class
    virtual std::string modifyUserInput(std::string &userInput, std::string currentPtrString, bool firstUserInput) = 0;
};

//creating a class that inherits from the abstract class 'forStringFormatting'
class implementAbstractClass : public forStringFormatting {
public:

    //providing implementation for the method of the abstract class
    //this function modifies the user input(a string) before inserting it to a table
    std::string modifyUserInput(std::string& userInput, std::string currentPtrString, bool firstUserInput) {

        //this is the complex procedure for formatting the user input before storing it to a table:
        
        cin >> userInput;
        //if the user input is too large to be stored inside the table
        while (userInput.length() > currentPtrString.length()-2) {

            cout << "Error, input is too large for this column, you can only enter a maximum number of: " << currentPtrString.length() - 2 << " characters!";
            cout << "Try again: \n";
            cin.clear();

            //clearing the buffer before each user input
            std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
       
            cin >> userInput;
            system("cls");
        }


        //if we are on the first column inside the table we need to add '|' to the left of the user input

          while (userInput.length() < currentPtrString.length() - 2)
          {
              //adding two spaces to the string, one in front of it and one at the end
              userInput.insert(userInput.begin(), ' ');
              userInput += ' ';
          }

          if (userInput.length() == currentPtrString.length() - 2) {
              userInput.insert(userInput.begin(), '|');
              userInput += '|';
          }
          else {
              userInput.pop_back();

              //adding the last characters to the input before storing it inside the table
              userInput.insert(userInput.begin(), '|');
              userInput += '|';
          }
                
          if (firstUserInput == false)
              userInput[0] = ' ';
        
        
          return "";
    }
};


//using inheritance to make this class a child of class Database and also inherit from the abstract class
class handleDatabases: public DataBase{
public:

    //declaring a method of the child class that is used to access a method of the base class
    void accessBaseClassMethods();

    //declaring another method used for creating, reading, updating and deleting tables
    void CRUD();

    
};

/*this class can be used to rate the functionality of a database
the rating is determined by the number of issues found inside the database*/
class rateDatabase {

public:

    //this function will look for potential issues in the database and inform the user if issues are found
    void findPotentialIssues();

    //this is the method that will give a rating to a database based on the number of issues found
    void giveRating(bool duplicateInTables, bool emptyDatabase);

};






