#!/usr/bin/env bash

echo "Building and launching cuACS."
echo "Please wait."
BUILD=`make && ./cuACS`
