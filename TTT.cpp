#include "TTT.h"

int main(){

    vector<vector<string>> board;
    board.resize(3);

    string empSym = "e";
    for (int i = 0; i < 3; i++){
        board[i].resize(3);
        for (int j = 0; j < 3; j++){
            board[i][j] = empSym;
        }
    }

    string player1Sym = "X";
    string player2Sym = "O";
    bool isPlayer1Turn = true; 
    bool winning = false;

    string currSym = player1Sym;
    int x, y;

    //board[row][col]
    while(true){
        printBoard(board);
        cout << endl;

        if(isPlayer1Turn){
            cout << "Enter your coordinates" << endl;
            cin >> x >> y;
            cout << endl;

            while(!isValidSquare(x, y, empSym, board)){
                cout << "Invalid input." << endl;
                cout << "Enter your coordinates" << endl;
                cin >> x >> y;
                cout << endl;
            }
        }
        else{
            tuple<int, int, int> temp = minimax(true, 0, "O", empSym, board);
            x = get<1>(temp);
            y = get<2>(temp);
        }


        board[x][y] = currSym;
        if(hasWon(currSym, board)){
            winning = true;
            break;
        }

        if(boardIsFull(empSym, board)){
            break;
        }

        isPlayer1Turn = !isPlayer1Turn;   
        if(isPlayer1Turn){
            currSym = player1Sym;
        }
        else{
            currSym = player2Sym;
        }
    }

    printBoard(board);
    cout << endl;

    if(winning){
        if(isPlayer1Turn){
            cout << ("Player 1 has won!") << endl;
        }

        else{
            cout << ("Player 2 has won!") << endl;
        }
    }
    else{
        cout << ("You've tied!") << endl;
    }
};

tuple <int, int, int> minimax(bool isMaxing, int depth, string symbol, string emptySym, vector<vector<string>> &board){

    tuple <int, int, int> bestSquare;
    if(isMaxing){
        int maxScore = INT_MIN;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(board[i][j] == emptySym){
                    board[i][j] = symbol;
                    if(hasWon(symbol, board)){
                        board[i][j] = emptySym;
                        return tuple <int, int, int> (10 - depth, i, j);
                    }

                    if(boardIsFull(emptySym, board)){
                        board[i][j] = emptySym;
                        return tuple <int, int, int> (0, i, j);
                    }

                    tuple<int, int, int> temp = minimax(!isMaxing, depth + 1, "X", emptySym, board);
                    board[i][j] = emptySym;

                    if(get<0>(temp) > maxScore){
                        get<1>(bestSquare) = i;
                        get<2>(bestSquare) = j;
                        maxScore = get<0>(temp);
                    }
                }
            }
        }
        get<0>(bestSquare) = maxScore;
    }

    else{
        int minScore = INT_MAX;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(board[i][j] == emptySym){
                    board[i][j] = symbol;
                    if(hasWon(symbol, board)){
                        board[i][j] = emptySym;
                        return tuple <int, int, int> (-10 + depth, i, j);
                    }

                    if(boardIsFull(emptySym, board)){
                        board[i][j] = emptySym;
                        return tuple <int, int, int> (0, i, j);
                    }

                    tuple<int, int, int> temp = minimax(!isMaxing, depth + 1, "O", emptySym, board);
                    board[i][j] = emptySym;

                    if(get<0>(temp) < minScore){
                        get<1>(bestSquare) = i;
                        get<2>(bestSquare) = j;
                        minScore = get<0>(temp);
                    }
                }
            }
        }
        get<0>(bestSquare) = minScore;
        
    }
    return bestSquare;

}

bool hasWon(string sym, vector<vector<string>> &board){
    for(int i = 0; i < 3; i++){
        //Check if cols are filled
        if(board[i][0] == sym && board[i][1] == sym && board[i][2] == sym){
            return true;
        }

        //Check if rows are filled
        if(board[0][i] == sym && board[1][i] == sym && board[2][i] == sym){
            return true;
        }
    }

    //Check down diagonal
    if(board[0][0] == sym && board[1][1] == sym && board[2][2] == sym){
        return true;
    }

    //Check up diagonal
    if(board[0][2] == sym && board[1][1] == sym && board[2][0] == sym){
        return true;
    }

    return false;
}

bool boardIsFull(string emptySym,vector<vector<string>> &board){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(board[i][j] == emptySym){
                return false;
            }
        }
    }
    return true;
}

bool isValidSquare(int row, int col, string emptySym, vector<vector<string>> &board){
    //In bounds
    if(row < 0 || col < 0 || row >= 3 || col >= 3){
        return false;
    }

    //Not already filled
    if(board[row][col] != emptySym){
        return false;
    }

    return true;
}

void printBoard(vector<vector<string>> &board){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

