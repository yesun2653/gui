/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/Int32.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include <sstream>
#include "Eigen/Dense"
#include "../include/gui/qnode.hpp"
#include "../include/gui/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/
using Eigen::MatrixXd;
using Eigen::VectorXd;
namespace gui {

/*****************************************************************************
** Implementation
*****************************************************************************/
//extern int ros_topic_data;
//extern int task_flag;
//extern int ros_arm_select_flag;
extern double LP;
extern double LPm;
extern double LPd;
extern double LK;
extern double LA;
extern double LF;
extern double RP;
extern double RPm;
extern double RPd;
extern double RK;
extern double RA;
extern double RF;

//extern double x_des;
//extern double y_des;
//extern double z_des;
//extern double yaw_des ;
//extern double pitch_des ;
//extern double roll_des ;

//extern bool ros_status_flag;
extern bool ros_status_flag1;

VectorXd desiredQ = VectorXd::Zero(6);
std_msgs::Int32 msg;
std_msgs::Float64MultiArray desQ_array;
std_msgs::Float64MultiArray desP_array;
QNode::QNode(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv){

}

QNode::~QNode() {
    if(ros::isStarted()) {
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }

    wait();
}

bool QNode::init()
{
    ros::init(init_argc,init_argv,"gui");
    if ( ! ros::master::check() ) {
        return false;
    }
    // ===== ROS CODE 작성 ===== //
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;

    // Add your ros communications here.
    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    al_btn   = n.advertise<std_msgs::Int32>("algorithm_btn", 100);
    taskflag = n.advertise<std_msgs::Int32>("task_flag", 100);
    select = n.advertise<std_msgs::Int32>("select_arm", 100);
    des_q  = n.advertise<std_msgs::Float64MultiArray>("desQ_array", 100);
    des_p  = n.advertise<std_msgs::Float64MultiArray>("desP_array", 100);
    start();

    return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
    std::map<std::string,std::string> remappings;
    remappings["__master"] = master_url;
    remappings["__hostname"] = host_url;
    ros::init(remappings,"gui");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.
    chatter_publisher  =  n.advertise<std_msgs::String>("chatter", 1000);

    // ===== algorithm btn generation based on ros com ===== //
    al_btn   = n.advertise<std_msgs::Int32>("algorithm_btn", 100);
    taskflag   = n.advertise<std_msgs::Int32>("task_flag", 100);
    select = n.advertise<std_msgs::Int32>("select_arm", 100);
    des_q = n.advertise<std_msgs::Float64MultiArray>("desQ_array", 100);
    des_p  = n.advertise<std_msgs::Float64MultiArray>("desP_array", 100);
    start();

    return true;
}

void QNode::run() {
    ros::Rate loop_rate(1);
    int count = 0;

    desQ_array.data.clear();

    desP_array.data.clear();

    while ( ros::ok() ) {

        //    std_msgs::String msg;
        //    std::stringstream ss;
        //    ss <String< "hello world " << count;

        //    msg.data = ss.str();
        //    chatter_publisher.publish(msg);
        //    log(Info,std::string("I sent: ")+msg.data);
        desQ_array.data.clear();
        desP_array.data.clear();

//        if(ros_status_flag == true){

//            desQ_array.data.push_back(x_des*10);
//            desQ_array.data.push_back(y_des*10);
//            desQ_array.data.push_back(z_des*10);
//            desQ_array.data.push_back(yaw_des);
//            desQ_array.data.push_back(pitch_des);
//            desQ_array.data.push_back(roll_des);

//            des_q.publish(desQ_array);

//            msg.data = ros_topic_data;
//            al_btn.publish(msg);

//            msg.data = task_flag;
//            taskflag.publish(msg);
//            ros_status_flag = false;
//        }

        if(ros_status_flag1 == true){

            desQ_array.data.push_back(LP);
            desQ_array.data.push_back(LPm);
            desQ_array.data.push_back(LPd);
            desQ_array.data.push_back(LK);
            desQ_array.data.push_back(LA);
            desQ_array.data.push_back(LF);
            desQ_array.data.push_back(RP);
            desQ_array.data.push_back(RPm);
            desQ_array.data.push_back(RPd);
            desQ_array.data.push_back(RK);
            desQ_array.data.push_back(RA);
            desQ_array.data.push_back(RF);

            des_q.publish(desQ_array);

//            msg.data = ros_topic_data;
//            al_btn.publish(msg);

//            msg.data = task_flag;

//            taskflag.publish(msg);
            ros_status_flag1 = false;
        }

        //msg.data = ros_arm_select_flag;
        //select.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }

    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


//void QNode::log( const LogLevel &level, const std::string &msg) {
//    logging_model.insertRows(logging_model.rowCount(),1);
//    std::stringstream logging_model_msg;
//    switch ( level ) {
//    case(Debug) : {
//        ROS_DEBUG_STREAM(msg);
//        logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
//        break;
//    }
//    case(Info) : {
//        ROS_INFO_STREAMString(msg);
//        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
//        break;
//    }
//    case(Warn) : {
//        ROS_WARN_STREAM(msg);
//        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
//        break;
//    }
//    case(Error) : {
//        ROS_ERROR_STREAM(msg);
//        logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
//        break;
//    }
//    case(Fatal) : {
//        ROS_FATAL_STREAM(msg);
//        logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
//        break;
//    }
//    }
//    QVariant new_row(QString(logging_model_msg.str().c_str()));
//    logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
//    Q_EMIT loggingUpdated(); // used to readjust the scrollbar
//}

}  // namespace gui
