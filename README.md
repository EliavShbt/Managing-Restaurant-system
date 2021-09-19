# Restaurant-management-system
## Table of contents
* [General info](#general-info)
* [Setup](#setup)

## General info
System for managing restaurant orders and bills, handling each table's bill and dishes.   
The project is all written in 'C' language and uses files only, meaning there is no interaction with the user directly,   it reads the Instructions from the 'Instructions.txt' file and getting the info about the possible meals and type of food from 'Manot.txt' file.
	
## Setup
To run this project, run 'main.c' file.
* 'Instructions.txt' file - The first line in the file stands for the number of tables available in the restaurant
  Each line start with number that represent the instruction the program needs to execute
```
'1' = Creating the possible dishes(meals) in the kitchen that the restaurant can sale
'2' = Updating stock of specific meal
'3' = Ordering meals to a spesific table
'4' = Canceling one item from the order (the item will not be included in the final bill of the table)
'5' = Closing table - calculating the final bill the table needs to pay (including the tip which is 10% of the final amount)
```
* 'Manot.txt' file:
```
"Steak 31 25" = The restaurant has 'Steak' meal with 40 possible steak units to sell in 25$ for each steak.
```
