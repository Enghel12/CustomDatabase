# This is a program made in C++ that acts as a custom database.

This software simulates the functionality of a database, incorporating fundamental Create, Read, Update, and Delete (CRUD) operations.
The primary objective of this project was to innovate a database system for local usage.

## How it works

The user can create, read, update or delete the data inside the tables, the databases are represented by notepad files(each database is a notepad file). The stored data will be
represented by strings.
All in all, this program was created to serve as a custom database for the user and to have some features (such as the rating feature) that other databases like MySql do not have.

## Rating system added
A unique feature worth mentioning is that this program now has a class that can rate the functionality of a database based on the number of issues found. Then, it will give a
grade to the database(a rating) from 1-10. For now this class can find three issues inside a database:

1.Duplicate/identical data on the same row of a table
2.An empty database, even though it should have some data in it
3.Empty table cells

For the time being, the grade can be 10(if no issues are found), 8(one issue is found) and 6(two issues are found). 

