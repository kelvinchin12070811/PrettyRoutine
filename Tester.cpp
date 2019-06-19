#include <iostream>
#include "json11.hpp"
#include "PrettyRoutine.hpp"

using namespace std;

void allObjectsTest()
{
	json11::Json json = json11::Json::object{
		{ "book", json11::Json::object{
			{ "name", "book1" },
			{ "author", "person1" },
			{ "year", 2019 }
		}},
		{ "test", 12.367 },
		{ "null", json11::Json{} }
	};

	cout << "raw:\n" << json.dump() << endl;

	json11::exts::PrettyRoutine routine{ json };
	cout << "prettify:\n" << routine.dump() << endl;
	routine.dumpFile("all_objects.json");
}

void arrayTest()
{
	json11::Json json = json11::Json::array{
		json11::Json::object{
			{ "test", "hello world" },
			{ "test2", "from json" }
		},
		json11::Json::object{
			{ "test", "hello world" },
			{ "test2", "from json" }
		}
	};

	cout << "raw:\n" << json.dump() << endl;

	json11::exts::PrettyRoutine routine{ json };
	cout << "prettify:\n" << routine.dump() << endl;
	routine.dumpFile("array_test.json");
}

void compoundTest()
{
	json11::Json json;
	std::string err;
	json = json11::Json::parse(R"({"test": "hello world", "array": [ 2, "t", 35.6 ]})", err);

	if (err.empty())
	{
		cout << "raw:\n" << json.dump() << endl;

		json11::exts::PrettyRoutine routine{ json };
		cout << "prettify:\n" << routine.dump() << endl;
		routine.dumpFile("compound_test.json");
	}
	else
	{
		cout << err << endl;
	}
}

int main(int argc, char** argv)
{
	cout << "===All objects test===" << endl;
	allObjectsTest();
	cout << endl;

	cout << "===Array test===" << endl;
	arrayTest();
	cout << endl;

	cout << "===compoundTest" << endl;
	compoundTest();
	cout << endl;

	return 0;
}