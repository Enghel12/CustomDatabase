#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include "ClassesHeader.h"



int main()
{
    
    
    //calling the first function of our program to promp the user for registration/log in
    registerLogin();

    //creating an instance of the child class and calling its method to call the method of base class
    handleDatabases childClassMethood;
    childClassMethood.accessBaseClassMethods();


    //calling the second method of child class
    childClassMethood.CRUD();
    

    cout << "Before you leave would you like to : \n\n1.See the rating of a database based on its functionality? \n\n2.Exit completely\n";
    int newUserChoice = 0;

    cin >> newUserChoice;
    system("cls");

    system("cls");
    if (newUserChoice != 1)
        exit(0);

    

   //creating an object of this class to call its functions
    rateDatabase callFunctions;

    //calling the function of class 'rateDatabase' to search for potential issues and create a rating
    callFunctions.findPotentialIssues();

    

    
    return 0;
}

