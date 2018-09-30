// Created by James WoMa

#include "Sarcomere.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>


Sarcomere::Sarcomere(double ca, double tn, double xb, double q1, double q2, double lambda, double t_cycle, double delay)
: state_vec(last)
{
    delay_ = delay;
    t_cycle_ = t_cycle;
    calcium_peak_ = .6;
    intn = tn;
    inxb = xb;
    inq1 = q1;
    inq2 = q2;
    state_vec[state_ca] = ca;
    state_vec[state_tn] = tn;
    state_vec[state_xb] = xb;
    state_vec[state_q1] = q1;
    state_vec[state_q1] = q2;
    state_vec[state_lambda] = lambda;
    //From Calcium Model in Li 2011
    V_up_ = 0.0785;//0.0785 // FF mice 0.0785 KO mice 0.0017
    K_d_ = 0.6; //kd_buffer = 0.6 range 60-160 micrometers
    K_m_up_ = 0.322;
    B_max_ = 109.0; //109.0 microMoles
    //From Land 2012
    ca2p_T50_ref_ = 0.8; //microMoles
    tn_50_ = 0.35;
    beta_0_ = 1.65;
    beta_1_ = -1.5;
    k_tn_ = 0.1; //2.0 //ms-1
    k_xb_ = 0.1; //k_np = 0.1
    n_tn_ = 2.0;
    n_xb_ = 5.0;
    A_1_ = -4.0;
    A_2_ = -4.0 * A_1_;
    alpha_1_ = 150.0e-3; //ms-1
    alpha_2_ = 500.0e-3; //ms-1
    a_ = 0.35 * 230; //2x = 230 1x = 500 1/2 = 1060
    T_ref_ = 120.0; //kPa
    
}

