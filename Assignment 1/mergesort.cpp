// Name: Akash Yeole
// Class: TY-A
// Gr. No.: 22120281
// Roll No.: 321092
// Batch: A3
// Assignment 1: A) Merge Sort implementation.

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define printv(v) for(auto i:v)cout<<i<<" ";cout<<endl;

// Merge function to merge two sorted arrays
void merge(ll low, ll mid, ll high, vector<ll>& arr, vector<ll>& aux){
    ll startOfLeft = low;
    ll startOfRight = mid;
    ll auxPtr = low;
    // Using auxiliary array to perform merging
    while(startOfLeft < mid && startOfRight <= high){
        if(arr[startOfLeft] < arr[startOfRight]){
            aux[auxPtr++] = arr[startOfLeft++];
        }else{
            aux[auxPtr++] = arr[startOfRight++];
        }
    }
    // Adding remaining elements
    while(startOfLeft < mid) aux[auxPtr++] = arr[startOfLeft++];
    while(startOfRight <= high) aux[auxPtr++] = arr[startOfRight++];

    // Copying back to the original array
    for(ll i = low; i <= high; i++) arr[i] = aux[i];
}

// Recursive merge sort function for halving array and merging
void mergeSort(ll low, ll high, vector<ll>& arr, vector<ll>& aux){
    // If low is equals to high no need of partitioning
    if(low < high){
        ll mid = (low+high)/2;
        // Partitioning from low-to-mid & mid+1-to-high (TC: O(log n))
        mergeSort(low, mid, arr, aux);
        mergeSort(mid+1, high, arr, aux);
        // Sorting and merging the paritioned part(TC: O(n))
        merge(low, mid+1, high, arr, aux);
    }
}

ll solve(){
    // N is an array size to be sorted
    ll n;
    cout << "Enter the number of elements in an array: ";
    cin >> n;
    vector<ll> arr(n, 0);
    // Auxiliary array for performing merge operation
    vector<ll> aux(n, 0);
    // Accepting array
    cout << "Enter array elements " << n << " separated by a space: ";
    for(ll i = 0; i < n; i++) cin >> arr[i];
    // Applying merge sort
    mergeSort(0, n-1, arr, aux);
    cout << "Array after applying Mergesort: ";
    printv(arr);
    return 0; 
}

// Main Execution
int main(){
    solve();
    return 0;
}

// Analysis: 
// (n is the size of an array)
// Average case Time complexity: O(n*log(n))
// Space Complexity: O(n) (Auxialiary array for performing merge)