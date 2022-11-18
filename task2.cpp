
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono; // necessary for time check

int main() {

    int graph[10][10];
    int temp = 100;
    int tempv = 0;
    int taskcomp = 0;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            graph[i][j] = 0;
        }
    }

    graph[0][1] = 6;
    graph[0][2] = 10;

    graph[1][0] = 6;
    graph[1][2] = 12;
    graph[1][3] = 11;
    graph[1][4] = 14;

    graph[2][0] = 10;
    graph[2][1] = 12;
    graph[2][3] = 12;
    graph[2][6] = 8;
    graph[2][7] = 16;

    graph[3][1] = 11;
    graph[3][2] = 12;
    graph[3][5] = 6;
    graph[3][6] = 3;

    graph[4][1] = 14;
    graph[4][5] = 4;
    graph[4][8] = 6;

    graph[5][3] = 6;
    graph[5][4] = 4;
    graph[5][8] = 12;

    graph[6][2] = 8;
    graph[6][3] = 3;
    graph[6][8] = 16;
    graph[6][9] = 6;

    graph[7][2] = 16;
    graph[7][9] = 8;

    graph[8][4] = 6;
    graph[8][5] = 12;
    graph[8][6] = 16;
    graph[8][9] = 13;

    graph[9][6] = 6;
    graph[9][7] = 8;
    graph[9][8] = 13;

    auto start = std::chrono::high_resolution_clock::now(); // time step 1; BEGIN
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(graph[i][j] < temp){
                temp = graph[i][j];
            }
            if(graph[i][j] > 0 && j > tempv){
                cout << "{" << i << ", " << j << "} " << graph[i][j] << endl;
                tempv++;
                graph[j][i] = 0;
            }
            taskcomp++;
        }
    }
    auto diff = std::chrono::high_resolution_clock::now() - start; // time step 2; END
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff); // time step 3; CALCULATE
    cout << "Time taken: " << t1.count() << " milliseconds" << endl;
    cout << "Number of comparisons: " << taskcomp << endl;

    getchar();
    getchar();

    return 0;
}