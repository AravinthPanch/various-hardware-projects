#sudo apt-get install python-serial
#on Pi - /boot/cmdline.txt should be 'dwc_otg.lpm_enable=0 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait'
#on Pi - /etc/inittab should be commented like this #T0:23:respawn:/sbin/getty -L ttyAMA0 115200 vt100
# screen /dev/ttyAMA0 115200  .... OR
# minicom -b 115200 -o -D /dev/ttyAMA0 as an terminal to talk to UART

#Tx and Rx of Pi can be connected directly and two sceen or minicom sessions can be opened to send serial data across Pi itself

import serial

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)

while True:
    port.write("\r\nSay something:")
    rcv = port.read(10)
    port.write("\r\nYou sent:" + repr(rcv))
