#pragma once
///��� ����
///�� Ÿ��	: ��
///Select	: ��
///Block	: ��

class Hint
{
public:
	//������Դϴ�.
	Byte SelectHint;
	Byte BlockHint;
private:
	///�Է°��Դϴ�.
	///m_Select		: ���� Select���Դϴ�.
	///m_Block		: ���� Block���Դϴ�.
	///m_Length		: Ÿ�� �����Դϴ�.
	///m_Answer		: ���� �迭�Դϴ�.
	Int64 m_Select;
	Int64 m_Block;
	int m_Length;
	vector<int> m_Answer;

	///�� Ÿ�� �迭�Դϴ�.
	vector<int> m_Spaces;

	///����� �����ߴ��� Ȯ���մϴ�.
	///����� ������� ������ Error�� ���ϴ�.
	bool m_Written;

public:
	Hint(Int64 select, Int64 block, int length, vector<int>& answer);

private:
	void Solve();

#pragma region [Answer]
	//������ ��ȿ���� Ȯ���մϴ�.
	bool IsVaildAnswer();
	//������ ���� ����մϴ�.
	int AnswerTotalSize(int answer_start, int answer_end);
#pragma endregion

#pragma region [Space]
	//����ִ� ������ �缳���մϴ�.
	void UpdateSpaces();
	//����ִ� ������ Ȯ���ϰ� �����ɴϴ�.
	bool TryGetSpace(int& start, int& end);
	//����ִ� Ÿ�Ͽ� ������ �־�ϴ�.
	bool CheckSpacing(int space, int answer_begin, int answer_end);
#pragma endregion

#pragma region [Search]
	//DFS �˰������� �˻��մϴ�.
	//����ִ� Ÿ�Ͽ� ������ ä������ �õ��� �մϴ�.
	void Search(int space_index, int answer_index, Int64 select, Int64 block);

	//���� ũ��� ����ִ� Ÿ�� ũ�⸦ ���ϰ�
	//������ �־ �� ����� �����մϴ�.
	void OverlapTile(
		int space_begin, int space_end,
		int answer_begin, int answer_end,
		Int64 crnt, Int64 mask,
		Int64& select, Int64& block);
#pragma endregion

#pragma region [Result]
	//�߰� ����� ����մϴ�.
	void OverlapHint(Int64 select, Int64 block);

	//���� ����� ����մϴ�.
	//��Ͻ� ���� Ÿ���� �����Ͽ� ��ϵ˴ϴ�.
	void WriteHint();
#pragma endregion
};