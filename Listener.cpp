#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

string buildCommand(string line);
void executeCommand(string newLine);

int main(int argc, char* argv[]) {
    ifstream cmdFile("cmd.txt");
    string line;
    string newLine;

    if(cmdFile.is_open()) {
		while(cmdFile.good()) {
            getline(cmdFile, line);
            cout << line << endl;
	    		newLine = buildCommand(line);
	    		cout << newLine << endl;
	    		executeCommand(newLine);
		}
		cmdFile.close();
    	}
    else {
		cout << "Cannot open command file.\n";
    }

    return 0;
}

string buildCommand(string line) {
    string command;

	if(line == "forward") {
		cout << "moving forward..." << endl;
		command = "rostopic pub /turtle1/command_velocity turtlesim/Velocity -- 2.0 0.0";
	}
	else if(line == "left") {
		cout << "moving left..." << endl;
		command = "rostopic pub /turtle1/command_velocity turtlesim/Velocity -- 0.0 1.0";
	}
	else if(line == "right") {
		cout << "moving right..." << endl;
		command = "rostopic pub /turtle1/command_velocity turtlesim/Velocity -- 0.0 -1.0";
	}
	else if(line == "quit") {
		cout << "quitting..." << endl;
		return "";
	}
	else {
		cout << "Not sure what " << line << " means..." << endl;
	}

    return command;
}

void executeCommand(string command) {
    cout << "Executing " << command << endl;
    char *holder = new char[command.size()+1];
    holder[command.size()] = 0;
    memcpy(holder, command.c_str(), command.size());
    system(holder);
}

