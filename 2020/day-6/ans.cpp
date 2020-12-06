#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

int findSolutionPart1(string path) {
  string line;
  ifstream inFile(path);
  vector<set<char>> groups;
  int total = 0;

  // Create set for first group
  set<char> temp;
  groups.push_back(temp);

  /* Process each line as it's read into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      // Create new set for each group
      if (line == "") { 
        set<char> temp; 
        groups.push_back(temp); 
        continue; 
      }
      for (const char &c : line) { groups.back().insert(c); }
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return -1; }

  // Sum up number of (unique) characters for each group
  for (set<char> g : groups) {
    total += g.size();
  }

  return total;

}

int findSolutionPart2(string path) {
  string line;
  ifstream inFile(path);
  map<char, int> groupAnswers;
  map<char, int>::const_iterator it;
  int total = 0;
  int n = 0;

  /* Process each line as it's read into memory */
  if (inFile.is_open()){
    while (getline(inFile, line)){
      // For each group, go through each question and check
      // if number of votes equals number of people in group
      if (line == "") {
        for (it = groupAnswers.cbegin(); it != groupAnswers.cend(); it++) {
          if (it->second == n) total++;
        }
        n = 0;
        groupAnswers.clear();
        continue; 
      }
      // Update map with count of each character (tracking number of votes)
      for (const char &c : line) {
        if (groupAnswers.count(c) > 0) {
          groupAnswers.at(c)++;
        } else groupAnswers.insert(pair<char, int> (c, 1));
      }
      n++;
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return -1; }

  for (it = groupAnswers.cbegin(); it != groupAnswers.cend(); it++) {
    if (it->second == n) total++;
  }

  return total;

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

  cout << "## Day 6 of Advent of Code ##" << endl;

  vector<string> vals;
  int64_t result = 0;
  clock_t start, stop;
  
  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1("input");
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2("input");
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

}

