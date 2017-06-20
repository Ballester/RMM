# ffmpeg -r 24 -i sintel_trailer_2k_1080p24.y4m -c:v libx264 -b:v 1000k -minrate 1000k -maxrate 1000k -bufsize 250k -x264opts keyint=48:minkeyint=48:scenecut=-1 sintel_1000k.mp4
import sys
import os
import re
import shlex
import subprocess
import tempfile
import json

def findVideoMetada(pathToInputVideo):
    cmd = "ffprobe -v quiet -print_format json -show_streams"
    # cmd = "ffprobe -select_streams v:0 -show_entries stream=bit_rate"
    args = shlex.split(cmd)
    args.append(pathToInputVideo)
    # run the ffprobe process, decode stdout into utf-8 & convert to JSON
    ffprobeOutput = subprocess.check_output(args).decode('utf-8')
    ffprobeOutput = json.loads(ffprobeOutput)

    return ffprobeOutput


path = "video_original.mp4"
sizes = [(1280, 720), (720, 480), (480, 320)]

names = []
for (i, size) in enumerate(sizes) :
    names.append(path.split('.')[0] + "_" + str(size[1]) + ".mp4")
    print names

    # os.system("ffmpeg -i " + path + " -vf scale=-1:" + str(size[1]) + " -preset ultrafast " + " -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy " + names[i])

# raise
for name in names:

    meta = findVideoMetada(path)
    # print meta
    bitrate = float(meta['streams'][0]['bit_rate'])
    bitrate += float(meta['streams'][1]['bit_rate'])
    bitrate = bitrate/1024.0
    print name
    os.system("ffmpeg -i " + name + " -b:a " + str(0.8*bitrate) + " -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy " + name.split('.')[0] + "_08.mp4")
    os.system("ffmpeg -i " + name + " -b:a " + str(0.6*bitrate) + " -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy " + name.split('.')[0] + "_06.mp4")
    os.system("ffmpeg -i " + name + " -b:a " + str(0.4*bitrate) + " -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy " + name.split('.')[0] + "_04.mp4")
    os.system("ffmpeg -i " + name + " -b:a " + str(0.2*bitrate) + " -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy " + name.split('.')[0] + "_02.mp4")

    # os.system("ffmpeg -i " + names[0] + str(size[1]) + " -preset veryfast" + " copy " + names[i].split('.')[0] + )
