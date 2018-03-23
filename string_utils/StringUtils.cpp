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
