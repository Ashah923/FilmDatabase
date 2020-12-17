#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "MovieDataBase.h"
#include "Movie.h"
#include "User.h"

class SaveData
{
public:
	void saveDataMovie(MovieDataBase& movieDataBase);
	void saveRatedMovies(User& user);
	void saveRatedUsers(MovieDataBase& movieDataBase);
};