//Finds force of next timestep, based on lambda and current state
//t is time, dt is timestep, and lambda is stretch ratio
double Sarcomere::calcForce(double t, double dt, double lambda){
    std::vector<double> newstate(last);
    double Force;
    this->extrapolate_state(t, dt, lambda, state_vec, newstate);
    //Find hlambda
    hlambda = 0.0;
    double derhlambda = 0.0;
    if (lambda < 1.2) {
        derhlambda = derive_hlambda(lambda);
    } if (lambda >= 1.2) {
        derhlambda = derive_hlambda(1.2);
    }
    if (derhlambda > 0) {
        hlambda = derhlambda;
    } if (derhlambda <= 0) {
        hlambda = 0;
    }
    //find g(q)
    double state_q = newstate[state_q1] + newstate[state_q2];
    double g_q_ = 0.0;
    if (state_q <= 0) {
        g_q_ = ((a_ * state_q) + 1) / (1 - state_q);
    } if (state_q > 0) {
        g_q_ = (1 + ((a_ + 2) * state_q)) / (1 + state_q);
    }
    Force = T_ref_ * hlambda * g_q_ * newstate[state_xb];
    return Force;
}
double Sarcomere::calcCurrentForce (){
    double Force;
    
    //find hlambda
    hlambda = 0.0;
    double derhlambda = 0.0;
    if (state_vec[state_lambda] < 1.2) {
        derhlambda = derive_hlambda(state_vec[state_lambda]);
    } if (state_vec[state_lambda] >= 1.2) {
        derhlambda = derive_hlambda(1.2);
    }
    if (derhlambda > 0) {
        hlambda = derhlambda;
    } if (derhlambda <= 0) {
        hlambda = 0;
    }
    //find g(q)
    double state_q = state_vec[state_q1] + state_vec[state_q2];
    double g_q_ = 0.0;
    if (state_q <= 0) {
        g_q_ = ((a_ * state_q) + 1) / (1 - state_q);
    } if (state_q > 0) {
        g_q_ = (1 + ((a_ + 2) * state_q)) / (1 + state_q);
    }
    Force = T_ref_ * hlambda * g_q_ * state_vec[state_xb];
    return Force;
}
//Finds the derivative of the force at the next time step with respect to lambda
double Sarcomere::getdForce_dLambda (double t, double dt, double lambda, double delta){
    
    double upperpnt = calcForce(t, dt, lambda + delta);
    double lowerpnt = calcForce(t, dt, lambda - delta);
    return (upperpnt - lowerpnt)/(2 * delta);
}
//Steps model forward by time step dt
void Sarcomere::integrate(double t, double dt, double lambda){
    std::vector<double> newstate(last);
    this->extrapolate_state(t, dt, lambda, state_vec, newstate);
    state_vec = newstate;
    
}
void Sarcomere::write_header(std::ofstream& f){
    f << " " << "Calcium" << " " << "Troponin" << " " << "CrossBridges" << " " << "Q1" << " " << "Q2" << " " << "HLambda";
}
void Sarcomere::write_timestep(double t, std::ofstream& f){
    double force;
    force = this-> calcCurrentForce();
    f << " " << state_vec[state_ca] << " " << state_vec[state_tn] << " " << state_vec[state_xb] << " " << state_vec[state_q1] << " " << state_vec[state_q2] << " " << hlambda;
}
void Sarcomere::extrapolate_state (double t, double dt, double lambda, const std::vector<double>& start_state, std::vector<double>& new_state){
    double time = t - delay_;
    if (time < 0) {
        time = 0;
    }
    
    time = time - (int(time/t_cycle_)) * t_cycle_;
    //lambda
    double derlambda;
    derlambda = (lambda - start_state[state_lambda])/dt;
    new_state[state_lambda] = lambda;
    double derca;
    //calcium - cyclic
    
    const double durationInterval = 1;
    if(time > delay_ && time < delay_ + durationInterval) {
        derca = calcium_peak_/durationInterval;
    } else {
        derca = (-V_up_ * pow(start_state[state_ca],2) * pow(1 + (K_d_ / start_state[state_ca]), 2)) / (K_d_ * B_max_ * (1 + pow(K_m_up_/start_state[state_ca], 2)));//(-V_up_ * pow(start_state[state_ca], 2) * (pow(1+K_d_/start_state[state_ca],2))) / ((1 + pow(K_m_up_*start_state[state_ca],2))*(pow(start_state[state_ca],2)*pow(1+(K_d_/start_state[state_ca]),2) + (B_max_*K_d_)));
    }
    new_state[state_ca] = start_state[state_ca] + (derca * dt);
    
    //troponin
    double dertn;
    double ca_tn50_ = ca2p_T50_ref_ * (1 + beta_1_ * (lambda - 1));
    dertn = k_tn_ * (pow(start_state[state_ca]/ca_tn50_, n_tn_) * (1-start_state[state_tn]) - start_state[state_tn]);
    new_state[state_tn] = start_state[state_tn] + (dertn * dt);
    
    //backwards euler cross bridges
    double derxb;
    double permtot_ = sqrt(pow(new_state[state_tn]/tn_50_, n_xb_));
    derxb = (((start_state[state_xb]*permtot_) + (k_xb_*dt*pow(permtot_, 2)))/(permtot_ + (k_xb_*dt*(pow(permtot_, 2) + 1))) - start_state[state_xb])/dt;
    new_state[state_xb] = start_state[state_xb] + (derxb * dt);
    //q1
    double derq1;
    derq1 = A_1_ * derlambda - (alpha_1_ * start_state[state_q1]);
    new_state[state_q1] = start_state[state_q1] + (derq1 * dt);
    //q2
    double derq2;
    derq2 = A_2_ * derlambda - (alpha_2_ * start_state[state_q2]);
    new_state[state_q2] = start_state[state_q2] + (derq2 * dt);
    
}
double Sarcomere::derive_hlambda (double lambda) {
    double derhlambda = 0.0;
    
    if (lambda < .87) {
        derhlambda = 1 + beta_0_ * (lambda + lambda - 1.87);
    } if (lambda >= .87) {
        derhlambda = 1 + beta_0_ * (lambda + .87 - 1.87);
    }
    return derhlambda;
}
bool Sarcomere::comp_double (double a, double b, double tol) {
    return fabs(a-b) < tol;
}
