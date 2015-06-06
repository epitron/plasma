from math import *
import os
import time

width = 60
height = 40

def clear():
  print "\x1b[2J",

def home():
  print "\x1b[H",


def dim(val):
  greyscale = "@MBHENR#KWXDFPQASUZbdehx*8Gm&04LOVYkpq5Tagns69owz$CIu23Jcfry%1v7l+it[]{}?j|()=~!-/<>\\\"^_';,:`. "
  return greyscale[int(min(1.0,max(0.0,val))*(len(greyscale)-1))]

def render(i):
  i = i/1000.0
  for y in range(0,height):
    line = ""
    for x in range(0,width):
      # line += dim(sin(tan(cos(x*y*(i/4)))))
      line += dim(((sin(y*(i/(cos(x))))*tan(x*i))*(i/(x+1)))*(i*(y+1)))
      # line += dim(sin( sin(x*i) * cos(y*i) ))
    print line

i = 1
clear()
while True:
  home()
  render(i)
  i+=1
  time.sleep(0.01)
