#pragma once

class Byte
{
#pragma region [Constructor]
public:
	Byte();
	Byte(Int64);
#pragma endregion

#pragma region [Class Def]
private:
	class BitReference
	{
	private:
		Int64& m_Value;
		int m_Index;

	public:
		BitReference(Int64& value, int index) : m_Value(value), m_Index(index)
		{

		}

		operator bool() const
		{
			return (m_Value >> m_Index) & 1ULL;
		}

		BitReference& operator=(bool value)
		{
			if (value)
			{
				m_Value |= (1ULL << m_Index);
			}
			else
			{
				m_Value &= ~(1ULL << m_Index);
			}
			return *this;
		}
	};
#pragma endregion

#pragma region [Constant]
public:
	static const Int64 LENGTH = 64;
	static const Int64 EMPTY = 0;
	static const Int64 FILL = 18446744073709551615ULL;
	static const Int64 PLUSTABLE[];
	static const Int64 MINUSTABLE[];
#pragma endregion

#pragma region [Field]
private:
	Int64 m_Value = 0;
#pragma endregion

#pragma region [Method]
public:
	bool IsValid();
	bool IsValid(int, int);

	static Int64 GetMask(int, int);
	static int FFSLL(Int64);
	static int FLSLL(Int64);

#pragma endregion

#pragma region [Operator]
public:
	operator Int64& ();
	BitReference operator[] (int);
	Byte& operator=(const Int64& value);
#pragma endregion
};
