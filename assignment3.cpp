
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono; 

ifstream file;
string command, filename, pattern, file_contents;

int main() {

    cout << "Press S for search or Q for quit" << endl;
    getline(std::cin, command);

    if (command == "S"){

        cout << "Please specify input text file name: ";
        getline(std::cin, filename);

        // read the file and time it
        auto start = std::chrono::high_resolution_clock::now();
        file.open(filename);
        if (file.is_open()){
            stringstream buffer;
            buffer << file.rdbuf();
            file_contents = buffer.str();
        }
        auto diff = std::chrono::high_resolution_clock::now() - start;
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
        cout << "Text read! Time to read: " << t1.count()  << " nanoseconds" << endl;
        
        cout << "Please specify pattern to search for: ";
        getline(std::cin, pattern);


        /* Karp Rabin
        cout << "Karp Rabin: ";
        cout << "Number of occurrences in the text is: " << xxxx << " - ";
        cout << "Number of Comparisons: " << xxxx << " - ";
        cout << "Time: " << xxxx << "milliseconds" << " - ";
        cout << "Number of spurious hits: " << xxxx << endl;

        // Horspool
        cout << "Horspool: ";
        cout << "Number of occurrences in the text is: " << xxxx << " - ";
        cout << "Number of Comparisons: " << xxxx << " - ";
        cout << "Time: " << xxxx << "milliseconds" << " - ";

        // KMP
        cout << "KMP: ";
        cout << "Number of occurrences in the text is: " << xxxx << " - ";
        cout << "Number of Comparisons: " << xxxx << " - ";
        cout << "Time: " << xxxx << "milliseconds" << " - ";


        */
    }

    if (command == "Q"){
        cout << "Goodbye.";
        return 0;
    }

    else {
        cout << "Neither an S or a Q. Goodbye.";
        return 0;
    }

    return 0;
}