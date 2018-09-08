"""
 Download and install libs, as well as other prequisite setup steps
"""

import urllib.request
import platform
import subprocess
import zipfile
import os
import sys


commands = {
    "platforms": {
        # For all platforms
        "common": {
            "Libs": ["SDL2", "SDL2_image", "SDL2_ttf", "Box2D"]
        },
        # Platform specific stuff
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
		"Box2D": {
			"Windows": [
				"dl https://github.com/premake/premake-core/releases/download/v5.0.0-alpha12/premake-5.0.0-alpha12-windows.zip tools/premake.zip",
				"extract tools/premake.zip Libs/Box2D",
				"exec cd Libs/Box2D && premake5.exe vs2017",
				"make Libs/Box2D/Build/Box2D.sln"
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
		subprocess.Popen([msBuildPath, args[0]]).wait()


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
    print("Installing libs")

    for lib in commands["platforms"][platformID]["Libs"]:
        installLib(lib)


def main():
	installLib(sys.argv[-1])
    #setupPlatform("common")


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
