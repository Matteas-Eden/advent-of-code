#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <ctime>

using namespace std;

int loadDataFromFile(string path, vector<int64_t> &vals) {
  string line;
  ifstream inFile(path);

  /* Load values from file into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      vals.push_back(stol(line));
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return 1; }

  cout << "Data loaded successfully from " << path << endl;
  return 0;
}

/*
 * Repurposed from the Day 1 Part 1 solution!
 * */
bool checkForSummingPair(const vector<int64_t> &vals, int64_t target) {
  vector<int64_t> sorted(vals);

  sort(sorted.begin(), sorted.end(), [](int64_t a, int64_t b) { return a < b; });

  vector<int64_t>::const_iterator v1 = sorted.begin();
  vector<int64_t>::const_iterator v2 = sorted.end() - 1;

  while (*v1 + *v2 != target && v1 != v2) {
    // cout << "V1: " << *v1 << " V2: " << *v2 << endl;
    if (*v1 + *v2 > target) v2--;
    if (*v1 + *v2 < target) v1++;
  }

  return (*v1 + *v2 == target);

}

int64_t findSolutionPart1(const vector<int64_t> &vals, int preamble, bool verbose = false) {

  vector<int64_t> sliced;
  unsigned int k = preamble;

  for (; k < vals.size(); k++) {
    sliced = vector<int64_t>(vals.begin() + k - preamble, vals.begin() + k);
    if (verbose) {
      cout << "-----------\nChecking: " << vals.at(k) 
        << "\n======= Values =======\n";
      for (auto num : sliced) cout << num << '\n';
      cout << "=======================" << endl;

    }
    if (!checkForSummingPair(sliced, vals.at(k))) break;
  }

  return (k == vals.size()) ? -1 : vals.at(k);

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

  cout << "## Day 9 of Advent of Code ##" << endl;

  vector<int64_t> vals;
  int64_t result = 0;
  clock_t start, stop;
  int preamble = (argc > 1) ? stoi(argv[1]) : 25;

  loadDataFromFile("input", vals);
  
  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals, preamble, true);
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

