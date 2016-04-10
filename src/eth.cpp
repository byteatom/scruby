#include <cstdio>
#include <string>
#include <stdexcept>
#include "eth.h"
#include "sock.h"

Mac::Mac(const Bin bin) {
 	if (nullptr == bin)		
         throw std::invalid_argument("");

	memcpy(bin_, bin, MAC_OCT_LEN);

	return;
}

Mac::Mac(const Str str) {
	if (nullptr == str)		
         throw std::invalid_argument("");
	
    int tmp[MAC_OCT_LEN];
    if (MAC_OCT_LEN == sscanf(str, "%2x:%2x:%2x:%2x:%2x:%2x", &tmp[0], &tmp[1], &tmp[2], &tmp[3], &tmp[4], &tmp[5])) {
        for (int i = 0; i < MAC_OCT_LEN; i++)
            bin_[i] = tmp[i];        
    } else
    	throw std::invalid_argument("");

    return;
}

inline bool Mac::isBroadcast() {
    for (int i = 0; i < MAC_OCT_LEN; i++) {
        if (0xFF != bin_[0]) return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Mac& mac) {
	MacStr macStr;
    sprintf(macStr, "%02x:%02x:%02x:%02x:%02x:%02x", 
		mac.bin_[0], mac.bin_[1], mac.bin_[2], mac.bin_[3], mac.bin_[4], mac.bin_[5]);
	return os << macStr;
}

Eth::Eth() : Layer(LEN_FRAME_MAX), head_(buf_)
{
	return;
}

Eth::Eth(byte *buf, size_t len) : Layer(buf, len), head_(buf_)
{		
	return;
}

Eth::~Eth()
{
	return;
}

inline bool Eth::isEth2()
{
	return (nullptr != head_ && 
			ntohs(head_->protocol.untag.typeLen) >= ETH_TYPE_MIN);
}

inline bool Eth::is802dot3()
{
	return (nullptr != head_ && 
			ntohs(head_->protocol.untag.typeLen) <= LEN_PAYLOAD_MAX);
}

inline bool Eth::isNovell()
{
	return (nullptr != head_ && 
			is802dot3() &&
			head_->protocol.untag.llc.dsap == 0xFF && 
			head_->protocol.untag.llc.ssap == 0xFF);
}

inline bool Eth::isLlc()
{
	return (nullptr != head_ && 
			is802dot3() && !isNovell());
}

inline bool Eth::isSnap()
{
	return (nullptr != head_ && 
			isLlc()  &&
			head_->protocol.untag.llc.dsap == 0xAA &&
			head_->protocol.untag.llc.ssap == 0xAA);
}

inline bool Eth::isDot1q()
{
	return (nullptr != head_ && 
			ntohs(head_->protocol.dot1q.qTag.tpid) == ETH_TYPE_DOT1Q);
}

inline bool Eth::isDot1ad()
{
	return (nullptr != head_ && 
			ntohs(head_->protocol.dot1ad.sTag.tpid) == ETH_TYPE_DOT1AD &&
			ntohs(head_->protocol.dot1ad.cTag.tpid) == ETH_TYPE_DOT1Q);
}

inline bool Eth::isTaged()
{
	return (isDot1q() || isDot1ad());
}

bool Eth::setType(EthType type) {
	if (type <= ETH_TYPE_MIN) return false;
	head_->
}

bool Eth::setLength(size_t len) {
	
}

bool Eth::setSrc(Mac mac) {
}

bool Eth::setDst(Mac mac) {
}

Layer& Eth::operator+(Layer& right) {
	right.carry(*this);
	return right;
}

