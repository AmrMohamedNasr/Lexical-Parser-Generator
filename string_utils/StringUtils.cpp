/*
 * StringUtils.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include "StringUtils.h"
#include <sstream>

vector<string> split_spaces(string str) {
	string buf;
	stringstream ss(str);
	vector<string> tokens;
	while (ss >> buf) {
		tokens.push_back(buf);
	}
	return tokens;
}

string handle_file_name_extension(string file_name, string ext) {
	if (file_name.size() > 3 && file_name.substr(file_name.size() - 4) == ".txt") {
		return (file_name.substr(0, file_name.size() - 4) + "." + ext);
	} else {
		return file_name + "." + ext;
	}
}
