//Benjamin Smith, last changed 28/11/23
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

//Function to read in data, data stored in 2 vectors, const use d to protect data and pass by reference used to prevent copying
void read_file(const std::string& file_name, std::vector<double>& x_values, std::vector<double>& y_values )
{
    std::ifstream input_file(file_name);
    std::string line_in_file;
    int counter;

    while (std::getline(input_file, line_in_file)){ //Reading lines as string
        counter += 1;
        double x,y;
        char dummy; //Dummy needed to read in comma

        if (counter!=1){ //Skipping first line as it only contains headers
            std::istringstream line_as_sstream(line_in_file);
            line_as_sstream >> x >> dummy >> y;
            x_values.push_back(x); //Storing x and y as vectors
            y_values.push_back(y);
        }
    }
    input_file.close();
}

//Overloaded print function to print a double
void print(double number)
{
    std::cout << number << std::endl;
}

//Overloaded print function to print a string
void print(std::string string)
{
    std::cout << string << std::endl;
}

//Overloaded print function to print a vector
void print(const std::vector<double>& vector)
{
    for (auto iterator = vector.begin(); iterator<vector.end(); iterator++){
        std::cout << *iterator << std::endl;
    }
}

//Overloaded function to print string to file
void output_to_file(const std::string string, const std::string file_name)
{
    std::ofstream out_file(file_name);
    out_file << string;
    out_file.close();
}

//Overloaded function to print vector to file
void output_to_file(const std::vector<double>& vector , std::string file_name)
{
    std::ofstream out_file(file_name);
    for (auto iterator = vector.begin(); iterator<vector.end(); iterator++){
        out_file << *iterator << std::endl;
    }
    out_file.close();
}

//Function to calculate magnitudes of data assuming x and y values are components of a vector
void calc_magnitude(const std::vector<double>& x_values, const std::vector<double>& y_values, std::vector<double>& magnitudes)
{
    for (int i{0}; i<x_values.size(); i++){
        double magnitude = std::sqrt(x_values[i]*x_values[i] + y_values[i]*y_values[i]);
        print(magnitude);
        magnitudes.push_back(magnitude);
    }
    output_to_file(magnitudes, "magntiudes_of_data_points.txt");
}

//Function to perform least squares fit of data to a straight line
//Ouputs straight line equation and reduced chi squared to the terminal and to a file
void fit_straight_line(const std::vector<double>& x_values, const std::vector<double>& y_values, const std::vector<double>& y_errors)
{
    //Initialising to zero in case function is run multiple times
    double x_average{0};
    double y_average{0};

    //Calculating averages for x and y
    for(int i=0; i<x_values.size(); i++){
        x_average += x_values[i]/(x_values.size());
        y_average += y_values[i]/(y_values.size());
    }

    double numerator{0}; //Numerator and denominator of least squares formula
    double denominator{0};

    //Calculating numerator and denominator of least squares expression for the gradient of a straight line
    for (int j=0; j<x_values.size(); j++){
        numerator += (x_average-x_values[j])*(y_average-y_values[j]);
        denominator += (x_average-x_values[j])*(x_average-x_values[j]);
    }

    double m = numerator/denominator; //Gradient of straight line y = mx + c
    double c = y_average-m*x_average; //y intercept

    std::ostringstream equation_stream;
    equation_stream << "y = "<< m << "x + "<< c; //Using string stream to format output

    print(equation_stream.str()); //Using overloaded print function for a string

    double chi_squared{0};

    for (int k=0; k<y_values.size(); k++){
        //Calculating chi squared using errors on y values only
        chi_squared += std::pow((y_values[k]-(m*x_values[k]+c))/y_errors[k],2);
    }

    //Reduced chi squared = chi squared/Ndof
    double reduced_chi_squared = chi_squared/(y_values.size()-2);
    std::ostringstream chi_squared_sstream;
    chi_squared_sstream << "Reduced chi squared: " << reduced_chi_squared; //Formatting output
    print(chi_squared_sstream.str());

    equation_stream << std::endl << "Reduced chi squared: " << reduced_chi_squared;

    //Writing equation to file using ofstream
    output_to_file(equation_stream.str(),"fitting_straight_line_output.txt");
}

//Function to print lines n_lines of a file
void print_lines(const std::string& file_name, const double& n_lines)
{
    std::ifstream input_file(file_name);
    std::string line_in_file;
    int counter;

    while (std::getline(input_file, line_in_file)){ 
        counter += 1;

        if (counter<=n_lines){ //Printing n_lines of file
            print(line_in_file);
        }
    }
}

//Function to calculate value^power
double exponentiate(double value, int power)
{
    if(power==0)
        return 1;//Anything to power zero is 1
    
    return (value*exponentiate(value,power-1)); //Using recursion to calculate power without loop or pow
}

//Function to calculate x values to the power of their corresponding y value
void x_to_power_y(const std::vector<double>& x_values, const std::vector<double>& y_values, std::vector<double>& exponentiated_x_values)
{
   for (int i=0; i<x_values.size(); i++){
    exponentiated_x_values.push_back(exponentiate(x_values[i], std::round(y_values[i]))); //Using rounded exponentials rather than truncated
   }
   print(exponentiated_x_values);
   output_to_file(exponentiated_x_values, "x_values_to_power_of_y.txt");
}


//Printing menu in visually appealing way
void print_menu()
{
	std::cout << "================Main menu=================" << std::endl;
	std::cout << "1: List lines in file" << std::endl;
	std::cout << "2: List magnitudes of data points" << std::endl;
	std::cout << "3: Fit a straight line to the data using a least squares fit" << std::endl;
	std::cout << "4: Raise x data to the power of the corresponding y data rounded to the nearest integer" << std::endl;
	std::cout << "5: Quit" << std::endl;
	std::cout << "==========================================" << std::endl;
}

