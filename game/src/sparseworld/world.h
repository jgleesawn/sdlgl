#ifndef WORLD_H
#define WORLD_H

//Hack of a fix
#undef Success
#include <pcl/point_cloud.h>
#include <pcl/octree/octree.h>

#include <iostream>

#include "object/object.h"
#include "object/renderable.h"

class World {
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree;

	std::vector<Renderable *> renObjs;

public:
	World();
	void addObject( Object *, glm::vec4 pos );
	void update();

	void Wiggle();	//remove
};


#endif
