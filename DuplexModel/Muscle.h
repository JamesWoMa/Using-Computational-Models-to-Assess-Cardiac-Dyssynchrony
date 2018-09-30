//
//  Muscle.h
//  DuplexModel
//
//  Created by James WoMa

#ifndef __DuplexModel__Muscle__
#define __DuplexModel__Muscle__

#include <iostream>
#include <vector>
#include "Passive.h"
#include "ParaFilament.h"
#include "Sarcomere.h"
#include "Filament.h"

class Muscle {
    
public:
    Muscle(Filament::FilamentType ft, std::vector<double> args, double beta, double unstretchedPassive, double startingLambda, double unstretchedLength);
    ~Muscle();
    double getForce(double time, double dt, double lambda);
    double getdForce_dLambda(double time, double dt, double lambda);
    double getLambda(double time, double dt, double load);
    void integrate(double time, double dt);
    void setLambda(double lambda);
    double getLambda();
    double getLength();
    double getUnstretchedLength();
    double getStartingLambda();
    double getPassiveForce(double lambda);
    double getSarcomereForce(double time, double dt, double lambda);
    void write_header(std::ofstream& f);
    //void write_timestep(double t, std::ofstream& f);
    
private:
    double lambda_;
    double unstretchedLength_;
    double startingLambda_;
    Filament* filament;
    Passive passive;
    bool compareDouble(double a, double b);
};

#endif /* defined(__DuplexModel__Muscle__) */
