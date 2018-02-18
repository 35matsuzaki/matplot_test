#include "ros/ros.h"
#include "std_msgs/String.h"
#include <matplotlib-cpp/matplotlibcpp.h>
#include <sstream>

namespace plt = matplotlibcpp;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);

  int nt = 1000;
	std::vector<double> x(nt), y(nt);

	for(int i=0; i<nt; ++i) {
		x[i] = 2 * M_PI * i / nt;
		y[i] = sin(x[i]);
	}
  plt::scatter(x,y);
	plt::plot(x, y);
	plt::show();

  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
