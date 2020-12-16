#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdint.h>

#define MAX_ROWS 128
#define MAX_COLS 8

using namespace std;

int loadDataFromFile(string path, vector<string> &vals) {
  string line;
  ifstream inFile(path);

  /* Load values from file into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      vals.push_back(line);
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return 1; }

  cout << "Data loaded successfully from " << path << endl;
  return 0;
}

void printSolutionsAndTiming(int64_t result, clock_t start, clock_t stop) {
  if (result == -1) cout << "No solution found" << endl;
  else {
    cout << "Solution: " << result << endl;
    double totalTime = (stop - start);
    cout << "Time elapsed to reach solution: " << totalTime / CLOCKS_PER_SEC << "s" << endl;
  }
}

int calculateSeatID(int row, int col) { return row * MAX_COLS + col; }

int getBase2Log(unsigned int val) {
  if (val == 0) return -1;
  int level = 0;
  while (val >>= 1) level++;
  return level;
}

vector<string> splitPartition(const string &partition) {
  vector<string> par;
  par.push_back(partition.substr(0, getBase2Log(MAX_ROWS)));
  par.push_back(partition.substr(getBase2Log(MAX_ROWS), 
      getBase2Log(MAX_COLS) - getBase2Log(MAX_ROWS)));
  return par;
}

// Would a recursive implementation have been better?
int getValFromSeq(const string &s, bool row, bool verbose) {

  vector<int> range = {0, (row) ? MAX_ROWS - 1 : MAX_COLS - 1};

  int x; 
  for (const char& c : s) {
    x = (range.at(1) - range.at(0)) / 2 + range.at(0);
    if (verbose) cout << range.at(0) << " -> " << range.at(1) << endl;
    if (c == 'F' || c == 'L') range.at(1) = x;
    else range.at(0) = x + 1;
  }

  return range.at(0);
}

vector<int> getIDSeats(const vector<string> &vals, bool verbose) {

  vector<int> idSeats;
  vector<string> parts;
  int row = 0, col = 0;

  // Obtain Seat IDs
  for (string s : vals) {
    parts = splitPartition(s);
    row = getValFromSeq(parts.at(0), true, verbose);
    col = getValFromSeq(parts.at(1), false, verbose);
    idSeats.push_back(calculateSeatID(row,col));
  }

  return idSeats;
}

int findSolutionPart1(const vector<string> &vals, bool verbose) {
  
  vector<int> idSeats = getIDSeats(vals, verbose);

  // Find highest
  sort(idSeats.begin(), idSeats.end(), [](int a, int b) { return a > b; });

  return idSeats.at(0);

}

int findSolutionPart2(const vector<string> &vals, bool verbose) {
  
  vector<int> idSeats = getIDSeats(vals, verbose);

  // Need to find first missing number in sequence
  sort(idSeats.begin(), idSeats.end(), [](int a, int b) { return a < b; });

  for (unsigned int i = 1; i < idSeats.size() - 1; i++) {
    if (verbose) cout << "Comparing " << idSeats.at(i-1) << " and " << idSeats.at(i) << endl;
    if (idSeats.at(i) - idSeats.at(i-1) != 1) return idSeats.at(i) - 1;
  }

  return -1;

}

int main(int argc, char ** argv) {

  cout << "## Day 5 of Advent of Code ##" << endl;

  vector<string> vals;
  int64_t result = 0;
  clock_t start, stop;

  loadDataFromFile("input", vals);
  
  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

}

