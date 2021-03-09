
#include "csc160.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


WeatherReport::WeatherReport(string location) {
  this->location = location;
  this->temperature = FILL_VALUE;
  this->windSpeed = FILL_VALUE;
}

WeatherReport::~WeatherReport() {
}

void WeatherReport::setTemperature(double temperature) {
  this->temperature = temperature;
}

double WeatherReport::getTemperature() {
  return this->temperature;
}

void WeatherReport::setWindSpeed(double windSpeed) {
  this->windSpeed = windSpeed;
}

double WeatherReport::getWindSpeed() {
  return this->windSpeed;
}

string WeatherReport::getLocation() {
  return this->location;
}

void Plotter::write_plot(vector<vector<double>> data, vector<string> seriesNames, string title, string filename) {
  ofstream txt("plot_data.txt");
  for (int i = 0; i < data[0].size(); i++) {
    string line = to_string(i);
    for (int j = 0; j < data.size(); j++) {
      line += " " + to_string(data[j][i]);
    }
    line += "\n";
    txt.write(line.c_str(), line.size());
  }
  txt.close();
  string cmd = "";
  cmd += "set xtics rotate by -45\n";
  cmd += "set title '" + title + "'\n";
  cmd += "set terminal jpeg\n";
  cmd += "set output '" + filename + "'\n";
  cmd += "plot ";
  for (int i = 0; i < data.size(); i++) {
    if (i > 0) {
      cmd += ", ";
    }
    cmd += "'plot_data.txt' using 1:" + to_string(i+2) + " title '" + seriesNames[i] + "' with lines linetype " + to_string(i+1) + " linewidth 1";
  }
  
  ofstream out_cmd("plot_commands.txt");
  out_cmd.write(cmd.c_str(), cmd.size());
  out_cmd.close();
  string plot_cmd = "/usr/bin/gnuplot -c plot_commands.txt";
  system(plot_cmd.c_str());
}