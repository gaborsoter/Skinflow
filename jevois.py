import libjevois as jevois
import cv2
import numpy as np

## Detect bend sensors

lower = np.array([0, 0, 0], dtype = "uint8")
upper = np.array([255, 70, 255], dtype = "uint8")

class Skinflow:
    # ###################################################################################################
    ## Constructor
    def __init__(self):
      self.timer = jevois.Timer('ArUco detection', 50, jevois.LOG_DEBUG)
      
    # ###################################################################################################
    ## Process function with USB output
    def process(self, inframe, outframe):
        frame = inframe.getCvBGR()
        
        # Start measuring image processing time (NOTE: does not account for input conversion time):
        self.timer.start()
        
        #grayimg = cv2.cvtColor(inimg, cv2.COLOR_BGR2GRAY)
        #ret,thresh1 = cv2.threshold(grayimg,127,255,cv2.THRESH_BINARY)
        #nonzero = cv2.countNonZero(thresh1)
        #jevois.sendSerial(str(nonzero))
        
        mask = cv2.inRange(frame, lower, upper)
        output = cv2.bitwise_and(frame, frame, mask = mask)
        gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY)
        #th = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 221, 1)

        
        
        fps = self.timer.stop()
  
        # Convert our output image to video output format and send to host over USB:
        outframe.sendCv(gray)
        
