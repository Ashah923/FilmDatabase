#include "Movie.h"


Movie::Movie()
{
	tempUserRating = nullptr;
	for (int i = 0; i < 3; i++)
		tag[i] = nullptr;
}
Movie::~Movie(){}

void Movie::setName(const std::string& name)
{
	const std::regex name_regex("[A-Z]{1}.{0,}");
	if (std::regex_match(name, name_regex))
	{
		this->name = name;
		return;
	}
	else
		throw "Bad title";
}

void Movie::setProductionYear(const std::string productionYear)
{
	time_t t;
	t = time(nullptr);
	std::string str = ctime(&t);
	int currentYear = stoi(str.erase(0, str.size() - 5));
	int pYear = stoi(productionYear);

	const std::regex year_regex1("[2-9]{1}[0-9]{3}");
	const std::regex year_regex2("[1]{1}[9]{1}[0-9]{2}");
	const std::regex year_regex3("[1]{1}[8]{1}[9]{1}[6-9]");

	if ((std::regex_match(productionYear, year_regex1) || std::regex_match(productionYear, year_regex2) || std::regex_match(productionYear, year_regex3)) && pYear < (currentYear + 5))
		this->productionYear = pYear;
	else throw "bad production year";
}

void Movie::setDescription(std::string& s1, std::string& s2, std::string& s3)
{
	const std::regex sentence_regex("[\\\. | \\? | \\!]");
	if (s1 != "" && !std::regex_match(s1, sentence_regex))
		s1 += ".";
	if (s2 != "" && !std::regex_match(s2, sentence_regex))
		s2 += ".";
	if (s3 != "" && !std::regex_match(s1, sentence_regex))
		s3 += ".";
	this->description = s1 + " " + s2 + " " + s3;
}


std::vector<Movie*> Movie::showInformation(std::string filmName, std::vector<Movie>& allMoviesData)
{
	std::vector<Movie>::iterator it;
	std::vector<Movie*> movies;

	for (it = allMoviesData.begin(); it != allMoviesData.end(); it++)
	{
		if (filmName == (*it).getName())
			movies.push_back(&(*it));
	}

	if (movies.empty())
		throw "the movie is not in the database";
	else return movies;
}


