/*
  The MIT License (MIT)

  Copyright (c) 2021 Liamaev Mihkail (kenny5660)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "clrc663.h"

/** @file */

// ---------------------------------------------------------------------------
// Command functions.
// ---------------------------------------------------------------------------

void CLRC663_cmd_read_E2(uint16_t address, uint16_t length) {
  uint8_t parameters[3] = {(uint8_t) (address >> 8), (uint8_t) (address & 0xFF), length};
  CLRC663_flush_fifo();
  CLRC663_write_fifo(parameters, 3);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_READE2);
}

void CLRC663_cmd_load_reg(uint16_t address, uint8_t regaddr, uint16_t length) {
  uint8_t parameters[4] = {(uint8_t) (address >> 8), (uint8_t) (address & 0xFF), regaddr, length};
  CLRC663_flush_fifo();
  CLRC663_write_fifo(parameters, 4);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_LOADREG);
}



void CLRC663_cmd_load_protocol(uint8_t rx, uint8_t tx) {
  uint8_t parameters[2] = {rx, tx};
  CLRC663_flush_fifo();
  CLRC663_write_fifo(parameters, 2);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_LOADPROTOCOL);
}

void CLRC663_cmd_transceive(const uint8_t* data, uint16_t len) {
  CLRC663_cmd_idle();
  CLRC663_flush_fifo();
  CLRC663_write_fifo(data, len);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_TRANSCEIVE);
}

void CLRC663_cmd_idle() {
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_IDLE);
}

void CLRC663_cmd_load_key_E2(uint8_t key_nr) {
  uint8_t parameters[1] = {key_nr};
  CLRC663_flush_fifo();
  CLRC663_write_fifo(parameters, 1);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_LOADKEYE2);
}

void CLRC663_cmd_auth(uint8_t key_type, uint8_t block_address, const uint8_t* card_uid) {
  CLRC663_cmd_idle();
  uint8_t parameters[6] = {key_type, block_address, card_uid[0], card_uid[1], card_uid[2], card_uid[3]};
  CLRC663_flush_fifo();
  CLRC663_write_fifo(parameters, 6);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_MFAUTHENT);
}

void CLRC663_cmd_load_key(const uint8_t* key) {
  CLRC663_cmd_idle();
  CLRC663_flush_fifo();
  CLRC663_write_fifo(key, 6);
  CLRC663_write_reg(CLRC663_REG_COMMAND, CLRC663_CMD_LOADKEY);
}

// ---------------------------------------------------------------------------
// Utility functions.
// ---------------------------------------------------------------------------

void CLRC663_flush_fifo() {
  CLRC663_write_reg(CLRC663_REG_FIFOCONTROL, 1<<4);
}

uint16_t CLRC663_fifo_length() {
  // should do 512 byte fifo handling here.
  return CLRC663_read_reg(CLRC663_REG_FIFOLENGTH);
}

void CLRC663_clear_irq0() {
  CLRC663_write_reg(CLRC663_REG_IRQ0, (uint8_t) ~(1<<7));
}
void CLRC663_clear_irq1() {
  CLRC663_write_reg(CLRC663_REG_IRQ1, (uint8_t) ~(1<<7));
}
uint8_t CLRC663_irq0() {
  return CLRC663_read_reg(CLRC663_REG_IRQ0);
}
uint8_t CLRC663_irq1() {
  return CLRC663_read_reg(CLRC663_REG_IRQ1);
}

uint8_t CLRC663_transfer_E2_page(uint8_t* dest, uint8_t page) {
  CLRC663_cmd_read_E2(page*64, 64);
  uint8_t res = CLRC663_fifo_length();
  CLRC663_read_fifo(dest, 64);
  return res;
}

void CLRC663_print_block(const uint8_t* data, uint16_t len) {
  uint16_t i;
  for (i=0; i < len; i++) {
    CLRC663_PRINTF("%02X ", data[i]);
  }
}

// ---------------------------------------------------------------------------
// Timer functions
// ---------------------------------------------------------------------------
void CLRC663_activate_timer(uint8_t timer, uint8_t active) {
  CLRC663_write_reg(CLRC663_REG_TCONTROL, ((active << timer) << 4) | (1 << timer));
}

void CLRC663_timer_set_control(uint8_t timer, uint8_t value) {
  CLRC663_write_reg(CLRC663_REG_T0CONTROL + (5 * timer), value);
}
void CLRC663_timer_set_reload(uint8_t timer, uint16_t value) {
  CLRC663_write_reg(CLRC663_REG_T0RELOADHI + (5 * timer), value >> 8);
  CLRC663_write_reg(CLRC663_REG_T0RELOADLO + (5 * timer), value & 0xFF);
}
void CLRC663_timer_set_value(uint8_t timer, uint16_t value) {
  CLRC663_write_reg(CLRC663_REG_T0COUNTERVALHI + (5 * timer), value >> 8);
  CLRC663_write_reg(CLRC663_REG_T0COUNTERVALLO + (5 * timer), value & 0xFF);
}
uint16_t CLRC663_timer_get_value(uint8_t timer) {
  uint16_t res = CLRC663_read_reg(CLRC663_REG_T0COUNTERVALHI + (5 * timer)) << 8;
  res += CLRC663_read_reg(CLRC663_REG_T0COUNTERVALLO + (5 * timer));
  return res;
}

