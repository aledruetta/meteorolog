#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import serial
import tkinter as tk
from time import strftime, localtime, sleep
from tkinter import ttk
from tkinter.constants import *

TEMP1 = "DS18B20"


class App(ttk.Frame):
    def __init__(self, root):
        super().__init__(root, padding="5 5 5 5")
        self.root = root
        Sensor("Temp1", "DS18B20")

    def interface(self):
        self.pack(fill=BOTH, expand=YES)

        # Shortcuts
        self.root.protocol("WM_DELETE_WINDOW", self.destroyWin)
        self.root.bind('<Control-q>', self.destroyWin)

        # Port entry
        port_frame = ttk.Frame(self)
        port_frame.pack(fill=X, expand=YES)

        port_label = ttk.Label(port_frame, text="Port: ")
        port_label.pack(side=LEFT)

        self.port = tk.StringVar()
        self.port_entry = ttk.Entry(port_frame, width=30,
                                    textvariable=self.port)
        self.port_entry.bind("<Return>", self.board)
        self.port_entry.pack(side=LEFT)

        self.port_entry.focus_set()

        # Port Button
        self.port_button = ttk.Button(port_frame, text="Ok", command=self.board)
        self.port_button.pack(side=LEFT)

        # Clock
        clock_frame = ttk.Frame(self)
        clock_frame.pack(fill=X, expand=YES)

        self.time = tk.StringVar()
        clock_label = ttk.Label(clock_frame, textvariable=self.time)
        clock_label.pack(fill=X, expand=YES)

        # Sensors
        sensors_frame = ttk.Frame(self)
        sensors_frame.pack(fill=BOTH, expand=YES)

        for i in range(len(Sensor.sensor_lst)):
            tag = Sensor.sensor_lst[i].tag
            sensor_label = ttk.Label(sensors_frame,
                                     text="{}: ".format(tag))
            sensor_label.grid(column=0, row=i)

        self.temp1 = tk.StringVar()
        temp1_val = ttk.Label(sensors_frame, textvariable=self.temp1)
        temp1_val.grid(column=1, row=0)

    def board(self, event=False):
        self.port_entry.unbind("<Return>")
        self.port_entry['foreground'] = 'blue'
        self.port_entry['state'] = "readonly"

        self.port_button.deletecommand(str(self.port_button.cget('command')))
        self.port_button['state'] = DISABLED

        try:
            self.arduino = serial.Serial(self.port.get(), 9600, timeout=0.1)
        except serial.SerialException as err:
            print(str(err))
            sys.exit(2)
        else:
            self.start()

    def start(self):
        codes = Sensor.code_lst()
        while True:
            self.update_clock()
            self.read_sensors(codes)
            try:
                self.update()       # update_idletasks()
            except Exception:
                sys.exit(2)
            sleep(1)

    def update_clock(self):
        str_f_time = strftime("%H:%M:%S", localtime())
        self.time.set(str_f_time)

    def read_sensors(self, codes):
        reads = []
        line = self.arduino.readline()
        line = line.decode('utf-8').strip()
        while line != "::END READS::":
            line = self.arduino.readline()
            line = line.decode('utf-8').strip()
            try:
                sensor, value = line.split(":", maxsplit=1)
            except ValueError:
                continue
            else:
                if sensor in codes:
                    reads.append((sensor, value))

        for sensor, value in reads:
            if sensor == TEMP1:
                self.temp1.set(value)

    def destroyWin(self, event=None):
        try:
            self.root.destroy()
        except Exception:
            sys.exit(0)


class Sensor:
    sensor_lst = []

    def __init__(self, tag, code):
        self.tag = tag
        self.code = code
        self.value = 0
        Sensor.sensor_lst.append(self)

    @staticmethod
    def code_lst():
        return [sensor.code for sensor in Sensor.sensor_lst]


def main():
    root = tk.Tk()
    root.title("MeteoroLog")
    root.resizable(width=False, height=False)
    app = App(root)
    app.interface()
    root.mainloop()

if __name__ == "__main__":
    main()
