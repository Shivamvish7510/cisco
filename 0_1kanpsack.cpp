#include <iostream>
using namespace std;

int knapsack_0_1(int W, int weight[], int values[], int n)
{
    int **K = new int *[n + 1];
    for (int i = 0; i <= n; i++)
    {
        K[i] = new int[W + 1];
    }
    for (int j = 0; j <= W; j++)
    {
        K[0][j] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        { 
            if (weight[i - 1] <= j)
            {
                K[i][j] = max(values[i - 1] + K[i - 1][j - weight[i - 1]], K[i - 1][j]);
            }
            else
            {
                K[i][j] = K[i - 1][j];
            }
        }
    }
    int maxValue = K[n][W];
    return maxValue;
}

int main()
{
    int cap,n ;
    cout<<"Enter the number of items"<<endl;
    cin>>n;
    int values[n], weight[n];
    
    for(int i=0;i<n;i++){
        cout<<"Enter the value and weight of item "<<i+1 <<" : ";
        cin>>values[i] , cin>>weight[i];
    }

    cout<<"Enter the capacity : ",
    cin>>cap, cout<< endl;
    // = {30, 40, 60};
    // int weights[];
    //  = {3, 2, 5};
    // int capacity = 6;
    
    int maxValue = knapsack_0_1(cap, weight, values, n);
    cout << "Maximum value that can be put in the knapsack: " << maxValue << endl;
}