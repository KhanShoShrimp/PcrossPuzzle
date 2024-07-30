#pragma once

class Solution
{
public:
	Solution(TileMap& tilemap, vector<int>* row_answer, vector<int>* col_answer) : 
		m_TileMap(tilemap), 
		m_Row_answer(row_answer), 
		m_Col_answer(col_answer)
	{
		Solve();
	}

private:
	TileMap& m_TileMap;
	vector<int>* m_Row_answer;
	vector<int>* m_Col_answer;

	bool IsCompleted()
	{
		for (int i = 0; i < m_TileMap.Height; i++)
		{
			Byte select = m_TileMap.Select[i];
			Byte block = m_TileMap.Block[i];

			if ((select | block) != Byte::MINUSTABLE[m_TileMap.Width - 1])
			{
				return false;
			}
		}
		return true;
	}

	void Solve()
	{
		do
		{
			for (int y = 0; y < m_TileMap.Height; y++)
			{
				Hint hint(
					m_TileMap.GetSelectRow(y),
					m_TileMap.GetBlockRow(y),
					m_TileMap.Width,
					m_Row_answer[y]);

				for (int x = 0; x < m_TileMap.Width; x++)
				{
					if ((hint.SelectHint >> x) & 1)
					{
						m_TileMap.Select[y][x] = true;
					}
					if ((hint.BlockHint >> x) & 1)
					{
						m_TileMap.Block[y][x] = true;
					}
				}
			}

			for (int x = 0; x < m_TileMap.Width; x++)
			{
				Hint hint(
					m_TileMap.GetSelectCol(x),
					m_TileMap.GetBlockCol(x),
					m_TileMap.Height,
					m_Col_answer[x]);

				for (int y = 0; y < m_TileMap.Height; y++)
				{
					if ((hint.SelectHint >> y) & 1)
					{
						m_TileMap.Select[y][x] = true;
					}
					if ((hint.BlockHint >> y) & 1)
					{
						m_TileMap.Block[y][x] = true;
					}
				}
			}
		} 
		while (!IsCompleted());
	}
};