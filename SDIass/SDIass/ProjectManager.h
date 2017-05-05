#pragma once
#include "Project.h"
#include <vector>
using namespace std;

class ProjectManager 
{
public:
	ProjectManager();
	void showMenu();
	void addProject();
	void displayProject();
	void loadProject();
private:
	vector<Project> movies;
	//vector<Project> readMovies;
	//Project p;
	ofstream file;
	ifstream infile;
};