/*                  SWE20004 - Team Project B
*                   Semester 2, 2021
* 
* File:             project.cpp (should be renamed, can do later)
* 
* Aurthors:         Kozminska, Jamie - 101114436
*                   Woodrow, Michael - 6798527
* 
* Created:          05/10/21
* 
* Last Modified:    12/10/2021
* 
* 
* 
*   (MW - 12/10/21)
*   A lot of good work here, but also a number of issues that I just don't have time to work on with the time I have left today (unfortunatly I need sleep)
*   I will make a bigger effort on adding code tomorrow, just needed to take time today to make sure the fondations are correct and everything is set up correctly so there wont be issues.
*       -> For example, there are a number of things that will need to be re-written to work as expected
*
*   IN REGARDS TO THE DATABASES:
*       - It says we need a primary DB, but I think 3 seperate DBs makes more sense
*       - Symptoms should be formatted to just have three lines, each line is a risk level
*           -> can add something at the start of the line to indicate this if needed, but remember we just need to read out the description and let the user select
*               (maybe ask line by line and each time the user replies yes/no and if they reply yes at high risk then its locked in?)
*       - Locations really just needs locations at each line
*           -> Duplicates might be an issue, but its low priority to address atm and not really a major issue
*       - Patients should be one ID per line and each detail (name, address, etc) seperated by a character (comma?) so we can format it in and out of the DB
*           -> When there is an update, the line can just be overwritten with new data.
*
*   FOR THE REST OF THE PROGRAM:
*       - You can read my block comments. Hopefully they are clear-ish.
*           -> I'll be doing a fair amount of work on this so just keep me upto date if you are working on something and I'll try and do the same
*
*/



#include <iostream> 
#include <fstream> 
#include <string>
#include <vector> // - MW
#include <sstream> // - MW
#include <ctime> // Required for date/time format - MW
#include <algorithm> //Required for string normalisation
#include <cctype> //Required for string normalisation

using namespace std;

const int MAX_YEAR = 2021; // Manually update each year

/*
* (MW - 12/10/21)
* Best not make globals like this as it is hard to keep track of / not good practice anyways
* - Might need some pointers for current user, etc as globals so I'll keep things posted.
* 
*/

//int patientID;
//string fname;
//string lname;
//int doB;
//string address;
//string visitedLocation;
//int date;
//string overseasTravel;
//string covidTest;
//string status;
//
//fstream myfile; 


/**
* For debugging
* @param none
* @returns nothing
* 
* (JK - 5/10/21)
* I was unsure how we should set up the db so this is a string to write a template to a file
* we could use an array, mysql queries, comma separated values, or json format. 
* this can basically be deleted when a database is setup
* 
* (MW - 12/10/21)
* - Once the DBs are made you are correct this will not be needed
* - The formatting of the text files should be noted though (good for report!) as it is how they will be read in and out
* 
*/
//void CreateDatabases()
//{
//    myfile.open("patient_detail_database.txt"); 
//    myfile << "Patient Detail Table\n\n"; 
//    myfile <<"Field Name\tData Type\tDescription\nPatient ID\tInteger\nName\tVar Char\tName of the patient\nDate of birth\tInteger\nAddress\tVar Char\nVisited Location\tVar Char\nDate/Timing\tDateTime\nLast overseas travel\tString\tYes/No\nCovid Test\tString\tPositive/Negative\nStatus\tString\tAlive/Dead" <<endl <<endl; 
//    myfile.close();
//
//    myfile.open("symptom_database.txt");  
//    myfile << "Symptom Table\n\n";
//    myfile << "Field Name\tData Type\tDescription\nLow Risk\tVar Char\t Fever, Dry Cough\nMedium Risk\tVar Char\nHigh Risk\tVar char" << endl <<endl;
//    myfile.close();
//
//    myfile.open("location_database.txt");
//    myfile << "High Risk Covid Location\n\n";
//    myfile << "Field Name\tData Type\tDescription\nid\tVar Char\tAuburn Train Station\nid\tVar Char\tRoyal Hotel";
//    myfile.close();
//   
//}

//needs to be tested if this works
//string NormaliseString(string data){
//    std::transform(data.begin(), data.end(), data.begin(),[](unsigned char c){ return std::tolower(c); });
//}


