// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"


void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    TEST();
}

void APawnTurret::TEST()
{
    Super::TEST();

    UE_LOG(LogTemp, Warning, TEXT("TURRET call"));
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    FVector PlayerCurrentLocation = PlayerPawn->GetActorLocation();
    RotateTurretFunction(PlayerCurrentLocation);
}

void APawnTurret::CheckFireCondition()
{
    if(!PlayerPawn){return;}

    if(!PlayerPawn->GetIsPlayerAlive()){return;}

    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()); // float distance = 

}
