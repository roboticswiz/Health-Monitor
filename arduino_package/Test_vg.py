#!/usr/bin/env python
#from cgi import print_directory 
#from re import T 
#import sys 
import rospy 
from std_msgs.msg import Float32 
from std_msgs.msg import UInt32 

global InputTemp
InputTemp=0

global InputHR
InputHR=0

global InputSPo2
InputSPo2=0

def cb_temp(data):
    global InputTemp
    InputTemp=data.data 

def cb_hr(data):
    global InputHR
    InputHR=data.data 

def cb_spo2(data):
    global InputSPo2
    InputSPo2=data.data 
    
def main(): 
    
    temp_pub =rospy.Publisher('/ros_temp',Float32,queue_size=10) 
    hr_pub =rospy.Publisher('/ros_hr',UInt32,queue_size=10)
    spo2_pub =rospy.Publisher('/ros_spo2',UInt32,queue_size=10)

    while not rospy.is_shutdown(): 
        rospy.init_node('serial_node', anonymous=True) 
        
        #here we are subscribing
        rospy.Subscriber("/arduino_temp", Float32, cb_temp)
        rospy.Subscriber("/arduino_heart", UInt32, cb_hr)
        rospy.Subscriber("/arduino_oxygen", UInt32, cb_spo2)

        if InputTemp>85:
            print("Temp: " + str(InputTemp))
            temp_pub.publish(InputTemp) 

        if InputHR>85:
            print("Heart Rate: " + str(InputHR))
            hr_pub.publish(InputHR) 

        if InputSPo2>85:
            print("SPo2: " + str(InputSPo2))
            spo2_pub.publish(InputSPo2) 
            
        rospy.sleep(3) 
        rospy.spin 
    
if __name__=='__main__': 
    try: main() 
    except rospy.ROSInterruptException: 
        pass