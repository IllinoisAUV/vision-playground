import rospy
from std_msgs.msg import Bool
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2

TOPIC = 'topic'

if __name__ == '__main__':
    rospy.init_node('topic_to_vid', anonymous=True)
    bridge = CvBridge()
    vid = cv2.VideoWriter('video.mp4', cv2.cv.CV_FOURCC(*'MJPG'), (1280, 720))
    sub = rospy.Subscriber(TOPIC, Image, callback)
    vid_end_sub = rospy.Subscriber('end_vid', Bool, callback2)
    def callback(img):
        cv_image = bridge.imgmsg_to_cv2(img, "bgr8")
        vid.write(cv_image)

    def callback2(b):
        if b.data:
            sub.unregister()
            vid_end_sub.unregister()
            vid.release()

    rospy.spin()
