"""ROS2 node for follow-me drone control."""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped
from sensor_msgs.msg import NavSatFix, Image
import math


class FollowMeNode(Node):
    def __init__(self):
        super().__init__('follow_me_controller')
        
        # Publishers
        self.cmd_pub = self.create_publisher(Twist, '/skyguard/cmd_vel', 10)
        
        # Subscribers
        self.gps_sub = self.create_subscription(
            NavSatFix, '/skyguard/gps', self.gps_callback, 10)
        self.target_sub = self.create_subscription(
            PoseStamped, '/skyguard/target', self.target_callback, 10)
        
        # State
        self.current_lat = 0.0
        self.current_lon = 0.0
        self.target_lat = 0.0
        self.target_lon = 0.0
        self.target_alt = 2.5
        
        # PID gains
        self.kp = 1.5
        self.ki = 0.3
        self.kd = 0.08
        
        # PID state
        self.integral_x = 0.0
        self.integral_y = 0.0
        self.prev_error_x = 0.0
        self.prev_error_y = 0.0
        
        # Control loop at 10Hz
        self.timer = self.create_timer(0.1, self.control_loop)
        
        self.get_logger().info('Follow-me controller started')
    
    def gps_callback(self, msg: NavSatFix):
        self.current_lat = msg.latitude
        self.current_lon = msg.longitude
    
    def target_callback(self, msg: PoseStamped):
        self.target_lat = msg.pose.position.x
        self.target_lon = msg.pose.position.y
        self.target_alt = msg.pose.position.z
    
    def haversine_distance(self, lat1, lon1, lat2, lon2):
        R = 6371000  # Earth radius in meters
        phi1, phi2 = math.radians(lat1), math.radians(lat2)
        dphi = math.radians(lat2 - lat1)
        dlambda = math.radians(lon2 - lon1)
        a = math.sin(dphi/2)**2 + math.cos(phi1)*math.cos(phi2)*math.sin(dlambda/2)**2
        return 2 * R * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    
    def control_loop(self):
        if self.target_lat == 0 and self.target_lon == 0:
            return
        
        # Calculate error in meters
        dx = self.haversine_distance(
            self.current_lat, self.current_lon,
            self.target_lat, self.current_lon)
        dy = self.haversine_distance(
            self.current_lat, self.current_lon,
            self.current_lat, self.target_lon)
        
        # PID
        self.integral_x = max(-2.0, min(2.0, self.integral_x + dx * 0.1))
        self.integral_y = max(-2.0, min(2.0, self.integral_y + dy * 0.1))
        
        deriv_x = (dx - self.prev_error_x) / 0.1
        deriv_y = (dy - self.prev_error_y) / 0.1
        
        cmd = Twist()
        cmd.linear.x = self.kp * dx + self.ki * self.integral_x + self.kd * deriv_x
        cmd.linear.y = self.kp * dy + self.ki * self.integral_y + self.kd * deriv_y
        cmd.linear.z = self.target_alt
        
        self.prev_error_x = dx
        self.prev_error_y = dy
        
        self.cmd_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = FollowMeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
