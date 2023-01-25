// Name: Akash Yeole
// Class: TY-A
// Gr. No.: 22120281
// Roll No.: 321092
// Batch: A3
// Assignment 1: B) Quick Sort implementation.

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define printv(v) for(auto i:v)cout<<i<<" ";cout<<endl;

// Partition by pivot index swapping the elements according to it
ll partitionAndGetPivot(ll low, ll high, vector<ll>& arr){
    // Selecting middle element as a pivot point
    ll pivotElement = arr[(low+high)/2];
    ll count = 0;
    for(ll i = low; i <= high+1; i++){
        if(arr[i] <= pivotElement) count++;
    }
    ll pivotIndex = (low+count-1);
    swap(arr[pivotIndex], arr[(low+high)/2]);
    ll i = low, j = high;
    while(i < pivotIndex && j > pivotIndex){
        while(arr[i] < pivotElement) i++;
        while(arr[j] > pivotElement) j--;
        if(i < pivotIndex && j > pivotIndex){
            swap(arr[i++], arr[j--]);
        }
    }
    // Return pivot index for partitioning
    return pivotIndex;
}

// Recursive function to split and sort array by selected pivot point
void quickSort(ll l, ll r, vector<ll>& arr){
    if(l < r){
        ll pivotPartitionIndex = partitionAndGetPivot(l, r, arr);
        quickSort(l, pivotPartitionIndex-1, arr);
        quickSort(pivotPartitionIndex+1, r, arr);
    }
}

void solve(){
    // N is an array size to be sorted
    ll n;
    cout << "Enter the number of elements in an array: ";
    cin >> n;
    vector<ll> arr(n, 0);
    // Accepting array
    cout << "Enter array elements " << n << " separated by a space: ";
    for(ll i = 0; i < n; i++) cin >> arr[i];
    // Applying quick sort
    quickSort(0, n-1, arr);
    cout << "Array after applying Quicksort: ";
    printv(arr);
    return;    
}

// Main Execution
int main() {
	solve();
    return 0;
}
