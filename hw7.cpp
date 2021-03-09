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


/*
  STUDENT:  Write a function that will take a vector of WeatherReport and
            return a vector of WeatherReport that is the daily maximum.
            This will require adding the valid time field to the WeatheReport
            object and then using getByLocationMap function as an example, 
            organize the reports by day.  Then find the max of each day's
            values.
*/

vector<double> getTemperatureValues(vector<WeatherReport> reports) {
  vector<double> data;
  for (int i = 0; i < reports.size(); i++) {
    data.push_back(reports[i].getTemperature());
  }
  return data;
}

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

map<string,vector<WeatherReport>> getByLocationMap(vector<WeatherReport> data) {
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
  return byLocation;
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
    double temperature = parseDouble(row[5]);
    string location = row[1];

    //we did this in hw4
    WeatherReport report = WeatherReport(location);
    report.setWindSpeed(windSpeed);
    report.setTemperature(temperature);

    data.push_back(report);
  }

  Plotter plotter;

  //Organize by location, make a map to hold our results where the key is the location
  map<string,vector<WeatherReport>> byLocation = getByLocationMap(data);

  //plot_data is a vector of vector where each vector in plot_data is a time series that we will plot, one for each location
  vector<vector<double>> plot_data;
  vector<string> rnames;
  //Here we will loop over each item in the map.  An item is a key/value pair.
  //we need to 
  map<string, vector<WeatherReport>>::iterator it; //iterator that will hold the item from the map
  for(it = byLocation.begin(); it != byLocation.end(); it++) { //each iteration, it will point to the next key/value pair
      string location = it->first; //first is the key, the location
      vector<WeatherReport> reports = it->second; //second is the value, the reports for this location
      cout << location << " - " << reports.size() << endl;

      vector<double> locationTemperatures = getTemperatureValues(reports); //get the temperature values for this location, this is what will be plotted
      plot_data.push_back(locationTemperatures); //add this location's data to the plot data
      rnames.push_back(location); //alos add this location to the list of titles
      
  }
  string filename = "all_temps.jpg";
  plotter.write_plot(plot_data, rnames, "Temperature", filename);

  //STUDENT: Use your new function to make a plot that is the daily maximum for each location
  
}
