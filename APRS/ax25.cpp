#include <Arduino.h>

#include "ax25.h"
#include "APRS.h"


// MODULE GLOBALS
static uint16_t crc;
static uint8_t ones_in_a_row;
static uint16_t packet_size; // size in bits of packets
static uint8_t *packet;
static unsigned int maxPacketSize;  // bytes


// MODULE FUNCTIONS
static void update_crc(const uint8_t a_bit) {
    const uint16_t xor_int = crc ^ a_bit;   // XOR lsb of CRC with the latest bit
    crc >>= 1;                              // Shift 16-bit CRC one bit to the right
    if (xor_int & 0x0001) {                 // If XOR result from above has lsb set
        crc ^= 0x8408;                      // Shift 16-bit CRC one bit to the right
    }
    return;
}


// EXPORTED FUNCTIONS

void ax25_send_bit(const uint8_t a_bit, const uint8_t bitStuff) {
    if (bitStuff) {
        update_crc(a_bit);
    }
    if (a_bit) {
        packet[packet_size >> 3] |= (1 << (packet_size & 7));
        packet_size++;
        if (bitStuff && ++ones_in_a_row == 5) {
            ax25_send_bit(0, 0);
            ones_in_a_row = 0;
        }
    } else {
        ones_in_a_row = 0;
        packet[packet_size >> 3] &= ~(1 << (packet_size & 7));
        packet_size++;
    }
}


void ax25_send_byte(uint8_t a_byte) {
    uint8_t i = 0;
    while (i++ < 8) {
        ax25_send_bit(a_byte & 1, 1);
        a_byte >>= 1;
    }
}


void ax25_send_flag() {
    // Send 0x7e without bit stuffing
    ax25_send_bit(0, 0);
    for (int i = 0; i < 6; i++) {
        ax25_send_bit(1, 0);
    }
    ax25_send_bit(0, 0);
}


unsigned int ax25_getPacketSize() {
    return packet_size;
}


void ax25_send_string(const char * const string) {
    for (int i = 0; string[i]; i++) {
        ax25_send_byte(string[i]);
    }
}


void ax25_initBuffer(uint8_t *buf, const int bufSize) {
    packet = buf;
    maxPacketSize = bufSize;
    packet_size = 0;
    ones_in_a_row = 0;
    crc = 0xffff;
}


void ax25_send_header(const struct PathAddress * const paths,
                      const uint16_t nPaths,
                      const uint16_t preambleFlags) {

    uint16_t i, j;

    for (i = 0; i < preambleFlags; i++) {
        ax25_send_flag();
    }

    for (i = 0; i < nPaths; i++) {
        // Transmit callsign
        for (j = 0; paths[i].callsign[j]; j++) {
            ax25_send_byte(paths[i].callsign[j] << 1);
        }
    
        // Transmit pad
        for (; j < 6; j++) {
            ax25_send_byte(' ' << 1);
        }
    
        // Transmit SSID. Termination signaled with last bit = 1
        if (i == nPaths - 1) {
            ax25_send_byte(('0' + paths[i].ssid) << 1 | 1);
        }
        else {
            ax25_send_byte(('0' + paths[i].ssid) << 1);
        }
    }

    // Control field: 3 = APRS-UI frame
    ax25_send_byte(0x03);

    // Protocol ID: 0xf0 = no layer 3 data
    ax25_send_byte(0xf0);
}


void ax25_send_footer() {
    // Save the crc so that it can be treated it atomically
    uint16_t final_crc = crc;

    // Send the CRC
    ax25_send_byte(~(final_crc & 0xff));
    final_crc >>= 8;
    ax25_send_byte(~(final_crc & 0xff));

    // Signal the end of frame
    ax25_send_flag();
}
