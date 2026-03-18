#pragma once
class Score {
private:
	int value;

public:
	Score() : value(0) {}

	void Add(int _amount) {
		value += _amount;
	}

	void Reset() {
		value = 0;
	}

	inline int GetValue() const { return value; }
};

