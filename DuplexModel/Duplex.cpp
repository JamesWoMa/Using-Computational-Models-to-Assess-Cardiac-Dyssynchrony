//
//  Duplex.cpp
//  DuplexModel
//
//  Created by James WoMa
//

#include "Duplex.h"
#include <cmath>

Duplex::Duplex(Filament::FilamentType ft, std::vector<double> m1args, double m1beta, double m1unstretchedPassive, double m1start, double m1unstretchedLength, std::vector<double> m2args, double m2beta, double m2unstretchedPassive, double m2start, double m2unstretchedLength) {
    
    muscle1 = new Muscle(ft,m1args,m1beta,m1unstretchedPassive,m1start, m1unstretchedLength);
    muscle2 = new Muscle(ft,m2args,m2beta,m2unstretchedPassive,m2start, m2unstretchedLength);
    
//    if(ft == Filament::PARA_FT) {
//        muscle1 = new Muscle(Filament::PARA_FT,m1args,m1beta,m1unstretchedPassive,m1start, m1unstretchedLength);
//        muscle2 = new Muscle(Filament::PARA_FT,m2args,m2beta,m2unstretchedPassive,m2start, m2unstretchedLength);
//        
//    } else if(ft == Filament::LAND_FT) {
//        muscle1 = new Muscle(Filament::LAND_FT,m1args,m1beta,m1unstretchedPassive,m1start, m1unstretchedLength);
//        muscle2 = new Muscle(Filament::LAND_FT,m2args,m2beta,m2unstretchedPassive,m2start, m2unstretchedLength);
//    }
    
    unstretchedLength_ = (m1unstretchedLength) + (m2unstretchedLength);
    initialLambda_ = (m1start + m2start)/2;
    
}

Duplex::~Duplex() {
    delete muscle1;
    delete muscle2;
}

double Duplex::getForce(double time, double dt, double totallambda) {

    double lambda1 = muscle1 -> getLambda();
    double lambda2 = 0.0;
    
    for(int i = 0; i < 20; i++) {
        
        lambda2 = calcLambda2(totallambda, lambda1);
        
        double f = muscle1 -> getForce(time, dt, lambda1) - muscle2 -> getForce(time, dt, lambda2);
        
        double dl = 1e-9;
        double df = muscle1 -> getdForce_dLambda(time, dt, lambda1) - (((calcLambda2(totallambda, lambda1+dl)-calcLambda2(totallambda, lambda1-dl))/(2*dl))*muscle2 -> getdForce_dLambda(time, dt, lambda2));
        
        //std::cout << "LAMBDA = " << lambda1 << "      FORCE: " << f <<  "       DF:" << df << std::endl;
        
        if(!compareDouble(f, 0.0)) {
            lambda1 -= (f/df);
        }
    }
    
    lambda2 = ((totallambda*getUnstretchedLength()) - (lambda1*muscle1 -> getUnstretchedLength()))/muscle2 -> getUnstretchedLength();
    
    muscle1 -> setLambda(lambda1);
    muscle2 -> setLambda(lambda2);
    
    return muscle1 -> getForce(time, dt, muscle1 -> getLambda());
    
}

void Duplex::integrate(double time, double dt) {
    muscle1->integrate(time, dt);
    muscle2->integrate(time, dt);
}

void Duplex::calcLambda(double time, double dt, double load) {
    muscle1 -> setLambda(muscle1 -> getLambda(time, dt, load));
    muscle2 -> setLambda(muscle2 -> getLambda(time, dt, load));
}

double Duplex::getLambda() {
    return (muscle1->getLength() + muscle2->getLength())/unstretchedLength_;
}

double Duplex::getInitialLambda() {
    return initialLambda_;
}

double Duplex::getM1Lambda() {
    return muscle1 -> getLambda();
}

double Duplex::getM1Length() {
    return getM1Lambda() * muscle1 -> getUnstretchedLength();
}

double Duplex::getM2Lambda() {
    return muscle2 -> getLambda();
}

double Duplex::getM2Length() {
    return getM2Lambda() * muscle2 -> getUnstretchedLength();
}

double Duplex::getLength() {
    return getLambda() * unstretchedLength_;
}

void Duplex::addLambda(double dlambda) {
    muscle1 -> setLambda(dlambda/2);
    muscle2 -> setLambda(dlambda/2);
}

double Duplex::getUnstretchedLength() {
    return unstretchedLength_;
}

double Duplex::compareDouble(double a, double b) {
    return fabs(a - b) < 1e-9;
}

double Duplex::calcLambda2(double totallambda, double lambda1) {
    return ((totallambda*getUnstretchedLength()) - (lambda1*muscle1 -> getUnstretchedLength()))/muscle2 -> getUnstretchedLength();
}

void Duplex::write_header(std::ofstream& f) {
    muscle1 -> write_header(f);
}
void Duplex::M1write_timestep(double t, std::ofstream& f){
    //muscle1 -> write_timestep(t, f);
}
void Duplex::M2write_timestep(double t, std::ofstream& f){
    //muscle2 -> write_timestep(t, f);
}