/**
* OPTION 5: Prints out the current users info as it is currently stored in the DB
* @param ...
* @returns ...
*
* - If the Patient detail is empty you should display "[] - the database is empty"
*
* (MW - 12/10/21)
* - This needs to get the details of THE CURRENT PATIENT (not the whole DB)
* - Just scan through patient DB and print out details at line of patient ID
*
*/
void DisplayPositivePatients()
{
    //string line;
    //myfile.open("patient_detail_database.txt");
    //if (myfile.is_open())
    //{
    //    while (getline(myfile, line))
    //    {
    //        cout << line << '\n'; // this also needs to be changed to display "[]" if db is empty
    //    }
    //}
    //myfile.close();
}



/**
* OPTION 4: Allows the current user to update their details and saves them to the DB
* @param ...
* @returns ...
*
* Remember:
* - Check for illigal characters
*       -> "Unknown selection, please try again"
* - If the Patient detail is empty you should display "[] - the database is empty"
* - Alow for upper/lower characters
*
* (MW - 12/10/21)
* - CURRENT PATIENT
* - Find line in DB using patient ID
* - Get new variables
* - Update via overwrting info at that line in the DB
*/
void UpdatePatientDetails()
{
    ////get by patientID or name
    //cout << "Enter your address:";
    //cin >> address;
    //cout << "Have you travelled overseas in the last 6 months, Y/N?";
    //cin >> overseasTravel;
    //cout << "Please select your visited location from the High Risk COVID areas:"; // similar to above, possibly display the db of high risk locations and display options 1-10 
    //cin >> visitedLocation;
    //cout << "Status:" << "1.Cured" << endl << "2.Dead";
    //cin >> status; // to be fixed
}



/**
* OPTION 3: Prints out a list of high risk locations to the terminal (for user to read)
* @param ...
* @returns ...
* 
* (MW - 12/10/21)
* - This is mostly fine, just needs some minor fixes (formatting from file, etc)
* - Add things like "The following locations are high risk:", etc...we can format the info from the DB however we like onces its read in
* 
*/
void DisplayUpdatedLocation()
{
    //string line;
    //myfile.open("location_database.txt");
    //if (myfile.is_open()) 
    //{ 
    //    while ( getline(myfile, line) ) 
    //    { 
    //    cout << line << '\n'; 
    //    }
    //} 
    //myfile.close();
}



/**
* OPTION 2: Takes in new user info, stores info to DB, and also recommends if user needs a test
* @param ...
* @returns ...
*
* Remember:
* - Check for illigal characters
*       -> "Unknown selection, please try again"
* - If the Patient detail is empty you should display "[] - the database is empty"
* - Alow for upper/lower characters
*
* (MW - 12/10/21)
* - We will need to load in the patient details DB and locations DB as they may required an update
* - Need to be able to check if ID exists
* - Update status of test result
*       -> Add any new locations to locations DB if positive (loop)
*       -> Check for location duplicates? (might be too much at this stage)
*/

