#include <iostream>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdio> //header to use remove function for files
#include "ClassesHeader.h"
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::invalid_argument;

//creating a global vector which will keep track of all the databases that exist
std::vector<std::string> currentDatabases;

/*Purpose of this method: If the user enters a non digit character(letters, symbols..) to a
double, float, integer, long, long long or short, the program will throw a custom exception*/
//(finished function)
void Exceptions::checkIfInputValid(void* input, char dataType) {
    bool validInput = false;
    

    // Keep taking user input until it's valid
    while (!validInput) {
    
        try {
            // Always reset the flag at the start of the loop
            validInput = true;

            switch (dataType) {
            case 'i':
                // Handle int input
                if (!(cin >> *reinterpret_cast<int*>(input))) //converting the void pointer
                    throw invalid_argument("You cannot enter a non digit char to an integer\n");
                break;

            case 's':
                // Handle short input
                if (!(cin >> *reinterpret_cast<short*>(input)))
                    throw invalid_argument("You cannot enter a non digit char to short\n");
                break;

            case 'l':
                // Handle long input
                if (!(cin >> *reinterpret_cast<long*>(input)))
                    throw invalid_argument("You cannot enter a non digit char to long\n");
                break;

            case 'f':
                // Handle float input
                if (!(cin >> *reinterpret_cast<float*>(input)))
                    throw invalid_argument("You cannot enter a non digit char to float\n");
                break;

            case 'd':
                // Handle double input
                if (!(cin >> *reinterpret_cast<double*>(input)))
                    throw invalid_argument("You cannot enter a non digit char to double\n");
                break;

            case 'L':
                // Handle long long input
                if (!(cin >> *reinterpret_cast<long long*>(input)))
                    throw invalid_argument("You cannot enter a non digit char to long long\n");
                break;

            default:
                // Handle unknown data type
                cout << "Unknown data type!" << endl;
                break;
            }
        }//If an exception was thrown, catch it
        catch (const std::invalid_argument& e) {
           

            cout << "Error: \n";
            std::cerr << e.what();  // Printing the exception to the console

            validInput = false;

            // Exiting the error state so that the program can continue its execution
            cin.clear();

            // Clearing the characters left in the buffer until we reach the end of the row
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        }
    }
}

//this function calls different different methods of class Exception to check the user input
//(finished function)
void callExceptionMethods(void* userInput, char dataType) {

    //checking if the user entered entered non digit characters by calling the function down below
    Exceptions E;
    E.checkIfInputValid(userInput, dataType);


}

//(finished function)
void registerLogin() {
    std::string name = "", password = "", anyUserInput = "";
    bool hasDigits = false, hasUpperChar = false, fileFound = true;
    int user_input = 0;

    cout << "Welcome to the custom database management system \n\n";
    cout << "Before you begin, you need to know the following: \n\n";
    cout << "1.You can create or delete databases\n\n";
    cout << "2.You can create, read, update or delete the tables inside each database\n\n";
    cout << "3.Each table has 5 rows and 5 columns \n\n";
    cout << "In the first row you need to specify what type of data you want to store\n\n";
    cout << "And then, you can add that data on the next rows\n\n";
    cout << "That's all, now you can start using the program:\n\n";
    cout << "Press 1 if you don't have an account 2.For log in\n";

  
    callExceptionMethods(&user_input, 'i');
    system("cls");

    do {
        
        //if the user input is not 1 or 2, execute this if statement
        if (user_input != 1 && user_input != 2) {
            system("cls");
            cout << "Error, you can only enter 1.For registration 2.For log in!\n";
            
            //prompt the user for input again
            cout << "Please try again: 1.Registration 2.Log in\n";
            callExceptionMethods(&user_input, 'i');
        }

        if (user_input == 1) {
            cout << "Welcome to the registration section\n";

            cout << "Enter your name : \n";
            cin >> name; 


            cout << "Enter your password : \n";
            cin >> password;

            do {
                hasDigits = false;
                hasUpperChar = false;

                //checking for upper characters
                for (int i = 0; i < password.length(); i++) {
                    int val = password[i];

                    //if there is an upper character inside the string
                    if (password[i] >= 'A' && password[i] <= 'Z') {
                        hasUpperChar = true;
                    }

                    //if there is a digit in the string execute this condition
                    if (val >= 48 && val <= 57) {
                        hasDigits = true;
                    }

                }

                //if the password does not contain upper chars, tell the user to use them
                if (hasUpperChar == false) {
                    cout << "Error, password must contain upper characters also\n\n";
                    cout << "Try again \n";
                    cin >> password;
                    system("cls");
                }

                //if the character is not digit, execute this loop again
                if (hasDigits == false) {
                    cout << "\n\nError, password must contain at least one digit\n\n";
                    cout << "Try again\n";
                    cin >> password;
                    system("cls");
                }

                //as long as the password is too weak, keep executing this loop
            } while (hasUpperChar == false || hasDigits == false);


            system("cls");
            cout << "The account has been created and saved!\n";


            // Creating the document and opening it to append text
            std::fstream myFile;
            myFile.open("StoreAccounts.txt", std::ios::app);

            if (myFile.is_open()) {
                // Storing the account information in the notepad
                myFile << name << std::endl;
                myFile << password << std::endl;

                std::cout << "Account information appended successfully." << std::endl;
            }
            else {
                std::cerr << "Error opening file for appending." << std::endl;

            }

            //closing the file
            myFile.close();

            cout << "Account created successfully!\n\n";
            cout << "Press any key to continue: \n\n";
            callExceptionMethods(&user_input, 'i');
            system("cls;");
        }
        else if (user_input == 2) {
            system("cls");

            cout << "Welcome to the login section, press any number to start: \n";
            callExceptionMethods(&user_input, 'i');

            bool userFound = false, passwordFound = false;

            do {
                userFound = false;
                passwordFound = false;

                std::cout << "Enter username: \n";
                cin >> name;

                std::cout << "Enter password: \n";
                cin >> password;

                std::fstream openFile;
                openFile.open("StoreAccounts.txt", std::ios::in);

                if (openFile.is_open()) {
                    std::string documentLine;

                    while (std::getline(openFile, documentLine)) {
                        //searching for the username inside the notepad
                        if (name == documentLine) {
                            userFound = true;
                        }//and searching for the password
                        else if (password == documentLine) {
                            passwordFound = true;
                        }

                        // If both user and password are found, break out of the loop
                        if (userFound && passwordFound) {
                            break;
                        }
                    }

                    openFile.close();
                }
                else {
                    std::cerr << "Error, file could not be opened\n\n";
                    cout << "Press any key to continue \n\n";
                    cin >> anyUserInput;
                    system("cls");

                    fileFound = false;
                }

                // If the user or password was not found, prompt the user for input again
                if ((!userFound || !passwordFound) && fileFound == true) {
                    system("cls");
                    std::cout << "Error, wrong username or password, try again\n";
                }

            } while (!userFound || !passwordFound);

            std::cout << "Account accepted!\n\n";
            cout << "Press any key to continue: \n";
            cin >> anyUserInput;
        }
       


    //as long as the user input is invalid(not 1 or 2), keep executing this loop
    } while (user_input != 1 && user_input != 2);

    
}


