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
    
    // If current tem number exceeds the actual number of item then return 0 profit.
    if(itemNumber >= totalItems) return 0;
    
    // Let the profit by skipping or selecting the current item be initially 0.
    int profitSelectingCurrentItem = 0, profitSkippingCurrentItem = 0;

    // Selecting the current item only if fits in the knapsack.   
    if(weights[itemNumber] <= currentCapacity){
        // Calling the recursion for the next item.
        profitSelectingCurrentItem = KnapSack01Recursion(totalItems, itemNumber+1, currentCapacity-weights[itemNumber], weights, profits) + profits[itemNumber];
    }
    
    // Skipping the current item regardless of what the weight and capacityt is.
    // Calling the recursion for the next item.
    profitSkippingCurrentItem = KnapSack01Recursion(totalItems, itemNumber+1, currentCapacity, weights, profits);
    
    // Returning the maximum profit obained either by selecting or skipping the current item.
    return max(profitSelectingCurrentItem, profitSkippingCurrentItem);
}

// Dynamic programming approach to obtain the maximum profit.
// Time complexity: O(n^2) (Quadratic) Here, n is the number item available to pick.
// Space Complexity: O(n) Auxiliary stack space + O(n * m) DP table = O(n * m) Here n is the number of items and m is he capcity of knapsack.
int KnapSack01Memoization(int totalItems, int itemNumber, int currentCapacity, vector<int>& weights, vector<int>& profits, vector<vector<int>>& dpArray){
    
    // If current tem number exceeds the actual number of item then return 0 profit.
    if(itemNumber >= totalItems) return 0;

    // If the current state of recursion call is already stored in DP table, return the value of that state.
    if(dpArray[itemNumber][currentCapacity] != -1) return dpArray[itemNumber][currentCapacity];

    // Let the profit by skipping or selecting the current item be initially 0.
    int profitSelectingCurrentItem = 0, profitSkippingCurrentItem = 0;
    
    // Selecting the current item only if fits in the knapsack.
    if(weights[itemNumber] <= currentCapacity){
        // Calling the recursion for the next item.
        profitSelectingCurrentItem = KnapSack01Memoization(totalItems, itemNumber+1, currentCapacity-weights[itemNumber], weights, profits, dpArray) + profits[itemNumber];
    }
    
    // Skipping the current item regardless of what the weight and capacityt is.
    // Calling the recursion for the next item.
    profitSkippingCurrentItem = KnapSack01Memoization(totalItems, itemNumber+1, currentCapacity, weights, profits, dpArray);
    
    // Before returning the maximum profit, store the state result in the DP table.
    return dpArray[itemNumber][currentCapacity] = max(profitSelectingCurrentItem, profitSkippingCurrentItem);
}

int main(){
    // Accepting the required data
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
    
    // Result of recursion
    clock_t start, end;
    start = clock();
    cout << "0/1 Knapsack Solution for given input(Brute Force Approach/Recursion): " << endl;
    cout << "Optimal profit: " << KnapSack01Recursion(numberOfItems, 0, capacityOfKnapSack, weights, profits) << endl;
    end = clock();
    cout << "Time Taken :" << double(end-start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms" << endl << endl;

    // Result of DP approach
    start = clock();
    vector<vector<int>> dpArray(numberOfItems, vector<int>(capacityOfKnapSack+1, -1));
    cout << "0/1 Knapsack Solution for given input(Optimzed using Dynamic Programming): " << endl;
    cout << "Optimal profit: " << KnapSack01Memoization(numberOfItems, 0, capacityOfKnapSack, weights, profits, dpArray) << endl;
    end = clock();
    cout << "Time Taken: " << double(end-start) / double(CLOCKS_PER_SEC) << setprecision(11) << "ms" << endl << endl;

}
<<<<<<< HEAD

// Analysis:
// Recursive solution takes O(2^n) time, there are 2 possibilites for each item (pick or don't pick)
// Memoized solution takes O(n^2) time, because we are storing the result of the optimal substructure.
=======
>>>>>>> e0f80eae7bcced2b74748fab8c91e01ccb7fbe24
