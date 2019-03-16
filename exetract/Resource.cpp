#include "Resource.h"

using namespace std;
using namespace Exetract;

/// <summary>
/// Constructor
/// </summary>
/// <param name="moduleHandle">Module handle</param>
/// <param name="resourceHandle">Resource handle</param>
/// <param name="resourceType">Resource type</param>
/// <param name="resourceName">Resource name</param>
Resource::Resource(HMODULE moduleHandle, HRSRC resourceHandle, LPCWSTR resourceType, LPWSTR resourceName) : moduleHandle(moduleHandle), resourceHandle(resourceHandle), resourceType(resourceType), resourceName(resourceName)
{
	// ...
}

/// <summary>
/// Destructor
/// </summary>
Resource::~Resource()
{
	if (resourceHandle)
	{
		FreeResource(resourceHandle);
		resourceHandle = nullptr;
	}
}

/// <summary>
/// Get resource type
/// </summary>
/// <param name="result">Result</param>
/// <returns>Resource type</returns>
wstring & Resource::GetType(wstring & result) const
{
	return (result = to_wstring(reinterpret_cast<const unsigned int>(resourceType)));
}

/// <summary>
/// Get resource type name
/// </summary>
/// <param name="result">Result</param>
/// <returns>Resource type name</returns>
wstring & Resource::GetTypeName(wstring & result) const
{
	switch (reinterpret_cast<const unsigned int>(resourceType))
	{
		case reinterpret_cast<const unsigned int>(RT_ACCELERATOR):
			result = L"ACCELERATOR";
			break;
		case reinterpret_cast<const unsigned int>(RT_ANICURSOR):
			result = L"ANICURSOR";
			break;
		case reinterpret_cast<const unsigned int>(RT_ANIICON):
			result = L"ANIICON";
			break;
		case reinterpret_cast<const unsigned int>(RT_BITMAP):
			result = L"BITMAP";
			break;
		case reinterpret_cast<const unsigned int>(RT_CURSOR):
			result = L"CURSOR";
			break;
		case reinterpret_cast<const unsigned int>(RT_DIALOG):
			result = L"DIALOG";
			break;
		case reinterpret_cast<const unsigned int>(RT_DLGINCLUDE):
			result = L"DLGINCLUDE";
			break;
		case reinterpret_cast<const unsigned int>(RT_FONT):
			result = L"FONT";
			break;
		case reinterpret_cast<const unsigned int>(RT_FONTDIR):
			result = L"FONTDIR";
			break;
		case reinterpret_cast<const unsigned int>(RT_GROUP_CURSOR):
			result = L"GROUP_CURSOR";
			break;
		case reinterpret_cast<const unsigned int>(RT_GROUP_ICON):
			result = L"GROUP_ICON";
			break;
		case reinterpret_cast<const unsigned int>(RT_HTML):
			result = L"HTML";
			break;
		case reinterpret_cast<const unsigned int>(RT_ICON):
			result = L"ICON";
			break;
		case reinterpret_cast<const unsigned int>(RT_MANIFEST):
			result = L"MANIFEST";
			break;
		case reinterpret_cast<const unsigned int>(RT_MENU):
			result = L"MENU";
			break;
		case reinterpret_cast<const unsigned int>(RT_MESSAGETABLE):
			result = L"MESSAGETABLE";
			break;
		case reinterpret_cast<const unsigned int>(RT_PLUGPLAY):
			result = L"PLUGPLAY";
			break;
		case reinterpret_cast<const unsigned int>(RT_RCDATA):
			result = L"RCDATA";
			break;
		case reinterpret_cast<const unsigned int>(RT_STRING):
			result = L"STRING";
			break;
		case reinterpret_cast<const unsigned int>(RT_VERSION):
			result = L"VERSION";
			break;
		case reinterpret_cast<const unsigned int>(RT_VXD):
			result = L"VXD";
			break;
		default:
			result = to_wstring(reinterpret_cast<const unsigned int>(resourceType));
			break;
	}
	return result;
}

/// <summary>
/// Get resource name
/// </summary>
/// <param name="result">Result</param>
/// <returns>Resource name</returns>
wstring & Resource::GetName(wstring & result) const
{
	return (result = to_wstring(reinterpret_cast<const unsigned int>(resourceName)));
}

/// <summary>
/// Write to file stream
/// </summary>
/// <param name="outputFileStream">Output file stream</param>
void Resource::WriteToFileStream(ofstream & outputFileStream)
{
	if (outputFileStream.is_open())
	{
		HGLOBAL resource_data_handle(LoadResource(moduleHandle, resourceHandle));
		if (resource_data_handle)
		{
			LPVOID resource_data(LockResource(resource_data_handle));
			if (resource_data)
			{
				string resource_type_name;
				DWORD resource_size(SizeofResource(moduleHandle, resourceHandle));
				outputFileStream.write(reinterpret_cast<const char *>(resource_data), resource_size);
			}
			else
			{
				error = GetLastError();
			}
			UnlockResource(resource_data_handle);
		}
		else
		{
			error = GetLastError();
		}
	}
}

/// <summary>
/// Get error
/// </summary>
/// <returns>Error</returns>
DWORD Resource::GetError() const
{
	return error;
}