//(finished function)
//the purpose of this function if to create or delete a database(a notepad file)
void DataBase::createDeleteDatabase() {
    
    
    system("cls");
    int createDatabase = 0, user_input = 0;


    //creating a file called allDatabases.txt
    std::fstream findDatabases;
    findDatabases.open("allDatabases.txt", std::ios::in);

    //execute this condition if the file is open
    if (findDatabases.is_open()) {

        std::string storeEveryDatabase = "";

        //checking for any existing databases and storing them to the vector called: currentDatabases
        while (getline(findDatabases, storeEveryDatabase)) {
            currentDatabases.push_back(storeEveryDatabase);
        }
    }
    else {
        cout << "Error, cannot open the file!\n";
    }
    findDatabases.close();

    //if the vector's size is greater then 1 it means that there are available databases, if so execute this condition
    if (currentDatabases.size() >= 1) {
        cout << "What would you like to do with a database: 1.Create 2.Delete or 3.Skip\n";
        callExceptionMethods(&user_input, 'i');
    }
    else if (currentDatabases.size() == 0) {
       
        cout << "For now there are no available databases, would you like to create one? \n";
        cout << "1.Yes 2.No(if you enter 2, the program will stop executing!)\n";
        callExceptionMethods(&createDatabase, 'i');
        
        //as long as the user input is not valid, keep running this loop
        while (createDatabase != 1 && createDatabase != 2) {
            system("cls");
            cout << "Error, you can only enter 1.For yes 2.For no\n";
            callExceptionMethods(&createDatabase, 'i');
        }
        //if the user does not want to create a new database, stop the program from executing
        if (createDatabase == 2) {
            system("cls");
            cout << "Goodbye \n";
            exit(0);
        }

    }
    
    
    //However if there are no databases available but the user wants to create one, execute this statement
    if(currentDatabases.size() == 0 && createDatabase == 1){
        user_input = 1;
    }
    else if (currentDatabases.size() == 0 && createDatabase == 2) {
        //when there are no databases and the user does not want to create a new one, stop the program
        cout << "Goodbye!\n";
        exit(0);
    }

    //clearing the vector before proceeding
    currentDatabases.clear();

        //if user input is 1, create a database
        if (user_input == 1) {
            system("cls");
            cout << "Enter a name for your database: \n";
            std::string databaseName = "";

            //giving a name to the databases
            cin >> databaseName;

            //here we create the new database which will be represented by a notepad file
            system("cls");
            std::fstream newDatabase; //creating a new file(notepad)
            newDatabase.open(databaseName + ".txt", std::ios::app);

            if (newDatabase.is_open()) {
                cout << "\nCongratulations, database " << databaseName << " was created!";
                newDatabase.close(); //closing the database after creation


                //when we create a database, we will save it to another notepad file
                std::fstream saveDatabases;
                saveDatabases.open("allDatabases.txt", std::ios::app);

                //if this file opened, execute this condition
                if (saveDatabases.is_open()) {

                    saveDatabases << databaseName + ".txt" << '\n';

                }
                else {
                    cout << "Error, database could not be added to the file\n";

                }


                saveDatabases.close(); //closing the file where each database is stored


                //storing the available databases to this vector
                saveDatabases.open("allDatabases.txt", std::ios::in);

                std::string eachDatabaseName = "";

                //storing each database name to the global vector
                if (saveDatabases.is_open()) {
                    while (getline(saveDatabases, eachDatabaseName)) {
                        if (eachDatabaseName != "")
                            currentDatabases.push_back(eachDatabaseName);
                    }
                }
                else {
                    cout << "Error, cannot open database!";
                }

                saveDatabases.close();

            }
            else {
                cout << "Error, cannot create data base!";
            }



        } //if the user entered 2, we will delete the database if it exists
        else if (user_input == 2) {

            //storing all the databases available to the global vector
            std::fstream saveDatabases;
            saveDatabases.open("allDatabases.txt", std::ios::in);

            if (saveDatabases.is_open()) {

                std::string takeDatabase;

                //searching in the file for all the databases that exist
                while (getline(saveDatabases, takeDatabase)) {
                    if (takeDatabase != "")
                        currentDatabases.push_back(takeDatabase); //storing to the vector all databases
                }
                saveDatabases.close(); //always closing the file
            }
            else {
                cout << "Error, cannot open the file that contains databases\n";
            }

            system("cls");
            cout << "Here is a list with all the databases that are available for deletion: \n";

            //printing all the databases that exist
            for (std::string eachDatabase : currentDatabases) {
                cout << eachDatabase << endl;
            }


            cout << "Enter the name of the database that you want to delete: \n";
            std::string databaseName = "";
            cin >> databaseName;
            databaseName += ".txt"; //adding .txt to the file name

            bool databaseFound = false;
            size_t databasePosition = 0;

            //searching for the database inside the vector
            for (const std::string& s : currentDatabases) {

                //if we found the database, exit the for loop
                if (databaseName == s) {
                    databaseFound = true;
                    break;
                }
                databasePosition++;
            }

            system("cls");
            if (databaseFound) {
                cout << "Database " << databaseFound << " was found at position " << databasePosition;
                cout << "\nAre you sure that you want to delete it? 1.Yes 2.No\n";
                callExceptionMethods(&user_input, 'i');

                if (user_input == 1) {

                    //here we delete the database, first from global vector, then the database itself
                    currentDatabases.erase(currentDatabases.begin() + databasePosition);

                    //using c_str() to return a const char pointer to the databaseName string
                    const char* fileName = databaseName.c_str();

                    //here we directly delete the database from the directory by using the pointer
                    system("cls");
                    if (std::remove(fileName) == 0) {
                        cout << "Database " << databaseName << " was deleted successfully\n";
                    }
                    else {
                        cout << "Error, the database could not be deleted\n";
                    }

                    //here we delete the last reference(name) of the database, which is stored in another file
                    std::fstream deleteFileName;
                    std::string currentRow;

                    /*this vector will hold temporarily each line of that notepad file except the
                    one that we want to delete*/
                    std::vector<std::string> temporaryLines;

                    deleteFileName.open("allDatabases.txt", std::ios::in);
                    if (deleteFileName.is_open()) {

                        //traversing the notepad file line by line
                        while (getline(deleteFileName, currentRow)) {

                            /*storing to this vector the name of the databases that we want to keep*/
                            if (currentRow != databaseName)
                                temporaryLines.push_back(currentRow);
                        }

                        deleteFileName.close();

                        //storing back to the file all the name of the databases except for the one that was removed
                        deleteFileName.open("allDatabases.txt", std::ios::out);

                        if (deleteFileName.is_open()) {

                            //travering our vector
                            for (size_t index = 0; index < temporaryLines.size(); index++) {
                                //adding the content back to the same notepad file
                                deleteFileName << temporaryLines[index] << '\n';
                            }

                            deleteFileName.close(); //closing the file one last time
                        }
                        else {
                            cout << "Error, cannot open the file called allDatabases.txt\n";
                        }
                    }
                    else {
                        cout << "Error, cannot open the file called allDatabases.txt";
                    }

                }
                else {
                    cout << "Database was not deleted\n";
                }
            }
            else {
                
                cout << "Error: Database: " << databaseName << " does not exist!\n";
                cout << "Press any number to continue: \n";
                callExceptionMethods(&user_input, 'i');
                system("cls");
            }

            system("cls");

            //if the database was found and deleted, execute this condition
            if (databaseFound) {

                //closing the program every time a database gets deleted and prompting the user to restart the program
                cout << "Database " << databaseName << " deleted successfully! \n";
                cout << "After each deletion of a database the program needs to restart \n";
                cout << "Press any key to shut down the program \n";
                std::string anyKeyToClose = "";
                cin >> anyKeyToClose;
                system("cls");


                cout << "GoodBye!\n";
                exit(0);
            }
            


        }//if user input is 3, skip all the code above
        else if (user_input == 3) {

            //storing again all the available databases to the global vector so that we can use them in other functions
            std::fstream moveDatabases;
            moveDatabases.open("allDatabases.txt", std::ios::in); //opening again the file with the available databases

            if (moveDatabases.is_open()) {
                std::string line = "";

                while (getline(moveDatabases, line)) {
                    currentDatabases.push_back(line); //storing to global vector the databases
                }

                moveDatabases.close();
            }
            else {
                cout << "Error, cannot open the file containing all the databases!\n";
            }

            //if the user did not want to create or delete a database(skip), execute this condition
            if (!currentDatabases.empty()) {
                cout << "Section skipped, enter any number to continue\n";
                callExceptionMethods(&user_input, 'i');
                system("cls");
            }

        }
        

}


