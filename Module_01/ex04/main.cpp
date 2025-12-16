/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:51:28 by pablo             #+#    #+#             */
/*   Updated: 2025/12/15 20:42:34 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

/**
 * @brief Reads the entire contents of a file into a string.
 *
 * This function attempts to open the specified file and read its entire
 * contents into the provided string reference. If the file cannot be opened,
 * the function returns false without modifying the content string.
 *
 * @param filename The path to the file to be read.
 * @param content A reference to a string where the file contents will be
 * stored.
 * @return true if the file was successfully read, false otherwise.
 */
bool read_file(const std::string &filename, std::string &content)
{
	std::ifstream infile(filename.c_str());
	if (!infile.is_open())
		return (false);
	content.assign((std::istreambuf_iterator<char>(infile)),
	               std::istreambuf_iterator<char>());
	infile.close();
	return (true);
}

/**
 * @brief Writes the given content to a file.
 * @param filename The name of the file to write to.
 * @param content The string content to write into the file.
 * @return true if the file was successfully opened and written to, false otherwise.
 */
bool write_file(const std::string &filename, const std::string &content)
{
	std::ofstream outfile(filename.c_str());
	if (!outfile.is_open())
		return (false);
	outfile << content;
	outfile.close();
	return (true);
}

/**
 * @brief Replaces all occurrences of a substring in a string with another substring.
 *
 * This function searches for all instances of the substring `s1` within the input string `content`
 * and replaces each occurrence with the substring `s2`. It returns a new string with all replacements made.
 *
 * @param content The original string in which replacements are to be made.
 * @param s1 The substring to be replaced.
 * @param s2 The substring to replace `s1` with.
 * @return A new string with all occurrences of `s1` replaced by `s2`.
 *
 * @note If `s1` is an empty string, the function will insert `s2` at every position in `content`,
 *       which may lead to unexpected behavior. Ensure `s1` is not empty for intended use.
 * @note This function does not modify the original `content` string; it returns a new string.
 */
std::string replace_all(const std::string &content, const std::string &s1,
                        const std::string &s2)
{
	std::string result;
	size_t last_position = 0;
	size_t find_position = 0;
	while ((find_position = content.find(s1, find_position)) != std::string::npos)
	{
		result += content.substr(last_position, find_position - last_position);
		result += s2;
		find_position += s1.length();
		last_position = find_position;
	}
	result += content.substr(last_position);
	return (result);
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "Only 3 arguments allowed!" << std::endl;
		return (1);
	}
	std::string infile_name(argv[1]);
	std::string file_contents;
	if (!read_file(infile_name, file_contents))
	{
		std::cout << "Error opening file. Aborting" << std::endl;
		return (1);
	}
	if (file_contents.empty())
	{
		std::cout << "Error reading file contents. Aborting" << std::endl;
		return (1);
	}
	std::string s1(argv[2]);
	std::string s2(argv[3]);
	if (s1.empty())
	{
		std::cout << "Cannot replace empty string. Aborting" << std::endl;
		return (1);
	}
	std::string outfile_name = infile_name + ".replace";
	std::string result = replace_all(file_contents, s1, s2);
	if (!write_file(outfile_name, result))
	{
		std::cout << "Error opening replace file. Aborting" << std::endl;
		return (1);
	}
	return (0);
}
