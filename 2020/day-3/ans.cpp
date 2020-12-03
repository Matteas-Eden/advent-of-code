#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdint.h>

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

int findSolutionPart1(const vector<string> &vals, bool verbose) {
  int width = vals.at(0).length();
  int pos = 3;
  int numTrees = 0;
  string line;

  if (verbose) {
    cout << "Width: " << width << endl;
    cout << vals.at(0) << endl;
  }

  // Skip the first row
  for (unsigned int i = 1; i < vals.size(); i++) {
    line = vals.at(i);
    if (pos >= width) pos -= width;

    if (line[pos] == '#') {
      if (verbose) line.replace(pos, 1, "X");
      numTrees++;
    } else if (verbose) {
      line.replace(pos, 1, "O");
    }

    if (verbose) cout << line << " ||" << pos << endl;

    pos += 3;
  }

  return numTrees;

}

int64_t findSolutionPart2(const vector<string> &vals, bool verbose, int right, int down) {
  int width = vals.at(0).length();
  int pos = right;
  int64_t numTrees = 0;
  string line;

  if (verbose) {
    cout << "Width: " << width << endl;
    cout << vals.at(0) << endl;
  }

  // Skip the first row
  for (unsigned int i = 1; i < vals.size(); i++) {

    line = vals.at(i);

    if (i % down != 0) {
      if (verbose) cout << line << " ||" << pos << endl;
      continue;
    }

    if (pos >= width) pos -= width;

    if (line[pos] == '#') {
      if (verbose) line.replace(pos, 1, "X");
      numTrees++;
    } else if (verbose) {
      line.replace(pos, 1, "O");
    }

    if (verbose) cout << line << " ||" << pos << endl;

    pos += right;
  }

  return numTrees;

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

  cout << "## Day 3 of Advent of Code ##" << endl;

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
  result = findSolutionPart2(vals, false, 1, 1);
  result *= findSolutionPart2(vals, false, 3, 1);
  result *= findSolutionPart2(vals, false, 5, 1);
  result *= findSolutionPart2(vals, false, 7, 1);
  result *= findSolutionPart2(vals, false, 1, 2);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

}

