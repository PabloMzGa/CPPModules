/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:09:15 by pablo             #+#    #+#             */
/*   Updated: 2026/05/15 19:39:35 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: Revisar todo y asegurarse que está limpio, terminar la lógica de
//process input

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

static std::string trim(const std::string &s)
{
	std::size_t start = 0;
	while (start < s.size() &&
	       std::isspace(static_cast<unsigned char>(s[start])))
		++start;
	std::size_t end = s.size();
	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
		--end;
	return s.substr(start, end - start);
}

static bool is_valid_date(const std::string &date)
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (std::size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}
	std::stringstream ss(date);
	int year, month, day;
	char d1, d2;
	ss >> year >> d1 >> month >> d2 >> day;
	if (ss.fail())
		return false;
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	return true;
}

void BitcoinExchange::throw_error(BitcoinExchange::ErrorCode code, const std::string &detail)
{
	std::string msg;
	switch (code)
	{
		case BitcoinExchange::InvalidHeader:
			msg = "invalid header";
			break;
		case BitcoinExchange::InvalidStructure:
			msg = "invalid structure";
			break;
		case BitcoinExchange::InvalidFields:
			msg = "invalid fields";
			break;
		case BitcoinExchange::ParseValue:
			msg = "error parsing value";
			break;
		case BitcoinExchange::NegativeValue:
			msg = "negative value";
			break;
		case BitcoinExchange::MalformedDate:
			msg = "malformed date";
			break;
		case BitcoinExchange::FileOpen:
			msg = "Unable to open csv file";
			break;
		case BitcoinExchange::DataNotLoaded:
			msg = "Data not loaded";
			break;
		case BitcoinExchange::InputOpen:
			msg = "Unable to open input file";
			break;
		case BitcoinExchange::TooLarge:
			msg = "too large a number";
			break;
		default:
			msg = detail.empty() ? "Unknown error" : detail;
			break;
	}
	if (!detail.empty() && (code != BitcoinExchange::FileOpen && code != BitcoinExchange::InputOpen && code != BitcoinExchange::DataNotLoaded && code != BitcoinExchange::TooLarge))
		msg += std::string(": ") + detail;
	throw std::runtime_error(msg);
}

/**
 * Generic line parser for delimited files. If `dest` is non-null the parsed
 * pair is inserted into the map; otherwise the parsed values are returned
 * through `out_key`/`out_value` and no insertion occurs.
 */
bool BitcoinExchange::parse_delimited_line(const std::string &line,
                                           std::string &out_key,
                                           float &out_value,
                                           unsigned int n_line, char separator,
                                           const std::string &header,
                                           std::map<std::string, float> *dest)
{
	std::string trimmed = trim(line);

	if (n_line == 0)
	{
		if (trimmed != header)
		{
			throw_error(InvalidHeader, "");
		}
		return true;
	}

	if (std::count(line.begin(), line.end(), separator) != 1)
		{
			throw_error(InvalidStructure, "");
		}

	std::stringstream ss(line);
	std::string k, v;
	if (!std::getline(ss, k, separator) || !std::getline(ss, v))
	{
		throw_error(InvalidStructure, "");
	}

	std::string key_trim = trim(k);
	std::string val_trim = trim(v);
	if (key_trim.empty() || val_trim.empty())
		{
		throw_error(InvalidFields, "");
	}

	// strict float parse
	std::stringstream vs(val_trim);
	float value;
	if (!(vs >> value))
	{
		throw_error(ParseValue, "");
	}
	std::string rem;
	if (vs >> rem)
	{
		throw_error(ParseValue, "");
	}
	if (value < 0)
	{
		throw_error(NegativeValue, "");
	}

	if (!is_valid_date(key_trim))
	{
		throw_error(MalformedDate, "");
	}

	out_key = key_trim;
	out_value = value;
	if (dest)
		(*dest)[out_key] = out_value;
	return true;
}

void BitcoinExchange::parse_csv(std::ifstream &file)
{
	std::string line;
	unsigned int line_counter = 0;
	std::string key;
	float value = 0.0f;

	while (std::getline(file, line))
	{
		try
		{
			parse_delimited_line(line, key, value, line_counter, ',',
			                     CSV_HEADER, &_data);
		}
		catch (const std::exception &e)
		{
			if (line_counter == 0)
				throw;
			std::string msg = e.what();
			std::cerr << "Error: " << msg << " => " << trim(line) << std::endl;
		}
		++line_counter;
	}
}

/**
 * @brief Parse a single input-format line (date | value) and return parsed
 * values without inserting into any map.
 */
bool BitcoinExchange::parse_input_line(const std::string &line,
                                       std::string &out_key, float &out_value,
                                       unsigned int n_line)
{
	return parse_delimited_line(line, out_key, out_value, n_line, '|',
	                            INPUT_HEADER, 0);
}

BitcoinExchange::BitcoinExchange(std::string data_path, std::string input_path)
{
	(void)input_path;
	std::ifstream data_file;
	try
	{
		data_file.open(data_path.c_str());
		if (!data_file.is_open())
			throw_error(FileOpen, "");
		parse_csv(data_file);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		_data = src._data;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

const std::map<std::string, float> &BitcoinExchange::getData() const
{
	return _data;
}

void BitcoinExchange::processInput(const std::string &input_path)
{
	std::ifstream file;
	std::string line;
	unsigned int line_counter = 0;
	float value = 0.0f;

	if (_data.empty())
	{
		std::cerr << "Error: Data not loaded" << std::endl;
		return;
	}

	file.open(input_path.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Unable to open input file" << std::endl;
		return;
	}

	while (std::getline(file, line))
	{
		std::string key;
		try
		{
				parse_input_line(line, key, value, line_counter);
		}
		catch (const std::exception &e)
		{
			if (line_counter == 0)
			{
				std::string msg = e.what();
				std::cerr << "Error: " << msg << std::endl;
				return;
			}
			std::string msg = e.what();
			if (msg.find("negative value") != std::string::npos)
				std::cerr << "Error: not a positive number. => " << trim(line)
						  << std::endl;
			else
				std::cerr << "Error: " << msg << " => " << trim(line)
						  << std::endl;
			++line_counter;
			continue;
		}

		if (value > 1000.0f)
		{
			std::cerr << "Error: too large a number. => " << trim(line) << std::endl;
			++line_counter;
			continue;
		}
		++line_counter;
	}
}
