#!/bin/bash
echo "const char *versionstring=\"`git describe --long`\";" > src/version.h
