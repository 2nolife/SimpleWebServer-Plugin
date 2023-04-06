// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleWebServer.h"
#include "HAL/Platform.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#if PLATFORM_WINDOWS
	#include "Windows/AllowWindowsPlatformTypes.h"
	#include "Windows/WindowsHWrapper.h"
#endif

THIRD_PARTY_INCLUDES_START
#include "sws.h"
THIRD_PARTY_INCLUDES_END

#if PLATFORM_WINDOWS
	#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include <string>

#define LOCTEXT_NAMESPACE "FSimpleWebServerModule"

void FSimpleWebServerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSimpleWebServerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FSwsCallback::on_post(std::string& path, std::string& content)
{
	FString Value = FString::Printf(TEXT("%s"), UTF8_TO_TCHAR(content.c_str()));
	if (OnWebServerPost.IsBound()) OnWebServerPost.Broadcast(Value);
	else UE_LOG(LogTemp, Warning, TEXT("No listener for OnWebServerPost event"));
}

void FSimpleWebServerModule::StartWebServer(FSwsCallback* Callback, const int Port)
{
	WebServer = new sws::SimpleWebServer();
	WebServer->create_instance();
	WebServer->add_default_routes();
	WebServer->callback = Callback;
	WebServer->start(Port);
}

void FSimpleWebServerModule::StopWebServer()
{
	WebServer->stop();
	WebServer->destroy_instance();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleWebServerModule, SimpleWebServer)