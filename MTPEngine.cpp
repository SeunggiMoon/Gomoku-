
#include "MTPEngine.h"

#include <string>
#include <algorithm>

void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ")
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

static const std::string COMMANDS[MTPEngine::COUNT_COMMANDS] = {
	"quit", "name", "version", "clear_board", "play", "genmove"
};
 
MTPEngine::MTPEngine() : is_Run(false), cmd_id(0), color(0)
{
	ai = new Gomokupp;
} 

MTPEngine::~MTPEngine()
{
	delete ai;
}

void MTPEngine::Run()
{
	is_Run = true;

	while (is_Run)
	{
		std::string line;
		std::getline(std::cin, line);

		_parse(line);
	}
}

void MTPEngine::_parse(const std::string& line)
{
	if (line.empty())
	{
		is_Run = false;
		return;
	}

	std::vector<std::string> tokens;
	Tokenize(line, tokens);

	CommandType cmd = _parse_command(tokens[0]);
	std::vector<std::string> args(tokens.begin() + 1, tokens.end());

	std::string response = "=";
	cmd_id++;
	response.append(std::to_string(cmd_id) + " ");

	switch (cmd)
	{
	case CommandType::QUIT:
		is_Run = false;
		break;

	case CommandType::NAME:
		response.append("Gomoku++");
		break;

	case CommandType::VERSION:
		response.append("2.0");
		break;

	case CommandType::CLEAR_BOARD:

		break;

	case CommandType::PLAY:
		_play(args, response);
		break;

	case CommandType::GENMOVE:
		_genmove(response);
		break;
	}

	response.append("\n\n");
	std::cout << response;
}

void MTPEngine::_play(const std::vector<std::string>& args, std::string& response)
{
	if (color == 0) color = 2;

	if (args.size() > 1)
	{
		int color = _parse_color(args[0]);
		Point coord = _parse_coordinate(args[1]);

		if (color > -1 && coord.X >= -1 && coord.Y >= -1)
		{
			if (coord.X > -1 && coord.Y > -1)
			{
				ai->Move(coord, color);

				response.append("setmove");
			}
		}
		else
		{
			response[0] = '?';
			response.append("invalid color or coordinate");
		}
	}
	else
	{
		response[0] = '?';
		response.append("syntax error");
	}
}

void MTPEngine::_genmove(std::string& response)
{
	if (color == 0) color = 1;

	Point pt = ai->GetMove();
	ai->Move(pt, color);

	const std::string pos_list("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	response.append("play ");
	response.append((color == 1) ? "b " : "w ");
	response += pos_list[pt.X];
	response.append(std::to_string(pt.Y));
}

MTPEngine::CommandType MTPEngine::_parse_command(const std::string& cmd)
{
	std::string str = cmd;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	for (int i = 0; i < COUNT_COMMANDS; i++)
	{
		if (COMMANDS[i] == str)
			return (CommandType)i;
	}

	return (CommandType)-1;
}

int MTPEngine::_parse_color(const std::string & color)
{
	std::string str = color;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	if (str == "black" || str == "b") return 1; // Black
	else if (str == "white" || str == "w") return 0; // White
	else return -1; // Err
}

Point MTPEngine::_parse_coordinate(const std::string & coord)
{
	std::string str = coord;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	if (str == "pass") return{ -1, -1 };

	const std::string pos_list("abcdefghijklmnopqrstuvwxyz");

	return Point((int)pos_list.find(str[0]),
		(int)14 - atoi(std::string(str.begin() + 1, str.end()).c_str()));
}