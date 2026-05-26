FROM ros:humble-ros-base

RUN apt-get update && apt-get install -y     ros-humble-gazebo-ros-pkgs     ros-humble-robot-state-publisher     ros-humble-xacro     python3-pip     && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . /workspace/skyguard_sim

RUN cd /workspace/skyguard_sim &&     pip install -e .

RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
RUN echo "source /workspace/skyguard_sim/install/setup.bash" >> ~/.bashrc

CMD ["ros2", "launch", "skyguard_sim", "skyguard.launch.py"]
