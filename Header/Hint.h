#pragma once

class Hint
{
public:
	Byte SelectHint;
	Byte BlockHint;

private:
	Int64 m_Select;
	Int64 m_Block;
	int m_Length;
	vector<int> m_Answer;
	vector<int> m_Spaces;
	bool m_Written;

public:
	Hint(Int64 select, Int64 block, int length, vector<int>& answer);

private:
	void UpdateSpaces();
	void Solve();

	void Search(int space_index, int answer_index, Int64 select, Int64 block);
	void OverlapTile(
		int space_begin, int space_end,
		int answer_begin, int answer_end,
		Int64 crnt, Int64 mask,
		Int64& select, Int64& block);

	void OverlapHint(Int64 select, Int64 block);
	void WriteHint();
	
	bool TryGetSpace(int& start, int& end);
	bool IsVaildAnswer();
	bool CheckSpacing(int space, int answer_begin, int answer_end);
	int AnswerTotalSize(int answer_start, int answer_end);
};