import os
cliPath = "../cmake-build-debug/executables/"

rootPath = os.path.dirname(os.path.realpath(__file__))
includePath = rootPath + "/bsIncludes"

for root, dirs, files in os.walk(includePath):
    for name in files:
        if ".bs" in name:
            print(f"Building {name}")
            command = "(cd " + cliPath + " && ./bsCLI " + "include/" + name + " -u -o " + rootPath + "/bsModules)"
            print(f"Running command: {command}")
            result = os.system(command)
            if(result != 0):
                print(f"Failed")
            else:
                print("Success")