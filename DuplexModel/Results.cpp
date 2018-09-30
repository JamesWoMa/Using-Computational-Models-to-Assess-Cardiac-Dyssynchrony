//
//  Results.cpp
//  DuplexModel
//
//  Created by James WoMa

#include <iostream>
#include <fstream>
#include "Duplex.h"
#include <cmath>
#include <sstream>
#include "Filament.h"
#include <vector>

using namespace std;

void MSDelayTest(std::ofstream& file, double initialDelay, double maxDelay, double delayIncrement, double k);
void AmpDelayTest(std::ofstream& file, double initialDelay, double maxDelay, double delayIncrement, double amp);

enum mode {ISOMETRIC = 0, ISOTONIC, PHYSIOISO, PHYSIOFILL};

const double TIME_INCREMENT = .005;
const double TIME = 1000.0;
const double LOAD = 150;//44.76376; //5;
const bool USELANDMUSCLE = false;
const bool DETAIL = false;
std::vector<double> betavalues;
std::vector<double>ampvalues;
double CASE = 0;

int main(int argc, const char * argv[])
{
//    betavalues.push_back(0.2);
    betavalues.push_back(0.5);
//    betavalues.push_back(0.7);
//    betavalues.push_back(1.0);
//    betavalues.push_back(2.0);
    
    double initialDelay = 0.0;
    double maxDelay = 50.0;
    double delayIncrement = 1.0;
    std::ofstream file("EjectionFraction.txt", std::ios::out);
    file << "Case" << " " << "Delay" << " " << "BetaValue" << " " << "DelayEF" << " " << "CRTEF" << " " << "CRTEfficacy" << '\n';
    for(int i = 0; i < betavalues.size(); i++) {
        std::cout << "Beta = " << betavalues[i] << std::endl;
        MSDelayTest(file, initialDelay, maxDelay, delayIncrement, betavalues[i]);
    }
    
//    file << "Case" << " " << "Delay" << " " << "Amplitude" << " " << "DelayEF" << " " << "CRTEF" << " " << "CRTEfficacy" << '\n';
//    for(int i = 0; i < ampvalues.size(); i++) {
//        std::cout << "Amplitude = " << ampvalues[i] << std::endl;
//        AmpDelayTest(file, initialDelay, maxDelay, delayIncrement, ampvalues[i]);
//    }

}

