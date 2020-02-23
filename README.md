# B-Robot_RC
 B-Robot Software with Radio Control Added

This software is based in the open source software from jjrobots. This software
runs on the Devia board version of the B-Robot. Radio control has been added,
and wifi control was removed. For radio control, an RC receiver with PPM/CPPM
is required. The PPM pin is connected to the D13 pin, which is available on J17
of the Devia board. 5V and ground are required also, which can be picked up on
J16.

The following RC receivers have been tested with this code:

Brand   Model     Protocol  channels
Frsky   XSR       Frsky     8
Orange  R610 V2   DSM2      6

The parameter "CPPM_CHANNELS" must be set to the number of channels to match the receiver.


