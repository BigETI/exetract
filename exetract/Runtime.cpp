#include <iostream>
#include <fstream>
#include "Runtime.h"

using namespace std;
using namespace std::filesystem;
using namespace Exetract;

const Command Runtime::helpCommand(CmdShowHelpTopic, L"Shows help topic", vector<wstring>() =
	{
		L"This command shows the available help topics.",
		L"",
		L"Usage: --help <help topic (optional)>",
		L"Example: --help module"
	});
const Command Runtime::moduleCommand(CmdDefineModulePath, L"Defines module path", vector<wstring>() =
	{
		L"This command defines the module path to extract resource data or files from.",
		L"Good practice: Specify module options before this command.",
		L"",
		L"Usage: --module <module path>",
		L"Example: --module example.exe"
	});
const Command Runtime::typeCommand(CmdDefineResourceTypeFilter, L"Adds resource type to filter", vector<wstring>() =
	{
		L"This commands sets the resource type filter for the current specified module.",
		L"",
		L"Usage: --type <resource types>",
		L"Example: --type ICON MANIFEST"
	});
const Command Runtime::nameCommand(CmdDefineResourceNameFilter, L"Adds resource name to filter", vector<wstring>() =
	{
		L"This commands sets the resource name filter for the current specified module.",
		L"",
		L"Usage: --name <resource names>",
		L"Example: --name 1 2"
	});
const Command Runtime::resetCommand(CmdResetFilters, L"Resets all filters", vector<wstring>() =
	{
		L"This commands resets all module options.",
		L"",
		L"Usage: --reset"
		L"Example: --reset"
	});
const Command Runtime::outputCommand(CmdDefineOutputPath, L"Specifies an output path", vector<wstring>() =
	{
		L"This command specifies an output path for the extracted resource data or files.",
		L"",
		L"Usage: --output <output path>",
		L"Example: --output dump"
	});

const map<wstring, const Command &> Runtime::commands =
{
	{ L"h", helpCommand },
	{ L"help", helpCommand },
	{ L"m", moduleCommand },
	{ L"module", moduleCommand },
	{ L"t", typeCommand },
	{ L"type", typeCommand },
	{ L"n", nameCommand },
	{ L"name", nameCommand },
	{ L"r", resetCommand },
	{ L"reset", resetCommand },
	{ L"o", outputCommand },
	{ L"output", outputCommand }
};

vector<pair<shared_ptr<Module>, ModuleOptions>> Runtime::moduleOptions;
ModuleOptions Runtime::currentModuleOptions;
bool Runtime::showHelp(true);

void Runtime::CmdShowHelpTopic(const vector<wstring> & params)
{
	if (params.size() > 0UL)
	{
		ShowHelpTopic(params[0]);
	}
	else
	{
		ShowHelpTopic();
	}
}

void Runtime::CmdDefineModulePath(const vector<wstring> & params)
{
	if (params.size() > 0)
	{
		for (auto & path : params)
		{
			moduleOptions.push_back(pair<shared_ptr<Module>, const ModuleOptions>(Module::Load(path), currentModuleOptions));
		}
	}
	else
	{
		cout << "Please define atleast one module path." << endl;
		ShowHelpTopic(moduleCommand);
	}
}

void Runtime::CmdDefineResourceTypeFilter(const vector<wstring> & params)
{
	currentModuleOptions.ClearTypeFilter();
	for (auto & type_filter : params)
	{
		currentModuleOptions.AddTypeFilter(type_filter);
	}
}

void Runtime::CmdDefineResourceNameFilter(const vector<wstring> & params)
{
	currentModuleOptions.ClearNameFilter();
	for (auto & name_filter : params)
	{
		currentModuleOptions.AddNameFilter(name_filter);
	}
}

void Runtime::CmdResetFilters(const vector<wstring> & params)
{
	currentModuleOptions.Clear();
	if (params.size() > 0UL)
	{
		cout << "Warning: Reset command ignores additional parameters." << endl;
	}
}

void Runtime::CmdDefineOutputPath(const vector<wstring> & params)
{
	if (params.size() == 1UL)
	{
		const wstring & output_path(params[0]);
		if (!(currentModuleOptions.SetOutputPath(output_path)))
		{
			wcout << L"Output path \"" << output_path << L"\" does not exist." << endl;
		}
	}
	else
	{
		cout << "Please define only one output path." << endl;
		ShowHelpTopic(outputCommand);
	}
}

/// <summary>
/// Get last error as string
/// </summary>
/// <param name="error">Error</param>
/// <param name="result">Result</param>
/// <returns>Error as string</returns>
wstring & Runtime::GetLastErrorAsString(DWORD error, wstring & result)
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
void Runtime::PrintError(DWORD error)
{
	wstring e;
	wcout << L"Error (" << error << L") : \"" << GetLastErrorAsString(error, e) << L"\"" << endl;
}

