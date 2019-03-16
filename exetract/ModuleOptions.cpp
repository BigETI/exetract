#include "ModuleOptions.h"

using namespace std;
using namespace std::filesystem;
using namespace Exetract;

ModuleOptions::ModuleOptions()
{
	// ...
}

ModuleOptions::ModuleOptions(const ModuleOptions & moduleOptions)
{
	typeFilter = moduleOptions.typeFilter;
	nameFilter = moduleOptions.nameFilter;
	outputPath = moduleOptions.outputPath;
}

ModuleOptions::~ModuleOptions()
{
	// ...
}

void ModuleOptions::AddTypeFilter(const wstring & resourceType)
{
	typeFilter.insert(resourceType);
}

void ModuleOptions::AddNameFilter(const wstring & resourceName)
{
	nameFilter.insert(resourceName);
}

bool ModuleOptions::SetOutputPath(const wstring & outputPath)
{
	bool ret(false);
	if (filesystem::exists(outputPath))
	{
		this->outputPath = outputPath;
		ret = true;
	}
	return ret;
}

void ModuleOptions::ClearTypeFilter()
{
	typeFilter.clear();
}

void ModuleOptions::ClearNameFilter()
{
	nameFilter.clear();
}

void ModuleOptions::ClearOutputPath()
{
	outputPath.clear();
}

void ModuleOptions::Clear()
{
	typeFilter.clear();
	nameFilter.clear();
	outputPath.clear();
}

const set<wstring> & ModuleOptions::GetTypeFilter() const
{
	return typeFilter;
}

const set<wstring> & ModuleOptions::GetNameFilter() const
{
	return nameFilter;
}

path ModuleOptions::GetOutputPath(path & result) const
{
	return (result = (outputPath.empty() ? filesystem::current_path() : filesystem::canonical(outputPath)));
}

ModuleOptions & ModuleOptions::operator = (const ModuleOptions & moduleOptions)
{
	typeFilter = moduleOptions.typeFilter;
	nameFilter = moduleOptions.nameFilter;
	outputPath = moduleOptions.outputPath;
	return (*this);
}
