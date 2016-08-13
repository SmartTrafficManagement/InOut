#include "Blob.h"



Blob::Blob()
{
}

void Blob::getBlobSpecs(vector <Point> hull)
{
	contour = hull;

	bound = boundingRect(hull);

	boundWidth = bound.width;
	boundHeight = bound.height;

	DiagonalSize = sqrt(pow(bound.width, 2) + pow(bound.height, 2));

	AspectRatio = (float)bound.width / (float)bound.height;
}
