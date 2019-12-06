#!/usr/bin/env python
import pygame
import serial
import time
ser = serial.Serial('/dev/ttyACM0',9600)
pygame.mixer.pre_init(22050,-16,2,64)
pygame.mixer.init()
pygame.init()

while True :
    s=str(int( ser.readline(),16 ))
    print(s)
    chemin = '/home/alban/Documents/WAV/' + s + ".wav"
    pygame.mixer.music.load(chemin)
    pygame.mixer.music.play(0)
    
