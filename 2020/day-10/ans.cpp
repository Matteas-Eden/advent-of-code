#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdint.h>

using namespace std;

int loadDataFromFile(string path, vector<int> &vals) {
  string line;
  ifstream inFile(path);

  /* Load values from file into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      vals.push_back(stoi(line));
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return 1; }

  cout << "Data loaded successfully from " << path << endl;
  return 0;
}

int64_t findSolutionPart1(const vector<int> &vals, bool verbose = false) {

  vector<int> sorted(vals);
  vector<int>::const_iterator it = sorted.begin() + 1;
  sort(sorted.begin(), sorted.end(), [](int a, int b){ return a < b; });

  vector<int> counting = {0,0,0};
  while (it != sorted.end()) {
    if (verbose) cout << "PREV: " << *(it - 1) << " || CURR: " << *it << " || DIFF: " << *it - *(it - 1) << endl;
    counting.at(*it - *(it - 1) - 1)++;
    it++;
  }

  if (verbose) {
    for (unsigned int i = 0; i < counting.size(); i++) {
      cout << "Diff: " << i + 1 << " Count: " << counting.at(i) << endl;
    }
  }

  return counting.at(2) * counting.at(0);

}

/*
 * I don't full understand how this function came to be, but it's derived from
 * a similar function here: https://bit.ly/3gYJfT6.
 *
 * In that person's code, they give justifications to how they arrived at the
 * hardcoded values in the switch statement based on an investigation of the
 * diffs in their input.
 * */
int calculateCombinations(int sublistLength) {

  if (sublistLength <= 1) return 1;

  int valid = 1;

  switch (sublistLength) {
    case 2:
      break;
    case 3:
      valid += 1;
      break;
    case 4:
      valid += 3;
      break;
    case 5:
      valid += 6;
      break;
  }

  return valid;

}

/*
 * Utilise the notion of 'unskippable' adapters acting as fixed points,
 * then calculating length of sublist between these fixed points.
 * */
int64_t findSolutionPart2(const vector<int> &vals, bool verbose = false) {
  vector<int> sorted(vals);
  sort(sorted.begin(), sorted.end(), [](int a, int b){ return a < b; });

  // Stores indices of unskippable values
  vector<int> fixedPoints;
  fixedPoints.push_back(0);
  int back_diff, front_diff;

  // O(n)
  for (unsigned int k = 1; k < sorted.size() - 1; k++) {
    back_diff = sorted.at(k) - sorted.at(k - 1);
    front_diff = sorted.at(k + 1) - sorted.at(k);
    // Indicates that this element can't be removed without breaking the chain
    if (back_diff == 3 || front_diff == 3) fixedPoints.push_back(k);
    // Means that removing this element would leave a gap of 4, which breaks
    // the chain
    else if (back_diff == 2 && front_diff == 2) fixedPoints.push_back(k);
  }

  // The last value is naturally unskippable
  fixedPoints.push_back(sorted.size() - 1);

  int64_t numArrangements = 1;

  // O(n)
  for (unsigned int k = 0; k < fixedPoints.size() - 1; k++) {
    numArrangements *= calculateCombinations(fixedPoints.at(k+1) - fixedPoints.at(k) + 1); 
  }

  return numArrangements;

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

  cout << "## Day 10 of Advent of Code ##" << endl;

  vector<int> vals;
  int64_t result = 0;
  clock_t start, stop;

  vals.push_back(0);
  loadDataFromFile("input", vals);
  vals.push_back(*max_element(vals.begin(), vals.end()) + 3);

  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
}

