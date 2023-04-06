// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "Modules/ModuleManager.h"

THIRD_PARTY_INCLUDES_START
	#include "ThirdParty/SimpleWebServerLibrary/include/sws.h"
THIRD_PARTY_INCLUDES_END

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebServerPost, FString&);

/** Callback to receive content from the web server.
 *  Throws an OnWebServerPost event with the content received.
 */
class SIMPLEWEBSERVER_API FSwsCallback : public sws::Callback
{
public:
	virtual ~FSwsCallback() = default;
	virtual void on_post(std::string& path, std::string& content) override;
	FOnWebServerPost OnWebServerPost;
};

class SIMPLEWEBSERVER_API FSimpleWebServerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Web server methods */
	void StartWebServer(FSwsCallback* Callback, const int Port = 8080);
	void StopWebServer();

private:
	sws::SimpleWebServer* WebServer;
};
