#!/usr/bin/env python
import rospy
from std_msgs.msg import UInt32

class health_monitor:
    def init_(self):
        pub_topic_name ="/ros_temp"
        sub_topic_name ="/arduino_temp"
        
        self.publisher = rospy.Publisher(pub_topic_name, UInt32, queue_size=10)
        self.subscriber = rospy.Subscriber(sub_topic_name, UInt32, self.callback)
        

    def callback(self, msg):
        if (data > 90):
            self.publisher.publish(data)


if __name__=='__main__':
node_name ="serial_node"
rospy.init_node(node_name)
health_monitor()
rospy.spin()