// ---------------------------------------------------------------------------
// From documentation
// ---------------------------------------------------------------------------
void CLRC663_AN11145_start_IQ_measurement() {
  // Part-1, configurate LPCD Mode
  // Please remove any PICC from the HF of the reader.
  // "I" and the "Q" values read from reg 0x42 and 0x43
  // shall be used in part-2 "Detect PICC"
  //  reset CLRC663 and idle
  CLRC663_write_reg(0, 0x1F);
  // Should sleep here... for 50ms... can do without.
  CLRC663_write_reg(0, 0);
  // disable IRQ0, IRQ1 interrupt sources
  CLRC663_write_reg(0x06, 0x7F);
  CLRC663_write_reg(0x07, 0x7F);
  CLRC663_write_reg(0x08, 0x00);
  CLRC663_write_reg(0x09, 0x00);
  CLRC663_write_reg(0x02, 0xB0);  // Flush FIFO
  // LPCD_config
  CLRC663_write_reg(0x3F, 0xC0);  // Set Qmin register
  CLRC663_write_reg(0x40, 0xFF);  // Set Qmax register
  CLRC663_write_reg(0x41, 0xC0);  // Set Imin register
  CLRC663_write_reg(0x28, 0x89);  // set DrvMode register
  // Execute trimming procedure
  CLRC663_write_reg(0x1F, 0x00);  // Write default. T3 reload value Hi
  CLRC663_write_reg(0x20, 0x10);  // Write default. T3 reload value Lo
  CLRC663_write_reg(0x24, 0x00);  // Write min. T4 reload value Hi
  CLRC663_write_reg(0x25, 0x05);  // Write min. T4 reload value Lo
  CLRC663_write_reg(0x23, 0xF8);  // Config T4 for AutoLPCD&AutoRestart.Set AutoTrimm bit.Start T4.
  CLRC663_write_reg(0x43, 0x40);  // Clear LPCD result
  CLRC663_write_reg(0x38, 0x52);  // Set Rx_ADCmode bit
  CLRC663_write_reg(0x39, 0x03);  // Raise receiver gain to maximum
  CLRC663_write_reg(0x00, 0x01);  // Execute Rc663 command "Auto_T4" (Low power card detection and/or Auto trimming)
}

void CLRC663_AN11145_stop_IQ_measurement() {
  // Flush cmd and Fifo
  CLRC663_write_reg(0x00, 0x00);
  CLRC663_write_reg(0x02, 0xB0);
  CLRC663_write_reg(0x38, 0x12);  // Clear Rx_ADCmode bit
  //> ------------ I and Q Value for LPCD ----------------
  // CLRC663_read_reg(CLRC663_REG_LPCD_I_RESULT) & 0x3F
  // CLRC663_read_reg(CLRC663_REG_LPCD_Q_RESULT) & 0x3F
}

void CLRC663_AN1102_recommended_registers_skip(uint8_t protocol, uint8_t skip) {
  switch (protocol) {
    case CLRC663_PROTO_ISO14443A_106_MILLER_MANCHESTER:
      {
        const uint8_t buf[] = CLRC663_RECOM_14443A_ID1_106;
        CLRC663_write_regs(CLRC663_REG_DRVMOD+skip, buf+skip, sizeof(buf)-skip);
      }
      break;
    case CLRC663_PROTO_ISO14443A_212_MILLER_BPSK:
      {
        const uint8_t buf[] = CLRC663_RECOM_14443A_ID1_212;
        CLRC663_write_regs(CLRC663_REG_DRVMOD+skip, buf+skip, sizeof(buf)-skip);
      }
      break;
    case CLRC663_PROTO_ISO14443A_424_MILLER_BPSK:
      {
        const uint8_t buf[] = CLRC663_RECOM_14443A_ID1_424;
        CLRC663_write_regs(CLRC663_REG_DRVMOD+skip, buf+skip, sizeof(buf)-skip);
      }
      break;
    case CLRC663_PROTO_ISO14443A_848_MILLER_BPSK:
      {
        const uint8_t buf[] = CLRC663_RECOM_14443A_ID1_848;
        CLRC663_write_regs(CLRC663_REG_DRVMOD+skip, buf+skip, sizeof(buf)-skip);
      }
      break;
  }
}
void CLRC663_AN1102_recommended_registers(uint8_t protocol) {
  CLRC663_AN1102_recommended_registers_skip(protocol, 0);
}

