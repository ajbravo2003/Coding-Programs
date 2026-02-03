#/**------------------------------------------
#     Project: CTA Database App
#     System: Codio IDE 2025
#     Author: Alejandro Bravo
#  ---------------------------------------------**/
import sqlite3
import matplotlib.pyplot as plt
import numpy as np
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


def command1(dbConn):#Prints station name and unique ID
    print()
    userInput = input("Enter partial station name (wildcards _ and %): ")
    Stations = "SELECT Station_ID, Station_Name FROM Stations WHERE Station_Name LIKE? ORDER BY Station_Name ASC"
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
    print()
    userInput = input("Enter the name of the station you would like to analyze: ") #Takes user input
    stationName = "SELECT Station_Name FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ?"
    Saturday = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ? AND Type_of_Day = 'A'"
    Weekday = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ? AND Type_of_Day = 'W'"
    SundayHoliday = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ? AND Type_of_Day = 'U'"
    total = "SELECT SUM(Num_Riders) FROM Ridership INNER JOIN Stations ON Ridership.Station_ID = Stations.Station_ID WHERE Station_Name = ?"
    dbCursor = dbConn.cursor()
    dbCursor.execute(stationName, (userInput,))#Gets weekday count
    userStationName = dbCursor.fetchone()
    dbCursor.execute(Weekday, (userInput,))#Gets weekday count
    weekCount = dbCursor.fetchone()[0]
    if(weekCount):
        dbCursor.execute(Saturday, (userInput,))#gets saturday count
        satCount = dbCursor.fetchone()[0]
        dbCursor.execute(SundayHoliday, (userInput,))#gets sunday/Holiday count
        holidayCount = dbCursor.fetchone()[0]
        dbCursor.execute(total, (userInput,))#Gets weekday count
        totalRiders = dbCursor.fetchone()[0]
        percentage_weekday = (weekCount / totalRiders) * 100 #divides the counts to the total
        percentage_saturday = (satCount / totalRiders) * 100
        percentage_sunday_holiday = (holidayCount / totalRiders) * 100
        print(" Percentage of ridership for the "+ userStationName[0] + " station: ")
        print(" Weekday ridership:", f"{weekCount:,}", f"({percentage_weekday:.2f}%)") #prints all riderships and its percentage
        print(" Saturday ridership:", f"{satCount:,}", f"({percentage_saturday:.2f}%)")
        print(" Sunday/holiday ridership:", f"{holidayCount:,}", f"({percentage_sunday_holiday:.2f}%)")
        print(" Total ridership:",f"{totalRiders:,}")
    
    else:
       print("**No data found...") 
       print()


def command3(dbConn):#function that prints out all stations count on the weekdays
    print(" Ridership on Weekdays for Each Station")
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
    print()
    userInput = input("Enter a line color (e.g. Red or Yellow): ").lower()#takes user input and makes it case insensitve
    colors = "SELECT Color FROM Lines WHERE LOWER(Color) = ?"#gets color from database and lowercases it for case insensitve
    dbCursor = dbConn.cursor()
    dbCursor.execute(colors, (userInput,))#gets the colors
    getColors = dbCursor.fetchone()

    if getColors:#if theres colors that exists
        direction = input("Enter a direction (N/S/W/E): ").lower()#lowers the input for direction and takes user input
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
                                handicap = "not handicap accessible"
                            
                            print(f"{stopName} : direction = {direction.upper()} ({handicap})")#prints out the stops and its accessiblility

        else:#else line doesnt travel in the direction
            print("**That line does not run in the direction chosen...")
            return

    else:#prints when line doenst exists
        print("**No such line...")
        return

def command5(dbConn):#function that gets sum of lines going in a direction 
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
            print(" Number of Stops For Each Color By Direction")
            for line, direction,numStops in lineColors:#iterates through data
                percentage = (numStops / total) * 100#gets the percentage
                print(f"{line} going {direction} : {numStops} ({percentage:.2f}%)")#prints the expeceted output


       
