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
	/// Data module class
	/// </summary>
	class DataModule
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
		/// Current data module
		/// </summary>
		static DataModule *currentDataModule;

		/// <summary>
		/// Resources
		/// </summary>
		std::vector<std::shared_ptr<Resource>> *resources;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="moduleHandle">Module handle</param>
		/// <param name="error">Error</param>
		DataModule(HMODULE moduleHandle, DWORD error);

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

		DataModule();
		DataModule(const DataModule &);
		DataModule & operator = (const DataModule &);

	public:
		/// <summary>
		/// Destructor
		/// </summary>
		~DataModule();

		/// <summary>
		/// Load data module
		/// </summary>
		/// <param name="path">Module path</param>
		/// <returns>Data module</returns>
		static std::shared_ptr<DataModule> Load(const std::wstring & path);

		/// <summary>
		/// Is data module loaded
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