//defining the method of the child class
void handleDatabases::accessBaseClassMethods() {

    //creating a unique pointer that points to an object of the base class stored on the heap
    std::unique_ptr<DataBase> myPtr = std::make_unique<DataBase>();

    //accessing the only method of the base class by using that pointer
    myPtr->createDeleteDatabase();


}

//when the user updates a table this function positions the new data to the middle of each table cell
void positionDataToMiddle(std::string &currentTableCell, std::string newData) {


    
    int middleCharPos = 0, leftCharactersPos = 0, rightCharactersPos = 0;

    //this strings represent separate parts of the user input(leftPiece for all the chars from left)
    //and right piece(for all the characters of the string that are from the middle to the right)
    
    std::string leftPiece = "", rightPiece = "";

    //and this will hold the character placed to the middle of the newData
    std::string middleChar = "";

    //finding the position of the middlecharacter (inside the string newData)
    middleCharPos = newData.length() / 2;

    //storing the middle character from the new data string
    middleChar = newData[middleCharPos];


    //storing the characters from the new data string apart from the middle character
    for (size_t i = 0; i < middleCharPos; i++) {
        leftPiece += newData[i];
    }

    for (size_t j = middleCharPos + 1; j < newData.length(); j++) {
        rightPiece += newData[j];
    }

    //finding the middle of the table cell
    int cellMiddlePos = currentTableCell.length() / 2;

    //storing the middle character of the newData string to the middle of the table cell
    currentTableCell.replace(cellMiddlePos, 1, middleChar);

    //and storing the characters from the left of the string to the left of the table cell
    currentTableCell.replace(cellMiddlePos - leftPiece.length(), leftPiece.length(), leftPiece);

    //and the characters from the right of the string(new data string) to the right of the table cell
    currentTableCell.replace(cellMiddlePos + 1, rightPiece.length(), rightPiece);
}

//this function is used to update the content of a notepad file by rewriting it
void updateTablesInDatabase(std::vector<std::vector<std::string>> &updatedTable, int tablePosition, std::string database, int rows) {
    
    tablePosition++;

    //this vector will hold the content of the database and the data from the updated table
    std::vector<std::string> fileContent;

    //opening the database to copy all the data from it and store it temporarily to vector: 'fileContent'
    std::ifstream openDatabase(database);

    std::string eachTableRow = "";

    if (openDatabase.is_open()) {

        std::string eachDocumentLine = "";

        while (getline(openDatabase, eachDocumentLine)) {
            
           //moving the content of the notepad file(currentDatabase) to the vector
            fileContent.push_back(eachDocumentLine);
        }

    }
    openDatabase.close();
    system("cls");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 5; j++) {
            //storing the content of each table row to this string
            eachTableRow += updatedTable[i][j];
        }
      
        //storing each updated table row to the vector that holds all the data from the notepadfile(database)
        fileContent[tablePosition] = eachTableRow;
        tablePosition++;

        eachTableRow = "";
    }

    //opening the same database to override its data
    std::ofstream storeDataBack(database);

    if (storeDataBack.is_open()) {

        //storing all the data(including the updated table) back to the database
        for (int i = 0; i < fileContent.size(); i++) {
            storeDataBack << fileContent[i] << "\n";
        }
    }
    storeDataBack.close();
    
}

//this function is used to extract data from the table
void extractTableData(std::string tableRowContent, std::vector<std::string> &eachTableRow) {
    eachTableRow.clear();

    //this stack will hold temporarily the data on each table cell
    std::stack<char> tableCells;

    //this string will store temporarily only the characters from one table cell
    std::string oneTableCell = "";

    int barNumber = 0;

    for (char ch : tableRowContent) {

        if (ch == '|')
            barNumber++;

        //storing all the table characters to the stack
        if (barNumber < 2) {
            tableCells.push(ch);
        }

        if (barNumber == 2) {
            barNumber--;
            tableCells.push(ch);

            //moving each character from the stack to the string
            while (tableCells.empty() == false) {
                
                //adding the characters to the string one by one
                oneTableCell += tableCells.top();

                //deleting the characters from the stack one by one
                tableCells.pop();
            }

            //reversing the string to have the characters placed in the right order
            std::reverse(oneTableCell.begin(), oneTableCell.end());

            //now we will store the data from the string to a vector of strings
            eachTableRow.push_back(oneTableCell);

            //resetting the string
            oneTableCell = "";

        }
       
    }
}

