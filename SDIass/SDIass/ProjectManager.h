#pragma once
#include "Project.h"
#include "Material.h"
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
	void postProject();
	void updateProject();
	void deleteProject();
	void searchProject();
	void addMaterial();
	void loadMaterial();
	void postMaterial();
	void displayMaterial();
	void deleteMaterial();
	void searchMaterial(string title);
private:
	vector<Project> movies;
	vector<Material> materials;
	ofstream file;
	ifstream infile;
};