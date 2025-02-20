// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridMap.generated.h"

// Define the types of cells within the maze
UENUM(BlueprintType)
enum class EGridCellType : uint8
{
	Empty	UMETA(DisplayName = "Empty"),
	Pellet        UMETA(DisplayName = "Pellet"),
	StaticWall    UMETA(DisplayName = "StaticWall"),
	MovingWall    UMETA(DisplayName = "MovingWall"),
	Player        UMETA(DisplayName = "Player"),
	Ghost         UMETA(DisplayName = "Ghost")
};

// Direction enum for neighbor queries
UENUM(BlueprintType)
enum class EGridDirection : uint8
{
	Up      UMETA(DisplayName = "Up"),
	Down    UMETA(DisplayName = "Down"),
	Left    UMETA(DisplayName = "Left"),
	Right   UMETA(DisplayName = "Right")
};

// A struct that represents one cell in the grid
USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	EGridCellType CellType;

	// For moving walls: indicates if the wall is active (present) or not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	bool bIsActive;

	FGridCell()
		: CellType(EGridCellType::Empty), bIsActive(true)
	{
	}
};

UCLASS()
class PACMANREMAKE_API UGridMap : public UObject
{
	GENERATED_BODY()
	
public:
	UGridMap();

	// ----- VARIABLES -----

	// Number of rows within the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Rows;

	// Number of columns within the grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Columns;

	// 1D-Array storing the grid cells (size: Rows * Columns)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<FGridCell> Grid;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Size;


	// ----- FUNCTIONS -----

	// Initialize the grid with empty cells
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void InitializeGrid(int32 InRows, int32 InColumns);

	// Toggle the state of moving walls (when the maze shifts)
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void ToggleMovingWalls(const TArray<FIntPoint>& WallPositions);

	// Set the value of a specific cell
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetCell(int32 Row, int32 Column, EGridCellType NewType, bool bActive = true);

	// Get the cell information at a specific grid location
	UFUNCTION(BlueprintCallable, Category = "Grid")
	FGridCell GetCell(int32 Row, int32 Column) const;

	// Get the coordinates of a neighbor cell at a specified direction and distance
	UFUNCTION(BlueprintCallable, Category = "Grid")
	FIntPoint GetNeighborCoordinates(int32 Row, int32 Column, EGridDirection Direction, int32 Distance) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FGridCell GetNeighborCell(int32 Row, int32 Column, EGridDirection Direction, int32 Distance) const;


private:
	// Convert 2D coordinates into a 1D index
	FORCEINLINE int32 GetIndex(int32 Row, int32 Column) const { return Row * Columns + Column; }
};
