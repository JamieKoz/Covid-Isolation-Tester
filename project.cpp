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
*   IN REGARDS TO THE DATABASES:
*       - It says we need a primary DB, but I think 3 seperate DBs makes more sense
*       - Symptoms should be formatted to just have three lines, each line is a risk level
*           -> can add something at the start of the line to indicate this if needed, but remember we just need to read out the description and let the user select
*               (maybe ask line by line and each time the user replies yes/no and if they reply yes at high risk then its locked in?)
*       - Locations really just needs locations at each line
*           -> Duplicates might be an issue, but its low priority to address atm and not really a major issue
*       - Patients should be one ID per line and each detail (name, address, etc) seperated by a character (comma?) so we can format it in and out of the DB
*           -> When there is an update, the line can just be overwritten with new data.
*   FOR THE REST OF THE PROGRAM:
*       - You can read my block comments. Hopefully they are clear-ish.
*           -> I'll be doing a fair amount of work on this so just keep me upto date if you are working on something and I'll try and do the same
* 
*   (MW - 14/10/21)
*   OPTION 1 fuly working
*       - Need to add 2-3 more option outputs as required ("At least Try 5 more combination from real life scenario")
*   New reusable functions added:
*       - void PrintMainMenu()
*       - bool CheckAddressValid(char(&charArray)[MAX_CHAR_ARRAY_LENGTH])
*       - bool CheckCharArrayValid(char(&charArray)[MAX_CHAR_ARRAY_LENGTH])
*       - bool CheckDateValid(string& date)
*       - bool CheckYesNoValid(string& answer)
*       - bool CheckInterupt(int& count)
* 
*   (MW - 15/10/21)
*   Minor tweaks to OPTION 1 
*       - Still need to add 2-3 more option outputs as required ("At least Try 5 more combination from real life scenario")
*   Reworked OPTION 2
*       - A lot of potential hazards and bugs fixed
*       - Haven't really tested the reworked code yet, but I am pretty confident its solid as its based a lot off what I did in OPTION 1
*   Added a bunch of useful #define's
*   Seperated and updated the name of the patient DB varible so they are easy to work with
*       - Gave them all default intiation values too...this might have a side effect on the CheckXisCorrectFormat functions...not sure yet
*   New reusable functions added:
*       - void SaveNewPatientData(ofstream& ofilePatientDB, **REFERENCES TO ALL PATIENT DB VARIABLES**)
*       - void PopulatePatientData(vector<string> &tempDataRow, **REFERENCES TO ALL PATIENT DB VARIABLES**)
*
*/

#include <iostream> 
#include <fstream> 
#include <string>
#include <vector> // - MW
#include <sstream> // - MW
#include <algorithm> //Required for string normalisation
#include <cctype> //Required for string normalisation
#include <regex> // - MW

using namespace std;

// ARRAY LENGTHS
#define MIN_CHAR_NULL_START     4
#define MAX_CHAR_ARRAY_LENGTH   100
#define SYMPTOMS_ARRAY_LENGTH   3
// ARRAY LOCATIONS
#define SYM_LOW_ARRAY_LOC               0
#define SYM_MED_ARRAY_LOC               1
#define SYM_HI_ARRAY_LOC                2
#define PATIENT_ID_ARRAY_LOC            0
#define PATIENT_FIRST_NAME_ARRAY_LOC    1
#define PATIENT_LAST_NAME_ARRAY_LOC     2
#define PATIENT_DOB_ARRAY_LOC           3
#define PATIENT_ADDRESS_ARRAY_LOC       4
#define PATIENT_LOC_VISITED_ARRAY_LOC   5
#define PATIENT_DATE_VISITED_ARRAY_LOC  6
#define PATIENT_TIME_VISITED_ARRAY_LOC  7
#define PATIENT_OS_TRAVEL_ARRAY_LOC     8
#define PATIENT_TEST_RESULT_ARRAY_LOC   9
#define PATIENT_STATUS_ARRAY_LOC        10
// MISC
#define CURRENT_YEAR            2021    // Manually update each year - MW
#define INT_CYCLES              10      // Cycles until a force quit - MW
#define DEFAULT_DATA           "N/A"
#define DEFAULT_STATUS         "Alive"

// SOME OF THESE MAY NEED WORK - MW
const regex CORRECT_DATE_FORMAT{ "\\b\\d{2}[/]\\d{2}[/]\\d{4}\\b" }; // dd/mm/yyyy
const regex CORRECT_TIME_FORMAT{ "\\b^(0[1-9]|1[0-2]):([0-5]\\d)\\s?((?:[Aa]|[Pp])\\.?[Mm]\\.?)$\\b" }; // hh:mm am|pm
const regex CORRECT_YES_NO_FORMAT{ "\\b[y|Y][e|E]?[s|S]?|[n|N][o|O]?\\b" }; // yes or no
const regex CORRECT_YES_FORMAT{ "\\b[y|Y][e|E]?[s|S]?\\b" }; // yes
const regex CORRECT_ALPHA_FORMAT{ "\\b[a-zA-Z]\\b" }; // letters only
const regex CORRECT_ADDRESS_FORMAT{ "\\b[a-zA-Z0-9\\s/]\\b" }; // letters, numbers, slashes, and spaces only (NO COMMAS)

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
//fstream myfile; 
/*
* Patient data used in database (will be stored in CSV format)
* @param ...
* @returns ...
* 
* (MW - 16/10/21)
* Making the patient data a class to that the varialbes can be initiated repeativly when required and avoid copy/pasting
*
*/
class PatientDataVaribles
{
public:
    int patientID;
    char patientFirstName[MAX_CHAR_ARRAY_LENGTH]{ 0 }, patientLastName[MAX_CHAR_ARRAY_LENGTH]{0}, patientAddress[MAX_CHAR_ARRAY_LENGTH]{0}, patientLocationVisited[MAX_CHAR_ARRAY_LENGTH]{0};
    string patientDOB, patientDateVisited, patientTimeVisited, patientOverseasTravel, patientTestResult, patientStatus;

