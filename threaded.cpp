#include <iostream>
#include <thread>
#include <vector>
#include <chrono> // added for time measurement
using namespace std;

#define MAX 8

int matA[MAX][MAX], matB[MAX][MAX], matC[MAX][MAX], matD[MAX][MAX];

void multi(int n)
{
    int i = n; //i denotes row number of resultant matC

    for (int j = 0; j < MAX; j++)
      for (int k = 0; k < MAX; k++)
        matC[i][j] += matA[i][k] * matB[k][j];
}

void display(int x[MAX][MAX])
{
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << x[i][j] << "\t";
        cout << endl;
    }
}

int main()
{
    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }

    // Displaying matA & matB
    cout << endl << "Matrix A" << endl;
    display(matA);
    cout << endl << "Matrix B" << endl;
    display(matB);

    // multiplication without threads
    auto start1 = chrono::steady_clock::now(); // added for time measurement
    for(int i = 0; i < MAX; ++i)
        for(int j = 0; j < MAX; ++j)
            for(int k = 0; k < MAX; ++k)
            {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
    auto end1 = chrono::steady_clock::now(); // added for time measurement
    cout << endl << "Multiplication of A and B without threads" << endl;
    display(matD);
    cout << "Time taken without threads: " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() << " microseconds" << endl; // added for time measurement

    // multiplication with threads
    vector<thread> threads;
    auto start2 = chrono::steady_clock::now(); // added for time measurement
    for (int i = 0; i < MAX; i++) {
        threads.push_back(thread(multi, i));
    }
    for (auto &th : threads) {
        th.join();
    }
    auto end2 = chrono::steady_clock::now(); // added for time measurement
    cout << endl << "Multiplication of A and B with threads" << endl;
    display(matC);
    cout << "Time taken with threads: " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << " microseconds" << endl; // added for time measurement

    return 0;
}
