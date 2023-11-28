//Benjamin Smith, last changed 28/11/23
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#include "CustomFunctions.h";

int main()
{
    //Defining necessary vectors
    int line_num_input;
    std::vector<double> x_vector;
    std::vector<double> y_vector;
    std::vector<double> x_errors;
    std::vector<double> y_errors;

    std::vector<double> magnitude_vector;
    std::vector<double> x_to_power_y_vector;

    //Reading in data and errors
    read_file("../input2D_float.txt", x_vector, y_vector);
    read_file("../error2D_float.txt", x_errors, y_errors);

    int lines_in_file = x_vector.size() + 1; //Plus one to as the line with headers is not included in x vector;

    while (true) { //Looping until user quits program
		int selection = 0;
		print_menu();
		std::cin >> selection;

		//Switch to use main menu
		switch (selection) {
		case 1:
			print("Enter the number of lines that you would like to be printed");
            std::cin >> line_num_input;

            if (line_num_input>lines_in_file){
            std::cout << "Error: There are only " << lines_in_file << " lines in this file" << std::endl;
            line_num_input = 5; // So we print 5 lines if the user asks to print more lines than there are in the file
            }
            print("Data: ");
            print_lines("../input2D_float.txt", line_num_input);
			break;
		case 2:
            magnitude_vector.clear(); //Clearing magnitude vector to prevent erros if option chosen more than once
            print("Magnitudes: ");
            calc_magnitude(x_vector, y_vector, magnitude_vector);
			break;
		case 3:
            print("Straight line fit: ");
			fit_straight_line(x_vector, y_vector, y_errors);
			break;
		case 4:
            print("x values raised to the corresponding powers of y: ");
            x_to_power_y_vector.clear();
			x_to_power_y(x_vector, y_vector, x_to_power_y_vector);
			break;
		case 5:
            print("bye!");
			return 0;
			break;
		default:
			std::cout << "Please input an integer between 1 and 5" << std::endl;
		}
    }
}

//g++ -std=c++20 -w AnalyseData.cxx CustomFunctions.cxx -o AnalyseData

    