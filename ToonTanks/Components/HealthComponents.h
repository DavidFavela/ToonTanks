// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponents.generated.h"

class ATankGameModeBase;

UCLASS()
class TOONTANKS_API AHealthComponents : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.0f;
	float Health = 0.0f;

	ATankGameModeBase* GameModeRef;

public:	
	// Sets default values for this actor's properties
	AHealthComponents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

};
