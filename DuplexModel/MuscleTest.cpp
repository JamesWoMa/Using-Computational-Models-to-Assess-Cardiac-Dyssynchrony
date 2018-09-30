////
////  main.cpp
////  DuplexModel
////
////  Created by James WoMa
//
//#include <iostream>
//#include <fstream>
//#include "Muscle.h"
//#include "Filament.h"
//#include <cmath>
//#include <vector>
//using namespace std;
//
//enum mode {ISOMETRIC = 0, ISOTONIC, PHYSIOISO, PHYSIOFILL};
//
//bool compareDouble(double a, double b);
//
//int main(int argc, const char * argv[])
//{
//    bool landMuscle = false;
//    
//    const double time_increment = 0.1;
//    const double Time = 700;
//    mode state = ISOMETRIC;
//    
//    double Fa = 100;//44.76376;
//    double F = 0;
//    double derivative;
//    double beta;
//    double unstretchedPassive;
//    double start;
//    std::vector<double> args(8);
//    Filament::FilamentType ft;
//    
//    if(!landMuscle) {
//        /**
//         Construction of muscle with parabolic filament
//         */
//        double duration = 500;
//        double amplitude = 43;
//        double unstretched = 1;
//        double delay = 0;
//        double width = 300;
//        start = 1.1;
//        args[0] = duration;
//        args[1] = amplitude;
//        args[2] = unstretched;
//        args[3] = delay;
//        args[4] = width;
//        beta = 0.5;
//        unstretchedPassive = 1;
//        ft = Filament::TRI_FT;
//        
//    } else {
//        
//        /**
//         Construction of muscle with sarcomere
//         */
//        double ca = .02;
//        double tn = 0;
//        double xb = 0;
//        double q1 = 0;
//        double q2 = 0;
//        double t_cycle = 700;
//        double delay = 90;
//        start = 1.1;
//        args[0] = ca;
//        args[1] = tn;
//        args[2] = xb;
//        args[3] = q1;
//        args[4] = q2;
//        args[5] = start;
//        args[6] = t_cycle;
//        args[7] = delay;
//        beta = .5;
//        unstretchedPassive = 1;
//        ft = Filament::LAND_FT;
//    }
//    
//    derivative = 0;
//    
//    Muscle muscle(ft,args,beta,unstretchedPassive,start, 5);
//    
//    const double initLambda = muscle.getLambda();
//    
//    
//    //std::ofstream file("SarcMuscleNoLoad.txt", std::ios::out);
//    std::ofstream file("SarcMuscleNoDelay.txt", std::ios::out);
//    file << "# Time" << " " << "Force" << " " << "Active_Force" << " " << "Passive_Force" << " " << "Lambda" << " " << "Derivative" << " " << "Mode";
//    muscle.write_header(file);
//    file << '\n';
////    
////    file << 0 << " " << 0 << " " << 0 << " " << 0 << " " << lambda << " " << derivative << " " << state;
////    if(landMuscle) {
////        muscle.write_timestep(0, file);
////    } else {
////        file << '\n';
////    }
//    
//    //for(int i = 0; i < 5; i++)
//    //  std::cout << muscle.getSarcomereForce(lambda, 10, time_increment) << std::endl;
//    
//    int i = 1;
//    mode newState = state;
//    //int timeMark = -1;
//    
//    double returnRate = 0.0;
//    for(double time = 0; time < Time; time += time_increment) {
//        //state = ISOMETRIC;
//        switch(state) {
//                
//            case ISOMETRIC:
//            {
//                F = muscle.getForce(time, time_increment, muscle.getLambda());
//                
//                if(F >= Fa) {
//                    newState = ISOTONIC;
//                }
//            }
//                break;
//                
//            case ISOTONIC:
//            {
//                double oldLambda = muscle.getLambda();
//                if(time > 0) {
//                    muscle.getLambda(time, time_increment, Fa);
//                }
//                
//                derivative = (muscle.getLambda() - oldLambda)/(time_increment);
//                
//                if(derivative > 0) {
//                    newState = PHYSIOISO;
//                }            }
//                break;
//                
//            case PHYSIOISO:
//            {
//                F = muscle.getForce(time, time_increment, muscle.getLambda());
//                if(F <= (0.15*Fa)) {
//                    returnRate = (initLambda - muscle.getLambda())/100;
//                    newState = PHYSIOFILL;
//                }
//            }
//                break;
//                
//            case PHYSIOFILL:
//            {
//                double lambda = muscle.getLambda();
//                lambda += (returnRate*time_increment);
//                muscle.setLambda(lambda);
//                
//                F = muscle.getForce(time, time_increment, muscle.getLambda());
//                
//                if(lambda >= muscle.getStartingLambda()) {
//                    lambda = muscle.getStartingLambda();
//                    newState = ISOMETRIC;
//                }
//            }
//                break;
//                
//        }
//        
//        
//        state = newState;
//        
//        
//        if(i % 100 == 0) {
//            file << time + time_increment << " " << F << " " << muscle.getSarcomereForce(time, time_increment, muscle.getLambda()) << " " << muscle.getPassiveForce(muscle.getLambda()) << " " << muscle.getLambda() << " " << derivative << " " << state;
//            if(landMuscle) {
//                //muscle.write_timestep(time, file);
//            } else {
//                file << '\n';
//            }
//        }
//        muscle.integrate(time, time_increment);
//        i++;
//        //std::cout << "C" << " " << "Lsc" << std::endl;
//        std::ofstream file2("Other", std::ios::out);
//        //muscle.write_timestep(time, file2);
//        //std::cout << muscle.getLambda() << " " << state << std::endl;
//    }
//}
//
//bool compareDouble(double a, double b) {
//    
//    if(abs(a - b) < 0.1e-10) {
//        return true;
//    } else {
//        return false;
//    }
//}
//
//
