#
# objecttier
#
# Builds Lobbyist-related objects from data retrieved through 
# the data tier.
#
# Original author: Ellen Kidane
#
import datatier
##################################################################
#
# Lobbyist:
#
# Constructor(...)
# Properties:
#   Lobbyist_ID: int
#   First_Name: string
#   Last_Name: string
#   Phone: string
#
class Lobbyist:
    def __init__(self,id,first,last,phone):#Creates constructor for lobbyist
        self._Lobbyist_ID = id#sets values from constructor into class
        self._First_Name = first
        self._Last_Name = last
        self._Phone = phone

    @property
    def Lobbyist_ID(self):#gets lobby ID
        return self._Lobbyist_ID

    @property 
    def First_Name(self):#gets first name
        return self._First_Name

    @property 
    def Last_Name(self):#gets last name
        return self._Last_Name
    
    @property 
    def Phone(self):#gets phone number
        return self._Phone

##################################################################
#
# LobbyistDetails:
#
# Constructor(...)
# Properties:
#   Lobbyist_ID: int
#   Salutation: string
#   First_Name: string
#   Middle_Initial: string
#   Last_Name: string
#   Suffix: string
#   Address_1: string
#   Address_2: string
#   City: string
#   State_Initial: string
#   Zip_Code: string
#   Country: string
#   Email: string
#   Phone: string
#   Fax: string
#   Years_Registered: list of years
#   Employers: list of employer names
#   Total_Compensation: float
#
class LobbyistDetails:
    def __init__(self,IDs,Salutations,First,Middle,Last,suffix,address_1,address_2,city,state,zip,country,email,phone,fax,years,employer,Compensation):#defines constructor for lobbyist details
        self._Lobbyist_ID = IDs #sets values from constructor into class
        self._Salutation = Salutations
        self._First_Name = First
        self._Middle_Initial = Middle
        self._Last_Name = Last
        self._Suffix = suffix
        self._Address_1 = address_1
        self._Address_2 = address_2
        self._City = city
        self._State_Initial = state
        self._Zip_Code = zip
        self._Country = country
        self._Email = email
        self._Phone = phone
        self._Fax = fax
        self._Years_Registered = years
        self._Employers = employer
        self._Total_Compensation = Compensation

    @property
    def Lobbyist_ID(self):#gets lobby ID
        return self._Lobbyist_ID

    @property
    def Salutation(self):#gets salutation
        return self._Salutation
    
    @property
    def First_Name(self):#gets first name
        return self._First_Name
    
    @property
    def Middle_Initial(self):#gets middle initial
        return self._Middle_Initial

    @property
    def Last_Name(self):#gets last name
        return self._Last_Name
    
    @property
    def Suffix(self):#gets suffix
        return self._Suffix
    
    @property
    def Address_1(self):#gets address 1
        return self._Address_1

    @property
    def Address_2(self):#gets address 2
        return self._Address_2
    
    @property
    def City(self):#gets city
        return self._City
    
    @property
    def State_Initial(self):#gets state
        return self._State_Initial

    @property
    def Zip_Code(self):#gets zip code
        return self._Zip_Code

    @property
    def Country(self):#gets country
        return self._Country

    @property
    def Email(self):#gets email
        return self._Email

    @property
    def Phone(self):#gets phone
        return self._Phone

    @property
    def Fax(self):#gets fax
        return self._Fax

    @property
    def Years_Registered(self):#gets years
        return self._Years_Registered

    @property
    def Employers(self):#gets employers
        return self._Employers

    @property
    def Total_Compensation(self):#gets compensation
        return self._Total_Compensation

##################################################################
#
# LobbyistClients:
#
# Constructor(...)
# Properties:
#   Lobbyist_ID: int
#   First_Name: string
#   Last_Name: string
#   Phone: string
#   Total_Compensation: float
#   Clients: list of clients
#
class LobbyistClients:
    def __init__(self,id,first,last,phone,compensation,clients):#Creates constructor for lobby clients
        self._Lobbyist_ID = id#sets values from constructor into class
        self._First_Name = first
        self._Last_Name = last
        self._Phone = phone
        self._Total_Compensation = compensation
        self._Clients = clients

    @property
    def Lobbyist_ID(self):#gets lobby ID
        return self._Lobbyist_ID

    @property 
    def First_Name(self):#gets first name
        return self._First_Name

    @property 
    def Last_Name(self):#gets last name
        return self._Last_Name
    
    @property 
    def Phone(self):#gets phone number
        return self._Phone

    @property 
    def Total_Compensation(self):#gets total compensation
        return self._Total_Compensation

    @property 
    def Clients(self):#gets total number of clients
        return self._Clients

##################################################################
# 
# num_lobbyists:
#
# Returns: number of lobbyists in the database
#           If an error occurs, the function returns -1
#
def num_lobbyists(dbConn):
   try:
    sql = "SELECT COUNT(Lobbyist_ID) FROM LobbyistInfo"#gets count of lobbbyists
    results = datatier.select_one_row(dbConn,sql,None)#gets the results
    return results[0]#returns the number of lobbyists

   except Exception as err:#handles exceptions
        print("num_lobbyists failed:", err)
        return -1

