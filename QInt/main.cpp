#include "FileHandle.h"

//int main() {
//
//	if (Calculator("data\input.txt", "output_sv\output.txt") == true)
//	{
//		cout << "Data is calculated. Please check output.txt" << endl;
//	}
//	else
//	{
//		cout << "Error in file/program. Canceling program..." << endl;
//	}
//	//QInt num1 = { 2,"11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" };
//	//QInt num2(10, "2");
//	//QInt result = num2 / num1;
//	//result.printbit();
//
//	return 0;
//}
int main() {

	QInt num1(2, "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	QInt num2(2, "1101");
	string bin1, hex1, dec1, dec2, hex2, bin2;
	cout << "INPUT " << endl
		<< "Variable 1 : "; num1.printbit();
	cout << endl << "Variable 2 : "; num2.printbit();
	cout << endl << "TRANSFORMATION OUTPUT: ";
	cout << endl << "(Bin -> Dec) : "; dec1 = num1.BinToDec(); cout << dec1;
	cout << endl << "(Bin -> Dec) : "; dec2 = num2.BinToDec(); cout << dec2;
	cout << endl << "(Dec -> Bin) : "; bin1 = QInt::DecToBin(dec1); cout << bin1;
	cout << endl << "(Dec -> Bin) : "; bin2 = QInt::DecToBin(dec2); cout << bin2;
	cout << endl << "(Bin -> Hex) : "; hex1 = num1.BinToHex(); cout << hex1;
	cout << endl << "(Bin -> Hex) : "; hex2 = num2.BinToHex(); cout << hex2;
	cout << endl << "(Hex -> Bin) : "; bin1 = QInt::HexToBin(hex1); cout << bin1;
	cout << endl << "(Hex -> Bin) : "; bin2 = QInt::HexToBin(hex2); cout << bin2;
	cout << endl << "(Hex -> Dec) : "; dec1 = QInt::HexToDec(hex1); cout << dec1;
	cout << endl << "(Hex -> Dec) : "; dec2 = QInt::HexToDec(hex2); cout << dec2;
	cout << endl << "(Dec -> Hex) : "; hex1 = QInt::DecToHex(dec1); cout << hex1;
	cout << endl << "(Dec -> Hex) : "; hex2 = QInt::DecToHex(dec2); cout << hex2;
	return 0;
}

/*int main(int argc, char* argv[])
int main(int argc, char* argv[])
{
	if (Calculator(argv[1], argv[2]) == true)
	{
@ -30,4 +32,4 @@ int main(int argc, char* argv[])
	}

	return 0;
}
}*/