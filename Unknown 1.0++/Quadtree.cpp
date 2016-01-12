#include "stdafx.h"
#include "Quadtree.h"


Quadtree::Quadtree()
{
}

void Quadtree::insert(QuadNode* node)
{
	if (!NW)
	{
		NW = node;
	}
	else
	{
		if (!NE)
		{
			NE = node;
		}
		else
		{
			if (!SW)
			{
				SW = node;
			}
			else
			{
				if (!SE)
				{
					SE = node;
				}
				else
				{
					// shift all Nodes back one

					QuadNode* shiftNode = new QuadNode;

					shiftNode->NE = NE;
					shiftNode->NW = NW;
					shiftNode->SE = SE;
					shiftNode->SW = SW;

					NW = nullptr;
					SE = nullptr;
					SW = nullptr;

					NE = shiftNode;
				}
			}
		}
	}
}
