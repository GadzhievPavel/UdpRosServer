#ifndef POINTCLOUD2TRANSLATE_H
#define POINTCLOUD2TRANSLATE_H
#include <sensor_msgs/PointCloud2.h>
#include <string>
#pragma once
class PointCloud2Translate
{
private:
  int offsetX, offsetY, offsetZ;
  int width, hieght;
  int row_step, point_step;
  int sizeData;
  uint8_t* data;
  std::string stringData;
public:
  PointCloud2Translate();
  PointCloud2Translate(sensor_msgs::PointCloud2* cloud);
  std::string getSeriazableString();
  ~PointCloud2Translate();
};

#endif // POINTCLOUD2TRANSLATE_H
