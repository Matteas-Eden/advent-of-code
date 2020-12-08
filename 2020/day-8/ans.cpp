#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
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

int executeInstruction(const string &instruction, int line, int &acc, bool verbose = false) {
  string opcode = instruction.substr(0, instruction.find_first_of(" "));
  int operand = stoi(instruction.substr(instruction.find_first_of("1234567890")));
  if (count(instruction.begin(), instruction.end(), '-')) operand *= -1;

  if (verbose) cout << "[" << line << "] " << "Opcode: " << opcode << " Operand: " << operand << endl;

  if (opcode == "acc") {
    acc += operand;
    if (verbose) cout << "# ACC: " << acc << endl;
    return line + 1;
  }
  else if (opcode == "jmp") {
    return line + operand;
  }

  return line + 1;

}

int findSolutionPart1(const vector<string> &vals, bool verbose = false) {

  set<int> indices;
  int acc = 0;
  int line = 0;

  while (!count(indices.begin(), indices.end(), line) && line < vals.size()) {
    indices.insert(line);
    line = executeInstruction(vals.at(line), line, acc, verbose);
  }

  return acc;

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

  cout << "## Day 8 of Advent of Code ##" << endl;

  vector<string> vals;
  int result = 0;
  clock_t start, stop;

  loadDataFromFile("input", vals);
  
  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals, true);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  /*
  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, "shiny gold");
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
  */
}

