#pragma once

struct QuadNode
{
	QuadNode* NW;
	QuadNode* NE;
	QuadNode* SW;
	QuadNode* SE;
};

class Quadtree
{
public:
	Quadtree();

	QuadNode* NW;
	QuadNode* NE;
	QuadNode* SW;
	QuadNode* SE;

	void insert(QuadNode* node);
};

