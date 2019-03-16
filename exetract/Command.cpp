#include "Command.h"

using namespace std;
using namespace Exetract;

Command::Command(void (*func)(const vector<wstring> &), const wstring & description, const vector<wstring> & fullDescription) : func(func), description(description), fullDescription(fullDescription)
{
	// ...
}

Command::~Command()
{
	// ...
}

void Command::Invoke(const vector<wstring> & params) const
{
	if (func)
	{
		func(params);
	}
}

const wstring & Command::GetDescription() const
{
	return description;
}

const vector<wstring> & Command::GetFullDescription() const
{
	return fullDescription;
}
