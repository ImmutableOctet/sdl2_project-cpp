#pragma once

// Includes:
#include "util.h"

#include <fstream>

// Namespace(s):
namespace game
{
	namespace utilities
	{
		std::string load_string(const std::string& path)
		{
			// Open a stream using 'path'.
			std::ifstream f;
			
			f.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			f.open(path);

			// Read the entire stream as a string:
			std::string output;

			// Seek to the end of the file, and reserve the
			// amount of space passed for 'output':
			f.seekg(0, std::ios::end);
			
			output.reserve(f.tellg());

			// Seek back to the beginning.
			f.seekg(0, std::ios::beg);

			// Read from the input-stream into 'output'.
			output.assign((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

			// Return the loaded output-string.
			return output;
		}
	}
}