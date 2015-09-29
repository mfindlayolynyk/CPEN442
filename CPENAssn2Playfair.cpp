// CPENAssn2Playfair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <random>
#include <iostream>

//not currently being used....
//taken from http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-playfair/
#include "qgr.h"
extern float qgram[];


int getXpos(int pos){
	return pos % 5;
}

int getYpos(int pos){
	return pos / 5;
}

char getCharFromPos(int x, int y, int positions[]){
	int pos = (y*5)+x;

	//ugh... could just make separate array to store this...
	for (int i = 0; i < 26; i++){
		if (positions[i] == pos)
			return (char) i + 65;
	}
	return (char) 9 + 65; //j: impossible

}

std::string DecryptPlayfair(std::string cipherText, int positions[]){

	int i = 0;
	char c;
	char d;
	int length = cipherText.length();

	//positions in matrix for chars c and d: between 0 and 4.
	int cx;
	int cy;
	int dx;
	int dy;

	for (i;  i < length; i = i+2){

		//getting matrix positions for chars
		c = cipherText[i]; //gets next char
		cx = getXpos(positions[((int)c)-65]); 
		cy = getYpos(positions[((int)c) - 65]);
		d = cipherText[i+1];
		dx = getXpos(positions[((int)d) - 65]);
		dy = getYpos(positions[((int)d) - 65]);

		//three rule cases:
		//same column: cx = dx
		//same row: cy = dy
		//rectangle
		if (cx == dx) {//same column
			cy--;
			if (cy < 0)
				cy = 4; //overflow around
			dy--;
			if (dy < 0)
				dy = 4; //overflow around
		}
		else if (cy == dy){//same row
			cx--;
			if (cx < 0)
				cx = 4; //overflow around
			dy--;
			if (dy < 0)
				dy = 4; //overflow around
		}
		else{//rectangle (switch x's)
			int temp = cx;
			cx = dx;
			dx = temp;
		}

		c = getCharFromPos(cx, cy, positions);
		if (c == 9+65)
			printf("Error! J!");
		cipherText[i] = c;
		d = getCharFromPos(dx, dy, positions);
		if (d == 9+65)
			printf("Error! J!");
		cipherText[i + 1] = d;

	}
	return cipherText;
}


void getFrequencies(std::string plainText, double frequencies[]){

	for (int i = 0; i < 26; i++){
		frequencies[i] = 0; //set all elemenents to zero
	}

	int length = plainText.length();

	for (int i = 0; i < length; i++){
		frequencies[(int) (plainText[i] - 65)]++;
	}

	for (int i = 0; i < 26; i++){
		frequencies[i]= frequencies[i]/length;
		//printf("%c: with precent frequency: %f \n", i+65, frequencies[i] * 100);
	}

//just modifyng frequencies, not returning anything
}


double AnalyseFrequencies(double frequencies[]){

	float expected[26] = { 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0, 0.0077, 0.040, 0.024, 0.067, 0.075, 0.019, 0.00095, 0.060, 0.063, 0.091, 0.028, 0.0098, 0.024, 0.0015, 0.020, 0.00074 };
	double totalError = 0;

	for (int i = 0; i < 26; i++){
		totalError += abs(frequencies[i] - expected[i]) * 100;
	}

	return totalError;

}


void switchPositions(int newPos[]){
	//randomizing info taken from stack overflow: http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 25); // guaranteed unbiased
	
	int pos1 = 9;
	int pos2 = 9;
	bool notRandomized = true;

		//randomizing for switch
		while (notRandomized){
			pos1 = uni(rng);
			if (pos1 != 9)
				notRandomized = false;
		}
		notRandomized = true;
		while (notRandomized){
			pos2 = uni(rng);
			if (pos2 != 9 && pos2 != pos1)
				notRandomized = false;
		}
		if (pos1 < 0 || pos1 >25 || pos2 <0 || pos2 > 25)
			printf("Random error! ie error in the randomization!");


	int temp = newPos[pos1];

	newPos[pos1] = newPos[pos2];
	newPos[pos2] = temp;

}


