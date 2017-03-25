# -*- coding: utf-8 -*-
''' author: inory '''
import cv2
import sys
import numpy as np

if __name__ == '__main__':
    ''' Parse video path or camera id '''
    if len(sys.argv) < 2:
        print 'Usage: python demo.py test.flv[video path] or python demo.py 0[camera id]'
        sys.exit(-1)
    video_path = sys.argv[1]    

    # judge if it is a video or a camera
    if '.' in video_path: # video
        print 'Opening a video: {}'.format(video_path)
    else:
        print 'Opening a camera, id={}'.format(video_path)

    # get VideoCapture
    cap = cv2.VideoCapture(video_path)
    
    # get fps
    fps = cap.get(cv2.CAP_PROP_FPS)
    if fps == 0:
        fps = 25
    frame_interval = int(1000 / fps)
    print 'Running in fps: {}'.format(fps)

    # Load .xml file to construct the cascadeClassifier
    xml_file = 'haarcascade_frontalface_default.xml'
    cascade = cv2.CascadeClassifier(xml_file)

    # Loop to detect
    print 'Press Q to exit'
    while True:
        # read frame
        ret, frame = cap.read()
        if not ret:
            break
        if frame.shape[1] > 1024:
            frame = cv2.resize(frame, (0,0), fx=0.5, fy=0.5)

        # detect
        frame_h, frame_w = frame.shape[:2]
        minSize_ratio = 0.02
        maxSize_ratio = 0.1
        minSize = (int(minSize_ratio*frame_w), int(minSize_ratio*frame_w))
        maxSize = (int(maxSize_ratio*frame_w), int(maxSize_ratio*frame_w))

        bboxes = cascade.detectMultiScale(frame, minSize=minSize, maxSize=maxSize)

        # draw rectangle
        for bbox in bboxes:
            x,y,w,h = bbox
            cv2.rectangle(frame, (x,y), (x+w,y+h), (255,0,0), 2)

        # show
        cv2.imshow('video', frame)
        key = cv2.waitKey(frame_interval)
        if key & 0xFF == ord('q'):
            break

