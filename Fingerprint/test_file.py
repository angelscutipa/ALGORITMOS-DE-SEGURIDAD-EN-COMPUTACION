import cv2 
from zhangsuen2 import ZhangSuen
import numpy as np
from preprocess import preprocess
import features
import helper
from rotation import correctrotation
import constants as const
from helper import shiftcorrection, cropfingerprint
import scipy

dir = "salida_imagen/"

def obtener_similitud(fv1,fv2):

	s = 0
	x,y = None,None
	for i in range(len(fv1)):
		for j in range(len(fv2)):
			si = helper.similarity(fv1[i],fv2[j])

			if si>s:
				x=i
				y=j 
				s = si

	return x,y,s

def nivel_similitud(pv1,pv2, fv1, fv2):

	ml = np.zeros((len(pv1),len(pv2)))

	for i in range((len(pv1))):
		for j in range((len(pv2))):
			if np.all(np.abs(pv1[i]-pv2[j]) > const.BG):
				continue

			ml[i,j] = 0.5 + (0.5*helper.similarity(fv1[i], fv2[j]))
			
	sum = 0
	count = 0
	while ml.any() != 0:
		ind = np.argmax(ml)
		x,y = ind//len(pv2), ind%(len(pv2))
		if ml[x,y] != 0.5: sum = sum + ml[x,y]

		ml[x] = 0
		ml[:,y] = 0
		count = count + 1

	return (sum/count)






class MiTest:

	def __init__(self, img1, img2):

		self.image = img1.copy()

		self.rotated = img2.copy()

		self.checker1 = 0
		self.checker2 = 0

	def _original_o(self):

		img2 = self.image.copy()

		imgd = img2.copy()


		cv2.imwrite(dir + "input.jpg", imgd)

		image, m, orientations = preprocess(imgd)
		for i in range(image.shape[0]):
			for j in range(image.shape[1]):
				if image[i][j] > 50: image[i][j] = 1
				else: image[i][j] = 0


		image, xmax, xmin, ymax, ymin = cropfingerprint(image)
		orientations = orientations[xmin:xmax+1, ymin:ymax+1]


		cv2.imwrite(dir + "imagen_mejorada.jpg", image*255)
		z = ZhangSuen(image)
		img = z.performThinning()
		thinned = img.copy()
		cv2.imwrite(dir + "salida_adelgazado.jpg", (1-img)*255)

		coords, mask = z.extractminutiae(thinned)
		cv2.imwrite(dir + "salida_minucias.jpg", mask*255 )
		fincoords = z.remove_minutiae(coords, cv2.imread(dir + "input.jpg", 0)[xmin:xmax+1, ymin:ymax+1])

		vector = z.get_ridge_count(fincoords, image)
		feature_vectors = features.get_features(fincoords,vector,orientations)

		return feature_vectors

	def _rotar_o(self):


		img2 = self.rotated.copy()

		rotd = img2.copy()
		cv2.imwrite(dir + "template.jpg", rotd)
		image, m, orientations = preprocess(rotd)
		for i in range(image.shape[0]):
			for j in range(image.shape[1]):
				if image[i][j] > 50: image[i][j] = 1
				else: image[i][j] = 0


		image, xmax, xmin, ymax, ymin = cropfingerprint(image)
		orientations = orientations[xmin:xmax+1, ymin:ymax+1]


		cv2.imwrite(dir + "imagen_mejorada-template.jpg", image*255)
		z = ZhangSuen(image)
		img = z.performThinning()
		thinned = img.copy()
		cv2.imwrite(dir + "salida_adelgazado-template.jpg", (1-img)*255)

		coords, mask = z.extractminutiae(thinned)
		cv2.imwrite(dir + "salida_minucias_t.jpg", mask*255 )
		fincoords = z.remove_minutiae(coords, cv2.imread(dir + "template.jpg", 0)[xmin:xmax+1, ymin:ymax+1])

		vector = z.get_ridge_count(fincoords, image)
		feature_vectors = features.get_features(fincoords,vector,orientations)

		return feature_vectors


	def convertir_a_polar(self, obj, index):

		base = obj[index]

		polars = []
		polar_obj = []
		for current in obj:
			cur = features.FeaturePolar(current,base)
			polars.append(cur.convert())
			polar_obj.append(cur)

		return polars, polar_obj




