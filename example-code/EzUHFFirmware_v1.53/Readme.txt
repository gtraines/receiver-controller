Types of firmware
=================

There are different types of firmwares, supporting different functionalities and 
different type of hardware. The firmware can be identified by various postfixes 
in the filename

Hardware:
- Transmitter: 
   * EzUHF TX: Tx500
   * EzUHF TX 2W: Tx2W
   * EzUHF JR Module: _TxJRModule_
- Receiver:
   * EzUHF 4CH: _Rx4ch_
   * EzUHF 8CH: _Rx8ch_
   * EzUHF 8CHLite: _Rx8chLite

Firmware specific functionalities:
- Tx:
   * PPM input by default
   * DSM2/DSMX input (only supported by JR module): _race_
- Rx: 
   * PPM output by default
   * sbus output: _race_sbus_
   * inverted sbus output: _race_sbus_inverted_
- All:
   * UK frequencies: _UK

Dynamic Settings in ImmersionRCTools
====================================

Number of transmitted channels
------------------------------
All firmwares now support setting of the number of channels that are transmitted 
over the air. This permits to send less data, improving link quality and 
transmission speed.
Tx and Rx in race/SBus/standard mode can work together, if the number of 
transmitted channel is set to the same on both and they were bound together after 
configuration.

For receiver PPM output, number of channels output can be set, to lower time of 
output. The number of PPM output channel can be different than the number of
channels sent over the air, to allow for additional channels for UPSTAT, Link 
Quality and RSSI.

Synchronised mode
-----------------
Synchronised PPM is synchronised to the Tx and emits a frame as soon as it is 
received. When no frame is received, nothing is output. This mode is used for 
miniquads and needs a failsafe setup in the flight controller.

Unsynchronised PPM is the traditional EzUHF mode, has a bit higher latency, but
supports failsafe output.

Transmitters also support synchronised or unsynchronised mode, to send out channel
information as soon as they get it and avoid adding latency. This can be set in
ImmersionRCTools. 

The SBus Rx and DSM2/DSMX Tx both only support synchronised mode.

Center and Endpoints
--------------------
When using SBus output, check max and min of the signal in your flight controller and 
set center and endpoints in the remote to have the correct range. Not all flight controller
use the same values.


