#!/usr/bin/env python
import pygame
import serial
import time

# This code will play piano sounds according to recieved serial data

# /dev/ttyACM0 corresponds to Arduino USB connection
# 9600 baud is enough
ser = serial.Serial('/dev/ttyACM0', 9600)
debug = False

# You may change the following settings to customize your piano
# Refer to : https://www.pygame.org/docs/ref/mixer.html#pygame.mixer.pre_init
pygame.mixer.pre_init(22050,-16,2,64)
pygame.mixer.init()
pygame.init()

while True :
    number = str(int(ser.readline(), 16))
    # number corresponds to one piano key (from 1 to 88)
    
    if debug:
        print(number)
    
    file = '../WAV/' + number + ".wav"
    pygame.mixer.music.load(file)
    pygame.mixer.music.play(0)
