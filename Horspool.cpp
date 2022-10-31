
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono; // necessary for time check

ifstream file; // the ability to read a file 
string command, filename, pattern, file_contents;

void Horspool(string& file_contents, string& pattern){
    int p = pattern.length();
    int t = file_contents.length();
    int table[128];
    int hmatches = 0;
    int hcomparisons = 0;

    auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN
    for (int i = 0; i < 128; i++)
        table[i] = p;

    for (int j = 0; j < p -1; j++){
        table[int(pattern[j])] = p-j-1;
    }

    int k = p-1;

    while(k < t){
        int j = p-1;
        int i = k;
        hcomparisons++;

        while((j >= 0) && (file_contents[i] == pattern[j])){
            j--;
            i--;
            hmatches++;
        }
        if(j == -1){
            i++;
            break;
        }
        k += table[int(file_contents[k])];
    }

    auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff); // time step 3; CALCULATE

    cout << "Horspool: ";
    cout << "Number of occurrences in the text is: " << hmatches << " - ";
    cout << "Number of Comparisons: " << hcomparisons << " - ";
    cout << "Time: " << t1.count() << " milliseconds" << endl;
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
        Horspool(file_contents, pattern);
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