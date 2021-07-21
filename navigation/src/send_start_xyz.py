#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Point
import math
import tf

def main():
	rospy.init_node('send_start_xyz')
	listener = tf.TransformListener()
	pub = rospy.Publisher('start_xyz', Point, queue_size=1)
	rate = rospy.Rate(1)

	while not rospy.is_shutdown():
		try:
			(trans,rot) = listener.lookupTransform('tb3_1/map', 'tb3_1/base_link', rospy.Time(0))
		except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
			continue
		
		start_xyz = Point()
		start_xyz.x = trans[0]
		start_xyz.y = trans[1]
		start_xyz.z = trans[2]

		rospy.loginfo(start_xyz)
		pub.publish(start_xyz)
		rate.sleep()

if __name__ == '__main__':
	try:
		main()
	except rospy.ROSInterruptException:
		pass
