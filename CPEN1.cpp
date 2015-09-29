// CPEN1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

//orginal attempts
//int main()
//{
//	string cipher;
//	//cipher = "OLDMEMRDCEQMPHUMDHMATHCIRCLEPAAUFIBAFDIREZFDIZFIPSFYCSFQHCIIZFDZFHPQMBBFMOFHPDQPHFEPIZGPAGCYCSSMMDHIZFHCCOEMQQZLIHCIIZFRCLDUZCGGPIQQIMOFHMIIZFHCCOPDJMPDTCOMEZPAFYCSSMMDHIZFDSMHFCTTYCSSMTFFAPDUIZMIIZFHMRCTIZFBMOIRECLAHDFJFOYCSFHCIPDQPHFGMUFDHYCSSMGPAGCMDHUMDHMATEFOFQPIIPDUMIIZFCBFDEPDHCECTMQSMAAOCCSACCKPDUCLIEFQICDICIZFUMOHFDHCIIZFAMIFMTIFODCCDEMQGOPUZIMDHBFMYFTLAHCIIZFTACEFOQUACEFHOFHMDHUCAHFDQDMBHOMUCDQMDHQLDTACEFOQYCSSMMDHDMQILOIPMDQIOMPAPDUMAACJFOIZFILOTEMAAQMDHBFFBPDUPDMIIZFOCLDHEPDHCEQ";
//	cipher = "QPHVXCFVEOGDQRHVXCFVPCCWZWXHVTFVVWQLWVDHAPDBDLWPEVTSALRDHPFOXROPPGPRTZSKBGWEHFADHFWFZFPOHVXCFVDZXUKSTKZDDAMDDOOFPCAWUMHGRWXDRKBGXTHFVHEOXNHFQLPCCGHFIMCWFHGRZFHVXCFVWVPRQLXYPZGLHPMPQLDOGQUGSKQGBHADFZXRNGVFFVYPEVBDDPBDHWUQAWXRDOQGWPAWXRGWCNHBKYQLGONYZGMPBDDPDOHADOQGHPFPAFQGQWSPMDFOBNUREWVZPKFVGHFQHVXCFVDZDKBHHOZGQRHPYPGQLMBDQLYSDEDOBOCWINZSACRDHPKOPKZUCNCUWFQPTCPYZKDOLFUQQUXNLSXILHVTFVWVPREOGDQRHPYFAWQHVTFVUKKOUQEUVWKLGHGZMDFOLMDPVHVTFVWVPRDZXRPDOPSEBGQLALPSGQPEOFQLWVFAACRUKYQLYUCNQUXNLSXICFWPWCXHVTFVFVGHFQPMUQEKLCEBVZPKOFOPSPBGGTCGHFHVXCFVWVPRQLXYPZGLHVXCFVDBSGFAWRODLIPRRPMHODAWXMATZNPYZWGBXRYQLCBGRPDLQGEOXRHPDOLHBPHNEOACSPHGVWQPLCXHEOXYKELWXIZWHOWPFWXRFWUVEBPMHGBPDPTEWPEOXRHVXCFVWVPREOGDQRHPFPLCCHVTFVBEQNWRODHVXCFVWYTZSUBGDOSYDPALGHOGHVXCFVWVPRDZXNNITSUQMQVTFVISXLQPXNQPPIUQHBUWDKZBTVGQHVTKZDFOUBCWEOWHHPDPMEBPXIAFHGBDFPBGDOSYDPALGHOGWVPRQLXYPZGLHVXCFVHBBTURXWOPLMHGHPYPMPRGAWGTKBDOOFQLPXAWNOPKFAGQALURNGAWQUPMSQTADYQLYWXIMDYPFCHVXCFVEOGDQRSYWEURHGFVGHFQUVPHMQVTFVZNBTLGVWNPKVCLHPGQPCOGALLGHVXCFVFQFPPYODEODPGLQFCWYPCNEUQPVRIYXNURPYMCPVLMHFHPDOAGLCFOPMBVATGQBSCUPZXKSRHGUWDOBVYIZGGQGHPWGQDPEBWNOHPDDOHGAWDOAWFHXIIDZVBVQKYPRPHGSIWGFHDYQLXMLCACMVVTFVDOOFPUQTDBBDCWTAKLHOSYHVXCFVWVPRDZGUWPLCTRPDFQOEHVXCFVWVPREOGDQRHPKHUYLAZGYFQXBPHQHVXCFVKPGXHGURDPBVBDAWXRUKQYHGUREONGPRWMDZDKEWGRLGHPMDDOQFIDZVBVQKYDBGWMWRINHGTVPHFZXRPMWKGAHOSYHPDKICWLBEHGQLXYPZGLHPMPFODYCLXHVTFVEOGDQRHBBTHGZOQGWSPMURYPFCDPWCLQQGUKXIYPDKPDAWXIZOQGQLXQPTTZMWWHCNCKBGMCIMCNEBVBQRHPDPLDVHVTFVWVPREOGDQRHVXCFVPMNINDNEURDFADHFSIYGVTDOHAHNEVTSALRDHPDOQGYSBDLHVTFVWUVWDKYDRYXNDPSIWCKOPKUWDOWEGQOFQXAWYUXNATNIPMKZHGPIQYXNMVVTFVDZLUBPXRHGATKYQLALGOXRDAMDDOQGAGYQPMHPDPGLZGFVDZKLHOQGYSBDLHVTFVQLYWPCHGURQPPWAWXUTPLMHFBGGPPYOHGQFWGQOZHKURNEVDBTURDEBGNTQGHQWQKYEODOLQOGSPHGDPHCAWDBPKDOHAACGLZGQUQGHPDOVWYPQKISCNQUXNBPDOWPFWXRHVXCFVQLTPURFHRPFOMDDOQGWEBGXPZWXHVTFVFHGNHAHPMDDOAFBGXPWIOPGLHPMGKTVPDPKYQLNGAWWCHPKHVDBTURNGOFQLDICLVWHGUWDOQPXMLCMEVTFVDZDLBGGHHDQLUCWRODQKMXBTURDEBGNTQGHQWQKYPOQGYSBDHGPDPODOBGMUHVXCFVDZRUXMZDQRPCLACLPEQGDBWCBGHOSQLSSDWHRDHPYPMPWSPMPVWFMGKWCHVTFVWPDKPYGDQYDEFOKYQGNPKVCLHPGQSRSRWSPMXDGLACQYFVRWGLXTOGQFHGRYXNHVXCFVPVFCOPSEVTFVQLWCCFHGPVDPWNQTAWQHVTFVUYDBSEVTFVWVPRDZXLVTFVRWZSXNQLGZICWLQAHGPDUKYFBPNLAPPEOFQLXPZFDPSPWYQLFWPCQGLHHVXUFODKZSRWEBXLLHVTFVWVPRQLXYPZGLHVXCFVTVSDIWXNQLGQFQPXPDDOOFIXWRODHVXCFVWVPRDZXLVTFVDBRDRPXNHPDOHGFHCNBKPMBHAWGXYGVTPEOFEOSDWHGLHDPOSYHPFOXRPEOFSZLCAWGXHGWPDBMDDPYDSPMDDOOFHVFWGRQKQUMDKHCWLIPYHVXCFVKSXRKLNWPXPDQLXYPZGLEWACVWEOMFEBWNEOXRCLBGHGTAGIZGHDPTSQNKTDPATVGQVZBTPXPDVWLHBDNHOFQGHVXCFVDZDLOGUXOFHQHGQPWVXYVBLMYGVTZGBPXRQLXIOPKBGHXIPCLQOGRGPTWHHDQLTVXUFHNZVDBTATTVXUFHXIBDQPWMVDPDHPMDDOLAVDBTEONODZFLGKGQAGDZYSMPGQPMGZURURNALCFOXRUXOWWHXOSQPZSPQKOFDZXUBGNBCG";
//	int var = 25;
//
//	int length = cipher.length();
//	string working = cipher;
//
//	//frequency analysis
//	float count[26] = { 0 }; //initializing all to zero
//	for (int pos1 = 0; pos1 < length; pos1++) {
//		count[working[pos1] - 65]++; //incremement position in alphabet to get counts
//	}
//	for (int a = 0; a < 26; a++) {
//		if (count[a] != 0)
//			count[a] = (count[a]*1.0) / length;
//		cout << count[a] <<endl;
//	}
//								 
////caesar cipher checking
//	for (var = 0; var < 27; var++) {
//		for (int pos = 0; pos < length; pos++) {
//			if (working[pos] + var > 90) {
//				working[pos] = working[pos] + var - 26;
//			}
//			else working[pos] = working[pos] + var;
//
//		}
//		cout << working << endl <<endl;
//	}
// return 0;
//}


