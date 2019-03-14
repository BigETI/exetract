#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

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
	wcout << L"Error (" << error << ") : \"" << GetLastErrorAsString(error, e) << "\"" << endl;
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
	cout << "Type: \"" << lpType << "\" | Name: \"" << lpName << "\"" << endl;
	if (resource_handle)
	{
		HGLOBAL resource_data_handle(LoadResource(hModule, resource_handle));
		if (resource_data_handle)
		{
			LPVOID resource_data(GlobalLock(resource_data_handle));
			if (resource_data)
			{
				DWORD resource_size(SizeofResource(hModule, resource_handle));
				static int index(0);
				string file_name(to_string(index) + ".bin");
				ofstream ofs(file_name, ios::binary);
				if (ofs.is_open())
				{
					ofs.write(reinterpret_cast<char *>(resource_data), resource_size);
					ofs.close();
				}
				else
				{
					cout << "Failed to open file \"" << file_name << "\"" << endl;
				}
				++index;
			}
			else
			{
				PrintError(GetLastError());
			}
			GlobalUnlock(resource_data_handle);
		}
		else
		{
			PrintError(GetLastError());
		}
	}
	else
	{
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
	cout << "Type: \"" << lpType << "\"" << endl;
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
