/**
 * @file    MyRobot.cpp
 * @brief   Avoid obstacle using odometry.
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;
    _left_encoder = 0.0;
    _right_encoder = 0.0;


    enableEncoders(_time_step);


}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    disableEncoders();

}

//////////////////////////////////////////////


void MyRobot::run()
{
    double distance;

    while (step(_time_step) != -1) {
        // lectura sensores

        _left_encoder=getLeftEncoder();
        _right_encoder=getRightEncoder();

        distance += _left_encoder / 1000 * .0825;

        // lógica control

        if((distance < 1.35) || ((distance > 5.65) && (distance < DESIRED_DISTANCE))){
            straight(distance);
        }
        else{
            if((distance > 1.35) && (distance < 1.7))
            {
                turn_right(distance);

            }
            else{
                if((distance > 1.7) && (distance < 4.8))
                {
                    forward(distance);
                }
                else{
                    if((distance > 4.8) && (distance < 5.65))
                    {
                        turn_left(distance);
                    }

                    else{
                        _right_speed=0;
                        _left_speed=0;
                        cout<<"Stop"<<endl;
                    }
                }
            }
        }

        // acciones (movimiento)

        setSpeed(_left_speed,_right_speed);
    }
}

//////////////////////////////////////////////

void MyRobot::straight(double distance)
{

    if(_left_encoder > _right_encoder)
    {
        _right_speed = MAX_SPEED;
        _left_speed = MAX_SPEED-10;
    }
    else{
        _right_speed = MAX_SPEED-10;
        _left_speed = MAX_SPEED;
    }

    cout<<"Straight"<<endl;
    cout<<"LeftEncoder: "<<_left_encoder<<" RightEncoder: "<<_right_encoder<<endl;
    cout<<"Distance: "<<distance<<endl;

}

//////////////////////////////////////////////

void MyRobot::turn_right(double distance)
{
    _right_speed=0;
    _left_speed=MAX_SPEED-10;

    cout<<"Turn right"<<endl;
    cout<<"Distance: "<<distance<<endl;

}

//////////////////////////////////////////////

void MyRobot::turn_left(double distance)
{
    _left_speed=0;
    _right_speed=MAX_SPEED-10;

    cout<<"Turn left"<<endl;
    cout<<"Distance: "<<distance<<endl;

}

//////////////////////////////////////////////

void MyRobot::forward(double distance)
{
    _right_speed=MAX_SPEED;
    _left_speed=MAX_SPEED;

    cout<<"Forward"<<endl;
    cout<<"Distance: "<<distance<<endl;
}

//////////////////////////////////////////////
