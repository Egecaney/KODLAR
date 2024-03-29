from cv2 import cv2
import numpy as np
import serial
import time
import schedule
from serial import Serial

ArduinoSerial = serial.Serial(port='COM1', baudrate=9600, timeout=.01)

""" 09.03.2022 BİRDEN FAZLA ÇEMBERİ HAFIZADA TUTAN KODUN SON HALİ. BUNDAN SONRA TEKLİYE GERİ DÖNÜLDÜ"""
""" KULLANILAN FONKSIYONLAR """

def PutTargetInfo(VideoFrame, x, y, r):

    """ Tespit edilen cemberi ve bilgilerini bastirir """

    HedefBilgisix = " ".join(["x:", str(x)])
    HedefBilgisiy = " ".join(["y:", str(y)])
    HedefBilgisir = " ".join(["r:", str(r)])

    cv2.circle(VideoFrame, (x, y), r, (0, 255, 0), 4)
    cv2.rectangle(VideoFrame, (x - 5, y - 5), (x + 5, y + 5), (0, 0, 255), -1)
    cv2.putText(VideoFrame, HedefBilgisix, (x + r, y - 50), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0,), 2,
                cv2.LINE_AA)
    cv2.putText(VideoFrame, HedefBilgisiy, (x + r, y - 30), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0,), 2,
                cv2.LINE_AA)
    cv2.putText(VideoFrame, HedefBilgisir, (x + r, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0,), 2,
                cv2.LINE_AA)

def RemoveNoise_Filter(VideoFrame):
        """ Tüm filtreleme & noise azaltma islemleri burda yapilir """

        # denoise = cv2.fastNlMeansDenoisingColored(VideoFrame, None, 5, 5, 1, 1)
        gray = cv2.cvtColor(VideoFrame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray, (5, 5), 0)
        gray = cv2.medianBlur(gray, 5)
        # gray = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 3.5)
        # gray = cv2.Canny(gray, 10, 20)
        kernel = np.ones((3, 3), np.uint8)

        gray = cv2.dilate(gray, kernel,iterations=2)  # dilate'in iteration'ının erode'dan fazla olması menzili artırdı gibi.
        gray = cv2.erode(gray, kernel, iterations=1)

        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 2))
        gray = cv2.morphologyEx(gray, cv2.MORPH_CLOSE, kernel)
        gray = cv2.morphologyEx(gray, cv2.MORPH_OPEN, kernel)

        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2))
        gray_final = cv2.morphologyEx(gray, cv2.MORPH_GRADIENT, kernel)
        #####
        gaussian_blur = cv2.GaussianBlur(gray_final, (3, 3), 0)
        gray_final = cv2.addWeighted(gray_final, 3, gaussian_blur, 2.0, 0)
        # gray_final = cv2.bilateralFilter(gray_final, 5, 15, 15)
        # gray_final = cv2.medianBlur(gray_final, 3)

        return gray_final

def ArduinoCordinatesXY(x,y):

    if y < 220:
        ArduinoSerial.write('D'.encode())
    if y > 260:
        ArduinoSerial.write('U'.encode())
    if x < 300:
        ArduinoSerial.write('L'.encode())
    if x > 340:
        ArduinoSerial.write('R'.encode())

    # print("x:", x, "y:", y, "r:", r)

def StepPositionandSonarDistance():
    ReceiveData = ArduinoSerial.readline()
    ReceiveDataStr = ReceiveData.decode('utf').rstrip(('\n'))
    print(ReceiveDataStr)
    """if (ReceiveDataStr != ''):
        FloatPositionandDistance = float(ReceiveDataStr)
        SonarDistanceinMeter = (FloatPositionandDistance%10)
        Position_Distance[0] = round(((FloatPositionandDistance-SonarDistanceinMeter)/10)*1.8)
        Position_Distance[1] = int((FloatPositionandDistance % 10) * 100)+1

        ProccesingData = str(Position_Distance[0])+','+str(Position_Distance[1])
        print(Position_Distance,ProccesingData)"""

""" Must global variables. """

x1, y1, TrackCounter, MemoryIterator = 0, 0, 0, 0
StepCounter = 0
CircleMemory = [0, 0, 0]
Position_Distance = [0,0]

""" Initializing camera. """

cap = cv2.VideoCapture(1)    # 0 - PC Kamerası , 1 - Logitech
# cap.set(3,1280)
# cap.set(4,720)

while True:

    ret, frame = cap.read()

    FilteredFrame = RemoveNoise_Filter(frame)

    circles = cv2.HoughCircles(FilteredFrame, cv2.HOUGH_GRADIENT, 1.0, 70, param1=80, param2=85, minRadius=10, maxRadius=80)


    if circles is not None:

        circles = np.round(circles[0, :]).astype("int")

        detected_circle = 0
        StepCounter = 0

        for (x, y, r) in circles:

            HedefBilgisix = " ".join(["x:", str(x)])
            HedefBilgisiy = " ".join(["y:", str(y)])
            HedefBilgisir = " ".join(["r:", str(r)])

            if (x1 - 10 < circles[0][0] < x1 + 10) and (y1 - 10 < circles[0][1] < y1 + 10):

                # CISIM HAREKET ETMIYORSA (YANI X, Y KOORDINATLARI +-5 PIXELDEN FAZLA OYNAMAMIS ISE) BU BLOGA GIRER

                TrackCounter += 1

                if TrackCounter < 25:
                    # CISIM 20 KEZ YUKARDAKI IF BLOGUNA GIRENE KADAR CISIM TAKIP EDILIR
                    ArduinoCordinatesXY(x,y)
                    #StepPositionandSonarDistance()
                    detected_circle = 1
                    PutTargetInfo(frame, x, y, r)
                    # print("x:", x, " y:", y, " r:", r)
                    if detected_circle == 1:
                        break

                else:
                    PutTargetInfo(frame, x, y, r)
                    cv2.putText(frame, "Object is locked", (x + r, y - 70), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2, cv2.LINE_AA)

                    # CISIM DURDUGUNU ARDUINO'YA ILETIR, ARDUİNO PYTHON'A UZAKLIK BİLGİSİNİ GÖNDERİR.
                    ArduinoSerial.write('S'.encode())
                    #StepPositionandSonarDistance()

                    # CISIM 20 KEZ IF BLOGUNA GIRDIGINDE ARTIK CISMIN DURDUGUNA KARAR VERILIR VE ARTIK TAKIP EDILMEZ
                    # print("Object is stopped.")

            else:
                #CISIM HAREKETLIYSE YANI PIXELLERI ONCEKI KAREYE GORE +-5 PIXELDEN FAZLA OYNADIYSA NORMAL BIR SEKILDE TAKIP EDILIR
                ArduinoCordinatesXY(x, y)
                #StepPositionandSonarDistance()
                detected_circle = 1
                PutTargetInfo(frame,x, y, r)
                # print("x:", x, " y:", y, " r:", r)

                TrackCounter = 0
                if detected_circle == 1:
                    break

        x1 = x
        y1 = y
    else:
        StepCounter += 1
        # CISIM BULUNAMADI, ARDUNIO'YA 'N' GONDEREREK STEP MOTORU HAREKET ETTIRILECEK.
        if StepCounter > 25:
            ArduinoSerial.write('N'.encode())
            #StepPositionandSonarDistance()

    cv2.imshow('FilteredFrame', FilteredFrame)
    cv2.imshow('frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture

cap.release()
cv2.destroyAllWindows()
