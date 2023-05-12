#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

vector<string> printBinaryString(int n ){
    queue<string> liveNodes;
    liveNodes.push("");

    int level = 0;
    vector<string> solutionNodes;

    while(!liveNodes.empty()){        
        int numberOfLiveNodes = liveNodes.size();
        cout << "Current Level: " << level << endl << "Number of Live Nodes: " << numberOfLiveNodes << endl;

        for(int i = 0; i < numberOfLiveNodes; i++){
            string eNode = liveNodes.front();
            liveNodes.pop();
            cout << eNode << ", ";
            if(eNode.size() == n){
                solutionNodes.push_back(eNode);
            }else{
                string possibleNode_1 = eNode + '0';
                string possibleNode_2 = eNode + '1';

                liveNodes.push(possibleNode_1);
                liveNodes.push(possibleNode_2);
            }
        }
        getch();
        cout << endl << endl;
        level++;
    }
    return solutionNodes;
}

int main(){

    int n;

    cout << "Enter the value of N: ";
    cin >> n;

    vector<string> solutionNodes = printBinaryString(n);
    
    for(string &solutionNode: solutionNodes){
        cout << "Binary: " << solutionNode << " | " << "Decimal: " << stoi(solutionNode, 0, 2) << endl;
    }

    return 0;
}