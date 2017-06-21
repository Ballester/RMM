import sys
import os
import re
import shlex
import subprocess
import tempfile
import json

def findVideoMetada(pathToInputVideo):
    cmd = "ffprobe -v quiet -print_format json -show_streams"
    args = shlex.split(cmd)
    args.append(pathToInputVideo)
    ffprobeOutput = subprocess.check_output(args).decode('utf-8')
    ffprobeOutput = json.loads(ffprobeOutput)
    return ffprobeOutput

path = "video_original.mp4"
sizes = [(1280, 720), (720, 480)]

names = []
for (i, size) in enumerate(sizes) :
    names.append(path.split('.')[0] + "_" + str(size[1]) + ".mp4")
    print names
    os.system("ffmpeg -i " + path + " -vf scale=" + str(size[0]) + ":" + str(size[1]) + " -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy " + names[i])

names.append(path)
for name in names:
    meta = findVideoMetada(name)
    bitrate = float(meta['streams'][0]['bit_rate'])
    bitrate = bitrate/1024.0
    print '\n\nBITRATE'
    print bitrate
    os.system("ffmpeg -i " + name + " -b:v " + str(0.8*bitrate) + "k -threads 0 -minrate " + str(0.8*bitrate) + "k -maxrate " + str(0.8*bitrate) + "k -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a aac -strict -2 -bufsize 154k " + name.split('.')[0] + "_08.mp4")
    os.system("ffmpeg -i " + name + " -b:v " + str(0.6*bitrate) + "k -threads 0 -minrate " + str(0.6*bitrate) + "k -maxrate " + str(0.6*bitrate) + "k -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a aac -strict -2 -bufsize 154k " + name.split('.')[0] + "_06.mp4")
    os.system("ffmpeg -i " + name + " -b:v " + str(0.4*bitrate) + "k -threads 0 -minrate " + str(0.4*bitrate) + "k -maxrate " + str(0.4*bitrate) + "k -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a aac -strict -2 -bufsize 154k " + name.split('.')[0] + "_04.mp4")
    os.system("ffmpeg -i " + name + " -b:v " + str(0.2*bitrate) + "k -threads 0 -minrate " + str(0.2*bitrate) + "k -maxrate " + str(0.2*bitrate) + "k -r 30 -preset ultrafast -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a aac -strict -2 -bufsize 154k " + name.split('.')[0] + "_02.mp4")

for name in names:
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_08.mp4 -lavfi psnr="psnr_' + name.split('.')[0] + '_08.log" -f null -')
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_06.mp4 -lavfi psnr="psnr_' + name.split('.')[0] + '_06.log" -f null -')
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_04.mp4 -lavfi psnr="psnr_' + name.split('.')[0] + '_04.log" -f null -')
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_02.mp4 -lavfi psnr="psnr_' + name.split('.')[0] + '_02.log" -f null -')

    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_08.mp4 -lavfi ssim="ssim_' + name.split('.')[0] + '_08.log" -f null -')
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_06.mp4 -lavfi ssim="ssim_' + name.split('.')[0] + '_06.log" -f null -')
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_04.mp4 -lavfi ssim="ssim_' + name.split('.')[0] + '_04.log" -f null -')
    os.system("ffmpeg -i " + name + ' -i ' + name.split('.')[0] + '_02.mp4 -lavfi ssim="ssim_' + name.split('.')[0] + '_02.log" -f null -')
