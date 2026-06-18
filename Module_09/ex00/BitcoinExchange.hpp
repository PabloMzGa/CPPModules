/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:58:14 by pablo             #+#    #+#             */
/*   Updated: 2026/06/18 21:05:32 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

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

	void process_input(const std::string &input_path);

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

	static bool parse_delimited_line(const std::string &line,
	                                 std::string &out_key, float &out_value,
	                                 unsigned int n_line, char separator,
	                                 const std::string &header,
	                                 std::map<std::string, float> *dest = 0);

	static bool parse_input_line(const std::string &line, std::string &out_key,
	                             float &out_value, unsigned int n_line);
	std::map<std::string, float>::const_iterator
	get_closest_date(const std::string &key) const;
	void parse_csv(std::ifstream &file);
	std::map<std::string, float> _data;
};

#endif
