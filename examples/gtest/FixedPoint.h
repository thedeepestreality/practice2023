#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H
#include <string>

template <int Size>
class FixedPoint {
private:
	int _integer;
	unsigned char _digits[Size] = {};

	void incrementDigits(){
		int idx;
		for (idx = Size-1; idx >= 0; --idx){
			if (++_digits[idx] < 10)
				break;
			_digits[idx] = 0;
		}
		if (idx == -1)
			++_integer;
	}
public:
	FixedPoint(double doubleVal = 0.0) : _integer(doubleVal) {
		doubleVal -= _integer;
		for (auto& c: _digits){
			doubleVal *= 10;
			c = doubleVal;
			doubleVal -= c;
		}
		if (doubleVal*10 >= 5)
			incrementDigits();
	}

	template <int OtherSize>
	FixedPoint(const FixedPoint<OtherSize>& val) : _integer(val._integer){
		int minSize = std::min(Size, OtherSize);
		for (int idx=0; idx<minSize; ++idx)
			_digits[idx] = val._digits[idx];
	}

	std::string toString() const {
		std::string intStr = std::to_string(_integer);
		std::string digitsStr;
		for (unsigned char c : _digits)
			digitsStr += c + '0';
		return intStr + std::string(".") + digitsStr;
	}

	template <int OtherSize>
	bool isEqual(const FixedPoint<OtherSize>& val)
	{
		int minSize = std::min(Size, OtherSize);
		for (int idx=0; idx<minSize; ++idx)
			if (_digits[idx] != val._digits[idx])
				return false;
		int maxSize = std::max(Size, OtherSize);
		const unsigned char* const maxPtr = (Size > OtherSize) ? _digits : val._digits;
		for (int idx=minSize; idx<maxSize - minSize; ++idx)
			if (maxPtr[idx] != 0)
				return false;
		return true;
	}
};

template <int LeftSize, int RightSize>
bool operator==(
	const FixedPoint<LeftSize>& left, 
	const FixedPoint<LeftSize>& right
){
	return left.isEqual(right);
}

std::string getVersion();

//const FixedPoint p(2);
//FixedPoint p();
//FixedPoint* p = new FixedPoint[10];

#endif
