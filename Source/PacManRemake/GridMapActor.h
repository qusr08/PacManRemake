// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridMap.h" 
#include "GridMapActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PACMANREMAKE_API AGridMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMapActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UGridMap* GridMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
