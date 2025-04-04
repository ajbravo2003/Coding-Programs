# /**------------------------------------------
#     Project 1 – CTA Database App
#     Course: CS 341, Spring 2024.
#     System: Codio IDE 2024
#     Author: Alejandro Bravo
#  ---------------------------------------------**/
import sqlite3
import matplotlib.pyplot as plt
##################################################################  
# print_stats
# Given a connection to the CTA database, executes various
# SQL queries to retrieve and output basic stats.
#
 
def print_stats(dbConn):
    dbCursor = dbConn.cursor()
    
    print("General Statistics:")
    
    dbCursor.execute("Select count(*) From Stations;") # retrives the amount of stations
    row = dbCursor.fetchone();
    print("  # of stations:", f"{row[0]:,}") #prints the count of stations
    
    dbCursor.execute("Select count(*) From Stops;") #gets count of stops
    row = dbCursor.fetchone();
    print("  # of stops:", f"{row[0]:,}") #prints count of stops
   
    dbCursor.execute("Select count(*) From Ridership;") #gets count of ride entries
    row = dbCursor.fetchone();
    print("  # of ride entries:", f"{row[0]:,}") #prints count of ride entries

    dbCursor.execute("SELECT strftime('%Y-%m-%d', MIN(Ride_Date)) as MinDate, strftime('%Y-%m-%d', MAX(Ride_Date)) as MaxDate FROM Ridership")
    row = dbCursor.fetchone()#gets the row
    minDate, maxDate = row #sets row into a two variables
    print(f"  date range: {minDate} - {maxDate}")#gets the earliest and oldest dates 
      
    dbCursor.execute("Select SUM(Num_Riders) From Ridership;") #gets number of riders
    row = dbCursor.fetchone();
    print("  Total ridership:", f"{row[0]:,}") #prints number of ridership
    print()


def command1(dbConn):
    print()
    userInput = input("Enter partial station name (wildcards _ and %): ")
    Stations = "SELECT Station_ID, Station_Name FROM Stations WHERE Station_Name LIKE? ORDER BY "
    dbCursor = dbConn.cursor()
    dbCursor.execute(Stations, (userInput,))#gets all the rows that have station_id and station_name and takes the user input for the like ?
    rows = dbCursor.fetchall()# gets all rows 
    if rows:
        for row in rows:
            station_id, station_name = row #seperates the row into two variables
            print(f"{station_id} : {station_name}") #uses f string to print out the station ID and station Station Name
    else:
        print("**No stations found...")



def command2(dbConn):#function that prints the ridership of all stations on weekends, weekdays, and holidays
    userInput = input("Enter the exact station name: ") #Takes user input
    Saturday = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ? AND Type_of_Day = 'A'"
    Weekday = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ? AND Type_of_Day = 'W'"
    SundayHoliday = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ? AND Type_of_Day = 'U'"
    total = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ?"
    dbCursor = dbConn.cursor()
    dbCursor.execute(Weekday, (userInput,))#Gets weekday count
    weekCount = dbCursor.fetchone()[0]
    if(weekCount):
        dbCursor.execute(Saturday, (userInput,))#gets saturday count
        satCount = dbCursor.fetchone()[0]
    
        if(satCount):
            dbCursor.execute(SundayHoliday, (userInput,))#gets sunday/Holiday count
            holidayCount = dbCursor.fetchone()[0]

        if(holidayCount):
            dbCursor.execute(total, (userInput,))#Gets weekday count
            totalRiders = dbCursor.fetchone()[0]

        if totalRiders > 0:#makes sure its greater then 0 so we dont divide by 0 
            percentage_weekday = (weekCount / totalRiders) * 100 #divides the counts to the total
            percentage_saturday = (satCount / totalRiders) * 100
            percentage_sunday_holiday = (holidayCount / totalRiders) * 100
            print(" Weekday ridership : ", f"{weekCount:,}", f"({percentage_weekday:.2f}%)") #prints all riderships and its percentage
            print(" Saturday ridership : ", f"{satCount:,}", f"({percentage_saturday:.2f}%)")
            print(" Sunday/Holiday ridership : ", f"{holidayCount:,}", f"({percentage_sunday_holiday:.2f}%)")
            print("Total ridership : ",f"{totalRiders:,}")
    
    else:
       print("**No data found...") 


def command3(dbConn):#function that prints out all stations count on the weekdays
    print("Ridership on Weekdays for Each Station")
    Stations = "SELECT Station_Name,SUM(Num_Riders) AS Sum FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Type_of_Day = 'W' GROUP BY Station_Name ORDER BY Sum DESC"
    Total = "SELECT SUM(Num_Riders) AS Sum FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Type_of_Day = 'W'"
    dbCursor = dbConn.cursor()
    dbCursor.execute(Stations)#gets info about stations
    results = dbCursor.fetchall()#gets the station names and riders
    dbCursor = dbConn.cursor()
    dbCursor.execute(Total)#gets total of all stations on weekends
    totalRiders = dbCursor.fetchone()[0]
    for station, stationRiders in results:#loops through every station and its count
        percentage = (stationRiders / totalRiders) * 100#gets the percentage of each station
        print(f"{station} : {stationRiders:,} ({percentage:.2f}%)")#prints the station and percentage

