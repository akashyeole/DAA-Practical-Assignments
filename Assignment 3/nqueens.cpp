// Name: Akash Yeole
// Class: TY-A
// Gr. No.: 22120281
// Roll No.: 321092
// Batch: A3
// Assignment 3: Implementing 8 queens problem using Backtracking.

#include<iostream>
#include<vector>

using namespace std;

int arrangementsCount = 0;

bool isSafePB(int row, int col, vector<vector<char>>& chessBoard){
    for(int i = col-1; i >= 0; i--){
        if(chessBoard[row][i] == 'Q') return false;
    }

    int i = row-1;
    int j = col-1;
    while(i >= 0 && j >= 0){
        if(chessBoard[i--][j--] == 'Q') return false;
    }

    i = row+1;
    j = col-1;
    while(i < chessBoard.size() && j >= 0){
        if(chessBoard[i++][j--] == 'Q') return false;
    }

    return true;
}

void recursiveNQueensPB(int col, int boardSize, vector<vector<char>>& chessBoard){
    if(col == boardSize) {
        arrangementsCount++;
        cout << "Possible Arrangement No. " << arrangementsCount << ": " << endl;
        for(int dashCounter = 0; dashCounter < (4*boardSize)+1; dashCounter++) cout << "-";
        cout << endl;
        for(int i = 0; i < boardSize; i++){
            cout << "| ";
            for(int j = 0; j < boardSize; j++){
                cout << chessBoard[i][j] << " | ";
            }
            cout << endl;
            for(int dashCounter = 0; dashCounter < (4*boardSize)+1; dashCounter++) cout <<"-";
            cout << endl;
        }    
        cout << endl;
        return;
    }

    for(int row = 0; row < boardSize; row++){
        if(isSafePB(row, col, chessBoard)){
            chessBoard[row][col] = 'Q';
            recursiveNQueensPB(col+1, boardSize, chessBoard);
            chessBoard[row][col] = ' ';
        }
    }
    return;
}

void printBoards(int numberOfQueens){
    vector<vector<char>> chessBoard(numberOfQueens, vector<char>(numberOfQueens, ' '));
    recursiveNQueensPB(0, numberOfQueens, chessBoard);
    return;
}

bool isSafeRV(int row, int col, vector<int>& rowVector){
    for(int k = col-1; k >= 0; k--){
        if(rowVector[k] == row || abs(k-col) == abs(row-rowVector[k])) return false;
    }
    return true;
}

void recursiveNQueensRV(int col, int numberOfQueens, vector<int>& rowVector){
    if(col == numberOfQueens){
        arrangementsCount++;
        cout << "Possible Row Vector No. " << arrangementsCount << ": " << endl;
        for(int colNm: rowVector) cout << colNm+1 << " ";
        cout << endl << endl;
        return;
    }
    for(int row = 0; row < numberOfQueens; row++){
        if(isSafeRV(row, col, rowVector)){
            rowVector[col] = row;
            recursiveNQueensRV(col+1, numberOfQueens, rowVector);
        }
    }
    return;
}

void printRowVectors(int numberOfQueens){
    vector<int> rowVector(numberOfQueens, 0);
    recursiveNQueensRV(0, numberOfQueens, rowVector);
    return;
}

int main(){

    int numberOfQueens;
    cout << "Enter the size of N: ";
    cin >> numberOfQueens;

    int choice;
    cout << "\nEnter 1 for Boards & 0 for Row vectors: ";
    cin >> choice;
    if(choice){
        cout << "Printing possible boards-\n";
        printBoards(numberOfQueens);
    }else{
        cout << "Printing possible row vectors-\n";
        printRowVectors(numberOfQueens);
    }
    return 0;
}

// Analysis:
// Time complexity: O(n!). Since, algorithm tries to put queen at every cell.
