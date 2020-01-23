#pragma once

class Basic
{
public:
    Basic() = default;                             // Constructor
    ~Basic() = default;                            // Destructor
    Basic(const Basic& other) = delete;            // Copy constructor 
    Basic& operator=(const Basic& other) = delete; // Copy assignment

    void function();

private:

};