def command4(dbConn): #function that prints out all stops on a certain direction on a certain line
    userInput = input("Enter a line color (e.g. Red or Yellow): ").lower()#takes user input and makes it case insensitve
    colors = "SELECT Color FROM Lines WHERE LOWER(Color) = ?"#gets color from database and lowercases it for case insensitve
    dbCursor = dbConn.cursor()
    dbCursor.execute(colors, (userInput,))#gets the colors
    getColors = dbCursor.fetchone()

    if getColors:#if theres colors that exists
        direction = input("Enter the direction (N/S/E/W): ").lower()#lowers the input for direction and takes user input
        directions = "SELECT Stop_Name FROM Lines INNER JOIN StopDetails ON Lines.Line_ID = StopDetails.Line_ID INNER JOIN Stops ON Stops.Stop_ID=StopDetails.Stop_ID  WHERE LOWER(Color) = ? AND LOWER(Direction) = ? ORDER BY Stop_Name ASC"
        dbCursor.execute(directions, (userInput, direction))#gets directions of the lines
        allDirections = dbCursor.fetchone()

        if  allDirections:#makes sure directions exists
                    stops = "SELECT Stop_Name,ADA FROM Lines INNER JOIN StopDetails ON Lines.Line_ID = StopDetails.Line_ID INNER JOIN Stops ON Stops.Stop_ID=StopDetails.Stop_ID  WHERE LOWER(Color) = ? AND LOWER(Direction) = ? ORDER BY Stop_Name ASC"
                    dbCursor.execute(stops, (userInput, direction))#gets stops
                    stops = dbCursor.fetchall()

                    if stops:#makes sure there is stops
                        for stop in stops:#traverses through the tuple
                            stopName, accessible = stop#gets the stop name and handicap accessible for the stops
                            if accessible == 1: #checks to see if its handicap accessible
                                handicap = "handicap accessible" 

                            else:#prints not handicap accessible otherwise
                                 "not handicap accessible"
                            
                            print(f"{stopName} : direction = {direction.upper()} ({handicap})")#prints out the stops and its accessiblility

        else:#else line doesnt travel in the direction
            print("**That line does not run in the direction chosen...")
            return

    else:#prints when line doenst exists
        print("**No such line...")
        return

def command5(dbConn):
    lineColors = "SELECT Color, Direction, COUNT(Direction) FROM Lines INNER JOIN StopDetails ON Lines.Line_ID = StopDetails.Line_ID INNER JOIN Stops ON Stops.Stop_ID=StopDetails.Stop_ID GROUP BY Direction,Color ORDER BY Color,Direction ASC"
    totalLineStops = "SELECT COUNT(Stops.Stop_ID) FROM Stops"#gets total number of stops between the lines
    dbCursor = dbConn.cursor()
    dbCursor.execute(lineColors)#gets all colors and directions
    lineColors = dbCursor.fetchall()#gets the rows
    if lineColors:#checks if theres any lines
        dbCursor.execute(totalLineStops)
        totalLineStops = dbCursor.fetchone()
        if totalLineStops:#checks theres a total
            total = totalLineStops[0]#gets the total
            print("Number of Stops For Each Color By Direction")
            for line, direction,numStops in lineColors:#iterates through data
                percentage = (numStops / total) * 100#gets the percentage
                print(f"{line} going {direction} : {numStops} ({percentage:.2f}%)")#prints the expeceted output


       
