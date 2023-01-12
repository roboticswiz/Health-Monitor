#!/usr/bin/env python
from cgi import print_directory 
from re import T 
import sys 
import rospy 
from std_msgs.msg import UInt32 

global InputTemp
InputTemp=0

def callback(data):
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    global InputTemp
    InputTemp=data.data 
    #print("Temp :",data.data)

def main(): 
    
    DataToBeDecided=10
    Temp_topic_Publisher =rospy.Publisher('/ros_temp',UInt32,queue_size=10) 
    Temp_published_data=UInt32()
    Temp_published_data.data=DataToBeDecided
    ITPD=UInt32()
    while not rospy.is_shutdown(): 
        rospy.init_node('serial_node', anonymous=True) 
        #here we are subscribing
        rospy.Subscriber("/arduino_temp", UInt32, callback)
        #InputTemp=ITPD.data
        if InputTemp>50:
            print("ITPD Higher than: " + str(ITPD))
            print("IT Higher than: " + str(InputTemp))
            
            #here we are publishing
            Temp_topic_Publisher.publish(Temp_published_data.data) 
            #print(Temp_published_data)
        rospy.sleep(3) 
        rospy.spin 
        

if __name__=='__main__': 
    try: main() 
    except rospy.ROSInterruptException: 
        pass