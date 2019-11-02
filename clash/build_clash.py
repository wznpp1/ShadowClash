import subprocess
import datetime
import plistlib
import platform
import os

def get_version():
    with open('./go.mod') as file:
        for line in file.readlines():
            if "clash" in line and "shadowclash" not in line:
                return line.split(" ")[-1].strip()
    return "unknown"


def build_clash(version):
    build_time = datetime.datetime.now().strftime("%Y-%m-%d-%H%M")
    if platform.system() == "Darwin":
        command = f"""CGO_CFLAGS=-mmacosx-version-min=10.12 \
        CGO_LDFLAGS=-mmacosx-version-min=10.10 \
        GOBUILD=CGO_ENABLED=0 \
        go build -ldflags '-X "github.com/Dreamacro/clash/constant.Version={version}" \
        -X "github.com/Dreamacro/clash/constant.BuildTime={build_time}"' \
        -buildmode=c-archive """
    else:
        command = f"""go build -ldflags '-X "github.com/Dreamacro/clash/constant.Version={version}" \
        -X "github.com/Dreamacro/clash/constant.BuildTime={build_time}"' \
        -buildmode=c-archive """
    subprocess.check_output(command, shell=True)
    try:
        os.system("mv shadowclash.h ../src")
        os.system("mv shadowclash.a ../framework")
    except Exception as e:
        print(e)

def write_to_info(version):
    path = "info.plist"

    with open(path, 'rb') as f:
        contents = plistlib.load(f)

    if not contents:
        exit(-1)

    contents["coreVersion"] = version
    with open(path, 'wb') as f:
        plistlib.dump(contents, f, sort_keys=False)


def run():
    version = get_version()
    print("current clash version:", version)
    build_clash(version)
    print("build static library complete!")
    if platform.system() == "Darwin":
        if os.environ.get("CI", False):
            print("writing info.plist")
            write_to_info(version)
    print("done")


if __name__ == "__main__":
    run()
