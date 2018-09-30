//
//  Passive.h
//  DuplexModel
//
//  Created by James WoMa

#ifndef __DuplexModel__Passive__
#define __DuplexModel__Passive__

#include <iostream>

class Passive {
public:
    Passive(double beta, double unstretched);
    double getForce(double lambda);
    double getdForce(double lambda);
private:
    double beta_; // kPa
    double alpha_; // um/um
    double unstretched_;
};

#endif /* defined(__DuplexModel__Passive__) */
