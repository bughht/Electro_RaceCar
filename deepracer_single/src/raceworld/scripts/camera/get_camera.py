#! /usr/bin/env python
import rospy, cv2, cv_bridge
from sensor_msgs.msg import Image

def image_callback(msg):
    bridge = cv_bridge.CvBridge()
    frame = bridge.imgmsg_to_cv2(msg, 'bgr8')
    cv2.imshow('window', frame)
    cv2.waitKey(1)
    pass

def get_camera():
    rospy.Subscriber("/deepracer1/camera/zed_left/image_rect_color_left", Image, image_callback)
    pass

if __name__ == '__main__':
    rospy.init_node("get_camera")
    get_camera()
    rospy.spin()
    pass