//defining the second method of the child class
void handleDatabases::CRUD() {
    
    bool databaseFound = false;
    int tryAgain = 0, connectToDatabase = 0;


    cout << "\nWould you like to connect to any database ? 1.Yes 2.No(if you enter 2, the program will exit!)\n";
    callExceptionMethods(&connectToDatabase, 'i');
    system("cls");

    //if the user does not enter 1, the program will stop executing
    if (connectToDatabase != 1) {
        system("cls");
        cout << "Goodbye!\n";
        exit(0);
    }

    cout << "Here is a list with all the databases available: \n";

    //printing all the databases that exist
    for (std::string eachDatabase : currentDatabases) {
        cout << eachDatabase << endl;
    }

    cout << "Ok now enter the name of the database that you want to connect to\n";
    std::string databaseName;
    cin >> databaseName;
    databaseName += ".txt";
    system("cls");


    //using a do while loop to keep searching for database until it is found or until user entered '2'
    do {

        //searching to see if the database exists
        for (const std::string& currentVectorElement : currentDatabases) {
            //if the database was found, exit the loop
            if (currentVectorElement == databaseName) {
                databaseFound = true;
                break;
            }
            
        }

        if (!databaseFound) {
            cout << "Error, database called " << databaseName << " cannot be located, try again? 1.Yes 2.No\n";
            callExceptionMethods(&tryAgain, 'i');
            databaseName = "";
        }

        //if the user wants to enter again the name of the database and to look for it
        if (tryAgain == 1 && !databaseFound) {
            cin.clear();

            //clear the buffer to prepare the console for repeating user input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");

            cout << "Enter the database name again: \n";
            cin >> databaseName;
            databaseName += ".txt";
        }

        //if the database was found execute this condition
        if (databaseFound) {
            continue;
        }

    } while (!databaseFound && tryAgain != 2);

    //if the program found the database, give the user the options to work with tables(if the database has any tables)
    if (databaseFound) {
        std::string tableName = "";
        int user_input = 0;

        cout << "You are now connected to : " << databaseName << " database\n";


        //check to see if the database is not empty
        bool databaseEmpty = true;
        std::fstream checkFileForChars(databaseName, std::ios::in);

        if (checkFileForChars.is_open()) {
            std::string eachDocumentLine = "";

            while (getline(checkFileForChars, eachDocumentLine)) {
                
                //if a line in the notepad file has a character(that is not a whitespace), it means that a table exists
                for (char ch : eachDocumentLine) {

                    //if we found a table, we will stop searching the notepad file
                    if (!isspace(static_cast<unsigned char> (ch))) {
                        databaseEmpty = false;
                        break;
                    }
                }
                
                if (databaseEmpty == false)
                    break;
            }
        }
        //closing the file
        checkFileForChars.close();
        
        //if the file is empty, make the user create a table before proceeding
        if (databaseEmpty) {
            
            cout << "For now, there are no tables inside " << databaseName << endl << endl;
            cout << "You need to create one before you can read, update or delete tables\n\n";
            cout << "This is necessary because you cannot work with an empty database!\n\n";
            cout << "Press 1 to create a table: \n\n";
            callExceptionMethods(&user_input, 'i');

            while (user_input != 1) {
                system("cls");
                cout << "Error, you used a different number, press 1 to create table! \n";
                callExceptionMethods(&user_input, 'i');
                
            }

        }//execute this condition if databases exist
        else if(!databaseEmpty) {
       
            cout << "\n\nYou can now: \n";
            cout << "1.Create table 2.Print content of a table 3.Update a table 4.Delete a table\n";
            cout << "Or press any other number to exit\n";
    
            callExceptionMethods(&user_input, 'i');  //calling this function to validate the input
            system("cls");
        }


        bool user_finished = false;
        bool targetNewDatabase = true;
        bool userFinishedStoringTables = false;

        //we will store the table witdh to this string
        size_t tableWidth = 0;
        
        do {
          
         //1.Create table 2.Read table 3.Update table 4.Delete table 
            
            if (user_input == 1) {
                cout << "Enter the name of the table: \n";
                cin >> tableName;
                system("cls");

                //creating a fixed size container to represent a 5x5 table
                std::string table[5][5];

                bool firstRow = true;
                bool addRowContent = false;
                bool firstWord = true;
                cout << "Enter what type of data you would like to add in this table: \n";

                //creating 5 pointers that will always point to all the columns of the first row of table
                std::string* ptrFirstColumn = &table[0][0], *ptrSecondColumn = &table[0][1];
                std::string* ptrThirdColumn = &table[0][2], *ptrForthColumn = &table[0][3];
                std::string* ptrFifthColumn = &table[0][4];

                //creating an array to store the pointers and use then when traversing the table
                std::string* storePtr[5];
                storePtr[0] = ptrFirstColumn, storePtr[1] = ptrSecondColumn, storePtr[2] = ptrThirdColumn;
                storePtr[3] = ptrForthColumn, storePtr[4] = ptrFifthColumn;


                //this string will hold all the characters of the first row of the table
                std::string allCharactersFirstRow = "";

                //traversing the 2d array(table) and adding data to the first row
                for (size_t row = 0; row < 1; row++) {
                    for (size_t col = 0; col < 5; col++) {

                    //if its the first row, ask the user to specify what data he/she wants to enter
                        if (firstRow) {
                            
                            cout << "\nWhat should column " << col << " contain: \n";
                            std::string columnData = "";
                            cin >> columnData;

                            //add the character '|' before the first word on each row to create the lines inside the table
                            if (firstWord) {
                                firstWord = false;
                                table[row][col] = "|     " + columnData + ":" + "     |"; //ading the user input to each column
                            }
                            else {
                                table[row][col] =  "     " + columnData + ":" + "     |";
                            }
                           
                            //storing all the characters from the first row to this string
                            allCharactersFirstRow += table[row][col];

                        } 


                    }     
                }
                //getting the table width
                tableWidth = allCharactersFirstRow.length();

                //opening the database and storing the name of the table above the table
                std::fstream storeTableName;
                storeTableName.open(databaseName, std::ios::app);
                int position = 0;
                if (storeTableName.is_open()){
                    
                    

                    //reaching the middle of each table by adding whitespaces
                    while (position < tableWidth / 2) {
                        storeTableName << " ";
                        position++;
                    }

                    //placing the name of the table above the table, to the middle of it
                    storeTableName << "*" << tableName << "*" << "\n";
                    
                }
                else {
                    cout << "Error, cannot open the table: " << tableName;
                }
                storeTableName.close();

                cout << "Table created, would you like to add data to the table: " << tableName << "?\n";
                cout << "1.Yes 2.No\n";
                int addData = 0;
                callExceptionMethods(&addData, 'i');

                //if the user wants to add data to the rest of the table, execute this statement
                if (addData == 1) {
                    system("cls");

                    bool hasCompletedTable = false;
                    int pointerIndex = 0;
                    cout << "Here is the table with the current content : \n\n\n";
                    size_t currentInputRow = 1, currentInputCol = 0;
                    
                    std::string moveFromLeft = "";

                        //traversing the table from row 1 to row 4 or until the user finished adding data
                        for (currentInputRow = 1; currentInputRow < 5; currentInputRow++) {


                            for (currentInputCol = 0; currentInputCol < 5; currentInputCol++) {
                             
                                int tableNamePosition = position;
                                std::string spacesFromLeft = "";

                                while (tableNamePosition > 0) {
                                    tableNamePosition--;
                                    spacesFromLeft += " ";
                                }

                                //storing the whitespaces from spacesFromLeft to string: moveFromLeft
                                moveFromLeft = spacesFromLeft;

                                //moving the name of the table to the middle of the console by using whitespaces
                                cout << spacesFromLeft << tableName << "\n";
                                
                                //printing the updated table after each user input
                                for (size_t row = 0; row < 5; row++) {
                                    for (size_t col = 0; col < 5; col++) {
                                        cout << table[row][col];
                                    }
                                    cout << endl;
                                }

                                /*storing the string of each column of the table to the currentPtrString
                                by using the pointer storePtr */
                                std::string currentPtrString = *storePtr[pointerIndex];
                                std::string printedString = "";
                                int i = 0;

                                /*printedString will represent the name of each column of the
                                first row of our table, but without whitespaces and bars*/
                                while (i < currentPtrString.length()) {

                                //getting rid of white spaces and '|' character from the initial string
                                    if (currentPtrString[i] != ' ' && currentPtrString[i] != '|')
                                        printedString += currentPtrString[i];
                                    i++;
                                }
                                
                                
                                //printing the printed string to the console
                                cout << "\nEnter new " << printedString << endl;

                                std::string userInput = "";

                                /*creating an object of this class to call the method inherited
                                from the abstract class */
                                implementAbstractClass accessVirtualFunction;

                                bool firstUserInput = false;

                                //if we are on the first column of the table, this boolean becomes true
                                if (currentInputCol == 0)
                                    firstUserInput = true;
                                else
                                    firstUserInput = false;
                                
                                
                                accessVirtualFunction.modifyUserInput(userInput, currentPtrString, firstUserInput);
                                system("cls");
                             
                                //storing the formatted user input to the table
                                table[currentInputRow][currentInputCol] = userInput;

                                /*At each iteration we will use the next pointer of our array
                                so that we can get access to the next string stored inside the table*/
                                pointerIndex++;

                            }
                            
                            //if the table is not full yet, ask the user if he/she wants to add a new row to the table
                            if (currentInputRow < 4) {
                                cout << "Would you like to add data to the next row? 1.Yes 2.No\n";
                                callExceptionMethods(&user_input, 'i');
                                system("cls");
                                pointerIndex = 0; //resetting the pointer index

                                if (user_input == 2) break;
                            }
                            
                        }
                        hasCompletedTable = true;
                    
                        cout << "Here is the completed table, congratulations! \n\n";

                        /*again, printing the table name after some whitespaces so that the
                        name of the table is placed right at the middle of the table*/
                        cout << moveFromLeft << tableName << endl;
                        
                        //printing the completed table to the user to see
                        for (int row = 0; row < 5; row++) {
                            for (int col = 0; col < 5; col++) {
                                cout << table[row][col];
                            }
                            cout << endl;
                        }

                        cout << "\n\nPress anything to store " << tableName << " to the database : " << databaseName << "\n";
                        callExceptionMethods(&user_input, 'i');
                        system("cls");

                        //since the user finished with the table, this boolean becomes true
                        user_finished = true;

                        system("cls");
                        cout << "Table stored! \n";
                        cout << "Press any number to continue: \n";
                        callExceptionMethods(&user_input, 'i');

                        //storing the table to the database that the user is connected to

                }
                else {
                    system("cls");

                    //since the user finished with the table, user_finished becomes true
                    user_finished = true;

                    cout << "Press anything to store " << tableName << " to the database : " << databaseName << "\n";
                    callExceptionMethods(&user_input, 'i');

                    cout << "Table " << tableName << " was successfully saved!\n";
                    cout << "Press any number to continue: \n";
                    callExceptionMethods(&user_input, 'i');
                    
                    system("cls");
                    
                }

                //storing the table to the database:
                std::fstream storeTable;
                storeTable.open(databaseName, std::ios::app);

                if (storeTable.is_open()) {
                    bool exitTable = false;

                    std::string eachTableElement = "";
                    
                    for (size_t row = 0; row < 5; row++) {
                        for (size_t col = 0; col < 5; col++) {
                        
                            //if there are no more elements left inside the table, exit the loops
                            if (table[row][col] == "") {
                                exitTable = true;
                                break;
                            }

                            //storing each element of the table to the notepad file(database)
                            eachTableElement = table[row][col];

                            if (col == 4)
                                storeTable << eachTableElement + "\n";
                            else
                                storeTable << eachTableElement;
                        }

                        if (exitTable) break;
                    }
                    storeTable << "\n\n"; //adding spaces between tables inside the notepad file
                    
                }
                else {
                    cout << "Error, database " << databaseName << " could not be opened!\n";
                }
                storeTable.close(); //closing the file

            }
            else if (user_input == 2) {
                //Caz 2: print a specific table of a database or all the tables

                cout << "Would you like to see all the tables from the database: \n" << databaseName << "\n";
                cout << "Or would you like to see a specific table ? \n";
                cout << "1.Specific table 2.All tables from the database\n";
             
                int tableChoice = 0;
                callExceptionMethods(&tableChoice, 'i');
                system("cls");

                if (tableChoice == 1) { //if the user wants to see a specific table, execute this condition

                    std::fstream storeTableNames;
                    storeTableNames.open(databaseName, std::ios::in);

                    std::string wholeTableLine = "", tableName = "", tableLineWithoutSpaces = "";
                    
                    bool tableFound = false;

                    if (storeTableNames.is_open()) {

                        cout << "Enter the name of the table that you want to see: \n";
                        cin >> tableName;
                        
                        system("cls");
                        
                        //traversing the notepad file(the database)
                        while (getline(storeTableNames, wholeTableLine)) {
                            
                            //traversing every line of the notepad file
                            for (char c : wholeTableLine) {
                                
                                //storing to the string down below all the characters that are not whitespaces
                                if (!isspace(c)) {
                                    tableLineWithoutSpaces += c;
                                }
                            }

                            //if we found the table name after removing the whitespaces,execute this condition
                            if (tableLineWithoutSpaces == tableName) {
                                tableFound = true;
                            }

                            //if the table was found, we print it here
                            if (tableFound == true) {
                                cout << wholeTableLine << "\n";
                            }

                            //if we reach the end of the table that we found, stop the loop
                            if (tableFound && wholeTableLine == "")
                                break;

                            tableLineWithoutSpaces = "";
                        }

                        //if the table was found, execute this condition
                        if (tableFound) {
                            cout << "Press anything to continue:\n ";
                            std::string takeAnyUserInput = "";
                            cin >> takeAnyUserInput;
                            system("cls");
                        }
                        else {
                            //if the table name does not exist, execute this condition
                            cout << "Error, the table that you entered does not currently exist!\n";
                            cout << "Try again later!\n";
                            cout << "Press anything to continue: \n";
                            std::string anyKey = "";
                            cin >> anyKey;
                            system("cls");
                        }
                        
                    }
                    else {
                        cout << "Error, cannot open file\n";

                    }

                    system("cls");
                   
                }
                else if (tableChoice == 2) { //if the user wants to see all the table execute this condition
                    
                    cout << "Here are all the tables from : " << databaseName << "\n\n";
                    //accessing the notepad file(database) to print all of its content(tables)
                    std::fstream allDatabaseTables;
                    allDatabaseTables.open(databaseName, std::ios::in);

                    if (allDatabaseTables.is_open()) {
                        
                        std::string eachNotepadLine = "";
                        
                        while (getline(allDatabaseTables, eachNotepadLine)) {
                            cout << eachNotepadLine << "\n";
                        }
                    }
                    else {
                        cout << "Error, cannot open the database : " << databaseName << "\n";
                    }
                    allDatabaseTables.close();

                    cout << "Press anything to continue : \n";
                    std::string anyUserInput = "";
                    cin >> anyUserInput;
                    system("cls");
                }
                
            }//if the user wants to update the content of a table, execute this function
            else if (user_input == 3) {

                cout << "Search the database and enter the name of the table that you want to update \n";

                std::fstream accessDatabase(databaseName, std::ios::in);

                if (accessDatabase.is_open()) {
                    std::string storeAllDocumentLines = "";

                    while (getline(accessDatabase, storeAllDocumentLines)) {

                        cout << storeAllDocumentLines << endl;
                    }
                }
                accessDatabase.close();

                bool tableExists = false;
                
               
                std::string currentTableName = "", tableRowWithoutSpaces = "";
                cout << "\nEnter name here: \n";
                cin >> currentTableName;
                system("cls");
                
                std::fstream openCurrentDatabase(databaseName, std::ios::in);
                int tablePositionInFile = 0, tableRows= -1;

                int tableMiddle = 0;
                bool executedOnce = false;

                //opening the database to start looking for the table that the user wants to update
                if (openCurrentDatabase.is_open()) {
                    
                    std::string contentOnEachLine = "";
                    while (getline(openCurrentDatabase, contentOnEachLine)) {

                        //now we look for the name of the table on each document line

                        if (!tableExists) {
                            for (char ch : contentOnEachLine) {

                                if (!isspace(ch)) {
                                    tableRowWithoutSpaces += ch;
                                }
                            }
                        }
                        
                        
                        if (currentTableName == tableRowWithoutSpaces) {
                            tableExists = true;
                        }

                        if (tableExists) {
                            
                            //counting the number of columns of the table
                            if (contentOnEachLine != "") tableRows++;
                            else break;
                        }

                        tableRowWithoutSpaces = "";
                        
                        if (!tableExists)
                            tablePositionInFile++;
                    }
                    openCurrentDatabase.close();

                    if (tableExists) {
                        int row = 0, column = 0;
                        std::vector<std::string> storeEachTableRow;

                        std::vector<std::vector<std::string>> theTable;


                        //opening the same file to print the table so that the user can update it
                        std::fstream openSameFile(databaseName, std::ios::in);
                        int rows = tableRows;
                        

                        if (openSameFile.is_open()) {
                            int currentDocumentLine = -1;
                            contentOnEachLine = "";

                            while (getline(openSameFile, contentOnEachLine)) {
                                std::vector<std::string> DataOnTableRow;

                                //if we stored all the content from the table to the 2d vector
                                //we will stop searching the file
                                if (tableRows == 0)
                                    break;

                                //when we reach the table, this condition will execute
                                if (currentDocumentLine >= tablePositionInFile) {
                                    tableRows--;


                                    //finding the middle of the table
                                    if (executedOnce == false)
                                        tableMiddle = contentOnEachLine.size() / 2;
                                    executedOnce = true;

                                    
                                    extractTableData(contentOnEachLine, storeEachTableRow);

                                    //storing each vector(table row) to the 2d vector(the table itself)
                                    theTable.push_back(storeEachTableRow);


                                }
                                else
                                    currentDocumentLine++;
                            }
                        
                        }
                        openSameFile.close();

                        system("cls");
                        cout << "Table found! Here is the table: \n\n";

                       
                        std::string containsWhiteSpaces = "";

                        //adding spaces to this string
                        while (tableMiddle > 0) {
                            containsWhiteSpaces += " ";
                            tableMiddle--;
                        }

                        int tableFinishedUpdating = 0;
                        int userChoice = 0;
                        bool loopExecutedOnce = false, dataEntered = false;

                        do {

                            if (dataEntered)
                                cout << "                    Here is the updated table: \n\n";

                            //printing the name of the table to the middle of the table
                            cout << containsWhiteSpaces << currentTableName << "\n\n";


                            //printing the table
                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < 5; j++) {
                                    cout << theTable[i][j];
                                }
                                cout << endl;
                            }


                            if (loopExecutedOnce) {
                                cout << "\n\nWould you like to add new data to the table ? 1.Yes 2.No\n";
                               

                                callExceptionMethods(&userChoice, 'i');

                                //if userChoice is 2
                                if (userChoice == 2) {
                                    tableFinishedUpdating = 1;

                                    system("cls");
                                    cout << "Everything was successfully stored to the table \n";
                                    cout << "Press any number to continue: \n";
                                    callExceptionMethods(&userChoice, 'i');
                                }
                                    
                            }

                            if (tableFinishedUpdating == 0) {


                                cout << "\n\n";
                                cout << "Enter the row where you want to update data: \n";
                                cin >> row;

                                cout << "Now enter the column where you want to update data: \n";
                                cin >> column;

                                //if the user input is not a valid position inside the table, execute this condition
                                if (row > rows - 1 || column > 4) {
                                    system("cls");

                                    cout << "Error, this position does not exist! \n\n";
                                    cout << "Reason, the number is too great\n\n";
                                    cout << "Enter any number to continue: \n\n";

                                    int tryAgain = 0;
                                    callExceptionMethods(&tryAgain, 'i');

                                    system("cls");
                                }
                                else {

                                    system("cls");

                                    cout << containsWhiteSpaces << currentTableName << "\n\n";

                                    //printing the table with an empty cell 
                                    for (int i = 0; i < rows; i++) {
                                        for (int j = 0; j < 5; j++) {

                                            if (i == row && j == column) {
                                                int cellWidth = theTable[i][j].length();

                                                //creating an empty cell inside the table where user input will be stored
                                                std::string emptyCell = "";


                                                while (cellWidth > 1) {
                                                    cellWidth--;

                                                    emptyCell += " ";
                                                }

                                                emptyCell += "|";

                                                if (column > 0)
                                                    cout << emptyCell;
                                                else {
                                                    emptyCell.erase(0, 1);

                                                    cout << "|" << emptyCell;
                                                }
                                                
                                                    
                                            }
                                            else {
                                                cout << theTable[i][j];
                                            }

                                        }
                                        cout << endl;
                                    }

                                    //taking new data from the user input
                                    cout << "Enter the new data in the empty cell(the one you selected)\n";
                                    std::string newData = "";
                                    cin >> newData;
                                    system("cls");


                                    //here we clear the previous data from the current table cells
                                    for (size_t i = 1; i < theTable[row][column].length() - 1; i++) {
                                        theTable[row][column].replace(i, 1, " ");
                                    }


                                    //making sure the size of the new data can fit the size of the table cell
                                    while (newData.length() > theTable[row][column].length() - 3) {
                                        system("cls");
                                        cout << "Error data is too large to fit the table cell, try again \n";
                                        cout << "Enter the data here: \n";
                                        cin >> newData;
                                    }

                                    //calling this function to position the new user input to the middle of each table cell
                                    positionDataToMiddle(theTable[row][column], newData);

                                }
                            }

                            loopExecutedOnce = true;
                         

                        } while (tableFinishedUpdating == 0);
                        
                        system("cls");

                        //storing the modified table back to the notepad file
                        updateTablesInDatabase(theTable, tablePositionInFile, databaseName, rows);
                        
                    }
                    else {
                        cout << "Error, the table: " << currentTableName << " does not exist! \n";
                        cout << "Press any key to continue: \n";
                        std::string currentUserInput = "";
                        cin >> currentUserInput;
                        system("cls");
                    }
                }
                tableExists = false;

            }//if the user wants to delete a specific table, execute this condition
            else if (user_input == 4) {
                
                //this vector will hold all the rows inside the notepad file(database)
                std::vector<std::string> containsDocumentLines;


                //this 2 variables will tell us the position of the table that will be deleted
                //and its number of rows(so that we can delete the whole table and not miss a row)
                int deletionPosition = 0;
                int nrOfRowsToBeDeleted = 0;

               system("cls");
               cout << "Here are all the tables that exist inside database " << databaseName << "\n\n\n";

               //opening the database to print to the user all the available tables
               std::ifstream openCurrentDatabase(databaseName);

               if (openCurrentDatabase.is_open()) {

                   std::string storeDocumentLines = "";

                   while (getline(openCurrentDatabase, storeDocumentLines)) {
                       cout << storeDocumentLines << endl;

                   }
               }
               openCurrentDatabase.close();

               cout << "\n\n";
               cout << "Enter the name of the table that you want to delete: \n";
               cin >> tableName;

               std::fstream deleteTables;
               deleteTables.open(databaseName, std::ios::in);

               std::string notepadLines = "", firstTableRow = "";

               bool tableFound = false;
               bool tablePrinted = false;

               if (deleteTables.is_open()) {

                   system("cls");

                   //traversing the notepad file(the database)
                   while (getline(deleteTables, notepadLines)) {

                       //storing to the vector all the document lines
                       containsDocumentLines.push_back(notepadLines);

                       //traversing every line of the notepad file
                       for (char c : notepadLines) {

                           //storing to the string down below all the characters that are not whitespaces
                           if (!isspace(c)) {
                               firstTableRow += c;
                           }
                       }

                       //if we found the table name after removing the whitespaces,execute this condition
                       if (firstTableRow == tableName) {
                           tableFound = true;
                       }

                       //if the table was found, we print it here
                       if (tableFound == true && tablePrinted == false) {
                           nrOfRowsToBeDeleted++;
                           cout << notepadLines << "\n";
                       }

                       //if we reach the end of the table that we found, stop the loop
                       if (tableFound && notepadLines == "") {
                           tablePrinted = true;
                       }
                           

                       firstTableRow = "";

                       //increasing this variable until we find the position of the table that will be deleted
                       
                       if(!tableFound)
                       deletionPosition++;
                   }

                   openCurrentDatabase.close();

                   //if the table was found, execute this condition
                   if (tableFound) {
                       cout << "Table " << tableName << " was found!\n";
                       cout << "Are you sure that you want to delete it ? 1.Yes 2.No\n";
                       callExceptionMethods(&user_input, 'i');

                       //execute this statement if the user will delete the table
                       if (user_input == 1) {
                           system("cls");


                           //deleting the table from the database:

                           //we will first delete all the table data that was stored in this vector
                           containsDocumentLines.erase(containsDocumentLines.begin() + deletionPosition, containsDocumentLines.begin() + deletionPosition + nrOfRowsToBeDeleted);

                           //then we will store back the content of the notepadfile(without the deleted table):
                           std::ofstream putBackContent(databaseName);

                           if (putBackContent.is_open()) {

                               //here we are adding back the tables to the database(except for the one deleted)
                               for (size_t i = 0; i < containsDocumentLines.size(); i++) {
                                   putBackContent << containsDocumentLines[i] << endl;
                               }
                           }
                           putBackContent.close();

                           system("cls");
                           cout << "Table " << tableName << " was deleted successfully! \n\n";

                           cout << "Enter any key to continue : \n";
                           std::string takeUserInput = "";

                           cin >> takeUserInput;
                           system("cls");
                       }

                       if (user_input == 2) {
                           system("cls");
                           cout << "Deletion canceled! \n";
                           cout << "Press any key to continue : \n";
                           std::string userStringInput = "";
                           cin >> userStringInput;
                           system("cls");
                       }
                   }
                   else {
                       //if the table name does not exist, execute this condition
                       cout << "Error, the table that you entered does not currently exist so it cannot be deleted!\n";
                       cout << "Try again later!\n";
                       cout << "Press anything to continue: \n";
                       std::string anyKey = "";
                       cin >> anyKey;
                       system("cls");
                   }


               }
            }//for any user input different than 1,2,3,4, execute this condition
            else {
                system("cls");
                
                break;

            }
            
            //check to see if there are any tables left in case the user deleted some tables
            std::ifstream checkOneLastTime(databaseName);
            bool isDatabaseEmpty = true;

            if (checkOneLastTime.is_open()) {
                std::string everyLine = "";

                while (getline(checkOneLastTime, everyLine)) {

                    for (char ch : everyLine) {
                        if (!isspace(static_cast<unsigned char> (ch))) {
                            isDatabaseEmpty = false;
                            break;
                        }
                    }

                    if (!isDatabaseEmpty)
                        break;
                }
            }



            //if there are any tables left, ask the user if he/she wants again to create, read,update,delete a new table
            if (!isDatabaseEmpty){
                system("cls");
                cout << "\nBefore you leave do you want to: \n\n1.Create one more table \n\n2.Read a new table\n\n";
                cout << "3.Update a new table \n\n4.Delete one more table \n\nOr any other number to leave\n";
                callExceptionMethods(&user_input, 'i');

                if (user_input >= 1 && user_input <= 4) user_finished = false;
                else user_finished = true;

            }//if there are no more tables left(because the user deleted them), the user has now to options
            else {
                system("cls");

                //option1: Create a new table to work with or option2: Leave this section for now
                cout << "Now there are no more tables left, would you like to:\n\n 1.Create one more table\n\n";
                cout << "Or any other number to leave this section : \n";
                callExceptionMethods(&user_input, 'i');

                if (user_input != 1) user_finished = true;
                else user_finished = false;
            }

            system("cls");
            
        //keep running the loop as long as the user works with tables or targets new databases
        } while (!user_finished );
       
        
    }
    else { //stop the program from running if the user does not want to connect to any database
        system("cls");
        cout << "Goodbye!\n";
        exit(0);
    }


}

