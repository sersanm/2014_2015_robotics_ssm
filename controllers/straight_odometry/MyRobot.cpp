/**
 * @file    MyRobot.cpp
 * @brief   Follow a straight line using odometry.
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

    while (step(_time_step) != -1){

        //Lectura sensores

        _left_encoder=getLeftEncoder();
        _right_encoder=getRightEncoder();

        distance += _left_encoder / 5 * .0825;

        //Lógica control

        if(distance<DESIRED_DISTANCE){
            straight(distance);
        }
        else{
            _left_speed=0;
            _right_speed=0;
            cout<<"Stop"<<endl;

        }

        //Acciones (movimiento)

        setSpeed(_left_speed,_right_speed);

    }


}

//////////////////////////////////////////////

void MyRobot::straight(double distance)
{


    if(_left_encoder > _right_encoder){
        _right_speed=MAX_SPEED;
        _left_speed=MAX_SPEED-15;
    }
    else{
        _right_speed=MAX_SPEED-15;
        _left_speed=MAX_SPEED;
    }

    cout<<"LeftEncoder: "<<_left_encoder<<" RightEncoder: "<<_right_encoder<<endl;
    cout<<"Distance: "<<distance<<endl;


}

//////////////////////////////////////////////
