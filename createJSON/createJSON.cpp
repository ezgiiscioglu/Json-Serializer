// createJSON.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "json.h"

int main()
{
	json* root = new json();

	root = root->addSimpleField("id", "gXKNLIb9WucJYIE4Am2zt5RrCkfeCM");
	root = root->addSimpleField("email", "abcd@gmail.com");
	root = root->addSimpleField("feature", 1234);
	root = root->addSimpleField("new1", 1);
	root = root->addSimpleField("new2", 2);
	
	json* newComplex = root->addComplexField("newComplex");
	newComplex = newComplex->addSimpleField("simple","simple");
	json* newComplex1 = newComplex->addComplexField("newComplex1");
	newComplex1 = newComplex1->addSimpleField("simple", "simple");
	json* newComplex2 = newComplex->addComplexField("newComplex2");
	
	std::vector<std::string> arrayInComplex;
	arrayInComplex.push_back("a");
	arrayInComplex.push_back("b");
	arrayInComplex.push_back("c");
	json* q = newComplex1->addJsonArray("arrayInComplex", arrayInComplex);
	
	json* mac = root->addComplexField("mac_adress");
	mac = mac->addSimpleField("eth0", "1234-345-342");
	mac = mac->addSimpleField("wireless", "ASD-FGH-3FGH");
	json* newComplexx = mac->addComplexField("newInterface");
	newComplexx = newComplexx->addSimpleField("ipAddress", 9);
	
	json* test = mac->addComplexField("test");
	test = test->addSimpleField("test1", "test1");
	test = test->addSimpleField("test2", 11);

	std::vector<std::string> ar;
	ar.push_back("one");
	ar.push_back("two");
	ar.push_back("three");
	json* dd = root->addJsonArray("licenses", ar);

	std::vector<std::string> arNull;
	json* newNull = root->addJsonArray("nullArray", arNull);

	json* featureDetails = new json();
	featureDetails = featureDetails->addSimpleField("featureId", "newFeature");
	featureDetails = featureDetails->addSimpleField("availableQuantity", 10);
	featureDetails = featureDetails->addSimpleField("consumedQuantity", 2);
	featureDetails = featureDetails->addSimpleField("totalQuantity", 12);
	featureDetails = featureDetails->addSimpleField("expirationDate", "2021-07-16");
	featureDetails = featureDetails->addSimpleField("featureInfo", "null");

	json* featureDetails1 = new json();
	featureDetails1 = featureDetails1->addSimpleField("featureId", "newFeature2");
	featureDetails1 = featureDetails1->addSimpleField("availableQuantity", 2);
	featureDetails1 = featureDetails1->addSimpleField("consumedQuantity", 2);
	featureDetails1 = featureDetails1->addSimpleField("totalQuantity", 4);
	featureDetails1 = featureDetails1->addSimpleField("expirationDate", "2021-09-10");
	featureDetails1 = featureDetails1->addSimpleField("featureInfo", " ");

	json* featureDetails2 = new json();
	featureDetails2 = featureDetails2->addSimpleField("featureId", "newFeature3");
	featureDetails2 = featureDetails2->addSimpleField("availableQuantity", 7);
	featureDetails2 = featureDetails2->addSimpleField("consumedQuantity", 5);
	featureDetails2 = featureDetails2->addSimpleField("totalQuantity", 12);
	featureDetails2 = featureDetails2->addSimpleField("expirationDate", "2021-10-04");
	featureDetails2 = featureDetails2->addSimpleField("featureInfo", "aa");
	
	std::vector<json> newFeatures;
	newFeatures.push_back(*featureDetails);
	newFeatures.push_back(*featureDetails1);
	newFeatures.push_back(*featureDetails2);
	json* news = root->addJsonArray("featureDetails", newFeatures);
	
	json* quantities = new json();
	quantities = quantities->addSimpleField("quantity", 2);
	quantities = quantities->addSimpleField("quantity", 4);

	std::vector<json> newQuantities;
	newQuantities.push_back(*quantities);
	json* newOne = root->addJsonArray("quantities", newQuantities);

	json* quantitiesEmpty = new json();
	std::vector<json> newQuantitiesEmpty;
	newQuantitiesEmpty.push_back(*quantitiesEmpty);
	json* newOneEmpty = root->addJsonArray("quantitiesEmpty", newQuantitiesEmpty);

	json* asd = new json();
	std::vector<json> moreFeatures1;
	moreFeatures1.push_back(*asd);
	json* featuresfe1 = root->addJsonArray("features11", moreFeatures1);

	json* arrayObjectwithComplex = new json();
	arrayObjectwithComplex = arrayObjectwithComplex->addSimpleField("quantity", 2);
	json* ss = arrayObjectwithComplex->addComplexField("complexField");
	ss = ss->addSimpleField("qwerty", 2);

	std::vector<json> newArrayObject;
	newArrayObject.push_back(*arrayObjectwithComplex);
	json* newOneObjectComplex = root->addJsonArray("arrayObjectwithComplex", newArrayObject);

	json* arrayObjectwithArray = new json();
	arrayObjectwithArray = arrayObjectwithArray->addSimpleField("quantity", 2);

	std::vector<std::string> arq;
	arq.push_back("one");
	arq.push_back("two");
	arq.push_back("three");
	json* ddnew = arrayObjectwithArray->addJsonArray("licenses", arq);

	json* arrayObjectwithArray1 = new json();
	arrayObjectwithArray1 = arrayObjectwithArray1->addSimpleField("quantity", 2);

	std::vector<std::string> arq1;
	arq1.push_back("one");
	arq1.push_back("two");
	arq1.push_back("three");
	json* ddnew1 = arrayObjectwithArray1->addJsonArray("licenses", arq1);

	std::vector<json> newArrayObject1;
	newArrayObject1.push_back(*arrayObjectwithArray);
	newArrayObject1.push_back(*arrayObjectwithArray1);
	json* newOneObjectComplex1 = root->addJsonArray("arrayObjectwithArray", newArrayObject1);
	
	std::cout << root->serialize();
	system("pause");
    return 0;
}

