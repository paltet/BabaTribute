
#define NUM_KEYS 256

class Input
{
public:
	Input();
	~Input();

	enum KEY_STATE {KEY_IDLE, KEY_PRESSED, KEY_HOLD, KEY_RELEASED};

	void init();
	void update(bool newKeys[]);

	KEY_STATE getKey(int key);

private:

	KEY_STATE keys[NUM_KEYS];
};