def command6(dbConn):#function that displays total ridership per year of a certain station
    print()
    userInput = input("Enter a station name (wildcards _ and %): ")
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
            print("Yearly Ridership at " + stationName[0])
            for row in rows:#else prints the year and its ridership
                year, numRiders = row #seperates the row into year and the number of riders
                allYears.append(year)
                numRider.append(numRiders)
                print(f"{year} : {numRiders:,}") #prints the year and riders

        plotInput = input("Plot? (y/n) \n")
        if(plotInput == 'y'):
            plt.figure(figsize=(12, 6)) 
            plt.title("Yearly Ridership at " + stationName[0])#title
            xpoints = allYears#sets x and y values
            ypoints = numRider
            plt.plot(xpoints, ypoints)#plots them
            plt.xlabel('Year')#sets labels
            plt.ylabel('Number of Riders')
            plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))#formats
            plt.show()
        
        else:
            return


    else:#else if prints no stations where found with that name
        print("**No station found...")
        return

def command7(dbConn):#function that displays monthly ridership of station in a year
    print()
    userStation = input("Enter a station name (wildcards _ and %): ")#gets user input for station
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
            month = ["01","02","03","04","05","06","07","08","09","10","11","12"]
            ridership = [] 
            print("Monthly Ridership at " + station[0] + " for " + userYear);
            for row in rows:
                months, numRiders = row #seperates the row into month and the number of riders
                print(f"{months} : {numRiders:,}") #prints the month and number of riders
                ridership.append(numRiders)
            print()
            plotInput = input("Plot? (y/n) \n")
            if(plotInput == 'y'):
                xpoints = month#sets plot axis
                ypoints = ridership
                plt.figure(figsize=(10, 6))#increases size
                plt.plot(xpoints, ypoints)#plots the graph
                plt.xlabel('Month')#sets the labels and title
                plt.ylabel('Number of Riders')
                plt.title('Monthly Ridership at ' + station[0] + " (" + userYear + ")" )
                plt.show()#display graph
            else:
                return
                

    else:
        print("**No station found...")
        return

    
