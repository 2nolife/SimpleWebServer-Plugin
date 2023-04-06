// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleWebServer.h"
#include "Components/ActorComponent.h"
#include "SimpleWebServerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebServerContentReceived, FString, Content);

/** Component to communicate with the web server.
 *  Throws an OnWebServerContentReceived event with the content received.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLEWEBSERVER_API USimpleWebServerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimpleWebServerComponent();

	UPROPERTY(BlueprintAssignable, Category="Web Server")
	FOnWebServerContentReceived OnWebServerContentReceived;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Web Server")
	int32 WebServerPort = 8080;
	
private:
	FSimpleWebServerModule* Plugin;
	FSwsCallback Callback;

	/** Called by the web server when content is received */
	UFUNCTION()
	void OnContentReceived(FString& Content);
};
