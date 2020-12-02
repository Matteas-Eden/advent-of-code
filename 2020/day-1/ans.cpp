#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

int findSolution(const vector<int> &vals) {
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

int main(int argc, char ** argv) {

  vector<int> vals;

  loadDataFromFile("input", vals);

  int result = findSolution(vals);
  if (result == -1) cout << "No solution found" << endl;
  else cout << "Solution: " << result << endl;

}

