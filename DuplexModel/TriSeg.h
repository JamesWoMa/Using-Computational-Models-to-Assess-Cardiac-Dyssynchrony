//
//  TriSeg.h
//  DuplexModel
//
//  Created by James WoMa

#ifndef __DuplexModel__TriSeg__
#define __DuplexModel__TriSeg__

#include "Filament.h"
#include <vector>
enum state2 {state_C, state_Lsc, last2};
class TriSeg : public Filament
{
public:
    TriSeg(double lambda, double delay);
    double calcForce(double t, double dt, double lambda);
    double calcCurrentForce(double lambda);
    double getdForce_dLambda (double t, double dt, double lambda, double delta);
    void integrate(double t, double dt, double lambda);
    
    void write_header(std::ofstream& f);
    //void write_timestep(double t, std::ofstream& f, double lambda);

private:
    std::vector<double> state_vec;
    double Crest;
    double Lsc0; // m
    double Lsref; // m
    double Lseiso; // m
    double vmax; // m s-1
    double τD; // ms
    double τR; // ms
    double τsc; // ms
    double σact; //kpa
    double delay_;
    
    void extrapolate_state (double lambda, double t, double dt, const std::vector<double>& start_state, std::vector<double>& new_state);
    
    double der_Lsc(double Ls, double dt);
    double calc_Ls(double lambda);
    double der_C(double t);
    double Cl();
    double Frise(double t);
    double T();
    double min(double a, double b);
    double max(double a, double b);
    
};
#endif /* defined(__DuplexModel__TriSeg__) */
