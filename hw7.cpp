#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "csc160.h"

using namespace std;
using std::ifstream;
using std::stringstream;


//STUDENT: Add the getAverageTemperature function here
//  you used this function in a previous homework and 
//  it has been discussed in lecture, copy it here so 
//  it can be used below



vector<string> splitLine(string line) {
  stringstream lineStream(line);
  string cell;
  vector<string> result;
  while(getline(lineStream, cell, ','))
  {
      result.push_back(cell);
  }
  return result;
}

double parseDouble(string value) {
  size_t sz;
  double val = stod(value, &sz);
  return val;
}

int main() {

  //open file stream that reads this file (already in our replit)
  ifstream str("US_points_hourly_CST.csv");

  //data will go here
  vector<WeatherReport> data;

  string line;
  string header;

  //read the first line into the header string
  getline(str, header);

  vector<string> headerNames = splitLine(header);

  //loop until we get to the end of the file
  while (true) {
    getline(str,line);

    //line length will be zero when we get to end of file
    if (line.length() == 0) {
      //break exits the loop
      break;
    }

    vector<string> row = splitLine(line);

    double windSpeed = parseDouble(row[13]);
    double temperature = parseDouble(row[4]);
    string location = row[1];

    //we did this in hw4
    WeatherReport report = WeatherReport(location);
    report.setWindSpeed(windSpeed);
    report.setTemperature(temperature);

    data.push_back(report);
  }

  //Organize by location, make a map to hold our results where the key is the location
  map<string,vector<WeatherReport>> byLocation;
  //loop throug each element in the data vector
  for (int i = 0; i < data.size(); i++) {
    string location = data[i].getLocation();
    //if this location is not in the map, add an empty vector for this location
    if (byLocation.count(location) <= 0) { //count function is 0 or less if key doesn't exist
      byLocation.insert(pair<string,vector<WeatherReport>>(location, vector<WeatherReport>())); //put an empty vector for this location
    }
    //put this weather report in this location's vector
    byLocation[location].push_back(data[i]);
  }

  //Here we will loop over each item in the map.  An item is a key/value pair.
  //we need to 
  map<string, vector<WeatherReport>>::iterator it; //iterator that will hold the item from the map
  for(it = byLocation.begin(); it != byLocation.end(); it++) { //each iteration, it will point to the next key/value pair
      string location = it->first; //first is the key, the location
      vector<WeatherReport> reports = it->second; //second is the value, the reports for this location
      cout << location << " - " << reports.size() << endl;

      //STUDENT: cout the average temperature for each location

  }

  //STUDENT: find the location with the highest average temperature
}
