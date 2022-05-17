import os
 
# Get the list of all files and directories
path = "./"
folder="TestingReFormat"
dir_list = os.listdir(path)
dir_list.sort()
 
print("Files and directories in '", path, "' :")

#print(len(dir_list))
 
# prints all files
#print(dir_list)


f = open("InstanceList.txt", "w")

for instance in dir_list:
    if (instance.endswith(".py") or instance.endswith(".DS_Store")):
        print(instance)

    else:
        strHold = '../{dir}/{file}\n'.format(dir=folder,file=instance)
        f.write(strHold)
    #print(strHold)
f.close()
