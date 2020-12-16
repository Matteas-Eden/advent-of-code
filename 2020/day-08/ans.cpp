#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
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

string getOpcode(const string &instruction) { return instruction.substr(0, instruction.find_first_of(" ")); }

int getOperand(const string &instruction) {
  int x = stoi(instruction.substr(instruction.find_first_of("1234567890")));
  return (count(instruction.begin(), instruction.end(), '-')) ? x * -1 : x;
}

int executeInstruction(const string &instruction, int line, int &acc, bool verbose = false) {
  string opcode = getOpcode(instruction);
  int operand = getOperand(instruction);

  if (verbose) cout << "[" << line + 1 << "] " << "Opcode: " << opcode << " Operand: " << operand << endl;

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

// For a brute force approach to Part 2
int validateSequence(const vector<string> &vals, bool verbose = false) {

  set<int> indices;
  int acc = 0;
  int line = 0;

  while (!count(indices.begin(), indices.end(), line) && line < vals.size()) {
    indices.insert(line);
    line = executeInstruction(vals.at(line), line, acc, verbose);
  }

  return (line == vals.size()) ? acc:-1;

}

string flipOpcode(const string &opcode) { return (opcode == "jmp") ? "nop" : "jmp"; }

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

/*
 * A cool idea, but not the right answer. I'm leaving this here because I still
 * like the thinking behind it, even if I couldn't get it to work.
 * ===========================================================================
 *
 * There is exactly one instruction that causes the program to loop.
 * However, this may not be instruction that directly leads to the repeated
 * instruction; it may be the instruction that indirectly leads to it.
 *
 * My approach:
 * - Track all 'jmp' instructions
 * - Once a loop is detected, stop and label the 'jmp' instruction with the
 *   highest line number as the 'culprit'
 * - Substitute that instruction out, reset accumulator, then re-run program
 * */
/*
int findSolutionPart2(vector<string> &vals, bool verbose = false) {

  set<int> indices;
  map<int, string, greater<int>> executed;
  int acc = 0;
  int line = 0;

  // Find where the program repeats an instruction
  while (!count(indices.begin(), indices.end(), line) && line < vals.size()) {
    executed.insert(pair<int,string>(line, vals.at(line)));
    indices.insert(line);
    line = executeInstruction(vals.at(line), line, acc, verbose);
  }

  map<int,string>::const_iterator it = executed.begin();

  cout << "Map.begin(): {" << it->first << ", " << it->second << "}" << endl; 
  char c = getchar();

  // Find the line that (indirectly) causes the program to loop
  // vals.at(it->first) = "nop 1";
  vals.at(316) = "nop 1";

  // Reset acc and start again with fixed instruction in place
  line = 0;
  acc = 0;
  while (line < vals.size()) {
    line = executeInstruction(vals.at(line), line, acc, verbose);
  }

  return acc;

}*/

/* This is the one that works - but don't ask about the time complexity
 * =========================================================================
 *
 * Iterate over the sequence, flipping 'jmp' and 'nop' instructions until the
 * exact one that causes the boot loop is found
 * */
int findSolutionPart2(vector<string> &vals, bool verbose = false) {

  string origInstr;
  int acc;
  vector<string>::iterator it = vals.begin();

  while (it != vals.end()) {

    // Check instruction and flip appropriately
    if (getOpcode(*it) == "jmp" || getOpcode(*it) == "nop") {
      origInstr = *it;
      *it = flipOpcode(getOpcode(*it)) + " " + to_string(getOperand(*it));
      if (verbose) cout << "----- [" 
                        << it - vals.begin() + 1 
                        << "] -----\n" 
                        << "Original: " 
                        << origInstr 
                        << "\nFlipped: " 
                        << *it 
                        << "\n-----------------" << endl;

      // Validate correct sequence is found
      if ((acc = validateSequence(vals, verbose)) != -1) {
        if (verbose) cout << "The Culprit: " << origInstr << endl;
        return acc;
      }

      // Didn't find correct sequence, so revert change
      *it = origInstr;

    }

    it++;

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

  cout << "## Day 8 of Advent of Code ##" << endl;

  vector<string> vals;
  int result = 0;
  clock_t start, stop;

  loadDataFromFile("input", vals);
  
  cout << "-- Part 1 --" << endl;
  start = clock();
  result = findSolutionPart1(vals, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);

  cout << "-- Part 2 --" << endl;
  
  start = clock();
  result = findSolutionPart2(vals, false);
  stop = clock();

  printSolutionsAndTiming(result, start, stop);
}