    PatientDataVaribles()
    {
        int i;
        patientID = NULL;
        strcpy_s(patientFirstName, DEFAULT_DATA);
        for (i = MIN_CHAR_NULL_START; i < MAX_CHAR_ARRAY_LENGTH; i++)
        {
            patientFirstName[i] = '\0';
        }        
        strcpy_s(patientLastName, DEFAULT_DATA);
        for (i = MIN_CHAR_NULL_START; i < MAX_CHAR_ARRAY_LENGTH; i++)
        {
            patientLastName[i] = '\0';
        }
        strcpy_s(patientAddress, DEFAULT_DATA);
        for (i = MIN_CHAR_NULL_START; i < MAX_CHAR_ARRAY_LENGTH; i++)
        {
            patientAddress[i] = '\0';
        }
        strcpy_s(patientLocationVisited, DEFAULT_DATA);
        for (i = MIN_CHAR_NULL_START; i < MAX_CHAR_ARRAY_LENGTH; i++)
        {
            patientLocationVisited[i] = '\0';
        }
        patientDOB = patientDateVisited = patientTimeVisited = patientOverseasTravel = patientTestResult = DEFAULT_DATA;
        patientStatus = DEFAULT_STATUS;
    }
};

/**
* Populates patient data variables from file when ID matches
* @param ...
* @returns ...
*
*/
void PopulatePatientDataVars(vector<string>& tempDataRow,
    int& patientID,
    char(&patientFirstName)[MAX_CHAR_ARRAY_LENGTH],
    char(&patientLastName)[MAX_CHAR_ARRAY_LENGTH],
    char(&patientAddress)[MAX_CHAR_ARRAY_LENGTH],
    char(&patientLocationVisited)[MAX_CHAR_ARRAY_LENGTH],
    string& patientDOB,
    string& patientDateVisited,
    string& patientTimeVisited,
    string& patientOverseasTravel,
    string& patientTestResult,
    string& patientStatus)
{
    //ID
    patientID = stoi(tempDataRow[PATIENT_ID_ARRAY_LOC]);
    //FIRST NAME
    strcpy_s(patientFirstName, tempDataRow[PATIENT_FIRST_NAME_ARRAY_LOC].c_str());
    //LAST NAME
    strcpy_s(patientLastName, tempDataRow[PATIENT_LAST_NAME_ARRAY_LOC].c_str());
    //DOB
    patientDOB = tempDataRow[PATIENT_DOB_ARRAY_LOC];
    //ADDRESS
    strcpy_s(patientAddress, tempDataRow[PATIENT_ADDRESS_ARRAY_LOC].c_str());
    //LOCATION VISITED
    strcpy_s(patientLocationVisited, tempDataRow[PATIENT_LOC_VISITED_ARRAY_LOC].c_str());
    //DATE VISITED
    patientDateVisited = tempDataRow[PATIENT_DATE_VISITED_ARRAY_LOC];
    //TIME VISITED
    patientTimeVisited = tempDataRow[PATIENT_TIME_VISITED_ARRAY_LOC];
    //OVERSEAS TRAVEL
    patientOverseasTravel = tempDataRow[PATIENT_OS_TRAVEL_ARRAY_LOC];
    //TEST RESULT
    patientTestResult = tempDataRow[PATIENT_TEST_RESULT_ARRAY_LOC];
    //STATUS
    patientStatus = tempDataRow[PATIENT_STATUS_ARRAY_LOC];
}
/**
* Sends new patient data to desired DB file
* @parm ...  (many)
* @returns ...
*
*/
void SaveNewPatientData(ofstream& ofilePatientDB,
    int& patientID,
    char(&patientFirstName)[MAX_CHAR_ARRAY_LENGTH],
    char(&patientLastName)[MAX_CHAR_ARRAY_LENGTH],
    char(&patientAddress)[MAX_CHAR_ARRAY_LENGTH],
    char(&patientLocationVisited)[MAX_CHAR_ARRAY_LENGTH],
    string& patientDOB,
    string& patientDateVisited,
    string& patientTimeVisited,
    string& patientOverseasTravel,
    string& patientTestResult,
    string& patientStatus)
{
    //ID
    ofilePatientDB << patientID;
    ofilePatientDB << ",";
    //FIRST NAME
    ofilePatientDB << patientFirstName;
    ofilePatientDB << ",";
    //LAST NAME
    ofilePatientDB << patientLastName;
    ofilePatientDB << ",";
    //DOB
    ofilePatientDB << patientDOB;
    ofilePatientDB << ",";
    //ADDRESS
    ofilePatientDB << patientAddress;
    ofilePatientDB << ",";
    //LOCATION VISITED
    ofilePatientDB << patientLocationVisited;
    ofilePatientDB << ",";
    //DATE VISITED
    ofilePatientDB << patientDateVisited;
    ofilePatientDB << ",";
    //TIME VISITED
    ofilePatientDB << patientTimeVisited;
    ofilePatientDB << ",";
    //OVERSEAS TRAVEL
    ofilePatientDB << patientOverseasTravel;
    ofilePatientDB << ",";
    //TEST RESULT
    ofilePatientDB << patientTestResult;
    ofilePatientDB << ",";
    //STATUS
    ofilePatientDB << patientStatus << endl;
}

