#pragma once 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printBoard(vector<vector<string>> &board);
bool hasWon(string symbol, vector<vector<string>> &board);
bool boardIsFull(string emptySym,vector<vector<string>> &board);
bool isValidSquare(int row, int col, string emptySym,vector<vector<string>> &board);
