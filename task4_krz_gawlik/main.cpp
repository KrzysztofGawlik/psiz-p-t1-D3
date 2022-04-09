#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <bitset>
using namespace std;

void createLog(string message){
    fstream logFile;
    logFile.open("log.txt", ios::app);
    time_t t = time(0);
    string dt = ctime(&t);
    logFile << endl << dt.substr(0, dt.length()-1) << " : " << message;
    logFile.close();
}

vector<vector<char>> convertToVector(fstream &file){
    vector<vector<char>> sequenceVector;
    while(!file.eof()){
        string byte;
        vector<char> byteVector;
        int charCode = file.get();
        int i = 0;

        if(charCode != -1){
            byte = bitset<8>(charCode).to_string();
        }

        for(int bit = 0; bit < 8; bit++){
            byteVector.push_back(byte[bit]);
        }
        sequenceVector.push_back(byteVector);
        i++;
    }
    createLog("Converted file to bits");
    return sequenceVector;
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

    vector<vector<char>> byteSeqA = convertToVector(file_A);
    vector<vector<char>> byteSeqB = convertToVector(file_B);

    file_A.close();
    file_B.close();
    createLog("Closed both files.");

    return 0;
}