void switchRows(int newPos[]){
	//randomizing info taken from stack overflow: http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 4); // guaranteed unbiased

	int row1 = 5;
	int row2 = 5;
	bool notRandomized = true;
	int pos = 0;
	int x = 0;
	int y = 0;

	//randomizing for switch
	while (notRandomized){
		row1 = uni(rng);
		notRandomized = false;
	}
	notRandomized = true;
	while (notRandomized){
		row2 = uni(rng);
		if (row2 != row1)
			notRandomized = false;
	}

	for (int i = 0; i < 26; i++){
		if (i != 9){//don't touch j...
			pos = newPos[i];
			y = getYpos(pos);
			if (y == row1){
				x = getXpos(pos);
				y = row2;
				pos = (y * 5) + x;
				newPos[i] = pos;
			}
			else if (y == row2){
				x = getXpos(pos);
				y = row1;
				pos = (y * 5) + x;
				newPos[i] = pos;
			}
		}
	}
}


void switchColumns(int newPos[]){
	//randomizing info taken from stack overflow: http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 4); // guaranteed unbiased

	int c1 = 5;
	int c2 = 5;
	bool notRandomized = true;
	int pos = 0;
	int x = 0;
	int y = 0;

	//randomizing for switch
	while (notRandomized){
		c1 = uni(rng);
		notRandomized = false;
	}
	notRandomized = true;
	while (notRandomized){
		c2 = uni(rng);
		if (c2 != c1)
			notRandomized = false;
	}

	for (int i = 0; i < 26; i++){
		if (i != 9){//don't touch j...
			pos = newPos[i];
			x = getXpos(pos);
			if (x == c1){
				y = getYpos(pos);
				x = c2;
				pos = (y * 5) + x;
				newPos[i] = pos;
			}
			else if (x == c2){
				y = getYpos(pos);
				x = c1;
				pos = (y * 5) + x;
				newPos[i] = pos;
			}
		}
	}
}

void reflectColumns(int newPos[]){

	int pos = 0;
	int x = 0;
	int y = 0;

	for (int i = 0; i < 26; i++){
		if (i != 9){//don't touch j...
			pos = newPos[i];
			x = getXpos(pos);
			y = getYpos(pos);
			x = 4 - x;
			newPos[i] = (y * 5) + x;
		}
	}
}

void reflectRows(int newPos[]){

	int pos = 0;
	int x = 0;
	int y = 0;

	for (int i = 0; i < 26; i++){
		if (i != 9){//don't touch j...
			pos = newPos[i];
			x = getXpos(pos);
			y = getYpos(pos);
			y = 4 - y;
			newPos[i] = (y * 5) + x;
		}
	}
}

void reverse(int newPos[]){

	int pos = 0;
	int x = 0;
	int y = 0;

	for (int i = 0; i < 26; i++){
		if (i != 9){//don't touch j...
			pos = newPos[i];
			newPos[i] = 24 - pos; 
		}
	}
}


void modifyKey(int newPos[]){

	//randomizing info taken from stack overflow: http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 50); // guaranteed unbiased

	int choice = uni(rng);

	if (choice > 4)
		switchPositions(newPos);
	else if (choice == 0)
		switchRows(newPos);
	else if (choice == 1)
		switchColumns(newPos);
	else if (choice == 2)
		reflectColumns(newPos);
	else if (choice == 3)
		reflectRows(newPos);
	else if (choice == 4)
		reverse(newPos);

}

double getError(std::string plainText){
	//not currently being used....

	//modelled after http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-playfair/
	char a, b, c, d;
	double error = 0;
	int length = plainText.length();

	for (int i = 0; i < length - 3; i++){
		a = plainText[i] - 65;
		b = plainText[i] - 65;
		c = plainText[i] - 65;
		d = plainText[i] - 65;

		error += qgram[17576 * a + 676 * b + 26 * c + d];
	}
	return error*-1.0;
}



