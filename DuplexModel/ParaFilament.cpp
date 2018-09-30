//
//  Filament.cpp
//  DuplexModel
//
//  Created by James WoMa

#include "ParaFilament.h"
#include <cmath>

ParaFilament::ParaFilament(double duration, double amplitude, double unstreched, double delay, double width) {
    unstreched_ = unstreched;
    amplitude_ = amplitude;
    duration_ = duration;
    delay_ = delay;
    width_ = width;
}

double ParaFilament::calcForce(double time, double dt, double lambda) {
    double t = time + dt;
    double gt = g(t);
    
    double fl = gt * h(lambda);
    return fl;
}

double ParaFilament::getdForce_dLambda(double time, double dt, double lambda, double delta) {
    //Analytical
    //return 2.5*g(time);
    
    //Finite Difference
    double t = time + dt;
    double dl = 0.1e-9;
    
    double lp = g(t) * h(lambda + dl);
    double ln = g(t) * h(lambda - dl);
    
    return (lp - ln) / (2*dl);
}

void ParaFilament::integrate(double time, double dt, double lambda) {
    
}

double ParaFilament::g(double time) {
    time -= delay_;
    time -= (int(time/duration_)) * duration_;
    if((time > width_) || (time < 0)) {
        return 0.0;
    }
    
    double k = amplitude_/((pow(width_, 2))/4);
    double gt = -k*time*(time - width_);
    
    return gt;
}

double ParaFilament::h(double lambda) {
    if(lambda <= 0.6) {
        return 0.0;
    }
    
    return (2.5*lambda) - 1.5;
}

void ParaFilament::write_header(std::ofstream& f) {
    
}

void ParaFilament::write_timestep(double t, std::ofstream& f) {
    
}
