#ifndef __EXETRACT_COMMAND_HELP_H__
#	define __EXETRACT_COMMAND_HELP_H__

#	include <string>
#	include <vector>

/// <summary>
/// Exetract namespace
/// </summary>
namespace Exetract
{
	/// <summary>
	/// Command class
	/// </summary>
	class Command
	{
	private:
		/// <summary>
		/// Command function
		/// </summary>
		void(*func)(const std::vector<std::wstring> &);

		/// <summary>
		/// Command description
		/// </summary>
		std::wstring description;

		/// <summary>
		/// Command full description
		/// </summary>
		std::vector<std::wstring> fullDescription;

		Command();
		Command(const Command &);
		Command & operator = (const Command &);
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="func">Command function</param>
		/// <param name="description">Command description</param>
		/// <param name="fullDescription">Command full description</param>
		Command(void(*func)(const std::vector<std::wstring> &), const std::wstring & description, const std::vector<std::wstring> & fullDescription);

		/// <summary>
		/// Destructor
		/// </summary>
		~Command();

		/// <summary>
		/// Invoke command
		/// </summary>
		/// <param name="params">Command parameters</param>
		void Invoke(const std::vector<std::wstring> & params) const;

		/// <summary>
		/// Get command description
		/// </summary>
		/// <returns>Command description</returns>
		const std::wstring & GetDescription() const;

		/// <summary>
		/// Get command full description
		/// </summary>
		/// <returns>Command full description</returns>
		const std::vector<std::wstring> & GetFullDescription() const;
	};
}

#endif
