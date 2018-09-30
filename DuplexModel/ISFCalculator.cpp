// ISFfinal.cpp : main project file.
// Created by James WoMa

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cassert>

using namespace System;
double calc_isf_from_strain_vector(const std::vector<std::vector<double> >& strain, const double time);

int main(array<System::String ^> ^args)
{


    double twitch_duration = 1; //in milliseconds for parabolic it is 500, for sarcomere it is 506. for milliseconds 1
    std::ofstream file("ISFsarcVel[0.5].txt", std::ios::out);
    file << "Delay" << " " << "ISF" << '\n';
    //for(int td = 300; td <= 500; td += 50) {
        for (double delay = 0; delay <= 50; delay += 5)
        {
            std::ostringstream oss;
            /*
            if(fmod(td , 1.0) == 0) {
                oss << "TD[" << td << ".0";
            } else {
                oss << "TD[" << td;
            }
            */

            if(fmod(delay , 1.0) == 0) {
                oss << "SarcVel[0.5]D[" << delay << ".0]L.txt";
            } else {
                oss << "SarcVel[0.5]D[" << delay << "]L.txt";
            }

            std::string fileName = oss.str();
            std::cout << fileName << '\n';
            //input
            int header = 9;
            //nikhil added info if so add 12
            std::vector<std::vector<double> > strain(2);
            double ISFvalue;
            double trash = 0;
            std::string junk;
            std::vector<double> time;

            const char *file_Name = fileName.c_str();

            //file input
            std::ifstream datafile(file_Name);

            //get rid of header
            for (int i = 0; i < header; i++){
                datafile >> junk;
            }


            //first read in all values needed
            int vectorlength = 141;
            int counter = 0;
            std::vector<double> ttime(vectorlength);
            std::vector<double> tduplex(vectorlength);
            std::vector<double> tstate(vectorlength);
            std::vector<std::vector<double>> tstrain(2);
            tstrain[0].resize(vectorlength);
            tstrain[1].resize(vectorlength);
            while(datafile.good()){
                double t;
                double dup;
                double s1;
                double s2;
                double state;
                datafile >> t >> dup >> trash >> trash >> state >> s1 >> trash >> s2 >> trash;
                /*for (int i = 1; i <= 12; i++){ // nikhil added info
                    datafile >> trash;
                }*/
                if (counter <= 140) {
                    ttime[counter] = t;
                    tduplex[counter] = dup;
                    tstrain[0][counter] = s1;
                    tstrain[1][counter] = s2;
                    tstate[counter] = state;
                    counter++;
                }
            }





            /*
                        Traditional ISF calculation
            */

            //find minimum
            assert(tduplex.size() > 1);
            double min_duplex = tduplex[0];
            double min_time = ttime[0];
            int min_point_time = 0;
            assert(tduplex.size() == ttime.size());
            for(int i = 1; i < vectorlength; i++){
                if (min_duplex > tduplex[i]) {
                    min_duplex = tduplex[i];
                    min_time = ttime[i];
                    min_point_time = i;
                    //std::cout << min_time << " " << min_duplex << '\n';
                }
            }

            //find most negative strain derivative & max strain & min strain
            double duplex_derivative = 0;
            double point_time;
            double point_duplex;
            double max_duplex = tduplex[0];
            double dt = ttime[1] - ttime[0]; //used for ISF calculation as well
            for(int i = 0; i < min_point_time; i++){
                if (duplex_derivative > ((tduplex[i+1] - tduplex[i]) / dt)){
                    duplex_derivative = (tduplex[i+1] - tduplex[i]) / dt;
                    point_time = ttime[i];
                    point_duplex = tduplex[i];
                }
                if (max_duplex < tduplex[i+1]){
                    max_duplex = tduplex[i+1];
                }
            }
            //std::cout << "minstrain:" << min_duplex << " maxstrain:" << max_duplex << " pointtime:" << point_time << " pointstrain:" << point_duplex << '\n';


            //find begin ejection and end ejection using slope-point equation
            double BE = ((max_duplex - point_duplex) / duplex_derivative) + point_time;
            double EE = ((min_duplex - point_duplex) / duplex_derivative) + point_time;
            std::cout <<"BE " << BE << " EE " << EE << '\n';

            //find strain during ejection
            for (int i = 0; i < ttime.size(); i++){
                if (ttime[i] > BE && ttime[i] < EE){
                    strain[0].push_back(tstrain[0][i]);
                    strain[1].push_back(tstrain[1][i]);
                }
            }



            /*
                        Isovolumetric Contraction & Ejection Phase Calculation
            */
            /*
            double dt = ttime[1] - ttime[0]; //used for ISF calculation
            for (int i = 0; i < vectorlength; i++){
                if (tstate[i] == 0 || tstate[i] == 1){ //in ejection phase
                    strain[0].push_back(tstrain[0][i]);
                    strain[1].push_back(tstrain[1][i]);
                }
            }
            */



            /*
            //read in file
            while(datafile.good()){
                double t;
                double state;
                double s1;
                double s2;
                datafile >> t >> trash >> trash >> trash >> state;
                if (state == 0 || state == 1){ //in ejection phase
                    datafile >> s1 >> trash >> s2 >> trash;
                    if (datafile.good()){
                        time.push_back(t);
                        strain[0].push_back(s1);
                        strain[1].push_back(s2);
                    }
                } else {
                    datafile >> trash >> trash >> trash >> trash;
                }
            }
            double dt = time[1] - time[0];
            */


            datafile.close();
            ISFvalue = calc_isf_from_strain_vector(strain, dt);
            file.precision(20);
            file << delay/twitch_duration << " " << ISFvalue << '\n';
        }
    //}


    file.close();
    getchar();
    return 0;
}
double calc_isf_from_strain_vector(const std::vector<std::vector<double> >& strain, const double time)
{
    double dt = time;

    int num_components = strain.size();
    int vectorlength = strain[0].size(); //will = strain[shortest].size()
    std::vector<std::vector<double> > derivative_length(num_components);

    //find smallest strain
    std::vector<int> strain_length(num_components, vectorlength);

    //dlambdat creation
    for (int i = 0; i < num_components; i++){
        derivative_length[i].resize(vectorlength - 1); //derivative is 1 less than strain vector length
    }

    for (int i = 0; i < num_components; i++){
        for (int j = 0; j < strain_length[i] - 1; j++){
            derivative_length[i][j] = (strain[i][j+1] - strain[i][j]) / dt;
            //std::cout << derivative_length[i][j] << '\n';
        }
    }

    //split into stretching and shortening
    std::vector<std::vector<double> > e_p (num_components);
    std::vector<std::vector<double> > e_n (num_components);
    for (int i = 0; i < num_components; i++){
        e_p[i].resize(derivative_length[i].size());
        e_n[i].resize(derivative_length[i].size());
    }
    for (int i = 0; i < num_components; i++){
        for (unsigned j = 0; j < derivative_length[i].size() ; j++){
            e_p[i][j] = std::max(derivative_length[i][j], 0.0);
            e_n[i][j] = std::min(derivative_length[i][j], 0.0);
        }
    }

    //temporary variable for adding all strains

    //average ep & en
    std::vector<double> avg_ep(e_p[0].size()); // assuming all strain vector lengths are equal
    std::vector<double> avg_en(e_n[0].size());
    for (int j = 0; j < strain_length[0] - 1; j++){
        double ep_sum = 0;
        double en_sum = 0;
        for (int i = 0; i < num_components; i++){
            ep_sum += e_p[i][j];
            en_sum += e_n[i][j];
        }
        avg_ep[j] = ep_sum / double(num_components);
        avg_en[j] = en_sum / double(num_components);
    }


    //integrate
    double integral_e_p = 0;
    double integral_e_n = 0;
    for (int i = 0; i < strain_length[0] - 1; i++){
        integral_e_p += avg_ep[i] * dt;
        integral_e_n += avg_en[i] * dt;
    }

    //calculate ISF
    double ISF = -1 * integral_e_p / integral_e_n;

  return ISF;
}

