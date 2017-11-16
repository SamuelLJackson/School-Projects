import argparse
from Instruction import Instruction
from pipelineFunctions import *

parser = argparse.ArgumentParser()
parser.add_argument(dest='filenames',metavar='filename',nargs='*')
args = parser.parse_args()
print args.filenames
#read of instructions
labels = {}
instructions = []
currentIndex = 0

rawInstructions = []
publishInstructions = []

with open(args.filenames[0], "r") as t:
    line = t.readline()
    while line:
        rawInstructions.append(line)
        lineList = line.split()
        if lineList[0].endswith(":"):
            labels[lineList[0][:-1]] = currentIndex
            lineList = lineList[1:]
        line = t.readline()
        currentIndex += 1
        
t.close()

memory = []
with open(args.filenames[1],"r") as data:
    word = data.readline()
    while word:
        memory.append(int(word.strip(), 2))
        word = data.readline()
        

data.close()

#index 32 will be the inUse for memory Addresses
memory.append([None])

#execution
registers = {"inUse":[],"dAccessRequests":0,"dCacheHits":0}

pipeline = {"Fetch":[None,0],"Decode":[None,0],"Execution1":[None,0],
            "Execution2":[None,0],"Execution3":[None,0],
            "Memory":[None,0], "WriteBack":[None,0],"stallBeforeFetch":0,
            "dataStall":0,"dataStallBool":False,"iAccessRequests":0,
            "instStallBool":0}

#2 blocks of 8 words
instructionCacheList = []
lastInstructionBlockUsed = 1
for i in range(16):
    instructionCacheList.append(9999)

#4 blocks of 4 words
#each val will be index of memory List
dataCacheList = [None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None]



publishList = []

rawIndex = 0
#for line in rawInstructions:
cycle = 1
line = "NOP"
#bools for haulting
done = False
halting = False
iCacheMiss = False
iCacheMisses = 0
while not done:
    if pipeline["stallBeforeFetch"] == 0 and not halting:
        if rawIndex not in instructionCacheList:
            iCacheMisses += 1
            iCacheMiss = True
            #i-cache miss
            pipeline["stallBeforeFetch"] += 23
            pipeline["instStallBool"] = 1
            for i in range(8):
                if (rawIndex + i) < len(rawInstructions):
                    if lastInstructionBlockUsed == 1:
                        instructionCacheList[i] = rawIndex + i
                    else:
                        instructionCacheList[i+8] = rawIndex + i
                else:
                    instructionCacheList[i] = 9999
                    
                    #pipeline["stallBeforeFetch"] -= 3
            
        else:
            #i-cache hit
            if rawIndex >= instructionCacheList[0] and rawIndex <= instructionCacheList[7]:
                lastInstructionBlockUsed = 0
            else:
                lastInstructionBlockUsed = 1

    if not pipeline["WriteBack"][0] == None and pipeline["WriteBack"][1] == 0:
        if pipeline["WriteBack"][0].name not in jumpInstructions:
            publishList[pipeline["WriteBack"][0].publishID][5] = cycle
        pipeline["WriteBack"] = [None,0]
    WriteBack(pipeline,cycle,publishList,dataCacheList,registers)
    Memory(pipeline,cycle,publishList,dataCacheList,registers,memory)
    Execution3(pipeline,cycle,publishList,dataCacheList,registers,memory)
    Execution2(pipeline,cycle,publishList,dataCacheList,registers,memory)
    rawIndex = Execution1(pipeline,cycle,publishList,dataCacheList,registers,memory,labels,rawIndex)
    Decode(pipeline,cycle,publishList,registers)
    if iCacheMiss:
        pipeline["Fetch"] = [None,0]
        iCacheMiss = False

    if not halting:
        line = rawInstructions[rawIndex]
        rawIndex = Fetch(pipeline,publishList,rawIndex,line)

    if cycle > 10:
        #DEBUGGING PIPELINE PROGRESSION
        print "pipeline[\"stallBeforeFetch\"]:",pipeline["stallBeforeFetch"]

        if pipeline["Fetch"][0]:
            print "Fetch :",pipeline["Fetch"][0].name,pipeline["Fetch"][1]
        if pipeline["Decode"][0]:
            print "Decode:",pipeline["Decode"][0].name,pipeline["Decode"][1]

        if pipeline["Execution1"][0]:
            print "Execu1:",pipeline["Execution1"][0].name,pipeline["Execution1"][1]
        if pipeline["Execution2"][0]:
            print "Execu2:",pipeline["Execution2"][0].name,pipeline["Execution2"][1]

        if pipeline["Execution3"][0]:
            print "Execu3:",pipeline["Execution3"][0].name,pipeline["Execution3"][1]

        if pipeline["Memory"][0]:
            print "Memory:",pipeline["Memory"][0].name,pipeline["Memory"][1]

        if pipeline["WriteBack"][0]:
            print "WriteB:",pipeline["WriteBack"][0].name,pipeline["WriteBack"][1]

        print "\n"

    if halting:
        done = True
        for stage in pipeline.values():
            if type(stage) == type([9]):
                if not stage[0] == None:
                    done = False

    if not pipeline["Fetch"][0] == None:
        if pipeline["Fetch"][0].name == "HLT":
            halting = True
            
    print "cycle:",cycle            

    #print "From Shit, dataStallBool:",pipeline["dataStallBool"]
    cycle += 1

    if cycle == 200:
        break

# print all the shit
with open(args.filenames[2], "w") as out:
    
    for inst in publishList:
        instruction = inst[0].split()
        if not instruction[0].endswith(":"):
            instruction = [" "] + instruction

        if len(instruction) == 2:
            string1 = "%-9s %-26s" % (instruction[0],instruction[1])
        else:
            string1 = "%-9s %-10s %-15s" % (instruction[0],instruction[1],instruction[2])
        
        print "%-34s %-4s %-4s %-4s %-4s %-4s" % (string1,str(inst[1]),str(inst[2]),str(inst[3]),str(inst[4]),str(inst[5]))
        line =  "%-34s %-4s %-4s %-4s %-4s %-4s\n" % (string1,str(inst[1]),str(inst[2]),str(inst[3]),str(inst[4]),str(inst[5]))
        out.write(line)

    out.write("\nTotal number of access requests for instruction cache: "+str(pipeline["iAccessRequests"]))
    out.write("\nNumber of instruction cache hits: "+str(pipeline["iAccessRequests"] - iCacheMisses))
    out.write("\n\nTotal number of access requests for data cache: "+str(registers["dAccessRequests"]))

    out.write("\nNumber of data cache hits: "+str(registers["dCacheHits"]))

print "Total number of access requests for instruction cache:",pipeline["iAccessRequests"]

print "Number of instruction cache hits:",pipeline["iAccessRequests"] - iCacheMisses

print "\nTotal number of access requests for data cache:",registers["dAccessRequests"]
print "Number of data cache hits:",registers["dCacheHits"]
out.close()
