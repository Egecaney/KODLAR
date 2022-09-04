import numpy as np
import matplotlib.pyplot as plt
from skimage import io, color
import cv2

img = cv2.imread("Findit.jpg")
[height, wide] = img.shape[:2]

# gray = color.rgb2gray(morph)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
equalized = cv2.equalizeHist(gray)
plt.imshow(equalized)
plt.show()

thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)[1]
plt.imshow(thresh)
plt.show()

contours = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
contours = contours[0] if len(contours) == 2 else contours[1]
big_contour = max(contours, key=cv2.contourArea)

result1 = img.copy()
cv2.drawContours(result1, [big_contour], 0, (255,255,255), 1)

contour = np.zeros((img.shape[:2]), dtype=np.uint8)
result2 = np.zeros_like(img)
cv2.drawContours(contour, [big_contour], 0, 255, -1)
result2[contour > 0] = img[contour > 0]

kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (150,150))
morph = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel)
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (1,1))
morph = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel)

for i in range (height):
  for j in range (wide):
    morph[i,j] = 125-morph[i,j]


plt.imshow(morph)
plt.show()
