#include "stdafx.h"
#include "json.h"
#include <sstream>
#include <iostream>

json::json()
{
}


json::~json()
{
}

json* json::addSimpleField(std::string tagName, std::string value)
{
	this->simpleStringFields.insert(std::pair<std::string, std::string>(tagName, value));
	return this;
}
json* json::addSimpleField(std::string tagName, int value)
{
	this->simpleIntFields.insert(std::pair<std::string, int>(tagName, value));
	return this;
}
json* json::addComplexField(std::string tagName)
{
	json* child = new json();
	this->complexFields.insert(std::pair<std::string, json*>(tagName, child));
	return child;
}
json* json::addJsonArray(std::string tagName, std::vector<std::string> &array)
{
	json* child = new json();
	this->arrayFields.insert(std::pair<std::string, std::vector<std::string>>(tagName, array));
	return child;
}
json * json::addJsonArray(std::string tagName, std::vector<json>& arrayObject)
{
	json* child = new json();
	this->arrayObjectFields.insert(std::pair<std::string, std::vector<json>>(tagName, arrayObject));
	return child;
}

std::string json::serialize()
{
	std::string readStrings = "{";
	readStrings += writeString();
	readStrings += writeInt();
	readStrings += writeArray();
	readStrings += writeComplex();
	readStrings += writeArrayObject();
	readStrings += "}";
	return readStrings;
}

std::string json::writeString()
{
	std::string myJson = "";
	std::string repeatedTag = "";
	int counter = 0;
	bool isFirst = true;

	std::map<std::string, std::string>::iterator simpleIter;
	for (simpleIter = this->simpleStringFields.begin(); simpleIter != this->simpleStringFields.end(); ++simpleIter)
	{
		if (counter == 0)
			repeatedTag = simpleIter->first;

		if (!isFirst && repeatedTag != simpleIter->first)   //If there is nothing before this string don't add comma, if there is, separate with comma
			myJson += ",";
		myJson += "\"" + simpleIter->first + "\": \"" + simpleIter->second + "\"";

		isFirst = false;
		counter++;
		if (simpleStringFields.count(simpleIter->first) > 1 && repeatedTag == simpleIter->first && counter != simpleStringFields.size())
			myJson += "},{";
	}
	return myJson;
}

std::string json::writeInt()
{
	std::string myJson = "";
	int counter = 0;
	std::string repeatedTag = "";
	bool isFirst;
	
	if (!simpleStringFields.empty())   //If there is string before this int map, add comma
		isFirst = false;
	else 
		isFirst = true;

	std::map<std::string, int>::iterator simpleIntIter;
	for (simpleIntIter = this->simpleIntFields.begin(); simpleIntIter != this->simpleIntFields.end(); ++simpleIntIter)
	{
		std::stringstream ss;
		ss << simpleIntIter->second;
		std::string newString = ss.str();

		if (counter == 0)
			repeatedTag = simpleIntIter->first;

		if (!isFirst)   //If there is nothing before this string don't add comma, if there is, separate with comma
			myJson += ",";
		myJson += "\"" + simpleIntIter->first + "\": " + newString;

		if (simpleIntFields.count(simpleIntIter->first) > 1)   //If it's an object list, don't add comma every time
			isFirst = true;
		else
			isFirst = false;

		counter++;

		if (simpleIntFields.count(simpleIntIter->first) > 1 && repeatedTag == simpleIntIter->first && counter != simpleIntFields.size())
			myJson += "},{";
	}
	return myJson;
}

std::string json::writeArray()
{
	std::string myJson = "";
	bool isFirst;

	if (!simpleStringFields.empty() || !simpleIntFields.empty())   //If there is maps before array map add comma
		isFirst = false;
	else
		isFirst = true;

	std::map<std::string, std::vector<std::string>>::iterator arrayIter;
	for (arrayIter = this->arrayFields.begin(); arrayIter != this->arrayFields.end(); ++arrayIter)
	{
		if (!isFirst)   //If there is nothing before this string don't add comma, if there is, separate with comma
			myJson += ",";
		myJson += "\"" + arrayIter->first + "\": [";
		std::vector<std::string>::iterator ptr;
		for (ptr = arrayIter->second.begin(); ptr < arrayIter->second.end(); ptr++) {
			myJson += "\"" + *ptr + "\",";
			if (ptr == std::prev(arrayIter->second.end()))
			{
				myJson = myJson.substr(0, myJson.size() - 1);   //delete last comma
				myJson += "]";
			}
			isFirst = false;
		}
		if (arrayIter->second.empty())
			myJson += "]";
	}
	return myJson;
}

std::string json::writeArrayObject()
{
	std::string myJson = "";
	bool isFirst;

	if (!simpleStringFields.empty() || !simpleIntFields.empty() || !arrayFields.empty() || !complexFields.empty())   //If there is maps before array map add comma
		isFirst = false;
	else
		isFirst = true;

	std::map<std::string, std::vector<json>>::iterator arrayObjectIter;
	for (arrayObjectIter = this->arrayObjectFields.begin(); arrayObjectIter != this->arrayObjectFields.end(); ++arrayObjectIter)
	{
		if (!isFirst)   //If there is nothing before this string don't add comma, if there is, separate with comma
			myJson += ",";
		myJson += "\"" + arrayObjectIter->first + "\": [";
		
		std::vector<json>::iterator ptr;
		for (ptr = arrayObjectIter->second.begin(); ptr < arrayObjectIter->second.end(); ptr++) {
			myJson += ptr->serialize() + ",";
			isFirst = false;

			if (ptr == std::prev(arrayObjectIter->second.end()))
			{
				myJson = myJson.substr(0, myJson.size() - 1);   //delete last comma
				myJson += "]";
			}
		}

		if(arrayObjectIter->second.empty())
			myJson += "]";
	}
	return myJson;
}

std::string json::writeComplex()
{
	std::string myJson = "";
	bool isFirst;
	
	if (!simpleStringFields.empty() || !simpleIntFields.empty() || !arrayFields.empty())   //If there is maps before complex map add comma
		isFirst = false;
	else
		isFirst = true;
		
	std::map<std::string, json*>::iterator complexIter;
	for (complexIter = this->complexFields.begin(); complexIter != this->complexFields.end(); ++complexIter)
	{
		if (!isFirst)
			myJson += ",";   //If there is nothing before this string don't add comma, if there is, separate with comma
		myJson += "\"" + complexIter->first + "\": ";
		myJson += complexIter->second->serialize();   //Complex tag's value could be different types so call the function again
		isFirst = false;
	}
	return myJson;
}