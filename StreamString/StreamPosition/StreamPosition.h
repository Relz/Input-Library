class StreamPosition
{
public:
	static const long MIN_LINE = 1;
	static const long MIN_COLUMN = 1;

	explicit StreamPosition(long line = MIN_LINE, long column = MIN_COLUMN);
	long GetLine() const;
	void SetLine(long value);
	long GetColumn() const;
	void SetColumn(long value);
	void IncreaseLine(long value = 1);
	void IncreaseColumn(long value = 1);
	void DecreaseLine(long value = 1);
	void DecreaseColumn(long value = 1);
	void ResetColumn();
	bool operator==(const StreamPosition & other) const;
	bool operator!=(const StreamPosition & other) const;

private:
	long m_line = MIN_LINE;
	long m_column = MIN_COLUMN;

	void SafeSetLine(long value);
	void SafeSetColumn(long value);
};