void CLRC663_AN1102_recommended_registers_no_transmitter(uint8_t protocol) {
  CLRC663_AN1102_recommended_registers_skip(protocol, 5);
}


// ---------------------------------------------------------------------------
// ISO 14443A
// ---------------------------------------------------------------------------

uint16_t CLRC663_iso14443a_REQA() {
  return CLRC663_iso14443a_WUPA_REQA(CLRC663_ISO14443_CMD_REQA);
}
uint16_t CLRC663_iso14443a_WUPA() {
  return CLRC663_iso14443a_WUPA_REQA(CLRC663_ISO14443_CMD_WUPA);
}

uint16_t CLRC663_iso14443a_WUPA_REQA(uint8_t instruction) {
  CLRC663_cmd_idle();
  // CLRC663_AN1102_recommended_registers_no_transmitter(CLRC663_PROTO_ISO14443A_106_MILLER_MANCHESTER);
  CLRC663_flush_fifo();

  // Set register such that we sent 7 bits, set DataEn such that we can send
  // data.
  CLRC663_write_reg(CLRC663_REG_TXDATANUM, 7 | CLRC663_TXDATANUM_DATAEN);

  // disable the CRC registers.
  CLRC663_write_reg(CLRC663_REG_TXCRCPRESET, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_OFF);
  CLRC663_write_reg(CLRC663_REG_RXCRCCON, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_OFF);

  CLRC663_write_reg(CLRC663_REG_RXBITCTRL, 0);

  // ready the request.
  uint8_t send_req[] = {instruction};

  // clear interrupts
  CLRC663_clear_irq0();
  CLRC663_clear_irq1();

  // enable the global IRQ for Rx done and Errors.
  CLRC663_write_reg(CLRC663_REG_IRQ0EN, CLRC663_IRQ0EN_RX_IRQEN | CLRC663_IRQ0EN_ERR_IRQEN);
  CLRC663_write_reg(CLRC663_REG_IRQ1EN, CLRC663_IRQ1EN_TIMER0_IRQEN);  // only trigger on timer for irq1

  // configure a timeout timer.
  uint8_t timer_for_timeout = 0;

  // Set timer to 221 kHz clock, start at the end of Tx.
  CLRC663_timer_set_control(timer_for_timeout, CLRC663_TCONTROL_CLK_211KHZ | CLRC663_TCONTROL_START_TX_END);
  // Frame waiting time: FWT = (256 x 16/fc) x 2 FWI
  // FWI defaults to four... so that would mean wait for a maximum of ~ 5ms

  CLRC663_timer_set_reload(timer_for_timeout, 1000);  // 1000 ticks of 5 usec is 5 ms.
  CLRC663_timer_set_value(timer_for_timeout, 1000);

  // Go into send, then straight after in receive.
  CLRC663_cmd_transceive(send_req, 1);
  CLRC663_PRINTF("Sending REQA\n");
  // block until we are done
  uint8_t irq1_value = 0;
  while (!(irq1_value & (1 << timer_for_timeout))) {
    irq1_value = CLRC663_irq1();
    if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {  // either ERR_IRQ or RX_IRQ
      break;  // stop polling irq1 and quit the timeout loop.
    }
  }
  CLRC663_PRINTF("After waiting for answer\n");
  CLRC663_cmd_idle();

  // if no Rx IRQ, or if there's an error somehow, return 0
  uint8_t irq0 = CLRC663_irq0();
  if ((!(irq0 & CLRC663_IRQ0_RX_IRQ)) || (irq0 & CLRC663_IRQ0_ERR_IRQ)) {
    CLRC663_PRINTF("No RX, irq1: %hhx irq0: %hhx\n", irq1_value, irq0);
    return 0;
  }

  uint8_t rx_len = CLRC663_fifo_length();
  uint16_t res;
  CLRC663_PRINTF("rx_len: %hhd\n", rx_len);
  if (rx_len == 2) {  // ATQA should answer with 2 bytes.
    CLRC663_read_fifo((uint8_t*) &res, rx_len);

    CLRC663_PRINTF("ATQA answer: ");
    CLRC663_print_block((uint8_t*) &res, 2);
    CLRC663_PRINTF("\n");
    return res;
  }
  return 0;
}

