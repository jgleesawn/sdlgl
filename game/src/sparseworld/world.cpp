#include "world.h"

#include <iostream>

World::World() : octree(1.0f)
		, cloud(new pcl::PointCloud<pcl::PointXYZ>) {
	focus = 0;	//camera
//	cloud->width = 0;
//	cloud->height = 1;
//	cloud->points.resize(0);
	octree.setInputCloud(cloud);
}

World::~World() {
	for( int i=0; i<objects.size(); i++ )
		delete objects[i];
}

int World::addObject( Object * obj, const glm::vec4 & pos ) {
	cloud->push_back(*((pcl::PointXYZ *)(&(obj->position[0]))));
	objects.push_back(obj);
	obj->index = cloud->size()-1;
	return obj->index;
}

int World::makeRenderable( int ind ) {
	renObjs.push_back( (Renderable *) objects[ind]);
	return renObjs.size()-1;
}

void World::update() {
	octree.deleteTree();
	octree.addPointsFromInputCloud();
}

void World::MoveObject( Object * obj, const glm::vec4 & offset ) {
	*(glm::vec4 *)&(cloud->points[obj->index]) += offset;
}

void World::MoveFocusForward() {
	*(glm::vec4 *)&(cloud->points[focus]) += objects[focus]->getForward();
}

void World::MoveFocusRight() {
	*(glm::vec4 *)&(cloud->points[focus]) += objects[focus]->getRight();
}

void World::MoveFocusLeft() {
	*(glm::vec4 *)&(cloud->points[focus]) -= objects[focus]->getRight();
}

void World::MoveFocusBack() {
	*(glm::vec4 *)&(cloud->points[focus]) -= objects[focus]->getForward();
}

void World::RotFocusRight() {
	objects[focus]->rotY(-.1);
}

void World::RotFocusLeft() {
	objects[focus]->rotY(.1);
}

void World::RotFocusUp() {
	objects[focus]->rotX(.1);
}

void World::RotFocusDown() {
	objects[focus]->rotX(-.1);
}

void World::focusCamera() {
	cloud->points[camera] = cloud->points[focus];
	focus = camera;
	printv(*(glm::vec4 *)&(cloud->points[focus]));
}

void World::focusNext() {
	focus++;
	if( focus > objects.size() )
		focus = 0;
	printv(*(glm::vec4 *)&(cloud->points[focus]));
}

void World::Wiggle() {
	for( int i=0; i<renObjs.size(); i++ ) {
		MoveObject( renObjs[i], glm::vec4( (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, (float)rand()/RAND_MAX - .5, 0.0f ) );
	}
}



