//Benjamin Smith, last changed 28/11/23
#pragma once
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//Declaring functions defined in CustomFunctions.cxx
void print(double number);

void print(std::string string);

void calc_magnitude(const std::vector<double>& x_values, const std::vector<double>& y_values, std::vector<double>& magnitudes);

void print_lines(const std::string& file_name, const double& n_lines);

void fit_straight_line(const std::vector<double>& x_values, const std::vector<double>& y_values, const std::vector<double>& y_errors);

double exponentiate(double value, int power);

void x_to_power_y(const std::vector<double>& x_values, const std::vector<double>& y_values, std::vector<double>& exponentiated_x_values);

void output_to_file(const std::string string, const std::string file_name);

void output_to_file(const std::vector<double>& vector , std::string file_name);

void print_menu();

void read_file(const std::string& file_name, std::vector<double>& x_values, std::vector<double>& y_values);
