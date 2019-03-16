#ifndef __EXETRACT_RUNTIME_H__
#	define __EXETRACT_RUNTIME_H__

#	include <map>
#	include "Command.h"
#	include "ModuleOptions.h"
#	include "Module.h"

/// <summary>
/// Exetract namespace
/// </summary>
namespace Exetract
{
	/// <summary>
	/// Runtime class
	/// </summary>
	class Runtime
	{
	private:
		/// <summary>
		/// Help command
		/// </summary>
		static const Command helpCommand;

		/// <summary>
		/// Module command
		/// </summary>
		static const Command moduleCommand;

		/// <summary>
		/// Type command
		/// </summary>
		static const Command typeCommand;

		/// <summary>
		/// Name command
		/// </summary>
		static const Command nameCommand;

		/// <summary>
		/// Reset command
		/// </summary>
		static const Command resetCommand;

		/// <summary>
		/// Output command
		/// </summary>
		static const Command outputCommand;

		/// <summary>
		/// Commands
		/// </summary>
		static const std::map<std::wstring, const Command &> commands;

		/// <summary>
		/// Module options
		/// </summary>
		static std::vector<std::pair<std::shared_ptr<Module>, ModuleOptions>> moduleOptions;

		/// <summary>
		/// Current module options
		/// </summary>
		static ModuleOptions currentModuleOptions;

		/// <summary>
		/// Show help
		/// </summary>
		static bool showHelp;

		/// <summary>
		/// Show help topic command
		/// </summary>
		/// <param name="params">Command parameters</param>
		static void CmdShowHelpTopic(const std::vector<std::wstring> & params);

		/// <summary>
		/// Define module path command
		/// </summary>
		/// <param name="params">Command parameters</param>
		static void CmdDefineModulePath(const std::vector<std::wstring> & params);

		/// <summary>
		/// Define resource type filter command
		/// </summary>
		/// <param name="params">Command parameters</param>
		static void CmdDefineResourceTypeFilter(const std::vector<std::wstring> & params);

		/// <summary>
		/// Define resource name filter command
		/// </summary>
		/// <param name="params">Command parameters</param>
		static void CmdDefineResourceNameFilter(const std::vector<std::wstring> & params);

		/// <summary>
		/// Reset module options command
		/// </summary>
		/// <param name="params">Command parameters</param>
		static void CmdResetModuleOptions(const std::vector<std::wstring> & params);

		/// <summary>
		/// Define output path command
		/// </summary>
		/// <param name="params">Command parameters</param>
		static void CmdDefineOutputPath(const std::vector<std::wstring> & params);

		/// <summary>
		/// Get last error as string
		/// </summary>
		/// <param name="error">Error</param>
		/// <param name="result">Result</param>
		/// <returns>Error as string</returns>
		static std::wstring & GetLastErrorAsString(DWORD error, std::wstring & result);

		/// <summary>
		/// Print error
		/// </summary>
		/// <param name="error">Error</param>
		static void PrintError(DWORD error);

		Runtime();
		Runtime(const Runtime &);
		~Runtime();
		Runtime & operator = (const Runtime &);

	public:
		/// <summary>
		/// Runtime main entry point
		/// </summary>
		/// <param name="args">Command line arguments</param>
		/// <returns>Exit code</returns>
		static int Main(const std::vector<std::wstring> & args);

		/// <summary>
		/// Show help topic
		/// </summary>
		static void ShowHelpTopic();

		/// <summary>
		/// Show help topic
		/// </summary>
		/// <param name="helpTopic">Help topic</param>
		static void ShowHelpTopic(const std::wstring & helpTopic);

		/// <summary>
		/// Show help topic
		/// </summary>
		/// <param name="command">Command</param>
		static void ShowHelpTopic(const Command & command);
	};
}

#endif
