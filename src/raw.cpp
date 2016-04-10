#include <stdexcept>

Payload::Payload(u32 len)
{
	len_ = len + DEFAULT_HEAD_LEN;
	buf_ = new u8[len_];
	head_ = data_ = buf_ + DEFAULT_HEAD_LEN;
	memory_ = true;
	return;
}

Payload::Payload(const Payload &payload)
{
	len_ = payload.len_;
	buf_ = payload.buf_;
	head_ = payload.head_;
	data_ = payload.data_;
	memory_ = false;
	payload.addUser(this);
	return;
}

Payload::~Payload()
{
	if (memory_)
		delete buf_;
	return;
}

void Payload::forward(u32 len)
{
	if (head_ - len >= buf_) {
		data_ = head_;
		head_ = head_ - len;
	} else
		throw std::length_error("");

	return;
}


