#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <bitset>
#include <tuple>
#include <chrono>
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
    long bytes = sequenceVector.size();
    auto mb = (float)bytes/1024/1024;
    createLog("Conversion finished: converted " + to_string(bytes) + " bytes ["+ to_string(mb) +" MB]");
    return sequenceVector;
}

tuple<int, int, float, long> makeComparison(vector<vector<char>> seqA, vector<vector<char>> seqB){
    createLog("Analyzing bits sequences... [clock start]");
    auto start = chrono::high_resolution_clock::now();
    vector<vector<char>> tmp;
    int diffs = 0, compared = 0;
    float ber = 0.;
    int size_A = seqA.size();
    int size_B = seqB.size();
    // seqA always shorter or equal
    if(size_A > size_B){
        tmp = seqA;
        seqA = seqB;
        seqB = tmp;
        size_A = seqA.size();
        size_B = seqB.size();
    }
    for(int i = 0; i < size_A; i++){
        for(int j = 0; j < 8; j++){
            if(seqA[i][j] != seqB[i][j]){
                diffs++;
            }
            compared++;
        }
    }
    diffs += (size_B - size_A) * 8;
    ber = float(diffs) / float(size_B * 8.) * 100.;
    auto stop = chrono::high_resolution_clock::now();
    createLog("Analysis finished. [clock stop]");
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    tuple<int, int, float, long> results = make_tuple(compared, diffs, ber, duration.count());
    return results;
}

int main(int argc, char** argv){
    createLog("*** APP start");

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

    tuple<int, int, float, long> results = makeComparison(byteSeqA, byteSeqB);
    string resultMsg = "*** RESULTS Compared bits: " + to_string(get<0>(results)) + 
                        "; Different bits: " + to_string(get<1>(results)) + 
                        "; BER: " + to_string(get<2>(results)) + "%" + 
                        "; Time: " + to_string(get<3>(results)) + " ms";
    createLog(resultMsg);
    cout << resultMsg << endl;

    file_A.close();
    createLog((string) "File " + argv[1] + " closed.");
    file_B.close();
    createLog((string) "File " + argv[2] + " closed.");

    createLog("*** APP stop");
    return 0;
}
