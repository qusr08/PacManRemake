#include "GridMapActor.h"

// Sets default values
AGridMapActor::AGridMapActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridMapActor::BeginPlay()
{
	Super::BeginPlay();

	// Exit case - the Grid Map is already initialized
	if (GridMap) return;

	// Initialize the Grid Map
	GridMap = NewObject<UGridMap>(this);
	GridMap->InitializeGrid(20, 20);

}

// Called every frame
void AGridMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

