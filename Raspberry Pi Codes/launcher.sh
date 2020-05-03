
#!/bin/sh
# launcher.sh
# navigate to home directory, then to this directory, then execute python script, then back home

cd /
cd home/pi/EE629
sudo python3 wait.py
sudo python3 Master_Control.py > Log.log 2>&1
cd /
