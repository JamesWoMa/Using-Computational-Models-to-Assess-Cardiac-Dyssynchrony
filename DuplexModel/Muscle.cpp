//
//  Muscle.cpp
//  DuplexModel
//
//  Created by James WoMa

#include "Muscle.h"
#include <iostream>
#include <vector>
#include "ParaFilament.h"
#include "Sarcomere.h"
#include "Filament.h"
#include "TriSeg.h"

Muscle::Muscle(Filament::FilamentType ft, std::vector<double> args, double beta, double unstretchedPassive, double startingLambda, double unstretchedLength):
passive(beta, unstretchedPassive){
    lambda_ = startingLambda;
    unstretchedLength_ = unstretchedLength;
    startingLambda_ = startingLambda;
    if(ft == Filament::PARA_FT) {
        filament = new ParaFilament(args[0], args[1], args[2], args[3], args[4]);
    } else if(ft == Filament::LAND_FT) {
        filament = new Sarcomere(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
    } else if(ft == Filament::TRI_FT) {
        double lambda = lambda_;
        //std::cout << args[3] << std::endl;
        filament = new TriSeg(lambda, args[3]);
    }
    //std::cout << lambda_ << std::endl;
}

Muscle::~Muscle() {
    delete filament;
}

double Muscle::getForce(double time, double dt, double lambda) {
    return getSarcomereForce(time, dt, lambda) + getPassiveForce(lambda);
}

double Muscle::getdForce_dLambda(double time, double dt, double lambda) {
    return filament->getdForce_dLambda(time, dt, lambda, 1e-9) + passive.getdForce(lambda);
}

double Muscle::getLambda(double time, double dt, double load) {
    double lambda = lambda_;
    for(int i = 0; i < 15; i++) {
        double f = load - getForce(time, dt, lambda);
        double df = -getdForce_dLambda(time, dt, lambda);
        
        if(!compareDouble(f, 0.0)) {
            //std::cout << "ERROR: Newton's Method Function not working!" << std::endl;
        }
        
        lambda -= (f/df);
        //std::cout << "LAMBDA = " << lambda << "      FORCE: " << f <<  "       DF:" << df << std::endl;
    }
    
    setLambda(lambda);
    return lambda;
}

void Muscle::setLambda(double lambda) {
    lambda_ = lambda;
}

double Muscle::getLambda() {
    return lambda_;
}

double Muscle::getUnstretchedLength() {
    return unstretchedLength_;
}

double Muscle::getLength() {
    return unstretchedLength_*lambda_;
}

double Muscle::getStartingLambda() {
    return startingLambda_;
}

void Muscle::integrate(double time, double dt) {
    filament->integrate(time, dt, lambda_);
}

double Muscle::getPassiveForce(double lambda) {
    return passive.getForce(lambda);
}
double Muscle::getSarcomereForce(double time, double dt, double lambda) {
    return filament->calcForce(time, dt, lambda);
}

bool Muscle::compareDouble(double a, double b) {
    
    if(abs(a - b) < 1e-9) {
        return true;
    } else {
        return false;
    }
}

void Muscle::write_header(std::ofstream& f) {
    filament -> write_header(f);
}

//void Muscle::write_timestep(double t, std::ofstream& f) {
//    filament -> write_timestep(t, f);
//}

