#include "world.h"

#include <iostream>

World::World() : octree(1.0f)
		, cloud(new pcl::PointCloud<pcl::PointXYZ>) {
//	cloud->width = 0;
//	cloud->height = 1;
//	cloud->points.resize(0);
	octree.setInputCloud(cloud);
}

void World::addObject( Object * obj, glm::vec4 pos ) {
	cloud->push_back(*((pcl::PointXYZ *)(&(obj->position[0]))));
	obj->index = cloud->size()-1;
}

void World::update() {
	octree.deleteTree();
	octree.addPointsFromInputCloud();
}

void World::Wiggle() {
	for( int i=0; i<renObjs.size(); i++ ) {
		cloud->points[renObjs[i]->index].x += (float)rand()/RAND_MAX - .5;
		cloud->points[renObjs[i]->index].y += (float)rand()/RAND_MAX - .5;
		cloud->points[renObjs[i]->index].z += (float)rand()/RAND_MAX - .5;
	}
}



