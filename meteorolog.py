#! /usr/bin/env python3
# -*- encoding: utf-8 -*-

import serial
import curses
from time import sleep, localtime, strftime


def main(stdscr):
    arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=.1)

    stdscr.clear()
    curses.curs_set(0)      # Hide cursor

    clock_win = curses.newwin(2, 80, 0, 0)
    temp_win = curses.newwin(2, 80, 2, 0)

    while True:
        now = strftime("%H:%M:%S", localtime())
        clock_win.addstr(0, 0, now, curses.A_REVERSE)
        clock_win.refresh()

        line = arduino.readline()
        line = line.decode('utf-8').strip()

        if ":" in line:
            sensor, value = line.split(":")
            if sensor == "DS18B20":
                temp_win.addstr(0, 0, "Temperature: {:2.1f} °C".format(
                    float(value)))
                temp_win.refresh()

        sleep(1)

if __name__ == "__main__":
    try:
        curses.wrapper(main)
    except KeyboardInterrupt:
        print("Meteoro Log exit")
        print("Ctrl-C Keyboard Interrupt")
