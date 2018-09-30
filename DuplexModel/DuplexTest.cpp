////
////  DuplexTest.cpp
////  DuplexModel
////
////  Created by James WoMa
////
//
//#include <iostream>
//#include <fstream>
//#include "Duplex.h"
//#include <cmath>
//
//using namespace std;
//
//enum mode {ISOMETRIC = 0, ISOTONIC, PHYSIOISO, PHYSIOFILL};
//
//int main(int argc, const char * argv[])
//{
//    const double time_increment = .001;
//    const double Time = 500;
//    
//    double Fa = 100;
//    
//    /**
//     Construction of duplex with parabolic filaments
//     */
//    
//    //Muscle 1
//    double m1duration = 500;
//    double m1amplitude = 43;
//    double m1unstretched = 1;
//    double m1delay = 0;
//    double m1width = 300;
//    double m1lambda = 1;
//    std::vector<double> m1args(5);
//    m1args[0] = m1duration;
//    m1args[1] = m1amplitude;
//    m1args[2] = m1unstretched;
//    m1args[3] = m1delay;
//    m1args[4] = m1width;
//    double m1k = 2.0;
//    double m1unstretchedPassive = 1;
//    double m1unstretchedLength = 5;
//    
//    //Muscle 2
//    double m2duration = 500;
//    double m2amplitude = 43;
//    double m2unstretched = 1;
//    double m2delay = 50;
//    double m2width = 300;
//    double m2lambda = 1;
//    std::vector<double> m2args(5);
//    m2args[0] = m2duration;
//    m2args[1] = m2amplitude;
//    m2args[2] = m2unstretched;
//    m2args[3] = m2delay;
//    m2args[4] = m2width;
//    double m2k = 2.0;
//    double m2unstretchedPassive = 1;
//    double m2unstretchedLength = 5;
//
//    Duplex duplex1(Filament::PARA_FT,m1args,m1k,m1unstretchedPassive,m1lambda, m1unstretchedLength,m2args,m2k,m2unstretchedPassive,m2lambda,m2unstretchedLength);
//    mode state1 = ISOMETRIC;
//    double F1 = 0;
//    double derivative1 = 0;
//    
//    /**
//     Construction of duplex with sarcomeres
//     */
//    
//    //Muscle 3
//    double ca = .55;
//    double tn = 0;
//    double xb = 0;
//    double q1 = 0;
//    double q2 = 0;
//    double t_cycle = 500;
//    double m3delay = 0;
//    double m3lambda = 1.1;
//    std::vector<double> m3args(8);
//    m3args[0] = ca;
//    m3args[1] = tn;
//    m3args[2] = xb;
//    m3args[3] = q1;
//    m3args[4] = q2;
//    m3args[5] = m3lambda;
//    m3args[6] = t_cycle;
//    m3args[7] = m3delay;
//    double beta3 = 0.5;
//    double m3unstretchedPassive = 1;
//    double m3unstretchedLength = 5;
//    
//    //Muscle 4
//    double ca4 = .55;
//    double tn4 = 0;
//    double xb4 = 0;
//    double q14 = 0;
//    double q24 = 0;
//    double t_cycle4 = 500;
//    double m4lambda = 1.1;
//    double m4delay = 100;
//    std::vector<double> m4args(8);
//    m4args[0] = ca4;
//    m4args[1] = tn4;
//    m4args[2] = xb4;
//    m4args[3] = q14;
//    m4args[4] = q24;
//    m4args[5] = m4lambda;
//    m4args[6] = t_cycle4;
//    m4args[7] = m4delay;
//    double beta4 = 0.5;
//    double m4unstretchedPassive = 1;
//    double m4unstretchedLength = 5;
//    
//    Duplex duplex2(Filament::LAND_FT,m3args,beta3,m3unstretchedPassive,m3lambda, m3unstretchedLength,m4args,beta4,m4unstretchedPassive,m4lambda, m4unstretchedLength);
//    mode state2 = ISOMETRIC;
//    double F2 = 0;
//    double derivative2 = 0;
//    
//    std::ofstream file("duplexNoLoad.txt", std::ios::out);
//    file << "Time" << " " << "D1Force" << " " << "D1M1Lambda" << " " << "D2M2Lambda" << " " << "D1Lambda" << " " << "Mode1" << " " << "D2Force" << " " << "D2M1Lambda" << " " << "D2M2Lambda" << " "<< "D2Lambda" << " " << "Mode2" << '\n';
//    file << '\n';
//    
//    file << 0 << " " << F1 << " " << m1lambda << " " << m2lambda << " " <<duplex1.getLambda() << " " << state1 << " " << F2 << " " << m3lambda << " " << m4lambda << " " << duplex2.getLambda() << " " << state2 << '\n';
//    
//    int i = 0;
//    mode newState1 = state1;
//    mode newState2 = state2;
//    
//    double returnRate = .0008;// / 8;
//    for(double time = 0; time < Time; time += time_increment) {
//        //std::cout << time << std::endl;
//        switch(state1) {
//                
//            case ISOMETRIC:
//            {
//                F1 = duplex1.getForce(time, time_increment, duplex1.getLambda());
//                
//                if(F1 >= Fa) {
//                    newState1 = ISOTONIC;
//                }
//            }
//                break;
//                
//            case ISOTONIC:
//            {
//                double oldLambda = duplex1.getLambda();
//                if(time > 0) {
//                    duplex1.calcLambda(time, time_increment, Fa);
//                }
//                
//                derivative1 = (duplex1.getLambda() - oldLambda)/(time_increment);
//                
//                if(derivative1 > 0) {
//                    newState1 = PHYSIOISO;
//                }
//            }
//                break;
//                
//            case PHYSIOISO:
//            {
//                F1 = duplex1.getForce(time, time_increment, duplex1.getLambda());
//                if(F1 <= (0.1*Fa)) {
//                    newState1 = PHYSIOFILL;
//                }
//            }
//                break;
//                
//            case PHYSIOFILL:
//            {
//                
//                double newLambda = duplex1.getLambda() + (returnRate*time_increment);
//                
//                F1 = duplex1.getForce(time, time_increment, newLambda);
//                
//                if(duplex1.getLength() >= duplex1.getUnstretchedLength()) {
//                    newState1 = ISOMETRIC;
//                }
//            }
//                break;
//                
//        }
//        
//        switch(state2) {
//                
//            case ISOMETRIC:
//            {
//                F2 = duplex2.getForce(time, time_increment, duplex2.getLambda());
//                
//                if(F2 >= Fa) {
//                    newState2 = ISOTONIC;
//                }
//            }
//                break;
//                
//            case ISOTONIC:
//            {
//                double oldLambda = duplex2.getLambda();
//                if(time > 0) {
//                    duplex2.calcLambda(time, time_increment, Fa);
//                }
//                
//                derivative2 = (duplex2.getLambda() - oldLambda)/(time_increment);
//                
//                if(derivative2 > 0) {
//                    newState2 = PHYSIOISO;
//                }
//            }
//                break;
//                
//            case PHYSIOISO:
//            {
//                F2 = duplex2.getForce(time, time_increment, duplex2.getLambda());
//                if(F2 <= (0.05*Fa)) {
//                    newState2 = PHYSIOFILL;
//                }
//            }
//                break;
//                
//            case PHYSIOFILL:
//            {
//                
//                double newLambda = duplex2.getLambda() + (returnRate*time_increment);
//                
//                F2 = duplex2.getForce(time, time_increment, newLambda);
//                
//                if(duplex2.getLength() >= duplex2.getUnstretchedLength()) {
//                    newState2 = ISOMETRIC;
//                }
//            }
//                break;
//                
//        }
//
//        
//        
//        state1 = newState1;
//        state2 = newState2;
//        
//        
//        if(i % 1000 == 0) {
//            file << time + time_increment << " " << F1 << " " << duplex1.getM1Lambda() << " " << duplex1.getM2Lambda() << " " << duplex1.getLambda() << " " << state1 << " " << F2 << " " << duplex2.getM1Lambda() << " " << duplex2.getM2Lambda() << " " << duplex2.getLambda() << " " << state2 << '\n';
//        }
//        duplex1.integrate(time, time_increment);
//        duplex2.integrate(time, time_increment);
//        i++;
//    }
//}
