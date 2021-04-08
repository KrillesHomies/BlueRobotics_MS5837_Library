/* Example code for the modified MS5837-30BA c++ library running as a ROS node */


#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/FluidPressure.h>
#include <sensor_msgs/Temperature.h>
#include <stdio.h>
#include <stdint.h>
#include <ros/ros.h>
#include <sstream>
#include "MS5837.hpp"

MS5837 sensor;
sensor_msgs::FluidPressure pressure;
sensor_msgs::Temperature temp;
ros::Publisher pub_pressure, pub_temp;

void Sample(const ros::TimerEvent& event)
{
    // Read sesnor ADC
    sensor.read_data();

    // Update Messages
    pressure.header.stamp  = ros::Time::now();
    temp.header.stamp = pressure.header.stamp;
    pressure.header.seq++;
    temp.header.seq++;
  
    // Get values
    pressure.fluid_pressure = sensor.pressure();
    temp.temperature = sensor.temperature();

    // Publish topics 
    pub_pressure.publish(pressure);
    pub_temp.publish(temp);
}


int main(int argc, char **argv)
{
    float publish_rate;
    ros::init(argc, argv, "MS53837_node");
    ros::NodeHandle nh;
    ROS_INFO("Starting MS53837_node \n");
    // Get Parameters
    nh.param("publish_rate",publish_rate, 10.0f);

    ROS_INFO("Initiating sensor MS53837_node \n");
    // Init sesnor
    int i = 0;
    while (!sensor.init()) {
        ROS_WARN("Failed to initiate MS53837 sensor, attempt %d \n",i);
        ros::Duration(2.0).sleep();
        if(i > 4)
        {
            ROS_ERROR("Failed to initiate MS53837 sensor, shutting down node!\n");
            return -1;
        }
            
    }
    ROS_INFO("Sensor Initiated \n");
    // Set model
    sensor.setModel(MS5837::MS5837_30BA);

    // Initiate messages
    pressure.header.frame_id  = "/MS53837_sensor";
    temp.header.frame_id  = "/MS53837_sensor";
    pressure.header.seq = 0;
    temp.header.seq = 0;

    // Advertise topics
    pub_pressure = nh.advertise<sensor_msgs::FluidPressure>("MS5837/pressure", 10);
    pub_temp = nh.advertise<sensor_msgs::Temperature>("MS5837/temperature", 10);
    
    // Initiate Timer
    ros::Timer timerReadSesnor = nh.createTimer(ros::Duration(1.0 / publish_rate), Sample);
    ros::spin();
}