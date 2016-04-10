#include <string>

#define HAVE_REMOTE
#include <pcap.h>

using namespace std;

class Pcap {
public:
	Pcap(string name);

private:
	pcap_t *pcap;
};

class PcapIf {
public:
	PcapIf();
};

class PcapIfs {
public:
	PcapIfs();
	~PcapIfs();

	void init();

private:
	pcap_if_t *ifs;
	char *errBuf;
};



class PcapPkt {

};

class Netif {
public:
	Netif();
	~Netif();
	
	pcap_if_t *ifList_;
	pcap_t *pcap_;
	char errbuf_[PCAP_ERRBUF_SIZE];
	int timeout_;
	
	bool list();
	bool open(unsigned int index);
	bool open(string name);
	void close();
	bool recv();
};
