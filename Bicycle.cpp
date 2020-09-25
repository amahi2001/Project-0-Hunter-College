//abrar mahi
//abrar.mahi14@myhunter.cuny.edu
#include <iostream>
#include <stdlib.h>
#include "Bicycle.hpp"
using namespace std;

Bicycle::Bicycle() // defualt constructor 
{
    //initialized private members
    curr_speed_ = 0;     
    curr_direction_ = 0; 
    distance_traveled_ = 0;
    seat_height_ = 10;
    curr_pedal_intensity_ = bike_details::NONE;

    int random = rand() % 4;

    switch (random) //randomly choosing a bike type
    {
    case 0:
        b_type_ = bike_details::bike_type::BMX;
        break;
    case 1:
        b_type_ = bike_details::bike_type::MOUNTAIN;
        break;
    case 2:
        b_type_ = bike_details::bike_type::TOURING;
        break;
    case 3:
        b_type_ = bike_details::bike_type::ROAD;
        break;
    }
}

Bicycle::Bicycle(int kind_of_bike) //param cinstructor, which allows user to choose bike
{
    curr_speed_ = 0;     
    curr_direction_ = 0; 
    distance_traveled_ = 0;
    seat_height_ = 10;
    curr_pedal_intensity_ = bike_details::pedalling_intensity::NONE;

    switch (kind_of_bike) // choose based on the param
    {
    case 0:
        b_type_ = bike_details::bike_type::BMX;
        break;
    case 1:
        b_type_ = bike_details::bike_type::MOUNTAIN;
        break;
    case 2:
        b_type_ = bike_details::bike_type::TOURING;
        break;
    case 3:
        b_type_ = bike_details::bike_type::ROAD;
        break;
    }
}

string Bicycle ::getDirection() // driection based on -360 <= degrees <= 360 degrees
{
    string result;
    if (curr_direction_ == 0 || curr_direction_ == 360 || curr_direction_ ==-360)
    {
        result = "East";
    }

    else if (curr_direction_ == 90)
    {
        result = "North";
    }

     else if (curr_direction_ == 270)
    {
        result = "South";
    }

    else if (curr_direction_ == 180)
    {
        result = "West";
    }

    else if (curr_direction_ > 0 && curr_direction_ < 90) //between north and east
    {
        result = "Northeast";
    }

    else if ( curr_direction_ > 90 && curr_direction_ < 180) //between north and west
    {
        result = "Northwest";
    }

    else if ( curr_direction_ > 180 && curr_direction_ < 270)//between south and west 
    {
        result = "Southwest";
    }

    else if (curr_direction_ > 270 && curr_direction_ < 360)//between south and east
    {
        result = "Southeast";
    }
    else
    {
        result = "South";
    }
    return result;
}

string Bicycle ::getBikeType() //getter for the bike type, converting the enum to a string
{
    string result;

    switch (b_type_) 
    {
    case bike_details::bike_type::BMX:
        result = "BMX";
        break;
    case bike_details::bike_type::MOUNTAIN:
        result = "MOUNTAIN";
        break;
    case bike_details::bike_type::TOURING:
        result = "TOURING";
        break;
    case bike_details::bike_type::ROAD:
        result = "ROAD";
        break;
    }
    return result;
}

int Bicycle ::getSeatHeight() //getter for seat height
{
    return seat_height_;
}

float Bicycle ::getSpeed() //getter for the speed in mph
{
    return curr_speed_;
}

float Bicycle ::getDistanceTraveled() //getter for distance traveled in miles
{
    return distance_traveled_;
}

string Bicycle ::getIntensity() // getter for the pedalling intensity, converting enum to string
{
    string inten; // pedalling intensity

    if (curr_pedal_intensity_ == bike_details::NONE)
    {
        inten = "None";
    }

    else if (curr_pedal_intensity_ == bike_details::LOW)
    {
        inten = "Low";
    }

    else if (curr_pedal_intensity_ == bike_details::MEDIUM)
    {
        inten = "Medium";
    }

    else if (curr_pedal_intensity_ == bike_details::HIGH)
    {
        inten = "High";
    }

    return inten;
}

void Bicycle ::changeSeatHeight(int inches) //changes the seat height based on param
{
    //0 <= inches < 37;
    if (inches < 0)
    {
        seat_height_ = 0;
    }
    else if (inches > 36)
    {
        seat_height_ = 36;
    }
    else
    {
        seat_height_ = inches;
    }
}

void Bicycle ::turn(float degrees) // adds degrees to the direction to change the dierection or turn
{
    //the range of the turn must be at or between -360 and 360
    //if the degree is over or under that range it must be converted to 0->360
    
    if (degrees >= 0 && degrees < 360) //stays the saeme
    {
        degrees = degrees;
    }
    else if (degrees == 360 || degrees == -360) // 360 -360 and 0 are the same
    {
        degrees = 0;
    }
    else if (degrees < 0 && degrees > -360) //converting to postive
    {
        degrees = degrees + 360;
    }
    else if (degrees > 360) //converting to 0->360
    {
        while (degrees > 360)
        {
            degrees = degrees - 360;
        }
        degrees = degrees;
    }
    else if (degrees < -360) // converting to positive and 0->360
    {
        while (degrees < -360)
        {
            degrees = degrees + 360;
        }
        if (degrees< 0)
        {
            degrees = 360 + degrees; 
        }
    }
    curr_direction_ += degrees; // adding the degrees turned to the current direction to make the turn
}

void Bicycle ::updateSpeed() // changes the speed based on the formula
{
    curr_speed_ = ((curr_pedal_intensity_)/8)*(b_type_) + ((curr_pedal_intensity_)/8 + (b_type_));

    if (curr_pedal_intensity_ == bike_details::NONE)
    {
        curr_speed_ = 0;
    } 
}

void Bicycle ::pedal() // speeds up the pedalling intensity by 1 as long its not HIGH already
{
    if (curr_pedal_intensity_ != bike_details::HIGH)
    {
        if (curr_pedal_intensity_ == bike_details::NONE)
        {
            curr_pedal_intensity_ = bike_details::LOW;
        }
        else if (curr_pedal_intensity_ == bike_details::LOW)
        {
            curr_pedal_intensity_ = bike_details::MEDIUM;
        }
        else if (curr_pedal_intensity_ == bike_details::MEDIUM)
        {
            curr_pedal_intensity_ = bike_details::HIGH;
        }
        updateSpeed();
    }
}

void Bicycle ::brake()// slows down pedalling intensity by 1 as long as it's not LOW already
{
    if (curr_pedal_intensity_ != bike_details::NONE)
    {
        if (curr_pedal_intensity_ == bike_details::LOW)
        {
            curr_pedal_intensity_ = bike_details::NONE;
        }
        else if (curr_pedal_intensity_ == bike_details::MEDIUM)
        {
            curr_pedal_intensity_ = bike_details::LOW;
        }
        else if (curr_pedal_intensity_ == bike_details::HIGH)
        {
            curr_pedal_intensity_ = bike_details::MEDIUM;
        }
        updateSpeed();
    }
}

float Bicycle ::ride(float duration) // total distance travlled
{
    float new_dist = curr_speed_ / duration; //calulating distance: distance = speed/time
    distance_traveled_ += new_dist; // incremeting the distance
    return distance_traveled_;
}

int main()
{
    return 0;
}  