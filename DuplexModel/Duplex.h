//
//  Duplex.h
//  DuplexModel
//
//  Created by James WoMa
//

#ifndef __DuplexModel__Duplex__
#define __DuplexModel__Duplex__

#include <iostream>
#include "Muscle.h"
#include "Filament.h"

class Duplex {
public:
    Duplex(Filament::FilamentType ft, std::vector<double> m1args, double m1beta, double m1unstretchedPassive, double m1start,double m1unstretchedLength,  std::vector<double> m2args, double m2beta, double m2unstretchedPassive, double m2start, double m2unstretchedLength);
    ~Duplex();
    double getForce(double time, double dt, double totallambda);
    //double getdForce_dLambda(double time, double dt, double lambda);
    void calcLambda(double time, double dt, double load);
    double getLambda();
    double getM1Lambda();
    double getM1Length();
    double getM2Lambda();
    double getM2Length();
    double getLength();
    void integrate(double time, double dt);
    void addLambda(double dlambda);
    double getUnstretchedLength();
    double getInitialLambda();
    void write_header(std::ofstream& f);
    void M1write_timestep(double t, std::ofstream& f);
    void M2write_timestep(double t, std::ofstream& f);
    
private:
    Muscle* muscle1;
    Muscle* muscle2;
    double unstretchedLength_;
    double initialLambda_;
    double compareDouble(double a, double b);
    double calcLambda2(double totallambda, double lambda1);
};

#endif /* defined(__DuplexModel__Duplex__) */
