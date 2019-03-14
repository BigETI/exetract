#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

/// <summary>
/// Get resource type name
/// </summary>
/// <param name="type">Resource type</param>
/// <param name="result">Result</param>
/// <returns>Resource type name</returns>
static string & GetResourceTypeName(LPCWSTR type, string & result)
{
	switch (reinterpret_cast<const long>(type))
	{
		case reinterpret_cast<long>(RT_ACCELERATOR):
			result = "ACCELERATOR";
			break;
		case reinterpret_cast<const long>(RT_ANICURSOR):
			result = "ANICURSOR";
			break;
		case reinterpret_cast<const long>(RT_ANIICON):
			result = "ANIICON";
			break;
		case reinterpret_cast<const long>(RT_BITMAP):
			result = "BITMAP";
			break;
		case reinterpret_cast<const long>(RT_CURSOR):
			result = "CURSOR";
			break;
		case reinterpret_cast<const long>(RT_DIALOG):
			result = "DIALOG";
			break;
		case reinterpret_cast<const long>(RT_DLGINCLUDE):
			result = "DLGINCLUDE";
			break;
		case reinterpret_cast<const long>(RT_FONT):
			result = "FONT";
			break;
		case reinterpret_cast<const long>(RT_FONTDIR):
			result = "FONTDIR";
			break;
		case reinterpret_cast<const long>(RT_GROUP_CURSOR):
			result = "GROUP_CURSOR";
			break;
		case reinterpret_cast<const long>(RT_GROUP_ICON):
			result = "GROUP_ICON";
			break;
		case reinterpret_cast<const long>(RT_HTML):
			result = "HTML";
			break;
		case reinterpret_cast<const long>(RT_ICON):
			result = "ICON";
			break;
		case reinterpret_cast<const long>(RT_MANIFEST):
			result = "MANIFEST";
			break;
		case reinterpret_cast<const long>(RT_MENU):
			result = "MENU";
			break;
		case reinterpret_cast<const long>(RT_MESSAGETABLE):
			result = "MESSAGETABLE";
			break;
		case reinterpret_cast<const long>(RT_PLUGPLAY):
			result = "PLUGPLAY";
			break;
		case reinterpret_cast<const long>(RT_RCDATA):
			result = "RCDATA";
			break;
		case reinterpret_cast<const long>(RT_STRING):
			result = "STRING";
			break;
		case reinterpret_cast<const long>(RT_VERSION):
			result = "VERSION";
			break;
		case reinterpret_cast<const long>(RT_VXD):
			result = "VXD";
			break;
		default:
			result = to_string(reinterpret_cast<const long>(type));
			break;
	}
	return result;
}

/// <summary>
/// Get last error as string
/// </summary>
/// <param name="error">Error</param>
/// <param name="result">Result</param>
/// <returns>Error as string</returns>
static wstring & GetLastErrorAsString(DWORD error, wstring & result)
{
	result.clear();
	if (error != 0)
	{
		LPWSTR buffer(nullptr);
		size_t size(FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&buffer), 0, nullptr));
		result = buffer;
		LocalFree(buffer);
	}
	return result;
}

/// <summary>
/// Print error
/// </summary>
/// <param name="error">Error</param>
static void PrintError(DWORD error)
{
	wstring e;
	wcout << L"Error (" << error << ") : \"" << GetLastErrorAsString(error, e) << L"\"" << endl;
}

/// <summary>
/// Enumerate resource name procedure
/// </summary>
/// <param name="hModule">Module handle</param>
/// <param name="lpType">Resource type</param>
/// <param name="lpName">Resource name</param>
/// <param name="lParam">Parameters</param>
/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
BOOL CALLBACK EnumResNameProc(_In_opt_ HMODULE hModule, _In_ LPCWSTR lpType, _In_ LPWSTR lpName, _In_ LONG_PTR lParam)
{
	HRSRC resource_handle(FindResourceW(hModule, lpName, lpType));
	cout << "\tResource name: \"" << reinterpret_cast<const long>(lpName) << "\"" << endl;
	if (resource_handle)
	{
		HGLOBAL resource_data_handle(LoadResource(hModule, resource_handle));
		if (resource_data_handle)
		{
			LPVOID resource_data(LockResource(resource_data_handle));
			if (resource_data)
			{
				string resource_type_name;
				DWORD resource_size(SizeofResource(hModule, resource_handle));
				string file_name(GetResourceTypeName(lpType, resource_type_name) + "_" + to_string(reinterpret_cast<const long>(lpName)) + ".bin");
				ofstream ofs(file_name, ios::binary);
				if (ofs.is_open())
				{
					cout << "\tWriting file \"" << file_name << "\"" << endl;
					ofs.write(reinterpret_cast<const char *>(resource_data), resource_size);
					ofs.close();
				}
				else
				{
					cout << "\tFailed to open file \"" << file_name << "\"" << endl;
				}
			}
			else
			{
				cout << "\t";
				PrintError(GetLastError());
			}
			UnlockResource(resource_data_handle);
		}
		else
		{
			cout << "\t";
			PrintError(GetLastError());
		}
	}
	else
	{
		cout << "\t";
		PrintError(GetLastError());
	}
	return TRUE;
}

/// <summary>
/// Enumerate resource type procedure
/// </summary>
/// <param name="hModule">Module handle</param>
/// <param name="lpType">Resource type</param>
/// <param name="lParam">Parameters</param>
/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
BOOL CALLBACK EnumResTypeProc(_In_opt_ HMODULE hModule, _In_ LPWSTR lpType, _In_ LONG_PTR lParam)
{
	string resource_type_name;
	cout << "Resource type: \"" << GetResourceTypeName(lpType, resource_type_name) << "\"" << endl;
	EnumResourceNamesW(hModule, lpType, EnumResNameProc, lParam);
	return TRUE;
}

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Arguments</param>
/// <returns>Exit code</returns>
int wmain(int argc, wchar_t *argv[])
{
	if (argc > 0)
	{
		HMODULE module_handle(LoadLibraryW(argv[1]));
		if (module_handle)
		{
			EnumResourceTypesW(module_handle, EnumResTypeProc, 0L);
			FreeLibrary(module_handle);
		}
		else
		{
			PrintError(GetLastError());
		}
	}
	return 0;
}
