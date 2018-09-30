// Created by James WoMa

#ifndef __DuplexModel__ParaFilament__
#define __DuplexModel__ParaFilament__

#include <iostream>
#include <fstream>
#include "Filament.h"

class ParaFilament : public Filament {
public:
    ParaFilament(double duration, double amplitude, double unstreched, double delay, double width);
    double calcForce(double time, double dt, double lambda);
    double getdForce_dLambda(double time, double dt, double lambda, double delta);
    void integrate(double time, double dt, double lambda);
    void write_header(std::ofstream& f);
    //void write_timestep(double t, std::ofstream& f);
    
private:
    double duration_;
    double amplitude_;
    double unstreched_;
    double delay_;
    double width_;
    
    double g(double time);
    double h(double lambda);
};

#endif /* defined(__DuplexModel__Filament__) */
