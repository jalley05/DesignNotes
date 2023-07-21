#ifndef _PID_H_
#define _PID_H_

/* PID object
 *
 * A template for a PID controller.
 *
 * Can be used for double for float types depending on optimization.
 * Advanced PID with intergral windup limits and derivative filtering.
 * 
 */

#include <limits>
#include <exception>
#include <vector>

template <class T>
class PID 
{
public:
    //! Constructors
    PID() = delete;
    PID(T dt) : m_dt(dt)
    {   
        if(dt <= 0.0) dt = 1.0;
    }   
    ~PID() = default;

    //! Run the PID controller
    T run(T setpoint, T pv) 
    {   
        // Raw proportional error
        T error = setpoint - pv; 
            
        // P
        T P_term = m_Kp * error;

        // I - with windup limit
        m_integralError += error * m_dt;
        m_integralError = (T)lim(m_integralError, -m_WindupLimit, m_WindupLimit);
        T I_term = m_Ki * m_integralError;

        // D - with d lp filter
        T D_term = m_Kd * ((error - m_prevError) / m_dt);
        m_dFiltered = m_dFiltered * m_dFilterAlpha + D_term * ((T)1.0 - m_dFilterAlpha);

        // Save previous error
        m_prevError = error;

        return P_term + I_term + m_dFiltered;
    }   

    //! Reset accumulated parameters of PID
    void reset()
    {   
        m_prevError = m_integralError = m_dFiltered = (T)0.0; 
    }   

    //! Set PID, windup and D term alpha filter: 0 alpha is inf freq limit
    void setPID(T P=1.0, T I=0.0, T D=0.0, T wl=std::numeric_limits<T>::max(), T dFilterAlpha=0.0)
    {   
        m_Kp = P;
        m_Ki = I;
        m_Kd = D;
        m_WindupLimit = wl; 
        m_dFilterAlpha = dFilterAlpha;

        // Windup limit = 0 means no limit.
        if(wl == 0) m_WindupLimit = std::numeric_limits<T>::max();
    }   

    //! Return vector of PID settings
    std::vector<T> getPID() const
    {   
        return std::vector<T>{m_Kp, m_Ki, m_Kd};
    }   

private:
    T m_Kp = (T)0.0;                //! Kp gain
    T m_Ki = (T)0.0;                //! Ki gain
    T m_Kd = (T)0.0;                //! Kd gain
    T m_WindupLimit;                //! Windup limit for I term
    T m_dFilterAlpha = (T)1.0;      //! D filter alpha term (0.0-1.0)

    T m_prevError     = (T)0.0;     //! Storage for pervious error
    T m_integralError = (T)0.0;     //! Storage for integral accumulation
    T m_dFiltered     = (T)0.0;     //! Storage for D filtered term

    T m_dt = (T)1.0;                //! Period or delta T
};

#endif // _PID_H_