def command6(dbConn):
    userInput = input("Enter partial station name (wildcards _ and %): ")
    Stations = "SELECT strftime('%Y', Ride_Date) AS YEAR,SUM(Num_Riders) FROM Stations INNER JOIN Ridership ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name LIKE ? GROUP BY YEAR ORDER BY YEAR ASC"
    count = "SELECT COUNT(Station_Name) FROM Stations WHERE Station_Name LIKE ?"
    station = "SELECT Station_Name FROM Stations WHERE Station_Name LIKE ?"
    dbCursor = dbConn.cursor()
    dbCursor.execute(Stations, (userInput,))
    rows = dbCursor.fetchall()# gets all rows 
    
    dbCursor.execute(count, (userInput,))#gets amount of train stations with name user input
    stationCount = dbCursor.fetchone()#gets all rows
    mutipleStations = stationCount
    if rows:#checks theres only one station
        if(mutipleStations[0]>1):#checks to make sure we only found one station
            print("**Multiple stations found...")#prints error message
            return
        
        else:
            dbCursor.execute(station, (userInput,))#gets name of station
            rows2 = dbCursor.fetchall()# gets all rows 
            stationName = rows2[0];
            allYears = []
            numRider = []
            for row in rows:#else prints the year and its ridership
                year, numRiders = row #seperates the row into year and the number of riders
                allYears.append(year)
                numRider.append(numRiders)
                print(f"{year} : {numRiders:,}") #prints the year and riders

        plotInput = input("Plot? (y/n) ")
        if(plotInput == 'y'):
            plt.title("Yearly Ridership at " + stationName[0])
            xpoints = allYears
            ypoints = numRider
            plt.figure(figsize=(12,7))
            plt.xlabel("Year")
            plt.ylabel("Number of Riders")
            plt.plot(xpoints, ypoints)
            plt.savefig('command6.png')
            plt.pause(0.001)

            #############FIX THE Y AXIS
    
        else:
            return


    else:#else if prints no stations where found with that name
        print("**No stations found...")
        return

def command7(dbConn):
    userStation = input("Enter partial station name (wildcards _ and %): ")#gets user input for station
    count = "SELECT COUNT(Station_Name) FROM Stations WHERE Station_Name LIKE ?"
    Stations = "SELECT Station_Name FROM Stations WHERE Station_Name LIKE ?"
    fullSearch = "SELECT strftime('%m/%Y', Ride_Date)AS date ,SUM(Num_Riders) FROM Stations INNER JOIN Ridership ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name LIKE ? AND strftime('%Y',Ride_Date) LIKE ? GROUP BY date ORDER BY date ASC"
    
    dbCursor = dbConn.cursor()
    dbCursor.execute(Stations, (userStation,))#gets train stations with name user input
    rows = dbCursor.fetchall()# gets all rows 
    if rows:
        dbCursor.execute(count, (userStation,))#gets amount of train stations with name user input
        stationCount = dbCursor.fetchone()#gets all rows
        mutipleStations = stationCount
         
        if(mutipleStations[0]>1):#checks to make sure we only found one station
            print("**Multiple stations found...")#prints error message
            return
        
        else:
            station = rows[0];
            userYear = input("Enter a year: ")
            dbCursor.execute(fullSearch, (userStation, userYear))#gets amount of train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            month = []
            ridership = [] 
            print("Monthly Ridership at " + station[0] + " for " + userYear);
            for row in rows:
                months, numRiders = row #seperates the row into month and the number of riders
                print(f"{months} : {numRiders:,}") #prints the month and number of riders
                month.append(months)
                ridership.append(numRiders)

            plotInput = input("Plot? (y/n) ")
            stationName = rows[0]
            if(plotInput == 'y'):
                xpoints = month
                ypoints = ridership
                # plt.figure(figsize=(12,7))
                # plt.xlabel("Month")
                # plt.ylabel("Number of Riders")
                # plt.title("Monthly Ridership at " + stationName[0])
                # plt.plot(xpoints, ypoints)
                # # plt.savefig('command7.png')
                # plt.pause(0.001)
                #FIX LATER

    else:
        print("**No stations found...")
        return

    
def command8():
    print("placeholder")

def command9():
    print("placeholder")
##################################################################  
#
# main
#
print('** Welcome to CTA L analysis app **')
print()
dbConn = sqlite3.connect('CTA2_L_daily_ridership.db')
print_stats(dbConn)
notDone = False
command = input("Please enter a command (1-9, x to exit):");
while(notDone != True or command != "x"):#keeps going till user exits
    if(command== "x" or command == "1" or command == "2" or command == "3" or command == "4" or command == "5" or command == "6" or command == "7" or command == "8" or command == "9"):
        if(command == "1"):#handles what command user wants to run
            command1(dbConn)
            command = input("Please enter a command (1-9, x to exit):");

        elif(command == "2"):
            command2(dbConn)
            command = input("Please enter a command (1-9, x to exit):");

        elif(command == "3"):
            command3(dbConn)
            command = input("Please enter a command (1-9, x to exit):");


        elif(command == "4"):
            command4(dbConn)
            command = input("Please enter a command (1-9, x to exit):");

        elif(command == "5"):
            command5(dbConn)
            command = input("Please enter a command (1-9, x to exit):");
            
        elif(command == "6"):
            command6(dbConn)
            command = input("Please enter a command (1-9, x to exit):");

        elif(command == "7"):
            command7(dbConn)
            command = input("Please enter a command (1-9, x to exit):");

        elif(command == "8"):
            command8()
            break;

        elif(command == "9"):
            command9()
            break;
        
        elif(command == "x"):
            break
    
    else:
        print(" **Error, unknown command, try again...")
        command = input("Please enter a command (1-9, x to exit): ");