def command8(dbConn):#function to compare ridership of two stations each day in a certain year
    print()
    userYear = input("Year to compare against? ")#takes year of user
    print()
    userStation1 = input("Enter station 1 (wildcards _ and %): ")
    checkStations = "SELECT Station_Name FROM Stations  WHERE Station_Name LIKE ?"
    dbCursor = dbConn.cursor()
    dbCursor.execute(checkStations, (userStation1,))#gets train stations with name user input
    mutipleStations = dbCursor.fetchall()# gets all rows 
    if mutipleStations:
        if(len(mutipleStations)>1):#checks to make sure we only found one station
            print("**Multiple stations found...")#prints error message
            return
        print()
        userStation2 = input("Enter station 2 (wildcards _ and %): ")#takes the first station
        dbCursor.execute(checkStations, (userStation2,))#gets train stations with name user input
        mutipleStations2 = dbCursor.fetchall()# gets all rows 
        if(len(mutipleStations2)>1):#checks to make sure we only found one station
            print("**Multiple stations found...")#prints error message
            return

        if mutipleStations2: 
            Station1Top5 = "SELECT strftime('%Y-%m-%d', Ride_Date)AS date,Num_Riders FROM Stations INNER JOIN Ridership ON Ridership.Station_ID = Stations.Station_ID WHERE strftime('%Y', Ride_Date) = ? AND Station_Name LIKE ?  ORDER BY strftime('%m%d', Ride_Date) ASC LIMIT 5"
            Station1Bottom5 = "SELECT strftime('%Y-%m-%d', Ride_Date)AS date,Num_Riders FROM Stations INNER JOIN Ridership ON Ridership.Station_ID = Stations.Station_ID WHERE strftime('%Y', Ride_Date) = ? AND Station_Name LIKE ? ORDER BY strftime('%m%d', Ride_Date) DESC LIMIT 5"
            Station1Title = "SELECT Station_ID, Station_Name FROM Stations WHERE Station_Name LIKE ?"
            dbCursor.execute(Station1Title, (userStation1,))#gets train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            station1ID, station1Name = rows[0]
            dbCursor.execute(Station1Top5, (userYear,userStation1))#gets train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            station1Riders = []
            Station1Dates = []
            station2Riders = []
            Station2Dates = []
            print("Station 1: " + str(station1ID) + " " + station1Name)
            for row in rows:
                date, numRiders = row #seperates the row into date and the number of riders
                print(f"{date} {numRiders}") #prints the date and riders
                station1Riders.append(numRiders)
                Station1Dates.append(date)
            dbCursor.execute(Station1Bottom5, (userYear,userStation1))#gets train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            rows.reverse()#reverses the list
            for row in rows:
                date, numRiders = row #seperates the row into date and the number of riders
                print(f"{date} {numRiders}") #prints the date and riders
                station1Riders.append(numRiders)
                Station1Dates.append(date)
            Station2Top5 = "SELECT strftime('%Y-%m-%d', Ride_Date)AS date,Num_Riders FROM Stations INNER JOIN Ridership ON Ridership.Station_ID = Stations.Station_ID WHERE strftime('%Y', Ride_Date) = ? AND Station_Name LIKE ?  ORDER BY strftime('%m%d', Ride_Date) ASC LIMIT 5"
            Station2Bottom5 = "SELECT strftime('%Y-%m-%d', Ride_Date)AS date,Num_Riders FROM Stations INNER JOIN Ridership ON Ridership.Station_ID = Stations.Station_ID WHERE strftime('%Y', Ride_Date) = ? AND Station_Name LIKE ? ORDER BY strftime('%m%d', Ride_Date) DESC LIMIT 5"
            Station2Title = "SELECT Station_ID, Station_Name FROM Stations WHERE Station_Name LIKE ?"
            dbCursor.execute(Station2Title, (userStation2,))#gets train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            station2ID, station2Name = rows[0]
            dbCursor.execute(Station2Top5, (userYear,userStation2))#gets train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            print("Station 2: " + str(station2ID) + " " + station2Name)
            for row in rows:
                date, numRiders = row #seperates the row into date and the number of riders
                print(f"{date} {numRiders}") #prints the date and riders
                station2Riders.append(numRiders)
                Station2Dates.append(date)
            dbCursor.execute(Station2Bottom5, (userYear,userStation2))#gets train stations with name user input
            rows = dbCursor.fetchall()# gets all rows
            rows.reverse() #reverses the list
            for row in rows:
                date, numRiders = row #seperates the row into date and the number of riders
                print(f"{date} {numRiders}") #prints the date and riders
                station2Riders.append(numRiders)#adds to the arrays
                Station2Dates.append(date)
            print()
            plotInput = input("Plot? (y/n) \n")
            if(plotInput == 'y'):
                if(station1Riders!=0 or station2Riders !=0):
                    xvalues = np.linspace(0, 350)
                    maxRiders = max(max(station1Riders), max(station2Riders))#gets max of values
                    linespace = np.interp(xvalues, np.linspace(0, 350, len(station1Riders)), station1Riders)
                    linespace2 = np.interp(xvalues, np.linspace(0, 350, len(station2Riders)), station2Riders)
                    plt.plot(xvalues, linespace, label=f"{station1Name}%", color='blue', linestyle='-', linewidth=2)
                    plt.plot(xvalues, linespace2, label=f"{station2Name}%", color='orange', linestyle='-', linewidth=2)
                    plt.xlim(0, 365)#sets parameters of the graph
                    plt.ylim(0, maxRiders+4000)
                    plt.xlabel('Days')#sets labes of x axis
                    plt.ylabel('Ridership')#sets labels of y axis
                    plt.title(f'Ridership Each Day of {userYear}') #displays title
                    plt.legend()#displays what stations is what line
                    plt.show()
                else:
                    plt.plot()
                    plt.show()
        else:
            print("**No station found...")
            return
    else:
        print("**No station found...")
        return
    

