// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = DefaultHealth;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	// ...
	}
	
}


// Called every frame
void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0) {return;}//|| Health <= 0//
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health is %f"), Health);

	if(Health <= 0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to the GameMode"));
		}
	}
}
