#include "PluginManager.hpp"

PluginManager::PluginManager() {
	LoadingAvailableLibraries();
}

void PluginManager::LoadingAvailableLibraries() {
	WIN32_FIND_DATAA wfd;
	HANDLE search_handle;
	std::string search_template = GetPathDLL();
	search_handle = FindFirstFileA(search_template.c_str(), &wfd);

	if (search_handle != INVALID_HANDLE_VALUE) {
		do {
			std::string path_to_current_dll;
			path_to_current_dll = search_template.substr(0, search_template.find_last_of("\\/") + 1).append(wfd.cFileName);
			HMODULE plugin = LoadLibraryA(path_to_current_dll.c_str());
			if (!plugin) {
				std::cout << "System error: Error loading dll libraries (wrong path is specified or the current dll library is not found)" << std::endl;
				std::exit(1);
			}
			if (GetProcAddress(plugin, "name") && GetProcAddress(plugin, "function") && 
				GetProcAddress(plugin, "countOperands") && GetProcAddress(plugin, "priority")) {

				NameFunc name_function = (NameFunc)GetProcAddress(plugin, "name");
				TypeFunc function = (TypeFunc)GetProcAddress(plugin, "function");
				CountOperands count_operands = (CountOperands)GetProcAddress(plugin, "countOperands");
				Priority priority = (Priority)GetProcAddress(plugin, "priority");
				
				InitializationAvailableFunctions(name_function(), function, count_operands(), priority());
				continue;
			}
			FreeLibrary(plugin);

		} while (FindNextFileA(search_handle, &wfd) != NULL);
		
		FindClose(search_handle);
	}
}

std::string PluginManager::GetPathDLL() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string full_path = buffer;
	size_t position = full_path.find_last_of("\\/");
	std::string dll_path = full_path.substr(0, position).append("\\plugins\\*.dll");
	return dll_path;
}

void PluginManager::InitializationAvailableFunctions(std::string name_function, TypeFunc function, int count_operands, int priority) {
	_available_functions[name_function] = { function, count_operands, priority };
}

FunctionsMap& PluginManager::GetAvailableFunctions() {
	return _available_functions;
}