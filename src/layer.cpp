Layer::Layer(size_t len) : 
	len_(len), malloc_(true) {
	buf_ = new byte[len_];
}

Layer::Layer(byte *buf, size_t len) : 
	buf_(buf), len_(len), malloc_(true) {
}

Layer::~Layer() {
	if (malloc_) delete buf_;
}

bool Layer::operator>>(Netif& netif) {
	return netif << *this;
}

