#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

using namespace std;

vector<string> split(const string &str, const string &delim = " ") {
  size_t pos = 0, lastPos = 0;
  vector<string> tokens;
  while ((pos = str.find(delim, lastPos)) != string::npos) {
    tokens.push_back(str.substr(lastPos, pos-lastPos));
    lastPos = pos + 1;
  }
  tokens.push_back(str.substr(lastPos,pos-lastPos));
  return tokens;
}

int findSolutionPart1(const string &path, const set<string> &fields, const set<string> &ignored) {
  string line;
  ifstream inFile(path);
  size_t pos = 0;
  string idField;
  short int numFields = 0;
  short int numRequired = fields.size() - ignored.size();
  int valid = 0;

  /* Process data as it's loaded from file */
  if (inFile.is_open()) {
    while (getline(inFile, line)) {
      // Determine validity of passport on blank lines
      if (line == "") {
        if (numFields == numRequired) {
          valid++;
          cout << "# Passport valid" << endl;
        } else cout << "! Passport invalid -- Missing " << numRequired-numFields << " fields" << endl;
        numFields = 0;
        continue;
      }

      // Check each id in line against lists
      for (string s : split(line)) {
        idField = split(s,":").at(0);
        cout << "Checking ID: " << idField << endl;
        // Ignored ones don't affect validity
        if (ignored.find(idField) != ignored.end()) {
          cout << "-!> Optional field" << endl;
          continue;
        }
        // Count valid fields
        if (fields.find(idField) != fields.end()) {
          numFields++;
          cout << "-> Found in list!" << endl;
        }
      }
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return -1; }

  if (numFields == numRequired) {
    valid++;
    cout << "# Passport valid" << endl;
  } else cout << "! Passport invalid -- Missing " << numRequired-numFields << " fields" << endl;

  return valid;
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

  cout << "## Day 4 of Advent of Code ##" << endl;

  /* How to solve Part 1
   *
   * - Iterate through input file
   * - Take each passport (separated by blank lines) in isolation
   * - Extract out each 
   * */

  vector<string> vals;
  set<string> fields = {
    "byr", 
    "iyr", 
    "eyr", 
    "hgt", 
    "hcl", 
    "ecl", 
    "pid", 
    "cid"
  };
  set<string> ignored = {"cid"};
  int result = 0;
  clock_t start, stop;

  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1("input", fields, ignored);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  /*cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, false, 1, 1);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);*/

}