uint8_t CLRC663_iso14443a_select(uint8_t* uid, uint8_t* sak) {
  CLRC663_cmd_idle();
  // CLRC663_AN1102_recommended_registers_no_transmitter(CLRC663_PROTO_ISO14443A_106_MILLER_MANCHESTER);
  CLRC663_flush_fifo();

  CLRC663_PRINTF("UID input: ");
  CLRC663_print_block(uid, 10);
  CLRC663_PRINTF("\n");

  CLRC663_PRINTF("\nStarting select\n");

  // we do not need atqa.
  // Bitshift to get uid_size; 0b00: single, 0b01: double, 0b10: triple, 0b11 RFU
  // uint8_t uid_size = (atqa & (0b11 << 6)) >> 6;
  // uint8_t bit_frame_collision = atqa & 0b11111;

  // enable the global IRQ for Rx done and Errors.
  CLRC663_write_reg(CLRC663_REG_IRQ0EN, CLRC663_IRQ0EN_RX_IRQEN | CLRC663_IRQ0EN_ERR_IRQEN);
  CLRC663_write_reg(CLRC663_REG_IRQ1EN, CLRC663_IRQ1EN_TIMER0_IRQEN);  // only trigger on timer for irq1

  // configure a timeout timer, use timer 0.
  uint8_t timer_for_timeout = 0;

  // Set timer to 221 kHz clock, start at the end of Tx.
  CLRC663_timer_set_control(timer_for_timeout, CLRC663_TCONTROL_CLK_211KHZ | CLRC663_TCONTROL_START_TX_END);
  // Frame waiting time: FWT = (256 x 16/fc) x 2 FWI
  // FWI defaults to four... so that would mean wait for a maximum of ~ 5ms

  CLRC663_timer_set_reload(timer_for_timeout, 1000);  // 1000 ticks of 5 usec is 5 ms.
  CLRC663_timer_set_value(timer_for_timeout, 1000);
  uint8_t cascade_level;
  for (cascade_level=1; cascade_level <= 3; cascade_level++) {
    uint8_t cmd = 0;
    uint8_t known_bits = 0;  // known bits of the UID at this level so far.
    uint8_t send_req[7] = {0};  // used as Tx buffer.
    uint8_t* uid_this_level = &(send_req[2]);
    // pointer to the UID so far, by placing this pointer in the send_req
    // array we prevent copying the UID continuously.
    uint8_t message_length;

    switch (cascade_level) {
      case 1:
        cmd = CLRC663_ISO14443_CAS_LEVEL_1;
        break;
      case 2:
        cmd = CLRC663_ISO14443_CAS_LEVEL_2;
        break;
      case 3:
        cmd = CLRC663_ISO14443_CAS_LEVEL_3;
        break;
    }

    // disable CRC in anticipation of the anti collision protocol
    CLRC663_write_reg(CLRC663_REG_TXCRCPRESET, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_OFF);
    CLRC663_write_reg(CLRC663_REG_RXCRCCON, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_OFF);


    // max 32 loops of the collision loop.
    uint8_t collision_n;
    for (collision_n=0; collision_n < 32; collision_n++) {
      CLRC663_PRINTF("\nCL: %hhd, coll loop: %hhd, kb %hhd long: ", cascade_level, collision_n, known_bits);
      CLRC663_print_block(uid_this_level, (known_bits + 8 - 1) / 8);
      CLRC663_PRINTF("\n");

      // clear interrupts
      CLRC663_clear_irq0();
      CLRC663_clear_irq1();


      send_req[0] = cmd;
      send_req[1] = 0x20 + known_bits;
      // send_req[2..] are filled with the UID via the uid_this_level pointer.

      // Only transmit the last 'x' bits of the current byte we are discovering
      // First limit the txdatanum, such that it limits the correct number of bits.
      CLRC663_write_reg(CLRC663_REG_TXDATANUM, (known_bits % 8) | CLRC663_TXDATANUM_DATAEN);

      // ValuesAfterColl: If cleared, every received bit after a collision is
      // replaced by a zero. This function is needed for ISO/IEC14443 anticollision (0<<7).
      // We want to shift the bits with RxAlign
      uint8_t rxalign = known_bits % 8;
      CLRC663_PRINTF("Setting rx align to: %hhd\n", rxalign);
      CLRC663_write_reg(CLRC663_REG_RXBITCTRL, (0<<7) | (rxalign<<4));


      // then sent the send_req to the hardware,
      // (known_bits / 8) + 1): The ceiled number of bytes by known bits.
      // +2 for cmd and NVB.
      if ((known_bits % 8) == 0) {
        message_length = ((known_bits / 8)) + 2;
      } else {
        message_length = ((known_bits / 8) + 1) + 2;
      }

      CLRC663_PRINTF("Send:%hhd long: ", message_length);
      CLRC663_print_block(send_req, message_length);
      CLRC663_PRINTF("\n");

      CLRC663_cmd_transceive(send_req, message_length);


      // block until we are done
      uint8_t irq1_value = 0;
      while (!(irq1_value & (1 << timer_for_timeout))) {
        irq1_value = CLRC663_irq1();
        // either ERR_IRQ or RX_IRQ or Timer
        if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {
          break;  // stop polling irq1 and quit the timeout loop.
        }
      }
      CLRC663_cmd_idle();

      // next up, we have to check what happened.
      uint8_t irq0 = CLRC663_irq0();
      uint8_t error = CLRC663_read_reg(CLRC663_REG_ERROR);
      uint8_t coll = CLRC663_read_reg(CLRC663_REG_RXCOLL);
      CLRC663_PRINTF("irq0: %hhX\n", irq0);
      CLRC663_PRINTF("error: %hhX\n", error);
      uint8_t collision_pos = 0;
      if (irq0 & CLRC663_IRQ0_ERR_IRQ) {  // some error occured.
        // Check what kind of error.
        // error = CLRC663_read_reg(CLRC663_REG_ERROR);
        if (error & CLRC663_ERROR_COLLDET) {
          // A collision was detected...
          if (coll & (1<<7)) {
            collision_pos = coll & (~(1<<7));
            CLRC663_PRINTF("Collision at %hhX\n", collision_pos);
            // This be a true collision... we have to select either the address
            // with 1 at this position or with zero
            // ISO spec says typically a 1 is added, that would mean:
            // uint8_t selection = 1;

            // However, it makes sense to allow some kind of user input for this, so we use the
            // current value of uid at this position, first index right byte, then shift such
            // that it is in the rightmost position, ten select the last bit only.
            // We cannot compensate for the addition of the cascade tag, so this really
            // only works for the first cascade level, since we only know whether we had
            // a cascade level at the end when the SAK was received.
            uint8_t choice_pos = known_bits + collision_pos;
            uint8_t selection = (uid[((choice_pos + (cascade_level-1)*3)/8)] >> ((choice_pos) % 8))&1;


            // We just OR this into the UID at the right position, later we
            // OR the UID up to this point into uid_this_level.
            uid_this_level[((choice_pos)/8)] |= selection << ((choice_pos) % 8);
            known_bits++;  // add the bit we just decided.

            CLRC663_PRINTF("uid_this_level now kb %hhd long: ", known_bits);
            CLRC663_print_block(uid_this_level, 10);
            CLRC663_PRINTF("\n");

          } else {
            // Datasheet of CLRC663:
            // bit 7 (CollPosValid) not set:
            // Otherwise no collision is detected or
            // the position of the collision is out of the range of bits CollPos.
            CLRC663_PRINTF("Collision but no valid collpos.\n");
            collision_pos = 0x20 - known_bits;
          }
        } else {
          // Can this ever occur?
          collision_pos = 0x20 - known_bits;
          CLRC663_PRINTF("No collision, error was: %hhx, setting collision_pos to: %hhx\n", error, collision_pos);
        }
      } else if (irq0 & CLRC663_IRQ0_RX_IRQ) {
        // we got data, and no collisions, that means all is well.
        collision_pos = 0x20 - known_bits;
        CLRC663_PRINTF("Got data, no collision, setting to: %hhx\n", collision_pos);
      } else {
        // We have no error, nor received an RX. No response, no card?
        return 0;
      }
      CLRC663_PRINTF("collision_pos: %hhX\n", collision_pos);

      // read the UID Cln so far from the buffer.
      uint8_t rx_len = CLRC663_fifo_length();
      uint8_t buf[5];  // Size is maximum of 5 bytes, UID[0-3] and BCC.

      CLRC663_read_fifo(buf, rx_len < 5 ? rx_len : 5);

      CLRC663_PRINTF("Fifo %hhd long: ", rx_len);
      CLRC663_print_block(buf, rx_len);
      CLRC663_PRINTF("\n");

      CLRC663_PRINTF("uid_this_level kb %hhd long: ", known_bits);
      CLRC663_print_block(uid_this_level, (known_bits + 8 - 1) / 8);
      CLRC663_PRINTF("\n");
      // move the buffer into the uid at this level, but OR the result such that
      // we do not lose the bit we just set if we have a collision.
      uint8_t rbx;
      for (rbx = 0; (rbx < rx_len); rbx++) {
        uid_this_level[(known_bits / 8) + rbx] |= buf[rbx];
      }
      known_bits += collision_pos;
      CLRC663_PRINTF("known_bits: %hhX\n", known_bits);

      if ((known_bits >= 32)) {
        CLRC663_PRINTF("exit collision loop: uid_this_level kb %hhd long: ", known_bits);
        CLRC663_print_block(uid_this_level, 10);
        CLRC663_PRINTF("\n");

        break;  // done with collision loop
      }
    }  // end collission loop

    // check if the BCC matches
    uint8_t bcc_val = uid_this_level[4];  // always at position 4, either with CT UID[0-2] or UID[0-3] in front.
    uint8_t bcc_calc = uid_this_level[0]^uid_this_level[1]^uid_this_level[2]^uid_this_level[3];
    if (bcc_val != bcc_calc) {
      CLRC663_PRINTF("Something went wrong, BCC does not match.\n");
      return 0;
    }

    // clear interrupts
    CLRC663_clear_irq0();
    CLRC663_clear_irq1();

    send_req[0] = cmd;
    send_req[1] = 0x70;
    // send_req[2,3,4,5] // contain the CT, UID[0-2] or UID[0-3]
    send_req[6] = bcc_calc;
    message_length = 7;

    // Ok, almost done now, we reenable the CRC's
    CLRC663_write_reg(CLRC663_REG_TXCRCPRESET, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_ON);
    CLRC663_write_reg(CLRC663_REG_RXCRCCON, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_ON);

    // reset the Tx and Rx registers (disable alignment, transmit full bytes)
    CLRC663_write_reg(CLRC663_REG_TXDATANUM, (known_bits % 8) | CLRC663_TXDATANUM_DATAEN);
    uint8_t rxalign = 0;
    CLRC663_write_reg(CLRC663_REG_RXBITCTRL, (0 << 7) | (rxalign << 4));

    // actually send it!
    CLRC663_cmd_transceive(send_req, message_length);
    CLRC663_PRINTF("send_req %hhd long: ", message_length);
    CLRC663_print_block(send_req, message_length);
    CLRC663_PRINTF("\n");

    // Block until we are done...
    uint8_t irq1_value = 0;
    while (!(irq1_value & (1 << timer_for_timeout))) {
      irq1_value = CLRC663_irq1();
      if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {  // either ERR_IRQ or RX_IRQ
        break;  // stop polling irq1 and quit the timeout loop.
      }
    }
    CLRC663_cmd_idle();

    // Check the source of exiting the loop.
    uint8_t irq0_value = CLRC663_irq0();
    if (irq0_value & CLRC663_IRQ0_ERR_IRQ) {
      // Check what kind of error.
      uint8_t error = CLRC663_read_reg(CLRC663_REG_ERROR);
      if (error & CLRC663_ERROR_COLLDET) {
        // a collision was detected with NVB=0x70, should never happen.
        return 0;
      }
    }

    // Read the sak answer from the fifo.
    uint8_t sak_len = CLRC663_fifo_length();
    if (sak_len != 1) {
      return 0;
    }
    uint8_t sak_value;
    CLRC663_read_fifo(&sak_value, sak_len);

    CLRC663_PRINTF("SAK answer: ");
    CLRC663_print_block(&sak_value, 1);
    CLRC663_PRINTF("\n");

    if (sak_value & (1 << 2)) {
      // UID not yet complete, continue with next cascade.
      // This also means the 0'th byte of the UID in this level was CT, so we
      // have to shift all bytes when moving to uid from uid_this_level.
      uint8_t UIDn;
      for (UIDn=0; UIDn < 3; UIDn++) {
        // uid_this_level[UIDn] = uid_this_level[UIDn + 1];
        uid[(cascade_level-1)*3 + UIDn] = uid_this_level[UIDn + 1];
      }
    } else {
      // Done according so SAK!
      // Add the bytes at this level to the UID.
      uint8_t UIDn;
      for (UIDn=0; UIDn < 4; UIDn++) {
        uid[(cascade_level-1)*3 + UIDn] = uid_this_level[UIDn];
      }

      *sak = sak_value;
      // Finally, return the length of the UID that's now at the uid pointer.
      return cascade_level*3 + 1;
    }

    CLRC663_PRINTF("Exit cascade %hhd long: ", cascade_level);
    CLRC663_print_block(uid, 10);
    CLRC663_PRINTF("\n");
  }  // cascade loop
  return 0;  // getting an UID failed.
}

