# ROS node for MS5837 Sensor

    Package contains a modified version of the MS5837 Arduino MS5837-30BA Pressure/Temperature Sensor library. The library is modified to work with a Raspberry Pi using the wiringPi library.

    https://bluerobotics.com/store/sensors-sonars-cameras/sensors/bar30-sensor-r1/
    

## Prerequisites

WiringPi
    sudo apt-get install WiringPi

ROS
    see https://www.ros.org/

## Published Topics

    MS5837/pressure - sensor_msgs::FluidPressure

    MS5837/temperature - sensor_msgs::Temperature

## Parameters 

    publish_rate (defualt 10.0) - Ros Publish Rate