/** (JK - 14/10/21) - UpdateTestStatus() info
Thus far I have the user input their patientID which we fetch from the database.
Then I get their input of status(positive or negative).
We know that their test status in the database is at index 9.
Retrieving each row, splitting at commas, we retrieve the 9th index.
We then write into their status positive or negative depending what they chose (1 or 2)
If they were positive, then we get their input of visitedLocations
So far I have just appended it to the database, duplicates arent checked at this stage. 

Things to fix:
-menu option selections and loopings need to function properly (high risk locations option is being reached)
- menu option when input is a char it still continues
-database needs to print on newlines

**/
void UpdateTestStatus()
{
    fstream ifileCheckPatientDB, fout;
    //opens existing record
    ifileCheckPatientDB.open("patientDB.txt", ios::in);
    fout.open("patientDBnew.txt", ios::out);
    int patientID, selection;
    string getRowLine, getRowVar, updatedStatus;
    string visitedLocation;
    vector<string> tempRow;
    

    int indexOfTestStatus = 9; //index of test in csv file
    int count = 0, i;
    // get patient id from user
    cout << "Enter your Patient ID:";
    cin >> patientID;
    //get data to be updated
    cout << "Enter test status." << endl;
    cout << "Enter 1 for positive.\nEnter 2 for Negative.";
    cin >> selection;
    while(selection != 1)
    {
        while (!(cin >> selection))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n\nPlease enter the number of the option you wish to select.\n1: Positive\n2: Negative" << endl;
            cout << "\n>> ";
        }
        switch(selection)
        {
            case 1:
                //update this patient is positive in the db
                updatedStatus = "Positive";
                cout << "Enter your visited location:" << endl;
                cin >> visitedLocation;
                break;
            case 2:
                //update this patient is negative in the db
                updatedStatus = "Negative";
                break;
            default:
                cout << "Unknown selection, please try again.\n" << endl;
        }
    }

    getline(ifileCheckPatientDB, getRowLine); 
    while (getline(ifileCheckPatientDB, getRowLine))
    { 
        tempRow.clear();
        stringstream ss(getRowLine); // Splits Row into "Columns" (RowVar)

        // word variable is storing the column data of a row
        while (getline(ss, getRowVar, ','))
        {
            tempRow.push_back(getRowVar);
        }
        int compareID = stoi(tempRow[0]);
        int row_size = tempRow.size();
        if(compareID == patientID)
        {
            count = 1;
            stringstream convert;
            convert << updatedStatus;
            tempRow[indexOfTestStatus] = convert.str();
            if(!ifileCheckPatientDB.eof())
            {
                for(i=0; i < row_size - 1; i++ )
                {
                    //write the updated data to new file 
                    fout << tempRow[i] << ", ";
                }
                fout << tempRow[row_size - 1] << "\n";
            }
        }
        else 
        {
            if(!ifileCheckPatientDB.eof())
            {
                for (i = 0; i < row_size - 1; i++) 
                {
                    fout << tempRow[i] << ", ";
                }
            }
        }
        if(ifileCheckPatientDB.eof())
        {
            break;
        }
    }
    if(count == 0)
    {
        cout << "[] - The database is empty.";
    }
        
    //update location database of new high risk location
    fstream ifileAddHighRiskLocations;
    ifileAddHighRiskLocations.open("highRiskLocationsDB.txt");
    ifileAddHighRiskLocations << visitedLocation << ", ";
    ifileCheckPatientDB.close();
    fout.close();
    remove("database.txt"); //removing the previous database, then renaming the newly written and changing its name to replace the old.
    rename("patientDBnew.txt", "patientDBnew1"); // this must be changed if it works to "patientDB.txt"


}