##################################################################
# 
# num_employers:
#
# Returns: number of employers in the database
#           If an error occurs, the function returns -1
#
def num_employers(dbConn):
    try:
        sql = "SELECT COUNT(Employer_ID) FROM EmployerInfo"#gets number of Employers
        results = datatier.select_one_row(dbConn,sql,None)#gets results from sql
        return results[0]#returns number of emplyers
    except Exception as err:#handles exceptions
        print("num_employers failed:", err)
        return -1

##################################################################
# 
# num_clients:
#
# Returns: number of clients in the database
#           If an error occurs, the function returns -1
#
def num_clients(dbConn):
    try:
        sql = "SELECT COUNT(Client_ID) FROM ClientInfo"#gets number of Employers
        results = datatier.select_one_row(dbConn,sql,None)#gets results from sql
        return results[0]#returns number of emplyers
    except Exception as err:#handles exceptions
        print("num_clients failed:", err)
        return -1

##################################################################
#
# get_lobbyists:
#
# gets and returns all lobbyists whose first or last name are "like"
# the pattern. Patterns are based on SQL, which allow the _ and % 
# wildcards.
#
# Returns: list of lobbyists in ascending order by ID; 
#          an empty list means the query did not retrieve
#          any data (or an internal error occurred, in
#          which case an error msg is already output).
#
def get_lobbyists(dbConn, pattern):
    try:
        sql = "SELECT Lobbyist_ID, First_Name , Last_Name,Phone FROM LobbyistInfo WHERE First_Name LIKE ? OR Last_Name LIKE ? ORDER BY Lobbyist_ID ASC"#gets number of Employers
        results = datatier.select_n_rows(dbConn,sql,[pattern,pattern])#gets last names and first name with pattern
        listOfLobby = []
        if results:
            for rows in results:#iterates through the list
              Lobbyist_ID,First_Name,Last_Name,Phone = rows#seperates into variables
              lobbyObject = Lobbyist(Lobbyist_ID,First_Name,Last_Name,Phone)#creates class object 
              listOfLobby.append(lobbyObject)#adds object to list
            return listOfLobby#returns list
        else:
            return []
    except Exception as err:#handles exceptions
        print("get_lobbyists failed:", err)
        return []

##################################################################
#
# get_lobbyist_details:
#
# gets and returns details about the given lobbyist
# the lobbyist id is passed as a parameter
#
# Returns: if the search was successful, a LobbyistDetails object
#          is returned. If the search did not find a matching
#          lobbyist, None is returned; note that None is also 
#          returned if an internal error occurred (in which
#          case an error msg is already output).
#
def get_lobbyist_details(dbConn, lobbyist_id):
    try:
        lobbySql = "SELECT Lobbyist_ID,Salutation, First_Name,Middle_Initial, Last_Name, Suffix, Address_1,Address_2,City,State_Initial,ZipCode,Country,Email,Phone,Fax FROM LobbyistInfo WHERE Lobbyist_ID LIKE ?"
        yearSql = "SELECT Year FROM LobbyistYears WHERE Lobbyist_ID LIKE ? ORDER BY Year"
        employerSQl = "SELECT DISTINCT Employer_Name FROM LobbyistAndEmployer INNER JOIN EmployerInfo ON EmployerInfo.Employer_ID = LobbyistAndEmployer.Employer_ID WHERE Lobbyist_ID LIKE ? ORDER BY Employer_Name ASC"
        compSql = "SELECT SUM(Compensation_Amount) FROM Compensation WHERE Lobbyist_ID LIKE ?"
        results4 = datatier.select_one_row(dbConn,compSql,[lobbyist_id])#gets compensation details
        results3 = datatier.select_n_rows(dbConn,employerSQl,[lobbyist_id])#gets employers details
        results2 = datatier.select_n_rows(dbConn,yearSql,[lobbyist_id])#gets year details
        results = datatier.select_n_rows(dbConn,lobbySql,[lobbyist_id])#gets lobby details
        yearList = []
        employerList = []
        
        if results2:
            for rows in results2:
                yearList.append(rows[0])

        if results3:
            for rows in results3:
                employerList.append(rows[0])
                
        if results:#checks if any rows are found
            if results4[0] is None:
                Total_Compensation = 0.0
            else:
                Total_Compensation = results4[0]
            
            for row in results:#iterates through the data
                IDs,Salutation, First_Name,Middle_Initial, Last_Name, Suffix, Address_1,Address_2,City,State_Initial,ZipCode,Country,Email,Phone,Fax = row#splits information into variables
                lobbyObject = LobbyistDetails(IDs,Salutation,First_Name,Middle_Initial,Last_Name,Suffix,Address_1,Address_2,City,State_Initial,ZipCode,Country,Email,Phone,Fax,yearList,employerList,Total_Compensation)#stores lobby details into an object
            return lobbyObject#returns lobby object

        else:
            return None

    except Exception as err:#handles exceptions
        print("get_lobbyist_details failed:", err)
        return None

