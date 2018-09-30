//
//  Filament.h
//  DuplexModel
//
//  Created by James WoMa

#ifndef __DuplexModel__Filament__
#define __DuplexModel__Filament__

#include <iostream>

class Filament {
public:
    enum FilamentType {PARA_FT = 0, LAND_FT, TRI_FT};
    virtual double calcForce(double time, double dt, double lambda) = 0;
    virtual double getdForce_dLambda(double time, double dt, double lambda, double delta) = 0;
    virtual void integrate(double time, double dt, double lambda) = 0;
    virtual void write_header(std::ofstream& f) = 0;
    //virtual void write_timestep(double t, std::ofstream& f, double lambda) = 0;
};

#endif /* defined(__DuplexModel__Filament__) */
