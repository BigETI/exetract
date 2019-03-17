#include "DataModule.h"

using namespace std;
using namespace Exetract;

DataModule *DataModule::currentDataModule(nullptr);

/// <summary>
/// Constructor
/// </summary>
/// <param name="moduleHandle">Module handle</param>
/// <param name="error">Error</param>
DataModule::DataModule(HMODULE moduleHandle, DWORD error) : moduleHandle(moduleHandle), error(error)
{
	// ...
}

/// <summary>
/// Enumerate resource name procedure
/// </summary>
/// <param name="hModule">Module handle</param>
/// <param name="lpType">Resource type</param>
/// <param name="lpName">Resource name</param>
/// <param name="lParam">Parameters</param>
/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
BOOL CALLBACK DataModule::EnumResNameProc(_In_opt_ HMODULE hModule, _In_ LPCWSTR lpType, _In_ LPWSTR lpName, _In_ LONG_PTR lParam)
{
	if (currentDataModule)
	{
		if (currentDataModule->resources)
		{
			HRSRC resource_handle(FindResourceW(hModule, lpName, lpType));
			if (resource_handle)
			{
				currentDataModule->resources->push_back(shared_ptr<Resource>(new Resource(hModule, resource_handle, lpType, lpName)));
			}
			else
			{
				currentDataModule->error = GetLastError();
			}
		}
	}
	return (currentDataModule ? TRUE : FALSE);
}

/// <summary>
/// Enumerate resource type procedure
/// </summary>
/// <param name="hModule">Module handle</param>
/// <param name="lpType">Resource type</param>
/// <param name="lParam">Parameters</param>
/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
BOOL CALLBACK DataModule::EnumResTypeProc(_In_opt_ HMODULE hModule, _In_ LPWSTR lpType, _In_ LONG_PTR lParam)
{
	string resource_type_name;
	EnumResourceNamesW(hModule, lpType, EnumResNameProc, lParam);
	return (currentDataModule ? TRUE : FALSE);
}

/// <summary>
/// Destructor
/// </summary>
DataModule::~DataModule()
{
	if (moduleHandle)
	{
		FreeLibrary(moduleHandle);
		moduleHandle = nullptr;
	}
}

/// <summary>
/// Load data module
/// </summary>
/// <param name="path">Module path</param>
/// <returns>Data module</returns>
shared_ptr<DataModule> DataModule::Load(const wstring & path)
{
	HMODULE module_handle(LoadLibraryExW(path.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE));
	DWORD error(GetLastError());
	return shared_ptr<DataModule>(new DataModule(module_handle, error));
}

/// <summary>
/// Is data module loaded
/// </summary>
/// <returns>"true" if loaded, otherwise "false"</returns>
bool DataModule::IsLoaded() const
{
	return (moduleHandle != nullptr);
}

/// <summary>
/// Get error
/// </summary>
/// <returns>Error</returns>
DWORD DataModule::GetError() const
{
	return error;
}

/// <summary>
/// Load resources
/// </summary>
/// <param name="result">Result</param>
/// <returns>Loaded resources</returns>
vector<shared_ptr<Resource>> & DataModule::LoadResources(vector<shared_ptr<Resource>> & result)
{
	result.clear();
	if (moduleHandle)
	{
		resources = &result;
		currentDataModule = this;
		EnumResourceTypesW(moduleHandle, EnumResTypeProc, 0UL);
		resources = nullptr;
		currentDataModule = nullptr;
	}
	return result;
}
