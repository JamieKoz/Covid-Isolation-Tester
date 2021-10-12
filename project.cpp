/*                  SWE20004 - Team Project B
*                   Semester 2, 2021
* 
* File:             project.cpp (should be renamed, can do later)
* 
* Aurthors:         Kozminska, Jamie - S/N
*                   Woodrow, Michael - 6798527
* 
* Created:          Date this was created?
* 
* Last Modified:    12/10/2021
* 
* 
* 
*   (MW - 12/10/21)
*   A lot of good work here, but also a number of issues that I just don't have time to work on with the time I have left today (unfortunatly I need sleep)
*   I will make a bigger effort on adding code tomorrow, just needed to take time today to make sure the fondations are correct and everything is set up correctly so there wont be issues.
*       -> Fpr example, there are a number of things that will need to be re-written to work as expected
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
#include <ctime> // Required for date/time format - MW
        
using namespace std; 

/*
* (MW - 12/10/21)
* Best not make globals like this as it is hard to keep track of / not good practice anyways
* - Might need some pointers for current user, etc as globals so I'll keep things posted.
* 
*/
int patientID;
string fname;
string lname;
int doB;
string address;
string visitedLocation;
int date;
string overseasTravel;
string covidTest;
string status;

fstream myfile; 



/**
* For debugging
* @param none
* @returns nothing
* 
* (JK - ??/10/21)
* I was unsure how we should set up the db so this is a string to write a template to a file
* we could use an array, mysql queries, comma separated values, or json format. 
* this can basically be deleted when a database is setup
* 
* (MW - 12/10/21)
* - Once the DBs are made you are correct this will not be needed
* - The formatting of the text files should be noted though (good for report!) as it is how they will be read in and out
* 
*/
void CreateDatabases()
{
    myfile.open("patient_detail_database.txt"); 
    myfile << "Patient Detail Table\n\n"; 
    myfile <<"Field Name\tData Type\tDescription\nPatient ID\tInteger\nName\tVar Char\tName of the patient\nDate of birth\tInteger\nAddress\tVar Char\nVisited Location\tVar Char\nDate/Timing\tDateTime\nLast overseas travel\tString\tYes/No\nCovid Test\tString\tPositive/Negative\nStatus\tString\tAlive/Dead" <<endl <<endl; 
    myfile.close();

    myfile.open("symptom_database.txt");  
    myfile << "Symptom Table\n\n";
    myfile << "Field Name\tData Type\tDescription\nLow Risk\tVar Char\t Fever, Dry Cough\nMedium Risk\tVar Char\nHigh Risk\tVar char" << endl <<endl;
    myfile.close();

    myfile.open("location_database.txt");
    myfile << "High Risk Covid Location\n\n";
    myfile << "Field Name\tData Type\tDescription\nid\tVar Char\tAuburn Train Station\nid\tVar Char\tRoyal Hotel";
    myfile.close();
   
}



/**
* Prints out a list of high risk locations to the terminal (for user to read)
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
    string line;
    myfile.open("location_database.txt");
    if (myfile.is_open()) 
    { 
        while ( getline(myfile, line) ) 
        { 
        cout << line << '\n'; 
        }
    } 
    myfile.close();
}



/**
* Allows the current user to update their details and saves them to the DB
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
    //get by patientID or name
    cout << "Enter your address:";
    cin >> address;
    cout << "Have you travelled overseas in the last 6 months, Y/N?";
    cin >> overseasTravel;
    cout << "Please select your visited location from the High Risk COVID areas:"; // similar to above, possibly display the db of high risk locations and display options 1-10 
    cin >> visitedLocation;
    cout << "Status:" <<"1.Cured" << endl << "2.Dead";
    cin >> status; // to be fixed
}



/**
* Prints out the current users info as it is currently stored in the DB
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
    string line;
    myfile.open("patient_detail_database.txt");
    if (myfile.is_open()) 
    {
         while ( getline(myfile, line) ) 
        { 
        cout << line << '\n'; // this also needs to be changed to display "[]" if db is empty
        }
    }
    myfile.close();
}



/**
* Takes in new user info, stores info to DB, and also recommends if user needs a test
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
* - All DBs required
* - For patient ID: scan through DB line by line only checking first column (ID)
*       -> No match proceed / match "This ID exists"
*       -> Order is not an issue atm
* - If at High Risk Location with any symptoms, recomend test
* - If High Risk Symptoms, recomend test
* - Other symptoms -> "isolate at home" or something like that
*       -> At least Try 5 more combination from real life scenario (???)
* - If the Symptom database is empty you should display, "Unable to recommend COVID Test – required data missing".
* 
*/
void CovidTestRecommendationDetails()
{
    
    cout << "Patient Details" << endl;
    cout << "Enter your patient ID:";
    cin >> patientID; // if patientID already exists then cant send to db
    cout << "Enter your First name:";
    cin >> fname;
    cout << "Enter your Family name:";
    cin >> lname;
    cout << "Enter your Date of birth:";
    cin >> doB;
    cout << "Enter your address:";
    cin >> address;
    cout << "Have you travelled overseas in the last 6 months, Y/N?";
    cin >> overseasTravel;
    cout << "Please select your symptoms:"; // could just make an if/switch statement for this one with options 1-3. eg. 1: (Low risk) Dry cough. 2: (Medium risk) Fever
    //cin >> 
    cout << "Please select your visited location from the High Risk COVID areas:"; // similar to above, possibly display the db of high risk locations and display options 1-10 
    cin >> visitedLocation;

    //send variables to db

}



/**
* Takes in new user info, stores info to DB, and also recommends if user needs a test
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
*
*/
void UpdateTestStatus()
{
    int var;
    cout << "Enter your PatientID:";
    cin >> patientID;
    cout << "Enter your covid test status:";
    cin >> status;
    cout << "Enter your visited location:";
    cin >> visitedLocation;
    cout << "Enter 1 for positive.\nEnter 2 for Negative.";
    cin >> var;
    if(var == 1)
    {
        //update this patient is positive in the db
        //update location database of new high risk location

    }
    else if(var == 2)
    {
        //update this patient is negative in the db
    }
    else
    {
        cout << "Please select an option 1 or 2." << endl;
    }
}



/**
* Main display loop that the user navigates through
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
* This is mostly good; some minor additions/fixes will be needed
* - I'll probably add some of my own flare eventually.
*
*/
void DisplayMenu()
{
    int selection;

    cin >> selection;

    while(selection != 6)
    {
        cout << "1: Enter your details for COVID-Test Recommendation" << endl;
        cout << "2: Submit your Covid test status & Update the location database" << endl;
        cout << "3: Display the updated location (High Risk for COVID)" << endl;
        cout << "4: Update COVID Patient Details" << endl;
        cout << "5: Display the COVID Positive patient details" << endl;
        cout << "6: Quit" << endl;
        cin >> selection;
        if(!isalpha(selection))
        {
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

                default: 
                    cout << "Unknown selection, please try again" << endl;
            }
        }
  
    } 
    cout << "Goodbye";
}


 
/**
* For testing purposes the database is created initially before calling the main loop
* @param ...
* @returns ...
* 
*/
int main () 
{ 
    CreateDatabases();
    DisplayMenu();
    
    return 0; 
} 




