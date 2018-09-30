////
////  Results.cpp
////  DuplexModel
////
////  Created by James WoMa
//
//#include <iostream>
//#include <fstream>
//#include "Duplex.h"
//#include <cmath>
//#include <sstream>
//#include "Filament.h"
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
//    double Fa = 30.0;
//    
//    bool landMuscle = false;
//    
//    std::ofstream file("DelayEjectionFraction.txt", std::ios::out);
//    file << "Delay" << " " << "DelayEDV" << " " << "DelaySV" << " " << "DelayEF" << " " << "CRTEDV" << " " << "CRTSV" << " " << "CRTEF" << " " << "CRTEfficacy" << '\n';
//    
//    //        file << "MuscleStiffness" << " " << "DelayEDV" << " " << "DelaySV" << " " << "DelayEF" << " " << "SyncEDV" << " " << "SyncSV" << " " << "SyncEF" << " " << "EjectionRatio" << '\n';
//    //        file << '\n';
//    
//    for(double delay = 0.0; delay < 100; delay+= 10) {
//        double k = 2.0;
//        //double delay = 30;
//        
//        /*
//         Construction of duplex with delay
//         */
//        
//        std::vector<double> m1args(8);
//        double m1k;
//        double m1unstretchedPassive;
//        double m1lambda;
//        double m1unstretchedLength;
//        
//        std::vector<double> m2args(8);
//        double m2k;
//        double m2unstretchedPassive;
//        double m2lambda;
//        double m2unstretchedLength;
//        
//        Filament::FilamentType ft1;
//        
//        if(!landMuscle) {
//            //Muscle 1
//            double m1duration = 500;
//            double m1amplitude = 43;
//            double m1unstretched = 1;
//            double m1delay = 0;
//            double m1width = 300;
//            m1lambda = 1;
//            m1args[0] = m1duration;
//            m1args[1] = m1amplitude;
//            m1args[2] = m1unstretched;
//            m1args[3] = m1delay;
//            m1args[4] = m1width;
//            m1k = k;
//            m1unstretchedPassive = 1;
//            m1unstretchedLength = 5;
//            
//            //Muscle 2
//            double m2duration = 500;
//            double m2amplitude = 43;
//            double m2unstretched = 1;
//            double m2delay = delay;
//            double m2width = 300;
//            m2lambda = 1;
//            m2args[0] = m2duration;
//            m2args[1] = m2amplitude;
//            m2args[2] = m2unstretched;
//            m2args[3] = m2delay;
//            m2args[4] = m2width;
//            m2k = k;
//            m2unstretchedPassive = 1;
//            m2unstretchedLength = 5;
//            
//            ft1 = Filament::PARA_FT;
//        } else {
//            
//            //Muscle1
//            double ca = .55;
//            double tn = 0;
//            double xb = 0;
//            double q1 = 0;
//            double q2 = 0;
//            double t_cycle = 500;
//            double m1delay = 0;
//            m1lambda = 1;
//            m1args[0] = ca;
//            m1args[1] = tn;
//            m1args[2] = xb;
//            m1args[3] = q1;
//            m1args[4] = q2;
//            m1args[5] = m1lambda;
//            m1args[6] = t_cycle;
//            m1args[7] = m1delay;
//            m1k = k;
//            m1unstretchedPassive = 1;
//            m1unstretchedLength = 5;
//            
//            //Muscle2
//            double ca2 = .55;
//            double tn2 = 0;
//            double xb2 = 0;
//            double q12 = 0;
//            double q22 = 0;
//            double t_cycle2 = 500;
//            double m2delay = delay;
//            m2lambda = 1;
//            m2args[0] = ca2;
//            m2args[1] = tn2;
//            m2args[2] = xb2;
//            m2args[3] = q12;
//            m2args[4] = q22;
//            m2args[5] = m2lambda;
//            m2args[6] = t_cycle2;
//            m2args[7] = m2delay;
//            m2k = k;
//            m2unstretchedPassive = 1;
//            m2unstretchedLength = 5;
//            ft1 = Filament::LAND_FT;
//        }
//        
//        Duplex duplex1(ft1,m1args,m1k,m1unstretchedPassive,m1lambda, m1unstretchedLength,m2args,m2k,m2unstretchedPassive,m2lambda,m2unstretchedLength);
//        mode state1 = ISOMETRIC;
//        double F1 = 0;
//        double derivative1 = 0;
//        double EDV = 0;
//        double ESV = 0;
//        
//        /**
//         Construction of duplex without delay
//         */
//        
//        std::vector<double> m3args(8);
//        double m3k;
//        double m3unstretchedPassive;
//        double m3lambda;
//        double m3unstretchedLength;
//        
//        std::vector<double> m4args(8);
//        double m4k;
//        double m4unstretchedPassive;
//        double m4lambda;
//        double m4unstretchedLength;
//        
//        Filament::FilamentType ft2;
//        
//        if(!landMuscle) {
//            //Muscle 3
//            double m3duration = 500;
//            double m3amplitude = 43;
//            double m3unstretched = 1;
//            double m3delay = 0;
//            double m3width = 300;
//            m3lambda = 1;
//            m3args[0] = m3duration;
//            m3args[1] = m3amplitude;
//            m3args[2] = m3unstretched;
//            m3args[3] = m3delay;
//            m3args[4] = m3width;
//            m3k = k;
//            m3unstretchedPassive = 1;
//            m3unstretchedLength = 5;
//            
//            //Muscle 4
//            double m4duration = 500;
//            double m4amplitude = 43;
//            double m4unstretched = 1;
//            double m4delay = 0;
//            double m4width = 300;
//            m4lambda = 1;
//            m4args[0] = m4duration;
//            m4args[1] = m4amplitude;
//            m4args[2] = m4unstretched;
//            m4args[3] = m4delay;
//            m4args[4] = m4width;
//            m4k = k;
//            m4unstretchedPassive = 1;
//            m4unstretchedLength = 5;
//            
//            ft2 = Filament::PARA_FT;
//        } else {
//            
//            //Muscle 3
//            double ca3 = .55;
//            double tn3 = 0;
//            double xb3 = 0;
//            double q13 = 0;
//            double q23 = 0;
//            double t_cycle3 = 500;
//            double m3delay = 0;
//            m3lambda = 1;
//            m3args[0] = ca3;
//            m3args[1] = tn3;
//            m3args[2] = xb3;
//            m3args[3] = q13;
//            m3args[4] = q23;
//            m3args[5] = m3lambda;
//            m3args[6] = t_cycle3;
//            m3args[7] = m3delay;
//            m3k = k;
//            m3unstretchedPassive = 1;
//            m3unstretchedLength = 5;
//            
//            //Muscle 4
//            double ca4 = .55;
//            double tn4 = 0;
//            double xb4 = 0;
//            double q14 = 0;
//            double q24 = 0;
//            double t_cycle4 = 500;
//            double m4delay = 0;
//            m4lambda = 1;
//            m4args[0] = ca4;
//            m4args[1] = tn4;
//            m4args[2] = xb4;
//            m4args[3] = q14;
//            m4args[4] = q24;
//            m4args[5] = m4lambda;
//            m4args[6] = t_cycle4;
//            m4args[7] = m4delay;
//            m4k = k;
//            m4unstretchedPassive = 1;
//            m4unstretchedLength = 5;
//            
//            ft2 = Filament::LAND_FT;
//        }
//        
//        Duplex duplex2(ft2,m3args,m3k,m3unstretchedPassive,m3lambda, m3unstretchedLength,m4args,m4k,m4unstretchedPassive,m4lambda,m4unstretchedLength);
//        mode state2 = ISOMETRIC;
//        double F2 = 0;
//        double derivative2 = 0;
//        double EDV2 = 0;
//        double ESV2 = 0;
//        
//        
//        std::ostringstream oss;
//        if(fmod(delay,1.0) == 0) {
//            oss << "D" << delay << ".0" << "L.txt";
//        } else {
//            oss << "D" << delay << "L.txt";
//        }
//        string fileName = oss.str();
//        
//        std::ofstream file2(fileName, std::ios::out);
//        file2 << "Time" << " " << "DuplexLambda" << " " << "DuplexLength" << " " << "DuplexForce" << " " << "State" << " " << "M1Lambda" << " " << "M1Length" << " " << "M2Lambda" << " " << "M2Length" << '\n';
//        file2 << "0" << " " << duplex1.getLambda() << " " << duplex1.getLength() << " " << duplex1.getForce(0, 1e-9, duplex1.getLambda()) << " " << duplex1.getM1Lambda() << " " << duplex1.getM1Length() << " " << duplex1.getM2Lambda() << " " << duplex1.getM2Length() << " " << state1 << '\n';//<< duplex2.getM1Length() << " " << duplex2.getM2Length() << '\n';
//        
//        int i = 0;
//        mode newState1 = state1;
//        mode newState2 = state2;
//        
//        double returnRate = .0008;
//        for(double time = 0; time < Time; time += time_increment) {
//            switch(state1) {
//                    
//                case ISOMETRIC:
//                {
//                    F1 = duplex1.getForce(time, time_increment, duplex1.getLambda());
//                    
//                    if(F1 >= Fa) {
//                        newState1 = ISOTONIC;
//                        EDV = duplex1.getLength();
//                    }
//                }
//                    break;
//                    
//                case ISOTONIC:
//                {
//                    double oldLambda = duplex1.getLambda();
//                    if(time > 0) {
//                        duplex1.calcLambda(time, time_increment, Fa);
//                    }
//                    
//                    derivative1 = (duplex1.getLambda() - oldLambda)/(time_increment);
//                    
//                    if(derivative1 > 0) {
//                        newState1 = PHYSIOISO;
//                    }
//                }
//                    break;
//                    
//                case PHYSIOISO:
//                {
//                    F1 = duplex1.getForce(time, time_increment, duplex1.getLambda());
//                    if(F1 <= (0.05*Fa)) {
//                        newState1 = PHYSIOFILL;
//                        ESV = duplex1.getLength();
//                    }
//                }
//                    break;
//                    
//                case PHYSIOFILL:
//                {
//                    
//                    double newLambda = duplex1.getLambda() + (returnRate*time_increment);
//                    
//                    F1 = duplex1.getForce(time, time_increment, newLambda);
//                    
//                    if(duplex1.getLength() >= duplex1.getUnstretchedLength()) {
//                        newState1 = ISOMETRIC;
//                    }
//                }
//                    break;
//                    
//            }
//            
//            switch(state2) {
//                    
//                case ISOMETRIC:
//                {
//                    F2 = duplex2.getForce(time, time_increment, duplex2.getLambda());
//                    
//                    if(F2 >= Fa) {
//                        newState2 = ISOTONIC;
//                        EDV2 = duplex2.getLength();
//                    }
//                }
//                    break;
//                    
//                case ISOTONIC:
//                {
//                    double oldLambda = duplex2.getLambda();
//                    if(time > 0) {
//                        duplex2.calcLambda(time, time_increment, Fa);
//                    }
//                    
//                    derivative2 = (duplex2.getLambda() - oldLambda)/(time_increment);
//                    
//                    if(derivative2 > 0) {
//                        newState2 = PHYSIOISO;
//                    }
//                }
//                    break;
//                    
//                case PHYSIOISO:
//                {
//                    F2 = duplex2.getForce(time, time_increment, duplex2.getLambda());
//                    if(F2 <= (0.05*Fa)) {
//                        newState2 = PHYSIOFILL;
//                        ESV2 = duplex2.getLength();
//                    }
//                }
//                    break;
//                    
//                case PHYSIOFILL:
//                {
//                    
//                    double newLambda = duplex2.getLambda() + (returnRate*time_increment);
//                    
//                    F2 = duplex2.getForce(time, time_increment, newLambda);
//                    
//                    if(duplex2.getLength() >= duplex2.getUnstretchedLength()) {
//                        newState2 = ISOMETRIC;
//                    }
//                }
//                    break;
//                    
//            }
//            
//            
//            
//            state1 = newState1;
//            state2 = newState2;
//            
//            if(i % 1000 == 999) {
//                file2 << time + time_increment << " " << duplex1.getLambda() << " " << duplex1.getLength() << " " << F1 << " " << state1 << " " << duplex1.getM1Lambda() << " " << duplex1.getM1Length() << " " << duplex1.getM2Lambda() << " " << duplex1.getM2Length() << '\n';
//            }
//            
//            duplex1.integrate(time, time_increment);
//            duplex2.integrate(time, time_increment);
//            i++;
//        }
//        file << delay << " " << EDV << " " << EDV-ESV << " " << ((EDV-ESV)/EDV)*100 << " " << EDV2 << " " << EDV2 - ESV2 << " " << ((EDV2-ESV2)/EDV2)*100 << " " << (((EDV2-ESV2)/EDV2)*100)-(((EDV-ESV)/EDV)*100) << '\n';
//        std::cout << delay << std::endl;
//    }
//}
