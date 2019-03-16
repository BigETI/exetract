#ifndef __EXETRACT_COMMAND_HELP_H__
#	define __EXETRACT_COMMAND_HELP_H__

#	include <string>
#	include <vector>

namespace Exetract
{
	class Command
	{
	private:
		void(*func)(const std::vector<std::wstring> &);
		std::wstring description;
		std::vector<std::wstring> fullDescription;

		Command();
		Command(const Command &);
		Command & operator = (const Command &);
	public:
		Command(void(*func)(const std::vector<std::wstring> &), const std::wstring & description, const std::vector<std::wstring> & fullDescription);
		~Command();

		void Invoke(const std::vector<std::wstring> & params) const;
		const std::wstring & GetDescription() const;
		const std::vector<std::wstring> & GetFullDescription() const;
	};
}

#endif