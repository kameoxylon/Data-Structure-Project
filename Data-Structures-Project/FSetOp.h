
template<typename T>
class FSetOp
{
public:
	enum typeOp
	{
		INS,
		DEL
	};
	int key;
	bool done;
	bool resp;

	FSetOp(enum type, int key)
	{
		this->done = false;
		this->key = key;
		this->resp = false;
		this->typeOp = type;
	}
};