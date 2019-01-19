#include "Menus.h"
#include "Utils.h"
#include "Randomizer.h"
#include "Algorithms.h"
#include <iomanip>



void initialInformation(){
	bool leaveprogram = false;
	do{
	cout << string(50, '\n');// clears the screen
	cout<<"Music Show - Random Distribution Generation"<<endl;
	int linesNumber = -1;
	int columnsNumber = -1;
	int peopleNumber = -1;
	int groupsNumber = -1;
	linesNumber = askForInput("Insert the number of lines ","Error: The number of lines must be a number between 1 and 30",1, 30, leaveprogram);
	if(linesNumber > 0)
		columnsNumber = askForInput("Insert the number of columns ","Error: The number of columns must be a number between 1 and 30",1, 30, leaveprogram);
	if(columnsNumber > 0)
		peopleNumber = askForInput("Insert the number of spectators ","Error: The number of spectators must be a number between 1 and "+to_string(linesNumber*columnsNumber),1, linesNumber * columnsNumber, leaveprogram);
	if(peopleNumber > 0)
		groupsNumber = askForInput("Insert the maximum number of groups ","Error: The number of groups must be a number between 0 and "+to_string(peopleNumber),1, peopleNumber, leaveprogram);

	if(groupsNumber >= 0){

	vector<vector<unsigned int>> distribution;
	generateMatrix(linesNumber, columnsNumber, peopleNumber, distribution);
	randomizeMatrix(distribution);
	vector<vector<unsigned int>> groups;
	randomizeGroups(groupsNumber, peopleNumber, groups);
	cout<<"Original Distribution:"<<endl;
	printMatrix(distribution);
	cout<<"\nGroups of Spectators:"<<endl;
	printGroups(groups);
	cout<<endl;
	chooseAlgorithm(distribution, groups, leaveprogram);
	}
	} while(! leaveprogram);
}

void chooseAlgorithm(vector<vector<unsigned int>> & distribution, vector<vector<unsigned int>> & groups, bool  & leaveprogram){
		bool backflag = false;
		do {
			bool errormessage = false;//If true will display an error message
				//cout << string(50, '\n');;// clears the screen
				cout << "Choose the algorithm to use in order to find the most suitable distribution "<< endl;
				if (errormessage) {
					cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
				}
				cout << "1: Simulated Annealing" << endl;
				cout << "2: Genetic Algorithms + Simulated Annealing" << endl;
				cout << "3: Genetic Algorithms" << endl;
				cout<< "4: Back"<<endl;
				cout << "5: Leave" << endl;
				cout << "Type the option number: ";
				string option;//option to be chosen by the user
				cin.clear();
				getline(cin, option);
				switch (convint(option))
				{
				case 1:
					simulatedAnnealing(distribution, groups);
					break;
				case 2:
					geneticAlgorithmSimulatedAnnealing(distribution, groups);
					break;
				case 3:
					geneticAlgorithm(distribution, groups);
					break;
				case 4:
					backflag = true;
					break;
				case 5:
					leaveprogram = true;//sets leaveprogram to true so that the program can end when it leaves this function
					break;
				default:
					errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated

			}
		} while (!leaveprogram && !backflag);

}

int askForInput(const string & askMessage, const string & errorMessage,int min, int max, bool & leaveprogram){
	int input;//variable that will be store the user input
	bool repeat = true;//this boolean will be set to true when the cycles that ask the user for the elements of the dates should be repeated
		//The following loop asks the user for the year of the date
	while (repeat) {
		cout << askMessage + " (press c to cancel and l to leave): ";
		string stringInput;//string that's going to be typed by the user
		cin.clear();
		getline(cin, stringInput);
		input = convint(stringInput);
		if (input >= min && input <= max)
				repeat = false;

		else if (stringInput == "c" )
			return -1;
		else if(stringInput == "l"){
			leaveprogram = true;
			return -1;
		}


		else {
			cout << errorMessage << endl;
		}
	}

	return input;
}


