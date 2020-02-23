/*
CPPM Decoder
This routine decodes a CPPM stream froman RC receiver. It supports 8 channels. The polarity of the CPPM
stream doesn't matter; it will work whether it is inverted or not. It assumes the following protocol:
Sync - high for > 10ms
Low - .4ms
High - .6-1.6ms (ch1)
Low - .4ms
High - .6-1.6ms (ch2)
Low - .4ms
High - .6-1.6ms (ch3)
Low - .4ms
High - .6-1.6ms (ch4)
Low - .4ms
High - .6-1.6ms (ch5)
Low - .4ms
High - .6-1.6ms (ch6)
Low - .4ms
High - .6-1.6ms (ch7)
Low - .4ms
High - .6-1.6ms (ch8)
Low - .4ms
Sync - high
This version uses micros(), which uses TIMER0
*/

void cppm_isr() {
  int16_t width = micros() -  last_time;
  last_time = micros();
  if (width < 900) {  // "spacer" pulse - do nothing
    return;
  }
  if (width < 2100) { // channel pulse. Get pulse width
    chan[ch_sel] = width;
    ch_sel++;
    return;
  }
  if (ch_sel != CPPM_CHANNELS) {  // error condition. Don't save data in this case. Frame gets discarded.
    ch_sel = 0;
    err_flag = 1; // set error flag for debug
    return;
  }
// Sync pulse detected
// Convert data to single byte variables so they can be read in the main loop asynchronously without errors.
// Current channel setup: CH2 = throttle, CH3 = steering, CH4 = arm servo. Radio is assumed to be T-A-E-R-servo, but can be
// whatever the user wants by remapping channels in the radio, or in the channel assignments below.
  ch_sel = 0;
  chan[3] = (chan[3] - 1000)/4;
  chan[2] = (chan[2] - 1000)/4;
  if (chan[3] < 0 ) chan[3] = 0;
  if (chan[3] > 255) chan[3] =255;
  if (chan[2] < 0 ) chan[2] = 0;
  if (chan[2] > 255) chan[2] =255;
  ch_thr = chan[2];
  ch_str = chan[3];
  if ((chan[4] > 1900) && (chan[4] < 2100))ch_svo = 1; else ch_svo = 0; // servo activates if this channel is maximum
  cppm_rdy = 1; // data ready flag
  return;
}
