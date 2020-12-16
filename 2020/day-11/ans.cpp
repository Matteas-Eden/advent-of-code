#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdint.h>

using namespace std;

int loadDataFromFile(string path, vector<vector<char>> &vals) {
  string line;
  ifstream inFile(path);
  vector<char> vec;

  /* Load values from file into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      vec = vector<char>(line.begin(), line.end());
      vals.push_back(vec);
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return 1; }

  cout << "Data loaded successfully from " << path << endl;
  return 0;
}

void printSeatingPlan(const vector<vector<char>> &plan) {
  for (unsigned int k = 0; k < plan[0].size(); k++) cout << '=';
  cout << '\n';
  for (vector<char> vec : plan) {
    for (char c : vec) {
      cout << c;
    }
    cout << '\n';
  }
  for (unsigned int k = 0; k < plan[0].size(); k++) cout << '=';
  cout << endl;
}

int getAdjacentOccupiedSeats(const vector<vector<char>> &plan, int row, int col) {

  int count = 0;

  // cout << "Check around: (" << row << ", " << col << ")" << endl;

  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      // Top row
      if (row == 0 && x == -1) continue;
      // Bottom row
      if (row == plan.size() - 1 && x == 1) continue;
      // Left edge
      if (col == 0 && y == -1) continue;
      // Right edge
      if (col == plan.at(0).size() - 1 && y == 1) continue;
      // Don't consider centre
      if (x == 0 && y == 0) continue;

      // cout << "- Checking: R=" << row+x << " C=" << col+y << endl; 
      if (plan[row + x][col + y] == '#') count++;
    }
  }

  return count;

}

/*
 * Empty seats with no adjacent occupied seats becomes occupied
 * Occupied seats with at least four adjacent occupied seats becomes occupied
 * */
vector<vector<char>> applyRules(const vector<vector<char>> &plan) {

  vector<vector<char>> result;
  vector<char> temp;

  for (unsigned int i = 0; i < plan.size(); i++) {
    temp = vector<char>();
    for (unsigned int j = 0; j < plan[i].size(); j++) {
      if (getAdjacentOccupiedSeats(plan, i, j) == 0 && plan[i][j] == 'L') {
        temp.push_back('#');
        continue;
      } else if (getAdjacentOccupiedSeats(plan, i, j) >= 4 && plan[i][j] == '#') {
        temp.push_back('L');
        continue;
      }
      temp.push_back(plan[i][j]);
    }
    result.push_back(temp);
  }

  return result;

}

int countSeats(const vector<vector<char>> &plan, char seat) {
  int count = 0;
  for (vector<char> vec : plan) {
    for (char c : vec) {
      if (c == seat) count++;
    }
  }
  return count;
}

/*
 * Map of characters
 * Create a working copy and a 'last run' copy
 * Iterate through all of it
 * Apply rules
 * Update a the 'last run' with the working copy
 * Repeat until working copy == last run
 * Calculate numSeats
 * return numSeats
 * */
int findSolutionPart1(const vector<vector<char>> &vals, bool verbose = false) {
  vector<vector<char>> last(vals);
  vector<vector<char>> curr;

  if (verbose) printSeatingPlan(last);

  while (curr != last) {
    if (curr.size()) last = curr;
    curr = applyRules(last);
    if (verbose) printSeatingPlan(curr);
  }

  return countSeats(last, '#'); 
}

void printSolutionsAndTiming(int64_t result, clock_t start, clock_t stop) {
  if (result == -1) cout << "No solution found" << endl;
  else {
    cout << "Solution: " << result << endl;
    double totalTime = (stop - start);
    cout << "Time elapsed to reach solution: " << totalTime / CLOCKS_PER_SEC << "s" << endl;
  }
}

int main(int argc, char ** argv) {

  cout << "## Day 11 of Advent of Code ##" << endl;

  vector<vector<char>> vals;
  int64_t result = 0;
  clock_t start, stop;

  loadDataFromFile("input", vals);

  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  
  /*
  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  */
}

