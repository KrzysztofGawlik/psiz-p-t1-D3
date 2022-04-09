#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void createLog(string message){
    fstream logFile;
    logFile.open("log.txt", ios::app);
    time_t t = time(0);
    string dt = ctime(&t);
    logFile << endl << dt.substr(0, dt.length()-1) << " : " << message;
    logFile.close();
}

int main(int argc, char** argv){

    if(argc != 3) {
        createLog("Provided wrong number of arguments (" + to_string(argc-1) + ") - required: 2.");
        return 0;
    }

    fstream file_A, file_B;
    file_A.open(argv[1]);
    file_B.open(argv[2]);
    if(!file_A.is_open() || !file_B.is_open()){
        createLog("Could not open at least one of provided files.");
        return 0;
    } else {
        createLog((string) "Successfully opened two files: 1) " + argv[1] + " 2) " + argv[2]);
    }

    file_A.close();
    file_B.close();
    createLog("Closed both files.");

    return 0;
}