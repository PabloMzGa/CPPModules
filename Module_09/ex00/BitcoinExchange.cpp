/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:09:15 by pablo             #+#    #+#             */
/*   Updated: 2026/05/20 21:14:59 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// ORTHODOX ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Builds an empty exchange database.
 */
BitcoinExchange::BitcoinExchange() {}

/**
 * @brief Copies the internal exchange-rate map from another instance.
 * @param src Source object.
 */
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
: _data(src._data)
{
}

/**
 * @brief Assigns the internal exchange-rate map from another instance.
 * @param src Source object.
 * @return Reference to this object.
 */
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		_data = src._data;
	}
	return *this;
}

/**
 * @brief Destroys the exchange object.
 */
BitcoinExchange::~BitcoinExchange() {}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// HELPERS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Removes leading and trailing whitespace from a string.
 * @param s Input string.
 * @return Trimmed copy of the input string.
 */
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

/**
 * @brief Checks whether a string matches the expected `YYYY-MM-DD` format.
 * @param date Date string to validate.
 * @return `true` if the format is valid, `false` otherwise.
 */
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

/**
 * @brief Throws a runtime error associated with a class error code.
 *
 * The helper centralizes every parser and loader error so the rest of the
 * implementation only needs to choose an error category and provide optional
 * context. The message is normalized before the exception is thrown.
 * @param code Error code that determines the message.
 * @param detail Extra context appended to the message when relevant.
 */
void BitcoinExchange::throw_error(BitcoinExchange::ErrorCode code,
                                  const std::string &detail)
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
	if (!detail.empty() && (code != BitcoinExchange::FileOpen &&
	                        code != BitcoinExchange::InputOpen &&
	                        code != BitcoinExchange::DataNotLoaded &&
	                        code != BitcoinExchange::TooLarge))
		msg += std::string(": ") + detail;
	throw std::runtime_error(msg);
}

/**
 * @brief Parses a delimited record and optionally stores it in a map.
 *
 * The parser is strict: it requires exactly one separator, trims both fields,
 * validates the date key, and parses the numeric value without trailing
 * garbage. It is shared by both the CSV loader and the user input parser so
 * the two file formats follow the same validation rules.
 * @param line Raw line to parse.
 * @param out_key Parsed key output.
 * @param out_value Parsed value output.
 * @param n_line Current line index.
 * @param separator Field separator.
 * @param header Expected header at line zero.
 * @param dest Optional destination map.
 * @return `true` if parsing succeeded.
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

/**
 * @brief Reads the CSV file and loads entries into `_data`.
 *
 * The first line is validated as the header, then each following record is
 * parsed with the shared delimited-line parser. Bad data rows do not abort the
 * load; instead, they are reported and skipped so the usable rates remain
 * available.
 * @param file Open CSV input stream.
 */
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
 * @brief Finds the exact or nearest lower date in the database.
 * @param key Date to search.
 * @return Iterator to the best matching entry, or `end()` if none exists.
 */
std::map<std::string, float>::const_iterator
BitcoinExchange::getClosestRate(const std::string &key) const
{
	std::map<std::string, float>::const_iterator it = _data.lower_bound(key);
	if (it != _data.end() && it->first == key)
		return it;
	if (it == _data.begin())
		return _data.end();
	if (it == _data.end())
		return --it;
	return --it;
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// WRAPPERS ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Parses a line from the input file format.
 *
 * This wrapper enforces the `date | value` layout used by the exercise input
 * file and delegates the actual validation to the generic parser.
 * @param line Raw line to parse.
 * @param out_key Parsed date output.
 * @param out_value Parsed amount output.
 * @param n_line Current line index.
 * @return `true` if parsing succeeded.
 */
bool BitcoinExchange::parse_input_line(const std::string &line,
                                       std::string &out_key, float &out_value,
                                       unsigned int n_line)
{
	return parse_delimited_line(line, out_key, out_value, n_line, '|',
	                            INPUT_HEADER);
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Loads the CSV database from the provided path.
 *
 * The constructor opens the historical-price file, validates it, and loads the
 * resulting rates into the internal map so the object is ready for lookups.
 * @param data_path Path to the CSV exchange-rate file.
 */
BitcoinExchange::BitcoinExchange(std::string data_path)
{
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

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// PUBLIC MEMBERS ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Processes an input file and prints the converted values.
 *
 * The function reads the file line by line, validates the header, rejects
 * malformed or out-of-range values, looks up the closest rate for each valid
 * date, and prints the conversion result. Errors are reported per line so a
 * single bad entry does not prevent the rest of the file from being processed.
 * @param input_path Path to the input file.
 */
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
			std::cerr << "Error: " << msg << " => " << trim(line) << std::endl;
			++line_counter;
			continue;
		}

		if (value > 1000.0f)
		{
			std::cerr << "Error: too large a number => " << trim(line)
			          << std::endl;
			++line_counter;
			continue;
		}
		if (line_counter > 0)
		{
			std::map<std::string, float>::const_iterator rate =
			    getClosestRate(key);
			if (rate == _data.end())
			{
				std::cerr << "Error: no rate available for date => " << key
				          << std::endl;
				continue;
			}
			std::cout << key << " => " << value << " = " << value * rate->second
			          << std::endl;
		}
		++line_counter;
	}
}