// ---------------------------------------------------------------------------
// MIFARE
// ---------------------------------------------------------------------------

uint8_t CLRC663_MF_auth(const uint8_t* uid, uint8_t key_type, uint8_t block) {
  // Enable the right interrupts.

  // configure a timeout timer.
  uint8_t timer_for_timeout = 0;  // should match the enabled interupt.

  // According to datashet Interrupt on idle and timer with MFAUTHENT, but lets
  // include ERROR as well.
  CLRC663_write_reg(CLRC663_REG_IRQ0EN, CLRC663_IRQ0EN_IDLE_IRQEN | CLRC663_IRQ0EN_ERR_IRQEN);
  CLRC663_write_reg(CLRC663_REG_IRQ1EN, CLRC663_IRQ1EN_TIMER0_IRQEN);  // only trigger on timer for irq1

  // Set timer to 221 kHz clock, start at the end of Tx.
  CLRC663_timer_set_control(timer_for_timeout, CLRC663_TCONTROL_CLK_211KHZ | CLRC663_TCONTROL_START_TX_END);
  // Frame waiting time: FWT = (256 x 16/fc) x 2 FWI
  // FWI defaults to four... so that would mean wait for a maximum of ~ 5ms

  CLRC663_timer_set_reload(timer_for_timeout, 2000);  // 2000 ticks of 5 usec is 10 ms.
  CLRC663_timer_set_value(timer_for_timeout, 2000);

  uint8_t irq1_value = 0;

  CLRC663_clear_irq0();  // clear irq0
  CLRC663_clear_irq1();  // clear irq1

  // start the authentication procedure.
  CLRC663_cmd_auth(key_type, block, uid);

  // block until we are done
  while (!(irq1_value & (1 << timer_for_timeout))) {
    irq1_value = CLRC663_irq1();
    if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {
      break;  // stop polling irq1 and quit the timeout loop.
    }
  }

  if (irq1_value & (1 << timer_for_timeout)) {
    // this indicates a timeout
    return 0;  // we have no authentication
  }

  // status is always valid, it is set to 0 in case of authentication failure.
  uint8_t status = CLRC663_read_reg(CLRC663_REG_STATUS);
  return (status & CLRC663_STATUS_CRYPTO1_ON);
}

