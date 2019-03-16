#ifndef __EXETRACT_RESOURCE_H__
#	define __EXETRACT_RESOURCE_H__
#	define WIN32_LEAN_AND_MEAN

#	include <Windows.h>
#	include <string>
#	include <fstream>

namespace Exetract
{
	class Resource
	{
	private:
		HMODULE moduleHandle;
		HRSRC resourceHandle;
		LPCWSTR resourceType;
		LPWSTR resourceName;
		DWORD error;

		Resource();
		Resource(const Resource &);
		Resource & operator = (const Resource &);
	public:
		Resource(HMODULE moduleHandle, HRSRC resourceHandle, LPCWSTR resourceType, LPWSTR resourceName);
		~Resource();

		std::wstring & GetType(std::wstring & result) const;
		std::wstring & GetTypeName(std::wstring & result) const;
		std::wstring & GetName(std::wstring & result) const;
		void WriteToFileStream(std::ofstream & outputFileStream);
		DWORD GetError() const;
	};
}

#endif
