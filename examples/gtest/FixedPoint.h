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
	FixedPoint(const FixedPoint<OtherSize>& val) : _integer(val.getInteger()){
		int minSize = std::min(Size, OtherSize);
		const unsigned char* otherDigits = val.getDigits();
		for (int idx=0; idx<minSize; ++idx)
			_digits[idx] = otherDigits[idx];
	}

	// std::string toString() const {
	// 	std::string intStr = std::to_string(_integer);
	// 	std::string digitsStr(Size, 0);
	// 	for (int idx = 0; idx < Size; ++idx)
	// 		digitsStr[idx] = _digits[idx] + '0';
	// 	return intStr + std::string(".") + digitsStr;
	// }

	std::string toString() const {
		std::string intStr = std::to_string(_integer);
		std::string result(Size + intStr.size() + 1, '.');
		result.replace(0, intStr.size(), intStr);
		for (int idx = 0; idx < Size; ++idx)
			result[idx + intStr.size() + 1] = _digits[idx] + '0';
		return result;
	}

	template <int OtherSize>
	bool isEqual(const FixedPoint<OtherSize>& val) const
	{
		int minSize = std::min(Size, OtherSize);
		const unsigned char* otherDigits = val.getDigits();
		for (int idx=0; idx<minSize; ++idx)
			if (_digits[idx] != otherDigits[idx])
				return false;
		int maxSize = std::max(Size, OtherSize);
		const unsigned char* const maxPtr = (Size > OtherSize) ? _digits : otherDigits;
		for (int idx=minSize; idx<maxSize - minSize; ++idx)
			if (maxPtr[idx] != 0)
				return false;
		return true;
	}

	int getInteger() const{
		return _integer;
	}

	const unsigned char* getDigits() const {
		return _digits;
	}

	template <int OtherSize>
	FixedPoint& operator+=(const FixedPoint<OtherSize>& val){
		_integer += val.getInteger();
		int minSize = std::min(Size, OtherSize);
		int rem = 0;
		const unsigned char* otherDigits = val.getDigits();
		if (Size < OtherSize && otherDigits[Size] >= 5)
			rem = 1;
		for (int idx = minSize-1; idx >= 0; --idx){
			_digits[idx] += otherDigits[idx] + rem;
			rem = _digits[idx] > 9;
			_digits[idx] -= rem*10;
		}
		_integer += rem;
		return *this;
	}

	FixedPoint& operator+=(const FixedPoint& val){
		_integer += val._integer;
		int rem = 0;
		for (int idx = Size-1; idx >= 0; --idx){
			_digits[idx] += val._digits[idx] + rem;
			rem = _digits[idx] > 9;
			_digits[idx] -= rem*10;
		}
		_integer += rem;
		return *this;
	}
};

template <int LeftSize, int RightSize>
bool operator==(
	const FixedPoint<LeftSize>& left, 
	const FixedPoint<RightSize>& right
){
	return left.isEqual(right);
}

template <int Size>
FixedPoint<Size> operator+(const FixedPoint<Size>& left, const FixedPoint<Size> right){
	FixedPoint<Size> result(left);
	result += right;
	return result;
}

template <int LeftSize, int RightSize, int MaxSize = std::max(LeftSize, RightSize)>
FixedPoint<MaxSize> operator+(const FixedPoint<LeftSize>& left, const FixedPoint<RightSize> right){
	FixedPoint<MaxSize> leftWiden(left);
	FixedPoint<MaxSize> rightWiden(right);
	leftWiden += rightWiden;
	return leftWiden;
}

//const FixedPoint p(2);
//FixedPoint p();
//FixedPoint* p = new FixedPoint[10];

#endif
