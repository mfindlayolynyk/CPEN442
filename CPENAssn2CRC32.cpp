// CPENAssn2CRC32.cpp : Defines the entry point for the console application.
//


//everything before main{} is from the C++ implementation in: http://rosettacode.org/wiki/CRC-32
#include "stdafx.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>

// These headers are only needed for main(), to demonstrate.
#include <iomanip>
#include <iostream>
#include <string>

// Generates a lookup table for the checksums of all 8-bit values.
std::array<std::uint_fast32_t, 256> generate_crc_lookup_table() noexcept
{


	// This is a function object that calculates the checksum for a value,
	// then increments the value, starting from zero.
	struct byte_checksum
	{
		std::uint_fast32_t operator()() noexcept
		{
			auto checksum = static_cast<std::uint_fast32_t>(n++);
			auto const reversed_polynomial = std::uint_fast32_t{ 0xEDB88320uL };

			for (auto i = 0; i < 8; ++i)
				checksum = (checksum >> 1) ^ ((checksum & 0x1u) ? reversed_polynomial : 0);

			return checksum;
		}

		unsigned n = 0;
	};

	auto table = std::array<std::uint_fast32_t, 256>{};
	std::generate(table.begin(), table.end(), byte_checksum{});

	return table;
}

// Calculates the CRC for any sequence of values. (You could use type traits and a
// static assert to ensure the values can be converted to 8 bits.)
template <typename InputIterator>
std::uint_fast32_t crc(InputIterator first, InputIterator last)
{
	// Generate lookup table only on first use then cache it - this is thread-safe.
	static auto const table = generate_crc_lookup_table();

	// Calculate the checksum - make sure to clip to 32 bits, for systems that don't
	// have a true (fast) 32-bit type.
	return std::uint_fast32_t{ 0xFFFFFFFFuL } &
		~std::accumulate(first, last,
			~std::uint_fast32_t{ 0 } &std::uint_fast32_t{ 0xFFFFFFFFuL },
			[](std::uint_fast32_t checksum, std::uint_fast8_t value)
	{ return table[(checksum ^ value) & 0xFFu] ^ (checksum >> 8); });
}


//begin my code
int _tmain(int argc, _TCHAR* argv[])
{

	std::string s = "64AFF6320F81725BF8D3239593D142E7";
	unsigned int mine = crc(s.begin(), s.end());

	int stringLength = 1;
	bool notdone = true;
	std::string test = "000000000000000000000000000000";
	std::string c = test.substr(0, stringLength);//position, size
	int i = 0;

	//bool check[0xffff] = { 0 };

	while (notdone) {
		while (notdone && i < stringLength) {
			i = 0;
			while (i < stringLength) {
				//iterate trhough strings
				if (c[i] >= 48 && c[i] < 57) {
					c[i] = c[i] + 1;
					break;
				}
				else if (c[i] == 57) {
					c[i] = 65;
					break;
				}
				else if (c[i] >= 65 && c[i] < 90) {
					c[i] = c[i] + 1;
					break;
				}
				else {//c[i] ==97
					c[i] = 48;
					i++;
				}
			}

			unsigned int message = crc(c.begin(), c.end());
			if (message == mine) {
				std::cout << c << " gives " << message << '\n';
				notdone = false;
			}

		}
		//changing string length idea came from Jeremy Goh
		stringLength++;
		c = test.substr(0, stringLength);
	}
	return 0;
}


