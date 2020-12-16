#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#define NORTH 0
#define EAST 90
#define SOUTH 180
#define WEST 270

using namespace std;

/*
 * Waypoint has:
 * - distance travelled horizontally (east/west)
 * - distance travelled vertically (north/south)
 * */
class Waypoint {
  protected:
    int horzDist;
    int vertDist;

  public:
    Waypoint() {
      this->horzDist = 0;
      this->vertDist = 0;
    } 

    Waypoint(int horzDist, int vertDist) {
      this->horzDist = horzDist;
      this->vertDist = vertDist;
    }

    virtual void rotate(char direction, int degrees) {
      if (direction == 'L') degrees = degrees * -1 + 360; // normalise to clockwise 
      // Perform rotation based on the notion of quadrants
      switch (degrees) {
        case 90:
          swap(horzDist, vertDist);
          vertDist *= -1;
          break;
        case 180:
          horzDist *= -1;
          vertDist *= -1;
          break;
        case 270:
          swap(horzDist, vertDist);
          horzDist *= -1;
          break;
      }
    }

    void moveDirection(char direction, int distance) {
      switch (direction) {
        case 'N':
          vertDist += distance;
          break;
        case 'E':
          horzDist += distance;
          break;
        case 'S':
          vertDist -= distance;
          break;
        case 'W':
          horzDist -= distance;
          break;
      }
    }

    int getVertDist() { return vertDist; }

    int getHorzDist() { return horzDist; }

    int getManhattanDistance() { 
      return abs(horzDist) + abs(vertDist);
    }
};

/*
 * Ship has:
 * - direction it's facing (either cardinal or degrees)
 * */
class Ship : public Waypoint {
  /* Member fields */
  private:
    int facing;

  public:
    // Constructor
    Ship() {
      this->facing = EAST;
    }

    /* Methods */
    void rotate(char direction, int degrees) {
      if (direction == 'L') degrees *= -1;
      this->facing += degrees;
      if (this->facing < 0) this->facing += 360;
      if (this->facing >= 360) this->facing -= 360;
    }

    virtual void moveForward(int distance) {
      switch (facing) {
        case NORTH:
          vertDist += distance;
          break;
        case EAST:
          horzDist += distance;
          break;
        case SOUTH:
          vertDist -= distance;
          break;
        case WEST:
          horzDist -= distance;
          break;
      }
    }

};

class Ferry : public Ship {
  private:
    Waypoint* wp;

  public:
    Ferry(Waypoint* wp) {
      this->wp = wp;
    }

    void moveForward(int distance) {
      vertDist += wp->getVertDist() * distance;
      horzDist += wp->getHorzDist() * distance;
    }

    ~Ferry() { delete wp; }
};


/* Function reuse from Day 8 */
char getDirection(const string &instruction) { return instruction.substr(0, instruction.find_first_of(" "))[0]; }

int getDistance(const string &instruction) {
  int x = stoi(instruction.substr(instruction.find_first_of("1234567890")));
  return (count(instruction.begin(), instruction.end(), '-')) ? x * -1 : x;
}

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

int findSolutionPart1(const vector<string> &vals) {
  Ship ship;

  for (string s : vals) {
    char direction = getDirection(s);
    int distance = getDistance(s);

    if (direction == 'F') ship.moveForward(distance);
    else if (direction == 'R' || direction == 'L') ship.rotate(direction, distance);
    else ship.moveDirection(direction, distance);

  }

  return ship.getManhattanDistance();

}

int findSolutionPart2(const vector<string> &vals) {
  Waypoint *wp = new Waypoint(10, 1);
  Ferry ferry(wp);

  for (string s : vals) {
    char direction = getDirection(s);
    int distance = getDistance(s);

    if (direction == 'F') ferry.moveForward(distance);
    else if (direction == 'R' || direction == 'L') wp->rotate(direction, distance);
    else wp->moveDirection(direction, distance);

  }

  return ferry.getManhattanDistance();

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

  cout << "## Day 12 of Advent of Code ##" << endl;

  vector<string> vals;
  int64_t result = 0;
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