void MSDelayTest(std::ofstream& file, double initialDelay, double maxDelay, double delayIncrement, double beta) {
    for(double delay = initialDelay; delay <= maxDelay; delay+= delayIncrement) {
        //double delay = 30;
        std::cout << delay << std::endl;
        
        /*
         Construction of duplex with delay
         */
        
        std::vector<double> m1args(8);
        double m1k;
        double m1unstretchedPassive;
        double m1lambda;
        double m1unstretchedLength;
        
        std::vector<double> m2args(8);
        double m2k;
        double m2unstretchedPassive;
        double m2lambda;
        double m2unstretchedLength;
        
        Filament::FilamentType ft1;
        
        if(!USELANDMUSCLE) {
            //Muscle 1
            double m1duration = 700;
            double m1amplitude = 89.2752;
            double m1unstretched = 1;
            double m1delay = 0;
            double m1width = 500;
            m1lambda = 1.1;
            m1args[0] = m1duration;
            m1args[1] = m1amplitude;
            m1args[2] = m1unstretched;
            m1args[3] = m1delay;
            m1args[4] = m1width;
            m1k = beta;
            m1unstretchedPassive = 1;
            m1unstretchedLength = 5;
            
            //Muscle 2
            double m2duration = 700;
            double m2amplitude = 89.2752;
            double m2unstretched = 2;
            double m2delay = delay;
            double m2width = 500;
            m2lambda = 1.1;
            m2args[0] = m2duration;
            m2args[1] = m2amplitude;
            m2args[2] = m2unstretched;
            m2args[3] = m2delay;
            m2args[4] = m2width;
            m2k = beta;
            m2unstretchedPassive = 1;
            m2unstretchedLength = 5;
            
            ft1 = Filament::TRI_FT;
        } else {
            
            //Muscle1
            double ca = .02;
            double tn = 0;
            double xb = 0;
            double q1 = 0;
            double q2 = 0;
            double t_cycle = 700;
            double m1delay = 0;
            m1lambda = 1.1;
            m1args[0] = ca;
            m1args[1] = tn;
            m1args[2] = xb;
            m1args[3] = q1;
            m1args[4] = q2;
            m1args[5] = m1lambda;
            m1args[6] = t_cycle;
            m1args[7] = m1delay;
            m1k = beta;
            m1unstretchedPassive = 1;
            m1unstretchedLength = 5;
            
            //Muscle2
            double ca2 = .02;
            double tn2 = 0;
            double xb2 = 0;
            double q12 = 0;
            double q22 = 0;
            double t_cycle2 = 700;
            double m2delay = delay;
            m2lambda = 1.1;
            m2args[0] = ca2;
            m2args[1] = tn2;
            m2args[2] = xb2;
            m2args[3] = q12;
            m2args[4] = q22;
            m2args[5] = m2lambda;
            m2args[6] = t_cycle2;
            m2args[7] = m2delay;
            m2k = beta;
            m2unstretchedPassive = 1;
            m2unstretchedLength = 5;
            ft1 = Filament::LAND_FT;
        }
        
        Duplex duplex1(ft1,m1args,m1k,m1unstretchedPassive,m1lambda, m1unstretchedLength,m2args,m2k,m2unstretchedPassive,m2lambda,m2unstretchedLength);
        mode state1 = ISOMETRIC;
        double F1 = 0;
        double derivative1 = 0;
        double EDV = 0;
        double ESV = 0;
        
        const double initLambda = duplex1.getLambda();
        
        /**
         Construction of duplex without delay
         */
        
        std::vector<double> m3args(8);
        double m3k;
        double m3unstretchedPassive;
        double m3lambda;
        double m3unstretchedLength;
        
        std::vector<double> m4args(8);
        double m4k;
        double m4unstretchedPassive;
        double m4lambda;
        double m4unstretchedLength;
        
        Filament::FilamentType ft2;
        
        if(!USELANDMUSCLE) {
            //Muscle 3
            double m3duration = 700;
            double m3amplitude = 89.2752;
            double m3unstretched = 1;
            double m3delay = 0;
            double m3width = 500;
            m3lambda = 1.1;
            m3args[0] = m3duration;
            m3args[1] = m3amplitude;
            m3args[2] = m3unstretched;
            m3args[3] = m3delay;
            m3args[4] = m3width;
            m3k = beta;
            m3unstretchedPassive = 1;
            m3unstretchedLength = 5;
            
            //Muscle 4
            double m4duration = 700;
            double m4amplitude = 89.2752;
            double m4unstretched = 1;
            double m4delay = 0;
            double m4width = 500;
            m4lambda = 1.1;
            m4args[0] = m4duration;
            m4args[1] = m4amplitude;
            m4args[2] = m4unstretched;
            m4args[3] = m4delay;
            m4args[4] = m4width;
            m4k = beta;
            m4unstretchedPassive = 1;
            m4unstretchedLength = 5;
            
            ft2 = Filament::TRI_FT;
        } else {
            
            //Muscle 3
            double ca3 = .02;
            double tn3 = 0;
            double xb3 = 0;
            double q13 = 0;
            double q23 = 0;
            double t_cycle3 = 700;
            double m3delay = 0;
            m3lambda = 1.1;
            m3args[0] = ca3;
            m3args[1] = tn3;
            m3args[2] = xb3;
            m3args[3] = q13;
            m3args[4] = q23;
            m3args[5] = m3lambda;
            m3args[6] = t_cycle3;
            m3args[7] = m3delay;
            m3k = beta;
            m3unstretchedPassive = 1;
            m3unstretchedLength = 5;
            
            //Muscle 4
            double ca4 = .02;
            double tn4 = 0;
            double xb4 = 0;
            double q14 = 0;
            double q24 = 0;
            double t_cycle4 = 700;
            double m4delay = 0;
            m4lambda = 1.1;
            m4args[0] = ca4;
            m4args[1] = tn4;
            m4args[2] = xb4;
            m4args[3] = q14;
            m4args[4] = q24;
            m4args[5] = m4lambda;
            m4args[6] = t_cycle4;
            m4args[7] = m4delay;
            m4k = beta;
            m4unstretchedPassive = 1;
            m4unstretchedLength = 5;
            
            ft2 = Filament::LAND_FT;
        }
        
        Duplex duplex2(ft2,m3args,m3k,m3unstretchedPassive,m3lambda, m3unstretchedLength,m4args,m4k,m4unstretchedPassive,m4lambda,m4unstretchedLength);
        mode state2 = ISOMETRIC;
        double F2 = 0;
        double derivative2 = 0;
        double EDV2 = 0;
        double ESV2 = 0;
        
        const double initLambda2 = duplex2.getLambda();
        
        /*
         Construction of filename organized as D[delay]MS[k]L.txt
         */
        std::ostringstream oss;
        if(USELANDMUSCLE) {
            oss << "Sarc";
        } else {
            oss << "Tri";
        }
        oss << "MS[" << beta;
        if(fmod(beta,1.0) == 0) {
            //oss << ".0";
        }
        oss << "]D[" << delay;
        if(fmod(delay,1.0)==0) {
            oss << ".0";
        }
        oss << "]L.txt";
        string fileName = oss.str();
        std::ofstream file2(fileName, std::ios::out);
        /*
         End of filename construction
         */
        file2 << "#Time" << " " << "DuplexLambda" << " " << "DuplexLength" << " " << "DuplexForce" << " " << "State" << " " << "M1Lambda" << " " << "M1Length" << " " << "M2Lambda" << " " << "M2Length";
        if(USELANDMUSCLE && DETAIL) {
            duplex1.write_header(file2);
            duplex2.write_header(file2);
        }
        file2 << '\n';
        file2 << "0" << " " << duplex1.getLambda() << " " << duplex1.getLength() << " " << duplex1.getForce(0, 1e-9, duplex1.getLambda()) << " " << state1 << " " << duplex1.getM1Lambda() << " " << duplex1.getM1Length() << " " << duplex1.getM2Lambda() << " " << duplex1.getM2Length();
        if(USELANDMUSCLE && DETAIL) {
            duplex1.M1write_timestep(0, file2);
            duplex2.M2write_timestep(0, file2);
        }
        file2 << '\n';
        
        int i = 0;
        mode newState1 = state1;
        mode newState2 = state2;
        
        double returnRate = 0.0;
        for(double time = 0; time < TIME; time += TIME_INCREMENT) {
            switch(state1) {
                    
                case ISOMETRIC:
                {
                    F1 = duplex1.getForce(time, TIME_INCREMENT, duplex1.getLambda());
                    
                    if(F1 >= LOAD) {
                        newState1 = ISOTONIC;
                        EDV = duplex1.getLambda();
                    }
                }
                    break;
                    
                case ISOTONIC:
                {
                    double oldLambda = duplex1.getLambda();
                    if(time > 0) {
                        duplex1.calcLambda(time, TIME_INCREMENT, LOAD);
                    }
                    
                    derivative1 = (duplex1.getLambda() - oldLambda)/(TIME_INCREMENT);
                    
                    if(derivative1 > 0) {
                            newState1 = PHYSIOISO;
                    }
                }
                    break;
                    
                case PHYSIOISO:
                {
                    F1 = duplex1.getForce(time, TIME_INCREMENT, duplex1.getLambda());
                    if(F1 <= (0.15*LOAD)) {
                        returnRate = (initLambda - duplex1.getLambda())/250;
                        newState1 = PHYSIOFILL;
                        ESV = duplex1.getLambda();
                    }
                }
                    break;
                    
                case PHYSIOFILL:
                {
                    
                    double newLambda = duplex1.getLambda() + (returnRate*TIME_INCREMENT);
                    
                    F1 = duplex1.getForce(time, TIME_INCREMENT, newLambda);
                    
                    if(duplex1.getLength() >= duplex1.getUnstretchedLength() * duplex1.getInitialLambda()) {
                        newState1 = ISOMETRIC;
                    }
                }
                    break;
                    
            }
            
            switch(state2) {
                    
                case ISOMETRIC:
                {
                    F2 = duplex2.getForce(time, TIME_INCREMENT, duplex2.getLambda());
                    
                    if(F2 >= LOAD) {
                        newState2 = ISOTONIC;
                        EDV2 = duplex2.getLambda();
                    }
                }
                    break;
                    
                case ISOTONIC:
                {
                    double oldLambda = duplex2.getLambda();
                    if(time > 0) {
                        duplex2.calcLambda(time, TIME_INCREMENT, LOAD);
                    }
                    
                    derivative2 = (duplex2.getLambda() - oldLambda)/(TIME_INCREMENT);
                    
                    if(derivative2 > 0) {
                            newState2 = PHYSIOISO;
                    }
                }
                    break;
                    
                case PHYSIOISO:
                {
                    F2 = duplex2.getForce(time, TIME_INCREMENT, duplex2.getLambda());
                    if(F2 <= (0.15*LOAD)) {
                        returnRate = (initLambda2 - duplex2.getLambda())/250;
                        newState2 = PHYSIOFILL;
                        ESV2 = duplex2.getLambda();
                    }
                }
                    break;
                    
                case PHYSIOFILL:
                {
                    
                    double newLambda = duplex2.getLambda() + (returnRate*TIME_INCREMENT);
                    
                    F2 = duplex2.getForce(time, TIME_INCREMENT, newLambda);
                    
                    if(duplex2.getLength() >= duplex2.getUnstretchedLength() * duplex2.getInitialLambda()) {
                        newState2 = ISOMETRIC;
                    }
                }
                    break;
                    
            }
            
            
            
            state1 = newState1;
            state2 = newState2;
            
            if(i % 1000 == 999) {
                file2 << (time + TIME_INCREMENT) << " " << duplex1.getLambda() << " " << duplex1.getLength() << " " << F1 << " " << state1 << " " << duplex1.getM1Lambda() << " " << duplex1.getM1Length() << " " << duplex1.getM2Lambda() << " " << duplex1.getM2Length();
                if(USELANDMUSCLE && DETAIL) {
                    duplex1.M1write_timestep(time, file2);
                    duplex1.M2write_timestep(time, file2);
                }
                file2 << '\n';
            }
            
            duplex1.integrate(time, TIME_INCREMENT);
            duplex2.integrate(time, TIME_INCREMENT);
            i++;
        }
        
        file << CASE << " " << delay/500 << " " << beta << " " << ((EDV-ESV)/EDV)*100 << " " << ((EDV2-ESV2)/EDV2)*100 << " " << (((EDV2-ESV2)/EDV2)*100)-(((EDV-ESV)/EDV)*100) << '\n';
        CASE++;
    }
}
