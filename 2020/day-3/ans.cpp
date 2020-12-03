#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

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

int findSolutionPart1(const vector<string> &vals) {
  int width = vals.at(0).length();
  int pos = 3;
  int numTrees = 0;
  string line;

  cout << "Width: " << width << endl;
  cout << vals.at(0) << endl;

  // Skip the first row
  for (unsigned int i = 1; i < vals.size(); i++) {
    line = vals.at(i);
    if (pos >= width) pos -= width;

    if (line[pos] == '#') {
      line.replace(pos, 1, "X");
      numTrees++;
    } else {
      line.replace(pos, 1, "O");
    }

    cout << line << " ||" << pos << endl;

    pos += 3;
  }

  return numTrees;

}

void printSolutionsAndTiming(int result, clock_t start, clock_t stop) {
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
  int result = -1;
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
  result = findSolutionPart2(vals);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  */
}

