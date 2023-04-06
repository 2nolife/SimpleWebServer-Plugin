#pragma once
#if defined _WIN64
	#define DLL_IMPORT __declspec(dllimport)
#endif
#ifndef DLL_IMPORT
	#define DLL_IMPORT
#endif

#include <string>
#include <thread>
#include <map>

namespace sws {

	using namespace std;

	class Callback {
	public:
		DLL_IMPORT virtual void on_post(string& path, string& content);
		DLL_IMPORT virtual void on_get(string& path, map<string, string>& query);
	};

	class SimpleWebServer {
	public:
		DLL_IMPORT SimpleWebServer();
		DLL_IMPORT ~SimpleWebServer();

		void* server;
		thread server_thread;
		Callback* callback = nullptr;

		DLL_IMPORT void create_instance();
		DLL_IMPORT void destroy_instance();
		DLL_IMPORT void start(int port);
		DLL_IMPORT void stop();
		DLL_IMPORT void add_default_routes();
	};

}
