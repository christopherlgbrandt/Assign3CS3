<<<<<<< Updated upstream

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

    while (command == "S"){

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

        cout << "Press S to search for another word, or Q to quit: ";
        getline(std::cin, command);

        if (command == "Q"){
        cout << "Goodbye.";
        return 0;
        }
    }

    return 0;
}
=======

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono; 

ifstream file;
string command, filename, pattern, file_contents;

void KMP(const char* file_contents, const char* pattern, int m, int n);

int main() {

    cout << "Press S for search or Q for quit" << endl;
    getline(std::cin, command);

    while (command == "S"){

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
        const char *fileCstr = file_contents.c_str();
        const char *patternCstr = pattern.c_str();
        int m = file_contents.length();
        int n = pattern.length();
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
        */
        KMP(fileCstr, patternCstr, m, n);
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

void KMP(const char* file_contents, const char* pattern, int m, int n)
{
    int kmpmatches = 0;
    int kmpcomparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();
    if (*pattern == '\0' || n == 0) {
        printf("The pattern is null, or empty");
    }
 
    if (*file_contents == '\0' || n > m) {
        printf("The file is null, or the pattern is a larger length then the text");
    }
 
    int next[n + 1];
 
    for (int i = 0; i < n + 1; i++) {
        next[i] = 0;
    }
 
    for (int i = 1; i < n; i++)
    {
        int j = next[i + 1];
        while (j > 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }
 
        if (j > 0 || pattern[j] == pattern[i]) {
            next[i + 1] = j + 1;
        }
    }
 
    for (int i = 0, j = 0; i < m; i++)
    {
        kmpcomparisons++;
        if (*(file_contents + i) == *(pattern + j))
        {
            kmpmatches++;
        }
        else if (j > 0)
        {
            j = next[j];
            i--;    
        }
    }
    auto diff = std::chrono::high_resolution_clock::now() - start;
    auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
    cout << "KMP: ";
    cout << "Number of occurrences in the text is: " << kmpmatches << " - ";
    cout << "Number of Comparisons: " << kmpcomparisons << " - ";
    cout << "Time: " << t1.count() << "milliseconds" << " - ";
}

>>>>>>> Stashed changes
