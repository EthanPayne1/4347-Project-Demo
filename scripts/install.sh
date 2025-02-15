#!/bin/bash 

DRIVE_LINK="https://drive.google.com/file/d/1oTv9i2GeOrIwMhjSwicV4rWL71nf3PCk/view?usp=sharing"

echo "\e[32mDownloading the database dump\e[0m"

curl -L -o dted_filled_database.dump $DRIVE_LINK
