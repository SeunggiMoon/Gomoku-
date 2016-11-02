#pragma once

#include <iostream>
#include <vector>

#include "Gomoku++.h"

class MTPEngine
{
public:
	enum CommandType
	{
		QUIT,
		NAME,
		VERSION,
		CLEAR_BOARD,
		PLAY,
		GENMOVE,
		COUNT_COMMANDS
	};
 
private:
	bool is_Run;
	int cmd_id;

	int color;

	Gomokupp* ai;

public:
	MTPEngine();
	~MTPEngine();

	void Run();

private:
	void _parse(const std::string& line);

	void _play(const std::vector<std::string>& args, std::string& response);
	void _genmove(std::string& response);

	CommandType _parse_command(const std::string& cmd);
	int _parse_color(const std::string& color);
	Point _parse_coordinate(const std::string& color);
};