#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int loadDataFromFile(string path, vector<vector<string>> &vals) {
  string line;
  ifstream inFile(path);

  /* Load values from file into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      string firstNum = line.substr(0, line.find("-"));
      string secondNum = line.substr(line.find("-") + 1, line.find(" ") - line.find("-"));
      string targetChar = line.substr(line.find(":") - 1, 1);
      string password = line.substr(line.find(":") + 2);
      vals.push_back({firstNum, secondNum, targetChar, password});
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return 1; }

  cout << "Data loaded successfully from " << path << endl;
  return 0;
}

int findSolutionPart1(vector<vector<string>> vals) {

  int numValid = 0;
  int min, max;
  int n;

  for (vector<string> v : vals) {
    min = stoi(v.at(0));
    max = stoi(v.at(1));
    n = count(v.at(3).begin(), v.at(3).end(), v.at(2)[0]);
    if (n >= min && n <= max) numValid++;
  }

  return numValid;

}

int findSolutionPart2(vector<vector<string>> vals) {

  int numValid = 0;
  int posOne, posTwo;

  for (vector<string> v : vals) {
    // Convert from 1-based indexing to 0-based
    posOne = stoi(v.at(0)) - 1;
    posTwo = stoi(v.at(1)) - 1;

    if ((v.at(3)[posOne] == v.at(2)[0]) != (v.at(3)[posTwo] == v.at(2)[0])) numValid++;
  }

  return numValid;

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

  cout << "## Day 2 of Advent of Code ##" << endl;

  vector<vector<string>> vals;
  int result = -1;
  clock_t start, stop;

  loadDataFromFile("input", vals);

  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  cout << "-- Part 2 --" << endl;
  start = clock();
  result = findSolutionPart2(vals);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

}

