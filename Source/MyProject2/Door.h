#pragma once

#include "LevelDefines.h"

struct Door
{
	Coord m_local_pos;
	Cardinal_Direction m_local_dir;

	Door(Coord new_pos, Cardinal_Direction dir = CD_NORTH) :
		m_local_pos(new_pos),
		m_local_dir(dir),
		m_is_connected(false)
	{
	}

	bool IsConnected()				{ return m_is_connected; }
	void SetConnected(bool val)		{ m_is_connected = val; }

private:
	bool m_is_connected = false;

};