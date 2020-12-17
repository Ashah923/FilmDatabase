#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>

class Rating
{
	double avgRating;
	
public:

	int numbersOfRatings[5];

	void setAvgRating(const double& rat) { this->avgRating = rat; }
	double& getAvgRating() { return avgRating; }

	void operator()();

	Rating() {};
	~Rating();

};