//not mine til next main()
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
	auto const reversed_polynomial = std::uint_fast32_t{ 0xEDB88320uL };

	// This is a function object that calculates the checksum for a value,
	// then increments the value, starting from zero.
	struct byte_checksum
	{
		std::uint_fast32_t operator()() noexcept
		{
			auto checksum = static_cast<std::uint_fast32_t>(n++);

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
int main()
{
	string s = "64AFF6320F81725BF8D3239593D142E7";
	unsigned int mine = crc(s.begin(), s.end());

	bool notdone = true;
	string c= "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	int i = 0;
	bool check[0xffff] = { 0 };

	while (notdone) {
		i = 0;
		while(i<32) {
		//iterate trhough strings
			if (c[i] < 122) {
				c[i] = c[i] + 1;
				i = 32;
			}
			else {
				c[i] = 97;
				i++;
			}
		}
		
		unsigned int message = crc(c.begin(), c.end());
		if (message == mine) {
			std::cout << c << " gives " << message << '\n';
			notdone = false;
		}


		//if (message < 0xffff) {
		//	if (check[message] == 1) {
		//		std::cout << c << " gives " << message << '\n';
		//		notdone = false;
		//		c = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		//	}
		//	else {
		//		check[message] = 1;
		//	}
		//}
	}

	//notdone = true;
	//while (notdone) {
	//	i = 0;
	//	while (i<32) {
	//		//iterate trhough strings
	//		if (c[i] < 122) {
	//			c[i] = c[i] + 1;
	//			i = 32;
	//		}
	//		else {
	//			c[i] = 97;
	//			i++;
	//		}
	//	}

	//	//		auto const t = std::string{ c };
	//	unsigned int message = crc(c.begin(), c.end());
	//	if (message < 0xffff) {
	//		if (check[message] == 1) {
	//			std::cout << c << " also gives " << message << '\n';
	//			notdone = false;
	//		}
	//	}
	//}


	return 0;
}
