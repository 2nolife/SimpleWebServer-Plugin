// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleWebServerComponent.h"

#include "SimpleWebServer.h"

// Sets default values for this component's properties
USimpleWebServerComponent::USimpleWebServerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Get the web server plugin
	Plugin = FModuleManager::GetModulePtr<FSimpleWebServerModule>("SimpleWebServer");
}


// Called when the game starts
void USimpleWebServerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start the web server plugin and listen to events
	Plugin->StartWebServer(&Callback, WebServerPort);
	Callback.OnWebServerPost.AddUObject(this, &USimpleWebServerComponent::OnContentReceived);
}

void USimpleWebServerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Stop the web server
	Plugin->StopWebServer();
}

void USimpleWebServerComponent::OnContentReceived(FString& Content)
{
	if (OnWebServerContentReceived.IsBound()) OnWebServerContentReceived.Broadcast(Content);
	else UE_LOG(LogTemp, Warning, TEXT("No listener for OnWebServerContentReceived event"));
}
