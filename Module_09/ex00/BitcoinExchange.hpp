/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:58:14 by pablo             #+#    #+#             */
/*   Updated: 2026/05/19 18:33:10 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <stdexcept>

#define CSV_HEADER "date,exchange_rate"
#define INPUT_HEADER "date | value"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange(std::string data_path);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();

		void processInput(const std::string &input_path);

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
