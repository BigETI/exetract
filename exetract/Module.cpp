#include "Module.h"

using namespace std;
using namespace Exetract;

/// <summary>
/// Constructor
/// </summary>
/// <param name="moduleHandle">Module handle</param>
/// <param name="error">Error</param>
Module::Module(HMODULE moduleHandle, DWORD error) : moduleHandle(moduleHandle), error(error)
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
BOOL CALLBACK Module::EnumResNameProc(_In_opt_ HMODULE hModule, _In_ LPCWSTR lpType, _In_ LPWSTR lpName, _In_ LONG_PTR lParam)
{
	Module *module(reinterpret_cast<Module *>(lParam));
	if (module)
	{
		if (module->resources)
		{
			HRSRC resource_handle(FindResourceW(hModule, lpName, lpType));
			if (resource_handle)
			{
				module->resources->push_back(shared_ptr<Resource>(new Resource(hModule, resource_handle, lpType, lpName)));
			}
			else
			{
				module->error = GetLastError();
			}
		}
	}
	return (module ? TRUE : FALSE);
}

/// <summary>
/// Enumerate resource type procedure
/// </summary>
/// <param name="hModule">Module handle</param>
/// <param name="lpType">Resource type</param>
/// <param name="lParam">Parameters</param>
/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
BOOL CALLBACK Module::EnumResTypeProc(_In_opt_ HMODULE hModule, _In_ LPWSTR lpType, _In_ LONG_PTR lParam)
{
	string resource_type_name;
	EnumResourceNamesW(hModule, lpType, EnumResNameProc, lParam);
	return (lParam ? TRUE : FALSE);
}

/// <summary>
/// Destructor
/// </summary>
Module::~Module()
{
	if (moduleHandle)
	{
		FreeLibrary(moduleHandle);
		moduleHandle = nullptr;
	}
}

/// <summary>
/// Load module
/// </summary>
/// <param name="path">Module path</param>
/// <returns>Module</returns>
shared_ptr<Module> Module::Load(const wstring & path)
{
	HMODULE module_handle(LoadLibraryW(path.c_str()));
	DWORD error(GetLastError());
	return shared_ptr<Module>(new Module(module_handle, error));
}

/// <summary>
/// Is module loaded
/// </summary>
/// <returns>"true" if loaded, otherwise "false"</returns>
bool Module::IsLoaded() const
{
	return (moduleHandle != nullptr);
}

/// <summary>
/// Get error
/// </summary>
/// <returns>Error</returns>
DWORD Module::GetError() const
{
	return error;
}

/// <summary>
/// Load resources
/// </summary>
/// <param name="result">Result</param>
/// <returns>Loaded resources</returns>
vector<shared_ptr<Resource>> & Module::LoadResources(vector<shared_ptr<Resource>> & result)
{
	result.clear();
	if (moduleHandle)
	{
		resources = &result;
		EnumResourceTypesW(moduleHandle, EnumResTypeProc, reinterpret_cast<int>(this));
	}
	return result;
}
