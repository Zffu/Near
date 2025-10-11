namespace near {

enum NearType {
	INTEGER,
	BOOLEAN,
	STRING,

	FILE_STREAM,
	COMPILER
};

class NearValue {
protected:
	void* data;

public:
	NearType type;
	bool is_array;
	
	NearValue(NearType type, bool is_array, void* data) {
		this->type = type;
		this->is_array = is_array;
		this->data = data;
	}
};

class NearInt: public NearValue {

}

}