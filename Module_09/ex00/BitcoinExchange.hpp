/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:58:14 by pablo             #+#    #+#             */
/*   Updated: 2026/05/19 17:54:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <stdexcept>

/* Error codes and helpers are declared inside the class to keep the header
   limited to the class declaration only. Definitions are in the .cpp file. */

#define CSV_HEADER "date,exchange_rate"
#define INPUT_HEADER "date | value"

/**
 * @class BitcoinExchange
 * @brief Loads a CSV exchange-rate database and provides input processing.
 *
 * The two-argument constructor loads only the CSV database from `data_path`
 * into the internal `_data` map. The `input_path` parameter is accepted for
 * API compatibility but is not parsed at construction time; call
 * `processInputFile` to process an input file on demand.
 *
 * This class targets portability to older compilers (C++98 compatible
 * parsing) so it uses `std::stringstream` for strict numeric parsing.
 */
class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange(std::string data_path, std::string input_path);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();

		void processInput(const std::string &input_path);
		const std::map<std::string, float> &getData() const;

	private:
		enum ErrorCode
		{
			OK = 0,
			InvalidHeader,
			InvalidStructure,
			InvalidFields,
			ParseValue,
			NegativeValue,
			MalformedDate,
			FileOpen,
			DataNotLoaded,
			InputOpen,
			TooLarge,
			Unknown
		};

		static void throw_error(ErrorCode code, const std::string &detail);

		static bool parse_delimited_line(const std::string &line, std::string &out_key,
							 float &out_value, unsigned int n_line,
							 char separator, const std::string &header,
							 std::map<std::string, float> *dest = 0);

		static bool parse_input_line(const std::string &line, std::string &out_key,
							 float &out_value, unsigned int n_line);
		std::map<std::string, float>::const_iterator
		getClosestRate(const std::string &key) const;
		void parse_csv(std::ifstream &file);
		std::map<std::string, float> _data;

};

#endif
