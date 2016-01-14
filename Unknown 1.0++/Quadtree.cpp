#include "stdafx.h"
#include "Quadtree.h"

void Unknown::Quad::renderContents()
{
	for (auto a : entitys)
	{
		a->render();
	}
}


Unknown::Quadtree::Quadtree()
{

}
