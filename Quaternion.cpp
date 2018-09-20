//
//  Quaternion.cpp
//  TumblingPencil
//
//  Created by Sovann Chak on 9/18/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#include "Quaternion.hpp"

Quaternion::Quaternion(double w, Matrix u) {
    w_ = w;
    u_ = u;
}

Quaternion::~Quaternion() {
    
}

Quaternion& Quaternion::operator=(Quaternion rhs) {
    w_ = rhs.w_;
    u_ = rhs.u_;
    return *this;
}

Quaternion& Quaternion::operator=(Matrix m) {
    u_ = Matrix(1,3);
    if(m.get_rows() == 1 && m.get_cols() == 4) {
        w_ = m(0,0);
        u_.place(m(0,1), 0, 0);
        u_.place(m(0,2), 0, 1);
        u_.place(m(0,3), 0, 2);
        return *this;
    }
    else if(m.get_cols() == 1 && m.get_rows() == 4) {
        w_ = m(0,0);
        u_.place(m(1,0), 0, 0);
        u_.place(m(2,0), 0, 1);
        u_.place(m(3,0), 0, 2);
        return *this;
    }
    else{
        throw std::runtime_error("Right hand side is not a quaternion!");
    }
}

Quaternion Quaternion::operator+(Quaternion rhs) {
    double w_addition = w_+rhs.w_;
    double x = u_(0,0) + rhs.u_(0,0);
    double y = u_(0,1) + rhs.u_(0,1);
    double z = u_(0,2) + rhs.u_(0,2);
    
    Matrix new_coords = Matrix(1,3);
    new_coords = { x, y, z};
    
    Quaternion q_to_return = Quaternion(w_addition, new_coords);
    
    return q_to_return;
}

Quaternion Quaternion::operator*(Quaternion rhs) {
    
    double w_mult = w_*rhs.w_;
    double vect_dot = u_.dot(rhs.u_);
    
    Matrix mult1 = rhs.u_*w_;
    Matrix mult2 = u_*rhs.w_;
    
    double cross_i = (u_(0,1)*rhs.u_(0,2) - u_(0,2)*rhs.u_(0,1));
    double cross_j = (u_(0,2)*rhs.u_(0,0) - u_(0,0)*rhs.u_(0,2));
    double cross_k = (u_(0,0)*rhs.u_(0,1) - u_(0,1)*rhs.u_(0,0));
    
    Matrix cross = Matrix(1,3);
    cross = { cross_i, cross_j, cross_k };
    
    double new_w = w_mult - vect_dot;
    Matrix new_u = mult1+mult2+cross;
    
    Quaternion q_return = Quaternion(new_w, new_u);
    return q_return;
}

Quaternion Quaternion::operator*(double scalar) {
    double scaled_w = w_*scalar;
    Matrix scaled_u = Matrix(1,3);
    scaled_u = u_*scalar;
    
    Quaternion q_return = Quaternion(scaled_w, scaled_u);
    
    return q_return;
}

double Quaternion::get_w() {
    return w_;
}

Matrix Quaternion::get_u() {
    return u_;
}

Matrix Quaternion::rot(double theta) {
    Matrix rotation = Matrix(3,3);
    
    double xx = u_(0, 0)*u_(0, 0)*((double)(1-cos(theta)));
    double xy = u_(0, 0)*u_(0, 1)*((double)(1-cos(theta)));
    double xz = u_(0, 0)*u_(0, 2)*((double)(1-cos(theta)));
    
    double yy = u_(0, 1)*u_(0, 1)*((double)(1-cos(theta)));
    double yz = u_(0, 1)*u_(0, 2)*((double)(1-cos(theta)));
    
    double zz = u_(0, 2)*u_(0, 2)*((double)(1-cos(theta)));
    
    
    rotation.place(xx+cos(theta), 0, 0);
    rotation.place(xy+u_(0,2)*sin(theta), 1, 0);
    rotation.place(xz-u_(0,1)*sin(theta), 2, 0);

    rotation.place(xy-u_(0,2)*sin(theta), 0, 1);
    rotation.place(yy+cos(theta), 1, 1);
    rotation.place(yz+u_(0,0)*sin(theta), 2, 1);

    rotation.place(xz+u_(0,1)*sin(theta), 0, 2);
    rotation.place(yz-u_(0,0)*sin(theta), 1, 2);
    rotation.place(zz+cos(theta), 2, 2);
    
    return rotation;
}

void Quaternion::print() {
    std::cout << w_;
    if(u_(0,0) > 0) {
        std::cout << "+";
    }
    std::cout << u_(0,0)<<"i";
    if(u_(0,1) > 0) {
        std::cout << "+";
    }
    std::cout << u_(0,1) << "j";
    if(u_(0, 2) > 0) {
        std::cout << "+";
    }
    std::cout << u_(0, 2) << "k " << std::endl;
}
