/**
* OPTION 1: Takes in new user info, stores info to DB, and also recommends if user needs a test
* @param ...
* @returns ...
*
* Remember:
* - Check for illigal characters
*       -> "Unknown selection, please try again"
* - Alow for upper/lower characters
*
* (MW - 12/10/21)
* - All DBs required
* - For patient ID: scan through DB line by line only checking first column (ID)
*       -> No DB = "[] - the database is empty"
*       -> No match proceed / match "This ID exists"
*       -> Order is not an issue atm
* - If at High Risk Location with any symptoms, recomend test
* - If High Risk Symptoms, recomend test
* - Other symptoms -> "isolate at home" or something like that
*       -> At least Try 5 more combination from real life scenario (???)
* - If the Symptom database is empty you should display, "Unable to recommend COVID Test � required data missing".
*
*/
void CovidTestRecommendationDetails()
{
    int patientID;
    bool allowContinue = false;
    while (!allowContinue)
    {
        patientID = NULL;
        cout << "\nEnter your patient ID (numbers only, no spaces): ";
        while (!(cin >> patientID)) // Prevents invalid inputs like letters, etc - MW
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n\nEnter your patient ID (numbers only, no spaces): ";
        }

ifstream ifileCheckPatientDB; // if patientID already exists then cant send to db
ifileCheckPatientDB.open("patientDB.txt");
if (ifileCheckPatientDB.fail())
{
    cout << "\nPatient Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
    cout << "\nReturning to main menu.\n" << endl;
    return;
}

if (ifileCheckPatientDB.is_open())
{
    string getRowLine, getRowVar;
    vector<string> tempRow;
    int compareID;

    allowContinue = true; // Will allow function to continue so long as patient ID does not exist

    getline(ifileCheckPatientDB, getRowLine); // First row redundant - Might be a better method (replace this if so)
    while (getline(ifileCheckPatientDB, getRowLine))
    {
        tempRow.clear(); // Memory Management - Clears previous line get

        stringstream ss(getRowLine); // Splits Row into "Columns" (RowVar)

        while (getline(ss, getRowVar, ','))
        {
            tempRow.push_back(getRowVar);
        }

        compareID = stoi(tempRow[0]);

        if (compareID == patientID)
        {
            allowContinue = false;

            int selection(0);
            cout << "\nPatient ID already exists.\nPlease enter the number of the option you wish to select.\n1: Try again\n2: Return to main menu" << endl;
            cout << "\n>> ";
            while (selection != 1)
            {
                while (!(cin >> selection)) // Prevents invalid inputs like letters, etc - MW
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input.\n\nPlease enter the number of the option you wish to select.\n1: Try again\n2: Return to main menu" << endl;
                    cout << "\n>> ";
                }
                switch (selection)
                {
                case 1:
                    ifileCheckPatientDB.close();
                    break;

                case 2:
                    ifileCheckPatientDB.close();
                    return;

                default:
                    cout << "Unknown selection, please try again.\n" << endl;
                }
            }
        }
    }
}
ifileCheckPatientDB.close();
    }

    // New patient - Allow details to be entered and then store data on a new line of the patient DB.
    char firstName[100], lastName[100], address[100], visitedLocation[100];
    int dayDOB, monthDOB, yearDOB;
    time_t dateLocationVisited;
    string overseasTravel;

    cout << "\nPlease enter your first name: "; // Remove commas
    cin.ignore();
    cin.getline(firstName, 100);

    cout << "\nPlease enter your last name: ";
    cin.getline(lastName, 100);

    cout << "\nWhat is your date of birth (format: dd/mm/yyyy): ";
    allowContinue = false;
    while (!allowContinue)
    {
        string temp;
        getline(cin, temp);
        dayDOB = stoi(temp.substr(0, 2));
        monthDOB = stoi(temp.substr(3, 5));
        yearDOB = stoi(temp.substr(6, 10));

        if ((yearDOB > 1900 && yearDOB < MAX_YEAR) && (monthDOB >= 1 && monthDOB <= 12) && (dayDOB >= 1 && dayDOB <= 31))
        {
            if ((monthDOB == 4 || monthDOB == 6 || monthDOB == 9 || monthDOB == 11) && (dayDOB < 31)) // Max days = 30
            {
                
            }
            if (monthDOB == 2)
            {
                if ((yearDOB % 4 == 0 && dayDOB <= 29) || (yearDOB % 4 != 0 && dayDOB <= 28)) // Check leap year
                {
                    allowContinue = true;
                }

            }
        }
        else
        {
            cout << "Invalid date. Please try again (format: dd/mm/yyyy): ";
        }
    }

    



    //cout << "Enter your address:";
    //cin >> address;

    //cout << "Have you travelled overseas in the last 6 months, Y/N?";
    //cin >> overseasTravel;

    //cout << "Please select your symptoms:"; // could just make an if/switch statement for this one with options 1-3. eg. 1: (Low risk) Dry cough. 2: (Medium risk) Fever
    ////cin >> 

    //cout << "Please select your visited location from the High Risk COVID areas:"; // similar to above, possibly display the db of high risk locations and display options 1-10 
    //cin >> visitedLocation;

    ////send variables to db
}


/**
* Simple function to print out the main menu instructions
* @param none
* @returns none
*/
void PrintMainMenu()
{
    cout << "1: Enter your details for COVID-Test Recommendation" << endl;
    cout << "2: Submit your Covid test status & Update the location database" << endl;
    cout << "3: Display the updated location (High Risk for COVID)" << endl;
    cout << "4: Update COVID Patient Details" << endl;
    cout << "5: Display the COVID Positive patient details" << endl;
    cout << "6: Quit" << endl;
    cout << "\n>> ";
}

/**
* Main display loop that the user navigates through
* @param ...
* @returns ...
*
* (MW - 12/10/21)
* This is mostly good; some minor additions/fixes will be needed
* - I'll probably add some of my own flare eventually.
*
*/
void DisplayMenu()
{
    int selection(0);

    while(selection != 6)
    {
        cout << "Please enter the number of the option you wish to select.\n" << endl;
        PrintMainMenu();

        while (!(cin >> selection)) // Prevents invalid inputs like letters, etc - MW
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please try again.\n" << endl;;
            PrintMainMenu();
        }
        switch (selection)
        {
            case 1: 
                CovidTestRecommendationDetails();
                break;

            case 2:
                UpdateTestStatus();
                break;

            case 3:
                DisplayUpdatedLocation();
                break;

            case 4:
                UpdatePatientDetails();
                break;

            case 5:
                DisplayPositivePatients();
                break;

            case 6:
                break;

            default: 
                cout << "Unknown selection, please try again.\n" << endl;
        }
  
    } 
    cout << "\nGoodbye" << endl;
}


 
/**
* For testing purposes the database is created initially before calling the main loop
* @param ...
* @returns ...
* 
*/
int main () 
{ 
    //CreateDatabases();

    cout << "\nWelcome\n" << endl;
    DisplayMenu();
    
    return 0; 
} 