uint8_t CLRC663_MF_read_block(uint8_t block_address, uint8_t* dest) {
  CLRC663_flush_fifo();

  CLRC663_write_reg(CLRC663_REG_TXCRCPRESET, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_ON);
  CLRC663_write_reg(CLRC663_REG_RXCRCCON, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_ON);

  uint8_t send_req[2] = {CLRC663_MF_CMD_READ, block_address};

  // configure a timeout timer.
  uint8_t timer_for_timeout = 0;  // should match the enabled interupt.

  // enable the global IRQ for idle, errors and timer.
  CLRC663_write_reg(CLRC663_REG_IRQ0EN, CLRC663_IRQ0EN_IDLE_IRQEN | CLRC663_IRQ0EN_ERR_IRQEN);
  CLRC663_write_reg(CLRC663_REG_IRQ1EN, CLRC663_IRQ1EN_TIMER0_IRQEN);


  // Set timer to 221 kHz clock, start at the end of Tx.
  CLRC663_timer_set_control(timer_for_timeout, CLRC663_TCONTROL_CLK_211KHZ | CLRC663_TCONTROL_START_TX_END);
  // Frame waiting time: FWT = (256 x 16/fc) x 2 FWI
  // FWI defaults to four... so that would mean wait for a maximum of ~ 5ms
  CLRC663_timer_set_reload(timer_for_timeout, 2000);  // 2000 ticks of 5 usec is 10 ms.
  CLRC663_timer_set_value(timer_for_timeout, 2000);

  uint8_t irq1_value = 0;
  uint8_t irq0_value = 0;

  CLRC663_clear_irq0();  // clear irq0
  CLRC663_clear_irq1();  // clear irq1

  // Go into send, then straight after in receive.
  CLRC663_cmd_transceive(send_req, 2);

  // block until we are done
  while (!(irq1_value & (1 << timer_for_timeout))) {
    irq1_value = CLRC663_irq1();
    if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {
      break;  // stop polling irq1 and quit the timeout loop.
    }
  }
  CLRC663_cmd_idle();

  if (irq1_value & (1 << timer_for_timeout)) {
    // this indicates a timeout
    return 0;
  }

  irq0_value = CLRC663_irq0();
  if (irq0_value & CLRC663_IRQ0_ERR_IRQ) {
    // some error
    return 0;
  }

  // all seems to be well...
  uint8_t buffer_length = CLRC663_fifo_length();
  uint8_t rx_len = (buffer_length <= 16) ? buffer_length : 16;
  CLRC663_read_fifo(dest, rx_len);
  return rx_len;
}

