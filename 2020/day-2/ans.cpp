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
      /* Need
       *  - min
       *  - max
       *  - target char
       *  - password string
       * */
      string min = line.substr(0, line.find("-"));
      string max = line.substr(line.find("-") + 1, line.find(" ") - line.find("-"));
      string target = line.substr(line.find(":") - 1, 1);
      string password = line.substr(line.find(":") + 2);
      /*cout << min << endl;
      cout << max << endl;
      cout << target << endl;
      cout << password << endl;
      return 1;*/
      vals.push_back({min, max, target, password});
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

  start = clock();
  result = findSolutionPart1(vals);
  stop = clock();

  cout << "-- Part 1 --" << endl;
  printSolutionsAndTiming(result, start, stop);

}

