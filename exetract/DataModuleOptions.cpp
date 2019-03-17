#include "DataModuleOptions.h"

using namespace std;
using namespace std::filesystem;
using namespace Exetract;

/// <summary>
/// Default constructor
/// </summary>
DataModuleOptions::DataModuleOptions()
{
	// ...
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="dataModuleOptions">Data module options</param>
DataModuleOptions::DataModuleOptions(const DataModuleOptions & dataModuleOptions) : typeFilter(dataModuleOptions.typeFilter), nameFilter(dataModuleOptions.nameFilter), outputPath(dataModuleOptions.outputPath)
{
	// ...
}

/// <summary>
/// Destructor
/// </summary>
DataModuleOptions::~DataModuleOptions()
{
	// ...
}

/// <summary>
/// Add resource type filter
/// </summary>
/// <param name="resourceType">Resource type filter</param>
void DataModuleOptions::AddTypeFilter(const wstring & resourceType)
{
	typeFilter.insert(resourceType);
}

/// <summary>
/// Add resource name filter
/// </summary>
/// <param name="resourceName">Resource name</param>
void DataModuleOptions::AddNameFilter(const wstring & resourceName)
{
	nameFilter.insert(resourceName);
}

/// <summary>
/// Set output path
/// </summary>
/// <param name="outputPath">Output path</param>
/// <returns>"true" if output path exists, otherwise "false"</returns>
bool DataModuleOptions::SetOutputPath(const wstring & outputPath)
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
void DataModuleOptions::ClearTypeFilter()
{
	typeFilter.clear();
}

/// <summary>
/// Clear resource name filter
/// </summary>
void DataModuleOptions::ClearNameFilter()
{
	nameFilter.clear();
}

/// <summary>
/// Clear output path
/// </summary>
void DataModuleOptions::ClearOutputPath()
{
	outputPath.clear();
}

/// <summary>
/// Clear data module options
/// </summary>
void DataModuleOptions::Clear()
{
	typeFilter.clear();
	nameFilter.clear();
	outputPath.clear();
}

/// <summary>
/// Get resource type filter
/// </summary>
/// <returns>Resource type filter</returns>
const set<wstring> & DataModuleOptions::GetTypeFilter() const
{
	return typeFilter;
}

/// <summary>
/// Get resource name filter
/// </summary>
/// <returns>Resource name filter</returns>
const set<wstring> & DataModuleOptions::GetNameFilter() const
{
	return nameFilter;
}

/// <summary>
/// Get output path
/// </summary>
/// <param name="result">Result</param>
/// <returns>Output path</returns>
path DataModuleOptions::GetOutputPath(path & result) const
{
	return (result = (outputPath.empty() ? filesystem::current_path() : filesystem::canonical(outputPath)));
}

/// <summary>
/// Assign operator
/// </summary>
/// <param name="dataModuleOptions">Module options</param>
/// <returns>This object</returns>
DataModuleOptions & DataModuleOptions::operator = (const DataModuleOptions & dataModuleOptions)
{
	typeFilter = dataModuleOptions.typeFilter;
	nameFilter = dataModuleOptions.nameFilter;
	outputPath = dataModuleOptions.outputPath;
	return (*this);
}
