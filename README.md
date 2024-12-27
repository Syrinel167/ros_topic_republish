## Function

Repulish rostopic to satisfy other ros nodes' requirements.

## Build and Run

```bash
cd YOUR_WORKSPACE/src
git clone https://github.com/Syrinel167/ros_topic_republish
cd ..
catkin_make
source devel/setup.bash
# roscore at another terminal
rosrun topic_republisher topic_republisher_node
```
