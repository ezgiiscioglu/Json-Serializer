#include "stdafx.h"
#include "CppUnitTest.h"
#include "json.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
TEST_MODULE_ATTRIBUTE(L"Date", L"2021/6/12")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("In Module Initialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("In Module Cleanup");
}


namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		//json* testObj;
		std::string result = "{\"quantitiesEmpty\":[{}]}";
	public:

		UnitTest1()
		{
			Logger::WriteMessage("In UnitTest1");
		}

		~UnitTest1()
		{
			Logger::WriteMessage("In ~UnitTest1");
		}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In UnitTest1 Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In UnitTest1 Cleanup");
		}


		TEST_METHOD(TestMethod1)
		{
			json* root = new json();
			json* newJson = new json();

			std::vector<json> newQuantitiesEmpty;
			newQuantitiesEmpty.push_back(*newJson);
			json* newOneEmpty = root->addJsonArray("quantitiesEmpty", newQuantitiesEmpty);
			Assert::AreEqual(result, root->serialize());
		}

	};
}