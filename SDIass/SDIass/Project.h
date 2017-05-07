#pragma once
#include <string>
//#include "Material.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Project
{
public:
	//enum projectStatus { UNRELEASED, NOWPLAYING, RELEASED };
	Project();

	//Material *material;
	//vector<Material> material;
	int status;
	string title;
	string summary;
	vector<string> genre;
	string releaseDate;
	vector<string> locations;
	string language;
	int runtime;
	string keyword;
	double boxOffice;
};