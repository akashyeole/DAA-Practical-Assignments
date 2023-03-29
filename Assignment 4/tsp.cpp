#include<iostream>
#include<bits/stdc++.h>

#define INF INT_MAX

using namespace std;

pair<int, vector<vector<int>>> reduceMatrix(int numberOfCities, vector<vector<int>> costMatrix){
    int currentCost = 0;
    for(int i = 0; i < numberOfCities; i++){
        int minVal = *min_element(costMatrix[i].begin(), costMatrix[i].end());
        if(minVal != INF){
            currentCost += minVal;
            for(int j = 0; j < numberOfCities; j++){
                if(costMatrix[i][j] != INF) costMatrix[i][j] -= minVal;
            }
        }
    }

    for(int i = 0; i < numberOfCities; i++){
        int minVal = INF;
        for(int j = 0; j < numberOfCities; j++){
            minVal = min(minVal, costMatrix[j][i]);
        }
        if(minVal != INF){
            currentCost += minVal;
            for(int j = 0; j < numberOfCities; j++){
                if(costMatrix[j][i] != INF) costMatrix[j][i] -= minVal;
            }
        }
    }

    return {currentCost, costMatrix};

}

void TSPLCBB(int numberOfCities, vector<vector<int>>& costMatrix){
    pair<int, vector<vector<int>>> reducedMatrix = reduceMatrix(numberOfCities, costMatrix);
    priority_queue<pair<int, pair<vector<int>, vector<vector<int>>>>, vector<pair<int, pair<vector<int>, vector<vector<int>>>>>, greater<pair<int, pair<vector<int>, vector<vector<int>>>>>> pq;
    
    pq.push({reducedMatrix.first, {{0}, reducedMatrix.second}});
    
    while(!pq.empty()){
        int currentCost = pq.top().first;
        vector<int> visitedCities = pq.top().second.first;
        vector<vector<int>> currentCostMatrix = pq.top().second.second;
        pq.pop();

        if(visitedCities.size() == numberOfCities){
            cout << endl << "Cost of Travelling: " << currentCost;
            cout << endl << "Path: 1";
            for(int k = 1; k < numberOfCities; k++) {
                cout << "->" << visitedCities[k]+1;
            }
            cout << "->1" << endl;
            cout << endl;
            continue;
        }

        for(int i = 0; i < numberOfCities; i++){
            if(find(visitedCities.begin(), visitedCities.end(), i) == visitedCities.end()){
                int newCurrentCost = currentCost;
                vector<int> newVisitedCities = visitedCities;
                vector<vector<int>> newCurrentMatrix = currentCostMatrix;
                int prevCity = visitedCities[visitedCities.size()-1];
                newCurrentMatrix[i][prevCity] = INF;
                newCurrentCost += newCurrentMatrix[prevCity][i];
                for(int j = 0; j < numberOfCities; j++){
                    newCurrentMatrix[prevCity][j] = INF;
                    newCurrentMatrix[j][i] = INF;
                }
                newVisitedCities.push_back(i);
                pair<int, vector<vector<int>>> newReducedMatrix = reduceMatrix(numberOfCities, newCurrentMatrix);
                newCurrentCost += newReducedMatrix.first;
                pq.push({newCurrentCost,{newVisitedCities, newReducedMatrix.second}});
            }
        }
    }

}

int main(){

    // Default Test Cases:
    int numberOfCities = 5;
    // vector<vector<int>> costMatrix ={   {INF, 7, 3, 12, 8}, 
    //                                     {3, INF, 6, 14, 9}, 
    //                                     {5, 8, INF, 6, 18}, 
    //                                     {9, 3, 5, INF, 11}, 
    //                                     {18, 14, 9, 8, INF}};
    vector<vector<int>> costMatrix ={   {INF, 20, 30, 10, 11}, 
                                        {15, INF, 16, 4, 2}, 
                                        {3, 5, INF, 2, 4}, 
                                        {19, 6, 18, INF, 3}, 
                                        {16, 4, 7, 16, INF}};

    // int numberOfCities;
    // cout << "Enter number of cities: ";
    // cin >> numberOfCities;
    
    // cout << endl;
    // vector<vector<int>> costMatrix(numberOfCities, vector<int>(numberOfCities, INF));
    // for(int i = 0; i < numberOfCities; i++){
    //     for(int j = 0; j < numberOfCities; j++){
    //         if(i!=j){
    //             cout << "Enter the cost of travelling from city " << i+1 << " to " << j+1 << ": ";
    //             cin >> costMatrix[i][j];
    //         }
    //     }
    // }
    TSPLCBB(numberOfCities, costMatrix);

    return 0;
}