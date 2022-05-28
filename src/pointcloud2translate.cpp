#include "pointcloud2translate.h"
#pragma once
PointCloud2Translate::PointCloud2Translate()
{

}

PointCloud2Translate::PointCloud2Translate(sensor_msgs::PointCloud2* cloud){
  this->data = cloud->data.data();
  std::cout<<"debug"<<"\n";
  this->hieght = cloud->height;
  this->offsetX = cloud->fields[0].offset;
  this->offsetY = cloud->fields[1].offset;
  this->offsetZ = cloud->fields[2].offset;
  this->point_step = cloud->point_step;
  this->row_step = cloud->row_step;
  this->sizeData = cloud->data.size();
  this->width = cloud->width;
  this->stringData = "";
}

PointCloud2Translate::~PointCloud2Translate()
{
  delete[] data;
}

std::string PointCloud2Translate::getSeriazableString(){
  this->stringData+="oX"+this->offsetX;
  this->stringData+="oY"+this->offsetY;
  this->stringData+="oZ"+this->offsetZ;
  this->stringData+="h"+this->hieght;
  this->stringData+="w"+this->width;
  this->stringData+="ps"+this->point_step;
  this->stringData+="rs"+this->row_step;
  this->stringData+="sD"+this->sizeData;
  this->stringData+="d";
//  for(int i =0;i<sizeData;i++){
//    this->stringData+=this->data[i]+",";
//  }

}
