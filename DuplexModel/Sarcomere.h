//
//  Sarcomere.h
//  DuplexModel
//
//  Created by James WoMa

#ifndef DuplexModel_Sarcomere_h
#define DuplexModel_Sarcomere_h
#include "Filament.h"
#include <vector>
enum state {state_ca, state_tn, state_xb, state_q1, state_q2, state_lambda, last};
class Sarcomere : public Filament
{
public:
    Sarcomere(double ca, double tn, double xb, double q1, double q2, double lambda, double t_cycle, double delay);
    //t_cycle is the length of time that 1 muscle twitch occupies in milliseconds
    //Finds force of next timestep, based on lambda and current state
    //t is time, dt is timestep, and lambda is stretch ratio
    double calcForce(double t, double dt, double lambda);
    //Finds the derivative of the force at the next time step with respect to lambda
    double calcCurrentForce();
    //Find the force at the current timestep
    double getdForce_dLambda (double t, double dt, double lambda, double delta);
    //Steps model forward by time step dt
    void integrate(double t, double dt, double lambda);
    const std::vector<double>& getstate(){
        return state_vec;
    }
    void write_header(std::ofstream& f);
    //void write_timestep(double t, std::ofstream& f, double lambda);
private:
    double hlambda;
    //current state
    std::vector<double> state_vec;
    double delay_;
    double t_cycle_;
    double calcium_peak_;
    double intn;
    double inxb;
    double inq1;
    double inq2;
    //From Calcium Model in Li 2011
    double V_up_; // FF mice 0.0785 KO mice 0.0017
    double K_d_; //kd_buffer = 0.6 range 60-160 micrometers
    double K_m_up_;
    double B_max_; //109.0 micrometers
    //From Land 2012
    double ca2p_T50_ref_; //micrometers
    double tn_50_;
    double beta_0_;
    double beta_1_;
    double k_tn_; //ms-1
    double k_xb_; //k_np = 0.1
    double n_tn_;
    double n_xb_;
    double A_1_;
    double A_2_;
    double alpha_1_; //ms-1
    double alpha_2_; //ms-1
    double a_; //0.35
    double T_ref_; //kPa
    //Finds next state given time t, timestep dt, stretch ratio lambda, and a state variable
    void extrapolate_state(double t, double dt, double lambda, const std::vector<double>& start_state, std::vector<double>& new_state);
    //takes function of lambda to solve for hlambda
    double derive_hlambda (double lambda);
    bool comp_double(double a, double b, double tol);
    
};
#endif