void rateDatabase::giveRating(bool duplicatesInTables, bool emptyDatabase) {

    system("cls");

    //here a rating is created based on the number of issues found
    cout << "Troubleshoot finished, press any number to see the results: \n";
    int userInput = 0;

    callExceptionMethods(&userInput, 'i');
    system("cls");

    if (duplicatesInTables) {
        
        cout << "One issue was found, there are duplicates on at least one table row! \n\n";
    }

    if (emptyDatabase) {
        cout << "A huge issue was found, the database that you tried to access is empty! \n\n";
    }

    if (!duplicatesInTables && !emptyDatabase) {
        cout << "There are no issues with this database :D \n";
    }

    cout << "Press any key to see how functional is the database: \n";
    std::string anyKey = "";
    cin >> anyKey;


    system("cls");

    int grade = 10;

    if (duplicatesInTables && emptyDatabase) {
        grade -= 4;
    }
    else if (duplicatesInTables || emptyDatabase) {
        grade -= 2;
    }
    
    cout << "This database grade is " << grade << "\n\n";
    cout << "This represents how functional the database on a scale of 1-10\n\n";

    if (grade == 8)
        cout << "The database has a few issues but it's functional\n\n";
    else if (grade == 6)
        cout << "The database has some issues, it's not so reliable \n\n";
    else
        cout << "This database is in perfect condition, 10/10\n\n";

    cout << "Thank you for using custom database!! \n\n";
    cout << "Press any key to stop the program : \n\n";

    cin >> anyKey;


}

