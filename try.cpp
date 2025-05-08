#include <iostream>
using namespace std;

/**
 * Function to solve the 0/1 Knapsack problem using dynamic programming.
 *
 * @param W     Maximum capacity of the knapsack.
 * @param weight Array of weights of the items.
 * @param values  Array of values of the items.
 * @param n      Number of items.
 *
 * @return Maximum value that can be put in the knapsack.
 */
int knapsack_0_1(int W, int weight[], int values[], int n) {
    // Create a 2D array to store the maximum values for subproblems
    int** K = new int*[n + 1];
    for (int i = 0; i <= n; i++) {
        K[i] = new int[W + 1];
    }

    // Initialize the first row and column of the 2D array
    for (int j = 0; j <= W; j++) {
        K[0][j] = 0;
    }
    for (int i = 0; i <= n; i++) {
        K[i][0] = 0;
    }

    // Fill the 2D array using dynamic programming
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weight[i - 1] <= w) {
                K[i][w] = max(values[i - 1] + K[i - 1][w - weight[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    // Get the maximum value that can be put in the knapsack
    int maxValue = K[n][W];

    // // Deallocate memory to prevent memory leak
    // for (int i = 0; i <= n; i++) {
    //     delete[] K[i];
    // }
    // delete[] K;

    return maxValue;
}

int main() {
    int values[] = {30, 40, 60};
    int weights[] = {3, 2, 5};
    int capacity = 6;
    int n = sizeof(values) / sizeof(values[0]);
    int maxValue = knapsack_0_1(capacity, weights, values, n);
    cout << "Maximum value that can be put in the knapsack: " << maxValue << endl;

    return 0;
}