#include <iostream>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdio> //header to use remove function for files
#include "ClassesHeader.h"

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
                    cout << "Error, password must contain upper characters also\n";
                    cout << "Try again \n";
                    cin >> password;
                    system("cls");
                }

                //if the character is not digit, execute this loop again
                if (hasDigits == false) {
                    cout << "Error, password must contain at least one digit\n";
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
        }
        else if (user_input == 2) {
            system("cls");

            cout << "Welcome to the login section, press any number to start: \n";
            callExceptionMethods(&user_input, 'i');

            bool userFound = false, passwordFound = false;

            do {
                userFound = false;
                passwordFound = false;

                std::cout << "Enter username: ";
                cin >> name;

                std::cout << "Enter password: ";
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
                    std::cerr << "Error, file could not be opened\n";
                    cout << "Press any key to continue \n";
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

            std::cout << "Account accepted!\n";
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
    if (currentDatabases.size() > 1) {
        cout << "What would you like to do with a database: 1.Create 2.Delete or 3.Skip\n";
        callExceptionMethods(&user_input, 'i');
    }
    else if(currentDatabases.size() == 1){
       
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
    if(currentDatabases.size() == 1 && createDatabase == 1){
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
            cout << "Or press any other number to continue : \n";
    
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
                                table[row][col] = "|     " + columnData + "     |"; //ading the user input to each column
                            }
                            else {
                                table[row][col] =  "     " + columnData + "     |";
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

                        cout << "Press anything to store " << tableName << " to the database : " << databaseName << "\n";
                        callExceptionMethods(&user_input, 'i');
                        system("cls");

                        //since the user finished with the table, this boolean becomes true
                        user_finished = true;

                        //storing the table to the database that the user is connected to

                }
                else {
                    system("cls");

                    //since the user finished with the table, user_finished becomes true
                    user_finished = true;

                    cout << "Press anything to store " << tableName << " to the database : " << databaseName << "\n";
                    callExceptionMethods(&user_input, 'i');
                    
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

                    cout << "Table was successfully saved! \n";
                    cout << "Press any key to continue: \n";
                    std::string anyKey = "";
                    cin >> anyKey;
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

                

            }//if the user wants to delete a specific table, execute this condition
            else if (user_input == 4) {



            }//for any user input different than 1,2,3,4, execute this condition
            else {



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
            if (!isDatabaseEmpty) {
                system("cls");
                cout << "Before you leave do you want to: 1.Create one more table 2.Read a new table\n";
                cout << "3.Update a new table 4.Delete one more table or any other number to leave\n";
                callExceptionMethods(&user_input, 'i');

                if (user_input >= 1 && user_input <= 4) user_finished = false;
                else user_finished = true;

            }//if there are no more tables left(because the user deleted them), the user has now to options
            else {
                system("cls");

                //option1: Create a new table to work with or option2: Leave this section for now
                cout << "Now there are no more tables left, would you like to 1.Create one more table\n";
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
