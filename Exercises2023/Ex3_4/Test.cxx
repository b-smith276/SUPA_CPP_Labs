#include "FiniteFunctions.h"
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

int main()
{
    //Converting file to ifstream
    std::string file_name("Outputs/data/MysteryData14104.txt");
    std::ifstream data_file(file_name);

    std::vector<double> mystery_data;
    double entry;

    while (data_file >> entry) { //Reading in mystery data into a vector
        mystery_data.push_back(entry);
    }

    double mean_of_mystery_data;

    //Calculating mean of mystery data for use when visually matching it to a function
    for (auto iterator = mystery_data.begin(); iterator<mystery_data.end(); iterator++){
        mean_of_mystery_data += (*iterator)/mystery_data.size();
    }

    data_file.close();

    //Testing default function
    FiniteFunction default_func;
    default_func.plotFunction();
    default_func.plotData(mystery_data,40); //40 used due to bug in given code for default constructor
    default_func.printInfo();

    //Testing normal distribution
    NormalDistribution normal_dist(-10.0, 10.0, mean_of_mystery_data, 1.0, "GaussianFunction");
    normal_dist.plotFunction();
    normal_dist.plotData(mystery_data,40);
    normal_dist.printInfo();

    //Testing Cauchy-Lorentz
    Lorentz lorentz_dist(-10.0, 10.0, mean_of_mystery_data, 0.8, "LorentzFunction"); //These values for mean and FWHM match the mystery data
    lorentz_dist.plotFunction();
    lorentz_dist.plotData(mystery_data,40);
    lorentz_dist.printInfo();

    //Testing negative Crystal Ball distribution
    NegativeCrystalBall negative_crystal_ball_dist(-10.0, 10.0, 1.0, 1.0, 2.0, 1.0, "NegativeCrystalBallFunction");
    negative_crystal_ball_dist.plotFunction();
    negative_crystal_ball_dist.plotData(mystery_data,40);
    negative_crystal_ball_dist.printInfo();

    //New Lorentz distribution to test metropolis algorithm
    Lorentz lorentz_dist_for_sampling(-10.0, 10.0, mean_of_mystery_data, 0.8, "SampledLorentzFunction");
    std::vector<double> random_samples;
    lorentz_dist_for_sampling.plotFunction();
    lorentz_dist_for_sampling.SampleFromFunction(1000000, random_samples);
    lorentz_dist_for_sampling.plotData(random_samples,41, false); //Use of false to label points as sampled points in plot legend

    //Bonus task
    std::random_device rd; //Initialising true random number to seed pseudo random number generator
    std::mt19937 gen(rd()); //Mersenne Twister 19937 pseudo random number generator seeded with random device

    std::uniform_real_distribution<double> x_uniform_function(-1.0, 1.0);
    std::uniform_real_distribution<double> y_uniform_function(-1.0, 1.0);

    int n_iterations = 10000;
    double points_in_circle;
    double total_points;
    

    for (int i = 0; i<n_iterations; i++){
        total_points += 1.0;
        double random_x_coord = x_uniform_function(gen);
        double random_y_coord = y_uniform_function(gen);

        double r_squared = std::pow(random_x_coord,2)+std::pow(random_y_coord,2);
        if (r_squared <= 1.0){
            points_in_circle += 1.0;
        }
    }


    double pi = 4.0*(points_in_circle/total_points);
    std::cout << "Pi = " << pi <<" calculated with " << n_iterations << " iterations" << std::endl;

    return 0;
}