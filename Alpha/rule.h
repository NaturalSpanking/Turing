#ifndef ruleH
#define ruleH

struct rule
{
	WideChar symbol;
	int shift;
	int new_state;
	int is_breakpoint;
	rule()
	{
		symbol = ' ';
		shift = -2;
		new_state = -1;
		is_breakpoint = -1;
	}
	friend bool operator== (rule &l, rule &r)
	{
		if (l.is_breakpoint == r.is_breakpoint && l.new_state == r.new_state && l.shift == r.shift && l.symbol == r.symbol) return 1;
		return 0;
	}
};

#endif

