#!/usr/bin/env python
#from cgi import print_directory 
#from re import T 
#import sys 
import rospy 
from std_msgs.msg import Float32 

global InputTemp
InputTemp=0

def callback(data):
    global InputTemp
    InputTemp=data.data 
    

def main(): 
    
    Temp_topic_Publisher =rospy.Publisher('/ros_temp',Float32,queue_size=10) 

    while not rospy.is_shutdown(): 
        rospy.init_node('serial_node', anonymous=True) 
        
        #here we are subscribing
        rospy.Subscriber("/arduino_temp", Float32, callback)

        if InputTemp>85:
            print("IT Higher than: " + str(InputTemp))
            Temp_topic_Publisher.publish(InputTemp) 
            
        rospy.sleep(3) 
        rospy.spin 
    
if __name__=='__main__': 
    try: main() 
    except rospy.ROSInterruptException: 
        pass