void rateDatabase::findPotentialIssues() {

    int userChoice = 0;

    cout << "Before a rating can be given, you need to select a database \n\n";
    cout << "Here is a list with all the available databases: \n\n";

    std::string databaseName = "";
    std::vector<std::string> storeDatabaseNames;

    //opening the file that contains all the databases that exist
    std::ifstream openFileContainingDatabases("allDatabases.txt");

    if (openFileContainingDatabases.is_open()) {

        std::string eachDocumentLine = "";

        while (getline(openFileContainingDatabases, eachDocumentLine)) {

            cout << eachDocumentLine << endl;

            //storing to this vector all the database names
            storeDatabaseNames.push_back(eachDocumentLine);
        }

    }//closing the file
    openFileContainingDatabases.close();



    cout << "\n\nEnter the name of the database: \n";
    cin >> databaseName;

    bool databaseFound = false;

    do {

        //finding if the name entered by the user is a valid database
        for (std::string currentDatabase : storeDatabaseNames) {
            
            if (currentDatabase == databaseName)
                databaseFound = true;
        }

        
        if (databaseFound) {
            system("cls");
            cout << "\n\nDatabase " << databaseName << " was found!\n\n";

            //take new user input
            cout << "Press 1 to let the program troubleshoot this database and the rate it \n\n";
            cout << "Or press any other number to exit the program \n";
            cin >> userChoice;

        }//execute this condition in case the database name typed by the user is not a valid database
        else {
            system("cls");
            cout << "Error, database " << databaseName << " does not exist, try again\n\n";
            cout << "Enter the name here: \n";
            cin >> databaseName;
        }


    } while (databaseFound == false);


    //here we stop the program if user choice is not 1
    if (userChoice != 1)
        exit(0);


    /*here the program will troubleshoot the current database and search for potential issues
    if there are no issues with the database, the program will give it the highest rating
    if there are many issues such as duplicate data inside tables or empty databases etc..
    the program will give it a small rating  */


    bool duplicatesInTables = false, emptyDatabase = true;


    //here the program checks if the database ie empty:
    std::ifstream checkIfEmpty(databaseName);

    if (checkIfEmpty.is_open()) {

        std::string eachLineFromNotepad = "";

        while (getline(checkIfEmpty, eachLineFromNotepad)) {

            if (eachLineFromNotepad != "") {
                emptyDatabase = false;
                break;
            }
               
        }
    }
    checkIfEmpty.close();


    //now the program will look for duplicates inside each table(duplicates meaning identical data on the same table row)
    bool tableFound = false;
    int barNumber = 0;

    std::vector<std::string> allDataOnOneRow;

    std::ifstream lookForDuplicates(databaseName);

    if (lookForDuplicates.is_open()) {

        std::string everyLine = "";

        while (getline(lookForDuplicates, everyLine)) {


            if (everyLine[0] == '|')
                tableFound = true;
           
            if (everyLine == "")
                tableFound = false;


            //if we reached a table we will store the data to a vector of strings to start looking for duplicates
            if (tableFound) {
                
                std::string tableCell = "";

                //traversing the string that holds each table row
                for (size_t i = 0; i < everyLine.length(); i++) {


                    if (everyLine[i] == '|') barNumber++;

                    //taking the data from each table cell
                    if (everyLine[i] != '|' && everyLine[i] != ' ' && barNumber < 2)
                        tableCell += everyLine[i];

                    if (barNumber == 2) {
                        barNumber--;
                    

                        //storing each table cell to this vector
                        allDataOnOneRow.push_back(tableCell);
                        tableCell = "";
                    }
                }

                //sorting the data in vector
                sort(allDataOnOneRow.begin(), allDataOnOneRow.end());

                //traversing the vector that holds the data from each table cell and looking for duplicates
                for (size_t i = 0; i < allDataOnOneRow.size()-1; i++) {

                    //looking for duplicates from the table that are stored in this vector
                    if (allDataOnOneRow[i] == allDataOnOneRow[i + 1])
                        duplicatesInTables = true;

                }


                allDataOnOneRow.clear();
            }
            
            //if we found duplicate data inside the vector, we will stop searching 
            if (duplicatesInTables)
                break;
        }
    }
    lookForDuplicates.close();
 
    giveRating(duplicatesInTables, emptyDatabase);
}