def command9(dbConn):#function that finds CTA stations within approxiamtely a mile of longitude and latitude coordinates
    print()
    dbCursor = dbConn.cursor()
    latitude= input("Enter a latitude: ")#asks for user latitude
    if(float(latitude) >=40 and float(latitude) <=43 ):
        longitude= input("Enter a longitude: ")#asks for user longitude
        if(float(longitude) <= -87 and float(longitude) >=-88):
            latitudeDivider = 1 / 69.0 #gets formula for latitude
            longitudeDivider = 1 / 51.0  #gets formula for longitude
            longitudeMin = round(float(longitude) - longitudeDivider, 3) #subtracts longitude by divider to get 1 mile west
            longitudeMax = round(float(longitude) + longitudeDivider, 3) #adds longitude by divider to get 1 mile east
            latitudeMin = round(float(latitude) - latitudeDivider, 3)#adds latitude by divider to get 1 mile south
            latitudeMax = round(float(latitude) + latitudeDivider, 3)#adds latitude by divider to get 1 mile north

            stationsWithLongAndLat = "SELECT DISTINCT Station_Name,Longitude, Latitude FROM Stops INNER JOIN Stations ON Stations.Station_ID = Stops.Station_ID WHERE Latitude BETWEEN ? AND ? AND Longitude BETWEEN ? AND ? ORDER BY Station_Name,longitude DESC,latitude ASC"
            dbCursor.execute(stationsWithLongAndLat, (latitudeMin, latitudeMax, longitudeMin, longitudeMax))#gets stations within a mile radius
            rows = dbCursor.fetchall()#gets rows            
            x = []
            y = []
            if rows:
                print()
                print("List of Stations Within a Mile")
                for row in rows:#gets rows
                    stationName, latitude,longitude = row #seperates the row into the station name and coordinates
                    print(f"{stationName} : ({longitude}, {latitude})") #prints stations within the radius
                    x.append(latitude)#adds to arrays to plot
                    y.append(longitude)
            else:
                print("**No stations found...")
                return

        else:
            print("**Longitude entered is out of bounds...")
            return
        plotInput = input("Plot? (y/n) \n")
        if(plotInput == 'y'):#asks to plot 
            image = plt.imread("chicago.png")
            xydims = [-87.9277, -87.5569, 41.7012, 42.0868]
            plt.imshow(image, extent=xydims)
            plt.title("Stations Near You")#sets title
            for row in rows:
                stationName, latitude, longitude = row#seperates tuple into 3 variables
                plt.annotate(stationName, (latitude, longitude),fontsize= 7)#annotates on image
            plt.scatter(x, y, color='blue', marker='o', label='Stations')#plots blue points
            plt.xlim([-87.9277, -87.5569])#sets boundaries
            plt.ylim([41.7012, 42.0868])
            plt.show()#shows plot
        else:
            plt.plot()
            plt.show()
            return


    else:
        print("**Latitude entered is out of bounds...")
        return

    
    
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

        elif(command == "2"):#handles command 2
            command2(dbConn)
            command = input("Please enter a command (1-9, x to exit):");

        elif(command == "3"):#handles command 3
            command3(dbConn)
            command = input("Please enter a command (1-9, x to exit):");


        elif(command == "4"):#handles command 4
            command4(dbConn)
            command = input("Please enter a command (1-9, x to exit): ");

        elif(command == "5"):#handles command 5
            command5(dbConn)
            command = input("Please enter a command (1-9, x to exit):");
            
        elif(command == "6"):#handles command 6
            command6(dbConn)
            command = input("Please enter a command (1-9, x to exit): ");

        elif(command == "7"):#handles command 7
            command7(dbConn)
            command = input("Please enter a command (1-9, x to exit): ");

        elif(command == "8"):#handles command 8
            command8(dbConn)
            command = input("Please enter a command (1-9, x to exit): ");

        elif(command == "9"):#handles command 9
            command9(dbConn)
            command = input("Please enter a command (1-9, x to exit): ");
        
        elif(command == "x"):#handles exit
            break
    
    else:#handles wrong error
        print(" **Error, unknown command, try again...")
        command = input("Please enter a command (1-9, x to exit): ");