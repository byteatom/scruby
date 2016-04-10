#include "pcapx.h"

#include <memory>
#include <exception>

PcapIfs::PcapIfs() : ifs(nullptr)
{
	errBuf = new char[PCAP_ERRBUF_SIZE];
	init();
}

PcapIfs::~PcapIfs()
{
	if (ifs) pcap_freealldevs(ifs);
	delete errBuf;
}

void PcapIfs::init()
{
	if (ifs) pcap_freealldevs(ifs);
	pcap_findalldevs(&ifs, errBuf);
}

Netif::Netif():ifList_(nullptr), pcap_(nullptr), timeout_(0)
{
	errbuf_[0] = 0;
	return;
}

Netif::~Netif()
{
	if (nullptr != ifList_) pcap_freealldevs(ifList_);
	if (nullptr != pcap_) pcap_close(pcap_);
}

bool Netif::list()
{	
	if (nullptr != ifList_) 
	{
		pcap_freealldevs(ifList_);
		ifList_ = nullptr;
	}	
	
	if (0 != pcap_findalldevs(&ifList_, errbuf_) || nullptr == ifList_)
	{
		return false;
	}

	int i = 0;
	for (pcap_if_t *dev = ifList_; dev != nullptr; dev = dev->next, i++)
	{
		for (pcap_addr *pcapAddr = dev->addresses; nullptr != pcapAddr; pcapAddr = pcapAddr->next)
		{
		}
	}

	if (0 == i)
	{
		return false;
	}

	return true;
}

bool Netif::open(unsigned int index)
{
	if (nullptr == ifList_) return false;	
	
	unsigned int i = 0;
	pcap_if_t *dev = nullptr;
	for (i = 0, dev = ifList_; i < index && nullptr != dev; dev = dev->next, i++);

	if (nullptr == dev) return false;

	if (nullptr != pcap_)
	{
		pcap_close(pcap_);
		pcap_ = nullptr;
	}
	
	pcap_ = pcap_create(dev->name, errbuf_);
	if (nullptr == pcap_)
	{
		return false;
	}
	pcap_set_snaplen(pcap_, 65536);
	pcap_set_promisc(pcap_, 1);
	/*if (pcap_can_set_rfmon(pcap_))
		pcap_set_rfmon(pcap_, 1);*/
	pcap_set_timeout(pcap_, timeout_);
	//pcap_set_buffer_size(pcap_, 32768);
	
	if (0 != pcap_activate(pcap_))
		return false;

	return true;
}

void Netif::close()
{

	if (nullptr != pcap_)
	{
		pcap_close(pcap_);
		pcap_ = nullptr;
	}
	return;
}


