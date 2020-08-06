#include "QInt.h"

QInt::QInt()
{
	this->bit = QInt(2, "0").bit;
}

QInt::QInt(const QInt& num)
{
	this->bit = num.bit;
}

QInt::QInt(uint16_t mode, string s)
{
	if (mode == 2)
		this->bit = binary(s);

	else if (mode == 10) {
		bool isNegative = false;
		if (s[0] == '-')
		{
			isNegative = true;
			s = s.substr(1);
		}

		this->bit = binary(DecToBin(s));

		if (isNegative)
		{
			bit = ~bit;
			*this = *this + QInt(2, "1");
		}
	}

	else if (mode == 16)
		this->bit = binary(HexToBin(s));
}

int* QInt::Addition(int* ResultArray, int* SaveNumber, int n, int bit) {
	int reminder = 0;

	if (bit == 1) {
		for (int i = n - 1; i >= 0; i--) {
			ResultArray[i] = ResultArray[i] + SaveNumber[i] + reminder;
			reminder = 0;
			if (ResultArray[i] >= 10) {
				ResultArray[i] = ResultArray[i] % 10;
				reminder++;
			}
		}
	}

	reminder = 0;
	for (int i = n - 1; i >= 0; i--) {
		SaveNumber[i] = SaveNumber[i] * 2 + reminder;
		reminder = 0;
		if (SaveNumber[i] >= 10) {
			SaveNumber[i] = SaveNumber[i] % 10;
			reminder++;
		}
	}
	return ResultArray;
}

string QInt::BinToDec()
{
	int check = ((*this).bit.to_string()).find_first_not_of("0");
	if (check == -1)
		return "0";
	string number = "";
	int n = 40;
	int* ResultArray = new int[n]{ 0 };
	int* SaveNumber = new int[n]{ 0 };
	SaveNumber[39] = 1;
	int negative = false;
	if ((*this).bit[127] == 1)
		negative = true;

	if (negative) {
		*this = *this - QInt(2, "1");
		*this = ~(*this);
	}

	for (int i = 0; i < (*this).bit.size(); i++) {
		ResultArray = Addition(ResultArray, SaveNumber, n, this->bit[i]);
	}
	for (int i = 0; i < n; i++) {
		number = number + to_string(ResultArray[i]);
	}
	
	number = normalize(number);

	if (negative) {
		number = "-" + number;
	}
	if (negative) {
		*this = ~(*this);
		*this = *this + QInt(2, "1");
	}
	delete [] ResultArray;
	delete [] SaveNumber;
	return number;
}

string QInt::BinToHex()
{
	string val = (*this).bit.to_string();
	string result;
	string temp;
	int i = 0;

	while(i < val.size()) {
		while(temp.size() <= 3) {
			temp = temp + val[i];
			++i;
		}
		QInt data(2, temp);
		string MapToHex = data.BinToDec();
		if (MapToHex == "10")
			MapToHex = "A";
		else if(MapToHex =="11")
			MapToHex = "B";
		else if (MapToHex == "12")
			MapToHex = "C";
		else if (MapToHex == "13")
			MapToHex = "D";
		else if (MapToHex == "14")
			MapToHex = "E"; 
		else if (MapToHex == "15")
			MapToHex = "F";

		result = result + MapToHex;
		temp.clear();
	}
	result = normalize(result);
	return result;
}

string QInt::DecToHex(string dec)
{
	string hex,bin;
	bin = QInt::DecToBin(dec);
	QInt Binary(2, bin);
	hex = Binary.BinToHex();
	return hex;
}

string QInt::HexToDec(string hex)
{
	string bin, dec;
	bin = QInt::HexToBin(hex);
	QInt Binary(2, bin);
	dec = Binary.BinToDec();
	return dec;
}

string QInt::CheckEven(string number) {
	string remainder;
	if (number[number.size() - 1] % 2 == 0) {
		remainder = "0";
	}
	else {
		remainder = "1";
	}
	return remainder;
}

string QInt::DivideBy2(string dec) {
	string ans;
	int idx = 0;
	int temp = dec[idx] - '0';
	if (dec.size() < 2 && temp < 2) {
			ans = "0";
			return ans;
	}
	while (temp < 2)
		
		temp = temp * 10 + (dec[++idx] - '0');
	while (dec.size() > idx)
	{
		ans += (temp / 2) + '0';
		temp = (temp % 2) * 10 + dec[++idx] - '0';
	}

	if (ans.length() == 0)
		return "0";
	return ans;
}

string QInt::DecToBin(string dec)
{
	bool isNegative = false;
	if (dec[0] == '-') {
		isNegative = true;
		dec = dec.substr(1);
	}


	if (dec == "0")
		return "0";
	string result = "";
	while (dec != "0") {
		result = CheckEven(dec) + result;
		dec = DivideBy2(dec);
	}

	if (isNegative) {
		QInt temp;
		temp.bit = binary(result);
		temp = ~temp;
		temp = temp + QInt(2, "1");
		result = temp.bit.to_string();
	}

	return result;
}

string QInt::HexToBin(string hex)
{
	string HexData = "0123456789ABCDEF";
	string result;
	for (int i = 0; i < hex.length(); i++)
	{
		int HexIndex = HexData.find(hex[i]);
		string MapToBin = DecToBin(to_string(HexIndex));
		while (MapToBin.size() < 4) {
			MapToBin = '0' + MapToBin;
		}
		result = result + MapToBin;
	}
	return result;
}