// The read and write block functions share a lot of code, the parts they have in common could perhaps be extracted
// to make it more readable.

uint8_t CLRC663_MF_write_block(uint8_t block_address, const uint8_t* source) {
  CLRC663_flush_fifo();

  // set appropriate CRC registers, only for Tx
  CLRC663_write_reg(CLRC663_REG_TXCRCPRESET, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_ON);
  CLRC663_write_reg(CLRC663_REG_RXCRCCON, CLRC663_RECOM_14443A_CRC | CLRC663_CRC_OFF);
  // configure a timeout timer.
  uint8_t timer_for_timeout = 0;  // should match the enabled interupt.

  // enable the global IRQ for idle, errors and timer.
  CLRC663_write_reg(CLRC663_REG_IRQ0EN, CLRC663_IRQ0EN_IDLE_IRQEN | CLRC663_IRQ0EN_ERR_IRQEN);
  CLRC663_write_reg(CLRC663_REG_IRQ1EN, CLRC663_IRQ1EN_TIMER0_IRQEN);

  // Set timer to 221 kHz clock, start at the end of Tx.
  CLRC663_timer_set_control(timer_for_timeout, CLRC663_TCONTROL_CLK_211KHZ | CLRC663_TCONTROL_START_TX_END);
  // Frame waiting time: FWT = (256 x 16/fc) x 2 FWI
  // FWI defaults to four... so that would mean wait for a maximum of ~ 5ms
  CLRC663_timer_set_reload(timer_for_timeout, 2000);  // 2000 ticks of 5 usec is 10 ms.
  CLRC663_timer_set_value(timer_for_timeout, 2000);

  uint8_t irq1_value = 0;
  uint8_t irq0_value = 0;

  uint8_t res;

  uint8_t send_req[2] = {CLRC663_MF_CMD_WRITE, block_address};

  CLRC663_clear_irq0();  // clear irq0
  CLRC663_clear_irq1();  // clear irq1

  // Go into send, then straight after in receive.
  CLRC663_cmd_transceive(send_req, 2);

  // block until we are done
  while (!(irq1_value & (1 << timer_for_timeout))) {
    irq1_value = CLRC663_irq1();
    if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {
      break;  // stop polling irq1 and quit the timeout loop.
    }
  }
  CLRC663_cmd_idle();

  // check if the first stage was successful:
  if (irq1_value & (1 << timer_for_timeout)) {
    // this indicates a timeout
    return 0;
  }
  irq0_value = CLRC663_irq0();
  if (irq0_value & CLRC663_IRQ0_ERR_IRQ) {
    // some error
    return 0;
  }
  uint8_t buffer_length = CLRC663_fifo_length();
  if (buffer_length != 1) {
    return 0;
  }
  CLRC663_read_fifo(&res, 1);
  if (res != CLRC663_MF_ACK) {
    return 0;
  }

  CLRC663_clear_irq0();  // clear irq0
  CLRC663_clear_irq1();  // clear irq1

  // go for the second stage.
  CLRC663_cmd_transceive(source, 16);

  // block until we are done
  while (!(irq1_value & (1 << timer_for_timeout))) {
    irq1_value = CLRC663_irq1();
    if (irq1_value & CLRC663_IRQ1_GLOBAL_IRQ) {
      break;  // stop polling irq1 and quit the timeout loop.
    }
  }

  CLRC663_cmd_idle();

  if (irq1_value & (1 << timer_for_timeout)) {
    // this indicates a timeout
    return 0;
  }
  irq0_value = CLRC663_irq0();
  if (irq0_value & CLRC663_IRQ0_ERR_IRQ) {
    // some error
    return 0;
  }

  buffer_length = CLRC663_fifo_length();
  if (buffer_length != 1) {
    return 0;
  }
  CLRC663_read_fifo(&res, 1);
  if (res == CLRC663_MF_ACK) {
    return 16;  // second stage was responded with ack! Write successful.
  }

  return 0;
}

