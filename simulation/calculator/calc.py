#!/usr/bin/python

import math

desired = 7.97194
real = -0.07967

phase_des = math.cos(desired)
phase_real = math.cos(real)

value_des = math.sin(desired)
value_real = math.sin(real)

error = phase_des - phase_real

des_deg = phase_des*360/(2*math.pi)
real_deg = phase_real*360/(2*math.pi)

print "Desired Phase = " + str(phase_des)
print "Real Phase = " + str(phase_real)
print "Phase Error = " + str(error)

corrected_real = phase_real + error

if(desired>0):
    corrected = value_real*value_real + corrected_real*corrected_real
else:
    corrected = value_real*value_real + corrected_real*corrected_real
    corrected = - corrected
    
print "Corrected Phase = " + str(corrected_real)
print "Corrected Point = " + str(corrected)
