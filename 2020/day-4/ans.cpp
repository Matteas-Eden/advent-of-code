#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <regex>
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

// Some magic C bs
bool validateStringAsInt(const string &val) {
  char *end;
  long i = strtol(val.c_str(), &end, 10);
  return *end == '\0';
}

bool validateYear(const string &val, int min, int max) {

  // Validate numberness of string itself
  if (val.size() != 4) return false;
  if (!validateStringAsInt(val)) return false;

  // Validate date range
  int year = stoi(val);
  return year >= min && year <= max;

}

// Not good code
bool validateHeight(const string &val) {
  
  size_t sz;
  int num = stoi(val, &sz);
  string suffix = val.substr(sz);

  if (suffix == "in") return num >= 59 && num <= 76;
  else if (suffix == "cm") return num >= 150 && num <= 193;

  return false;

}

// Using if ladder instead of trying to use maps/hashes for string switch
// (also, didn't feel like using regex)
bool validateField(const string& field, const string& val) {

  set<string> eyeColours = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  regex hairColourPattern("^#(?=[0-9a-f]{6}$).*");

  // Four digits between 1920 & 2002 (inclusive)
  if (field == "byr") return validateYear(val, 1920, 2002);
  // Four digits between 2010 & 2020 (inclusive)
  if (field == "iyr") return validateYear(val, 2010, 2020);
  // Four digits between 2020 & 2030 (inclusive)
  if (field == "eyr") return validateYear(val, 2020, 2030);
  /*
   * For cm: 150 -> 193 (inclusive) 
   * For in: 59 -> 76 (inclusive)
   * (guess they don't like short people and/or children)
   * */
  if (field == "hgt") return validateHeight(val);
  // Must start with # and followed by exactly 6 chars 0-9 / a-f
  // (okay I caved into regex)
  if (field == "hcl") return regex_match(val, hairColourPattern);
  // Compared against above set
  if (field == "ecl") return eyeColours.find(val) != eyeColours.end();
  // Nine digit number including leading zeroes
  if (field == "pid") return validateStringAsInt(val) && val.size() == 9;
  return false;
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
        if (numFields == numRequired) valid++;
        numFields = 0;
        continue;
      }

      // Check each id in line against lists
      for (string s : split(line)) {
        idField = split(s,":").at(0);
        // Ignored ones don't affect validity
        if (ignored.find(idField) != ignored.end()) continue;
        // Count valid fields
        if (fields.find(idField) != fields.end()) numFields++;
      }
    }
    inFile.close();
  }
  else { cout << "Error in opening file" << endl; return -1; }

  if (numFields == numRequired) valid++;

  return valid;
}

int findSolutionPart2(const string &path, const set<string> &fields, const set<string> &ignored) {
  string line;
  ifstream inFile(path);
  size_t pos = 0;
  vector<string> pair;
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
        pair = split(s,":");
        cout << "Checking ID: " << pair.at(0) << endl;
        // Ignored ones don't affect validity
        if (ignored.find(pair.at(0)) != ignored.end()) {
          cout << "-!> Optional field" << endl;
          continue;
        }
        // Count valid fields
        if (fields.find(pair.at(0)) != fields.end() && validateField(pair.at(0), pair.at(1))) {
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

  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2("input", fields, ignored);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

}