int Runtime::Main(const vector<wstring> & args)
{
	int ret(0);
	vector<pair<const Command &, vector<wstring>>> args_params;
	for (auto & arg : args)
	{
		if (arg.size() > 0UL)
		{
			if (arg[0] == L'-')
			{
				if (arg.size() > 1UL)
				{
					wstring command;
					if (arg[1] == L'-')
					{
						if (arg.size() > 2UL)
						{
							command = arg.substr(2UL);
						}
					}
					else
					{
						command = arg.substr(1UL);
					}
					if (command.size() > 0UL)
					{
						auto it(commands.find(command));
						if (it != commands.end())
						{
							args_params.push_back(pair<const Command &, vector<wstring>>(it->second, vector<wstring>()));
						}
						else
						{
							if (args_params.size() == 0UL)
							{
								args_params.push_back(pair<const Command &, vector<wstring>>(moduleCommand, vector<wstring>()));
							}
							args_params.rbegin()->second.push_back(arg);
						}
					}
				}
			}
			else
			{
				if (args_params.size() == 0UL)
				{
					args_params.push_back(pair<const Command &, vector<wstring>>(moduleCommand, vector<wstring>()));
				}
				args_params.rbegin()->second.push_back(arg);
			}
		}
	}
	for (auto & args_param : args_params)
	{
		args_param.first.Invoke(args_param.second);
	}
	if (moduleOptions.size() > 0UL)
	{
		moduleOptions.rbegin()->second = currentModuleOptions;
		for (auto & module_option : moduleOptions)
		{
			Module & module(*(module_option.first));
			if (module.IsLoaded())
			{
				vector<shared_ptr<Resource>> resources;
				module.LoadResources(resources);
				for (auto & resource : resources)
				{
					bool write_file(true);
					const set<wstring> & type_filter(module_option.second.GetTypeFilter());
					const set<wstring> & name_filter(module_option.second.GetNameFilter());
					wstring resource_type_name;
					wstring resource_type;
					wstring resource_name;
					resource->GetTypeName(resource_type_name);
					resource->GetType(resource_type);
					resource->GetName(resource_name);
					if (!(type_filter.empty()))
					{
						write_file = false;
						for (auto & t_f : type_filter)
						{
							wstring upper_t_f(t_f);
							std::transform(upper_t_f.begin(), upper_t_f.end(), upper_t_f.begin(), ::toupper);
							if ((upper_t_f == resource_type_name) || (upper_t_f == resource_type))
							{
								write_file = true;
								break;
							}
						}
					}
					if (write_file)
					{
						if (!(name_filter.empty()))
						{
							write_file = false;
							for (auto & n_f : name_filter)
							{
								wstring upper_n_f(n_f);
								std::transform(upper_n_f.begin(), upper_n_f.end(), upper_n_f.begin(), ::toupper);
								if (upper_n_f == resource_name)
								{
									write_file = true;
									break;
								}
							}
						}
					}
					if (write_file)
					{
						path directory;
						path p(module_option.second.GetOutputPath(directory) / path(resource_type_name + L"_" + resource_name + L".bin"));
						ofstream ofs(p, ios::binary);
						if (ofs.is_open())
						{
							wcout << L"Writing file \"" << p << L"\"..." << endl;
							resource->WriteToFileStream(ofs);
							ofs.close();
						}
						else
						{
							wcout << "Failed to open file \"" << p << L"\"." << endl;
						}
					}
				}
			}
			else
			{
				PrintError(module.GetError());
			}
		}
		showHelp = false;
	}
	if (showHelp)
	{
		ShowHelpTopic();
	}
	return ret;
}

void Runtime::ShowHelpTopic()
{
	wcout << L"Start of help topic:" << endl << endl;
	for (auto & command : commands)
	{
		wcout << L"\t-" << command.first << L", --" << command.first << endl << L"\t\t" << command.second.GetDescription() << endl << endl;
	}
	cout << endl << "End of help topic." << endl;
	showHelp = false;
}

void Runtime::ShowHelpTopic(const wstring & helpTopic)
{
	auto it(commands.find(helpTopic));
	if (it != commands.end())
	{
		ShowHelpTopic(it->second);
	}
	else
	{
		ShowHelpTopic();
	}
}

void Runtime::ShowHelpTopic(const Command & command)
{
	const vector<wstring> & full_description(command.GetFullDescription());
	wcout << L"Start of help topic:" << endl << endl << L"\tDescription: " << endl << L"\t\t" << command.GetDescription() << endl << endl << L"\tFull description:" << endl;
	for (auto & f_d : full_description)
	{
		wcout << L"\t\t" << f_d << endl;
	}
	cout << endl << "End of help topic." << endl;
	showHelp = false;
}
