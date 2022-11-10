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
void Karp_Rabin(const char* file_contents, const char* pattern, int n, int m);
void Horspool(const char* file_contents, const char* pattern, int n, int m);

int main() {

    cout << "Press S for search or Q for quit" << endl;
    getline(cin, command);

    while (command == "S"){

        cout << "Please specify input text file name: ";
        getline(cin, filename);

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
        getline(cin, pattern);
        const char *fileCstr = file_contents.c_str();
        const char *patternCstr = pattern.c_str();
        int m = file_contents.length();
        int n = pattern.length();
        
        Karp_Rabin(fileCstr, patternCstr, n, m);
        Horspool(fileCstr, patternCstr, n, m);
        KMP(fileCstr, patternCstr, m, n);
        
        
        

        cout << "Press S to search for another word, or Q to quit: ";
        getline(cin, command);

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
    cout << "Number of occurrences in the text is: " << kmpmatches << " - " << endl;
    cout << "Number of Comparisons: " << kmpcomparisons << " - " << endl;
    cout << "Time: " << t1.count() << " milliseconds" << " - " << endl;
}

void Karp_Rabin(const char* file_contents, const char* pattern, int m, int n){
    int q = 128;
    int x = 11;
    int x_m = 1;
    int hash_pattern = 0;
    int hash_file_contents = 0;

    int krmatches = 0;
    int krcomparisons = 0;
    int krspurious_hits = 0;    

    auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN
    for(int i = 0; i < m-1; ++i)
        x_m = (x_m*x)%q;

    for(int i = 0; i < m; ++i){
        hash_pattern = (hash_pattern*x + pattern[i]) % q;
        hash_file_contents = (hash_file_contents*x + file_contents[i]) % q;
    }

    for(int i = 0; i < n-m+1; ++i){
        krcomparisons++;
        if(hash_pattern == hash_file_contents){
            for(int j = 0; j < m; ++j){
                if(pattern[j] != file_contents[i+j]){
                    break;
                }
                krmatches++;
            }
            krspurious_hits++;

        }
        if(i < n-m){
            hash_file_contents = (x*(hash_file_contents - file_contents[i]*x_m) + file_contents[i+m]) % q;
            if(hash_file_contents < 0)
                hash_file_contents += q;
        }
    }
    auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff); // time step 3; CALCULATE

    cout << "Karp Rabin: ";
    cout << "Number of occurrences in the text is: " << krmatches << " - " << endl;
    cout << "Number of Comparisons: " << krcomparisons << " - " << endl;
    cout << "Time: " << t1.count() << " milliseconds" << " - " << endl;
    cout << "Number of spurious hits: " << krspurious_hits << endl;
}

void Horspool(const char* file_contents, const char* pattern, int n, int m){
    int p = n;
    int t = m;
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
    cout << "Number of occurrences in the text is: " << hmatches << " - " << endl;
    cout << "Number of Comparisons: " << hcomparisons << " - " << endl;
    cout << "Time: " << t1.count() << " milliseconds" << endl;
}