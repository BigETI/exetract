#include "ModuleOptions.h"

using namespace std;
using namespace std::filesystem;
using namespace Exetract;

/// <summary>
/// Default constructor
/// </summary>
ModuleOptions::ModuleOptions()
{
	// ...
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="moduleOptions">Module options</param>
ModuleOptions::ModuleOptions(const ModuleOptions & moduleOptions)
{
	typeFilter = moduleOptions.typeFilter;
	nameFilter = moduleOptions.nameFilter;
	outputPath = moduleOptions.outputPath;
}

/// <summary>
/// Destructor
/// </summary>
ModuleOptions::~ModuleOptions()
{
	// ...
}

/// <summary>
/// Add resource type filter
/// </summary>
/// <param name="resourceType">Resource type filter</param>
void ModuleOptions::AddTypeFilter(const wstring & resourceType)
{
	typeFilter.insert(resourceType);
}

/// <summary>
/// Add resource name filter
/// </summary>
/// <param name="resourceName">Resource name</param>
void ModuleOptions::AddNameFilter(const wstring & resourceName)
{
	nameFilter.insert(resourceName);
}

/// <summary>
/// Set output path
/// </summary>
/// <param name="outputPath">Output path</param>
/// <returns>"true" if output path exists, otherwise "false"</returns>
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

/// <summary>
/// Clear resource type filter
/// </summary>
void ModuleOptions::ClearTypeFilter()
{
	typeFilter.clear();
}

/// <summary>
/// Clear resource name filter
/// </summary>
void ModuleOptions::ClearNameFilter()
{
	nameFilter.clear();
}

/// <summary>
/// Clear output path
/// </summary>
void ModuleOptions::ClearOutputPath()
{
	outputPath.clear();
}

/// <summary>
/// Clear module options
/// </summary>
void ModuleOptions::Clear()
{
	typeFilter.clear();
	nameFilter.clear();
	outputPath.clear();
}

/// <summary>
/// Get resource type filter
/// </summary>
/// <returns>Resource type filter</returns>
const set<wstring> & ModuleOptions::GetTypeFilter() const
{
	return typeFilter;
}

/// <summary>
/// Get resource name filter
/// </summary>
/// <returns>Resource name filter</returns>
const set<wstring> & ModuleOptions::GetNameFilter() const
{
	return nameFilter;
}

/// <summary>
/// Get output path
/// </summary>
/// <param name="result">Result</param>
/// <returns>Output path</returns>
path ModuleOptions::GetOutputPath(path & result) const
{
	return (result = (outputPath.empty() ? filesystem::current_path() : filesystem::canonical(outputPath)));
}

/// <summary>
/// Assign operator
/// </summary>
/// <param name="moduleOptions">Module options</param>
/// <returns>This object</returns>
ModuleOptions & ModuleOptions::operator = (const ModuleOptions & moduleOptions)
{
	typeFilter = moduleOptions.typeFilter;
	nameFilter = moduleOptions.nameFilter;
	outputPath = moduleOptions.outputPath;
	return (*this);
}
