#ifndef __EXETRACT_MODULE_H__
#	define __EXETRACT_MODULE_H__

#	include <vector>
#	include <memory>
#	include "Resource.h"

/// <summary>
/// Exetract namespace
/// </summary>
namespace Exetract
{
	/// <summary>
	/// Module class
	/// </summary>
	class Module
	{
	private:
		/// <summary>
		/// Module handle
		/// </summary>
		HMODULE moduleHandle;

		/// <summary>
		/// Error
		/// </summary>
		DWORD error;

		/// <summary>
		/// Resources
		/// </summary>
		std::vector<std::shared_ptr<Resource>> *resources;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="moduleHandle">Module handle</param>
		/// <param name="error">Error</param>
		Module(HMODULE moduleHandle, DWORD error);

		/// <summary>
		/// Enumerate resource name procedure
		/// </summary>
		/// <param name="hModule">Module handle</param>
		/// <param name="lpType">Resource type</param>
		/// <param name="lpName">Resource name</param>
		/// <param name="lParam">Parameters</param>
		/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
		static BOOL CALLBACK EnumResNameProc(_In_opt_ HMODULE hModule, _In_ LPCWSTR lpType, _In_ LPWSTR lpName, _In_ LONG_PTR lParam);

		/// <summary>
		/// Enumerate resource type procedure
		/// </summary>
		/// <param name="hModule">Module handle</param>
		/// <param name="lpType">Resource type</param>
		/// <param name="lParam">Parameters</param>
		/// <returns>"TRUE" to keep enumerating, otherwise "FALSE"</returns>
		static BOOL CALLBACK EnumResTypeProc(_In_opt_ HMODULE hModule, _In_ LPWSTR lpType, _In_ LONG_PTR lParam);

		Module();
		Module(const Module &);
		Module & operator = (const Module &);

	public:
		/// <summary>
		/// Destructor
		/// </summary>
		~Module();

		/// <summary>
		/// Load module
		/// </summary>
		/// <param name="path">Module path</param>
		/// <returns>Module</returns>
		static std::shared_ptr<Module> Load(const std::wstring & path);

		/// <summary>
		/// Is module loaded
		/// </summary>
		/// <returns>"true" if loaded, otherwise "false"</returns>
		bool IsLoaded() const;

		/// <summary>
		/// Get error
		/// </summary>
		/// <returns>Error</returns>
		DWORD GetError() const;

		/// <summary>
		/// Load resources
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Loaded resources</returns>
		std::vector<std::shared_ptr<Resource>> & LoadResources(std::vector<std::shared_ptr<Resource>> & result);
	};
}

#endif
