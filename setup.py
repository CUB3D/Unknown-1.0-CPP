"""
 Download and install libs, as well as other prequisite setup steps
"""

import urllib.request
import platform
import subprocess
import zipfile
import os
import sys
import shutil


commands = {
    "platforms": {
        # For all platforms
        "common": {
            "Libs": ["SDL2", "SDL2_image", "SDL2_ttf", "SDL2_mixer", "Box2D", "assimp"]
        },
        # Windows specific setup
        "Windows": {
            "commands": [
                "cp Libs/SDL2/lib/x64/SDL2.dll:Unknown Test/",
                "cp Libs/SDL2_image/lib/x64/SDL2_image.dll:Unknown Test/",
                "cp Libs/SDL2_image/lib/x64/libpng16-16.dll:Unknown Test/",
		"cp Libs/SDL2_image/lib/x64/libjpeg-9.dll:Unknown Test/",
                "cp Libs/SDL2_ttf/lib/x64/libfreetype-6.dll:Unknown Test/",
                "cp Libs/SDL2_ttf/lib/x64/SDL2_ttf.dll:Unknown Test/",
		"cp Libs/SDL2_mixer/lib/x64/SDL2_mixer.dll:Unknown Test/",
		"cp Libs/assimp/bin/Debug/assimp-vc140-mt.dll:Unknown Test/",
		"cp Libs/SDL2_image/lib/x64/zlib1.dll:Unknown Test/"
            ]
        }
    },
    "libs": {
        ## How to get sdl2 on different platforms
        "SDL2": {
            "Windows": [
                "dl https://www.libsdl.org/release/SDL2-devel-2.0.8-VC.zip tools/SDL2.zip",
                "extract tools/SDL2.zip Libs",
                "mv Libs/SDL2-2.0.8 Libs/SDL2"
            ],
            "Linux": [
                "install libsdl2,sdl2"
            ]
        },
		"SDL2_image": {
			"Windows": [
				"dl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip tools/SDL2_image.zip",
				"extract tools/SDL2_image.zip Libs",
				"mv Libs/SDL2_image-2.0.3 Libs/SDL2_image"
			]
		},
		"SDL2_ttf": {
			"Windows": [
				"dl https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip tools/SDL2_ttf.zip",
				"extract tools/SDL2_ttf.zip Libs",
				"mv Libs/SDL2_ttf-2.0.14 Libs/SDL2_ttf"
			]
		},
		"SDL2_mixer": {
			"Windows": [
				"dl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.2-VC.zip tools/SDL2_mixer.zip",
				"extract tools/SDL2_mixer.zip Libs",
				"mv Libs/SDL2_mixer-2.0.2 Libs/SDL2_mixer"
			]
		},
		"Box2D": {
			"Windows": [
				"dl https://github.com/premake/premake-core/releases/download/v5.0.0-alpha12/premake-5.0.0-alpha12-windows.zip tools/premake.zip",
				"extract tools/premake.zip Libs/Box2D/Box2D",
				"exec cd Libs/Box2D/Box2D && premake5.exe vs2017",
				"make Libs/Box2D/Box2D/Build/vs2017/Box2D.sln"
			]
		},
        "assimp": {
            "Windows": [
                "dl https://github.com/assimp/assimp/archive/v4.1.0.zip tools/assimp.zip",
                "extract tools/assimp.zip Libs/",
                "rm Libs/assimp",
                "mv Libs/assimp-4.1.0 Libs/assimp",
                "dl https://cmake.org/files/v3.12/cmake-3.12.2-win64-x64.zip tools/cmake.zip",
                "extract tools/cmake.zip tools/build/cmake-dist",
                "exec cd Libs/assimp && \"../../tools/build/cmake-dist/cmake-3.12.2-win64-x64/bin/cmake.exe\" -G \"Visual Studio 15 2017 Win64\" CMakeLists.txt",
                "exec cd Libs/assimp && \"../../tools/build/cmake-dist/cmake-3.12.2-win64-x64/bin/cmake.exe\" --build ."
            ]
        }
    }
}

commands_mapping = {}

def command(name):
	def command_func_wrap(func):
		commands_mapping[name] = func
		return func

	return command_func_wrap

@command("install")
def command_install(args):
	print(f"Installing package {args[-1]}", end="")
	for x in args[-1].split(","):
		proc = subprocess.Popen(["sudo", "pacman", "--quiet", "--noconfirm", "-Sy", x], stdout=subprocess.PIPE)
		proc.wait()
	print("    [Done]")

@command("dl")
def command_dl(args):
	def dl_command_callback(blocknum, blocksize, total):
		progress = (blocknum * blocksize) * (100 / total)

		if progress % 20 < 0.5 and progress > 1:
			print(f"- {int(progress)} %")
	
	print(f"Downloading {args[0]}")

	urllib.request.urlretrieve(args[0], filename=args[1], reporthook=dl_command_callback)

@command("extract")
def command_extract(args):
	zip_ = zipfile.ZipFile(args[0], "r")
	zip_.extractall(args[1])
	zip_.close()

@command("mv")
def command_mv(args):
	os.rename(args[0], args[1]) 

@command("rm")
def command_rm(args):
    shutil.rmtree(args[0])

@command("exec")
def command_exec(args):
	os.system(" ".join(args))

@command("make")
def command_make(args):
	if windows():
		# First find vs install location
		tmp = subprocess.Popen(["reg", "query", "HKLM\SOFTWARE\Wow6432Node\Microsoft\VisualStudio\SxS\VS7"], stdout=subprocess.PIPE)
		# Skip crap
		tmp.stdout.readline();
		tmp.stdout.readline();
		location = " ".join(tmp.stdout.readline().decode("utf-8").rstrip("\r\n").split(" ")[12:])
		msBuildPath = os.path.join(location, "MSBuild", "15.0", "Bin", "MSBuild.exe")
		subprocess.Popen([msBuildPath, args[0], "/p:Configuration=Release"]).wait()

@command("cp")
def command_mv(args):
    tmp = " ".join(args).split(":")
    shutil.copy2(tmp[0], tmp[1])

def runCommandList(commands):
	for command,*args in [x.split(" ") for x in commands]:
		if command in commands_mapping:
			commands_mapping[command](args)
		else:
			print(f"Unknown command '{command}'")



def installLib(name):
    print(f"Installing lib '{name}'")

    runCommandList(commands["libs"][name][platform.system()])



def setupPlatform(platformID):
    print(f"Running setup for platform '{platformID}'")

    platformCommands = commands["platforms"][platformID]

    if "Libs" in platformCommands:
        print("Installing libs")

        for lib in platformCommands["Libs"]:
            installLib(lib)

    if "commands" in platformCommands:
        runCommandList(platformCommands["commands"])


def main():
    setupPlatform("common")
    setupPlatform(platform.system())


def download(url, out):
    """
    Download a file to a location
    :param url: url to download
    :param out: output location
    """
    with open(out, "wb") as fHandle:
        fHandle.write(urllib.request.urlopen(url).read())


def windows():
    """
    :return: True if platform is windows
    """
    return platform.system() == "Windows"


def linux():
    """
    :return: True if platform is linux
    """
    return platform.system() == "Linux"


if __name__ == "__main__":
    main()
