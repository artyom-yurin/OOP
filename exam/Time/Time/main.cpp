#include <string>
#include <sstream>
#include <iostream>

using namespace std;

void Normalize(int & hours, int & minutes, int & seconds)
{
	if ((hours < 0) || (minutes < 0) || (seconds < 0))
	{
		if (seconds < 0)
		{
			seconds += 60;
			--minutes;
		}
		if (minutes < 0)
		{
			minutes += 60;
			--hours;
		}
		if (hours < 0)
		{
			hours += 24;
		}
	}
	else
	{
		minutes += seconds / 60;
		seconds = seconds % 60;
		hours += minutes / 60;
		minutes = minutes % 60;
		hours = hours % 24;
	}
}

class CTime
{
public:
	// Конструирует время (чч:мм:сс). 
	// Если часы, минуты, или секунды выходят за пределы 23:59:59, бросает
	// исключение invalid_argument
	CTime(int hours, int minutes, int seconds)
	{
		if ((hours > 23) || (minutes > 59) || (seconds > 59))
		{
			throw std::invalid_argument("One or more value out of the top border");
		}
		if ((hours < 0) || (minutes < 0) || (seconds < 0))
		{
			throw std::invalid_argument("values can not be negative");
		}
		m_seconds = seconds;
		m_minutes = minutes;
		m_hours = hours;
	}

	// Возвращает количество часов (0..23)
	int GetHours()const
	{
		return m_hours;
		// Написать  недостающий код
	}

	// Возвращает количество минут (0..59)
	int GetMinutes()const
	{
		return m_minutes;
		// Написать  недостающий код
	}

	// Возвращает количество секунд (0..59)
	int GetSeconds()const
	{
		return m_seconds;
		// Написать  недостающий код
	}

	// Возвращает строковое представление времени в формате чч:мм:сс
	string ToString()const
	{
		std::stringstream result;
		result << (m_hours <= 9 ? "0" : "")
			<< m_hours
			<< ":"
			<< (m_minutes <= 9 ? "0": "")
			<< m_minutes
			<< ":"
			<< (m_seconds <= 9 ? "0": "")
			<< m_seconds;
		return result.str();
	}

	const CTime operator+=(const CTime & summand)
	{
		int hours = GetHours() + summand.GetHours();
		int minutes = GetMinutes() + summand.GetMinutes();
		int seconds = GetSeconds() + summand.GetSeconds();
		Normalize(hours, minutes, seconds);
		m_hours = hours;
		m_minutes = minutes;
		m_seconds = seconds;
		return *this;
	}

	const CTime operator-=(const CTime & subtrahend)
	{
		int hours = GetHours() - subtrahend.GetHours();
		int minutes = GetMinutes() - subtrahend.GetMinutes();
		int seconds = GetSeconds() - subtrahend.GetSeconds();
		Normalize(hours, minutes, seconds);
		m_hours = hours;
		m_minutes = minutes;
		m_seconds = seconds;
		return *this;
	}

private:
	int m_seconds;
	int m_minutes;
	int m_hours;
};

const CTime operator+(const CTime & lhs, const CTime & rhs)
{
	int hours = lhs.GetHours() + rhs.GetHours();
	int minutes = lhs.GetMinutes() + rhs.GetMinutes();
	int seconds = lhs.GetSeconds() + rhs.GetSeconds();
	Normalize(hours, minutes, seconds);
	return CTime(hours, minutes, seconds);
}

const CTime operator-(const CTime & lhs, const CTime & rhs)
{
	int hours = lhs.GetHours() - rhs.GetHours();
	int minutes = lhs.GetMinutes() - rhs.GetMinutes();
	int seconds = lhs.GetSeconds() - rhs.GetSeconds();
	Normalize(hours, minutes, seconds);
	return CTime(hours, minutes, seconds);
}

std::ostream & operator<<(std::ostream & output, const CTime & value)
{
	output << value.ToString();
	return output;
}

/*
Реализовать методы класса и перечисленные ниже операции. Сложение и вычитание выполняется в пределах суток
Примеры:
+	складывает временные интервалы: 23:59:17 + 01:12:13 -> 01:11:30
-	вычитает временные интервалы: 00:15:25 - 01:16:25 -> 22:59:00
+=	a += b аналогично a = a + b
-=	a -= b аналогично a = a - b
<<	выводит время в заданный ostream в формает чч:мм:сс
*/

int main()
{
	CTime fTime(23, 59, 17);
	CTime sTime(1, 12, 13);
	std::cout << fTime + sTime << "\n";
	fTime += sTime;
	std::cout << fTime << "\n";
	CTime tTime(0, 15, 25);
	CTime foTime(1, 16, 25);
	std::cout << tTime - foTime << "\n";
	tTime -= foTime;
	std::cout << tTime<< "\n";
	std::cout << foTime - foTime << "\n";
	/*

	*/
	return 0;
}