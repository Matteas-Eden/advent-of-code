#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

int findSolutionPart1(const vector<int> &vals) {
  int firstNum, secondNum;
  /* Brute force approach to solving problem */
  for (int v1 : vals) {
    firstNum = v1;
    // cout << v1 << endl;
    for (int v2 : vals) {
      secondNum = v2;
      // cout << v1 + v2 << endl;
      if (v2 + v1 == 2020) {
          return v1 * v2;
      }
    }
  }

  return -1;

}

int findSolutionPart2(const vector<int> vals) {
  int firstNum, secondNum, thirdNum;
  /* Brute force approach to solving problem */
  for (int v1 : vals) {
    firstNum = v1;
    for (int v2 : vals) {
      secondNum = v2;
      for (int v3 : vals) {
        if (v3 + v2 + v1 == 2020) {
            return v1 * v2 * v3;
        }
      }
    }
  }

  return -1;
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

  cout << "## Day 1 of Advent of Code ##" << endl;

  vector<int> vals;
  int result;
  clock_t start, stop;

  loadDataFromFile("input", vals);

  /* Part 1 of Day 1 Challenge */
  start = clock();
  result = findSolutionPart1(vals);
  stop = clock();

  cout << "-- Part 1 --" << endl;
  printSolutionsAndTiming(result, start, stop);

  /* Part 2 of Day 1 Challenge */
  start = clock();
  result = findSolutionPart2(vals);
  stop = clock();

  cout << "-- Part 2 --" << endl;
  printSolutionsAndTiming(result, start, stop);

}

