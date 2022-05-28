#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Point.h>
#include "pointcloud2translate.h"
#include <vector>
#include <iostream>
#include <QByteArray>
#include <cloudpointudp.h>

using namespace std;
static sensor_msgs::PointCloud2 currentCloud;
bool isNewData;

void pointCloud2Callback(const sensor_msgs::PointCloud2 &msg)
{
  currentCloud = msg;
  isNewData = true;
}

void getImageDepth(sensor_msgs::PointCloud2 &pc){

}

void pixelTo3DPoint(const sensor_msgs::PointCloud2& pCloud, const int u, const int v, vector<geometry_msgs::Point> &p)
{
 //Вычисляем начало позиции элемента
 geometry_msgs::Point point;
 int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;
 // Вычисляем сдвиг каждого из полей
 int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X имеет сдвиг 0
 int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y имеет сдвиг 4
 int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z имеет сдвиг 8
 float X = 0.0;
 float Y = 0.0;
 float Z = 0.0;
 memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
 memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
 memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));
 point.x = X;
 point.y = Y;
 point.z = Z;
 p.push_back(point);

}
void pixelToByteArray(const sensor_msgs::PointCloud2& pCloud, const int u, const int v, QByteArray& arr, vector<QByteArray>& vectorArr){
  int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;
  // Вычисляем сдвиг каждого из полей
  int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X имеет сдвиг 0
  int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y имеет сдвиг 4
  int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z имеет сдвиг 8
  float X = 0.0;
  float Y = 0.0;
  float Z = 0.0;
  memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
  memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
  memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));
  char x[8];
  char y[8];
  char z[8];
  int ret;
  if(arr.size()>60000){
    char num[3];
    ret = snprintf(num,sizeof(num),"%d",vectorArr.size());
    arr.push_front(num);
    arr.push_front("num");
    vectorArr.push_back(arr);
    arr.clear();
  }
  ret = snprintf(x, sizeof(x), "%f", X);
  if (ret >= sizeof(x)) {
      // Result was truncated - resize the buffer and retry.
    arr.append("(");
    arr.append("x");
    arr.append(x);
  }

  ret = snprintf(y, sizeof(y), "%f", Y);
  if (ret >= sizeof(y)) {
      // Result was truncated - resize the buffer and retry.
    arr.append("y");
    arr.append(y);
  }

  ret = snprintf(z, sizeof(z), "%f", Z);
  if (ret >= sizeof(z)) {
      // Result was truncated - resize the buffer and retry.
    arr.append("z");
    arr.append(z);
    arr.append(")");
  }
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "cloudReader_node");
  ros::NodeHandle nh;
  ros::Subscriber cloud_sub = nh.subscribe("/camera/depth/points", 10, pointCloud2Callback);
  isNewData = false;
  ros::Rate r(10);
  int count = 0;
  CloudPointUDP cpUDP;
  while(ros::ok()) {
    if(isNewData) {
      cout<< count++<<endl;
      QByteArray qbd;
      vector<QByteArray> vectorByteArray;
      //qbd.append("new data");
      for(int i = 0; i < currentCloud.width; i++) {
        for(int j = 0; j < currentCloud.height; j++) {
          pixelToByteArray(currentCloud,i,j,qbd,vectorByteArray);
        }
      }
      cout<<"size"<<sizeof(qbd)*qbd.size()<<endl;
    cpUDP.setData(vectorByteArray);
    cout<<"qByteData "<<qbd.size()<<endl;
    isNewData = false;
    //pC2T.~PointCloud2Translate();
    }
    ros::spinOnce();
  }
}
