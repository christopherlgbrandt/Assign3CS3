
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono; 



string command, filename, pattern;

void Karp_Rabin(const char* file_contents, const char* pattern, int n, int m);
void Horspool(const char* file_contents, const char* pattern, int n, int m);
void KMP(const char* file_contents, const char* pattern, int m, int n);

int main() {

    cout << "Press S for search or Q for quit" << endl;
    getline(cin, command);

    while (command == "S"){

        cout << "Please specify input text file name: ";
        getline(cin, filename);

        // read the file and time it
        auto start = std::chrono::high_resolution_clock::now();
        ifstream fin;
        int file_length= 0;
        char *file_contents;
        fin.open(filename);
        if (!fin.good())
        {
            cout << "Error opening file." << endl;
            return -1;
        }
        fin.seekg(0, ios::end);
        file_length = fin.tellg();
        //getting file length
        //char *buffer = new(nothrow) char[file_length]; 
        //buffer = NULL;
        file_contents = (char *)malloc(file_length+1);
        fin.seekg(0, ios::beg);
        //reset to beginning of file to begin file read
        fin.read(file_contents, file_length);
        fin.close();
        auto diff = std::chrono::high_resolution_clock::now() - start;
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
        cout << "Text read! Time to read: " << t1.count()  << " nanoseconds" << endl;

        cout << "Please specify pattern to search for: ";
        getline(cin, pattern);
        
        const char *patternCstr = pattern.c_str();
        
        int n = pattern.length();
        
        KMP(file_contents, patternCstr, file_length, n); //3       
        Karp_Rabin(file_contents, patternCstr, n, file_length); //1
        Horspool(file_contents, patternCstr, n, file_length); //2

    
        cout << "Press S to search for another word, or Q to quit: ";
        getline(cin, command);

        if (command == "Q"){
        cout << "Goodbye.";
        return 0;
        }
    }

    return 0;
}

void KMP(const char* file_contents, const char* pattern, int m, int n){
    int kmpmatches = 0;
    int kmpcomparisons = 0;
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

    auto start = std::chrono::high_resolution_clock::now();
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
        if (file_contents[i] == pattern[j])
        {
            if(++j == n){
                kmpmatches++;
            }
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
    int d = 256;
    int p = 0;
    int t = 0; 
    int h = 1;
    int j;
    int q = INT32_MAX;
    int krmatches = 0;
    int krcomparisons = 0;
    auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN 
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + file_contents[i]) % q;
    }
    for (int i = 0; i <= n - m; i++) {
        krcomparisons++;
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (file_contents[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m)
                krmatches++;
        }
 
        if (i < n - m) {
            t = (d * (t - file_contents[i] * h) + file_contents[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    } 
    auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff); // time step 3; CALCULATE
    cout << "Karp Rabin: ";
    cout << "Number of occurrences in the text is: " << krmatches << " - " << endl;
    cout << "Number of Comparisons: " << krcomparisons << " - " << endl;
    cout << "Time: " << t1.count() << " milliseconds" << " - " << endl;
}

void Horspool(const char* file_contents, const char* pattern, int n, int m){
    const int noChars = 256;
    int hmatches = 0;
    int hcomparisons = 0;
    int badchar[noChars];
    int i;
    int s = 0;
    //Iniitializing badchar array to -1
    for (i = 0; i < noChars; i++)
    {
        badchar[i] = -1;
    }

    //Fill in values
    for (i = 0; i < n; i++)
    {
        badchar[(int) pattern[i]] = i;
    }
    auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN
    while(s <= (m-n))
    {
        int j = n-1;
        hcomparisons++;
        while(j >= 0 && pattern[j] == file_contents[s + j])
        {
            j--;
            
        }

        if (j < 0)
        {
            hmatches++;
            s += (s + m < n)? m-badchar[file_contents[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badchar[file_contents[s + j]]);
        }
    }


    

    auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff); // time step 3; CALCULATE

    cout << "Horspool: ";
    cout << "Number of occurrences in the text is: " << hmatches << " - " << endl;
    cout << "Number of Comparisons: " << hcomparisons << " - " << endl;
    cout << "Time: " << t1.count() << " milliseconds" << endl;
}
