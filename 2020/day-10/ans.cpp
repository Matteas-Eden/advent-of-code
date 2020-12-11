#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

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

int findSolutionPart1(const vector<int> &vals, bool verbose = false) {

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
  int result = 0;
  clock_t start, stop;

  vals.push_back(0);
  loadDataFromFile("input", vals);
  vals.push_back(*max_element(vals.begin(), vals.end()) + 3);

  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  /*
  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, preamble, 2, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  */
}

