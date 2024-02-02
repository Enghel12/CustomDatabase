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
    
    
    return 0;
}
