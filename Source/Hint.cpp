#include "Base.h"

Hint::Hint(Int64 select, Int64 block, int length, vector<int>& answer) :
	m_Select(select),
	m_Block(block | Byte::PLUSTABLE[length]),
	m_Length(length),
	m_Answer(answer),
	SelectHint(Byte::FILL),
	BlockHint(Byte::EMPTY)
{
	UpdateSpaces();
	Solve();
}

void Hint::UpdateSpaces()
{
	int start = 0;
	int end = 0;

	m_Spaces.clear();

	while (TryGetSpace(start, end))
	{
		m_Spaces.push_back(start);
		m_Spaces.push_back(end);
	}
}

void Hint::Solve()
{
	if (!IsVaildAnswer())
	{
		SelectHint = Byte::EMPTY;
		BlockHint = Byte::FILL;
		return;
	}

	m_Written = false;

	Search(0, 0, ~Byte::GetMask(0, m_Length - 1), Byte::EMPTY);

	WriteHint();
}

bool Hint::TryGetSpace(int& start, int& end)
{
	start = Byte::FFSLL(~m_Block & Byte::PLUSTABLE[end]);
	if (start < 0)
	{
		return false;
	}

	end = Byte::FFSLL(m_Block & Byte::PLUSTABLE[start]);
	if (end < 0)
	{
		return false;
	}

	return true;
}


bool Hint::IsVaildAnswer()
{
	if (m_Answer.size() == 0)
	{
		return false;
	}

	if (m_Answer[0] == 0)
	{
		return false;
	}

	return true;
}

void Hint::Search(int space_index, int answer_index, Int64 select, Int64 block)
{
	if (answer_index >= m_Answer.size())
	{
		OverlapHint(select, block);
		return;
	}

	for (int i = space_index; i < m_Spaces.size(); i += 2)
	{
		int space_begin = m_Spaces[i];
		int space_end = m_Spaces[i + 1];
		int space = space_end - space_begin - 1;
		Int64 mask = Byte::GetMask(space_begin, space);

		for (int j = answer_index; j < m_Answer.size(); j++)
		{
			int answer_begin = answer_index;
			int answer_end = j;

			if (!CheckSpacing(space + 1, answer_begin, answer_end))
			{
				continue;
			}

			Int64 overlap_select = mask;
			Int64 overlap_block = Byte::EMPTY;

			OverlapTile(
				space_begin,
				space_end,
				answer_begin,
				answer_end,
				Byte::EMPTY,
				mask,
				overlap_select,
				overlap_block);

			Search(i + 2, j + 1, (select | overlap_select) & ~m_Block, block | overlap_block);
		}

		if ((mask & m_Select) != 0)
		{
			break;
		}
	}
}

bool Hint::CheckSpacing(int space, int answer_begin, int answer_end)
{
	for (int i = answer_begin; i < answer_end; i++)
	{
		if (m_Answer[i] + 1 <= space)
		{
			space -= m_Answer[i] + 1;
		}
		else
		{
			return false;
		}
	}
	return m_Answer[answer_end] <= space;
	//return AnswerTotalSize(answer_begin, answer_end) <= space;
}

void Hint::OverlapTile(
	int space_begin, int space_end,
	int answer_begin, int answer_end,
	Int64 crnt, Int64 mask,
	Int64& select, Int64& block)
{
	int totalsize = AnswerTotalSize(answer_begin, answer_end);
	int space_part_end = space_end - totalsize;

	if (space_begin > space_part_end)
	{
		return;
	}

	if (answer_begin < answer_end)
	{
		for (int i = space_begin; i <= space_part_end; i++)
		{
			OverlapTile(
				i + m_Answer[answer_begin] + 1,
				space_end,
				answer_begin + 1,
				answer_end,
				crnt | Byte::GetMask(i, m_Answer[answer_begin] - 1),
				mask,
				select,
				block);
		}
	}
	else
	{
		for (int i = space_begin; i <= space_part_end; i++)
		{
			Int64 result = crnt | Byte::GetMask(i, m_Answer[answer_begin] - 1);

			if ((m_Select & ~result & mask) == 0)
			{
				select &= result;
				block |= result;
			}
		}
	}
}

int Hint::AnswerTotalSize(int answer_start, int answer_end)
{
	int totalsize = 0;
	for (int i = answer_start; i < answer_end - 1; i++)
	{
		totalsize += m_Answer[i] + 1;
	}
	return totalsize + m_Answer[answer_end];
}

void Hint::OverlapHint(Int64 select, Int64 block)
{
	m_Written = true;
	SelectHint &= select;
	BlockHint |= block;
}

void Hint::WriteHint()
{
	if (m_Written)
	{
		SelectHint = SelectHint ^ m_Select;
		BlockHint = (~BlockHint ^ m_Block);
	}
	else
	{
		SelectHint = Byte::EMPTY;
		BlockHint = Byte::EMPTY;
	}
}