#pragma once
///용어 설명
///빈 타일	: □
///Select	: ■
///Block	: Ⅹ

class Hint
{
public:
	//결과값입니다.
	Byte SelectHint;
	Byte BlockHint;
private:
	///입력값입니다.
	///m_Select		: 현재 Select값입니다.
	///m_Block		: 현재 Block값입니다.
	///m_Length		: 타일 길이입니다.
	///m_Answer		: 정답 배열입니다.
	Int64 m_Select;
	Int64 m_Block;
	int m_Length;
	vector<int> m_Answer;

	///빈 타일 배열입니다.
	vector<int> m_Spaces;

	///결과를 저장했는지 확인합니다.
	///결과가 저장되지 않으면 Error로 봅니다.
	bool m_Written;

public:
	Hint(Int64 select, Int64 block, int length, vector<int>& answer);

private:
	void Solve();

#pragma region [Answer]
	//정답이 유효한지 확인합니다.
	bool IsVaildAnswer();
	//정답의 합을 계산합니다.
	int AnswerTotalSize(int answer_start, int answer_end);
#pragma endregion

#pragma region [Space]
	//비어있는 공간을 재설정합니다.
	void UpdateSpaces();
	//비어있는 공간을 확인하고 가져옵니다.
	bool TryGetSpace(int& start, int& end);
	//비어있는 타일에 정답을 넣어봅니다.
	bool CheckSpacing(int space, int answer_begin, int answer_end);
#pragma endregion

#pragma region [Search]
	//DFS 알고리즘으로 검색합니다.
	//비어있는 타일에 정답을 채워보는 시도를 합니다.
	void Search(int space_index, int answer_index, Int64 select, Int64 block);

	//정답 크기와 비어있는 타일 크기를 비교하고
	//정답을 넣어본 뒤 결과를 저장합니다.
	void OverlapTile(
		int space_begin, int space_end,
		int answer_begin, int answer_end,
		Int64 crnt, Int64 mask,
		Int64& select, Int64& block);
#pragma endregion

#pragma region [Result]
	//중간 결과를 기록합니다.
	void OverlapHint(Int64 select, Int64 block);

	//최종 결과를 기록합니다.
	//기록시 현재 타일을 제외하여 기록됩니다.
	void WriteHint();
#pragma endregion
};