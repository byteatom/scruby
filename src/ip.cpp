#include "ip.h"
#include "util.h"

bool IpAddr::isClassA() {
    return (addr_ & MASK_CLASSB) == MASK_CLASSA;
}

bool IpAddr::isClassB() {
    return (addr_ & MASK_CLASSC) == MASK_CLASSB;
}

bool IpAddr::isClassC() {
    return (addr_ & MASK_CLASSD) == MASK_CLASSC;
}

bool IpAddr::isClassD() {
    return (addr_ & MASK_CLASSE) == MASK_CLASSD;
}