void CLRC663_MF_deauth() {
  CLRC663_write_reg(CLRC663_REG_STATUS, 0);
}

void CLRC663_MF_example_dump() {
  uint16_t atqa = CLRC663_iso14443a_REQA();
  if (atqa != 0) {  // Are there any cards that answered?
    uint8_t sak;
    uint8_t uid[10] = {0};  // uids are maximum of 10 bytes long.

    // Select the card and discover its uid.
    uint8_t uid_len = CLRC663_iso14443a_select(uid, &sak);

    if (uid_len != 0) {  // did we get an UID?
      CLRC663_PRINTF("UID of %hhd bytes (SAK:0x%hhX): ", uid_len, sak);
      CLRC663_print_block(uid, uid_len);
      CLRC663_PRINTF("\n");

      // Use the manufacturer default key...
      uint8_t FFkey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

      CLRC663_cmd_load_key(FFkey);  // load into the key buffer

      // Try to athenticate block 0.
      if (CLRC663_MF_auth(uid, CLRC663_MF_AUTH_KEY_A, 0)) {
        CLRC663_PRINTF("Yay! We are authenticated!\n");

        // Attempt to read the first 4 blocks.
        uint8_t readbuf[16] = {0};
        uint8_t len;
        uint8_t b;
        for (b=0; b < 4 ; b++) {
          len = CLRC663_MF_read_block(b, readbuf);
          CLRC663_PRINTF("Read block 0x%hhX: ", b);
          CLRC663_print_block(readbuf, len);
          CLRC663_PRINTF("\n");
        }
        CLRC663_MF_deauth();  // be sure to call this after an authentication!
      } else {
        CLRC663_PRINTF("Could not authenticate :(\n");
      }
    } else {
      CLRC663_PRINTF("Could not determine UID, perhaps some cards don't play");
      CLRC663_PRINTF(" well with the other cards? Or too many collisions?\n");
    }
  } else {
    CLRC663_PRINTF("No answer to REQA, no cards?\n");
  }
}
