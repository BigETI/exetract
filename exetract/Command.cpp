#include "Command.h"

using namespace std;
using namespace Exetract;

/// <summary>
/// Constructor
/// </summary>
/// <param name="func">Command function</param>
/// <param name="description">Command description</param>
/// <param name="fullDescription">Command full description</param>
Command::Command(void (*func)(const vector<wstring> &), const wstring & description, const vector<wstring> & fullDescription) : func(func), description(description), fullDescription(fullDescription)
{
	// ...
}

/// <summary>
/// Destructor
/// </summary>
Command::~Command()
{
	// ...
}

/// <summary>
/// Invoke command
/// </summary>
/// <param name="params">Command parameters</param>
void Command::Invoke(const vector<wstring> & params) const
{
	if (func)
	{
		func(params);
	}
}

/// <summary>
/// Get command description
/// </summary>
/// <returns>Command description</returns>
const wstring & Command::GetDescription() const
{
	return description;
}

/// <summary>
/// Get command full description
/// </summary>
/// <returns>Command full description</returns>
const vector<wstring> & Command::GetFullDescription() const
{
	return fullDescription;
}
