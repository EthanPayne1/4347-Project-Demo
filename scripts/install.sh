#!/bin/bash 

DB_DUMP_LINK="https://drive.google.com/file/d/1oTv9i2GeOrIwMhjSwicV4rWL71nf3PCk/view?usp=sharing"

# Be aware that a level 2 DTED map of the US is HUGE. 
# The compressed folder(which your downloading) is around 8gb and the uncompressed version is just under 30gb
# Loading this much data into a program might blow up your PC
ENTIRE_US_LINK="https://drive.google.com/file/d/1-IXr8wSxu1lgKkocce8zpUrvrJMyaMG_/view?usp=sharing"
echo "Downloading the entire US."

curl -L -o $ENTIRE_US_LINK
