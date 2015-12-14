#! /usr/bin/env python
# coding: utf-8

import curses
from arduino import Arduino
from time import sleep, strftime, localtime


class CliApp:
    def __init__(self, clock_w, sensor_w, ino):
        self.clock_win = clock_w
        self.sensor_win = sensor_w
        self.arduino = ino

    def run(self):
        freq = 5
        count = 0
        self.show_reads()
        while True:
            self.clock()
            if count == freq:
                self.show_reads()
                count = 0
            count += 1
            sleep(1)

    def clock(self):
        now = strftime("%H:%M:%S", localtime())
        self.clock_win.addstr(0, 0, " {} MeteoroLog Real Time ".format(now),
                              curses.A_REVERSE)
        self.clock_win.refresh()

    def show_reads(self):
        self.arduino.read_sensors()

        line = 0
        for sensor in self.arduino.sensors:
            self.sensor_win.addstr(line, 1, "{:<11} {:02.1f} {}".format(
                sensor["tag"] + ":", sensor["value"], sensor["unit"]))
            line += 1

        self.sensor_win.refresh()


def main(stdscr, port):
    stdscr.clear()
    curses.curs_set(0)      # Hide cursor

    ino = Arduino(port)

    clock_w = curses.newwin(2, curses.COLS, 0, 0)
    sensor_w = curses.newwin(len(ino.sensors), curses.COLS, 2, 0)

    app = CliApp(clock_w, sensor_w, ino)
    app.run()
