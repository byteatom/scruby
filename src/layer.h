#ifndef __SCRUBY_LAYER__
#define __SCRUBY_LAYER__

class Layer {
public:
	Layer() = delete;
	Layer(const Layer &) = delete;
	Layer &operator=(const Layer &) = delete;
	virtual ~Layer();

	byte *buf_ = nullptr;
	size_t len_ = 0;	
	bool malloc_ = false;
	
	Layer(size_t len);
	Layer(byte *buf, size_t len);

	virtual bool carry(Layer &payload) = 0;
	virtual Layer& operator+(Layer& right) = 0;
	bool operator>>(Netif& netif);
};

#endif