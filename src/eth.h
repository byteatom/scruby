#include <string>
#include "type.h"
#include "data.h"

using namespace std;

/*most-significant octet(big-endian) and least-significant bit(LSB, little-endian) first*/

class Mac
{
public:	
	static const int MAC_OCT_LEN = 6;
	static const int MAC_STR_LEN = 18;	/*include terminated 0*/

	typedef octet Bin[MAC_OCT_LEN];
	typedef char Str[MAC_STR_LEN];

	Bin bin_;
	
	Mac(const Bin macBin);
	Mac(const Str macStr);

	
	inline bool isUnicast() { return 0x0 == (bin_[0] | 0x1); };
	inline bool isIndividual() { return isUnicast(); }; 
	inline bool isMulticast() { return 0x1 == (bin_[0] | 0x1); };
	inline bool isGroup() { return isMulticast(); };
	inline bool isBroadcast();
	inline bool isGlobal() { return 0x0 == (bin_[0] | 0x2); };
	inline bool isLocal() { return 0x1 == (bin_[0] & 0x2); };	
};

std::ostream& operator<<(std::ostream& os, const Mac& mac);

class Eth : public Layer{
public:
	
	enum {
		LEN_FRAME_MIN = 64,

		LEN_FRAME_UNTAG_MAX = 1518,
		LEN_FRAME_TAGED_MAX = 1522,

		LEN_FRAME_MAX = 1522,
		
		LEN_HEAD_UNTAG = 14,
		LEN_HEAD_DOT1Q = 18,
		LEN_HEAD_DOT1AD = 22,

		LEN_PAYLOAD_UNTAG_MIN = 46,
		LEN_PAYLOAD_DOT1Q_MIN = 42,
		LEN_PAYLOAD_DOT1AD_MIN = 38,
		
		LEN_PAYLOAD_MAX = 1500,	/*DOT1Q also*/
		LEN_PAYLOAD_DOT1AD_MAX = 1496,

		LEN_FCS = 4,
	};

	typedef enum {
		ETH_TYPE_MIN		= 0x0600,	/*1536*/
		ETH_TYPE_IPV4		= 0x0800,
		ETH_TYPE_ARP		= 0x0806,
		ETH_TYPE_DOT1Q		= 0x8100,
		ETH_TYPE_IPV6		= 0x86DD,
		ETH_TYPE_DOT1AD		= 0x88a8,
	}EthType;

	typedef struct {
		u16 tpid;	/*Tag Protocol Identifier*/
		u16 tci;	/*Tag Control Information*/
	}Tag;

	typedef struct {
		Mac::Bin dst;
		Mac::Bin src;
		union {
			union UnTag{			
				u16 typeLen;
				struct {
					octet dsap;
					octet ssap;
					octet control;
					struct {
						octet oui[3];
						octet type[2];
					}snap;
				}llc;
			}untag;
			struct {
				Tag qTag;
				union UnTag untag;
			}dot1q;
			struct {
				Tag sTag;
				Tag cTag;
				union UnTag untag;
			}dot1ad;
		} protocol;
	}Header;

	Header *head_ = nullptr;
	
	Eth();
	Eth(const Eth &) = delete;
	Eth &operator=(const Eth &) = delete;
	virtual ~Eth();
	
	Eth(byte *buf, size_t len);

	bool isEth2();	/*dix*/	
	bool is802dot3();
	bool isLlc();
	bool isSnap();
	bool isNovell();	/*raw 802.3*/
	bool isDot1q();
	bool isDot1ad();
	bool isTaged();


	bool setType(EthType type);
	bool setLength(size_t len);
	bool setSrc(Mac mac);
	bool setDst(Mac mac);

	virtual bool carry(Layer &payload);
	virtual Layer& operator+(Layer& right);
};