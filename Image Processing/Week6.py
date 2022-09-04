import cv2
import numpy as np
from matplotlib.pyplot import figure

FirstImage = cv2.imread("Egemen.jpg")
SecondImage = cv2.imread("PyhtonLogo.png")

NewImage = np.zeros(FirstImage.shape,FirstImage.dtype)

# Alpha = 0.30
# Beta = 0.70
# FinalImage = cv2.addWeighted(FirstImage,Alpha,SecondImage,Beta,0.00)
# cv2.imshow("Mixed Photo",FinalImage)

Contrast = 3.0
Bright = 2

for x in range(FirstImage.shape[0]):
    for y in range(FirstImage.shape[1]):
        for z in range(FirstImage.shape[2]):
            NewImage[x,y,z] = np.clip(Contrast * FirstImage[x,y,z] + Bright, 0, 255)

cv2.putText(NewImage, "I am a EGEMEN", (230, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2, cv2.LINE_AA)

figure(0)
cv2.imshow("First Image",FirstImage)
figure(1)
cv2.imshow("New Image",NewImage)

cv2.waitKey(0)
cv2.destroyAllWindows()
