#ifndef _PID_SOURCE_
#define _PID_SOURCE_

#include <iostream>
#include <cmath>
#include <PID.h>

class PIDImpl
{
    public:
        PIDImpl( double dt, double max, double min, double Kp, double Kd, double Ki );
        ~PIDImpl();
        double Update( double setpoint, double current_val);

    private:
        double _dt;
        double _max;
        double _min;
        double _Kp;
        double _Kd;
        double _Ki;
        double _pre_error;
        double _integral;
};


PID::PID( double dt, double max, double min, double Kp, double Kd, double Ki )
{
    pid1 = new PIDImpl(dt,max,min,Kp,Kd,Ki);
}

double PID::Update( double setpoint, double current_val )
{
    return pid1->Update(setpoint,current_val);
}
PID::~PID() 
{
    delete pid1;
}


PIDImpl::PIDImpl( double dt, double max, double min, double Kp, double Kd, double Ki ) :
    _dt(dt),
    _max(max),
    _min(min),
    _Kp(Kp),
    _Kd(Kd),
    _Ki(Ki),
    _pre_error(0),
    _integral(0)
{
}

double PIDImpl::Update( double setpoint, double current_val )
{
    double error = setpoint - current_val;
    
    // Proportional, integral, derivatve terms
    double Pterm = _Kp * error;
    
    _integral += error * _dt;
    double Iterm = _Ki * _integral;

    double derivative = (error - _pre_error) / _dt;
    double Dterm = _Kd * derivative;

    //Calculate total output
    double output = Pterm + Iterm + Dterm;

    // Restrict the output to desired max/min value
    if(output > _max)
        output = _max;
    else if(output < _min)
        output = _min;

    // Save error to previous error
    _pre_error = error;

    return output;
}

PIDImpl::~PIDImpl()
{
}

#endif