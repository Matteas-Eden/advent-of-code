#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
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

/*
 * Create a set of all colours of bags that contain a given colour
 * Then create a set of all colours of bags that contain a colour in that set
 * Repeat until none are found
 * */
int findSolutionPart1(const vector<string> &vals, const set<string> &baseColours, bool verbose = false) {

  set<string> colours(baseColours);
  set<string> temp;
  bool found = true;
  string bagColour;
  size_t pos;

  while (found) {
    found = false;
    for (string line : vals) {
      bagColour = line.substr(0, line.find("bags") - 1);
      if (verbose) cout << "@ Checking bag: " << bagColour << endl;
      if (count(colours.begin(), colours.end(), bagColour)) continue;
      for (string colour : colours) {
        pos = line.find("contain");
        if (verbose) cout << "# Looking for: " << colour << endl;
        // Check if colour exists in comma separated list
        if (line.find(colour, pos) != string::npos) {
          if (verbose) cout << "-> Found!" << endl;
          found = true;
          // Find the colour of the container bag and add it
          temp.insert(line.substr(0, line.find("bags") - 1));
        }
      }
      // Copy colours found during loop to main set
      // to prevent issues with insertion during iteration
      if (temp.size()) colours.insert(temp.begin(), temp.end());
      temp.clear();
    }
  }

  return colours.size() - baseColours.size();

}

// Extract contained bags (w/ quantity & colour separate) from a given string
vector<vector<string>> extractBags(const string& s, bool verbose = false) {

  string bag;
  vector<string> bagVec;
  vector<vector<string>> bags;
  string quantity;
  string colour;
  size_t pos, lastPos;
  pos = s.find("contain") + 8;
  lastPos = pos;

  while ((pos = s.find("bag", lastPos)) != string::npos) {
    bag = s.substr(lastPos, pos - lastPos);

    // Strip string of unwanted spaces/chars
    bag.erase(0, bag.find_first_not_of(" ,."));
    bag.erase(bag.find_last_not_of(" ,.") + 1);

    // Split up quantity/colour
    quantity = bag.substr(0, bag.find_first_not_of("0123456789"));
    colour = bag.substr(bag.find_first_not_of("0123456789 "));
    bagVec.push_back(quantity);
    bagVec.push_back(colour);

    // Debug output
    if (verbose) {
      cout << "Got bag!" << endl;
      cout << "-- Quantity: " << quantity << endl;
      cout << "-- Colour: " << colour << endl;
    }

    bags.push_back(bagVec);
    bagVec.clear();
    lastPos = pos + 4;
  }

  return bags;

}

// Let's try this recursively and see how it goes
int64_t findSolutionPart2(const vector<string> &vals, const string& colour, bool verbose = false) {

  int64_t total = 0;
  size_t pos;
  vector<vector<string>> bags;

  if (verbose) cout << "## " << colour << " ##" << endl;

  for (string line : vals) {
      pos = line.find("contain") + 8;
      // Look for colour of bag
      if (line.substr(0, line.find("bags") - 1) == colour) {
        // Now that it's been found, figure out how many bags it needs
        bags = extractBags(line);
      }
  }

  // Calculate total number of bags
  for (vector<string> bag : bags) {
    if (verbose) cout << "Bag: " << bag.at(0) << "|" << bag.at(1) << endl;

    // Base case
    if (bag.at(1) == "no other") return 0;

    // Recursion
    // "I have N many bags + however many bags those bags have"
    total += stoi(bag.at(0)) + stoi(bag.at(0)) * findSolutionPart2(vals, bag.at(1), verbose);
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

  cout << "## Day 7 of Advent of Code ##" << endl;

  vector<string> vals;
  set<string> baseColours = {"shiny gold"};
  int64_t result = 0;
  clock_t start, stop;

  loadDataFromFile("input", vals);
  
  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals, baseColours);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, "shiny gold");
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

}

