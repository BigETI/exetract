#include "Runtime.h"

using namespace std;
using namespace Exetract;

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Arguments</param>
/// <returns>Exit code</returns>
int wmain(int argc, wchar_t *argv[])
{
	vector<wstring> args;
	for (int i(1); i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	return Runtime::Main(args);
}
