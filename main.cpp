#include <bits/stdc++.h>
using namespace std; 
 
vector<pair<int,int>> directions={{0,1}, {0,-1}, {1,0}, {-1, 0}, {1,1}, {-1,-1}, {-1,1}, {1,-1}}; 
 
bool isPositionValid(vector<vector<int>>& board, int x, int y){
    return x >=0 && y >= 0 && x < board.size() && y < board[0].size(); 
}

bool isDropValid(vector<vector<int>>&board, int pos){
    return pos >= 0 && pos < board.size() && !board[0][pos]; 
}

bool checkVertical(vector<vector<int>>& board, pair<int,int> coords){
    int player = board[coords.first][coords.second]; 
    int x = coords.first-1, y = coords.second, score = 1; 
    while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; x--; 
    }
    x = coords.first+1; 
     while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; x++; 
    }

    return score >= 4; 
}

bool checkHorizontal(vector<vector<int>>& board, pair<int,int> coords){
    int player = board[coords.first][coords.second]; 
    int x = coords.first, y = coords.second-1, score = 1; 
    while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; y--; 
    }
    y = coords.second+1; 
     while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; y++; 
    }

    return score >= 4; 
}

bool checkDiagonal(vector<vector<int>>& board, pair<int,int> coords){
    int player = board[coords.first][coords.second]; 
    int x = coords.first-1, y = coords.second-1, score = 1; 
    while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; x--; y--; 
    }
    x = coords.first+1; y = coords.second+1; 
     while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; x++; y++; 
    }

    return score >= 4; 
}

bool checkRevDiagonal(vector<vector<int>>& board, pair<int,int> coords){
    int player = board[coords.first][coords.second]; 
    int x = coords.first-1, y = coords.second+1, score = 1; 
    while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; x--; y++; 
    }
    x = coords.first+1; y = coords.second-1; 
     while(isPositionValid(board, x, y)){
        if(board[x][y] != player) break; 
        score++; x++; y--; 
    }

    return score >= 4; 
}
 
bool didPlayerWin(vector<vector<int>>& board, int pos, int player, int& winner){
    int y = pos, x = 0; 
    for(int i = 0; i< board.size(); i++) { if(board[i][pos] == player){ x = i; break; } }
    pair<int,int> coords = make_pair(x,y); 
    if(checkVertical(board, coords) || checkHorizontal(board, coords)
    || checkDiagonal(board, coords) || checkRevDiagonal(board, coords)) return player;
    return 0; 
}
 
void printBoard(const vector<vector<int>>& board) {
    int n = board.size();
    if (n == 0) return;
    int m = board[0].size();

    // Find max width for non-zero numbers
    int width = 0;
    for (auto& row : board)
        for (auto val : row)
            if (val != 0)
                width = max(width, (int)to_string(val).size());

    // Also account for (index) length
    int headerWidth = max(width, (int)to_string(m - 1).size() + 2); // +2 for parentheses
    int idxWidth = max(2, (int)to_string(n - 1).size());

    auto printBorder = [&]() {
        cout << string(idxWidth + 1, ' ') << "+";
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < headerWidth + 2; k++) cout << "-";
            cout << "+";
        }
        cout << "\n";
    };

    // Print header row
    printBorder();
    cout << string(idxWidth, ' ') << " |";
    for (int j = 0; j < m; j++) {
        string header = "(" + to_string(j) + ")";
        cout << setw(headerWidth + 1) << header << " |";
    }
    cout << "\n";
    printBorder();

    // Print board rows
    for (int i = 0; i < n; i++) {
        cout << setw(idxWidth) << i << " |";
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 0)
                cout << " " << setw(headerWidth) << " " << " |";
            else
                cout << " " << setw(headerWidth) << (board[i][j] == 2 ? 0 : board[i][j]) << " |";
        }
        cout << "\n";
        printBorder();
    }
}

bool drop(vector<vector<int>>& board, int player, int pos){
    bool dropped = false; 
    for(int i = board[pos].size()-1; i>=0; i--){
        if(board[i][pos] == 0){ board[i][pos] = player; dropped = true; break;}
    }
    return dropped; 
}
 
bool playTurn(vector<vector<int>>& board, int player, int pos){
    if(pos<0 || pos >= board.size()) return false; 
    return drop(board, player, pos); 
}

void switchTurn(int& turn){
    turn = turn==1 ? 2 : 1;  
}
 
int main()
{
    int size = 8, winner = 0, turn = 1, steps = 0; 
    vector<vector<int>> board(size, vector<int>(size, 0)); 
    
    while(steps < (size * size) && !winner){
        int drop; 
        printBoard(board);
        while(true){
            cout << "Player " << turn << "'s turn: ";
            cin >> drop;
            if(!cin || !isDropValid(board, drop)) { cout << "Invalid Move. Try Again!!" << endl;  continue; }
            playTurn(board, turn, drop); break;
        }
        steps++; 
        winner = didPlayerWin(board, drop, turn, winner); 
        switchTurn(turn); 
    }
    printBoard(board);
    if(winner) cout << "Congratulations Player"<< winner << " Won the match!!" << endl; 
    else cout << "It's a tie!!"; 
    
    return 0;
}