#include "Rating.h"

Rating::~Rating() {}

void Rating::operator() ()
{
	int numberOfRating = 0;
	avgRating = 0;

	for (int i = 0; i < 5; i++)
	{
		numberOfRating += numbersOfRatings[i];
		avgRating += numbersOfRatings[i] * (i + 1);
	}
	if (avgRating == 0)
	{
		return;
	}
	avgRating = avgRating / numberOfRating;
	avgRating *= 100;
	avgRating /= 100;

	return;
}
