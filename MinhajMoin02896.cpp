// Name : Minhaj Ahmed Moin
// ID: hm02896
// OOP Assignment 1

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <windows.h>
#include <limits>

using namespace std;

void TimeDelay(int delay);      //This function should delay the execution to 3 second default, 0 sec min and 10 sec max
string ToUpperCase(string&);    //Converts a string to UpperCase. Also returns the string if required.
void read (int*);               //Reads a file and gets a pointer to the variable in main that holds the count of letters read
int edit ();                   //Creates and writes a new file

int main ()
{
    int countchar = 0; // Counts the number of Characters read so far
    string command;
    bool loopRunning = true;

    while (loopRunning)
    {
        system("CLS");
        cout << "Total Characters read so far = " << countchar << " " << endl << endl;

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "       Welcome to SimpleTextEdit!       " << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Type 'edit' to edit a Text File" << endl;
        cout << "Type 'read' to read a Text File" << endl;                 //The Main Menu
        cout << "Type 'exit' to exit the Program" << endl;
        cout << "Choose what you want to do" << endl << ">";
        getline(cin,command); //cin and getline don't work together, so we use getline in the entire program.
        ToUpperCase(command);
        if (command == "EDIT")       //If the user inputs 'edit' then the edit function will run
        {
            edit();
        }
        else  if (command == "READ") //If the user inputs 'read' then the read function will run
        {
            read(&countchar);
        }
        else if (command == "EXIT") //If the user inputs 'exit' the the main function will return, terminating the program.
        {
            return 0;
        }
        else //If the user enters and invalid command, this will be done.
        {
            cout << "ERROR!" << endl << "Please Enter a valid command!" << endl << endl;
            system("Pause");
        }
    }
    return 0;
}

void TimeDelay(int delay) //For the delay of 3 seconds for the execution
{
    cout << "Moving back to the Main Menu..." << endl;
    for (int i=delay;i>0;i--)
    {
        cout << i << ".";        //Shows a 3 second timer on the screen
        Sleep(1000);
    }
    cout << endl;

}

string ToUpperCase(string& text) //This function changes the string to uppercase, so whatever case the user inputs, all will be recognized by the program
{
    for (size_t i=0;i<text.size();i++)
    {
        if (islower(text[i]))
        {
            text.at(i) = toupper(text.at(i));
        }
    }
    return text;
}

void read (int* countchar) // The read function
{
    int line = 1;  //counts the number of lines that have been printed
    int line_num = 24; //the limit of 24 lines at which the program will ask for continuation
    string OutputLine; //variable which contains the contents of a line of the opened file
    string ContinueReading = "Y"; //Default line continuation variable
    char filename[50]; //name of the file to be opened. was char array but I was having problems with it so I changed it to string
    ifstream readfile; // the filestream object that will open the file.
    cout << endl << "Reading Mode" << endl << endl;
    cout << "Enter name of the file to read: "<< endl << ">";
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(filename,50); //get a line of 50 characters
    readfile.open(filename);
    if (!readfile.is_open()) cout << "\nFile Does Not Exist\n" << endl; //returns this if file doesn't exist
    else
    {
        while (getline(readfile, OutputLine)) //getline() works as a boolean in this context. if EOF is reached, it will return false.
        {
            if (line == line_num)
            {
                cout << "Do You want to Continue Reading the File? (y/n)"; //prompt for continuation of file reading after 24 lines
                cout << endl << ">";
                cin >> ContinueReading;
                ToUpperCase(ContinueReading);
                cout << ContinueReading;
                line_num+=24; // The prompt for continuation of reading of the file has to show up after every 24th line
            }
            if (ContinueReading == "Y")
            {
                cout << line << "> " << OutputLine << endl;
                line++; //increment the number of the current line
                *countchar += OutputLine.size(); //increments the total characters read by the number of characters in the line.
            }
            else
            {
                break;
            }
        }
    }
    readfile.close(); //closes the file after read operation
    system("PAUSE");
    TimeDelay(3);
}


int edit ()
{
    ofstream EditFile; //outputfile stream object for opening the file to be edited.
    string filename;
    string InputLine; //variable which will contain the current entered line which will then be entered to the file.
    int LineNum = 1; //variable which contains the current line number
    bool LoopRunning = true;

    cout << endl << "Editing Mode" << endl << endl;
    cout << "Enter the name of the file to edit:" << endl << '>';

    getline(cin,filename); // Will take a whole line from the user input and put it in the string variable named filename

    EditFile.open(filename,ios::trunc); // creates a new file and opens it for editing, if file exists, it overwrites the file

    cout << "Start Typing, Enter '/' or Press Ctrl+X to stop editing the file." << endl;

    while(LoopRunning)
    {
        cout << LineNum << "> ";
        getline(cin,InputLine); // Takes a line as input, delimited by the default \n character.
        if (InputLine == "/" || (InputLine[0]==char(24) && InputLine.length() == 1)) // If user inputs a '/' at the start of a line, editing will be stopped.
        {
            break;
        }
        EditFile << InputLine << endl;
        LineNum++;
    }
    cout << endl;
    EditFile.close();
    TimeDelay(3); // After finishing editing, a 3-second timer has to show up
    return 0;
}
