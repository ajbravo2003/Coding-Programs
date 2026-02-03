  #/**------------------------------------------
#     Project 2 – Chicago Lobbyist Database App
#     Course: CS 341,
#     System: Codio IDE 2025
#     Author: Alejandro Bravo
#  ---------------------------------------------**/
import sqlite3
import objecttier

def command1(dbConn):#function that runs command 1
    userInput = input("Enter lobbyist name (first or last, wildcards _ and % supported): \n")#takes user input
    values = objecttier.get_lobbyists(dbConn,userInput)#gets objects of lobbyists
    print()
    print("Number of lobbyists found: " + str(len(values)))#prints number of lobbyists found
    if len(values)<100:
        for rows in values:#prints info about Lobbyists
            print(str(rows.Lobbyist_ID) + " : "+rows.First_Name +  " " + rows.Last_Name + " Phone: " + str(rows.Phone))
    else:
        print("There are too many lobbyists to display, please narrow your search and try again...")#displays error when 100 lobbyists

def command2(dbConn):#function that runs command 2
    userInput = input("Enter Lobbyist ID:")
    print()
    value = objecttier.get_lobbyist_details(dbConn,userInput)#gets object with the lobbyist ID
    if value:#checks to make sure there is a lobbist with that id
            print(str(value.Lobbyist_ID) + " :")#prints lobby id
            print("  Full Name: " + value.Salutation+ " "+ value.First_Name + " " + value.Middle_Initial + " " + value.Last_Name + " "+ value.Suffix)#prints lobbyist info
            print("  Address: " + value.Address_1 + " " + value.Address_2 + " , "+  value.City + " , " + value.State_Initial  + " " + str(value.Zip_Code) + " " + value.Country)
            print("  Email: " + value.Email)
            print("  Phone: " + str(value.Phone))
            print("  Fax: "+ str(value.Fax))
            years = ""#uses string to add all items in list 
            for year in value.Years_Registered:
                years += str(year) + ", "#adds year and comma

            print("  Years Registered: " + years)#prints values
            employer = ""#uses string to add all items in list 
            for employers in value.Employers:#loops through employers
                employer += str(employers) + ", "#adds year and comma

            print("  Employers: " + employer)#prints values
            print(f"  Total Compensation: ${value.Total_Compensation:,.2f}")#prints compensation
    else:#error message when no lobbbyist is found
        print("No lobbyist with that ID was found.")

def command3(dbConn):#function that runs command 3
    userN = input("Enter the value of N: ")#asks for user N value
    if int(userN) <= 0:#checks for postive N value
        print("Please enter a positive value for N...")
        return
    userYear = input("Enter the year: ")#asks for year

    values = objecttier.get_top_N_lobbyists(dbConn,int(userN),userYear)#gets top ten lobbyists
    if values:
        counter = 1 
        print()
        for lobbyist in values:#Goes through every lobbyist in list
            print(str(counter) + " . " + lobbyist.First_Name + " " + lobbyist.Last_Name)#prints lobbyist details
            print("  Phone: "+ str(lobbyist.Phone))
            print(f"  Total Compensation: ${lobbyist.Total_Compensation:,.2f}")#adds comma and rounds to two decimal places
            clients = ""#uses string to add all items in list 
            
            for client in lobbyist.Clients:#loops through clients
                clients += str(client) + ", "#adds year and comma

            print("  Clients: " + clients)#prints values
            counter+=1#adds to counter

def command4(dbConn):#function that runs command 4
    year = input("Enter year: ")#asks for user year and ID
    lobbyID = input("Enter the lobbyist ID: ")
    result = objecttier.add_lobbyist_year(dbConn,lobbyID, year)#adds year
    if result == 0 or result == -1:#Id isnt found
      print()
      print("No lobbyist with that ID was found.")

    elif result==1:#ID is found and year is inserted
        print()
        print("Lobbyist successfully registered.")

def command5(dbConn):#function that runs command 5
    lobbyID = input("Enter the lobbyist ID: ")#asks for salutation and ID
    salutation = input("Enter the salutation: ")
    result = objecttier.set_salutation(dbConn,lobbyID, salutation)#adds salutation
    if result == 0 or result ==-1:#lobbyist isnt found
      print()
      print("No lobbyist with that ID was found.")

    elif result == 1:#ID is found and salutation is inserted
        print()
        print("Salutation successfully set.")

##################################################################  
#main
##################################################################
dbConn = sqlite3.connect('Chicago_Lobbyists.db')
print('** Welcome to the Chicago Lobbyist Database Application **')
print("General Statistics:")#prints general Statistics
print("  Number of Lobbyists:" ,f"{objecttier.num_lobbyists(dbConn):,}")
print("  Number of Employers:" ,f"{objecttier.num_employers(dbConn):,}")
print("  Number of Clients:" ,f"{objecttier.num_clients(dbConn):,}")
print()
cmd = input("Please enter a command (1-5, x to exit): ")
while cmd != "x":
    if cmd == "1":
        print()
        command1(dbConn)#calls 1st command 
    
    elif cmd == "2":
        print()
        command2(dbConn)#calls 2nd command

    elif cmd =="3":
        print()
        command3(dbConn)#calls 3rd command
    
    elif cmd =="4":
        print()
        command4(dbConn)#calls 4th command

    elif cmd =="5":
        print()
        command5(dbConn)#calls 5th command
       
        
    else:
        print("**Error, unknown command, try again...")#prints error message when command isnt 1-5
    print()    
    cmd = input("Please enter a command (1-5, x to exit): ")#asks for user input again till x is inputted
dbConn.close()#closes connection
