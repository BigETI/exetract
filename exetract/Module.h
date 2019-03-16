#ifndef __EXETRACT_MODULE_H__
#	define __EXETRACT_MODULE_H__

#	include <vector>
#	include <memory>
#	include "Resource.h"

namespace Exetract
{
	class Module
	{
	private:
		HMODULE moduleHandle;
		DWORD error;
		std::vector<std::shared_ptr<Resource>> *resources;

		Module(HMODULE moduleHandle, DWORD error);

		static BOOL CALLBACK EnumResNameProc(_In_opt_ HMODULE hModule, _In_ LPCWSTR lpType, _In_ LPWSTR lpName, _In_ LONG_PTR lParam);
		static BOOL CALLBACK EnumResTypeProc(_In_opt_ HMODULE hModule, _In_ LPWSTR lpType, _In_ LONG_PTR lParam);

		Module();
		Module(const Module &);
		Module & operator = (const Module &);
	public:
		~Module();

		static std::shared_ptr<Module> Load(const std::wstring & path);

		bool IsLoaded() const;
		DWORD GetError() const;
		std::vector<std::shared_ptr<Resource>> & LoadResources(std::vector<std::shared_ptr<Resource>> & result);
	};
}

#endif
