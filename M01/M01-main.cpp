/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/10/2025
Purpose: File I/O practice*/

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Participant{
    private:
        string firstName;
        string lastName;
        int age;
        string gender;
        int id;
    public:
        Participant(string firstName, string lastName, int age, string gender, int id);
        static void displayParticipants(vector<Participant> participants){
            for (int i = 0; i < participants.size(); i++){
                cout << "ID: " << participants[i].getId() << endl;
                cout << "Name: " << participants[i].getFirstName() << " " << participants[i].getLastName() << endl;
                cout << "Age: " << participants[i].getAge() << endl;
                cout << "Gender: " << participants[i].getGender() << endl;
                string studymor = participants[i].getStudyMor() ? "Yes" : "No";
                cout << "StudyMor: " << studymor << endl;
                cout << endl;
                cout << "**************************************************" << endl;
            }
        }
        /*GETTERS*/
        int getID(){
            return id;
        }
        string getFirstName(){
            return firstName;
        }
        string getLastName(){
            return lastName;
        }
        int getAge(){
            return age;
        }
        string getGender(){
            return gender;
        }
        int getId(){
            return id;
        }
        bool getStudyMor(){
            if (id % 2 == 0){
                return true;
            }
            else{
                return false;
            }
        }
};

/*CONSTRUCTOR*/
Participant::Participant(string firstName, string lastName, int age, string gender, int id) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->gender = gender;
    this->id = id;
}

int main(){
    /* Array of participants*/
    vector<Participant> participants;
    int id = 1;
    string gender;
    int age;
    string firstName;
    string lastName;
    /* Menu*/
    while (true){
        cout << "Welcome to the Westlake Research Hostpital StudyMor Study!" << endl;
        cout << "1. Add a New Participant" << endl;
        cout << "2. Collect Survey for Participant" << endl;
        cout << "3. Display Participants" << endl;
        cout << "4. Quit" << endl;
        cout << "Please enter a command to continue: ";
        int choice;
        cin >> choice;
        if (choice == 1){
            /* collect first name, last name, age, gender, and assign them an id in an array*/
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter gender: ";
            cin >> gender;
            /* Add the participant to the array*/
            Participant participant(firstName, lastName, age, gender, id);
            participants.push_back(participant);
            id++;
            cout << "Participant added successfully!" << endl;
        }
        else if (choice == 2){
            int participantChoice;
            cout << "Please choose the study participant: " << endl;
            Participant::displayParticipants(participants);
            cin >> participantChoice;
            Participant participant = participants[participantChoice - 1];
            string response1;
            string response2;
            string response3;
            string response4;
            string response5;
            cout << "Ask the participant the following questions and enter their responses." << endl;
            cout << "1. Did you have any headaches using StudyMor?" << endl;
            cin >> response1;
            cout << "2. Did you have any constipation using StudyMor?" << endl;
            cin >> response2;
            cout << "3. Did you experience any difficulty sleeping while using StudyMor?" << endl;
            cin >> response3;
            cout << "4. List any other potential side effects, you experienced using StudyMor." << endl;
            cin >> response4;
            cout << "5. Did you feel like you could study more using StudyMor?" << endl;
            cin >> response5;
            /*Add survey results to survey.dat*/
            ofstream surveyFile("survey.dat", ios::app);
            surveyFile << participant.getID() << "," << response1 << "," << response2 << "," << response3 << "," << response4 << "," << response5 << endl;
            surveyFile.close();
            cout << "Survey results added successfully to survey.dat!" << endl;
        }
        else if (choice == 3){
            Participant::displayParticipants(participants);
        }
        else if (choice == 4){
            cout << "Thank you for using the Westlake Research Hostpital StudyMor Study!" << endl;
            /*Add all participants to participant.dat*/
            ofstream participantFile("participant.dat", ios::app);
            for (int i = 0; i < participants.size(); i++){
                string studyMor = participants[i].getStudyMor() ? "Yes" : "No";
                participantFile << participants[i].getID() << "," << participants[i].getFirstName() << "," << participants[i].getLastName() << "," << participants[i].getAge() << "," << participants[i].getGender() << ", StudyMor: " << studyMor << endl;
            }
            participantFile.close();
            cout << "All participants added successfully to participant.dat!" << endl;
            return 0;
        }
    }
} 