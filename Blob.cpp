#include "Blob.h"



Blob::Blob()
{
}

void Blob::getBlobSpecs(vector <Point> hull)
{
	bound = boundingRect(hull);

	boundWidth = bound.width;
}
