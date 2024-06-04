#include "Score.h"

bool Score::operator>(const Score& s) const
{
	bool greater = false;

	if (m_points > s.getPoints())
	{
		greater = true;
	}

	return greater;
}