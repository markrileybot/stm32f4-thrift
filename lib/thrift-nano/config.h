
#ifndef __CONFIG_H__
#define __CONFIG_H__

/**
* override byteswap
*/
#define TN_BYTESWAP
#include <stdint.h>
int64_t bswap_64(int64_t x);
int32_t bswap_32(int64_t x);
int16_t bswap_16(int64_t x);
#define ntohll(x) bswap_64 (x)
#define ntohl(x)  bswap_32 (x)
#define ntohs(x)  bswap_16 (x)
#define htonll(x) bswap_64 (x)
#define htonl(x)  bswap_32 (x)
#define htons(x)  bswap_16 (x)

/**
 * Version stuff
 */
#define THRIFT_NANO_VERSION_MAJOR 0
#define THRIFT_NANO_VERSION_MINOR 1
#define THRIFT_NANO_VERSION_PATCH 0


/**
 * Configurable things
 * Note: If you modify this list you may want to update defs.h with defaults
 */

/**
 * Will you allow thrift_nano to allocate memory?
 */
#define THRIFT_ALLOC                    THRIFT_ALLOC_DEF
/**
 * Enabled binary protocol?
 */
#define THRIFT_PROTOCOL_BINARY          THRIFT_PROTOCOL_BINARY_DEF
/**
 * Enabled compact protocol? (requires binary)
 */
#define THRIFT_PROTOCOL_COMPACT         THRIFT_PROTOCOL_COMPACT_DEF

/**
 * Enabled file transport?
 */
#define THRIFT_TRANSPORT_FILE           0
/**
 * Enabled memory transport?
 */
#define THRIFT_TRANSPORT_MEMORY         0

#endif /* __CONFIG_H__ */