int _tmain(int argc, _TCHAR* argv[])
{
	std::string cipherText = "QPHVXCFVEOGDQRHVXCFVPCCWZWXHVTFVVWQLWVDHAPDBDLWPEVTSALRDHPFOXROPPGPRTZSKBGWEHFADHFWFZFPOHVXCFVDZXUKSTKZDDAMDDOOFPCAWUMHGRWXDRKBGXTHFVHEOXNHFQLPCCGHFIMCWFHGRZFHVXCFVWVPRQLXYPZGLHPMPQLDOGQUGSKQGBHADFZXRNGVFFVYPEVBDDPBDHWUQAWXRDOQGWPAWXRGWCNHBKYQLGONYZGMPBDDPDOHADOQGHPFPAFQGQWSPMDFOBNUREWVZPKFVGHFQHVXCFVDZDKBHHOZGQRHPYPGQLMBDQLYSDEDOBOCWINZSACRDHPKOPKZUCNCUWFQPTCPYZKDOLFUQQUXNLSXILHVTFVWVPREOGDQRHPYFAWQHVTFVUKKOUQEUVWKLGHGZMDFOLMDPVHVTFVWVPRDZXRPDOPSEBGQLALPSGQPEOFQLWVFAACRUKYQLYUCNQUXNLSXICFWPWCXHVTFVFVGHFQPMUQEKLCEBVZPKOFOPSPBGGTCGHFHVXCFVWVPRQLXYPZGLHVXCFVDBSGFAWRODLIPRRPMHODAWXMATZNPYZWGBXRYQLCBGRPDLQGEOXRHPDOLHBPHNEOACSPHGVWQPLCXHEOXYKELWXIZWHOWPFWXRFWUVEBPMHGBPDPTEWPEOXRHVXCFVWVPREOGDQRHPFPLCCHVTFVBEQNWRODHVXCFVWYTZSUBGDOSYDPALGHOGHVXCFVWVPRDZXNNITSUQMQVTFVISXLQPXNQPPIUQHBUWDKZBTVGQHVTKZDFOUBCWEOWHHPDPMEBPXIAFHGBDFPBGDOSYDPALGHOGWVPRQLXYPZGLHVXCFVHBBTURXWOPLMHGHPYPMPRGAWGTKBDOOFQLPXAWNOPKFAGQALURNGAWQUPMSQTADYQLYWXIMDYPFCHVXCFVEOGDQRSYWEURHGFVGHFQUVPHMQVTFVZNBTLGVWNPKVCLHPGQPCOGALLGHVXCFVFQFPPYODEODPGLQFCWYPCNEUQPVRIYXNURPYMCPVLMHFHPDOAGLCFOPMBVATGQBSCUPZXKSRHGUWDOBVYIZGGQGHPWGQDPEBWNOHPDDOHGAWDOAWFHXIIDZVBVQKYPRPHGSIWGFHDYQLXMLCACMVVTFVDOOFPUQTDBBDCWTAKLHOSYHVXCFVWVPRDZGUWPLCTRPDFQOEHVXCFVWVPREOGDQRHPKHUYLAZGYFQXBPHQHVXCFVKPGXHGURDPBVBDAWXRUKQYHGUREONGPRWMDZDKEWGRLGHPMDDOQFIDZVBVQKYDBGWMWRINHGTVPHFZXRPMWKGAHOSYHPDKICWLBEHGQLXYPZGLHPMPFODYCLXHVTFVEOGDQRHBBTHGZOQGWSPMURYPFCDPWCLQQGUKXIYPDKPDAWXIZOQGQLXQPTTZMWWHCNCKBGMCIMCNEBVBQRHPDPLDVHVTFVWVPREOGDQRHVXCFVPMNINDNEURDFADHFSIYGVTDOHAHNEVTSALRDHPDOQGYSBDLHVTFVWUVWDKYDRYXNDPSIWCKOPKUWDOWEGQOFQXAWYUXNATNIPMKZHGPIQYXNMVVTFVDZLUBPXRHGATKYQLALGOXRDAMDDOQGAGYQPMHPDPGLZGFVDZKLHOQGYSBDLHVTFVQLYWPCHGURQPPWAWXUTPLMHFBGGPPYOHGQFWGQOZHKURNEVDBTURDEBGNTQGHQWQKYEODOLQOGSPHGDPHCAWDBPKDOHAACGLZGQUQGHPDOVWYPQKISCNQUXNBPDOWPFWXRHVXCFVQLTPURFHRPFOMDDOQGWEBGXPZWXHVTFVFHGNHAHPMDDOAFBGXPWIOPGLHPMGKTVPDPKYQLNGAWWCHPKHVDBTURNGOFQLDICLVWHGUWDOQPXMLCMEVTFVDZDLBGGHHDQLUCWRODQKMXBTURDEBGNTQGHQWQKYPOQGYSBDHGPDPODOBGMUHVXCFVDZRUXMZDQRPCLACLPEQGDBWCBGHOSQLSSDWHRDHPYPMPWSPMPVWFMGKWCHVTFVWPDKPYGDQYDEFOKYQGNPKVCLHPGQSRSRWSPMXDGLACQYFVRWGLXTOGQFHGRYXNHVXCFVPVFCOPSEVTFVQLWCCFHGPVDPWNQTAWQHVTFVUYDBSEVTFVWVPRDZXLVTFVRWZSXNQLGZICWLQAHGPDUKYFBPNLAPPEOFQLXPZFDPSPWYQLFWPCQGLHHVXUFODKZSRWEBXLLHVTFVWVPRQLXYPZGLHVXCFVTVSDIWXNQLGQFQPXPDDOOFIXWRODHVXCFVWVPRDZXLVTFVDBRDRPXNHPDOHGFHCNBKPMBHAWGXYGVTPEOFEOSDWHGLHDPOSYHPFOXRPEOFSZLCAWGXHGWPDBMDDPYDSPMDDOOFHVFWGRQKQUMDKHCWLIPYHVXCFVKSXRKLNWPXPDQLXYPZGLEWACVWEOMFEBWNEOXRCLBGHGTAGIZGHDPTSQNKTDPATVGQVZBTPXPDVWLHBDNHOFQGHVXCFVDZDLOGUXOFHQHGQPWVXYVBLMYGVTZGBPXRQLXIOPKBGHXIPCLQOGRGPTWHHDQLTVXUFHNZVDBTATTVXUFHXIBDQPWMVDPDHPMDDOLAVDBTEONODZFLGKGQAGDZYSMPGQPMGZURURNALCFOXRUXOWWHXOSQPZSPQKOFDZXUBGNBCG";
	int positions[26] = { 13, 4, 21, 1, 14, 17, 8, 18, 15, -1, 23, 19, 0, 6, 24, 10, 7, 20, 22, 16, 9, 11, 5, 12, 3, 2};
	int newPos[26] = { 13, 4, 21, 1, 14, 17, 8, 18, 15, -1, 23, 19, 0, 6, 24, 10, 7, 20, 22, 16, 9, 11, 5, 12, 3, 2 }; //try other random start positions...
	//''random'' starting key:   c, d, e,  f, g,  h,  i, *j*, k, l,  m, n, o,  p,  q,  r,  s, t,  u,  v,  w,  x,  y, z
	//alpha positions:     0, 1, 2  3  4   5   6  7   8   9  10  11  12 13 14  15  16 17  18  19  20  21  22  23  24 25

	double frequencies[26] = { 0 };
	double bestError = 200000;
	double err = 0;
	std::string plainText;
	double prob = 0;
	double dF = 0;

	for (int j = 0; j < 10; j++) {
		printf("iteration %d", j);
		for (double T = 100; T > 0; T -= 0.2){//big strings need big T. smaller delta T gives better results but takes longer
			for (int count = 0; count < 10000; count++){//make longer for better results, but takes longer

				modifyKey(newPos);

				plainText = DecryptPlayfair(cipherText, newPos);

				getFrequencies(plainText, frequencies);
				err = AnalyseFrequencies(frequencies);

				if (err < bestError) {//new best found!
					bestError = err;
					for (int i = 0; i < 26; i++){
						positions[i] = newPos[i];
					}
				}
				else {//put it back
					// probabilistic selection of worse keys modelled after: http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-playfair/
					dF = (bestError - err); //want dF < 0 in this case
					prob = exp(dF / T);
					if (prob > 1.0*rand() / RAND_MAX){//replace anway with probability distribution
						for (int i = 0; i < 26; i++){
							positions[i] = newPos[i];
						}
					}
					else {
						for (int i = 0; i < 26; i++){
							newPos[i] = positions[i];
						}
					}
				}

				if (err < 30){//modify this value as things get better! //It never got better!!!!!
					printf("error: %d", err);
					for (int i = 0; i < 26; i++){
						printf("%c: with frequency: %f, and matrix position: %i \n", i + 65, frequencies[i], positions[i]);
					}
					std::cout << plainText;
				}

			}
		}
		
		for (int i = 0; i < 26; i++){
			printf("%c: with frequency: %f, and matrix position: %i \n", i + 65, frequencies[i], positions[i]);
		}
		std::cout << plainText;
	}




	return 0;
}



