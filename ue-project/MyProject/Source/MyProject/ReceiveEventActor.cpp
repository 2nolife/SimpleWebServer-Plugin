// Fill out your copyright notice in the Description page of Project Settings.


#include "ReceiveEventActor.h"
#include "SimpleWebServerComponent.h"

// Sets default values
AReceiveEventActor::AReceiveEventActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WebServerComponent = CreateDefaultSubobject<USimpleWebServerComponent>(TEXT("WebServer"));
	WebServerComponent->OnWebServerContentReceived.AddDynamic(this, &AReceiveEventActor::OnContentReceived);
}

// Called when the game starts or when spawned
void AReceiveEventActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AReceiveEventActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReceiveEventActor::OnContentReceived(FString Content)
{
	UE_LOG(LogTemp, Warning, TEXT("CONTENT: %s"), *Content);

	// Test the value can be assigned and used
	ReceivedContent = Content;
	UE_LOG(LogTemp, Warning, TEXT("ReceivedContent: %s"), *ReceivedContent);
}

