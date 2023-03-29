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

ll partitionAndGetPivot(ll low, ll high, vector<ll>& arr){
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
    return pivotIndex;
}

void quickSort(ll l, ll r, vector<ll>& arr){
    if(l < r){
        ll pivotPartitionIndex = partitionAndGetPivot(l, r, arr);
        quickSort(l, pivotPartitionIndex-1, arr);
        quickSort(pivotPartitionIndex+1, r, arr);
    }
}

void solve(){
    ll n;
    cout << "Enter the number of elements in an array: ";
    cin >> n;
    vector<ll> arr(n, 0);
    cout << "Enter array elements " << n << " separated by a space: ";
    for(ll i = 0; i < n; i++) cin >> arr[i];
    quickSort(0, n-1, arr);
    cout << "Array after applying Quicksort: ";
    printv(arr);
    return;    
}

int main() {
	solve();
    return 0;
}

// Analysis: 
// (n is the size of an array)
// Average case Time complexity: O(n*log(n)) | O(n^2) in worst case.
// Space Complexity: O(1)(No Extra Space required)