"""
 Download and install libs, as well as other prequisite setup steps
"""

import urllib.request
import platform
import subprocess


commands = {
    "platforms": {
        # For all platforms
        "common": {
            "Libs": ["SDL2"]
        },
        # Platform specific stuff
    },
    "libs": {
        ## How to get sdl2 on different platforms
        "SDL2": {
            "Windows": [
                "dl ....",
                "extract .... Libs/SDL2"
            ],
            "Linux": [
                "install libsdl2,sdl2"
            ]
        }
    }
}


def runCommandList(commands):
    for command,*args in [x.split(" ") for x in commands]:
        if command == "install":
            print(f"Installing package {args[-1]}", end="")
            for x in args[-1].split(","):
                proc = subprocess.Popen(["sudo", "pacman", "--quiet", "--noconfirm", "-Sy", x], stdout=subprocess.PIPE)
                proc.wait()
            print("    [Done]")


def installLib(name):
    print(f"Installing lib '{name}'")

    runCommandList(commands["libs"][name][platform.system()])



def setupPlatform(platformID):
    print(f"Running setup for platform '{platformID}'")
    print("Installing libs")

    for lib in commands["platforms"][platformID]["Libs"]:
        installLib(lib)


def main():
    setupPlatform("common")


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