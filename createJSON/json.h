#pragma once

#include <map>
#include <vector>

class json
{
private:

	std::multimap<std::string, std::string> simpleStringFields;
	std::multimap<std::string, int> simpleIntFields;
	std::map<std::string, json*> complexFields;
	std::map<std::string, std::vector<std::string>> arrayFields;
	std::map<std::string, std::vector<json>> arrayObjectFields;

public:
	json();
	~json();

	std::string serialize();
	std::string writeString();
	std::string writeInt();
	std::string writeArray();
	std::string writeArrayObject();
	std::string writeComplex();

	json* addComplexField(std::string tagName);
	json* addSimpleField(std::string tagName, std::string value);
	json* addSimpleField(std::string tagName, int value);
	json* addJsonArray(std::string tagName, std::vector<std::string> &array);
	json* addJsonArray(std::string tagName, std::vector<json> &arrayObject);
};

