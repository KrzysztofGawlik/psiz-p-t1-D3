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
    createLog("Converting file content into bits...");
    vector<vector<char>> sequenceVector;
    while(!file.eof()){
        string byte;
        vector<char> byteVector;
        int charCode = file.get();
        int i = 0;

        if(charCode != -1){
            byte = bitset<8>(charCode).to_string();

            for(int bit = 0; bit < 8; bit++){
                byteVector.push_back(byte[bit]);
            }
            sequenceVector.push_back(byteVector);
            i++;
        }
    }
    createLog("Conversion finished.");
    return sequenceVector;
}

int makeComparison(vector<vector<char>> seqA, vector<vector<char>> seqB){
    createLog("Analyzing bits sequences...");
    vector<vector<char>> tmp;
    int diffs = 0;
    int size_A = seqA.size();
    int size_B = seqB.size();
    // seqA always shorter or equal
    if(size_A > size_B){
        tmp = seqA;
        seqA = seqB;
        seqB = tmp;
    }
    for(int i = 0; i < size_A; i++){
        for(int j = 0; j < 8; j++){
            if(seqA[i][j] != seqB[i][j]) diffs++;
        }
    }
    diffs += (size_B - size_A) * 8;
    createLog("Analysis finished.");
    return diffs;
}

int main(int argc, char** argv){
    createLog("APP start");

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

    int diff = makeComparison(byteSeqA, byteSeqB);

    file_A.close();
    createLog((string) "File " + argv[1] + " closed.");
    file_B.close();
    createLog((string) "File " + argv[2] + " closed.");

    createLog("APP stop");
    return 0;
}
