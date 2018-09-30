//
//  Passive.cpp
//  DuplexModel
//
//  Created by James WoMa

#include "Passive.h"
#include <cmath>

Passive::Passive(double beta, double unstretched) {
    unstretched_ = unstretched;
    beta_ = beta; //0.5
    alpha_ = 26.28;
}

double Passive::getForce(double lambda) {
    return beta_ * (exp(alpha_ * (lambda - 1))-1);
}

double Passive::getdForce(double lambda) {
    //Analytical
    return beta_ * exp(alpha_*(lambda-1)) * alpha_;
}
