
#include <iostream> 
#include <fstream> 
#include <string>
        
using namespace std; 

int patientID;
string name;
int doB;
string address;
string visitedLocation;
int date;
string overseasTravel;
string covidTest;
string status;

fstream myfile; 

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

}

void DisplayPositivePatients()
{

}

void CovidTestRecommendationDetails()
{

}
void UpdateTestStatus()
{
    int var;
    cout << "Enter your covid test status:";
    cout << "Enter 1 for positive.\nEnter 2 for Negative.";
    cin >> var;
    if(var == 1)
    {
            
    }
    else if(var == 2)
    {

    }
    else
    {
        
    }
}

void DisplayMenu()
{
    int selection;
    while(selection != 6)
    {
        cout << "Enter your details for COVID-Test Recommendation";
        cout << "Submit your Covid test status & Update the location database";
        cout << "Display the updated location (High Risk for COVID)";
        cout << "Update COVID Patient Details";
        cout << "Display the COVID Positive patient details";
        cout << "Quit";
        cout << "Unknown selection, please try again";
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
            
            }
        }
  
    } 
    cout << "Goodbye";
}


int main () 
{ 
    CreateDatabases();
    DisplayMenu();
    
    return 0; 
} 



/*
im goiung to create a long piece of code just to set up the databse info
then task 2 pulls the information from it and asks the user.

patient id  1
name        John
dob         20/11/1960

*/
