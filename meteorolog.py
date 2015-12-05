#! /usr/bin/env python3
# -*- encoding: utf-8 -*-

import sys
import getopt
import serial
import curses
from time import sleep, localtime, strftime

ONE_WIRE_DIGITAL_TEMP = "DS18B20"


def usage():
    print("""usage:

    Set arduino baudrate = 9600

    ./meteorolog.py -p [port]
    ./meteorolog.py --port=[port]
""")


def clock(clock_win):
    now = strftime("%H:%M:%S", localtime())
    clock_win.addstr(0, 0, now, curses.A_REVERSE)
    clock_win.refresh()


def show_data(arduino, sensors_win):
    line = arduino.readline()
    line = line.decode('utf-8').strip()
    if (":" not in line) or (line[-1] == ":"):
        return

    sensor, value = line.split(":")
    if sensor == ONE_WIRE_DIGITAL_TEMP:
        sensors_win.addstr(0, 0, "Temperature: {:2.1f} °C".format(
            float(value)))
        sensors_win.refresh()


def main(stdscr, port):
    try:
        arduino = serial.Serial(port, 9600, timeout=0.1)
    except serial.SerialException as err:
        stdscr.addstr(str(err))
        stdscr.getch()
        sys.exit(2)

    stdscr.clear()
    curses.curs_set(0)      # Hide cursor

    clock_win = curses.newwin(2, curses.COLS, 0, 0)
    sensors_win = curses.newwin(5, curses.COLS, 2, 0)

    while True:
        clock(clock_win)                    # Show clock
        show_data(arduino, sensors_win)     # Show sensors data
        sleep(1)

if __name__ == "__main__":
    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:", ["port="])
    except getopt.GetoptError as err:
        print("Error:", str(err))
        usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-p", "--port"):
            port = arg

    try:
        curses.wrapper(main, port)      # Call main(stdscr, port)
    except KeyboardInterrupt:
        print("Exit MeteoroLog: Ctrl-C Keyboard Interrupt")
    except NameError as err:
        print("Error:", str(err))
        usage()
        sys.exit(2)
