#include "GridMap.h"

UGridMap::UGridMap() : Rows(0), Columns(0), Size(0) {}

void UGridMap::InitializeGrid(int32 InRows, int32 InColumns)
{
	// Set the amount of rows and columns
	Rows = InRows;
	Columns = InColumns;
	Size = Rows * Columns;

	// Empty the grid and set the amount of rows
	Grid.Empty();
	Grid.SetNum(Size);

	// Initialize all cells to empty by default
	for (int32 i = 0; i < Size; i++)
	{
		Grid[i] = FGridCell();
	}
}

void UGridMap::ToggleMovingWalls(const TArray<FIntPoint>& WallPositions)
{
	// Iterate through each given point
	for (const FIntPoint& Pos : WallPositions)
	{
		// Get the index of the cell
		int32 Row = Pos.X;
		int32 Column = Pos.Y;
		int32 Index = GetIndex(Row, Column);

		// Exit case - if the index is invalid
		if (!Grid.IsValidIndex(Index)) return;

		// Exit case - if the cell is not a moving wall
		if (Grid[Index].CellType != EGridCellType::MovingWall) return;

		// Toggle activity
		Grid[Index].bIsActive = !Grid[Index].bIsActive;
	}
}

void UGridMap::SetCell(int32 Row, int32 Column, EGridCellType NewType, bool bActive)
{
	// Get the index
	int32 Index = GetIndex(Row, Column);

	// Exit case - the index is invalid
	if (!Grid.IsValidIndex(Index)) return;

	// Set the cell type and active state
	Grid[Index].CellType = NewType;
	Grid[Index].bIsActive = bActive;
}

FGridCell UGridMap::GetCell(int32 Row, int32 Column) const
{
	// Get the index
	int32 Index = GetIndex(Row, Column);

	// Exit case - the index is invalid
	if (!Grid.IsValidIndex(Index)) return FGridCell();

	// Return the cell at the index
	return Grid[Index];
}

FIntPoint UGridMap::GetNeighborCoordinates(int32 Row, int32 Column, EGridDirection Direction, int32 Distance) const
{
	int32 NewRow = Row;
	int32 NewColumn = Column;

	// Update the neighbor based on the direction and distance
	switch (Direction)
	{
	case EGridDirection::Up:
		NewRow = FMath::Clamp(Row - Distance, 0, Rows - 1);
		break;

	case EGridDirection::Down:
		NewRow = FMath::Clamp(Row + Distance, 0, Rows - 1);
		break;

	case EGridDirection::Left:
		NewColumn = FMath::Clamp(Column - Distance, 0, Columns - 1);
		break;

	case EGridDirection::Right:
		NewColumn = FMath::Clamp(Column + Distance, 0, Columns - 1);
		break;

	default:
		break;
	}

	// Return the neighbor point
	return FIntPoint(NewRow, NewColumn);
}

FGridCell UGridMap::GetNeighborCell(int32 Row, int32 Column, EGridDirection Direction, int32 Distance) const
{
	// Get the neighbor coordinates
	FIntPoint NeighborCoords = GetNeighborCoordinates(Row, Column, Direction, Distance);

	// Return the cell at the neighbor coordinates
	return GetCell(NeighborCoords.X, NeighborCoords.Y);
}