//// TestSarcomereClass.cpp : main project file.
//// Created by James WoMa
//
//#include "Sarcomere.h"
//#include <fstream>
//#include <vector>
//#include <cmath>
//
//int main(int argc, const char * argv[])
//{
//
//    //For debugging: Console::WriteLine(L"Hello World");
//    Sarcomere s(.6, 0, 0, 0, 0, 1, 500);
//    double time = 0;
//    double dtime = .01;
//    double iteration = 10000;
//    double slambda = 1;
//    double force;
//    
//    //file creation
//    std::ofstream file("sarcomere.txt", std::ios::out);
//    file << "Time" << "," << "Calcium" << "," << "Troponin" << "," << "CrossBridges" << "," << "Q1" << "," << "Q2" << "," << "Force" << '\n';
//    std::vector<double> state;
//    for (double i=0; i<=iteration; i++){
//        s.integrate(time, dtime, slambda);
//        force = s.calcForce(time, dtime, slambda);
//        state = s.getstate();
//        file << time << "," << state[state_ca] << "," << state[state_tn] << "," << state[state_xb] << "," << state[state_q1] << "," << state[state_q2] << "," << force << '\n';
//        
//        time += dtime;
//        
//    }
//    file.close();
//    return 0;
//}
