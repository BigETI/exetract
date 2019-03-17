#ifndef __EXETRACT_MODULE_OPTIONS_H__
#	define __EXETRACT_MODULE_OPTIONS_H__

#	include <string>
#	include <set>
#	include <filesystem>

/// <summary>
/// Exetract namespace
/// </summary>
namespace Exetract
{
	/// <summary>
	/// Data module options class
	/// </summary>
	class DataModuleOptions
	{
	private:
		/// <summary>
		/// Resource type filter
		/// </summary>
		std::set<std::wstring> typeFilter;

		/// <summary>
		/// Resource name filter
		/// </summary>
		std::set<std::wstring> nameFilter;

		/// <summary>
		/// Output path
		/// </summary>
		std::wstring outputPath;

	public:
		/// <summary>
		/// Default constructor
		/// </summary>
		DataModuleOptions();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="dataModuleOptions">Data module options</param>
		DataModuleOptions(const DataModuleOptions & dataModuleOptions);

		/// <summary>
		/// Destructor
		/// </summary>
		~DataModuleOptions();

		/// <summary>
		/// Add resource type filter
		/// </summary>
		/// <param name="resourceType">Resource type filter</param>
		void AddTypeFilter(const std::wstring & resourceType);

		/// <summary>
		/// Add resource name filter
		/// </summary>
		/// <param name="resourceName">Resource name</param>
		void AddNameFilter(const std::wstring & resourceName);

		/// <summary>
		/// Set output path
		/// </summary>
		/// <param name="outputPath">Output path</param>
		/// <returns>"true" if output path exists, otherwise "false"</returns>
		bool SetOutputPath(const std::wstring & outputPath);

		/// <summary>
		/// Clear resource type filter
		/// </summary>
		void ClearTypeFilter();

		/// <summary>
		/// Clear resource name filter
		/// </summary>
		void ClearNameFilter();

		/// <summary>
		/// Clear output path
		/// </summary>
		void ClearOutputPath();

		/// <summary>
		/// Clear module options
		/// </summary>
		void Clear();

		/// <summary>
		/// Get resource type filter
		/// </summary>
		/// <returns>Resource type filter</returns>
		const std::set<std::wstring> & GetTypeFilter() const;

		/// <summary>
		/// Get resource name filter
		/// </summary>
		/// <returns>Resource name filter</returns>
		const std::set<std::wstring> & GetNameFilter() const;

		/// <summary>
		/// Get output path
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Output path</returns>
		std::filesystem::path GetOutputPath(std::filesystem::path & result) const;

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="dataModuleOptions">Data module options</param>
		/// <returns>This object</returns>
		DataModuleOptions & operator = (const DataModuleOptions & dataModuleOptions);
	};
}

#endif
