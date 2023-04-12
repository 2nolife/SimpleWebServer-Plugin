// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReceiveEventActor.generated.h"

/** Sample actor with the web server component.
 *  Prints received data from the web server to the log.  
 */
UCLASS()
class MYPROJECT_API AReceiveEventActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReceiveEventActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class USimpleWebServerComponent* WebServerComponent;
	
	UFUNCTION()
	void OnContentReceived(FString Path, FString Content);

	FString ReceivedContent;
};
