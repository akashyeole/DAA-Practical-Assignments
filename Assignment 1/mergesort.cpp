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

void merge(ll low, ll mid, ll high, vector<ll>& arr, vector<ll>& aux){
    ll startOfLeft = low;
    ll startOfRight = mid;
    ll auxPtr = low;

    while(startOfLeft < mid && startOfRight <= high){
        if(arr[startOfLeft] < arr[startOfRight]){
            aux[auxPtr++] = arr[startOfLeft++];
        }else{
            aux[auxPtr++] = arr[startOfRight++];
        }
    }
    while(startOfLeft < mid) aux[auxPtr++] = arr[startOfLeft++];
    while(startOfRight <= high) aux[auxPtr++] = arr[startOfRight++];

    for(ll i = low; i <= high; i++) arr[i] = aux[i];
}

void mergeSort(ll low, ll high, vector<ll>& arr, vector<ll>& aux){
    if(low < high){
        ll mid = (low+high)/2;
        mergeSort(low, mid, arr, aux);
        mergeSort(mid+1, high, arr, aux);
        merge(low, mid+1, high, arr, aux);
    }
}

ll solve(){
    ll n;
    cout << "Enter the number of elements in an array: ";
    cin >> n;
    vector<ll> arr(n, 0);
    vector<ll> aux(n, 0);
    cout << "Enter array elements " << n << " separated by a space: ";
    for(ll i = 0; i < n; i++) cin >> arr[i];
    mergeSort(0, n-1, arr, aux);
    cout << "Array after applying Mergesort: ";
    printv(arr);
    return 0; 
}

int main(){
    solve();
    return 0;
}

// Analysis: 
// (n is the size of an array)
// Average case Time complexity: O(n*log(n))
// Space Complexity: O(n) (Auxialiary array for performing merge)