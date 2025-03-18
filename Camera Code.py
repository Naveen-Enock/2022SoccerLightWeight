# Single Color RGB565 Blob Tracking Example
#
# This example shows off single color RGB565 tracking using the OpenMV Cam.

import sensor, image, time, math
from math import atan2, degrees
from pyb import UART

threshold_index = 1 # 0 for red, 1 for yellow, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(30, 100, 15, 127, 15, 127), # generic_red_thresholds
              (79, 88, -17, -1, 61, 127),# generic_yellow_thresholds
             (12, 36, -40, 37, -36, -8)] # generic_blue_thresholds

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.HVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
sensor.set_brightness(3)
sensor.set_saturation(2)
sensor.set_contrast(3)
sensor.set_auto_exposure(False,14000)
clock = time.clock()
roleIndexx = 0




# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.


while(True):
    clock.tick()
    uart = UART(1,19200)
    img = sensor.snapshot()

    #convertedIndex = int(roleIndex)

    #if (roleIndex == 1):
     #   roleIndex = 2
    #if (roleIndex == 0):
     #   roleIndex = 1
    robotAngle = -5
    focalLength = -5
    robotAngle2 = -5
    focalLength2 = -5
    for blob in img.find_blobs([thresholds[1]], pixels_threshold=500, area_threshold=505, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if blob.elongation() > 0.5:
            img.draw_edges(blob.min_corners(), color=(255,0,0))
            img.draw_line(blob.major_axis_line(), color=(0,255,0))
            img.draw_line(blob.minor_axis_line(), color=(0,0,255))
        # These values are stable all the time.
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())



        # Note - the blob rotation is unique to 0-180 only.
        img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
        print(clock.fps())

        x = int(blob.cx())
        y = int(blob.cy())
        x = x-200
        y = y-195
        robotAngle = degrees(atan2(x,y))
        robotAngle += 180
        print(" x: " , x, "y: " , y)

        width = blob.w()
        initialLength = (75*96.5)/65
        height = blob.h()
        focalLength = (65*initialLength)/width


    for blob in img.find_blobs([thresholds[2]], pixels_threshold=500, area_threshold=500, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if blob.elongation() > 0.5:
            img.draw_edges(blob.min_corners(), color=(255,0,0))
            img.draw_line(blob.major_axis_line(), color=(0,255,0))
            img.draw_line(blob.minor_axis_line(), color=(0,0,255))
        # These values are stable all the time.
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())



        # Note - the blob rotation is unique to 0-180 only.
        img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
        print(clock.fps())

        x2 = int(blob.cx())
        y2 = int(blob.cy())
        x2 = x2-200
        y2 = y2-195
        robotAngle2 = degrees(atan2(x2,y2))
        robotAngle2 += 180
        print(" x: " , x2, "y: " , y2)

        width2 = blob.w()
        initialLength2 = (75*96.5)/65
        height2 = blob.h()
        focalLength2 = (65*initialLength2)/width2
    print(" RobotAngle : ", robotAngle)
    print(focalLength)
    print(" RobotAngle2 : ", robotAngle2)
    print(focalLength2)
    data = (str(robotAngle), str(focalLength),str(robotAngle2), str(focalLength2))
    uart.write("|".join(data)+"a")


        #if (uart.any()):
            #print(uart.read())
        #time.sleep(1)



