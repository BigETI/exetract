#ifndef __EXETRACT_RUNTIME_H__
#	define __EXETRACT_RUNTIME_H__

#	include <map>
#	include "Command.h"
#	include "ModuleOptions.h"
#	include "Module.h"

namespace Exetract
{
	class Runtime
	{
	private:
		static const Command helpCommand;
		static const Command moduleCommand;
		static const Command typeCommand;
		static const Command nameCommand;
		static const Command resetCommand;
		static const Command outputCommand;
		static const std::map<std::wstring, const Command &> commands;
		static std::vector<std::pair<std::shared_ptr<Module>, ModuleOptions>> moduleOptions;
		static ModuleOptions currentModuleOptions;
		static bool showHelp;

		static void CmdShowHelpTopic(const std::vector<std::wstring> & params);
		static void CmdDefineModulePath(const std::vector<std::wstring> & params);
		static void CmdDefineResourceTypeFilter(const std::vector<std::wstring> & params);
		static void CmdDefineResourceNameFilter(const std::vector<std::wstring> & params);
		static void CmdResetFilters(const std::vector<std::wstring> & params);
		static void CmdDefineOutputPath(const std::vector<std::wstring> & params);
		static std::wstring & GetLastErrorAsString(DWORD error, std::wstring & result);
		static void PrintError(DWORD error);

		Runtime();
		Runtime(const Runtime &);
		~Runtime();
		Runtime & operator = (const Runtime &);
	public:
		static int Main(const std::vector<std::wstring> & args);
		static void ShowHelpTopic();
		static void ShowHelpTopic(const std::wstring & helpTopic);
		static void ShowHelpTopic(const Command & command);
	};
}

#endif
