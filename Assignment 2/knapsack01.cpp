// Name: Akash Yeole
// Class: TY-A
// Gr. No.: 22120281
// Roll No.: 321092
// Batch: A3
// Assignment 2: Implement 0/1 Knapsack using Dynamic Programming.

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int KnapSack01Recursion(int totalItems, int itemNumber, int currentCapacity, vector<int>& weights, vector<int>& profits){
    if(itemNumber >= totalItems) return 0;

    int profitSelectingCurrentItem = 0, profitSkippingCurrentItem = 0;

    if(weights[itemNumber] <= currentCapacity){
        profitSelectingCurrentItem = KnapSack01Recursion(totalItems, itemNumber+1, currentCapacity-weights[itemNumber], weights, profits) + profits[itemNumber];
    }
    profitSkippingCurrentItem = KnapSack01Recursion(totalItems, itemNumber+1, currentCapacity, weights, profits);

    return max(profitSelectingCurrentItem, profitSkippingCurrentItem);
}

int KnapSack01Memoization(int totalItems, int itemNumber, int currentCapacity, vector<int>& weights, vector<int>& profits, vector<vector<int>>& dpArray){
    if(itemNumber >= totalItems) return 0;

    if(dpArray[itemNumber][currentCapacity] != -1) return dpArray[itemNumber][currentCapacity];

    int profitSelectingCurrentItem = 0, profitSkippingCurrentItem = 0;
    
    if(weights[itemNumber] <= currentCapacity){
        profitSelectingCurrentItem = KnapSack01Memoization(totalItems, itemNumber+1, currentCapacity-weights[itemNumber], weights, profits, dpArray) + profits[itemNumber];
    }
    profitSkippingCurrentItem = KnapSack01Memoization(totalItems, itemNumber+1, currentCapacity, weights, profits, dpArray);

    return dpArray[itemNumber][currentCapacity] = max(profitSelectingCurrentItem, profitSkippingCurrentItem);
}

int main(){
    int numberOfItems;
    cout << endl <<  "Enter number of items available to pick: ";
    cin >> numberOfItems;
    int capacityOfKnapSack;
    cout << "Enter capacity of Knapsack: ";
    cin >> capacityOfKnapSack;
    vector<int> weights(numberOfItems), profits(numberOfItems);

    cout << "Enter WEIGHTS of " << numberOfItems << " items separated by space: ";
    for(int i = 0; i < numberOfItems; i++) cin >> weights[i];
    cout << "Enter PROFITS of " << numberOfItems << " items separated by space: ";
    for(int i = 0; i < numberOfItems; i++) cin >> profits[i];
    cout << endl; 

    clock_t start, end;
    start = clock();
    cout << "0/1 Knapsack Solution for given input(Brute Force Approach/Recursion): " << endl;
    cout << "Optimal profit: " << KnapSack01Recursion(numberOfItems, 0, capacityOfKnapSack, weights, profits) << endl;
    end = clock();
    cout << "Time Taken :" << double(end-start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms" << endl << endl;

    start = clock();
    vector<vector<int>> dpArray(numberOfItems, vector<int>(capacityOfKnapSack+1, -1));
    cout << "0/1 Knapsack Solution for given input(Optimzed using Dynamic Programming): " << endl;
    cout << "Optimal profit: " << KnapSack01Memoization(numberOfItems, 0, capacityOfKnapSack, weights, profits, dpArray) << endl;
    end = clock();
    cout << "Time Taken: " << double(end-start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms" << endl << endl;

}

// Analysis:
// Recursive solution takes O(2^n) time, there are 2 possibilites for each item (pick or don't pick)
// Memoized solution takes O(n^2) time, because we are storing the result of the optimal substructure.