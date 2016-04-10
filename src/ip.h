#include <string>
#include "sock.h"
#include "type.h"
#include "layer.h"

using namespace std;

class IpAddr {
public:
    IpAddr(unsigned int address);
    IpAddr(string address);

    enum {
        MASK_CLASS_A = 0,
        MASK_CLASS_B = 0x80000000,
        MASK_CLASS_C = 0xC0000000,
        MASK_CLASS_D = 0xE0000000,
        MASK_CLASS_E = 0xE0000000,
    };

    u32 addr_;

    static char *sockaddrToString(const sockaddr *addr, char *inBuf = nullptr);

    bool isClassA();
    bool isClassB();
    bool isClassC();
    bool isClassD();

    bool isUnicast();
    inline bool isMulticast() { return isClassD(); };
    bool isBroadcast();

    bool isPrivate();

    string toString();
};

class Ip : public Payload {
public:

    typedef struct {
        u8  version: 4,
        ihl: 4;      /*Internet Header Length is the length of the internet header in 32
                    bit words, and thus points to the beginning of the data, min:5, max: 15*/
        u8 tos;     /*Type of Service*/
        u16 totalLen;
        u16 id;
        u16 frag;
        u8 ttl;
        u8 protocol;
        u16 checksum;
        u32 srcAddr;
        u32 dstAddr;
        /*option or data*/
    } Head;

    Head *head_;

    Ip(u32 srcAddr, u32 dstAddr);

};

