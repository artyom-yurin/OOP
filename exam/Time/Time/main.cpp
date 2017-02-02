#include <string>
#include <iostream>
using namespace std;

std::string FormatNumber(int number)
{
	return (number <= 9 ? "0" + std::to_string(number) : std::to_string(number));
}

class CTime
{
public:
	// ������������ ����� (��:��:��). 
	// ���� ����, ������, ��� ������� ������� �� ������� 23:59:59, �������
	// ���������� invalid_argument
	explicit CTime(int timeStamp)
	{
		if (timeStamp >= 86400 || timeStamp < 0)
		{
			throw std::invalid_argument("Timestamp must be from 0 to 86399");
		}
		m_timeStamp = timeStamp;
	}

	CTime(int hours, int minutes, int seconds)
	{
		if ((hours > 23) || (hours < 0))
		{
			throw std::invalid_argument("Hours must be from 0 to 23");
		}
		if ((minutes > 59) || (minutes < 0))
		{
			throw std::invalid_argument("Minutes must be from 0 to 59");
		}
		if ((seconds > 59) || (seconds < 0))
		{
			throw std::invalid_argument("Seconds must be from 0 to 59");
		}
		m_timeStamp = hours * 3600 + minutes * 60 + seconds;
	}

	// ���������� ���������� ����� (0..23)
	int GetHours()const
	{
		return m_timeStamp / 3600;
		// ��������  ����������� ���
	}

	// ���������� ���������� ����� (0..59)
	int GetMinutes()const
	{
		return (m_timeStamp % 3600) / 60;
		// ��������  ����������� ���
	}

	// ���������� ���������� ������ (0..59)
	int GetSeconds()const
	{
		return m_timeStamp % 60;
		// ��������  ����������� ���
	}

	// ���������� ��������� ������������� ������� � ������� ��:��:��
	string ToString()const
	{
		std::string hours = FormatNumber(GetHours());
		std::string minutes = FormatNumber(GetMinutes());
		std::string seconds = FormatNumber(GetSeconds());
		return{
			hours + ":" + minutes + ":" + seconds
		};
	}

	int GetTimeStamp()const
	{
		return m_timeStamp;
	}

	const CTime operator+=(const CTime & summand)
	{
		m_timeStamp = (m_timeStamp + summand.m_timeStamp) % (24 * 60 * 60);
		return *this;
	}

	const CTime operator-=(const CTime & subtrahend)
	{
		m_timeStamp = (m_timeStamp - subtrahend.m_timeStamp + (24 * 60 * 60)) % (24 * 60 * 60);
		return *this;
	}

private:
	int m_timeStamp = 0;
};

const CTime operator+(const CTime & lhs, const CTime & rhs)
{
	return CTime((lhs.GetTimeStamp() + rhs.GetTimeStamp()) % (24 * 60 * 60));
}

const CTime operator-(const CTime & lhs, const CTime & rhs)
{
	return CTime((lhs.GetTimeStamp() - rhs.GetTimeStamp() + (24 * 60 * 60)) % (24 * 60 * 60));
}

std::ostream & operator<<(std::ostream & output, const CTime & time)
{
	output << time.ToString();
	return output;
}

/*
����������� ������ ������ � ������������� ���� ��������. �������� � ��������� ����������� � �������� �����
�������:
+	���������� ��������� ���������: 23:59:17 + 01:12:13 -> 01:11:30
-	�������� ��������� ���������: 00:15:25 - 01:16:25 -> 22:59:00
+=	a += b ���������� a = a + b
-=	a -= b ���������� a = a - b
<<	������� ����� � �������� ostream � ������� ��:��:��
*/

int main()
{
	return 0;
}