/**
* Press enter to continue stub
* @param ...
* @returns ...
*/
void PressEnterToContinue()
{
    cout << "\n\nPress enter to continue...";
    cin.ignore();
    cin.clear();
    while (!(cin.peek())) {}
    cout << "---------------------------------------------------------------------------------------------------------\n\n";
}
/**
* Checks if interupt is required
* @param ...
* @returns ...
*/
bool CheckInterupt(int& count)
{
    count++;
    if (count == INT_CYCLES)
    {
        cout << "\nToo many invalid inputs.\nReturning to main menu.\n" << endl;
        return true;
    }
    return false;
}
/**
* Checks to make sure the answer is yes or no
* @param ...
* @returns ...
*/
bool CheckYesNoValid(string& answer)
{
    cin.clear();
    getline(cin, answer);
    if (!regex_match(answer, CORRECT_YES_NO_FORMAT))
    {
        cout << "Please try again (yes or no): ";
        return false;
    }
    return true;
}
/**
* Checks to make sure the time entered is the correct format
* @param ...
* @returns ...
*/
bool CheckTimeValid(string& answer)
{
    cin.clear();
    getline(cin, answer);
    if (!regex_match(answer, CORRECT_TIME_FORMAT))
    {
        cout << "Please try again (format: hh:mm [am|pm]): ";
        return false;
    }
    return true;
}
/**
* Checks to make sure the date is formatted correctly
* @param ...
* @returns ...
*/
bool CheckDateValid(string& date)
{
    cin.clear();
    int dayDOB, monthDOB, yearDOB;
    while (!regex_match(date, CORRECT_DATE_FORMAT))
    {
        getline(cin, date);
        if (!regex_match(date, CORRECT_DATE_FORMAT))
        {
            cout << "Please try again (format: dd/mm/yyyy): ";
        }
    }
    dayDOB = stoi(date.substr(0, 2));
    monthDOB = stoi(date.substr(3, 5));
    yearDOB = stoi(date.substr(6, 10));

    if ((yearDOB >= 1900 && yearDOB <= CURRENT_YEAR) && (monthDOB >= 1 && monthDOB <= 12) && (dayDOB >= 1 && dayDOB <= 31))
    {
        if (((monthDOB == 4 || monthDOB == 6 || monthDOB == 9 || monthDOB == 11) && dayDOB < 31)               // IF (Months with 30 max days)
            || (monthDOB != 2)                                                                                 // OR (Not Febuary)
            || (monthDOB == 2 && ((yearDOB % 4 == 0 && dayDOB <= 29) || (yearDOB % 4 != 0 && dayDOB <= 28))))  // OR (Check leap year)
        {
            return true;
        }
    }
    date.clear();
    cout << "Invalid date. Please try again (format: dd/mm/yyyy): ";
    return false;
}
/**
* Checks an array of Char values to make sure it contains only letters
* @param ...
* @returns ...
*/
bool CheckCharArrayValid(char(&charArray)[MAX_CHAR_ARRAY_LENGTH])
{
    cin.clear();
    cin.getline(charArray, MAX_CHAR_ARRAY_LENGTH);
    for (int i = 0; i < MAX_CHAR_ARRAY_LENGTH; i++)
    {
        if (!isalpha(charArray[i]) && charArray[i] != '\0')
        {
            return false;
        }
    }
    return true;
}
/**
* Checks an address to make sure it only contains valid characters (no commas)
* @param ...
* @returns ...
*/
bool CheckAddressValid(char(&charArray)[MAX_CHAR_ARRAY_LENGTH])
{
    cin.clear();
    cin.getline(charArray, MAX_CHAR_ARRAY_LENGTH);
    if (charArray[0] == 0)
    {
        cout << "Invalid input. Please try again: ";
        return false;
    }
    for (int i = 0; i < MAX_CHAR_ARRAY_LENGTH; i++)
    {
        if (charArray[i] == ',')
        {
            charArray[i] = ' ';
        }
    }
    return true;
}
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
    int patientID, interuptCount(0);
    bool allowContinue(false), patientMatch(false);

    while (!allowContinue)
    {
        // Get patient id from user
        cout << "\nEnter your patient ID (numbers only, no spaces): ";
        while (!(cin >> patientID)) // Prevents invalid inputs like letters, etc - MW
        {
            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n\nEnter your patient ID (numbers only, no spaces): ";
        }

        // Open the patient DB
        ifstream ifilePatientDB;
        ifilePatientDB.open("patientDB.txt");
        if (ifilePatientDB.fail())
        {
            cout << "\nPatient Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
            cout << "\nReturning to main menu.\n" << endl;
            PressEnterToContinue();
            return;
        }

        //Whilst the patient DB file is open
        if (ifilePatientDB.is_open())
        {
            string getRowLine, getRowVar;
            vector<string> tempDataRow;
            int compareID;

            getline(ifilePatientDB, getRowLine); // First row redundant

            while (getline(ifilePatientDB, getRowLine))
            {
                if (!getRowLine.empty())
                {
                    tempDataRow.clear(); // Memory Management - Clears previous line get
                    stringstream ss(getRowLine); // Splits Row into "Columns" (RowVar)
                    while (getline(ss, getRowVar, ','))
                    {
                        tempDataRow.push_back(getRowVar);
                    }

                    compareID = stoi(tempDataRow[PATIENT_ID_ARRAY_LOC]);
                    if (compareID == patientID)
                    {
                        patientMatch = true;
                        cout << "\n-----PATIENT " << patientID << " DETAILS-----" << endl;
                        cout << "\nFirst Name: \t" << tempDataRow[PATIENT_FIRST_NAME_ARRAY_LOC] << endl;
                        cout << "Last Name: \t" << tempDataRow[PATIENT_LAST_NAME_ARRAY_LOC] << endl;
                        cout << "Date of Birth: \t" << tempDataRow[PATIENT_DOB_ARRAY_LOC] << endl;
                        cout << "Address: \t" << tempDataRow[PATIENT_ADDRESS_ARRAY_LOC] << endl;

                        if (tempDataRow[PATIENT_LOC_VISITED_ARRAY_LOC] == "N/A")
                        {
                            cout << "\n" << tempDataRow[PATIENT_FIRST_NAME_ARRAY_LOC] << " has not indicated visiting any locations (yet)." << endl;
                        }
                        else
                        {
                            cout << "\n" << tempDataRow[PATIENT_FIRST_NAME_ARRAY_LOC] << " visited " << tempDataRow[PATIENT_LOC_VISITED_ARRAY_LOC];
                            cout << " on the " << tempDataRow[PATIENT_DATE_VISITED_ARRAY_LOC];
                            cout << " at " << tempDataRow[PATIENT_TIME_VISITED_ARRAY_LOC] << endl;
                        }

                        cout << tempDataRow[PATIENT_FIRST_NAME_ARRAY_LOC] << " has ";
                        if (tempDataRow[PATIENT_OS_TRAVEL_ARRAY_LOC] == "No")
                        {
                            cout << "not ";
                            
                        }
                        cout << "traveled overseas." << endl;

                        if (tempDataRow[PATIENT_TEST_RESULT_ARRAY_LOC] == "Not Recomended")
                        {
                            cout << tempDataRow[PATIENT_FIRST_NAME_ARRAY_LOC] << " was not recomended to get tested for COVID." << endl;
                        }
                        else
                        {
                            cout << "\nTEST RESULT: \t" << tempDataRow[PATIENT_TEST_RESULT_ARRAY_LOC] << endl;
                        }

                        cout << "STATUS: \t" << tempDataRow[PATIENT_STATUS_ARRAY_LOC] << endl;
                    }
                }
            }
            if (patientMatch)
            {
                allowContinue = true;
                ifilePatientDB.close();
                PressEnterToContinue();
            }
            else
            {
                ifilePatientDB.close();
                cout << "\n[] - The database is empty." << endl; // As required in PDF

                // TELL USER / TRY A NEW SEARCH????
                int selection(0);
                cout << "\nThe patient ID " << patientID << " does not exist in the database.\nPlease enter the number of the option you wish to select.\n1: Try again\n2: Return to main menu" << endl;
                cout << "\n>> ";
                interuptCount = 0;
                while (selection != 1)
                {
                    if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
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
                        break;

                    case 2:
                        PressEnterToContinue();
                        return;

                    default:
                        cout << "Unknown selection, please try again.\n" << endl;
                    }
                }
            }
        }
    }
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
    int interuptCount(0);
    bool allowContinue(false), patientMatch(false);
    //PATIENT DB VARS
    PatientDataVaribles tempPatientData;

    while (!allowContinue)
    {
        // Get patient id from user
        cout << "\nEnter your patient ID (numbers only, no spaces): ";
        while (!(cin >> tempPatientData.patientID)) // Prevents invalid inputs like letters, etc - MW
        {
            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n\nEnter your patient ID (numbers only, no spaces): ";
        }

        // Open the patient DB
        ifstream ifilePatientDB;
        ifilePatientDB.open("patientDB.txt");
        if (ifilePatientDB.fail())
        {
            cout << "\nPatient Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
            cout << "\nReturning to main menu.\n" << endl;
            PressEnterToContinue();
            return;
        }

        //Whilst the patient DB file is open
        if (ifilePatientDB.is_open())
        {
            // Creat a temp patient DB to store new data
            ofstream ofilePatientDBTemp;
            ofilePatientDBTemp.open("patientDBTemp.txt");

            string getRowLine, getRowVar;
            vector<string> tempDataRow;
            int compareID;

            getline(ifilePatientDB, getRowLine); // First row redundant - Add to temp DB
            ofilePatientDBTemp << getRowLine << endl;

            while (getline(ifilePatientDB, getRowLine))
            {
                if (!getRowLine.empty())
                {
                    tempDataRow.clear(); // Memory Management - Clears previous line get

                    stringstream ss(getRowLine); // Splits Row into "Columns" (RowVar)

                    while (getline(ss, getRowVar, ','))
                    {
                        tempDataRow.push_back(getRowVar);
                    }

                    compareID = stoi(tempDataRow[PATIENT_ID_ARRAY_LOC]);

                    // !!!!!! - This is where patient data is updated IFF a match is found
                    if (compareID == tempPatientData.patientID)
                    {
                        patientMatch = true;

                        // Store the current patients data ready to modify
                        PopulatePatientDataVars(tempDataRow,
                            tempPatientData.patientID,
                            tempPatientData.patientFirstName, tempPatientData.patientLastName, tempPatientData.patientAddress, tempPatientData.patientLocationVisited,
                            tempPatientData.patientDOB, tempPatientData.patientDateVisited, tempPatientData.patientTimeVisited, tempPatientData.patientOverseasTravel, tempPatientData.patientTestResult, tempPatientData.patientStatus);

                        cout << "\nMatch found!" << endl;

                        bool continueUpdating(true);
                        while (continueUpdating)
                        {
                            cout << "\nFirst Name: \t " << tempPatientData.patientFirstName << endl;
                            cout << "Last Name: \t " << tempPatientData.patientLastName << endl;
                            cout << "Date of Birth: \t " << tempPatientData.patientDOB << endl;
                            cout << "Address: \t " << tempPatientData.patientAddress << endl;
                            cout << "Overseas travel: " << tempPatientData.patientOverseasTravel << endl;
                            cout << "STATUS: \t " << tempPatientData.patientStatus << endl;

                            cout << "\n\nPress enter to continue...";
                            cin.ignore();
                            cin.clear();
                            while (!(cin.peek())) {}

                            cout << "Are these details correct? (Yes or No): ";
                            string answer;
                            cin.ignore();
                            while (!CheckYesNoValid(answer))
                            {
                                if (CheckInterupt(interuptCount))
                                {
                                    ifilePatientDB.close();
                                    ofilePatientDBTemp.close();
                                    remove("patientDBTemp.txt");
                                    PressEnterToContinue();
                                    return;
                                }
                            }
                            if (regex_match(answer, CORRECT_YES_FORMAT))
                            {
                                continueUpdating = false;
                            }
                            else
                            {
                                cout << "\n\nWhat would you like to UPDATE?" << endl;
                                cout << "1: First name" << endl;
                                cout << "2: Last name" << endl;
                                cout << "3: Date of Birth" << endl;
                                cout << "4: Address" << endl;
                                cout << "5: Overseas travel" << endl;
                                cout << "6: STATUS" << endl;
                                cout << "7: Disregard changes and return to main menu" << endl;
                                cout << "\n>> ";
                                int selection(0);
                                bool breakSwitch(false);
                                while (!breakSwitch)
                                {
                                    while (!(cin >> selection))
                                    {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "\nInvalid input. Please try again: ";
                                    }
                                    switch (selection)
                                    {
                                    case 1:
                                        breakSwitch = true;
                                        cout << "\nPlease enter a new first name (letters only, no spaces): ";
                                        cin.ignore();
                                        interuptCount = 0;
                                        while (!CheckCharArrayValid(tempPatientData.patientFirstName))
                                        {
                                            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
                                            cout << "Please try again (letters only, no spaces): ";
                                        }
                                        break;

                                    case 2:
                                        breakSwitch = true;
                                        cout << "\nPlease enter a new last name (letters only, no spaces): ";
                                        interuptCount = 0;
                                        while (!CheckCharArrayValid(tempPatientData.patientLastName))
                                        {
                                            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
                                            cout << "Please try again (letters only, no spaces): ";
                                        }
                                        break;

                                    case 3:
                                        breakSwitch = true;
                                        cout << "\nWhat is your new date of birth (format: dd/mm/yyyy): ";
                                        interuptCount = 0;
                                        while (!CheckDateValid(tempPatientData.patientDOB))
                                        {
                                            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
                                        }
                                        break;

                                    case 4:
                                        breakSwitch = true;
                                        cout << "\nPlease enter your new address (no commas): ";
                                        interuptCount = 0;
                                        while (!CheckAddressValid(tempPatientData.patientAddress))
                                        {
                                            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
                                        }
                                        break;

                                    case 5:
                                        breakSwitch = true;
                                        cout << "\nHave you travelled overseas in the last 6 months (yes or no)?: ";
                                        interuptCount = 0;
                                        while (!CheckYesNoValid(tempPatientData.patientOverseasTravel))
                                        {
                                            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
                                        }
                                        if (regex_match(tempPatientData.patientOverseasTravel, CORRECT_YES_FORMAT))
                                        {
                                            tempPatientData.patientOverseasTravel = "Yes";
                                        }
                                        else
                                        {
                                            tempPatientData.patientOverseasTravel = "No";
                                        }
                                        break;

                                    case 6:
                                        breakSwitch = true;
                                        if (tempPatientData.patientStatus == "Alive")
                                        {
                                            tempPatientData.patientStatus = "Dead";
                                        }
                                        else
                                        {
                                            tempPatientData.patientStatus = "Alive";
                                        }
                                        break;

                                    case 7:
                                        breakSwitch = true;
                                        //Exit
                                        ifilePatientDB.close();
                                        ofilePatientDBTemp.close();
                                        remove("patientDBTemp.txt");
                                        cout << "\nAll changes have been removed.\nReturning to main menu." << endl;
                                        PressEnterToContinue();
                                        return;

                                    default:
                                        cout << "Unknown selection, please try again.\n" << endl;
                                    }
                                }
                            }
                        }
                        // Save to patient DB
                        SaveNewPatientData(ofilePatientDBTemp,
                            tempPatientData.patientID, tempPatientData.patientFirstName, tempPatientData.patientLastName, tempPatientData.patientAddress, tempPatientData.patientLocationVisited,
                            tempPatientData.patientDOB, tempPatientData.patientDateVisited, tempPatientData.patientTimeVisited, tempPatientData.patientOverseasTravel, tempPatientData.patientTestResult, tempPatientData.patientStatus);
                    }
                    // !!!!!! - This is where the remaining lines of data are transfered to the temp file
                    else
                    {
                        ofilePatientDBTemp << getRowLine << endl;
                    }
                }
            }
            if (patientMatch)
            {
                // Make temp file the new DB
                allowContinue = true;
                ifilePatientDB.close();
                ofilePatientDBTemp.close();

                remove("patientDB.txt"); //removing the previous database, then renaming the newly written and changing its name to replace the old.
                rename("patientDBtemp.txt", "patientDB.txt"); // this must be changed if it works to "patientDB.txt"
                cout << "\nYou've successfully updated the database." << endl;

                PressEnterToContinue();

            }
            else
            {
                // Disregard temp file and tell user that the patient ID does not exist in the DB (try again?)

                ifilePatientDB.close();
                ofilePatientDBTemp.close();
                remove("patientDBTemp.txt");
                cout << "\n[] - The database is empty." << endl; // As required in PDF

                // TELL USER / TRY A NEW SEARCH????
                int selection(0);
                cout << "\nThe patient ID " << tempPatientData.patientID << " does not exist in the database.\nPlease enter the number of the option you wish to select.\n1: Try again\n2: Return to main menu" << endl;
                cout << "\n>> ";
                interuptCount = 0;
                while (selection != 1)
                {
                    if (CheckInterupt(interuptCount)) { ifilePatientDB.close(); PressEnterToContinue(); return; }
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
                        break;

                    case 2:
                        PressEnterToContinue();
                        return;

                    default:
                        cout << "Unknown selection, please try again.\n" << endl;
                    }
                }
            }
        }
    }
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
    string line;
    ifstream displayLocationsFile;
    displayLocationsFile.open("highRiskLocationsDB.txt");
    if (displayLocationsFile.fail())
    {
        cout << "\High Risk Locations Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
        cout << "\nReturning to main menu.\n" << endl;
        PressEnterToContinue();
        return;
    }

    //Whilst the patient DB file is open
    if (displayLocationsFile.is_open())
    {
        cout << "\nThe following locations are HIGH RISK:\n" << endl;
        string getRowLine;
        while (getline(displayLocationsFile, getRowLine))
        {
            if (!getRowLine.empty())
            {
                cout << "\t -> " << getRowLine << endl;
            }
        }
    }
    displayLocationsFile.close();

    PressEnterToContinue();
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
*
* (JK - 14/10/21)
* Thus far I have the user input their patientID which we fetch from the database.
*   -> (MW - 15/10/21) I've reworked the code so that it checks the DB once a patient ID is entered...after all if the ID is not in the DB then we need to try again or return to main menu.
* Then I get their input of status(positive or negative).
*   -> (MW - 15/10/21) I added an option for the user to basically quit if they don't have their result for some reason.
* We know that their test status in the database is at index 9.
*   -> (MW - 15/10/21) I hate magic numbers so thats part of the reason I went ahead and made all those #define's, etc.
* Retrieving each row, splitting at commas, we retrieve the 9th index.
*   -> (MW - 15/10/21) When the patient ID is found in the DB, the function PopulatePatientData() is called and converts all those array points into the patientX variables, so just modify those.
* We then write into their status positive or negative depending what they chose (1 or 2)
*   -> (MW - 15/10/21) Now done automatically when the user selects 1 or 2 for positive or negative.
* If they were positive, then we get their input of visitedLocations
*   -> (MW - 15/10/21) THIS IS WHAT NEEDS WORK. Also need time and date of visit!
* So far I have just appended it to the database, duplicates arent checked at this stage. 
* Things to fix:
* - menu option when input is a char it still continues
* 
* (MW - 15/10/21)
* Left a bunch of reply comments above.
* Hopefully the bugs are gone now.
* Just need to add all that functionalilty required when the patient states they returned a positive test then I think its good.
* 
*/
void UpdateTestStatus()
{
    int interuptCount(0);
    bool allowContinue(false), patientMatch(false), breakSwitch(false), atHighRiskLoc(false), brokeIsolation(false);
    //PATIENT DB VARS
    PatientDataVaribles tempPatientData;

    while (!allowContinue)
    {
        // Get patient id from user
        cout << "\nEnter your patient ID (numbers only, no spaces): ";
        while (!(cin >> tempPatientData.patientID)) // Prevents invalid inputs like letters, etc - MW
        {
            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n\nEnter your patient ID (numbers only, no spaces): ";
        }

        // Open the patient DB
        ifstream ifilePatientDB;
        ifilePatientDB.open("patientDB.txt");
        if (ifilePatientDB.fail())
        {
            cout << "\nPatient Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
            cout << "\nReturning to main menu.\n" << endl;
            PressEnterToContinue();
            return;
        }

        //Whilst the patient DB file is open
        if (ifilePatientDB.is_open())
        {
            // Creat a temp patient DB to store new data
            ofstream ofilePatientDBTemp;
            ofilePatientDBTemp.open("patientDBTemp.txt");

            string getRowLine, getRowVar;
            vector<string> tempDataRow;
            int compareID;

            getline(ifilePatientDB, getRowLine); // First row redundant - Add to temp DB
            ofilePatientDBTemp << getRowLine << endl;

            while (getline(ifilePatientDB, getRowLine))
            {
                if (!getRowLine.empty())
                {
                    tempDataRow.clear(); // Memory Management - Clears previous line get

                    stringstream ss(getRowLine); // Splits Row into "Columns" (RowVar)

                    while (getline(ss, getRowVar, ','))
                    {
                        tempDataRow.push_back(getRowVar);
                    }

                    compareID = stoi(tempDataRow[PATIENT_ID_ARRAY_LOC]);

                    // !!!!!! - This is where patient data is updated IFF a match is found
                    if (compareID == tempPatientData.patientID)
                    {
                        patientMatch = true;

                        // Store the current patients data ready to modify
                        PopulatePatientDataVars(tempDataRow,
                            tempPatientData.patientID,
                            tempPatientData.patientFirstName, tempPatientData.patientLastName, tempPatientData.patientAddress, tempPatientData.patientLocationVisited,
                            tempPatientData.patientDOB, tempPatientData.patientDateVisited, tempPatientData.patientTimeVisited, tempPatientData.patientOverseasTravel, tempPatientData.patientTestResult, tempPatientData.patientStatus);

                        cout << "\nHello, " << tempPatientData.patientFirstName << " " << tempPatientData.patientLastName << "," << endl;

                        // Check if test was pending or not and just ask if patient wants to continue if they werent recomended a test
                        if (tempPatientData.patientTestResult == "Not Recomended")
                        {
                            cout << "You were not recomended to get a COVID test.\nDid you still want to continue? ('Yes' or 'No'): ";
                            string answer;
                            cin.ignore();
                            while (!CheckYesNoValid(answer))
                            {
                                if (CheckInterupt(interuptCount))
                                {
                                    ifilePatientDB.close();
                                    ofilePatientDBTemp.close();
                                    remove("patientDBTemp.txt");
                                    PressEnterToContinue();
                                    return;
                                }
                            }
                            if (!regex_match(answer, CORRECT_YES_FORMAT))
                            {
                                ifilePatientDB.close();
                                ofilePatientDBTemp.close();
                                remove("patientDBTemp.txt");
                                cout << "\nNow returning you to main menu." << endl;
                                PressEnterToContinue();
                                return;
                            }
                        }

                        //get test status to be updated
                        cout << "\nWhat was your test result?" << endl;
                        cout << "Enter 1 (Positive), 2 (Negative), or 3 (Not Sure): ";

                        int selection(0);
                        while (!breakSwitch)
                        {
                            while (!(cin >> selection))
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "\n\nInvalid input.\nEnter 1 (Positive), 2 (Negative), or 3 (Not Sure): ";
                            }
                            switch (selection)
                            {
                            case 1:
                                breakSwitch = true;
                                //update this patient is positive in the db
                                tempPatientData.patientTestResult = "Positive";
                                break;

                            case 2:
                                breakSwitch = true;
                                //update this patient is negative in the db
                                tempPatientData.patientTestResult = "Negative";
                                break;

                            case 3:
                                breakSwitch = true;
                                //Exit
                                ifilePatientDB.close();
                                ofilePatientDBTemp.close();
                                remove("patientDBTemp.txt");
                                cout << "\nPlease come back when you know your test result.\nNow returning you to main menu." << endl;
                                PressEnterToContinue();
                                return;

                            default:
                                cout << "Unknown selection, please try again.\n" << endl;
                            }
                        }
                        // TEST RESULT POSITIVE: ADD STUFF HERE LIKE LOC VISTED, DATE VISITED, TIME VISITED, ETC
                        if (tempPatientData.patientTestResult == "Positive")
                        {
                            // LOAD LIST OF CURRENT HIGH RISK LOCS SO PATIENT CAN ADD NEW ONE OR NOT
                            ifstream ifileHighRiskLocDB;
                            ifileHighRiskLocDB.open("highRiskLocationsDB.txt");
                            if (ifileHighRiskLocDB.fail())
                            {
                                cout << "\n\nHigh Risk Location Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
                                cout << "\nDuplicate High Risk Location might be added to database\n\n" << endl;
                            }

                            if (ifileHighRiskLocDB.is_open())
                            {
                                cout << "\nThe following locations are already high risk:" << endl;
                                string getRowLine, atLocationAnswer;
                                cin.ignore();
                                while (getline(ifileHighRiskLocDB, getRowLine))
                                {
                                    if (!getRowLine.empty())
                                    {
                                        cout << "Have you recently visited this location -> ";
                                        cout << getRowLine;
                                        cout << " (yes or no)?: ";
                                        interuptCount = 0;
                                        while (!CheckYesNoValid(atLocationAnswer))
                                        {
                                            if (CheckInterupt(interuptCount))
                                            {
                                                ifilePatientDB.close();
                                                ofilePatientDBTemp.close();
                                                remove("patientDBTemp.txt");
                                                PressEnterToContinue();
                                                return;
                                            }
                                        }
                                        if (regex_match(atLocationAnswer, CORRECT_YES_FORMAT))
                                        {
                                            atHighRiskLoc = true;
                                            strcpy_s(tempPatientData.patientLocationVisited, getRowLine.c_str());
                                            break;
                                        }
                                    }
                                }
                            }
                            ifileHighRiskLocDB.close();

                            // Get new high risk location from patient
                            if (!atHighRiskLoc)
                            {
                                cout << "\nHave you visited another location / broke isolation?";
                                cout << " (Yes or No): ";
                                string answer;
                                interuptCount = 0;
                                while (!CheckYesNoValid(answer))
                                {
                                    if (CheckInterupt(interuptCount))
                                    {
                                        ifilePatientDB.close();
                                        ofilePatientDBTemp.close();
                                        remove("patientDBTemp.txt");
                                        PressEnterToContinue();
                                        return;
                                    }
                                }
                                if (regex_match(answer, CORRECT_YES_FORMAT))
                                {
                                    brokeIsolation = true;
                                }

                                if (brokeIsolation)
                                {
                                    cout << "\nEnter the name or address of the location you recently visited: ";
                                    interuptCount = 0;
                                    while (!CheckAddressValid(tempPatientData.patientLocationVisited))
                                    {
                                        if (CheckInterupt(interuptCount))
                                        {
                                            ifilePatientDB.close();
                                            ofilePatientDBTemp.close();
                                            remove("patientDBTemp.txt");
                                            PressEnterToContinue();
                                            return;
                                        }
                                    }
                                }
                            }

                            // Get date and time of location visit IFF required
                            if (atHighRiskLoc || brokeIsolation)
                            {
                                cout << "\nWhat date did you visit this location? (format: dd/mm/yyyy): ";
                                interuptCount = 0;
                                while (!CheckDateValid(tempPatientData.patientDateVisited))
                                {
                                    cin.clear();
                                    if (CheckInterupt(interuptCount))
                                    {
                                        ifilePatientDB.close();
                                        ofilePatientDBTemp.close();
                                        remove("patientDBTemp.txt");
                                        PressEnterToContinue();
                                        return;
                                    }
                                }

                                cout << "\nWhat time did you visit this location? (format: hh:mm [am|pm]): ";
                                interuptCount = 0;
                                while (!CheckTimeValid(tempPatientData.patientTimeVisited))
                                {
                                    if (CheckInterupt(interuptCount))
                                    {
                                        ifilePatientDB.close();
                                        ofilePatientDBTemp.close();
                                        remove("patientDBTemp.txt");
                                        PressEnterToContinue();
                                        return;
                                    }
                                }
                            }

                            // IF THE PATIENTS ADDS A NEW HIGH RISK LOCATION, ADD JUST THAT VAR TO THE HIGH RISK DB TOO
                            if (brokeIsolation)
                            {
                                ofstream ofileHighRiskLocDB;
                                ofileHighRiskLocDB.open("highRiskLocationsDB.txt", ios::app);
                                ofileHighRiskLocDB << endl; // Enter data on new line
                                ofileHighRiskLocDB << tempPatientData.patientLocationVisited;
                                ofileHighRiskLocDB.close();
                            }

                        }
                        // Save to patient DB
                        SaveNewPatientData(ofilePatientDBTemp,
                            tempPatientData.patientID, tempPatientData.patientFirstName, tempPatientData.patientLastName, tempPatientData.patientAddress, tempPatientData.patientLocationVisited,
                            tempPatientData.patientDOB, tempPatientData.patientDateVisited, tempPatientData.patientTimeVisited, tempPatientData.patientOverseasTravel, tempPatientData.patientTestResult, tempPatientData.patientStatus);
                    }
                    // !!!!!! - This is where the remaining lines of data are transfered to the temp file
                    else
                    {
                        ofilePatientDBTemp << getRowLine << endl;
                    }
                }
            }
            if (patientMatch)
            {
                // Make temp file the new DB
                allowContinue = true;
                ifilePatientDB.close();
                ofilePatientDBTemp.close();

                remove("patientDB.txt"); //removing the previous database, then renaming the newly written and changing its name to replace the old.
                rename("patientDBtemp.txt", "patientDB.txt"); // this must be changed if it works to "patientDB.txt"
                cout << "\nYou've successfully updated the database." << endl;

                PressEnterToContinue();

            }
            else
            {
                // Disregard temp file and tell user that the patient ID does not exist in the DB (try again?)

                ifilePatientDB.close();
                ofilePatientDBTemp.close();
                remove("patientDBTemp.txt");
                cout << "\n[] - The database is empty." << endl; // As required in PDF

                // TELL USER / TRY A NEW SEARCH????
                int selection(0);
                cout << "\nThe patient ID " << tempPatientData.patientID << " does not exist in the database.\nPlease enter the number of the option you wish to select.\n1: Try again\n2: Return to main menu" << endl;
                cout << "\n>> ";
                interuptCount = 0;
                while (selection != 1)
                {
                    if (CheckInterupt(interuptCount)) { ifilePatientDB.close(); PressEnterToContinue(); return; }
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
                        break;

                    case 2:
                        PressEnterToContinue();
                        return;

                    default:
                        cout << "Unknown selection, please try again.\n" << endl;
                    }
                }
            }
        }
    }
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
    int interuptCount(0);
    bool allowContinue(false), highRiskLocAnswer(false), symptomsAnswers[3]{false};
    //PATIENT DB VARS
    PatientDataVaribles newPatientData;

    while (!allowContinue)
    {
        cout << "\nEnter your patient ID (numbers only, no spaces): ";
        while (!(cin >> newPatientData.patientID)) // Prevents invalid inputs like letters, etc - MW
        {
            if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input.\n\nEnter your patient ID (numbers only, no spaces): ";
        }

        ifstream ifilePatientDB; // if patientID already exists then cant send to db
        ifilePatientDB.open("patientDB.txt");
        if (ifilePatientDB.fail())
        {
            cout << "\nPatient Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
            cout << "\nReturning to main menu.\n" << endl;
            PressEnterToContinue();
            return;
        }

        if (ifilePatientDB.is_open())
        {
            string getRowLine, getRowVar;
            vector<string> tempRow;
            int compareID;

            allowContinue = true; // Will allow function to continue so long as patient ID does not exist

            getline(ifilePatientDB, getRowLine); // First row redundant - Might be a better method (replace this if so)
            while (getline(ifilePatientDB, getRowLine))
            {
                if (!getRowLine.empty())
                {
                    tempRow.clear(); // Memory Management - Clears previous line get

                    stringstream ss(getRowLine); // Splits Row into "Columns" (RowVar)

                    while (getline(ss, getRowVar, ','))
                    {
                        tempRow.push_back(getRowVar);
                    }

                    compareID = stoi(tempRow[PATIENT_ID_ARRAY_LOC]);

                    if (compareID == newPatientData.patientID)
                    {
                        allowContinue = false;

                        int selection(0);
                        cout << "\nPatient ID already exists.\nPlease enter the number of the option you wish to select.\n1: Try again\n2: Return to main menu" << endl;
                        cout << "\n>> ";
                        interuptCount = 0;
                        while (selection != 1)
                        {
                            if (CheckInterupt(interuptCount)) { ifilePatientDB.close(); return; }
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
                                ifilePatientDB.close();
                                break;

                            case 2:
                                ifilePatientDB.close();
                                PressEnterToContinue();
                                return;

                            default:
                                cout << "Unknown selection, please try again.\n" << endl;
                            }
                        }
                    }
                }
            }
        }
        ifilePatientDB.close();
    }

    // New patient - Allow details to be entered and then store data on a new line of the patient DB.
    cout << "\nPlease enter your first name (letters only, no spaces): ";
    cin.ignore();
    interuptCount = 0;
    while (!CheckCharArrayValid(newPatientData.patientFirstName))
    {
        if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
        cout << "Please try again (letters only, no spaces): ";
    }


    cout << "\nPlease enter your last name (letters only, no spaces): ";
    interuptCount = 0;
    while (!CheckCharArrayValid(newPatientData.patientLastName))
    {
        if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
        cout << "Please try again (letters only, no spaces): ";
    }

    cout << "\nWhat is your date of birth (format: dd/mm/yyyy): ";
    interuptCount = 0;
    while (!CheckDateValid(newPatientData.patientDOB))
    {
        if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
    }

    cout << "\nPlease enter your address (no commas): ";
    interuptCount = 0;
    while (!CheckAddressValid(newPatientData.patientAddress))
    {
        if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
    }

    cout << "\nHave you travelled overseas in the last 6 months (yes or no)?: ";
    interuptCount = 0;
    while (!CheckYesNoValid(newPatientData.patientOverseasTravel))
    {
        if (CheckInterupt(interuptCount)) { PressEnterToContinue(); return; }
    }
    if (regex_match(newPatientData.patientOverseasTravel, CORRECT_YES_FORMAT))
    {
        newPatientData.patientOverseasTravel = "Yes";
    }
    else
    {
        newPatientData.patientOverseasTravel = "No";
    }

    ifstream ifileHighRiskLocDB;
    ifileHighRiskLocDB.open("highRiskLocationsDB.txt");
    if (ifileHighRiskLocDB.fail())
    {
        cout << "\nHigh Risk Location Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
        cout << "\nA test can still be recomended, but it will be less accurate.\n" << endl;
    }

    if (ifileHighRiskLocDB.is_open())
    {
        string getRowLine, atLocationAnswer;

        while (getline(ifileHighRiskLocDB, getRowLine))
        {
            cout << "\nHave you recently visited this location -> ";
            cout << getRowLine;
            cout << " (yes or no)?: ";
            interuptCount = 0;
            while (!CheckYesNoValid(atLocationAnswer))
            {
                if (CheckInterupt(interuptCount)) { ifileHighRiskLocDB.close(); PressEnterToContinue(); return; }
            }
            if (regex_match(atLocationAnswer, CORRECT_YES_FORMAT))
            {
                highRiskLocAnswer = true;
                break;
            }
        }
    }
    ifileHighRiskLocDB.close();


    ifstream ifileSymptomsDB;
    ifileSymptomsDB.open("symptomsDB.txt");
    if (ifileSymptomsDB.fail())
    {
        cout << "\nSymptoms Database Missing!\nPlease contact the application administrator on 555-123-456" << endl;
        cout << "\nA test can not be recomended at this stage.\n" << endl;
    }

    if (ifileSymptomsDB.is_open())
    {
        string getRowLine, symptomsAnswer;
        int count = 0;

        while (getline(ifileSymptomsDB, getRowLine) && count < SYMPTOMS_ARRAY_LENGTH)
        {
            if (getRowLine.empty())
            {
                ifileSymptomsDB.close();
                cout << "\nUnable to recommend COVID Test - required data missing" << endl; // As required - MW
                PressEnterToContinue();
                return;
            }
            cout << "\nHave you had any of these symptoms -> ";
            cout << getRowLine;
            cout << " (yes or no)?: ";
            interuptCount = 0;
            while (!CheckYesNoValid(symptomsAnswer))
            {
                if (CheckInterupt(interuptCount)) { ifileSymptomsDB.close(); return; }
            }
            if (regex_match(symptomsAnswer, CORRECT_YES_FORMAT))
            {
                symptomsAnswers[count] = true;
            }
            count++;
        }
    }
    ifileSymptomsDB.close();

    // No symptoms, no high risk locations
    if (!highRiskLocAnswer && !symptomsAnswers[2])
    {
        cout << "\nBased on your answers, this program does NOT recommend need a COVID test!" << endl;
        if (!symptomsAnswers[0] && !symptomsAnswers[1])
        {
            cout << "You are highly likely to be free of covid!" << endl;
        }
        if (symptomsAnswers[0] || symptomsAnswers[1])
        {
            cout << "However, it is recomended you should still isolate yourself at home for 14 days!" << endl;
        }
        newPatientData.patientTestResult = "Not Recomended";
    }
    // Either high risk symptoms, high risk location, or both
    else
    {
        cout << "\n\n-----------------------------------------------------------------------------" << endl;
        cout << "\n\nBased on your answers, this program recommends that you DO need a COVID test!" << endl;
        if (symptomsAnswers[2])
        {
            if (symptomsAnswers[0] || symptomsAnswers[1])
            {
                cout << "Please contact you local GP and advise you have many symptoms (including sever ones) so that they can best direct you!" << endl;
            }
            else
            {
                cout << "Please contact you local GP and advise you have sever symptoms so that they can bes direct you!" << endl;
            }
        }
        else
        {
            if (!symptomsAnswers[0] && !symptomsAnswers[1])
            {
                cout << "Although you show no signs of infection, it is advised you maintain social distance!" << endl;
            }
            else
            {
                cout << "You show some signs of infection, it is advised you maintain social distance!" << endl;
            }
        }
        newPatientData.patientTestResult = "Recomended (Pending)";
    }

    // Save to patient DB
    ofstream ofilePatientDB;
    ofilePatientDB.open("patientDB.txt", ios::app);
    ofilePatientDB << endl;
    SaveNewPatientData(ofilePatientDB,
        newPatientData.patientID, newPatientData.patientFirstName, newPatientData.patientLastName, newPatientData.patientAddress, newPatientData.patientLocationVisited,
        newPatientData.patientDOB, newPatientData.patientDateVisited, newPatientData.patientTimeVisited, newPatientData.patientOverseasTravel, newPatientData.patientTestResult, newPatientData.patientStatus);

    // ONE FINAL MESSAGE TO SAY USER INFO NOW STORED IN DB / PLEASE RETURN AFTER TEST AND SELCT 2 IF TEST WAS RECOMENDED ETC
    cout << "\nYour patient information has been stored in the database!\nIf a test was recomended, please return with your result and select OPTION 2." << endl;

    PressEnterToContinue();

    ofilePatientDB.close();
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
        cout << "\nPlease enter the number of the option you wish to select." << endl;
        cout << "\n1: Enter your details for COVID-Test Recommendation" << endl;
        cout << "2: Submit your Covid test status & Update the location database" << endl;
        cout << "3: Display the updated location (High Risk for COVID)" << endl;
        cout << "4: Update COVID Patient Details" << endl;
        cout << "5: Display the COVID Positive patient details" << endl;
        cout << "6: Quit" << endl;
        cout << "\n>> ";
        while (!(cin >> selection)) // Prevents invalid inputs like letters, etc - MW
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please try again: ";
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
                cout << "\nUnknown selection, please try again: ";
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

    cout << "\nWelcome" << endl;
    DisplayMenu();
    
    return 0; 
} 




