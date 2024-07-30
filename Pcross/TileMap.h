#pragma once

class TileMap
{
private:

public:
	int Width;
	int Height;
	Byte* Select;
	Byte* Block;

	TileMap(int width, int height) : Width(width), Height(height)
	{
		Select = new Byte[height];
		Block = new Byte[height];
	}

	~TileMap()
	{
		delete[] Select;
		delete[] Block;
	}

	Int64 GetSelectRow(int index)
	{
		return Select[index];
	}

	Int64 GetBlockRow(int index)
	{
		return Block[index];
	}

	Int64 GetSelectCol(int index)
	{
		Int64 value = 0;
		for (int y = 0; y < Height; y++)
		{
			if (Select[y][index])
			{
				value |= (1ULL << y);
			}
		}
		return value;
	}

	Int64 GetBlockCol(int index)
	{
		Int64 value = 0;
		for (int y = 0; y < Height; y++)
		{
			if (Block[y][index])
			{
				value |= (1ULL << y);
			}
		}
		return value;
	}

	void Show()
	{
		cout << "Map : " << endl;
		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x++)
			{
				if (Select[y][x])
				{
					cout << "бс";
				}
				else if (Block[y][x])
				{
					cout << "е╣";
				}
				else
				{
					cout << "бр";
				}
			}
			cout << endl;
		}
	}
};