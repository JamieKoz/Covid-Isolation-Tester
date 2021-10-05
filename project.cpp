/*This is mostly outlining requirements and is pretty scuffed at the moment. Being mostly boilerplate code there may be some  
things youll find that may not make sense.

*/
#include <iostream> 
#include <fstream> 
#include <string>
        
using namespace std; 


// these variables are made to outline what may be needed from our req. and have left them global for the time being
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

// I was unsure how we should set up the db so this is a string to write a template to a file
// we could use an array, mysql queries, comma separated values, or json format. 
// this can basically be deleted when a database is setup 
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

void UpdatePatientDetails()
{
    //get by patientID or name
    cout << "Enter your address:"
    cin >> address;
    cout << "Have you travelled overseas in the last 6 months, Y/N?";
    cin >> overseasTravel;
    cout << "Please select your visited location from the High Risk COVID areas:"; // similar to above, possibly display the db of high risk locations and display options 1-10 
    cin >> visitedLocation;
    cout << "Status:" <<"1.Cured" << endl << "2.Dead";
    cin >> status; // to be fixed
}

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
    cout << "Enter your address:"
    cin >> address;
    cout << "Have you travelled overseas in the last 6 months, Y/N?";
    cin >> overseasTravel;
    cout << "Please select your symptoms:"; // could just make an if/switch statement for this one with options 1-3. eg. 1: (Low risk) Dry cough. 2: (Medium risk) Fever
    cin >> 
    cout << "Please select your visited location from the High Risk COVID areas:"; // similar to above, possibly display the db of high risk locations and display options 1-10 
    cin >> visitedLocation;

    //send variables to db

}
void UpdateTestStatus()
{
    int var;
    cout << "Enter your PatientID:";
    cin >> patientID;
    cout << "Enter your covid test status:";
    cin << status;
    cout << "Enter your visited location:";
    cin << visitedLocation;
    cout << "Enter 1 for positive.\nEnter 2 for Negative.";
    cin >> var;
    if(var == 1)
    {
        //update this patient is positive in the db
        //update location database of new high risk location

    }
    else if(var == 2)
    {
        //update this patient is positive in the db
    }
    else
    {
        cout << "Please select an option 1 or 2." << endl;
    }
}
// this is the main loop that the user navigates through. The respective choice calls the function which the user wants to perform.
// the methods within these choices need work 
void DisplayMenu()
{
    int selection;
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

// for testing purposes the database is created initially before calling the main loop
int main () 
{ 
    CreateDatabases();
    DisplayMenu();
    
    return 0; 
} 




