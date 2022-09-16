// ab521@uakron.edu
// Amid Babaev

#include <bits/stdc++.h>
using namespace std;

void printSolution(vector < vector < int >> board) {
  int N = board.size();
  ofstream fout("solution.csv");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      fout << " " << board[i][j] << " ";
    fout << endl;
  }
}

bool isSafe(vector < vector < int >> board, int row, int col) {
  int i, j;
  int N = board.size();
  /* Check this row on left side */
  for (i = 0; i < col; i++)
    if (board[row][i])
      return false;

  /* Check upper diagonal on left side */
  for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return false;

  /* Check lower diagonal on left side */
  for (i = row + 1, j = col - 1; j >= 0 && i < N; i++, j--)
    if (board[i][j])
      return false;

  return true;
}

/* A recursive utility function to solve N
Queen problem */
bool placeNQ(vector < vector < int >> & board, int col) {
  //printSolution(board);
  int N = board.size();
  if (col >= N)
    return true;

  for (int i = 0; i < N; i++) {
    if (board[i][col] == 1) {
      if (isSafe(board, i, col))
        return placeNQ(board, col + 1);
      else {
        return false;
      }
    }
  }
  /* base case: If all queens are placed
  then return true */

  /* Consider this column and try placing
  this queen in all rows one by one */
  for (int i = 0; i < N; i++) {
    /* Check if the queen can be placed on
    board[i][col] */
    if (isSafe(board, i, col)) {
      /* Place this queen in board[i][col] */
      board[i][col] = 1;

      /* recur to place rest of the queens */
      if (placeNQ(board, col + 1))
        return true;

      /* If placing queen in board[i][col]
      doesn't lead to a solution, then
      remove queen from board[i][col] */
      board[i][col] = 0; // BACKTRACK
    }
  }

  /* If the queen cannot be placed in any row in
   this column col then return false */
  return false;
}

bool solveNQ() {
  vector < vector < int >> board;
  string s;
  ifstream fin("input.csv");
  if (fin.is_open()) {
    while (getline(fin, s)) {
      vector < int > temp;
      s += ',';
      for (int i = 0; i < s.size(); i += 2) {
        temp.push_back(s[i] - 48);
      }
      board.push_back(temp);
    }
  }

  ofstream fout("solution.csv");
  int N = board.size();
  if (placeNQ(board, 0) == false) {
    fout << "No solution";
    return false;
  }
  printSolution(board);
  return true;

}
int main() {
  solveNQ();
  return 0;
}
