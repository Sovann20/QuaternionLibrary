//
//  Quaternion.hpp
//  TumblingPencil
//
//  Created by Sovann Chak on 9/18/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "Matrix.hpp"
#include <cmath>

class Quaternion {
    
    double w_;
    Matrix u_;
    
public:
    Quaternion(double,double,double,double);
    Quaternion(double, Matrix);
    ~Quaternion();
    
    Quaternion& operator=(Quaternion);
    Quaternion& operator=(Matrix);
    Quaternion operator+(Quaternion);
    Quaternion operator*(Quaternion);
    Quaternion operator*(double);
    
    double get_w();
    
    Matrix get_u();
    Matrix rot(double theta);

    void print();
    
    
};

#endif /* Quaternion_hpp */
