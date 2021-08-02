#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <iostream>
#include <sstream>

using namespace std;

int Pick[5] = {1,3,2,5};
int Place[5] = {4,1,2,5};
bool start_act = true;
string place = "place";
string pick;
int cnt;
bool fin_call = true;

// void movemove(const std_msgs::Bool& allow_to_act){
// 	start_act = allow_to_act.data;
// }

// void which(const std_msgs::String& place_or_pick){
// 	if(place_or_pick.data == "pick"){
// 		pick =  place_or_pick.data;
// 	}
// 	else if(place_or_pick.data == "place"){
// 		place =  place_or_pick.data;
// 	}
// }

void fin_act_call(const std_msgs::Bool& msg){

    fin_call = msg.data;
    ROS_INFO("ang");

}

int main(int argc, char **argv){
    
	ros::init(argc, argv,"pub_check_mode_num");

	ros::NodeHandle nh;

	ros::Publisher chatter_pub = nh.advertise<std_msgs::Int32>("check_mode", 1000);
	
	//ros::Subscriber sub1 = nh.subscribe("mode", 10, movemove);
	//ros::Subscriber sub2 = nh.subscribe("which", 10, which);
    ros::Subscriber sub3 = nh.subscribe("fin_act", 10, fin_act_call);
	std_msgs::Int32 check_num;
	ros::Rate loop_rate(0.5);

	while(ros::ok()){
		

        ROS_INFO("start_act : %d, pick : %s, fin_call : %d", start_act, pick, fin_call);
        if(start_act){
			
            if(pick == "pick"){
                
                if(fin_call){
                    

                    if(cnt == 5){
                        cnt = 0;
                        //break;
                    }
                    
                    check_num.data = Pick[cnt];
                    ROS_INFO("*pick* check_num.data : %d, cnt : %d", check_num.data, cnt);
                    cnt++;
                }
                
            }

            if(place == "place"){

                if(fin_call){
        

                    if(cnt == 5){
                        cnt = 0;
                        //break;
                    }
                    
                    check_num.data = Place[cnt];
                    ROS_INFO("*place* check_num.data : %d, cnt : %d", check_num.data, cnt);
                    cnt++;
                }
                
            }

			ros::Duration(2.0).sleep();
            
			chatter_pub.publish(check_num);
            ROS_INFO("%d", check_num);
			fin_call = false;
            ROS_INFO("fin_call false : %d", fin_call);

        }

		
		
        //ros::Duration(4.0).sleep();

		//chatter_pub.publish(check_num);
		

	ros::spinOnce();

	loop_rate.sleep();
	}
}
