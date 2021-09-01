// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponents.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthComponents::AHealthComponents()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;



}

// Called when the game starts or when spawned
void AHealthComponents::BeginPlay()
{
	Super::BeginPlay();
	
	Health = DefaultHealth;
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &AHealthComponents::TakeDamage);
}

void AHealthComponents::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0) {return;}
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if(Health <= 0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health compoonent has no reference to the GameMode"));
		}
	}
}


