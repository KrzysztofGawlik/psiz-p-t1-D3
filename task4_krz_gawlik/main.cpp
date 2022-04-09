#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv){

    if(argc != 3) {
        cout << "You've provided wrong number of arguments (" << argc << ") - required: 2" << endl;
    } else {
        fstream file_A, file_B;
        try {
            file_A.open(argv[1]);
            file_B.open(argv[2]);
        } catch (exception e) {
            cout << "Could not open one of the files!" << endl;
            return 0;
        }
        cout << "Files opened!\n1) " << argv[1] << "\n2) " << argv[2] << endl;
    }

    return 0;
}