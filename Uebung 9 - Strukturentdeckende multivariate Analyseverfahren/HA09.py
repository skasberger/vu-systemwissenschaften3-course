# -*- coding: utf-8 -*-
"""
Spyder Editor

This temporary script file is located here:
/home/chris/.spyder2/.temp.py
"""

import rpy2 as r
import rpy2.robjects as r
import numpy as n

data = robjects.FloatVector([1,2,7,8,8,3,2,3,5,6,1,2,8,9,1,4,6,5,8,9,1,5,8,7])
datamat = robjects.r['matrix'](data,nrow=3)

