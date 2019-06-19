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
#pragma once
#include <cstdint>
#include <sstream>
#include "json11.hpp"

namespace json11
{
	namespace exts
	{
		class PrettyRoutine
		{
		public:
			//Construct Pretty Routine with json11's JSON object. indentPlaceholder default = 4 space
			PrettyRoutine(const json11::Json& value, const std::string& indentPlaceholder = "    ");
			//Dump json to string
			std::string dump();
			//Dump json to std::ostream based stream
			void dumpStream(std::ostream& stream);
			//Dump json to file, return true if success
			bool dumpFile(const std::string& filename);
		private:
			void dumpObject(const std::string& name, const json11::Json* object, std::ostream& stream);
			void dumpArray(const std::string& name, const json11::Json* object, std::ostream& stream);
			void dumpValue(const std::string& name, const json11::Json* object, std::ostream& stream);

			void fillSpace(std::ostream& stream);
		private:
			const json11::Json* value{ nullptr };
			std::string indentPlaceholder;
			uint32_t level{ 0 };
		};
	}
}