//===========================================================================================================
// MIT License
// 
// Copyright(c) 2019 Kelvin Chin
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//===========================================================================================================
#include <fstream>
#include <iomanip>
#include "PrettyRoutine.hpp"

namespace json11
{
	namespace exts
	{
		PrettyRoutine::PrettyRoutine(const json11::Json& value, const std::string & indentPlaceholder):
			value(&value), indentPlaceholder(indentPlaceholder)
		{
		}

		std::string PrettyRoutine::dump()
		{
			std::ostringstream buffer;
			dumpStream(buffer);
			return buffer.str();
		}

		void PrettyRoutine::dumpStream(std::ostream& stream)
		{
			if (value->is_object())
			{
				dumpObject("", value, stream);
			}
			else if (value->is_array())
			{
				dumpArray("", value, stream);
			}
		}

		bool PrettyRoutine::dumpFile(const std::string& filename)
		{
			std::ofstream output;
			output.open(filename, std::ios::out);
			if (!output.is_open()) return false;
			dumpStream(output);
			return true;
		}

		void PrettyRoutine::dumpObject(const std::string& name, const json11::Json* object,
			std::ostream& stream)
		{
			fillSpace(stream);
			level++;
			if (name.empty())
			{
				stream << "{\n";
			}
			else
			{
				stream << std::quoted(name) << ": {\n";
			}

			auto&& childs = object->object_items();
			for (auto itr = childs.begin(); itr != childs.end(); itr++)
			{
				if (itr->second.is_object())
					dumpObject(itr->first, &itr->second, stream);
				else if (itr->second.is_array())
					dumpArray(itr->first, &itr->second, stream);
				else
					dumpValue(itr->first, &itr->second, stream);

				if (std::next(itr) != childs.end())
					stream << ",";
				stream << "\n";
			}

			level--;
			fillSpace(stream);
			stream << "}";
		}

		void PrettyRoutine::dumpArray(const std::string& name, const json11::Json* object,
			std::ostream& stream)
		{
			fillSpace(stream);
			level++;
			if (name.empty())
			{
				stream << "[\n";
			}
			else
			{
				stream << std::quoted(name) << ": [\n";
			}

			auto&& childs = object->array_items();
			for (auto itr = childs.begin(); itr != childs.end(); itr++)
			{
				if (itr->is_object())
					dumpObject("", &*itr, stream);
				else if (itr->is_array())
					dumpArray("", &*itr, stream);
				else
					dumpValue("", &*itr, stream);

				if (std::next(itr) != childs.end())
					stream << ",";
				stream << "\n";
			}

			level--;
			fillSpace(stream);
			stream << "]";
		}

		void PrettyRoutine::dumpValue(const std::string& name, const json11::Json* object,
			std::ostream& stream)
		{
			fillSpace(stream);
			if (!name.empty())
				stream << "\"" << name << "\": ";

			if (object->is_string())
				stream << std::quoted(object->string_value());
			else if (object->is_bool())
				stream << (object->bool_value() ? "true" : "false");
			else if (object->is_number())
				stream << object->number_value();
			else if (object->is_null())
				stream << "null";
		}

		void PrettyRoutine::fillSpace(std::ostream& stream)
		{
			for (uint64_t count{ 0 }; count < level; count++)
				stream << indentPlaceholder;
		}
	}
}
