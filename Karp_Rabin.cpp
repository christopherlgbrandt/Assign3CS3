
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono; // necessary for time check

ifstream file; // the ability to read a file 
string command, filename, pattern, file_contents;

void Karp_Rabin(string& file_contents, string& pattern){
    int m = pattern.length();
    int n = file_contents.length();
    int q = 128;
    int x = 11;
    int x_m = 1;
    int hash_pattern = 0;
    int hash_file_contents = 0;

    int krmatches = 0;
    int krcomparisons = 0;


    auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN
    for(int i = 0; i < m-1; ++i)
        x_m = (x_m*x)%q;

    for(int i = 0; i < m; ++i){
        hash_pattern = (hash_pattern*x + pattern[i]) % q;
        hash_pattern = (hash_file_contents*x + file_contents[i]) % q;
    }

    for(int i = 0; i < n-m+1; ++i){
        krcomparisons++;
        if(hash_pattern == hash_file_contents){
            for(int j = 0; j < m; ++j){
                if(pattern[j] != file_contents[i+j]){
                    break;
                }
            }
            krmatches++;
        }
    }
    auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff); // time step 3; CALCULATE

    cout << "Karp Rabin: ";
    cout << "Number of occurrences in the text is: " << krmatches << " - ";
    cout << "Number of Comparisons: " << krcomparisons << " - ";
    cout << "Time: " << t1.count() << " milliseconds" << " - ";
    cout << "Number of spurious hits: " << "xxxx" << endl;
}


int main() {

    cout << "Press S for search or Q for quit" << endl;
    getline(std::cin, command);

    while (command == "S"){

        cout << "Please specify input text file name: ";
        getline(std::cin, filename);

        // read the file and time it
        auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN
        file.open(filename);
        if (file.is_open()){
            stringstream buffer;
            buffer << file.rdbuf();
            file_contents = buffer.str();
        }
        auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff); // time step 3; CALCULATE
        cout << "Text read! Time to read: " << t1.count()  << " nanoseconds" << endl;

        cout << "Please specify pattern to search for: ";
        getline(std::cin, pattern);


        // Karp Rabin
        Karp_Rabin(file_contents, pattern);


        /* Horspool
        cout << "Horspool: ";
        cout << "Number of occurrences in the text is: " << xxxx << " - ";
        cout << "Number of Comparisons: " << xxxx << " - ";
        cout << "Time: " << xxxx << "milliseconds" << " - ";
        */

        // KMP

        cout << "Press S to search for another word, or Q to quit: ";
        getline(std::cin, command);

        if (command == "Q"){
        cout << "Goodbye.";
        return 0;
        }
    }

    return 0;
}