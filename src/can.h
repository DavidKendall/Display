/*
 * A simple CAN driver for FRDM-K64F
 * 
 * 11-bit identifiers only; no acceptance filtering
 * 
 * DK - 29-01-2019
 */

#ifndef __CAN_H
#define __CAN_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct canMessage {
  uint32_t id;
  uint32_t len;
  uint32_t dataA;
  uint32_t dataB; 
} canMessage_t;

typedef void (*canISR_t)(canMessage_t *msg);
/*
 * Initialises the CAN controller
 * Called by bspInit() in the standard project
 * configuration.
 */
void canInit(bool loopback);


/*
 * Note that the CAN message data fields dataA and dataB
 * are written and read in little-endian order on the FRDM-K64F
 * e.g. the values dataA = 0x04030201 and dataB = 0x08070605
 * will be transmitted in the order 01, 02, 03, 04, 05, 06, 07, 08
 *
 * Also the CAN receive buffers are not reset
 * on each message reception, so if a long message is transmitted
 * followed by a short message, the extraneous bytes from the long
 * message may remain in the receive buffers.
 * e.g. Assume you send a message of length 8 with dataA and dataB
 * as above, followed by a message of length 3 with dataA = 0x000B0A09
 * and dataB = 0, then canRead may return a message with
 * dataA = 0x040B0A09 and dataB = 0x08070605, i.e. only the number of bytes
 * indicated by the message length can be assumed to be valid; the 
 * remaining bytes should be assumed to be any old rubbish
 */
bool canWrite(canMessage_t *message);
void canRead(canMessage_t *message);


/* Returns true if there is data ready to be read from
 * CAN port 'port'; otherwise returns false
 */
bool canReady(void);


/*
 * Returns the value of the CAN status register 
 */
uint32_t canStatus(void);

/* Enables receive interrupts on the CAN controller
 * and installs 'handler' as the interrupt handler
 */
//void canRxInterrupt(pVoidFunc_t handler);
  
#ifdef __cplusplus
}
#endif

#endif