##################################################################
#
# get_top_N_lobbyists:
#
# gets and returns the top N lobbyists based on their total 
# compensation, given a particular year
#
# Returns: returns a list of 0 or more LobbyistClients objects;
#          the list could be empty if the year is invalid. 
#          An empty list is also returned if an internal error 
#          occurs (in which case an error msg is already output).
#
def get_top_N_lobbyists(dbConn, N, year):
    try:
        lobbysql = """SELECT LobbyistInfo.Lobbyist_ID,First_Name,Last_Name,Phone,SUM(Compensation_Amount) AS TOTAL FROM LobbyistInfo 
        INNER JOIN Compensation ON  LobbyistInfo.Lobbyist_ID = Compensation.Lobbyist_ID
        INNER JOIN ClientInfo ON ClientInfo.Client_ID = Compensation.Client_ID
        WHERE strftime("%Y", Period_Start) = ? OR strftime("%Y", Period_End) = ?
        GROUP BY Compensation.Lobbyist_ID
        ORDER BY TOTAL DESC
        LIMIT ?
        """#gets lobbyist info and compensation

        clientSql = """SELECT Client_Name FROM Compensation
        INNER JOIN ClientInfo ON ClientInfo.Client_ID = Compensation.Client_ID
        WHERE Compensation.Lobbyist_ID = ? AND (strftime('%Y', Period_Start) = ? OR strftime('%Y', Period_End) = ?)
        GROUP BY ClientInfo.Client_ID
        ORDER BY Client_Name ASC
        """#gets the clients 

        objectList = []#stores all objects 
        results = datatier.select_n_rows(dbConn,lobbysql,[str(year),str(year),str(N)])#gets the lobby info        
        if results:#checks for results
            for row in results:
                listOfClients = []#creates list to store clients
                Lobbyist_ID,First_Name, Last_Name,Phone,Total_Compensation = row#sepertates info into variables
                if Total_Compensation is None:
                    Total_Compensation = 0.0

                results2 = datatier.select_n_rows(dbConn,clientSql,[Lobbyist_ID,str(year),str(year)])#runs sql to get clients
                for rows in results2:#iterates through clients
                    listOfClients.append(rows[0])#stores into list
                LobbyClientObject = LobbyistClients(Lobbyist_ID,First_Name,Last_Name,Phone,Total_Compensation,listOfClients)#creates LobbyistClients object
                objectList.append(LobbyClientObject)#adds class object to list of class objects
            return objectList
        else:#if nothing is found return empty list
            return []

    except Exception as err:#handles errors
        print("get_top_N_lobbyists failed:", err)
        return []
 
##################################################################
#
# add_lobbyist_year:
#
# Inserts the given year into the database for the given lobbyist.
# It is considered an error if the lobbyist does not exist (see below), 
# and the year is not inserted.
#
# Returns: 1 if the year was successfully added, 
#          0 if not (e.g. if the lobbyist does not exist, or if
#          an internal error occurred).
#
def add_lobbyist_year(dbConn, lobbyist_id, year):
    try:
        sql = "INSERT INTO LobbyistYears (Lobbyist_ID, Year) VALUES (?, ?)" #inserts values into the function
        lobbySql = "SELECT Lobbyist_ID FROM LobbyistInfo WHERE Lobbyist_ID = ?"#gets count of lobbbyists
        results2 = datatier.select_one_row(dbConn,lobbySql,[str(lobbyist_id)])#checks to make sure the lobby exists
        if results2:
            results = datatier.perform_action(dbConn,sql,[lobbyist_id,year])#gets number of rows changed
            if results>0:
                return 1#lobbyists exists
            else:
                return 0#lobbyist doesnt exist
        else:
            return 0#lobby id not found
    
    except Exception as err:#handles exceptions
        print("add_lobbyist_year failed:", err)
        return 0


##################################################################
#
# set_salutation:
#
# Sets the salutation for the given lobbyist.
# If the lobbyist already has a salutation, it will be replaced by
# this new value. Passing a salutation of "" effectively 
# deletes the existing salutation. It is considered an error
# if the lobbyist does not exist (see below), and the salutation
# is not set.
#
# Returns: 1 if the salutation was successfully set,
#          0 if not (e.g. if the lobbyist does not exist, or if
#          an internal error occurred).
#
def set_salutation(dbConn, lobbyist_id, salutation):
    try: 
        lobbySql = "SELECT Lobbyist_ID FROM LobbyistInfo WHERE Lobbyist_ID = ?"#gets count of lobbbyists
        sql = "UPDATE LobbyistInfo SET Salutation = ? WHERE Lobbyist_ID = ?"#updates salutation if it exists
        results = datatier.select_one_row(dbConn,lobbySql,[str(lobbyist_id)])#checks to make sure the lobby exists
        if results:
            rowsChanged = datatier.perform_action(dbConn,sql,[salutation,lobbyist_id])#gets number of rows changed
            return 1#lobbyist changed
        else:#no lobbyist found
            return 0

    except Exception as err:#handles exceptions
        print("set_salutation failed:", err)
        return 0