// //pcd_to_rviz.cpp
// #include<ros/ros.h>
// #include<pcl/point_cloud.h>
// #include<pcl_conversions/pcl_conversions.h>
// #include<sensor_msgs/PointCloud2.h>
// #include<pcl/io/pcd_io.h>
// //which contains the required definitions to load and store point clouds to PCD and other file formats.
 
// main (int argc, char **argv)
// {
//   ros::init (argc, argv, "UandBdetect");
//   ros::NodeHandle nh;
//   ros::Publisher pcl_pub_source = nh.advertise<sensor_msgs::PointCloud2> ("pcl_source", 1);
//   ros::Publisher pcl_pub_target = nh.advertise<sensor_msgs::PointCloud2> ("pcl_target", 1);
//   pcl::PointCloud<pcl::PointXYZ> cloud_source, cloud_target;
//   sensor_msgs::PointCloud2 output_source, output_target;
//   pcl::io::loadPCDFile ("/home/xiangchenliu/SLAMDatasets/steel1.pcd", cloud_source);//更换为自己的pcd文件路径
//   pcl::io::loadPCDFile ("/home/xiangchenliu/SLAMDatasets/steel2.pcd", cloud_target);
//   // //Convert the cloud to ROS message
//   // for (int i = 0; i < cloud.points.size(); i++)
//   // {
//   //   cloud.points[i].x = cloud.points[i].x/1000.0;
//   //   cloud.points[i].y = cloud.points[i].y/1000.0;
//   //   cloud.points[i].z = cloud.points[i].z/1000.0;
//   // }
  
//   pcl::toROSMsg(cloud_source, output_source);
//   pcl::toROSMsg(cloud_target, output_target);
//   double frequency = 1.0/15.0;
//   // output.header.frame_id = "odom";//this has been done in order to be able to visualize our PointCloud2 message on the RViz visualizer，这里时fix frame的名字
//   ros::Rate loop_rate(frequency);
//   while (ros::ok())
//   {
//     pcl_pub_source.publish(output_source);
//     pcl_pub_target.publish(output_target);
//     ros::spinOnce();
//     loop_rate.sleep();
//   }
//   return 0;
// }

#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>

std::string get_pcd_filename(int index)
{
  std::string base_path = "/home/xiangchenliu/SLAMDatasets/plane_seq2/";
  std::string filename = "plane" + std::to_string(index) + ".pcd";
  return base_path + filename;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "UandBdetect");
  ros::NodeHandle nh;
  ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl", 1);

  int num_files = 6; // Total number of PCD files to load and publish
  double frequency = 1.0;
  ros::Rate loop_rate(frequency);
  // double i_array[6] = {1.0,2.0,3.0,4.0,5.0,6.0};

  while (ros::ok())
  {
    for (int i = 1; i <= num_files; i++)
    {
      pcl::PointCloud<pcl::PointXYZ> cloud;
      sensor_msgs::PointCloud2 output;

      std::string file_path = get_pcd_filename(i);
      if (pcl::io::loadPCDFile(file_path, cloud) == -1)
      {
      ROS_ERROR("Couldn't read PCD file %s\n", file_path.c_str());
      continue;
      }

      pcl::toROSMsg(cloud, output);
      output.header.frame_id = "odom";
      // output.header.seq = i_array[i-1];
      // std::cout << output.header.seq << std::endl;
      output.header.stamp = ros::Time(i);
      std::cout << output.header.stamp << std::endl;
      pcl_pub.publish(output);
      ros::spinOnce();
      loop_rate.sleep();
    }
    sleep(10.0);
  }

return 0;
}