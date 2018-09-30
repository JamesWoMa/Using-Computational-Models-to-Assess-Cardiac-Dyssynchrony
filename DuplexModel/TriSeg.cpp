//
//  TriSeg.cpp
//  DuplexModel
//
//  Created by James WoMa

#include "TriSeg.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


TriSeg::TriSeg(double lambda, double delay)
: state_vec(last2)
{
    Crest = .02;
    Lsc0 = 1.51; // um
    Lsref = 2.0; // um
    Lseiso = .04; // um
    vmax = .007; // um s-1
    τD = 32; // ms
    τR = 48; // ms
    τsc = 425; // ms
    σact = 120; //kpa
    state_vec[state_C] = Crest;
    state_vec[state_Lsc] = calc_Ls(lambda) - Lseiso;
    //std::cout << delay << std::endl;
    delay_ = delay;
    
}

void TriSeg::write_header(std::ofstream& f){
    f << " " << "C" << "Lsc";
}
//void TriSeg::write_timestep(double t, std::ofstream& f, double lambda){
//    double force;
//    force = this-> calcCurrentForce(lambda);
//    f << " " << state_vec[state_C] << " " << state_vec[state_Lsc];
//    //std::cout << "C" << " " << " Lsc"  << " " << "Lambda" << " " << "State" << std::endl;
//    //std::cout << state_vec[state_C] << " " << state_vec[state_Lsc] << " "; // << std::endl;
//}

double TriSeg::calcForce(double t, double dt, double lambda){
    std::vector<double> newstate(last2);
    double Force;
    this->extrapolate_state(t, dt, lambda, state_vec, newstate);
    
    Force = σact * newstate[state_C] * (newstate[state_Lsc] - Lsc0) * ((calc_Ls(lambda) - newstate[state_Lsc])/Lseiso);
    //std::cout << Force << std::endl;
    return Force;
}

double TriSeg::calcCurrentForce(double lambda){
    std::vector<double> newstate(last2);
    double Force;
    
    Force = σact * state_vec[state_C] * (state_vec[state_Lsc] - Lsc0) * ((calc_Ls(lambda) - (state_vec[state_Lsc])/Lseiso));
    return Force;
}

double TriSeg::getdForce_dLambda (double t, double dt, double lambda, double delta){
    
    double upperpnt = calcForce(t, dt, lambda + delta);
    double lowerpnt = calcForce(t, dt, lambda - delta);
    return (upperpnt - lowerpnt)/(2 * delta);
}

void TriSeg::integrate(double t, double dt, double lambda){
    std::vector<double> newstate(last2);
    this->extrapolate_state(t, dt, lambda, state_vec, newstate);
    state_vec = newstate;
    
}

double TriSeg::calc_Ls(double lambda) {
    double Ls = lambda * Lsref;
    return Ls;
}

double TriSeg::der_Lsc(double Ls, double dt) {
    //std::cout << Ls << std::endl;
    return (((Ls - state_vec[state_Lsc])/Lseiso) - 1) * vmax;
}

double TriSeg::Cl() {
    return tanh(4.0* pow((state_vec[state_Lsc] - Lsc0), 2));
}

double TriSeg::Frise(double t) {
    double x = min(8, max(0, t/τR));
    return 0.02 * pow(x, 3) * pow(8-x, 2) * exp(-x);
}

double TriSeg::T() {
    return τsc * (0.29 + (0.3*state_vec[state_Lsc]));
}

double TriSeg::der_C(double t) {
    return (1/τR) * Cl() * Frise(t) + (1/τD) * ((Crest - state_vec[state_C])/(1 + exp((T() - t)/τD)));
}

void TriSeg::extrapolate_state (double t, double dt, double lambda, const std::vector<double>& start_state, std::vector<double>& new_state){
    t -= delay_;
    if (t < 0) {
        t = 0;
    }
    
    double Ls = calc_Ls(lambda);
    //std::cout << lambda << " " << Ls << std::endl;
    double derLs = der_Lsc(Ls, dt);
    new_state[state_Lsc] = start_state[state_Lsc] + (derLs * dt);
    
    double derC = der_C(t);
    new_state[state_C] = start_state[state_C] + (derC * dt);
}

double TriSeg::min(double a, double b) {
    if(a < b) {
        return a;
    } else {
        return b;
    }
}

double TriSeg::max(double a, double b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}
