#pragma once 
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <limits.h>
using namespace std;

void printBoard(vector<vector<string>> &board);
bool hasWon(string symbol, vector<vector<string>> &board);
bool boardIsFull(string emptySym, vector<vector<string>> &board);
bool isValidSquare(int row, int col, string emptySym, vector<vector<string>> &board);
tuple <int, int, int> minimax(bool isMaxing, int depth, string symbol, string emptySym, vector<vector<string>> &board);