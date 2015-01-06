
#ifndef __CONFIG_H__
#define __CONFIG_H__

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
