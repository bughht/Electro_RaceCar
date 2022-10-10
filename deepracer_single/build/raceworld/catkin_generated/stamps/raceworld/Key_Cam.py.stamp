
import rospy, cv_bridge
import cv2 as cv
import sys, select, termios, tty
from ackermann_msgs.msg import AckermannDriveStamped
from sensor_msgs.msg import Image,CompressedImage
import numpy as np 

CAM_SIZE=[480,640,3]

class Key_Cam:
    def __init__(self) -> None:
        self.frame= np.zeros(2,*CAM_SIZE)
        rospy.Subscriber("/deepracer1/camera/zedleft/image_rect_color_left",Image,self.image_callback_left)
        rospy.Subscriber("/deepracer1/camera/zedright/image_rect_color_right",Image,self.image_callback_right)


    def image_callback_left(self,msg):
        bridge = cv_bridge.CvBridge()
        self.frame[0]=bridge.imgmsg_to_cv2(msg,'bgr8')

    def image_callback_right(self,msg):
        bridge = cv_bridge.CvBridge()
        self.frame[1]=bridge.imgmsg_to_cv2(msg,'bgr8')
        cv.imshow(self.frame.reshape((480,1280,3)))
        cv.waitKey(1)

    # def getKey(self):

if __name__ == "__main__":
    rospy.init_node("Key_Cam")
    Key_Cam()
    rospy.spin()
    pass
