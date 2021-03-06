#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "math.h"
#include "std_srvs/Trigger.h"
#include "string"
#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    FILE *lsofFile_p = popen("~/cpp/Driver_IMU/minimu9-ahrs --output euler", "r");
    if (!lsofFile_p)
    {
        return -1;
    }
    ros::init(argc, argv, "cap_node");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("capRaw", 1000);
    ros::Rate loop_rate(15.);
    while (ros::ok())
    {
        std_msgs::Float64 msg;
        char buffer[100];
        char *line_p = fgets(buffer, sizeof(buffer), lsofFile_p);
        float data_cap = strtof((buffer),0);
        msg.data = data_cap;
        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    pclose(lsofFile_p);
    return 0;
}