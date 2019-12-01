import cv2 
from zhangsuen2 import ZhangSuen
import numpy as np
from preprocess import preprocess
import features
import helper
import os
import sys


from test_file import MiTest, obtener_similitud, nivel_similitud

for i in range(8):
	a="BD/"+str(i)+"_2.jpg"
	b="BD/"+str(i)+"_1.jpg"
	image = cv2.imread(a,0)
	img2 = cv2.imread(b,0)

	#cv2.namedwindow("My first OpenCV window")

	test1 = MiTest(image, img2)

	fv1,fo1 = test1._original_o()
	fv2,fo2 = test1._rotar_o()


	sl = obtener_similitud(fv1,fv2)

	b1 = sl[0]
	b2 = sl[1]

	pv1, po1 = test1.convertir_a_polar(fo1,b1)
	pv2, po2 = test1.convertir_a_polar(fo2,b2)

	ml = nivel_similitud(pv1,pv2,fv1,fv2)
	print(ml, "Desbloqueado" if (ml>0.3) else "No Desbloqueado")


