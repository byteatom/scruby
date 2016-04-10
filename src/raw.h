#include "type.h"
#include "layer.h"

class Raw : public Layer {	
public:	
	enum {
		DEFAULT_HEAD_LEN = 1024,
	}
	
	u8 *buf_ = nullptr;
	u8 *head_ = nullptr;
	u8 *data_ = nullptr;
	u32 len_ = 0;
	bool memory_ = false;
	
	Payload() = delete;
	Payload(const Payload &data);
	Payload &operator=(const Payload &) = delete;
	Payload(u32 len);
	
	virtual ~Payload();
	
	void forward(u32 len);
};
