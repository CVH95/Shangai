'''
Copyright (C) 2018 Xiaofeng Xiong and Poramate Manoonpong

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

'''

'''
Goal: Jacobian matrix of a 2-joint robot

(Expected) Result: calculating its joint torques given by the forces (i.e., q) of its end-effector

Subtask1: gen_EE(l0, l1, q)
Subtask2: eev
'''

from scipy import *

from matplotlib import *
from pylab import *

import numpy as np
import numpy.linalg as la

#Subtask1:
def gen_jacEET(l0, l1, q):
	JEET = np.zeros((2,2))
	
	# The transposed of the previous JEE (velocity) Jacobian matrix
	JEET[0,0] = -l0*np.sin(q[0]) - l1*np.sin(q[0] + q[1])
	JEET[0,1] = l0*np.cos(q[0]) + l1*np.cos(q[0] + q[1])
	JEET[1,0] = - l1*np.sin(q[0] + q[1])
	JEET[1,1] = l1*np.cos(q[0] + q[1]) 

	return JEET

L0 = 1.0
L1 = 1.0
q = [np.pi/4.0, np.pi*3.0/8.0]

#Jacobian - F_x -> tau_q

F_x = [1.0, 1.0]
F_x = np.asmatrix(F_x)
F_x = F_x.T

print 'Force vector: \n', F_x

Jeet = np.asmatrix(gen_jacEET(L0, L1, q)) 

print 'Jacobian Jee.T: \n', Jeet

#Subtask2:
qtor = Jeet*F_x

print 'The joint torques are: \n', qtor # python2.x

#print ('The joint torques are ', qtor) # python3.x