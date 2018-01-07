import cv2 
fps = 14
#fourcc = cv2.CV_FOURCC('M','J','P','G')
videoWriter = cv2.VideoWriter('test_result.avi', cv2.VideoWriter_fourcc(*'MPEG'), fps, (2560, 1440))
for i in range(0, 4190):
    img = cv2.imread('./images/' + str(i) + '.png')
    videoWriter.write(img)
    print("Process image " + str(i) + '.png')
