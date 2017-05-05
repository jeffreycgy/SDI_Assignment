#pragma once
#include <string>
//#include "Material.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Project
{
public:
	enum projectStatus { UNRELEASED, NOWPLAYING, RELEASED };
	Project();
	//Project();
	//Project(projectStatus);  
	//void showMenu();
	//void loadProject();	//on cold start, load project details from file
	//void addProject();	//3 conditions, check doc for details
	//void updateProject();
	//void deleteProject();
	//void displayProject();
	//void maintenanceMode();
	//void addMaterial();


	//Material *material;
	projectStatus status;
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