#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <direct.h>
#include <cstdio>
#include <stdlib.h>
#include <regex>
#include <time.h>
#include <stdio.h>
#include "TextSupport.h"
#include "Rating.h"
#include "Genre.h"
#include "Tag.h"
#include "User.h"


class Genre;
class Tag;
class User;

class Movie
{
	std::string name;
	std::string description;
	int* genre;
	int* tag[3];
	Rating rating;
	int productionYear;
	

public:
	
	int * tempUserRating;
	std::vector<std::string>* ratedUsers;

	void setName(const std::string& name);
	inline std::string& getName() { return name; }
	void setDescription(const std::string& description) { this->description = description; }
	void setDescription(std::string& s1, std::string& s2, std::string& s3);
	std::string& getDescription() { return description; }
	void setTempGenre(int* genre) { this->genre = genre; }
	void setGenre(int& genre) { this->genre = &genre; }
	int& getGenre() { return *genre; }
	void setTempTag(int* tag, int& i) { this->tag[i] = tag; }
	void setTag(int& tag, int& i) { this->tag[i] = &tag; }
	int& getTag(int i) { return *tag[i]; }
	Rating& getRating() { return rating; }
	void setProductionYear(const int productionYear) { this->productionYear = productionYear; }
	void setProductionYear(const std::string productionYear);
	inline int& getProductionYear() { return productionYear; }

	Movie();
	~Movie();
	std::vector<Movie*> showInformation(std::string filmName, std::vector<Movie>& allMoviesData);
};

