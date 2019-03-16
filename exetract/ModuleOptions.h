#ifndef __EXETRACT_MODULE_OPTIONS_H__
#	define __EXETRACT_MODULE_OPTIONS_H__

#	include <string>
#	include <set>
#	include <filesystem>

namespace Exetract
{
	class ModuleOptions
	{
	private:
		std::set<std::wstring> typeFilter;
		std::set<std::wstring> nameFilter;
		std::wstring outputPath;

	public:
		ModuleOptions();
		ModuleOptions(const ModuleOptions & moduleOptions);
		~ModuleOptions();

		void AddTypeFilter(const std::wstring & resourceType);
		void AddNameFilter(const std::wstring & resourceName);
		bool SetOutputPath(const std::wstring & outputPath);
		void ClearTypeFilter();
		void ClearNameFilter();
		void ClearOutputPath();
		void Clear();
		const std::set<std::wstring> & GetTypeFilter() const;
		const std::set<std::wstring> & GetNameFilter() const;
		std::filesystem::path GetOutputPath(std::filesystem::path & result) const;

		ModuleOptions & operator = (const ModuleOptions & moduleOptions);
	};
}

#endif
