#ifndef __EXETRACT_RESOURCE_H__
#	define __EXETRACT_RESOURCE_H__
#	define WIN32_LEAN_AND_MEAN

#	include <Windows.h>
#	include <string>
#	include <fstream>

/// <summary>
/// Exetract namespace
/// </summary>
namespace Exetract
{
	/// <summary>
	/// Resource class
	/// </summary>
	class Resource
	{
	private:
		/// <summary>
		/// Module handle
		/// </summary>
		HMODULE moduleHandle;

		/// <summary>
		/// Resource handle
		/// </summary>
		HRSRC resourceHandle;

		/// <summary>
		/// Resource type
		/// </summary>
		LPCWSTR resourceType;

		/// <summary>
		/// Resource name
		/// </summary>
		LPWSTR resourceName;

		/// <summary>
		/// Error
		/// </summary>
		DWORD error;

		Resource();
		Resource(const Resource &);
		Resource & operator = (const Resource &);
	public:

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="moduleHandle">Module handle</param>
		/// <param name="resourceHandle">Resource handle</param>
		/// <param name="resourceType">Resource type</param>
		/// <param name="resourceName">Resource name</param>
		Resource(HMODULE moduleHandle, HRSRC resourceHandle, LPCWSTR resourceType, LPWSTR resourceName);

		/// <summary>
		/// Destructor
		/// </summary>
		~Resource();

		/// <summary>
		/// Get resource type
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Resource type</returns>
		std::wstring & GetType(std::wstring & result) const;

		/// <summary>
		/// Get resource type name
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Resource type name</returns>
		std::wstring & GetTypeName(std::wstring & result) const;

		/// <summary>
		/// Get resource name
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Resource name</returns>
		std::wstring & GetName(std::wstring & result) const;

		/// <summary>
		/// Write to file stream
		/// </summary>
		/// <param name="outputFileStream">Output file stream</param>
		void WriteToFileStream(std::ofstream & outputFileStream);

		/// <summary>
		/// Get error
		/// </summary>
		/// <returns>Error</returns>
		DWORD GetError() const;
	};
}

#endif
