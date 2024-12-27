#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Imu.h>

class TopicRepublisher
{
public:
    TopicRepublisher(ros::NodeHandle& nh)
    {
        // 订阅 /hesai/pandar 话题
        pandar_sub_ = nh.subscribe("/hesai/pandar", 10, &TopicRepublisher::pandarCallback, this);
        // 发布 /points_raw 话题
        points_pub_ = nh.advertise<sensor_msgs::PointCloud2>("/velodyne_points", 10);

        // 订阅 /vectornav/Imu 话题
        imu_sub_ = nh.subscribe("/vectornav/IMU", 10, &TopicRepublisher::imuCallback, this);
        // 发布 /imu_correct 话题
        imu_pub_ = nh.advertise<sensor_msgs::Imu>("/imu/data", 10);
    }

private:
    void pandarCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
    {
        sensor_msgs::PointCloud2 modified_msg = *msg;
        modified_msg.header.frame_id = "velodyne"; // 修改 frame_id
        modified_msg.fields[4].name = "time";
        modified_msg.fields[5] = modified_msg.fields[4];
        modified_msg.fields[4] = msg->fields[5];
        points_pub_.publish(modified_msg);
    }

    void imuCallback(const sensor_msgs::ImuConstPtr& msg)
    {
        sensor_msgs::Imu modified_msg = *msg;
        modified_msg.header.frame_id = "/imu"; // 修改 frame_id
        imu_pub_.publish(modified_msg);
    }

    ros::Subscriber pandar_sub_;
    ros::Publisher points_pub_;

    ros::Subscriber imu_sub_;
    ros::Publisher imu_pub_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "topic_republisher_node");
    ros::NodeHandle nh;

    TopicRepublisher republisher(nh);

    ros::spin();

    return 0;
}