//Arithmetic
QInt& QInt::operator=(QInt const& Qint)
{
	this->bit = Qint.bit;
	return (*this);
}

QInt QInt::operator+(const QInt& Qint2)
{
	QInt result;
	int carry = 0;

	for (int i = 0; i < this->bit.size(); i++) {
		if (this->bit[i] == 0 && Qint2.bit[i] == 0) {
			result.bit[i] = 0 ^ carry;
			carry = 0;
		}
		else if ((this->bit[i] & Qint2.bit[i]) == 0) {
			if (carry == 1) {
				result.bit[i] = 0;
				carry = 0;
				carry++;
			}
			else if (carry == 0) {
				result.bit[i] = 1;
			}
		}
		else
		{
			result.bit[i] = (this->bit[i] ^ Qint2.bit[i]) ^ carry;
			carry = 0;
			carry++;
		}
	}
	return result;
}

QInt QInt::operator-(const QInt& Qint2)
{
	QInt result, temp = Qint2;
	temp = ~temp;
	temp = temp + QInt(2,"1");
	result = *this + temp;
	return result;
}

QInt QInt::operator*(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (Qint2.bit[i] == 1) {
			result = result + *this;
		}
		this->bit = this->bit << 1;
	}
	return result;
}

QInt QInt::operator/(const QInt& Qint2) //Non-restore division
{
	int flag = 0;
	QInt Quotent = (*this);

	if (Quotent.bit[127] == 1)
	{
		Quotent = Quotent - QInt(2, "1");
		Quotent = ~Quotent;
		flag++;
	}

	QInt Divisor = Qint2;

	if ((Divisor).bit[127] == 1)
	{
		Divisor = Divisor - QInt(2, "1");
		Divisor = ~Divisor;
		flag++;
	}

	QInt Remainder;
	int n = Quotent.bit.size();

	while (n > 0) {
		bool carry = Quotent.bit[127];

		Remainder = Remainder << 1;
		Quotent = Quotent << 1;
			
		Remainder.bit[0] = carry;

		Remainder = Remainder - Divisor;

		if (Remainder.bit[127] == 1) {
			Quotent.bit[0] = 0;
			Remainder = Remainder + Divisor;
		}
		else
			Quotent.bit[0] = 1;
		
		n = n - 1;
	}

	if (flag == 1) {
		Quotent = ~Quotent;
		Quotent = Quotent + QInt(2, "1");
	}

	return Quotent;
}

//Bitwise
QInt QInt::operator&(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (this->bit[i] == 1 && Qint2.bit[i] == 1)
			result.bit[i] = 1;
		else
			result.bit[i] = 0;
	}
	return result;
}

QInt QInt::operator|(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (this->bit[i] == 0 && Qint2.bit[i] == 0)
			result.bit[i] = 0;
		else
			result.bit[i] = 1;
	}
	return result;
}

QInt QInt::operator^(const QInt& Qint2)
{
	QInt result;
	for (int i = 0; i < Qint2.bit.size(); i++) {
		if (this->bit[i] == Qint2.bit[i])
			result.bit[i] = 0;
		else
			result.bit[i] = 1;
	}
	return result;
}

QInt QInt::operator~()
{
	QInt result = *this;
	for (int i = 0; i < result.bit.size(); i++) {
		if (result.bit[i] == 0)
			result.bit[i] = 1;
		else if (result.bit[i] == 1)
			result.bit[i] = 0;
	}
	return result;
}

QInt QInt::operator>>(int step)
{
	QInt result = *this;
	if (step >= 127) {
		step = 127;
	}
	for (int i = step; i < 127; i++) {
		result.bit[i - step] = result.bit[i];
	}
	if (result.bit[127] == 1) {

		for (int i = 126; i > 126 - step; i--) {
			result.bit[i] = 1;
		}
	}
	else {
		for (int i = 126; i > 126 - step; i--) {
			result.bit[i] = 0;
		}
	}
	return result;
}

QInt QInt::operator<<(int step)
{
	QInt result = *this;
	if (step >= 128) {
		step = 128;
	}
	for (int i = 127 - step; i >= 0; i--) {
		result.bit[i + step] = result.bit[i];
	}
	for (int i = 0; i < step; i++) {
		result.bit[i] = 0;
	}
	return result;
}

QInt QInt::rol()
{
	QInt result = *this;
	bool carry = (*this).bit[127];
	result = result << 1;
	result.bit[0] = carry;
	return result;
}

QInt QInt::ror()
{
	QInt result = *this;
	bool carry = (*this).bit[0];
	result = result >> 1;
	result.bit[127] = carry;
	return result;
}

void QInt::printbit()
{
	for (int i = (*this).bit.size() - 1; i >= 0; i--) {
		cout << (*this).bit[i];
	}
}

string QInt::printAsMode(uint16_t mode)
{
	string result;
	if (mode == 10)
		result = (*this).BinToDec();
	if (mode == 2)
	{
		result = (*this).bit.to_string();
		result = normalize(result);
	}
	if (mode == 16)
		result = (*this).BinToHex();
	return result;
}

string normalize(string s) {
	int i = s.find_first_not_of("0");
	if (i == -1)
		return "0";
	return s.substr(i);
}
